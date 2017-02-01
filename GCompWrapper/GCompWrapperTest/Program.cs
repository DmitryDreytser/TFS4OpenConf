using GComp;
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace GCompConnectorTest
{

    public static class ConsoleHelper
    {
        public static void CreateConsole()
        {
            AllocConsole();
            IntPtr defaultStdout = new IntPtr(7);
            IntPtr currentStdout = GetStdHandle(StdOutputHandle);

            if (currentStdout != defaultStdout)
                SetStdHandle(StdOutputHandle, defaultStdout);

            Console.OutputEncoding = Encoding.Unicode;
            Console.InputEncoding = Encoding.Unicode;
        }

        // P/Invoke required:
        private const UInt32 StdOutputHandle = 0xFFFFFFF5;
        [DllImport("kernel32.dll")]
        private static extern IntPtr GetStdHandle(UInt32 nStdHandle);
        [DllImport("kernel32.dll")]
        private static extern void SetStdHandle(UInt32 nStdHandle, IntPtr handle);
        [DllImport("kernel32")]
        static extern bool AllocConsole();
    }

    class Program
    {

        public class ProgressForm : Form
        {
            private System.Windows.Forms.ProgressBar CurrentProgress;
            private System.ComponentModel.IContainer components = null;
            public int Progress { get; set; }
            private void InitializeComponent()
            {
                this.Width = 300;
                this.Height = 60;

                this.CurrentProgress = new ProgressBar();
                CurrentProgress.Dock = DockStyle.Fill;

                this.CurrentProgress.Minimum = 0;
                this.CurrentProgress.DataBindings.Add( new Binding("Value", this, "Progress", false, DataSourceUpdateMode.OnPropertyChanged));
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
            }

            protected override void WndProc(ref Message m)
            {
                if (m.Msg == WM_GCOMP_INFO)
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
                            break;

                        case GComp_Inf_Progress:
                            this.CurrentProgress.Value = (int)m.LParam;
                            this.Progress = (int)m.LParam;
                            break;

                        case GComp_Inf_Total:
                            this.CurrentProgress.Maximum = (int)m.LParam;
                            break;
                    }

                    if ((int)m.LParam > this.CurrentProgress.Maximum)
                    {
                        this.CurrentProgress.Value = this.CurrentProgress.Maximum;
                    }
                    this.Text = string.Format("Выполнено: {0:0} %", (float)CurrentProgress.Value / (float)CurrentProgress.Maximum * 100);
                }
                base.WndProc(ref m);
            }

            public ProgressForm()
            {
                InitializeComponent();
            }

        }

        public static GCompWrapper.CGCompParameters Params;
       
        private static void formProgressor()
        {
            Application.Run(new ProgressForm());
        }

        public const uint WM_USER = 0x0400;
        public const uint WM_GCOMP_INFO = WM_USER + 123;

        public const uint GComp_Inf_Start = 0;
        public const uint GComp_Inf_Stop = 1;
        public const uint GComp_Inf_Total = 2;     //в lParam передаётся общее количество объектов
        public const uint GComp_Inf_Progress = 3;  //в lParam передаётся количество обработанных объектов

        [STAThread]
        static void Main(string[] args)

        {
            Application.EnableVisualStyles();
            ConsoleHelper.CreateConsole();

            Console.WriteLine("Версия GComp: {0}", GCompWrapper.GetVersion());
            Params = GCompWrapper.SetDefaults();
            Params.DirectoryName = @"SRC"; 
            Params.CompoundFileName = @"1cv7.MD";
            Params.CompoundType = GCompWrapper.CompoundTypes.meta_data;
            Params.LogType = GCompWrapper.LogType.STDout;
            Params.SaveVersion = GCompWrapper.BOOL.False;
            Params.Messaging = GCompWrapper.Verbose.real_deeds;
            Params.Language = GCompWrapper.Languages.Rus;


            Thread th = new Thread(formProgressor);
            th.Start();
            Params.InfoMessage = WM_GCOMP_INFO;

            while (Params.hwndInfoReceiver == IntPtr.Zero) 
            {
                Thread.Sleep(10);
            }

            
            Console.WriteLine("Разборка конфигурации... (Если ничего не выводится, значит измененных файлов нет.)");
            Console.WriteLine("HWnd:{0}  msg:{1}", Params.hwndInfoReceiver, Params.InfoMessage);
            GCompWrapper.Decompile(ref Params);
            Console.WriteLine("Разборка конфигурации завершена.");
            Console.WriteLine("Нажмите что-нибудь");
            Console.ReadKey();

            GCompWrapper.SaveSettings(ref Params);
           

            Console.WriteLine("Сборка конфигурации...");
            Console.WriteLine("HWnd:{0}  msg:{1}", Params.hwndInfoReceiver, Params.InfoMessage);
            GCompWrapper.Compile(ref Params);
            Console.WriteLine("Сборка конфигурации завершена.");
            Console.WriteLine("Нажмите что-нибудь");
            Console.ReadKey();

            Params = GCompWrapper.SetDefaults();
            Params.DirectoryName = @"External Reports";
            Params.CompoundFileName = @"Тест.ert";
            Params.CompoundType = GCompWrapper.CompoundTypes.external_report;
            GCompWrapper.SaveSettings(ref Params);

            GCompWrapper.Decompile(ref Params);
            Console.WriteLine("Разборка внешнего отчета завершена.");
            Console.WriteLine("Нажмите что-нибудь");
            Console.ReadKey();

            GCompWrapper.Compile(ref Params);
            Console.WriteLine("Сборка внешнего отчета завершена.");
            Console.WriteLine("Нажмите что-нибудь");
            Console.ReadKey();
            Process.GetCurrentProcess().Kill();
        }

        private delegate IntPtr WndProc(IntPtr hWnd, uint msg, IntPtr wParam, IntPtr lParam);

    }
}
