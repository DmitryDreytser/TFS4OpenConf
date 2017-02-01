using GComp;
using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;

namespace WorkWithTFS
{

    [ProgId("WorkWithTFS.GCompTools")]
    [ComVisible(true)]
    [ComSourceInterfaces(typeof(WorkWithTFS.IGCompTools))]
    public class GCompTools : IGCompTools
    {
        public delegate void GCompTools_ProgressChanged(int CurrentProgress);
        public delegate void GCompTools_LogMessage(string pMessage);
        public delegate void GCompTools_Finish();
        public delegate void GCompTools_Start();

        public event GCompTools_ProgressChanged onProgressChange;
        public event GCompTools_Finish onFinishDecompile;
        public event GCompTools_Finish onFinishCompile;
        public event GCompTools_Start onStartTask;
        public event GCompTools_LogMessage onLog;
        private IWin32Window MainWindow;

        public class ProgressForm : Form
        {

            private readonly GCompTools MainWindow;
            private System.Windows.Forms.ProgressBar CurrentProgress;
            private System.ComponentModel.IContainer components = null;
            public int Progress { get; set; }
            private void InitializeComponent()
            {
                this.Width = 300;
                this.Height = 60;
                this.CurrentProgress = new ProgressBar
                {
                    Dock = DockStyle.Fill
                };

                this.CurrentProgress.Minimum = 0;
                this.CurrentProgress.DataBindings.Add(new Binding("Value", this, "Progress", false, DataSourceUpdateMode.OnPropertyChanged));
                this.components = new System.ComponentModel.Container();
                this.Controls.Add(this.CurrentProgress);
                this.Text = "Выполнено";

                this.MaximizeBox = false;
                this.MinimizeBox = false;
                this.FormBorderStyle = FormBorderStyle.FixedDialog;
                this.StartPosition = FormStartPosition.CenterScreen;

                this.ResumeLayout(false);
                this.PerformLayout();
                this.FormBorderStyle = FormBorderStyle.FixedSingle;
                this.ControlBox = false;
                this.TopMost = true;
                Params.hwndInfoReceiver = Handle;
                Params.InfoMessage = WM_GCOMP_INFO;
                Params.hwndLog = Handle;
                Params.LogType = GCompWrapper.LogType.ListBox;
            }

            protected override void WndProc(ref Message m)
            {
                switch (m.Msg)
                {
                    case (int)WM_GCOMP_INFO:
                        {
                            switch ((uint)m.WParam)
                            {
                                case GComp_Inf_Start:
                                    this.CurrentProgress.Value = 0;
                                    this.Progress = 0;
                                    break;

                                case GComp_Inf_Stop:
                                    this.CurrentProgress.Value = CurrentProgress.Maximum;
                                    this.Progress = CurrentProgress.Maximum;
                                    this.Close();
                                    break;

                                case GComp_Inf_Progress:
                                    int NewValue = (int)m.LParam;
                                    if (NewValue >= this.CurrentProgress.Maximum)
                                    {
                                        NewValue = this.CurrentProgress.Maximum;
                                    }
                                    this.CurrentProgress.Value = NewValue;
                                    this.Progress = (int)m.LParam;

                                    if ((int)m.LParam < this.CurrentProgress.Maximum)
                                    {
                                        this.Text = string.Format("Выполнено: {0:0} %", (float)CurrentProgress.Value / (float)CurrentProgress.Maximum * 100);
                                    }

                                    MainWindow.onProgressChange?.BeginInvoke((int)((float)CurrentProgress.Value / (float)CurrentProgress.Maximum * 100), null, this);

                                    break;

                                case GComp_Inf_Total:
                                    this.CurrentProgress.Maximum = (int)m.LParam;
                                    break;
                            }
                            break;
                        }
                    case (int)LB_ADDSTRING:
                        {
                            string txt = Marshal.PtrToStringUni(m.LParam);
                            if(txt.Contains("ERR"))
                                {
                                    this.Close();
                                }
                            if (!string.IsNullOrEmpty(txt))
                                this.MainWindow.onLog?.BeginInvoke(txt, null, null);
                            break;
                        }
                }
                base.WndProc(ref m);
            }

            public ProgressForm(GCompTools Owner)
            {
                this.MainWindow = Owner;
                InitializeComponent();
            }



        }

        public static GCompWrapper.CGCompParameters Params;
        ProgressForm frm;

        private void formProgressor()
        {
            //if (frm.Handle == IntPtr.Zero)
            //    frm = new ProgressForm(this);

            frm.BeginInvoke(new MethodInvoker(delegate
          {
              if (this.MainWindow != null)
                  frm.ShowDialog(this.MainWindow);
              else
                  frm.ShowDialog();
          }
            ));
        }

        public const uint LB_ADDSTRING = 0x0180;
        public const uint WM_USER = 0x0400;
        public const uint WM_GCOMP_INFO = WM_USER + 123;

        public const uint GComp_Inf_Start = 0;
        public const uint GComp_Inf_Stop = 1;
        public const uint GComp_Inf_Total = 2;     //в lParam передаётся общее количество объектов
        public const uint GComp_Inf_Progress = 3;  //в lParam передаётся количество обработанных объектов

        public int IsInit = 0;
        public bool TaskResult;

        /// <summary>
        /// Оригинальный конструктор
        /// </summary>
        public GCompTools()
        {
            Params = GCompWrapper.SetDefaults();
            frm = new ProgressForm(this);
            loadDefaultParams();
        }

        private void loadDefaultParams()
        {
            Params.Messaging = GCompWrapper.Verbose.real_deeds;
            Params.NoEmptyFolders = GCompWrapper.BOOL.True;
            // Params
            //Params.NotParseForms = GCompWrapper.BOOL.True; // Так формы не едут, но нужно поэкспериментировать
        }



        /// <summary>
        /// Инициализация класса
        /// </summary>
        /// <returns></returns>
        public int Init(IWin32Window MainWindow = null)
        {
            Init();

            this.MainWindow = MainWindow;
            return IsInit;
        }

        /// <summary>
        /// Инициализация класса
        /// </summary>
        /// <returns></returns>
        public int Init()
        {
            this.MainWindow = null;
            IsInit = 1;
            return IsInit;
        }

        /// <summary>
        /// Собирает отчет/обработку из исходных файлов
        /// </summary>
        /// <param name="ExternalReportPath">Каталог с исходными файлами очета/обработки</param>
        /// <param name="DestReport">Полное имя файла, в который должен быть собран отчет/обработка</param>
        public void CompileExternalReport(string ExternalReportPath, string DestReport)
        {
            if (IsInit == 1)
            {
                if (Directory.Exists(ExternalReportPath))
                {
                    loadDefaultParams();
                    Params.DirectoryName = @ExternalReportPath;
                    Params.CompoundFileName = @DestReport;
                    Params.CompoundType = GCompWrapper.CompoundTypes.external_report;
                    frm = new ProgressForm(this);
                    Thread th = new Thread(formProgressor);
                    th.Start();

                    while (Params.hwndInfoReceiver == IntPtr.Zero)
                    {
                        Thread.Sleep(10);
                    }

                    Thread thWorker = new Thread(CompileThread);
                    thWorker.Start();
                }
            }
        }

        /// <summary>
        /// Разбирает отчет/обработку на исходные файлы. Новый каталог не создается.
        /// </summary>
        /// <param name="ExternalReportFile">Отчет/обработка, который(ую) нужно разобрать</param>
        /// <param name="DestReportPath">Каталог, в который должен быть разобран отчет/обработка</param>
        public void DecompileExternalReport(string ExternalReportFile, string DestReportPath)
        {
            if (IsInit == 1 && File.Exists(ExternalReportFile))
            {
                loadDefaultParams();
                Params.DirectoryName = @DestReportPath;
                Params.CompoundFileName = @ExternalReportFile;
                Params.CompoundType = GCompWrapper.CompoundTypes.external_report;
                DecompileThread();
                // Пришлось отказаться от многопоточности, т.к. отчет не успеваеи разобраться перед добавление в TFS. + он и так разбирается быстро.
            }
        }

        private void DecompileThread()
        {
            onStartTask?.BeginInvoke(null, null);
            TaskResult = GCompWrapper.Decompile(ref Params);
            if (frm.Visible)
                frm.BeginInvoke(new MethodInvoker(delegate { frm.Hide(); }));
            onFinishDecompile?.BeginInvoke(null, null);
        }
               

        private void CompileThread()
        {
            onStartTask?.BeginInvoke(null, null);
            TaskResult = GCompWrapper.Compile(ref Params);
            if(frm.Visible)
                frm.BeginInvoke(new MethodInvoker(delegate {frm.Hide();   }));
            onFinishCompile?.BeginInvoke(null, null);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="ConfigurationFilePath"></param>
        /// <param name="DestinationPath"></param>
        public void DecompileConfiguration(string ConfigurationFilePath, string DestinationPath)
        {
            if (IsInit == 1 && File.Exists(ConfigurationFilePath))
            {
                loadDefaultParams();
                Params.CompoundFileName = ConfigurationFilePath;
                Params.DirectoryName = DestinationPath;
                Params.CompoundType = GCompWrapper.CompoundTypes.meta_data;
                frm = new ProgressForm(this);
                Thread th = new Thread(formProgressor);
                th.Start();
                while (Params.hwndInfoReceiver == IntPtr.Zero)
                {
                    Thread.Sleep(10);
                }

                Thread thWorker = new Thread(DecompileThread);
                thWorker.Start();
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="ConfigurationFilePath"></param>
        /// <param name="DestinationPath"></param>
        public void CompileConfiguration(string ConfigurationFilePath, string SourcePath)
        {
            if (IsInit == 1 && Directory.Exists(SourcePath))
            {
                loadDefaultParams();
                Params.CompoundFileName = ConfigurationFilePath;
                Params.DirectoryName = SourcePath;
                Params.CompoundType = GCompWrapper.CompoundTypes.meta_data;
                frm = new ProgressForm(this);
                Thread th = new Thread(formProgressor);
                th.Start();
                while (Params.hwndInfoReceiver == IntPtr.Zero)
                {
                    Thread.Sleep(10);
                }
                Thread thWorker = new Thread(CompileThread);
                thWorker.Start();

            }

        }

    }
}
