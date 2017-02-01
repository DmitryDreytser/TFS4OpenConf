using Microsoft.TeamFoundation.Client;
using Microsoft.TeamFoundation.VersionControl.Client;
using OpenConf;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Linq;
using System.Diagnostics;
using System.Collections;
using Microsoft.TeamFoundation.VersionControl.Common;
using Microsoft.Win32;
using System.Runtime.ExceptionServices;
using System.Security;

namespace WorkWithTFS
{
    [ComVisible(true)]
    [ProgId("WorkWithTFS.Tools")]
    [ComSourceInterfaces(typeof(WorkWithTFS.ITools))]
    [ClassInterface(ClassInterfaceType.AutoDual)]
    [Description("Класс для работы с GComp и TFS")]
    public partial class Tools : ITools, IDisposable
    {
        #region Атрибуты 
        /// <summary>
        /// Объект для работы с проектами TFS
        /// </summary>
        public TfsTeamProjectCollection projects { get; set; }

        /// <summary>
        /// Репозиторий проекта TFS. Содержит данные о changeset'ах и прочее.
        /// </summary>
        public VersionControlServer versionControl { get; set; }

        /// <summary>
        /// Объект для работы с рабочей областью TFS 
        /// </summary>
        public Workspace workspace { get; set; }

        /// <summary>
        /// Путь к проекту на сервере TFS. Например http://ruvvos20006srv:8080/tfs/accounting
        /// </summary>
        public string ProjectServerName { get; set; }

        /// <summary>
        /// Локальный путь каталога рабочей области TFS
        /// </summary>
        public string WorkFolder { get; set; }

        /// <summary>
        /// Объект для работы с компонентой GComp
        /// </summary>
        public GCompTools gcomptools { get; set; }

        /// <summary>
        /// Флаг инициализации компоненты
        /// </summary>
        public bool IsInit = false;

        /// <summary>
        /// Серверный каталог с разобранными внешними отчетами
        /// </summary>
        public string ToolsServerFolder = @"$/Accounting/Developer/Tools/";

        /// <summary>
        /// Серверный каталог с файлами конфигурации
        /// </summary>
        public string ConfigurationServerFolder = @"$/Accounting/Developer/Configuration/";

        /// <summary>
        /// Серверный каталог с внешними отчетами
        /// </summary>
        public string ExternalReportsServerFolder = @"$/Accounting/Developer/External Reports/";

        /// <summary>
        /// Локальный каталог с разобранными внешними отчетами
        /// </summary>
        public string ExternalReportsDisassembledLocalFolder { get; set; }

        /// <summary>
        /// Локальный каталог с собранными внешними отчетами
        /// </summary>
        public string ExternalReportsAssembledLocalFolder { get; set; }


        /// <summary>
        /// Каталог информационной базы 1С
        /// </summary>
        public string IBFolder { get; set; }
        public string IBName { get; set; }

        /// <summary>
        /// Каталог информационной базы 1С
        /// </summary>
        public string PathToThisDll  { get; set; }

        /// <summary>
        /// Каталог информационной базы 1С
        /// </summary>
        public string DecompiledConfigurationName = "1Cv7.Developer.MD";

        public delegate bool DocReadonlyToggle(TextDoc Doc);

        public event DocReadonlyToggle TextDocSetReadOnly;
        public event DocReadonlyToggle TextDocUnSetReadOnly;

        private TreeForm TF;
        private WindowWrapper MainWindow;
        private NativeMenu.SubMenu MainMenu;
        #endregion

        private static OpenConf.Configurator _oConfigurator;

        public static OpenConf.Configurator oConfigurator
        {
            get
            {
                return _oConfigurator;
            }

            set
            {
                _oConfigurator = value;
            }
        }

        #region Методы по инициализации работы компоненты
        /// <summary>
        /// Оригинальный конструктор
        /// </summary>
        public Tools()
        {
             
        }
        public ArrayList PendingObjects = new ArrayList();
        /// <summary>
        /// Получение рабочего каталога TFS
        /// </summary>
        /// <param name="WorkSpaceName">Название рабочего места. Если не задано, то имя рабочей станции</param>
        /// <param name="Owner">Владелец рабочей области. Если не задано, то текущий пользователь</param>
        /// <returns>Локальный путь рабочего каталога TFS</returns>
        public string GetWorkFolder(string WorkSpaceName = "", string Owner = "")
        {
            WorkFolder = "";
            WorkSpaceName = WorkSpaceName == "" ? Environment.MachineName : WorkSpaceName;
            Owner = Owner == "" ? Environment.UserName : Owner;
            workspace = versionControl.GetWorkspace(WorkSpaceName, Owner);
            if (workspace != null)
            {
                foreach (var folder in workspace.Folders)
                {
                    if (!folder.IsCloaked)
                    {
                        WorkFolder = folder.LocalItem;
                        break;
                    }
                }
            }
            return WorkFolder;
        }

        /// <summary>
        /// Инициализация всех объектов для работы с компонентой
        /// </summary>
        /// <param name="pProjectServerName">Имя проекта на сервере TFS. Например: http://ruvvos20006srv:8080/tfs/accounting </param>
        /// <param name="pIBFolder">Каталог информационной базы 1С</param>
        /// <returns>1 - инициализация прошла успешно. 0 - инициализация не выполнена</returns>
        /// 
        public bool InitConnectionToTFS(string pProjectServerName)
        {
            return InitConnectionToTFS(pProjectServerName, null);
        }

        public FileSystemWatcher FSWatcher = null;
        public bool InitConnectionToTFS(string pProjectServerName = null, string pIBFolder = null)
        {
            IsInit = false;
            bool TFSIsOffline = false;

            if (string.IsNullOrEmpty(pIBFolder))
            {
                pIBFolder = _oConfigurator.IBDir;
                this.IBFolder = pIBFolder.TrimEnd('\\');
            }

            ConfigurationServerFolder = SettingsDialog.ConfigurationRootFolder ?? ConfigurationServerFolder;
            SettingsDialog.ConfigurationRootFolder = ConfigurationServerFolder;
            ExternalReportsServerFolder = SettingsDialog.ExtReportRootFolder ?? ExternalReportsServerFolder;
            SettingsDialog.ExtReportRootFolder = ExternalReportsServerFolder;

            if (!Directory.Exists(IBFolder)) return IsInit;
            oConfigurator.Status("Авторизуемся на сервере TF...");
            string WorkspaceName = IBFolder.Replace(":", "_").Replace("\\", "_");
            string WorkspaceRootPath = string.Format("{0}\\.tfs\\", IBFolder);

            if (!string.IsNullOrEmpty(pProjectServerName))
            {
                ProjectServerName = pProjectServerName;
                var uri = new Uri(ProjectServerName);
                projects = TfsTeamProjectCollectionFactory.GetTeamProjectCollection(uri);
                if (projects != null)
                {
                    versionControl = (VersionControlServer)projects.GetService(typeof(VersionControlServer));
                    if (versionControl == null)
                    {
                        TFSIsOffline = true;
                        throw new Exception("не удалось подключиться к проекту: " + pProjectServerName);
                    }
                    versionControl.Getting += VersionControl_Getting;
                    versionControl.GetCompleted += VersionControl_GetCompleted;
                }
                GetWorkFolder();
            }
            else
            {
                WorkspaceInfo IBworkspace = null;
                try
                {
                    WorkspaceInfo[] everything = Workstation.Current.GetAllLocalWorkspaceInfo();
                    foreach (var wsi in everything)
                    {
                        try
                        {
                            if (wsi.ServerUri.ToString().Contains("defaultcollection")) // Отчистить полностью пока не удалось, поэтому пока так
                            {
                                continue;
                            }
                            oConfigurator.Message(wsi.ServerUri.ToString());
                            var server = TfsTeamProjectCollectionFactory.GetTeamProjectCollection(wsi.ServerUri).GetService<VersionControlServer>();
                            Workstation.Current.UpdateWorkspaceInfoCache(server, server.AuthorizedUser);
                            if (wsi.MappedPaths.Contains(WorkspaceRootPath))
                                oConfigurator.Status("Обновлем кэш рабочих областей...");
                        }
                        catch (Exception ex)
                        {
                            //TFSIsOffline = true;
                            oConfigurator.Message("Ошибка обновления рабочей области:" + ex.Message, MsgLineMarkers.mRedErr);
                        }
                    }
                }
                catch (Exception ex)
                {
                    TFSIsOffline = true;
                    oConfigurator.Message("Ошибка обновления рабочей области:" + ex.Message, MsgLineMarkers.mRedErr);
                }

                var Servers = RegisteredTfsConnections.GetConfigurationServers();
                var Collections = RegisteredTfsConnections.GetProjectCollections();

                IBworkspace = Workstation.Current.GetAllLocalWorkspaceInfo().FirstOrDefault(t => t.MappedPaths.Contains(Path.Combine(WorkspaceRootPath, "Developer")));

                if (Servers.Length == 0 || IBworkspace == null)
                {
                    RegistryKey VSEntry = Registry.CurrentUser.OpenSubKey("Software\\Microsoft\\VisualStudio");
                    Decimal Ver;
                    string[] VS = VSEntry.GetSubKeyNames().Where(t => Decimal.TryParse(t.Replace('.', ','), out Ver)).ToArray();
                    foreach (string VSVer in VS)
                    {
                        var TFEntry = VSEntry.OpenSubKey(VSVer).OpenSubKey("TeamFoundation\\Instances");
                        if (TFEntry != null)
                        {
                            var ServerEntries = TFEntry.GetSubKeyNames().Where(t => TFEntry.OpenSubKey(t).GetValue("Uri").ToString().Contains(":8080/tfs")).ToArray();
                            foreach (string ServerName in ServerEntries)
                            {
                                var server = new TfsConfigurationServer(new Uri(TFEntry.OpenSubKey(ServerName).GetValue("Uri").ToString()), new TfsClientCredentials(true));
                                RegisteredTfsConnections.RegisterConfigurationServer(server);
                            }
                        }
                    }

                    Servers = RegisteredTfsConnections.GetConfigurationServers();

                    using (TeamProjectPicker Picker = new TeamProjectPicker(TeamProjectPickerMode.NoProject, false))
                    {
                        if (Picker.ShowDialog() == DialogResult.OK)
                        {
                            projects = Picker.SelectedTeamProjectCollection;
                        }
                        else
                        {
                            TFSIsOffline = true;
                        }

                    }
                }
                else// if (Collections.Length == 1)
                {
                    projects = TfsTeamProjectCollectionFactory.GetTeamProjectCollection(IBworkspace.ServerUri);//TfsTeamProjectCollectionFactory.GetTeamProjectCollection(Collections[0]);
                    workspace = IBworkspace.GetWorkspace(projects);
                }

                versionControl = projects.GetService<VersionControlServer>();
                versionControl.Getting += VersionControl_Getting;
                versionControl.GetCompleted += VersionControl_GetCompleted;

                try
                {
                    projects.EnsureAuthenticated();
                    Workstation.Current.EnsureUpdateWorkspaceInfoCache(versionControl, versionControl.AuthorizedUser);
                }
                catch (Exception ex)
                {
                    TFSIsOffline = true;
                    Debug.Print("InitConnectionToTFS() : " , ex.ToString() );
                }


                ProjectServerName = projects.Uri.ToString();
                //Workspace[] WsList = versionControl.QueryWorkspaces(WorkspaceName, Environment.UserName, Environment.MachineName);

                if (workspace == null)
                {
                    oConfigurator.Status("Создаем рабочую область...");
                    var NewWorkSpaceParameters = new CreateWorkspaceParameters(WorkspaceName) {
                        Comment = "Автоматически создана для базы " + IBFolder,
                        Computer = Environment.MachineName,
                        Folders = new WorkingFolder[] { new WorkingFolder("$/Accounting/Developer/", Path.Combine(WorkspaceRootPath, "Developer")) },
                        Location = WorkspaceLocation.Server,
                        OwnerDisplayName = Environment.UserName,
                        OwnerName = Environment.UserName,
                        RemoveUnparentedCloaks = true,
                        WorkspaceName = WorkspaceName,
                        WorkspaceOptions = WorkspaceOptions.SetFileTimeToCheckin
                    };

                    workspace = versionControl.CreateWorkspace(NewWorkSpaceParameters);
                    oConfigurator.Message("Создана рабочая область: " + WorkspaceName, MsgLineMarkers.mInformation);

                    GetRequest request = new GetRequest(new ItemSpec(ConfigurationServerFolder, RecursionType.Full), VersionSpec.Latest);
                    oConfigurator.Status("Актуализируем конфигурацию...");
                    GetStatus status = workspace.Get(request, GetOptions.Overwrite);
                }

                WorkFolder = WorkspaceRootPath;
            }

            IBName = oConfigurator.IBName;

            SettingsDialog.CurrentWorkSpace =  workspace.Name;
            SettingsDialog.CurrentServer =  ProjectServerName;
            SettingsDialog.CurrentProject  =  projects.Name;

            oConfigurator.Status("Инициализируем GComp...");
            gcomptools = new GCompTools();
            gcomptools.Init(MainWindow);
            gcomptools.onLog += Gcomptools_onLog;
            //gcomptools.onProgressChange += Gcomptools_onProgressChange;
            gcomptools.onFinishDecompile += Gcomptools_onFinishDeCompileTask;

            try
            {
                GetWorkFolder(WorkspaceName);

                if (WorkFolder != String.Empty)
                {
                    if (gcomptools.IsInit == 1)
                    {
                        oConfigurator.Message("Модуль для работы с GComp активирован.", MsgLineMarkers.mInformation);

                        ExternalReportsAssembledLocalFolder = IBFolder + "\\.tfs\\Developer\\External Reports Compiled";
                        Directory.CreateDirectory(ExternalReportsAssembledLocalFolder);

                        ExternalReportsDisassembledLocalFolder = workspace.TryGetLocalItemForServerItem(ExternalReportsServerFolder);// GetLocalItemForServerItem(ExternalReportsServerFolder);

                        TF = new TreeForm(this);
                        TF.onFinishUpdate += TF_onFinishUpdate;
                        TF.onStarthUpdate += TF_onStarthUpdate;

                        if (!TFSIsOffline)
                            IsInit = true;

                        FSWatcher = new FileSystemWatcher(WorkFolder)
                        {
                            NotifyFilter = NotifyFilters.Attributes
                        };
                        FSWatcher.Changed += FSWatcher_Changed;
                        FSWatcher.IncludeSubdirectories = true;
                        FSWatcher.EnableRaisingEvents = true;
                    }
                }
            }
            catch (Exception ex)
            {
                oConfigurator.Message(ex.Message, MsgLineMarkers.mRedErr);
            }

            // Проверка наличия новой версии
            PathToThisDll = System.Reflection.Assembly.GetExecutingAssembly().Location;// oConfigurator.BinDir + "config\\WorkWithTFS.dll";
            CheckNewVersion();

            return IsInit;
        }

        public void FSWatcher_Changed(object sender, FileSystemEventArgs e)
        {
            if (e.ChangeType == WatcherChangeTypes.Changed && (File.Exists(e.FullPath)))
            {

                //У файлов изменились атрибуты. Перезаполним список ожидающих изменнеий. 
                //Вдруг че взяли в работу или зачекнили с помощью TeamExplorer.

                PendingObjects.Clear();

                foreach (var Change in workspace.GetPendingChanges())
                    PendingObjects.Add(Change.ServerItem);

                SettingsDialog.ClearPendingList();
                foreach (string obj in PendingObjects)
                    SettingsDialog.AddObjectToPendingList(obj);
            }
        }

        public DateTime CheckNewVersion(bool Silent = false)
        {
            DateTime LastVersionDate = DateTime.MinValue;
            if (IsInit)
            {     
                try
                {
                    FileInfo FIdll = new FileInfo(PathToThisDll);
                    DateTime LWTime = FIdll.LastWriteTime.AddDays(0);

                    string DownloadsFolder = Path.GetDirectoryName(PathToThisDll);
                    string TempFolder = oConfigurator.BinDir +"temp\\";
                    if (Directory.Exists(TempFolder))
                    {
                        Directory.Delete(TempFolder,true);
                    }


                    string ServerFolderForDownload;
#if DEBUG
                    string TFS_Folder_WorkWithTFS = "$/Accounting/Developer/Tools/WorkWithTFS/WorkWithTFS";
                    ServerFolderForDownload = SettingsDialog.UpdateCheckPath ?? "$/Accounting/Developer/Tools/WorkWithTFS/WorkWithTFS/bin/Release/*";

#else
                    string TFS_Folder_WorkWithTFS = "$/Accounting/Production/Tools/WorkWithTFS/WorkWithTFS";
                    ServerFolderForDownload = SettingsDialog.UpdateCheckPath ?? "$/Accounting/Production/Tools/WorkWithTFS/WorkWithTFS/bin/Release/*";
#endif

                    SettingsDialog.UpdateCheckPath = ServerFolderForDownload;

                    List<Changeset> Changes = ((IEnumerable<Changeset>)versionControl.QueryHistory(
                                                        TFS_Folder_WorkWithTFS,
                                                        VersionSpec.Latest,
                                                        0,
                                                        RecursionType.Full,
                                                        null,
                                                        new ChangesetVersionSpec(1),
                                                        VersionSpec.Latest,
                                                        int.MaxValue,
                                                        true,
                                                        false
                                                        )).Where(x => x.CreationDate >= LWTime).ToList();

                    if (Changes.Count > 0)
                    {
                        LastVersionDate = Changes[0].CreationDate;

                        if (!Silent)
                        {
                            string strComments = "";
                            foreach (Changeset changeset in Changes)
                            {
                                strComments += String.Format("- {0}:  {1}\n\r", changeset.CreationDate.ToShortDateString(), changeset.Comment.Trim());
                            }

                            string UpdateFile = TempFolder + "!Обновить плагин.bat";
                            string text = String.Format(
@"Доступна новая версия плагина для работы с TFS (сбобра от {0}).
{1}
Необходимо закрыть конфигуратор и запустить под администратором файл {2}
Закрыть конфигуратор и перейти в каталог для обновления?", 
LastVersionDate.ToShortDateString(), 
strComments, 
UpdateFile);
                            string caption = "Проверка наличия обновлений";

                            if (MessageBox.Show(text, caption, MessageBoxButtons.YesNo) == DialogResult.Yes)
                            {
                                Directory.CreateDirectory(TempFolder);
                                ItemSet IS = versionControl.GetItems(ServerFolderForDownload);
                                using (StreamWriter sw = new StreamWriter(UpdateFile, false))
                                {
                                    foreach (var item in IS.Items)
                                    {
                                        string[] strs = item.ServerItem.Split('/');
                                        string filename = strs[strs.Length - 1];
                                        item.DownloadFile(TempFolder + filename);
                                        sw.WriteLine(String.Format("copy \"{0}\" \"{1}\"", TempFolder + filename, DownloadsFolder + "\\" + filename));
                                    }

                                    sw.WriteLine(String.Format("timeout /t 5"));
                                    // sw.WriteLine(String.Format("{0} config /D\"{1}\"", oConfigurator.CommandLine, oConfigurator.IBDir));
                                    sw.Close();
                                }

                                Process.Start("explorer", TempFolder);
                            
                                MainWindow.SendMessage((int)WinApi.WindowsMessages.WM_CLOSE, 0, 0); 
                            }
                        }
                    }

                }
                catch (Exception ex)
                {
                    oConfigurator.Message("Произошла ошибка проверки новой версии плагина для TFS: " + ex.Message);
                }
            }
            return LastVersionDate;
        }

        private Dictionary<string, System.Windows.Win32Window> WindowCache = new Dictionary<string, System.Windows.Win32Window>();

        private bool SetTableReadOnly(CfgDoc Doc, bool set, WorkBook Parent = null)
        {
            System.Windows.Win32Window ThisWindow = new System.Windows.Win32Window(new IntPtr(Windows.ActiveWnd.hWnd), false);

            var TableWindow = ThisWindow.Children.FirstOrDefault(t => t.ClassName == "AfxMDIFrame42");

            if (TableWindow != null)
            {
                if (set)
                {
                    TableWindow.Children.Last().Disable();
                     MainMenu.DisableItem("Та&блица");
                }
                else
                {
                    TableWindow.Children.Last().Enable();
                    MainMenu.EnableItem("Та&блица");
                }

                ThisWindow = null;
                return set;
            }
            else
            {
                return Doc.ReadOnly();
            }
            
        }

        private bool SetTextReadOnly(CfgDoc Doc, bool set, WorkBook Parent = null)
        {
            var ThisTextDoc = (TextDoc)Doc;
            ThisTextDoc.ReadOnly = set;
            return ThisTextDoc.ReadOnly;
        }

        private bool SetDlgReadOnly(CfgDoc Doc, bool set, WorkBook Parent = null)
        {
            System.Windows.Win32Window ThisWindow = new System.Windows.Win32Window(new IntPtr(Windows.ActiveWnd.hWnd), false);

            var dialogWindow = ThisWindow.Children.Where(t => t.ExtendedStyle.HasFlag(System.Windows.WinAPI.WindowStylesEx.WS_EX_DLGMODALFRAME)).FirstOrDefault();

            if (dialogWindow != null)
            {
                if (set)
                {
                    dialogWindow.Parent.Disable();
                    MainMenu.DisableItem("Д&иалог");
                }
                else
                {
                    dialogWindow.Parent.Enable();
                    MainMenu.EnableItem("Д&иалог");
                }
                ThisWindow = null;
                return set;
            }
            else
            {
                return Doc.ReadOnly();
            }

        }

        private bool SetWorkBookReadOnly(CfgDoc Doc, bool set, WorkBook Parent = null)
        {
            try
            {
                WorkBook ActiveWorkbook = (WorkBook)Doc;
                CfgDoc ActivePage = ActiveWorkbook.Page[ActiveWorkbook.ActivePage];
                bool result = ActivePage.ReadOnly(set, ActiveWorkbook);
                ActivePage = null;
                ActiveWorkbook = null;
                Doc = null;
                return result;
            }
            catch (Exception ex)
            {
                Debug.Print(ex.Message);
            }
            return false;
        }

        private void TF_onStarthUpdate()
        {
            oConfigurator.Status("Обновляется дерево внешней отчетности...");
        }

        private void TF_onFinishUpdate()
        {
            oConfigurator.Status("Завершено обновление дерева внешней отчетности...");
        }

        int CurrentObject = 0;

        private void VersionControl_GetCompleted(object sender, WorkspaceEventArgs e)
        {
            CurrentObject = 0;
        }
        #endregion

        #region Общие методы для работы TFS
        /// <summary>
        /// Скачивает объект из TFS в рабочий каталог
        /// </summary>
        /// <param name="ObjectName">Серверное имя объекта в TFS</param>
        /// <returns>Локальный путь объект</returns>
        public string GetObjectFromTFS(string ObjectName)
        {
            string Result = String.Empty;

            if (ObjectName == String.Empty)
            {
                return Result;
            }

            ItemSet items = versionControl.GetItems(ObjectName, VersionSpec.Latest, RecursionType.Full);
            try
            {
                Result = workspace.GetLocalItemForServerItem(items.Items[0].ServerItem);
                foreach (Item item in items.Items)
                {
                    string relativePath = workspace.GetLocalItemForServerItem(item.ServerItem);

                    switch (item.ItemType)
                    {
                        case ItemType.Any:
                            throw new ArgumentOutOfRangeException("Неизвестный тип объекта для получения из TFS");
                        case ItemType.File:
                            item.DownloadFile(relativePath);
                            break;
                        case ItemType.Folder:
                            Directory.CreateDirectory(relativePath);
                            break;
                    }
                }
            }
            catch (Exception ex)
            {
                oConfigurator.Message(ex.Message, MsgLineMarkers.mRedErr);
                Result = String.Empty;
                throw;
            }

            return Result;
        }

        public void OpenDocByServerPath(string ServerPath)
        {
            string DocName = String.Empty;
            if (ServerPath.Contains(ExternalReportsServerFolder) && ExternalReportsServerFolder != "$/")
            {
                DocName = ServerPath.Replace(ExternalReportsServerFolder, "");
                DocName = ExternalReportsAssembledLocalFolder + "\\" + (DocName.Substring(0, DocName.LastIndexOf(".ert/"))+ ".ert").Replace('/', '\\');
                oConfigurator.Documents.Open(DocName);
            }
            else 
            {
                DocName = GetDocNameByServerPath(ServerPath); 
                if (DocName != String.Empty)
                {
                    oConfigurator.Documents[DocName].Open();
                }
            } 
        }

        public string GetDocNameByServerPath(string ServerPath)
        {
            string DocName = String.Empty;
            string FileName = ServerPath.Replace(ConfigurationServerFolder, "").Replace("/", "\\");
            string[] parts = FileName.Split('\\');
            if (parts[0] == "ГлобальныйМодуль.1s")
            {
                DocName = parts[0];
            }
            else if (parts[0] == "Документы")
            {
                DocName = "Документ." + parts[1] + ".";
                if (parts[2] == "МодульПроведения.1s")
                {
                    DocName = DocName + "Модуль Документа";
                }
                else
                {
                    DocName = DocName + "Форма";
                }
            }
            else if (parts[0] == "Справочники")
            {
                DocName = "Справочник." + parts[1] + ".Форма";
            }
            else if (parts[0] == "Обработки")
            {
                DocName = "Обработка." + parts[1] + ".Форма";
            }
            else if (parts[0] == "Отчеты")
            {
                DocName = "Отчет." + parts[1] + ".Форма";
            }
            return DocName;
        }

        public string MapObject(string ObjectName, string DestObject = "")
        {
            if (DestObject == String.Empty)
            {
                DestObject = workspace.GetLocalItemForServerItem(ObjectName);
            }

            if (!workspace.IsServerPathMapped(ObjectName))
            {
                oConfigurator.Message("Сопоставляем серверному пути \"" + ObjectName + "\"  локальный путь \"" + DestObject + "\"");
                workspace.Map(ObjectName, DestObject);
            }

            oConfigurator.Message("Получаем последнюю версию \"" + ObjectName + "\"");
            GetRequest request = new GetRequest(new ItemSpec(ObjectName, RecursionType.Full), VersionSpec.Latest);
            GetStatus status = workspace.Get(request, GetOptions.Overwrite);
            var failures = status.GetFailures();

            foreach (var fail in failures)
            {
                oConfigurator.Message(fail.GetFormattedMessage(), MsgLineMarkers.mRedErr);
            }

            return "";
        }

        private void VersionControl_Getting(object sender, GettingEventArgs e)
        {
            CurrentObject++;
            oConfigurator.Message("Загружено \"" + e.TargetLocalItem + "\"", MsgLineMarkers.mInformation);
            oConfigurator.Status((CurrentObject * 100 / e.Total).ToString() + "%");
        }

        public string GetServerObjectByDoc(CfgDoc Doc)
        {
            string TFSDir = string.Empty;
            if (Doc.Type == DocTypes.docWorkBook)
            {
                bool IsExtReport = IsExternalReport(Doc);

                if (IsExtReport)
                {
                    TFSDir = ExternalReportsServerFolder +  Doc.path.Replace(ExternalReportsAssembledLocalFolder + "\\", "").Replace("\\","/");
                }
                else
                {
                    var DocWb = (WorkBook)Doc;
                    TFSDir = ConfigurationServerFolder + Doc.TFSDirectory();
                }
            }
            else if (Doc.Type == DocTypes.docText)
            {
                TFSDir = Doc.TFSDirectory();
                if (!string.IsNullOrEmpty(TFSDir))
                {
                    TFSDir = ConfigurationServerFolder + Doc.TFSDirectory();

                }
            }

            bool ItemExists = true;
            try
            {
                ItemExists = versionControl.ServerItemExists(TFSDir, ItemType.Any);
            }
            catch (Exception)
            {
                ItemExists = false;
            }

            if (!ItemExists)
            {
                //oConfigurator.Message("Объект не существует в TFS");
                TFSDir = string.Empty;
            }

            return TFSDir;
        }


        public bool UndoCheckOutCurrentWnd()
        {
            var ActiveWnd =Windows.ActiveWnd;
            if (ActiveWnd != null)
            {
                var Doc =Windows.ActiveWnd.Document;
                if (Doc != null)
                {
                    string TFSDir = GetServerObjectByDoc(Doc);

                    if (!string.IsNullOrEmpty(TFSDir))
                    {
                        int CountObjects = workspace.Undo(TFSDir, RecursionType.Full);
                        if (CountObjects == 0)
                        {
                            oConfigurator.Message("Не удалось отменить: " + TFSDir);
                            return false;
                        }
                        else
                        {
                            Doc.ReadOnly(true);
                            MainMenu.GetSubMenu("TFS")?.DisableItem("Отменить взятие объекта в работу");
                            MainMenu.GetSubMenu("TFS")?.EnableItem("Взять объект в работу");
                            return true;
                        }
                    }
                    else
                    {
                        oConfigurator.Message("Объект отсутствует в TFS");
                    }
                }
            }
            return false;
        }

        public bool CheckOutCurrentWnd()
        {
            var ActiveWnd =Windows.ActiveWnd;
            if (ActiveWnd != null)
            {
                var Doc = Windows.ActiveWnd.Document;
                if (Doc != null)
                {
                    string TFSDir = GetServerObjectByDoc(Doc);

                    if (!string.IsNullOrEmpty(TFSDir))
                    {
                        MapObject(TFSDir);

                        int CountObjects = workspace.PendEdit(TFSDir, RecursionType.Full);
                        if (CountObjects == 0)
                        {
                            oConfigurator.Message("Не удалось взять объект в работу: " + TFSDir);
                            return false;
                        }
                        else
                        {
                            Doc.ReadOnly(false);

                            MainMenu.GetSubMenu("TFS")?.EnableItem("Отменить взятие объекта в работу");
                            MainMenu.GetSubMenu("TFS")?.DisableItem("Взять объект в работу");

                            return true;
                        }
                    }
                    else
                    {
                        oConfigurator.Message("Объект отсутствует в TFS");
                    }
                }
            }

            return false;
        }

        public bool IsExternalReport(CfgDoc Object)
        {
            return Object.ID == -1;
        }

        #endregion

        #region Методы для работы с конфигурацией 1С
        public string CompileConfiguration(string ConfigurationFilePath, string SourcePath)
        {
            if (Directory.Exists(SourcePath))
            {
                oConfigurator.Status("Компилируется конфигурация...");
                gcomptools.CompileConfiguration(ConfigurationFilePath, SourcePath);
            }
            else
                oConfigurator.Message("Не найден каталог с исходными текстами", MsgLineMarkers.mRedErr);
            return "";
        }

        public string CompileConfiguration(string ConfigurationFilePath, string SourcePath, string PassWord)
        {
            CompileConfiguration(ConfigurationFilePath, SourcePath);
            Compound MD = new Compound(ConfigurationFilePath);
            MD.SetPassword(PassWord);
            MD.Save(ConfigurationFilePath);
            oConfigurator.Message("Установлен пароль конфигурации \"" + PassWord + "\"", MsgLineMarkers.mRedErr);
            return "";
        }

        public string DeCompileConfiguration(string ConfigurationFilePath, string SourcePath)
        {
            Compound MD = new Compound(ConfigurationFilePath);
            if (MD.IsEncrypted)
            {
                MD.SetPassword(string.Empty);
                MD.Save(ConfigurationFilePath);
                oConfigurator.Message("Снят пароль конфигурации", MsgLineMarkers.mRedErr);
            }
            gcomptools.DecompileConfiguration(ConfigurationFilePath, SourcePath);
            return "";

        }

        public void DeCompileCurrentConfiguration()
        {
            oConfigurator.Status("Разбираем текущую конфигурацию...");
            DeCompileConfiguration(Path.Combine(IBFolder, "1cv7.md"), workspace.GetLocalItemForServerItem(ConfigurationServerFolder));
        }

        bool metadataChanged = false;

        ArrayList Updated = new ArrayList();
        ArrayList Created = new ArrayList();
        ArrayList Deleted = new ArrayList();
        private void Gcomptools_onLog(string pMessage)
        {
            string prefix = pMessage.Substring(0, pMessage.IndexOf(':') + 1);
            string obj = pMessage.Replace(prefix + " ", "");

            if (prefix.Contains("PRE_"))
                return;

            if (obj.Contains("gcomp.ver"))
                return;

            if (obj.Contains("GUIDData"))
                return;

                switch (prefix)
            {
                case "DEL:":
                    {
                        Deleted.Add(workspace.TryGetServerItemForLocalItem(obj, true));
                      //  oConfigurator.Message(pMessage, MsgLineMarkers.mUnderlinedErr);
                        break;
                    }
                case "ERR:":
                    {
                        oConfigurator.Message(pMessage, MsgLineMarkers.mUnderlinedErr);
                        break;
                    }
                case "NEW:":
                    {
                        Created.Add(workspace.TryGetServerItemForLocalItem(obj, true));
                       //oConfigurator.Message(pMessage, MsgLineMarkers.mBlueTriangle);
                        break;
                    }
                case "UPD:":
                    {
                        string ServerPath = workspace.GetServerItemForLocalItem(obj);
                        if (!PendingObjects.Contains(ServerPath))
                            Updated.Add(ServerPath);
                        //oConfigurator.Message(pMessage, MsgLineMarkers.mInformation);
                        break;
                    }
                case "WARN:":
                    {
                        //WARN: Не найден объект с идентификатором 47741
                        oConfigurator.Message(pMessage, MsgLineMarkers.mExclamation);
                        break;
                    }
                case "INF:":
                    break;
                default:
                    oConfigurator.Message(pMessage, MsgLineMarkers.mNone);
                    break;
            }

        }

        private void Gcomptools_onProgressChange(int CurrentProgress)
        {
            oConfigurator.Status(string.Format("{0} %", CurrentProgress));
        }

        private void Gcomptools_onFinishCompileTask()
        {
            oConfigurator.Status("");
            switch (GCompTools.Params.CompoundType)
            {
                case GComp.GCompWrapper.CompoundTypes.external_report:
                    {
                        oConfigurator.Message("Скомпилирован внешний отчет" + GCompTools.Params.CompoundFileName);
                        break;
                    }
                case GComp.GCompWrapper.CompoundTypes.meta_data:
                    {
                        oConfigurator.Message("Скомпилирована конфигурация" + GCompTools.Params.CompoundFileName);
                        break;
                    }
            }

        }

        private void Gcomptools_onFinishDeCompileTask()
        {
            oConfigurator.Status("");
            switch (GCompTools.Params.CompoundType)
            {
                case GComp.GCompWrapper.CompoundTypes.external_report:
                    {
                        oConfigurator.Message("Декомпилирован внешний отчет: " + GCompTools.Params.CompoundFileName);
                        break;
                    }
                case GComp.GCompWrapper.CompoundTypes.meta_data:
                    {
                        metadataChanged = Updated.Contains(Path.Combine(ConfigurationServerFolder, "ОбъектыМетаданных.txt"));

                        if (metadataChanged)
                            if (MessageBox.Show(MainWindow, "Изменились идентификаторы объектов.\r\nНеобходимо взять в работу файл \"ОбъектыМетаданных.txt\".\r\nЕсли не взять файл в работу то он будет заменен на актуальный из хранилища сервера.\r\nСделать это сейчас? ", "Вопрос", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation) == DialogResult.Yes)
                            {
                                workspace.PendEdit(ConfigurationServerFolder + "ОбъектыМетаданных.txt");
                                //Debug.Print("Checkout {0}", ConfigurationServerFolder + "ОбъектыМетаданных.txt");
                            }
                        
                        oConfigurator.Status("Выполняется анализ обновленных, удаленных и добавленных файлов...");
                        int total = Created.Count + Updated.Count + Deleted.Count;
                        int current = 0;

                        foreach (string obj in Created)
                        {
                            current++;
                            oConfigurator.Status(string.Format("Выполняется анализ обновленных, удаленных и добавленных файлов {0}%", (current * 100 / total)));
                            if(!PendingObjects.Contains(obj))
                                if (workspace.Get(new GetRequest(obj, RecursionType.None, VersionSpec.Latest), GetOptions.Preview).NumFiles == 0)
                                    oConfigurator.Message("Файл не существует на сервере. Нужно выполнить Add. :" + obj, MsgLineMarkers.mExclamation);
                        }

                        ItemSpec[] ItemsToRestore = new ItemSpec[Updated.Count];
                        foreach (string obj in Updated)
                        {
                            current++;
                            oConfigurator.Status(string.Format("Выполняется анализ обновленных, удаленных и добавленных файлов {0}%", (current * 100 / total)));
                            oConfigurator.Message("Файл был обновлен при разборке, но не взят в работу :" + obj, MsgLineMarkers.mExclamation);
                            string localItem = workspace.GetLocalItemForServerItem(obj);
                            ItemsToRestore[Updated.IndexOf(obj)] = new ItemSpec(obj, RecursionType.None);
                        }

                        if (ItemsToRestore.Length != 0)
                        {
                            var Restore = MessageBox.Show(MainWindow, "Были обновлены файлы не взятые в работу. \r\nОни не будут автоматически загружены с сервреа при очередном обновлении локального хранилища.\r\nЭто приведет к тому, что конфигурация собранная в будущем не будет соответствовать актуальной.\r\nВернуть измененный файлы сейчас?", "Вопрос", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                            if (Restore == DialogResult.Yes)
                            {
                                var res = workspace.GetItems(ItemsToRestore, DeletedState.NonDeleted, ItemType.File, true, GetItemsOptions.Download);
                                foreach (var itemset in res)
                                    foreach (var item in itemset.Items)
                                    {
                                        oConfigurator.Status(string.Format("Загружается файл {0}", item.ServerItem));
                                        item.DownloadFile(item.LocalItem);
                                        File.SetLastWriteTime(item.LocalItem, item.CheckinDate);
                                        File.SetAttributes(item.LocalItem, FileAttributes.ReadOnly);
                                        oConfigurator.Message("Отменены изменения объекта: " + item.LocalItem);
                                    }
                            }
                            else
                            {
                                Restore = MessageBox.Show(MainWindow, "Взять в работу?", "Вопрос", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                                if (Restore == DialogResult.Yes)
                                {
                                    workspace.PendEdit((string[])Updated.ToArray(typeof(string)));
                                }
                            }  
                        }

                        foreach (string obj in Deleted)
                        {
                            current++;
                            oConfigurator.Status(string.Format("Выполняется анализ обновленных, удаленных и добавленных файлов {0}%", (current * 100 / total)));
                            if (!PendingObjects.Contains(obj))
                            {
                                if(workspace.PendDelete(obj) != 0)
                                    oConfigurator.Message("Файл был удален. Удаление добавлено в набор изменений :" + obj, MsgLineMarkers.mExclamation);
                                
                            }
                        }

                        Deleted.Clear();
                        Updated.Clear();
                        Created.Clear();
                        oConfigurator.Status("");
                        oConfigurator.Message("Декомпилирована конфигурация: " + GCompTools.Params.CompoundFileName, MsgLineMarkers.mMetaData);
                        break;
                    }
            }
        }

        public void GetLastVersionOfConfiguration()
        {
            oConfigurator.Status("Получаем последнюю версию конфигурации...");
            string DestObject = workspace.GetLocalItemForServerItem(ConfigurationServerFolder);
            MapObject(ConfigurationServerFolder, DestObject);

            string NewConfigFile = Path.Combine(Path.GetDirectoryName(DestObject), DecompiledConfigurationName);

            oConfigurator.Message("Компилируется конфигурация \"" + NewConfigFile + "\"", MsgLineMarkers.mMetaData);
            oConfigurator.Message("----------------------------------------------------------------------------------------------------------------");
            gcomptools.onFinishCompile -= Gcomptools_onFinishCompileTask; // Не корректно вызываются несколько обработчиков событий. Уберем дефолтный.
            gcomptools.onFinishCompile += Gcomptools_onFinishGetLatest;
            CompileConfiguration(NewConfigFile, DestObject);
        }

        private void Gcomptools_onFinishGetLatest()
        {

            string NewConfigFile = GCompTools.Params.CompoundFileName;
            gcomptools.onFinishCompile -= Gcomptools_onFinishGetLatest;
            gcomptools.onFinishCompile += Gcomptools_onFinishCompileTask;
            if (gcomptools.TaskResult)
            {
                while (Windows.ActiveWnd != null)
                   Windows.ActiveWnd.Close();

                oConfigurator.Message("----------------------------------------------------------------------------------------------------------------");
                oConfigurator.Message("Скомпилирована конфигурация \"" + NewConfigFile + "\"", MsgLineMarkers.mMetaData);
                oConfigurator.Message("Загружется измененная конфигурацию из файла \"" + NewConfigFile + "\"", MsgLineMarkers.mMetaData);
                oConfigurator.Status("Загружется измененная конфигурацию из файла \"" + NewConfigFile + "\"");
                oConfigurator.OnFileDialog += OConfigurator_OnFileDialog; // Установим обработчик диалога "Загрузка конфигурации"
                oConfigurator.SendCommand(ConfigCommands.cmdLoadMD);
            }
            else
            {
                oConfigurator.Message("Ошибка компиляции файла \"" + NewConfigFile + "\".", MsgLineMarkers.mBlackErr);
                oConfigurator.Status("");
            }
        }

        private void OConfigurator_OnFileDialog(bool Saved, string Caption, string Filter, ref object FileName, ref object Answer)
        {
            // Отключим обработчик диалога "Загрузка конфигурации"
            oConfigurator.OnFileDialog -= OConfigurator_OnFileDialog;

            FileName = GCompTools.Params.CompoundFileName;
            Answer = 1;
            oConfigurator.Status("");
        }


        public string SendConfiguration()
        {
            string NewConfigFile = IBFolder + "\\1Cv7.MD";
            string ConfigurationLocalFolder = workspace.GetLocalItemForServerItem(ConfigurationServerFolder);
            gcomptools.DecompileConfiguration(NewConfigFile, ConfigurationLocalFolder);
            return "";
        }

        #endregion

        #region Методы для работы с внешней отчетностью 1С
        /// <summary>
        /// Получение последней версии внешнего отчета из TFS и помещение его в "[Каталог ИБ]\.tfs\Developer\External Reports\[Полнй путь отчета в ВО]"
        /// </summary>
        /// <param name="ObjectName">Серверное имя внешнего объекта</param>
        /// <returns>Полное локальное имя собранного файла</returns>
        public string GetLastVersionOfExternalReport(string ObjectName)
        {
            LogAdd(String.Format("Началось получение последней версии отчета: \"{0}\"", ObjectName));
            string ObjectLocalPath = GetObjectFromTFS(ObjectName);
            if (ObjectLocalPath == String.Empty)
            {
                return String.Empty;
            }
            
            string ResultFile = ObjectLocalPath.Replace(ExternalReportsDisassembledLocalFolder, ExternalReportsAssembledLocalFolder);
            string ResDirectory = Path.GetDirectoryName(ResultFile);
            LogAdd(String.Format("Создан каталог: \"{0}\"", ResDirectory));
            Directory.CreateDirectory(ResDirectory);

            ModifyFolder.SetIcoToFolder(ObjectLocalPath, PathToThisDll); 

            gcomptools.onFinishCompile -= Gcomptools_onFinishCompileTask;
            gcomptools.onFinishCompile += Gcomptools_onFinishCompileExtReportTask;

            gcomptools.CompileExternalReport(ObjectLocalPath, ResultFile);
            LogAdd(String.Format("Собран отчет \"{0}\" из \"{1}\"", ResultFile, ObjectLocalPath));
            return ResultFile;
        }

        private void Gcomptools_onFinishCompileExtReportTask()
        {

            oConfigurator.Documents.Open(GCompTools.Params.CompoundFileName);
            //Не забываем отключать одноразовые обработчики событий.
            gcomptools.onFinishCompile -= Gcomptools_onFinishCompileExtReportTask;
            gcomptools.onFinishCompile += Gcomptools_onFinishCompileTask;
        }

        /// <summary>
        /// Открывает окно для выбора внешнего отчета из TFS
        /// </summary>
        /// <param name="SourceFolder">Каталог на сервере, который будет корневым в дереве</param>
        /// <returns>Серверный путь выбранного отчета. Если не выбрано ничего, то возвращается пустая строка</returns>
        public string SelectExternalReportFromTFS(string SourceFolder = "")
        {
            string result = "";
            if (SourceFolder == String.Empty)
                SourceFolder = ExternalReportsServerFolder;

            TF.SourceFolder = SourceFolder;
            TF.OnlyFolders = false;
            TF.EditMode = false;

            LogAdd(String.Format("Из TFS выбирается внешний отчет:  \"{0}\"", TF.SelectedItem));

            if (TF.ShowDialog(MainWindow) == DialogResult.OK)
            {    
                TreeForm.Ert ert = TF.SelectedItem;

                LogAdd(String.Format("Из TFS выбран отчет:  \"{0}\"", ert.ServerPath));
                result = ert.ServerPath;
            }
            else
            {
                LogAdd("Отменен выбор отчета");
            }

            return result;
        }

        /// <summary>
        /// Открывает окно для выбора каталога в TFS
        /// </summary>
        /// <param name="SourceFolder">Каталог на сервере, который будет корневым в дереве</param>
        /// <returns>Серверный путь выбранного каталога. Если не выбрано ничего, то возвращается пустая строка</returns>
        public string SelectFolderInTFS(string SourceFolder = "")
        {
            string result = "";
            if (SourceFolder == String.Empty)
            {
                SourceFolder = ExternalReportsServerFolder;
            }
            TF.OnlyFolders = true;
            TF.EditMode = true;
            TF.SourceFolder = SourceFolder;

            if (TF.ShowDialog(MainWindow) == DialogResult.OK)
            {
                TreeForm.Ert ert = TF.SelectedItem;
                if (!String.IsNullOrEmpty(ert.ServerPath))
                {
                    LogAdd(String.Format("Из TFS выбран каталог:  \"{0}\"", ert.ServerPath), true);
                    result = ert.ServerPath;
                }
                else
                {
                    LogAdd("Отменен выбор каталога, т.к. выбранный каталог не содержит серверного пути", true);
                }        
            }
            else
            {
                LogAdd("Отменен выбор каталога");
            }
            return result;
        }

        /// <summary>
        /// Помещает отчет/обработку во внешнюю отчетность TFS предварительно разобрав его на исходные файлы
        /// </summary>
        /// <param name="ExternalReportFile">Полный путь к отчету/обработке</param>
        /// <param name="SelectedFolderTFS">Серверный путь к каталогу TFS, куда должны быть помещены исходные файлы отчета/обработки</param>
        /// <returns>Возвращает путь к разобранному отчету</returns>
        public string SendReportToTFS(string ExternalReportFile, string SelectedFolderTFS)
        {
            LogAdd(String.Format("Начинается разбор внешнего отчета: \"{0}\" в \"{1}\"", ExternalReportFile, SelectedFolderTFS));
            string NewReportLocalPath = SelectedFolderTFS;
            if (SelectedFolderTFS.StartsWith("$"))
            {
                NewReportLocalPath = SelectedFolderTFS.Replace(ExternalReportsServerFolder, ExternalReportsDisassembledLocalFolder + "\\").Replace("/", "\\");
            }

            NewReportLocalPath = NewReportLocalPath.TrimEnd('\\') + "\\" + Path.GetFileName(ExternalReportFile);
            LogAdd(String.Format("Создан каталог: \"{0}\"", NewReportLocalPath));
            Directory.CreateDirectory(NewReportLocalPath);

            gcomptools.DecompileExternalReport(ExternalReportFile, NewReportLocalPath);
            
            LogAdd(String.Format("Отчет \"{0}\" разобран в \"{1}\"", ExternalReportFile, NewReportLocalPath));
            
            return NewReportLocalPath;
        }

        public void Dispose()
        {
            try
            {
                MainWindow.MainMenu?.Dispose();
                MainWindow.Dispose();
                SettingsDialog.Dialog?.Destroy();
                SettingsDialog = null;
            }
            catch (Exception Ex)
            {
                MessageBox.Show("Ошибка в деструкторе:" + Ex.Message);
            }
        }

        #endregion

        #region Меню в конфигураторе

        public string Init(Configurator pConfigurator)
        {
            Tools.oConfigurator = pConfigurator;
            oConfigurator.AllPluginsInit += OConfigurator_AllPluginsInit;
            //oConfigurator.OnIdle += OConfigurator_OnIdle;
            IBName = oConfigurator.IBName;
            
            SettingsDialog = new Settings(this);

            AppDomain.CurrentDomain.UnhandledException += CurrentDomain_UnhandledException;
            Application.ThreadException += Application_ThreadException;
            Timer timer = new Timer();
            timer.Tick += Timer_Tick;
            timer.Interval = 3000;
            timer.Start();
            return "TFS";
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            CheckSaveCurrentWindow();
        }

        DateTime Last = DateTime.Now;


        Dictionary<string, int> TextHistory = new Dictionary<string, int>();
        public CfgWindows Windows = null;

        private void CheckSaveCurrentWindow()
        {
            int kk;
            try
            {
                if (Windows.ActiveWnd != null)

                    if (Windows.ActiveWnd.Caption.Contains("Форма") ||Windows.ActiveWnd.Caption.Contains("Модуль"))
                    {
                        dynamic doc = Windows.ActiveWnd.Document;

                        DocTypes DocType = (DocTypes)doc.Type;

                        if (DocType == DocTypes.docWorkBook)
                        {
                            int ActivePAge = ((WorkBook)doc).ActivePage;
                           // Marshal.ReleaseComObject(((WorkBook)doc).ActivePage);

                            doc = doc.Page[ActivePAge];
                            DocType = (DocTypes)doc.Type;
                        }

                        if (!((CfgDoc)doc).ReadOnly())

                            switch (DocType)
                            {
                                case DocTypes.docText:
                                    int NewHash = doc.text.GetHashCode();
                                    if (TextHistory.ContainsKey(doc.Path))
                                    {
                                        if (TextHistory[doc.Path] != NewHash)
                                        {
                                            File.WriteAllText(Path.Combine(WorkFolder, ((TextDoc)doc).TFSFileName()).Replace("/", "\\"), doc.text, System.Text.Encoding.GetEncoding(1251));
                                            TextHistory[doc.Path] = NewHash;
                                        }
                                    }
                                    else
                                        TextHistory[doc.Path] = NewHash;
                                    break;
                                case DocTypes.docDEdit:
                                    if (Windows.ActiveWnd.Caption.Contains("*"))
                                    { }
                                    break;
                                case DocTypes.docTable:
                                    //if (Windows.ActiveWnd.Caption.Contains("*"))
                                    //((TableDoc)doc).SaveToFile(Path.Combine(WorkFolder, ((CfgDoc)doc).TFSFileName()).Replace("/", "\\"));
                                    break;
                            }

                        //kk = Marshal.ReleaseComObject(doc);
                        doc = null;
                        kk = Marshal.FinalReleaseComObject(Windows.ActiveWnd);
                    }
               // kk = Marshal.FinalReleaseComObject(oConfigurator.Windows);
            }
            catch (Exception ex)
            {
                Debug.Print(ex.Message);
            }
        }

        private void Application_ThreadException(object sender, System.Threading.ThreadExceptionEventArgs e)
        {
            MessageBox.Show(e.Exception.Message, "Необработанное исключение");
            oConfigurator?.Status("Необработанное исключение." + e.Exception.Message);
            Debug.Print(e.Exception.Message.ToString());
        }

        private void CurrentDomain_UnhandledException(object sender, UnhandledExceptionEventArgs e)
        {
            MessageBox.Show(e.ExceptionObject.ToString(), "Необработанное исключение");
            oConfigurator?.Status("Необработанное исключение." + e.ExceptionObject.ToString());
            Debug.Print(e.ExceptionObject.ToString());
        }

        private bool NewObjectCreating = false;
        internal  ArrayList StatusLog = new ArrayList();
        private void OConfigurator_AllPluginsInit()
        {
            oConfigurator.AllPluginsInit -= OConfigurator_AllPluginsInit;
            Windows = oConfigurator.Windows;
            oConfigurator.Message("Начинаем инициализацию");


            try
            {
                MainWindow = new WindowWrapper(new IntPtr(Windows.MainWnd.hWnd), new NativeMenu.UpdateMenu(MenuConstructor));
                //MainWindow.MainMenu.PopUpMenuTracker = new NativeMenu.PopUpMenuInit(OnPopUpMenu);
                MainWindow.MainMenu.CommandMap.Add(20070, delegate (int comandId)  //Отслеживаем переключение ReadOnly для текста
                {
                    return OnToggleReadOnly();
                });

                MainWindow.MainMenu.CommandMap.Add(33710, delegate (int comandId)  //Отслеживаем Создание нового объекта
                {
                    NewObjectCreating = true;
                    return true;
                });

                //WindowMessageFilter(WindowWrapper Window, NativeMenu.WindowsMessages uMsg, IntPtr wParam, IntPtr lParam);
                MainWindow.WindowMessageMap.Add((NativeMenu.WindowsMessages)866,  delegate (WindowWrapper Window, NativeMenu.WindowsMessages msg, IntPtr wParam, IntPtr lParam)  //Отслеживаем текст в статустной строке
                {
                    string text = Marshal.PtrToStringAnsi(lParam);
                    if (!string.IsNullOrEmpty(text))
                    {
                        LogAdd(text);
                    }
                    return true;
                });

                //MainWindow.WindowMessageMap.Add(NativeMenu.WindowsMessages.WM_PARENTNOTIFY, delegate (WindowWrapper Window, NativeMenu.WindowsMessages msg, IntPtr wParam, IntPtr lParam)  //Отслеживаем активацию окон
                //{
                //    if(Windows.ActiveWnd != null) 
                //        OConfigurator_OnActivateWindow(Windows.ActiveWnd, true);
                //    return true;
                //});

                //MainWindow.WindowMessageMap.Add(NativeMenu.WindowsMessages.WM_NCACTIVATE, delegate (WindowWrapper Window, NativeMenu.WindowsMessages msg, IntPtr wParam, IntPtr lParam)  //Отслеживаем активацию окон
                //{
                //    if (Windows.ActiveWnd != null)
                //        OConfigurator_OnActivateWindow(Windows.ActiveWnd, true);
                //    return true;
                //});


                iCfgDocExtension.AddReadOnlyOperationHandler(DocTypes.docWorkBook, new iCfgDocExtension.ReadOnlyState_handler(SetWorkBookReadOnly));
                iCfgDocExtension.AddReadOnlyOperationHandler(DocTypes.docDEdit, new iCfgDocExtension.ReadOnlyState_handler(SetDlgReadOnly));
                iCfgDocExtension.AddReadOnlyOperationHandler(DocTypes.docTable, new iCfgDocExtension.ReadOnlyState_handler(SetTableReadOnly));
                iCfgDocExtension.AddReadOnlyOperationHandler(DocTypes.docText, new iCfgDocExtension.ReadOnlyState_handler(SetTextReadOnly));

                Windows.MainWnd.Maximized = true;
                MainWindow.SendMessage(0x0006, 2, 0); //WindowActivate

                InitConnectionToTFS(); //"http://vv1000070146pc:8080/tfs/accounting"
                MainWindow.SendMessage(0x0006, 2, 0);

                if (IsInit)
                {
                    oConfigurator.Message("Модуль для работы с TFS активирован");

                    //var vsExt = new Microsoft.VisualStudio.TeamFoundation.VersionControl.VersionControlExt  as VersionControlExt;

                    versionControl.NewPendingChange += VersionControl_NewPendingChange;
                    versionControl.UndonePendingChange += VersionControl_UndonePendingChange;
                    foreach (var Change in workspace.GetPendingChanges())
                        PendingObjects.Add(Change.ServerItem);
                    
                }
                else
                {
                    oConfigurator.Message("Модуль для работы с TFS не активирован");
                }

                Windows.MainWnd.Maximized = true;
                TextDocUnSetReadOnly += Tools_TextDocUnSetReadOnly;
                oConfigurator.OnActivateWindow += OConfigurator_OnActivateWindow;

                oConfigurator.SendCommand(ConfigCommands.cmdOpenConfigWnd);
                //oConfigurator.SendCommand((ConfigCommands)33281); //Очистим окно собщений.


            }
            catch (Exception ex)
            {
                oConfigurator.Message(ex.Message, MsgLineMarkers.mRedErr);
            }
        }

        public void LogAdd(string text, bool AddMessage = false)
        {
            string ftext = string.Format("{0};{1};{2}", DateTime.Now, IBFolder, text);
            StatusLog.Add(ftext);
            SettingsDialog.UpdateLog(ftext);
            if (AddMessage)
            {
                oConfigurator.Message(text);
            }
        }

        private bool Tools_TextDocUnSetReadOnly(TextDoc Doc)
        {
            return !((CfgDoc)Doc).ReadOnly();
        }

        private void VersionControl_UndonePendingChange(object sender, PendingChangeEventArgs e)
        {
            PendingObjects.Remove(e.PendingChange.ServerItem);
            SettingsDialog.RemoveObjectFromPendingList(e.PendingChange.ServerItem);
            oConfigurator.Message("Отмена: " + e.PendingChange.LocalItem, MsgLineMarkers.mInformation);
        }

        private void VersionControl_NewPendingChange(object sender, PendingChangeEventArgs e)
        {
            PendingObjects.Add(e.PendingChange.ServerItem);
            SettingsDialog.AddObjectToPendingList(e.PendingChange.ServerItem);
            oConfigurator.Message("Взято в работу: " + e.PendingChange.LocalItem, MsgLineMarkers.mInformation);
        }

        private void OnPopUpMenu(NativeMenu.SubMenu PoUpMenu)
        {

            //var Doc = Windows.ActiveWnd.Document;

            //if (Doc.Type == DocTypes.docWorkBook)
            //{
            //    var DocWb = (WorkBook)Doc;
            //    int k = DocWb.ActivePage();
            //    oConfigurator.Message("Док : " + DocWb.Page[k].TFSFileName(DocWb));
            //}
            //else
            //    oConfigurator.Message("Док : " + ((ICfgDoc)Doc).TFSFileName());

        }


        ArrayList NewObjects = new ArrayList();
        Dictionary<IntPtr, WindowWrapper> OtherWindowCashe = new Dictionary<IntPtr, WindowWrapper>();
        Dictionary<IntPtr, System.Windows.SysTabControl32> Tabs = new Dictionary<IntPtr, System.Windows.SysTabControl32>();

        IntPtr LastWindow = IntPtr.Zero;

        [SecurityCritical]
        [HandleProcessCorruptedStateExceptions]
        private void OConfigurator_OnActivateWindow(CfgWindow Wnd, bool bActive)
        {
            if(!bActive)
                return;

            Wnd = Windows.ActiveWnd;

            if (oConfigurator.MDWnd.hWnd == Wnd.hWnd)
            {
                var MDWnd = new System.Windows.Win32Window(new IntPtr(Wnd.hWnd), false);
                var state = MDWnd.State;
                MDWnd.State = System.Windows.Win32Window.WindowState.Maximized;
                return;
            }
            
            try
            {
                MainMenu = MainWindow.MainMenu.MainMenu;
                var TFSMenu = MainMenu.GetSubMenu("TFS");

                if (NewObjectCreating || Wnd.Caption.Contains("Внешний отчет(обработка)1")) // Команду для нового отчета пока не нашел
                {
                    var Doc = Wnd.Document;
                    if (Doc.ID != -1)
                    {
                        NewObjects.Add(Doc.TFSDirectory());
                        NewObjectCreating = false;
                    }
                    else
                    {
                        NewObjects.Add(Doc.TFSDirectory());
                    }
                    oConfigurator.Message("Создан " + Doc.Kind + " " + Doc.Name);
                }

                TFSMenu?.DisableItem("Взять объект в работу");
                TFSMenu?.DisableItem("Отменить взятие объекта в работу");
                TFSMenu?.DisableItem("Разобрать внешний отчет/обработку");            

                if (!Wnd.Caption.Contains(oConfigurator.BinDir))
                {
                    if (iCfgDocExtension.ReadOnlyOperations.ContainsKey(Wnd.Document.Type))
                    {
                        var Doc = Wnd.Document;
                        string ObjectPath = Path.Combine(ConfigurationServerFolder, Doc.TFSFileName());

                        bool IsPending = PendingObjects.Contains(ObjectPath);

                        if (IsExternalReport(Doc))
                        {
                            TFSMenu?.EnableItem("Разобрать внешний отчет/обработку");
                           
                            ObjectPath = GetServerObjectByDoc(Doc);
                            if (ObjectPath == String.Empty)
                            {
                                Doc.ReadOnly(false);
                                return;
                            }

                            IsPending = PendingObjects.ToArray().ToList().Any(x => x.ToString().Contains(ObjectPath));
                        }
                        
                        bool IsNew = NewObjects.Contains(Doc.TFSDirectory());
                         
                        if (IsNew)
                        {
                            Doc.ReadOnly(false);
                        }
                        else
                        {
                            if (IsPending)
                            {
                                TFSMenu?.EnableItem("Отменить взятие объекта в работу");
                                if (Doc.ReadOnly())
                                    Doc.ReadOnly(false);
                            }
                            else
                            {
                                TFSMenu?.EnableItem("Взять объект в работу");
                                Doc.ReadOnly(true);
                            }
                        }

                        Marshal.ReleaseComObject(Doc);
                        Doc = null;
                    }
                }
                else
                {
                    //var DocUnknownType = Wnd.Document.Name.Split(':')[0];
                    //if(DocUnknownType.Contains("CMDDoc")) //Это метаданные
                    //{
                    //    //получим путь к файлу "Структура.mdp" и проверим взят ли он в работу.
                    //    string ObjectPath = Path.Combine(ConfigurationServerFolder, Wnd.Document.TFSFileName());
                    //    bool MustBeReadOnly = !PendingObjects.Contains(ObjectPath);

                    //    if (MustBeReadOnly)
                    //    {
                    //        //var win = new System.Windows.Win32Window(CurrentWindow, false).Children[0];
                    //        //foreach (var WinControl in win.Children)
                    //        //{
                    //        //    switch(WinControl.ClassName.ToLower())
                    //        //    {
                    //        //        case "button":
                    //        //            if(WinControl.Text != "&Форма")
                    //        //                WinControl.Disable();
                    //        //            break;
                    //        //        default:
                    //        //            WinControl.Disable();
                    //        //            WinControl.Attach(WinControl.hWnd);
                    //        //            WinControl.WndProc += WinControl_WndProc;
                    //        //            break;
                    //        //    }

                    //        //}
                    //        //new System.Windows.Win32Window(new IntPtr(oConfigurator.MDWnd.hWnd), false).SendMessage(0x0006, 2, 0);
                    //        //MainWindow
                    //        //win.Parent.SendMessage(0x0006, 2, 0);

                    //    }

                    //}

                }
                TFSMenu = null;
                Marshal.ReleaseComObject(Wnd);
                Marshal.FinalReleaseComObject(Wnd);
                Wnd = null;

            }
            catch (Exception ex)
            {
                oConfigurator.Message(ex.Message, MsgLineMarkers.mRedErr);                  
            }
        }

        private int WinControl_WndProc(IntPtr hWnd, uint msg, IntPtr wParam, IntPtr lParam)
        {
            //Debug.Print(((WinApi.WindowsMessages)msg).ToString());
            if ((WinApi.WindowsMessages)msg == WinApi.WindowsMessages.WM_ENABLE)
            {
                wParam = new IntPtr(1);
                return 1;
            }

            if ((WinApi.WindowsMessages)msg == WinApi.WindowsMessages.WM_PAINT)
                return 1;

            return 1;
        }

        private string ExtractParentFromExternalReport(string ServerFolder)
        {
            string ParentLocalPath = ServerFolder.Substring(0, ServerFolder.LastIndexOf('/'));
            return ParentLocalPath;
        }

        private NativeMenu.SubMenu MenuConstructor(NativeMenu.SubMenu Parent, out string ItemAfter)
        {
            NativeMenu.SubMenu TFSMenu = new NativeMenu.SubMenu("TFS", NativeMenu.MenuFlags.MF_POPUP | NativeMenu.MenuFlags.MF_ENABLED, Parent.Owner);

            var menuItem_Config_GetLast = new NativeMenu.MenuItem("Получить последнюю версию конфигурации", Properties.Resources.GetLatestVersion, NativeMenu.MenuFlags.MF_STRING, 0, delegate (int MenuItemId)
                {
                    GetLastVersionOfConfiguration();
                    return false;
                });

            var menuItem_Config_Decompile = new NativeMenu.MenuItem("Разобрать текущую конфигурацию", NativeMenu.MenuFlags.MF_STRING, 0, delegate (int MenuItemId)
                 {
                     DeCompileCurrentConfiguration();
                     return false;
                 });

            var menuItem_Separator = new NativeMenu.MenuItem("-", NativeMenu.MenuFlags.MF_SEPARATOR);

            var menuItem_ExtReport_Open = new NativeMenu.MenuItem("Открыть внешний отчет/обработку", Properties.Resources.GetExternalReport, NativeMenu.MenuFlags.MF_STRING, 0, delegate (int MenuItemId)
                {
                    string name = SelectExternalReportFromTFS();
                    if (!string.IsNullOrEmpty(name))
                    {
                        GetLastVersionOfExternalReport(name);
                    }

                    return false;
                });

            var menuItem_ExtReport_Decompile = new NativeMenu.MenuItem("Разобрать внешний отчет/обработку", NativeMenu.MenuFlags.MF_STRING | NativeMenu.MenuFlags.MF_GRAYED, 0, delegate (int MenuItemId)
            {
                var Doc = Windows.ActiveWnd.Document;
                if (Doc != null)
                {
                    if (Doc.Type == DocTypes.docWorkBook)
                    {
                        if (IsExternalReport(Doc))
                        {
                            string ServerFolder = GetServerObjectByDoc(Doc);
                            bool IsNewObject = false;
                            if (ServerFolder == String.Empty)
                            {
                                LogAdd("Объект "+ Doc + " отсутствует в TFS. Нужно выбрать каталог для него");
                                IsNewObject = true;
                                ServerFolder = SelectFolderInTFS();
                            }
                            else
                            {
                                ServerFolder = ExtractParentFromExternalReport(ServerFolder);
                            }
                            if (ServerFolder != String.Empty)
                            {
                                string DecopiledPath = SendReportToTFS(Doc.path, ServerFolder);
                                if (Directory.Exists(DecopiledPath))
                                {
                                    int CountAdded = workspace.PendAdd(DecopiledPath, true);
                                    if (IsNewObject)
                                    {
                                        LogAdd(String.Format("В TFS добавлено {0} объектов", CountAdded), true);
                                    }                      
                                }
                            }
                        }
                    }
                }
         
                return false;
            });

            var menuItem_Checkout = new NativeMenu.MenuItem("Взять объект в работу", Properties.Resources.CheckOut, NativeMenu.MenuFlags.MF_STRING | NativeMenu.MenuFlags.MF_GRAYED, 0, delegate (int MenuItemId)
            {
                CheckOutCurrentWnd();
                return false;
            });

            var menuItem_Undocheckout = new NativeMenu.MenuItem("Отменить взятие объекта в работу", Properties.Resources.UndoCheckOut, NativeMenu.MenuFlags.MF_STRING | NativeMenu.MenuFlags.MF_GRAYED, 0, delegate (int MenuItemId)
            {
                UndoCheckOutCurrentWnd();
                return false;
            });

            var menuItem_About = new NativeMenu.MenuItem("О плагине", NativeMenu.MenuFlags.MF_STRING, 0, delegate (int MenuItemId)
            {
                DateTime LastVersion = CheckNewVersion(true);
                string status = LastVersion == DateTime.MinValue ? "последняя" : "Доступна версия от "+LastVersion.ToShortDateString();

                string text = String.Format(
@"Плагин для работы с TFS. 
Сборка от {0} ({1})

Copyright Siemens finance 2016",
new FileInfo(PathToThisDll).LastWriteTime,
status
);
                MessageBox.Show(MainWindow, text, "О плагине", MessageBoxButtons.OK ,MessageBoxIcon.Information);
                return false;
            });

            // Формируем порядок пунктов меню
            TFSMenu.Append(menuItem_Config_GetLast);
            TFSMenu.Append(menuItem_Config_Decompile);
            TFSMenu.Append(menuItem_Separator);
            TFSMenu.Append(menuItem_ExtReport_Open);
            TFSMenu.Append(menuItem_ExtReport_Decompile);
            TFSMenu.Append(menuItem_Separator);
            TFSMenu.Append(menuItem_Checkout);
            TFSMenu.Append(menuItem_Undocheckout);
            TFSMenu.Append(menuItem_Separator);
            TFSMenu.Append(menuItem_About);

            ItemAfter = "&Конфигурация";

            
            return TFSMenu;
        }



        public bool OnToggleReadOnly()
        {
            var ActiveDoc =Windows.ActiveWnd.Document;

            switch (ActiveDoc.Type)
            {
                case DocTypes.docText: //Текст
                    if (((TextDoc)ActiveDoc).ReadOnly)
                    {
                        if (TextDocUnSetReadOnly != null)
                            return TextDocUnSetReadOnly.Invoke((TextDoc)ActiveDoc);
                        else
                            return true;
                    }
                    else
                    {
                        if (TextDocSetReadOnly != null)
                            return TextDocSetReadOnly.Invoke((TextDoc)ActiveDoc);
                        else
                            return true;
                    }
                    
                case DocTypes.docDEdit: //Форма
                    return true;
                    
                case DocTypes.docTable: //Таблица
                    return true;
                    
                case DocTypes.docWorkBook: //Объект метаданных

                    WorkBook Doc = (WorkBook)ActiveDoc;
                    TextDoc doc = (TextDoc)Doc.Page[Doc.ActivePage];
                    if (doc.ReadOnly)
                    {
                        if (TextDocUnSetReadOnly != null)
                            return TextDocUnSetReadOnly.Invoke(doc);
                        else
                            return true;
                    }
                    else
                    {
                        if (TextDocSetReadOnly != null)
                            return TextDocSetReadOnly.Invoke(doc);
                        else
                            return true;
                    }
                    
                default:
                    return true;
            }
        }

        public void Done()
        {
            Dispose();
        }

        public dynamic GetPluginCaps(PluginCaps capNum)
        {
            switch (capNum)
            {
                case PluginCaps.capGetMenu:
                    {
                        return null;
                    }
                case PluginCaps.capIconNum:
                    {
                        return 0;
                    }
                case PluginCaps.capOpenIn:
                    {
                        return 1;
                    }
                case PluginCaps.capShowMacros:
                    {
                        return true;
                    }
            }
            return null;
        }

        public dynamic DoAction(PluginAction Action, object Param)
        {

            oConfigurator.Message(Param.ToString());
            return 1;
        }

        #endregion
    }
    
}
