using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using Microsoft.TeamFoundation.Client;
using Microsoft.TeamFoundation.VersionControl.Client;
using Microsoft.TeamFoundation.Server;
using System.Collections;
using System.Threading;

using WorkWithTFS;

namespace WorkWithTFS
{
    public partial class TreeForm : Form
    {
        public delegate void TreeView_UpdateFinished();
        public delegate void TreeView_UpdateStarted();

        public event TreeView_UpdateFinished onFinishUpdate;
        public event TreeView_UpdateStarted onStarthUpdate;

        public Ert SelectedItem;

        public Tools tools;
        public string SourceFolder;
        public bool OnlyFolders;
        public bool EditMode = false;
        public bool isUpdating = false;
        private System.Timers.Timer UpdateTimer;

        private DateTime LastUdateTime = new DateTime();

        /// <summary>
        /// Структура объекта внешней отчетности. Может быть как каталогом так и отчетом.
        /// </summary>
        public struct Ert
        {
            public string Name;
            public string FullPath;
            public string ServerPath;
            public bool IsFolder;
            public string ParentFullPath;
            public bool IsAdded;
        }

        /// <summary>
        /// Основной список объектов ВО
        /// </summary>
        public List<Ert> ErtList = new List<Ert>();

        public TreeForm(Tools tools)
        {
            InitializeComponent();
            this.tools = tools;
            this.SourceFolder = tools.ExternalReportsServerFolder;
            LastUdateTime = DateTime.MinValue; // Потом добавить в настройки реестра

            onFinishUpdate += ClearFilter;

            UpdateTimer = new System.Timers.Timer();
            UpdateTimer.Elapsed += UpdateTimer_Elapsed;
            UpdateTimer.Interval = 3600000; //Раз в час
            UpdateTimer.Start();

            UpdateTree(false);
        }

        private void UpdateTimer_Elapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            UpdateTree(false);
        }

        /// <summary>
        /// Получает данные о ВО из TFS и формирует список объектов оттуда.
        /// </summary>
        public void FillErtList()
        {
            ErtList = new List<Ert>();

            ItemSet itemset = tools.versionControl.GetItems(String.Format(@"{0}*", SourceFolder), RecursionType.Full);

            // Получаем все папки кроме PictureGallery
            List<Item> erts = itemset.Items.Where(item => 
                (item.ItemType == ItemType.Folder)
                && (!item.ServerItem.ToLower().EndsWith(".ert/picturegallery"))
                ).OrderBy(x=>x.ServerItem).ToList();

            foreach (Item item in erts)
            {
                string FullPath = item.ServerItem.Replace(SourceFolder, "");
                string[] parts = FullPath.Split('/');

                Ert NewErt = new Ert();
                NewErt.ServerPath = item.ServerItem;
                NewErt.FullPath = FullPath;
                NewErt.Name = parts[parts.Length - 1];
                NewErt.IsFolder = FullPath.ToLower().EndsWith(".ert") ? false : true;
                NewErt.IsAdded = false;
                NewErt.ParentFullPath = FullPath.Remove(FullPath.LastIndexOf(NewErt.Name)).Trim('/');

                ErtList.Add(NewErt);
            }
        }

        /// <summary>
        /// Формирует дерево на основании списка объектов внешней отчетности
        /// </summary>
        /// <param name="erts">Список объектов внешней отчетности</param>
        public void CreateErtTree(List<Ert> erts)
        {
            this.tree.Nodes.Clear();
            this.tree.BeginUpdate();
            try
            {  
                List<Ert> SortedErts = erts.OrderBy(x => !x.IsFolder).ThenBy(x => x.FullPath).ToList();
                
                foreach (Ert ert in SortedErts)
                {
                    int Ico = GetIco(ert);

                    TreeNode TN = new TreeNode();
                    TN.Name = ert.FullPath;
                    TN.Text = ert.Name;

                    TN.ToolTipText = String.Format(@"{0}",ert.ServerPath);
                    TN.ImageIndex = Ico;
                    TN.SelectedImageIndex = Ico;
                    TN.Tag = ert;
      
                    if (ert.ParentFullPath == String.Empty || txbFilter.Text != String.Empty)
                    {
                        this.tree.Nodes.Add(TN);
                    }
                    else
                    {
                        TreeNode ParentNode = this.tree.Nodes.Find(ert.ParentFullPath, true)[0];
                        ParentNode.Nodes.Add(TN);
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("CreateErtTree " + ex.Message);
            }
            this.tree.EndUpdate();
        }

        /// <summary>
        /// Фильтрует основной список объектов ВО
        /// </summary>
        /// <returns>Фильтрованный список объектов ВО</returns>
        public List<Ert> GetFiltredErtList()
        {
            List<Ert> res = new List<Ert>();

            foreach (Ert ert in ErtList)
            {
                bool MustBeAdded = false;

                if ((OnlyFolders && ert.IsFolder) || (!OnlyFolders))
                {
                    if (txbFilter.Text != String.Empty)
                    {
                        if (!ert.IsFolder && ert.Name.ToLower().Contains(txbFilter.Text.Trim().ToLower()))
                        {
                            MustBeAdded = true;
                        }
                    }
                    else
                    {
                        MustBeAdded = true;
                    }
                }

                if (MustBeAdded)
                {
                    res.Add(ert);
                }  
            }

            return res;
        }

        /// <summary>
        /// Возвращает индекс иконки для объекта ВО
        /// </summary>
        /// <param name="ert">Объект ВО</param>
        /// <returns>Индекс иконки</returns>
        private int GetIco(Ert ert)
        {
            int res = 0;
            if (ert.IsFolder)
            {
                res = 0;
            }
            else
            {
                res = 2;
            }
            return res;
        }

        /// <summary>
        /// Получает данные о внешней отчетности, на основании которых будет строиться дерево.
        /// Сначала получаются изменения в TFS, которые были после последнего обновления. Если их нет, то обновляться не надо.
        /// </summary>
        /// <param name="Forced">Принудительное обновление</param>
        public void UpdateTree(bool Forced)
        {
            onStarthUpdate?.Invoke();
            bool NeedToUpdate = true;
            if (!Forced) NeedToUpdate = NeedToUpdateTree();  
            if (NeedToUpdate)
            {
                FillErtList();
                LastUdateTime = DateTime.Now;
                RefreshTree();
            }
            onFinishUpdate?.Invoke();
        }

        /// <summary>
        /// Ищет во внешней отчетности изменения после последнего обновления
        /// </summary>
        /// <returns>Необходимость обновления</returns>
        private bool NeedToUpdateTree()
        {
            // Потом добавить проверки только на изменения, связанные со структурой
            bool ExistsChanges = ((IEnumerable<Changeset>)tools.versionControl.QueryHistory(
                                    SourceFolder,
                                    VersionSpec.Latest,
                                    0,
                                    RecursionType.Full,
                                    null,
                                    new ChangesetVersionSpec(1),
                                    VersionSpec.Latest,
                                    int.MaxValue,
                                    false,
                                    false
                                    )).Any(x => x.CreationDate >= LastUdateTime);

            return ExistsChanges;
        }

        /// <summary>
        /// Обновляет структуру дерева с ВО. Исходный набор данных не меняется. Происходит пересоздание дерева на основании данных фильтра
        /// </summary>
        private void RefreshTree()
        {
            string CurrentPath = "";
            if (tree.SelectedNode != null)
            {
                CurrentPath = ((Ert)tree.SelectedNode.Tag).FullPath;
            }
            List<Ert> FiltredList = GetFiltredErtList();
            CreateErtTree(FiltredList);

            if (CurrentPath != "")
            {
                TreeNode[] TNS = tree.Nodes.Find(CurrentPath, true);
                if (TNS.Length == 1)
                {
                    tree.SelectedNode = TNS[0];
                    tree.SelectedNode.Expand();
                }
            }
            //treeCache = new TreeView();
            //Thread ReadingThread = new Thread(UpdateTree);
            //ReadingThread.Start();
        }

        private void TreeForm_Load(object sender, EventArgs e)
        {
            if (tools == null)
            {
                Close();
            }
            else if (!tools.IsInit)
            {
                Close();
            }

            if (EditMode)
            {
                this.Text = "Выберите каталог";
            }
            else
            {
                this.Text = "Выберите внешний отчет";
            }
            btnAddFolder.Visible = EditMode;
            toolStripButton1.Visible = EditMode;
            ClearFilter();
        }

        /// <summary>
        /// Окончательный выбор узла
        /// </summary>
        private void SelectNode()
        {
            TreeNode TN = tree.SelectedNode;
            if (TN != null)
            {
                bool CanBeSelected = false;
                Ert ert = (Ert)TN.Tag;
                if ((OnlyFolders && ert.IsFolder)
                    || (!OnlyFolders && !ert.IsFolder))
                {
                    CanBeSelected = true;
                }

                if (CanBeSelected)
                {
                    SelectedItem = ert;
                    this.DialogResult = DialogResult.OK;
                    
                    Close();
                } 
            }
        }

        private void btnSelect_Click(object sender, EventArgs e)
        {
            SelectNode();
        }

        private void tree_DoubleClick(object sender, EventArgs e)
        {
            if (!OnlyFolders)
            {
                SelectNode();
            }
        }

        /// <summary>
        /// Добавляет новый каталог на основании выбранного узла
        /// </summary>
        private void NewCatalog()
        {
            string NewName = "Новый каталог";
            int count = ErtList.Count(x => x.Name.Contains(NewName));
            if (count >= 1)
            {
                NewName += " " + (count + 1).ToString();
            }

            Ert NewErt = new Ert();
            NewErt.Name = NewName;       
            NewErt.IsFolder = true;
            NewErt.IsAdded = true;

            TreeNode TN = tree.SelectedNode;
            if (TN != null)
            {
                Ert ParentErt = (Ert)TN.Tag;
                NewErt.ServerPath = ParentErt.ServerPath + "/" +NewName;
                NewErt.FullPath = ParentErt.FullPath + "/" + NewName;
                NewErt.ParentFullPath = ParentErt.FullPath;
            }
            else
            {
                NewErt.FullPath = NewName;
                NewErt.ParentFullPath = "";
                NewErt.ServerPath = SourceFolder + NewName;
            }
            ErtList.Add(NewErt);
        }

        private void btnRefresh_Click(object sender, EventArgs e)
        {
            UpdateTree(true);
        }

        private void btnAddFolder_Click(object sender, EventArgs e)
        {
            NewCatalog();
            RefreshTree();
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void tsbExpandAll_Click(object sender, EventArgs e)
        {
            tree.ExpandAll();
            if (tree.SelectedNode != null) tree.SelectedNode.EnsureVisible();
        }

        private void tsbCollapsAll_Click(object sender, EventArgs e)
        {
            tree.CollapseAll();
        }

        private void txbFilter_TextChanged(object sender, EventArgs e)
        {
            if (txbFilter.Text != String.Empty)
            {
                RefreshTree();
                tree.ExpandAll();
            }
            else
            {
                ClearFilter();
            }
        }

        /// <summary>
        /// Очищение фильтра
        /// </summary>
        private void ClearFilter()
        {
            txbFilter.Text = "";
            RefreshTree();
        }

        private void btnClearFilter_Click(object sender, EventArgs e)
        {
            ClearFilter();
        }

        private void tree_AfterLabelEdit(object sender, NodeLabelEditEventArgs e)
        {
            if (e.Label != null)
            {
                if (e.Label.Length > 0)
                {
                    if (e.Label.IndexOfAny(new char[] { '@', '.', ',', '!' }) == -1)
                    {
                        e.Node.EndEdit(false);
                        Ert ert = (Ert)e.Node.Tag;

                        int index = ErtList.FindLastIndex(x => x.ServerPath == ert.ServerPath);
                        Ert NewErt = ErtList[index];
                        NewErt.Name = e.Label;
                        ErtList[index] = NewErt;
                        tools.LogAdd(ErtList[index].Name, true);

                        List<Ert> ErtForEdit = ErtList.FindAll(x => x.ServerPath.Contains(ert.ServerPath));
                        string ertNewServerPath = ert.ServerPath.Remove(ert.ServerPath.LastIndexOf('/')) + '/' + e.Label;
                        for (int i = 0; i < ErtForEdit.Count; i++)
                        {
                            int ind = ErtList.FindLastIndex(x => x.ServerPath == ErtForEdit[i].ServerPath);
                            Ert EditedErt = ErtList[ind];

                            EditedErt.ServerPath = EditedErt.ServerPath.Replace(ert.ServerPath, ertNewServerPath);

                            ErtList[ind] = EditedErt;
                        }

                        ErtForEdit = ErtList.FindAll(x => x.FullPath.IndexOf(ert.FullPath) == 0);

                        string ertNewFullPath = ert.FullPath.Remove(ert.FullPath.LastIndexOf('/')) + '/' + e.Label;
                        for (int i = 0; i < ErtForEdit.Count; i++)
                        {
                            int ind = ErtList.FindLastIndex(x => x.ServerPath == ErtForEdit[i].ServerPath);
                            Ert EditedErt = ErtList[ind];

                            EditedErt.FullPath = ertNewFullPath + EditedErt.FullPath.Remove(0, ert.FullPath.Length);

                            ErtList[ind] = EditedErt;
                        }

                        ErtForEdit = ErtList.FindAll(x => x.ParentFullPath.IndexOf(ert.FullPath) == 0);
                        string ertNewParentFullPath = ert.FullPath.Remove(ert.FullPath.LastIndexOf('/')) + '/' + e.Label;
                        for (int i = 0; i < ErtForEdit.Count; i++)
                        {
                            int ind = ErtList.FindLastIndex(x => x.ServerPath == ErtForEdit[i].ServerPath);
                            Ert EditedErt = ErtList[ind];

                            EditedErt.ParentFullPath = ertNewParentFullPath + EditedErt.ParentFullPath.Remove(0, ert.FullPath.Length);
                            ErtList[ind] = EditedErt;
                        }


                        e.CancelEdit = true;
                        RefreshTree();
                        TreeNode[] TNS = tree.Nodes.Find(ertNewFullPath, true);
                        if (TNS.Length == 1)
                        {
                            tree.SelectedNode = TNS[0];
                            tree.SelectedNode.Expand();
                        }
                    }
                    else
                    {
                        e.CancelEdit = true;
                        e.Node.BeginEdit();
                    }
                }
                else
                {
                    e.CancelEdit = true;
                    e.Node.BeginEdit();
                }
            }
        }

        private void tree_BeforeLabelEdit(object sender, NodeLabelEditEventArgs e)
        {
            if (!((Ert)e.Node.Tag).IsAdded) e.CancelEdit = true;
        }

        private void TreeForm_Shown(object sender, EventArgs e)
        {
            UpdateTree(false);
            pnlFilter.Visible = !OnlyFolders;        
        }

        private void tree_MouseUp(object sender, MouseEventArgs e)
        {
            Point p = new Point(e.X, e.Y);
            TreeNode node = tree.GetNodeAt(p);
            if (node == null)
            {
                tree.SelectedNode = null;
            }     
        }
    }
}
