//using Microsoft.VisualStudio.OLE.Interop;
using Microsoft.Win32;
using OpenConf;
using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.ExceptionServices;
using System.Runtime.InteropServices;
using System.Security;
using System.Text;
using System.Threading;
using System.Windows;
using System.Windows.Forms;

namespace WorkWithTFS
{
    #region Классы для работы с системными диалогами
    public static class WinApi
    {

        internal const int RT_DIALOG = 5;
        internal const int S_OK = 0x00000000;
        internal const int S_FALSE =     0x00000001;
        internal const int OLEOBJ_S_CANNOT_DOVERB_NOW = 0x00040181;

        public delegate int DialogDelegate(IntPtr hDialog, WindowsMessages uMsg, IntPtr wParam, IntPtr lParam);

        public enum WindowsMessages : uint
        {
            BM_SETCHECK = 0x00F1,  // set radio or checkbox button state
            BST_UNCHECKED = 0x0000,
            BST_CHECKED = 0x0001,
            BM_CLICK = 0x00F5,
            WM_ACTIVATE = 0x0006,
            WM_ACTIVATEAPP = 0x001C,
            WM_AFXFIRST = 0x0360,
            WM_AFXLAST = 0x037F,
            WM_APP = 0x8000,
            WM_ASKCBFORMATNAME = 0x030C,
            WM_CANCELJOURNAL = 0x004B,
            WM_CANCELMODE = 0x001F,
            WM_CAPTURECHANGED = 0x0215,
            WM_CHANGECBCHAIN = 0x030D,
            WM_CHANGEUISTATE = 0x0127,
            WM_CHAR = 0x0102,
            WM_CHARTOITEM = 0x002F,
            WM_CHILDACTIVATE = 0x0022,
            WM_CLEAR = 0x0303,
            WM_CLOSE = 0x0010,
            WM_COMMAND = 0x0111,
            WM_COMPACTING = 0x0041,
            WM_COMPAREITEM = 0x0039,
            WM_CONTEXTMENU = 0x007B,
            WM_COPY = 0x0301,
            WM_COPYDATA = 0x004A,
            WM_CREATE = 0x0001,
            WM_CTLCOLORBTN = 0x0135,
            WM_CTLCOLORDLG = 0x0136,
            WM_CTLCOLOREDIT = 0x0133,
            WM_CTLCOLORLISTBOX = 0x0134,
            WM_CTLCOLORMSGBOX = 0x0132,
            WM_CTLCOLORSCROLLBAR = 0x0137,
            WM_CTLCOLORSTATIC = 0x0138,
            WM_CUT = 0x0300,
            WM_DEADCHAR = 0x0103,
            WM_DELETEITEM = 0x002D,
            WM_DESTROY = 0x0002,
            WM_DESTROYCLIPBOARD = 0x0307,
            WM_DEVICECHANGE = 0x0219,
            WM_DEVMODECHANGE = 0x001B,
            WM_DISPLAYCHANGE = 0x007E,
            WM_DRAWCLIPBOARD = 0x0308,
            WM_DRAWITEM = 0x002B,
            WM_DROPFILES = 0x0233,
            WM_ENABLE = 0x000A,
            WM_ENDSESSION = 0x0016,
            WM_ENTERIDLE = 0x0121,
            WM_ENTERMENULOOP = 0x0211,
            WM_ENTERSIZEMOVE = 0x0231,
            WM_ERASEBKGND = 0x0014,
            WM_EXITMENULOOP = 0x0212,
            WM_EXITSIZEMOVE = 0x0232,
            WM_FONTCHANGE = 0x001D,
            WM_GETDLGCODE = 0x0087,
            WM_GETFONT = 0x0031,
            WM_GETHOTKEY = 0x0033,
            WM_GETICON = 0x007F,
            WM_GETMINMAXINFO = 0x0024,
            WM_GETOBJECT = 0x003D,
            WM_GETTEXT = 0x000D,
            WM_GETTEXTLENGTH = 0x000E,
            WM_HANDHELDFIRST = 0x0358,
            WM_HANDHELDLAST = 0x035F,
            WM_HELP = 0x0053,
            WM_HOTKEY = 0x0312,
            WM_HSCROLL = 0x0114,
            WM_HSCROLLCLIPBOARD = 0x030E,
            WM_ICONERASEBKGND = 0x0027,
            WM_IME_CHAR = 0x0286,
            WM_IME_COMPOSITION = 0x010F,
            WM_IME_COMPOSITIONFULL = 0x0284,
            WM_IME_CONTROL = 0x0283,
            WM_IME_ENDCOMPOSITION = 0x010E,
            WM_IME_KEYDOWN = 0x0290,
            WM_IME_KEYLAST = 0x010F,
            WM_IME_KEYUP = 0x0291,
            WM_IME_NOTIFY = 0x0282,
            WM_IME_REQUEST = 0x0288,
            WM_IME_SELECT = 0x0285,
            WM_IME_SETCONTEXT = 0x0281,
            WM_IME_STARTCOMPOSITION = 0x010D,
            WM_INITDIALOG = 0x0110,
            WM_INITMENU = 0x0116,
            WM_INITMENUPOPUP = 0x0117,
            WM_INPUTLANGCHANGE = 0x0051,
            WM_INPUTLANGCHANGEREQUEST = 0x0050,
            WM_KEYDOWN = 0x0100,
            WM_KEYFIRST = 0x0100,
            WM_KEYLAST = 0x0108,
            WM_KEYUP = 0x0101,
            WM_KILLFOCUS = 0x0008,
            WM_LBUTTONDBLCLK = 0x0203,
            WM_LBUTTONDOWN = 0x0201,
            WM_LBUTTONUP = 0x0202,
            WM_MBUTTONDBLCLK = 0x0209,
            WM_MBUTTONDOWN = 0x0207,
            WM_MBUTTONUP = 0x0208,
            WM_MDIACTIVATE = 0x0222,
            WM_MDICASCADE = 0x0227,
            WM_MDICREATE = 0x0220,
            WM_MDIDESTROY = 0x0221,
            WM_MDIGETACTIVE = 0x0229,
            WM_MDIICONARRANGE = 0x0228,
            WM_MDIMAXIMIZE = 0x0225,
            WM_MDINEXT = 0x0224,
            WM_MDIREFRESHMENU = 0x0234,
            WM_MDIRESTORE = 0x0223,
            WM_MDISETMENU = 0x0230,
            WM_MDITILE = 0x0226,
            WM_MEASUREITEM = 0x002C,
            WM_MENUCHAR = 0x0120,
            WM_MENUCOMMAND = 0x0126,
            WM_MENUDRAG = 0x0123,
            WM_MENUGETOBJECT = 0x0124,
            WM_MENURBUTTONUP = 0x0122,
            WM_MENUSELECT = 0x011F,
            WM_MOUSEACTIVATE = 0x0021,
            WM_MOUSEFIRST = 0x0200,
            WM_MOUSEHOVER = 0x02A1,
            WM_MOUSELAST = 0x020D,
            WM_MOUSELEAVE = 0x02A3,
            WM_MOUSEMOVE = 0x0200,
            WM_MOUSEWHEEL = 0x020A,
            WM_MOUSEHWHEEL = 0x020E,
            WM_MOVE = 0x0003,
            WM_MOVING = 0x0216,
            WM_NCACTIVATE = 0x0086,
            WM_NCCALCSIZE = 0x0083,
            WM_NCCREATE = 0x0081,
            WM_NCDESTROY = 0x0082,
            WM_NCHITTEST = 0x0084,
            WM_NCLBUTTONDBLCLK = 0x00A3,
            WM_NCLBUTTONDOWN = 0x00A1,
            WM_NCLBUTTONUP = 0x00A2,
            WM_NCMBUTTONDBLCLK = 0x00A9,
            WM_NCMBUTTONDOWN = 0x00A7,
            WM_NCMBUTTONUP = 0x00A8,
            WM_NCMOUSEHOVER = 0x02A0,
            WM_NCMOUSELEAVE = 0x02A2,
            WM_NCMOUSEMOVE = 0x00A0,
            WM_NCPAINT = 0x0085,
            WM_NCRBUTTONDBLCLK = 0x00A6,
            WM_NCRBUTTONDOWN = 0x00A4,
            WM_NCRBUTTONUP = 0x00A5,
            WM_NCXBUTTONDBLCLK = 0x00AD,
            WM_NCXBUTTONDOWN = 0x00AB,
            WM_NCXBUTTONUP = 0x00AC,
            WM_NCUAHDRAWCAPTION = 0x00AE,
            WM_NCUAHDRAWFRAME = 0x00AF,
            WM_NEXTDLGCTL = 0x0028,
            WM_NEXTMENU = 0x0213,
            WM_NOTIFY = 0x004E,
            WM_NOTIFYFORMAT = 0x0055,
            WM_NULL = 0x0000,
            WM_PAINT = 0x000F,
            WM_PAINTCLIPBOARD = 0x0309,
            WM_PAINTICON = 0x0026,
            WM_PALETTECHANGED = 0x0311,
            WM_PALETTEISCHANGING = 0x0310,
            WM_PARENTNOTIFY = 0x0210,
            WM_PASTE = 0x0302,
            WM_PENWINFIRST = 0x0380,
            WM_PENWINLAST = 0x038F,
            WM_POWER = 0x0048,
            WM_POWERBROADCAST = 0x0218,
            WM_PRINT = 0x0317,
            WM_PRINTCLIENT = 0x0318,
            WM_QUERYDRAGICON = 0x0037,
            WM_QUERYENDSESSION = 0x0011,
            WM_QUERYNEWPALETTE = 0x030F,
            WM_QUERYOPEN = 0x0013,
            WM_QUEUESYNC = 0x0023,
            WM_QUIT = 0x0012,
            WM_RBUTTONDBLCLK = 0x0206,
            WM_RBUTTONDOWN = 0x0204,
            WM_RBUTTONUP = 0x0205,
            WM_RENDERALLFORMATS = 0x0306,
            WM_RENDERFORMAT = 0x0305,
            WM_SETCURSOR = 0x0020,
            WM_SETFOCUS = 0x0007,
            WM_SETFONT = 0x0030,
            WM_SETHOTKEY = 0x0032,
            WM_SETICON = 0x0080,
            WM_SETREDRAW = 0x000B,
            WM_SETTEXT = 0x000C,
            WM_SETTINGCHANGE = 0x001A,
            WM_SHOWWINDOW = 0x0018,
            WM_SIZE = 0x0005,
            WM_SIZECLIPBOARD = 0x030B,
            WM_SIZING = 0x0214,
            WM_SPOOLERSTATUS = 0x002A,
            WM_STYLECHANGED = 0x007D,
            WM_STYLECHANGING = 0x007C,
            WM_SYNCPAINT = 0x0088,
            WM_SYSCHAR = 0x0106,
            WM_SYSCOLORCHANGE = 0x0015,
            WM_SYSCOMMAND = 0x0112,
            WM_SYSDEADCHAR = 0x0107,
            WM_SYSKEYDOWN = 0x0104,
            WM_SYSKEYUP = 0x0105,
            WM_TCARD = 0x0052,
            WM_TIMECHANGE = 0x001E,
            WM_TIMER = 0x0113,
            WM_UNDO = 0x0304,
            WM_UNINITMENUPOPUP = 0x0125,
            WM_USER = 0x0400,
            WM_USERCHANGED = 0x0054,
            WM_VKEYTOITEM = 0x002E,
            WM_VSCROLL = 0x0115,
            WM_VSCROLLCLIPBOARD = 0x030A,
            WM_WINDOWPOSCHANGED = 0x0047,
            WM_WINDOWPOSCHANGING = 0x0046,
            WM_WININICHANGE = 0x001A,
            WM_XBUTTONDBLCLK = 0x020D,
            WM_XBUTTONDOWN = 0x020B,
            WM_XBUTTONUP = 0x020C
        }


        [DllImport("user32.dll", SetLastError = true)]
        public static extern int GetDlgCtrlID(IntPtr hwndCtl);

        [DllImport("user32.dll", SetLastError = true)]
        public static extern uint GetDlgItemText(IntPtr hDlg, int nIDDlgItem, [Out] StringBuilder lpString, int nMaxCount);

        [DllImport("user32.dll")]
        public static extern bool SetDlgItemText(IntPtr hDlg, int nIDDlgItem,   string lpString);

        [DllImport("user32.dll")]
        public static extern IntPtr DialogBoxIndirectParam(IntPtr hInstance, IntPtr lpTemplate, IntPtr hWndParent, DialogDelegate lpDialogFunc, IntPtr dwInitParam);

        [DllImport("user32.dll")]
        public static extern IntPtr CreateDialogIndirectParam(IntPtr hInstance, IntPtr lpTemplate, IntPtr hWndParent, DialogDelegate lpDialogFunc, IntPtr lParamInit);

        [DllImport("user32.dll")]
        public static extern IntPtr CreateDialogParam(IntPtr hInstance, string lpTemplateName, IntPtr hwndParent, DialogDelegate lpDialogFunc, IntPtr lParamInit);

        [DllImport("kernel32.dll")]
        public static extern IntPtr FindResource(IntPtr hModule, IntPtr lpName, IntPtr lpType);

        [DllImport("kernel32.dll")]
        public static extern IntPtr FindResource(IntPtr hModule, int lpName, int lpType);

        [DllImport("kernel32.dll")]
        public static extern IntPtr FindResource(IntPtr hModule, int lpName, string lpType);

        [DllImport("kernel32.dll")]
        public static extern IntPtr FindResource(IntPtr hModule, string lpName, int lpType);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern IntPtr LoadResource(IntPtr hModule, IntPtr hResInfo);
        [DllImport("Kernel32.dll", EntryPoint = "FindResourceW", SetLastError = true, CharSet = CharSet.Unicode)]
        private static extern IntPtr FindResource(IntPtr hModule, string pName, string pType);

        [DllImport("Kernel32.dll", EntryPoint = "SizeofResource", SetLastError = true)]
        private static extern uint SizeofResource(IntPtr hModule, IntPtr hResource);


        [DllImport("Kernel32.dll", EntryPoint = "LockResource")]
        private static extern IntPtr LockResource(IntPtr hGlobal);

        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        public static extern IntPtr GetModuleHandle(string libname);

        [DllImport("user32.dll")]
        public static extern bool IsDialogMessage(IntPtr hDlg,  ref WindowsMessages lpMsg);

        public static IntPtr FindLoadnLock(IntPtr hExe, int fileName, int fileType = RT_DIALOG)
        {
            IntPtr hResource;  //handle to resource
            IntPtr pResource;  //pointer to resource in memory
            hResource = FindResource(hExe, fileName, fileType);
            if (hResource.ToInt32() == 0)
            {
                throw new Win32Exception(Marshal.GetLastWin32Error());
            }
            hResource = LoadResource(hExe, hResource);
            if (hResource.ToInt32() == 0)
            {
                throw new Win32Exception(Marshal.GetLastWin32Error());
            }

            pResource = LockResource(hResource);
            if (pResource.ToInt32() == 0)
            {
                throw new Win32Exception(Marshal.GetLastWin32Error());
            }
            return pResource;
        }

        public class NativeDialog : System.Windows.Win32Window, IWin32Window
        {
            private delegate int ControlDelegate(IntPtr hDialog, WindowsMessages uMsg, IntPtr wParam, IntPtr lParam);

            public delegate int DlgControlChaged(int ControlId, WindowsMessages uMsg, IntPtr wParam, IntPtr lParam);

            public event DlgControlChaged ControlChanged;

            private IntPtr pResource;
            private GCHandle hDlgProc;
            private ArrayList hControlGC = new ArrayList();

            public Dictionary<string , DlgItem> Controls = new Dictionary<string, DlgItem>();


            static int DlgProc(IntPtr Hwnd, WinApi.WindowsMessages uMsg, IntPtr wParam, IntPtr lParam)
            {
                switch (uMsg)
                {
                    case WinApi.WindowsMessages.WM_INITDIALOG:
                        return 1;
                    default:
                        return 0;
                }
            }

            public NativeDialog(int ResNumber, System.Windows.Win32Window parent) : base(IntPtr.Zero)
            {

                WinApi.DialogDelegate eventHandler = new WinApi.DialogDelegate(DlgProc).Invoke;
                if (hDlgProc.IsAllocated)
                    hDlgProc.Free();
                hDlgProc = GCHandle.Alloc(eventHandler);
                pResource = FindLoadnLock(GetModuleHandle("WorkWithTFS"), ResNumber, RT_DIALOG);
                base.hWnd = WinApi.CreateDialogIndirectParam(IntPtr.Zero, pResource, parent, (WinApi.DialogDelegate)hDlgProc.Target, IntPtr.Zero); //

                foreach (var dlgControl in Children.Where(t=> t.ClassName != "Static") )
                {
                    var Item = new DlgItem(dlgControl.hWnd);
                    Controls[string.Format("{0}.{1}", Item.ClassName, Item.ID)] = Item;
                }
            }

            private void DlgControl_KeyUp(object sender, KeyEventArgs e)
            {
                var thisControl = (System.Windows.Win32Window)sender;
                int ControlId = GetDlgCtrlID(thisControl.hWnd);
                //Debug.Print("Control {0} ({1}):{2}", thisControl.ClassName, ControlId, thisControl.Text);
            }

            private void DlgControl_Click(object sender, MouseEventArgs e)
            {
                var thisControl = (System.Windows.Win32Window)sender; 
                int ControlId = GetDlgCtrlID(thisControl.hWnd);
                //Debug.Print("Control {0} ({1}):{2} wParam{3}, lParam{4}", thisControl.ClassName, ControlId, thisControl.Text, e.X, e.Y);
            }

            private void DlgControl_WndProc(IntPtr hWnd, uint msg, IntPtr wParam, IntPtr lParam)
            {
                var thisControl = Controls.First(t=>t.Value.hWnd == hWnd).Value;

                WindowsMessages message = (WindowsMessages)msg;
                switch(message)
                {
                    case WindowsMessages.WM_KILLFOCUS:
                        //Debug.Print("Control {0} ({1}):{2} wParam{3}, lParam{4}", thisControl.ClassName, thisControl.ID, message, wParam, lParam);
                        break;
                    case WindowsMessages.WM_SETFOCUS:
                        //Debug.Print("Control {0} ({1}):{2} wParam{3}, lParam{4}", thisControl.ClassName, thisControl.ID, message, wParam, lParam);
                        break;
                    case WindowsMessages.WM_KEYUP:
                        ControlChanged?.Invoke(thisControl.ID, message, wParam, lParam);
                        break;
                    case WindowsMessages.WM_LBUTTONDOWN:
                    case WindowsMessages.WM_RBUTTONDOWN:
                    case WindowsMessages.WM_MBUTTONDOWN:
                        ControlChanged?.Invoke(thisControl.ID, message, wParam, lParam);
                        break;
                }
            }

            ~NativeDialog()
            {
                foreach(GCHandle proc in hControlGC)
                {
                    if (proc.IsAllocated)
                        proc.Free();
                }

                if (hDlgProc.IsAllocated)
                    hDlgProc.Free();
            }
        }
    }

    public class DlgItem
    {
        const string Button = "Button";
        const string ComboBox = "ComboBox"; //The class for a combo box.
        const string Edit = "Edit";     //The class for an edit control.
        const string ListBox = "ListBox";   //The class for a list box.
        const string ScrollBar = "ScrollBar";   //The class for a scroll bar.
        const string Static = "Static";	//The class for a static control.

        public int ID = 0;
        public string Name;
        public dynamic Control;
        public IntPtr hWnd { get { return Control.hWnd; } }
        public string ClassName { get { return Control.ClassName; } }

        public WinAPI.WindowTypes ControlType;

        public DlgItem(Win32Window item)
        {
            ID = WinApi.GetDlgCtrlID(item.hWnd);
            this.Control = item;
        }

        public DlgItem(IntPtr hWnd)
        {
            Win32Window item = new Win32Window(IntPtr.Zero);
            item.hWnd = new IntPtr(hWnd.ToInt32());
            ID = WinApi.GetDlgCtrlID(hWnd);
            switch ((string)(item.ClassName))
            {
                case Button:
                    if (item.Style.HasFlag(WinAPI.WindowStyles.BS_AUTOCHECKBOX))
                    {
                        this.Control = new Win32CheckBox(new IntPtr(hWnd.ToInt32()));
                        ControlType = WinAPI.WindowTypes.CheckBox;
                    }
                    else
                        this.Control = new Win32Button(hWnd);
                    break;
                case Edit:
                    this.Control = new Win32TextBox(hWnd);
                    break;
                case ListBox:
                    this.Control = new Win32ListBox(hWnd);
                    break;
            }
            if(ControlType == WinAPI.WindowTypes.Window)
                Enum.TryParse<WinAPI.WindowTypes>(item.ClassName, out ControlType);

           
        }

    }
    #endregion

    #region Класс настроек
    public class Settings
    {
        Tools owner;
        const int DialogID = 106;
        string IBName;
        //string IBPath;
        public IntPtr ParentWindow;

        public WinApi.NativeDialog Dialog = null;

        public Dictionary<string, DlgItem> DialogControls = null;

        public void ShowDialog()
        {
            ShowDialog(new Win32Window(ParentWindow, false), new System.Windows.RECT()); 
        }

        public void ShowDialog(Win32Window parent, System.Windows.RECT Position)
        {
            if (Dialog != null)
                Dialog = null;
            Dialog = new WinApi.NativeDialog(DialogID, parent);
            Dialog.Style = (WinAPI.WindowStyles)0x56810000;
            Dialog.ExtendedStyle = (WinAPI.WindowStylesEx)0x00010200;
            Dialog.Position = Position;
            Dialog.Visible = false;
            Dialog.Disable();
            Dialog.ControlChanged += Dialog_ControlChanged;
            DialogControls = Dialog.Controls;

            DialogControls["Edit.1001"].Control.Text = CurrentServer;
            DialogControls["Edit.1002"].Control.Text = CurrentWorkSpace;
            ((Win32Button)DialogControls["Button.1000"].Control).Click += Button1000_Click;

            DialogControls["Button.1003"].Control.Checked = logStateHistory;
            ((Win32CheckBox)DialogControls["Button.1003"].Control).Click += ShowLog_Click;
            if (logStateHistory)
                ShowLog_Click(DialogControls["Button.1003"].Control, null);

            DialogControls["Button.1007"].Control.Checked = AutoSave;
            ((Win32CheckBox)DialogControls["Button.1007"].Control).Click += Autosave_Click;

            ((Win32ListBox)DialogControls["ListBox.1004"].Control).DoubleClick += ListItem_DoubleClick;
        }

        private void ListItem_DoubleClick(object sender, MouseEventArgs e)
        {
            Win32ListBox listbox = ((Win32ListBox)DialogControls["ListBox.1004"].Control);
            string SelectedItem = listbox.ItemString(listbox.SelectedItem);
            owner.OpenDocByServerPath(SelectedItem);
        }

        private void Autosave_Click(object sender, MouseEventArgs e)
        {
            AutoSave = ((Win32CheckBox)sender).Checked == true;
        }

        private void Button1000_Click(object sender, MouseEventArgs e)
        {
            if (owner.PendingObjects.Count > 0)
                if (MessageBox.Show(Dialog, "Действительно отменить взятие в работу всех объектов?", "Вопрос", MessageBoxButtons.YesNo) == DialogResult.Yes)
                {
                    owner.FSWatcher.Changed -= owner.FSWatcher_Changed; // Если не выключить, то будт ругаться на то, что коллекция (PendingObjects) изменена
                    string[] copy = new string[owner.PendingObjects.Count];
                    owner.PendingObjects.CopyTo(copy);
                    foreach (string obj in copy)
                        owner.workspace.Undo(obj);
                    owner.FSWatcher.Changed += owner.FSWatcher_Changed;
                }
        }

        static Log LogfForm = new Log();

        private void ShowLog()
        {
            LogfForm.StatusLogList.Items.Clear();
            LogfForm.ShowInTaskbar = true;
            LogfForm.StatusLogList.Items.AddRange(owner.StatusLog.ToArray());
            LogfForm.ShowDialog();
        }

        private void ShowLog_Click(object sender, MouseEventArgs e)
        {
            if(sender != null)
                Parameters.logStateHistory = ((Win32CheckBox)sender).Checked == true;

            if (logStateHistory)
            {
                if (!LogfForm.Visible)
                {
                    LogfForm.FormClosed += LogfForm_FormClosed;
                    Thread logThread = new Thread(ShowLog);
                    logThread.SetApartmentState(ApartmentState.STA);
                    logThread.Start();
                }
            }
            else
                if(LogfForm.Visible)
                    LogfForm.BeginInvoke(new MethodInvoker(delegate
                    {
                        LogfForm.Close();
                    }));
        }

        private void LogfForm_FormClosed(object sender, FormClosedEventArgs e)
        {

            logStateHistory = false;
            if (DialogControls != null)
            {
                DialogControls["Button.1003"].Control.Checked = logStateHistory;

            }
        }

        public void AddObjectToPendingList(string Obj)
        {
            if(DialogControls != null)
            {
                Win32ListBox ListBox = DialogControls["ListBox.1004"].Control;
                if (!ListBox.Contains(Obj))
                    ListBox.AddItem(Obj);
            }

        }

        public void RemoveObjectFromPendingList(string Obj)
        {
            if (DialogControls != null)
            {
                Win32ListBox ListBox = DialogControls["ListBox.1004"].Control;
                if (ListBox.Contains(Obj))
                    ListBox.RemoveItem(ListBox.ItemIndex(Obj));
            }
        }

        public void ClearPendingList()
        {
            if (DialogControls != null)
            {
                Win32ListBox ListBox = DialogControls["ListBox.1004"].Control;
                while(ListBox.ItemCount > 0)
                    ListBox.RemoveItem(0);
            }
        }

        private int Dialog_ControlChanged(int ControlId, WinApi.WindowsMessages uMsg, IntPtr wParam, IntPtr lParam)
        {
            return 0;
        }

        public Settings(Tools owner)
        {
            this.owner = owner;
            IBName = owner.IBName;
            Parameters.Load(IBName);
            logStateHistory = Parameters.logStateHistory;
        }

        public string CurrentServer { get { return Parameters.CurrentServer; } set { Parameters.CurrentServer = value; } }
        public string CurrentWorkSpace { get { return Parameters.CurrentWorkSpace; } set { Parameters.CurrentWorkSpace = value; } }
        public string CurrentProject { get { return Parameters.CurrentProject; } set { Parameters.CurrentProject = value; } }
        public string ConfigurationRootFolder { get { return Parameters.ConfigurationRootFolder; } set { Parameters.ConfigurationRootFolder = value; } }
        public string ExtReportRootFolder { get { return Parameters.ExtReportRootFolder; } set { Parameters.ExtReportRootFolder = value; } }
        public string UpdateCheckPath { get { return Parameters.UpdateCheckPath; } set { Parameters.UpdateCheckPath = value; } }
        public bool AutoSave { get { return Parameters.AutoSave; } set { Parameters.AutoSave = value; Parameters.Save(IBName); } }
        public bool logStateHistory { get {
                return Parameters.logStateHistory;
            } set {
                Parameters.logStateHistory = value;
                ShowLog_Click(null, null);    
                Parameters.Save(IBName);
            } }


        [Serializable]
        struct Parameters
        {
            public static string CurrentServer;
            public static string CurrentWorkSpace;
            public static string CurrentProject;
            public static string ConfigurationRootFolder;
            public static string ExtReportRootFolder;
            public static string UpdateCheckPath;
            public static bool logStateHistory;
            public static bool AutoSave;

            public static void Load(string IBName)
            {
                RegistryKey TFSPluginEntry = Registry.CurrentUser.OpenSubKey("Software\\1C\\1Cv7\\7.7\\" + IBName + "\\Config\\TFS");
                if (TFSPluginEntry != null)
                    foreach (var Parameter in typeof(Parameters).GetFields(BindingFlags.Static | BindingFlags.Public))
                    {
                        var paramValue = (string)TFSPluginEntry.GetValue(Parameter.Name);
                        if (Parameter.FieldType == typeof(bool))
                        {
                            bool temp = false;
                            bool.TryParse(paramValue, out temp);
                            Parameter.SetValue(null, temp);
                        }
                        else
                        {
                            Parameter.SetValue(null, Convert.ChangeType(paramValue, Parameter.FieldType));
                        }     
                    } 
            }

            public static void Save(string IBName)
            {
                RegistryKey TFSPluginEntry = Registry.CurrentUser.CreateSubKey("Software\\1C\\1Cv7\\7.7\\" + IBName + "\\Config\\TFS");
                var n = typeof(Parameters).GetFields(BindingFlags.Static | BindingFlags.Public);
                foreach (var Parameter in n)
                {
                    string Name = Parameter.Name;
                    try
                    {
                        var value = Parameter.GetValue(null);
                        if (value != null)
                        {
                            TFSPluginEntry.SetValue(Name, value.ToString());
                        }
                    }
                    catch (Exception Ex)
                    {
                        MessageBox.Show("Произошла ошибка при сохранении параметров в регистр: \n\r" + Ex.Message + ". Ошибка получения параметра: " + Name);
                    }
                }
            }
        }

        internal void UpdateLog(ArrayList statusLog)
        {
            if (LogfForm.Visible)
            {
                LogfForm.BeginInvoke(new MethodInvoker(delegate { LogfForm.Update(statusLog); }));  
            }
        }

        internal void UpdateLog(string  text)
        {
            if (LogfForm.Visible)
            {
                LogfForm.BeginInvoke(new MethodInvoker(delegate { LogfForm.Update(text); }));
            }
        }

        ~Settings()
        {
            Parameters.Save(IBName);
        }
    }
    #endregion

    #region Расширение для CfgDoc
    public static class iCfgDocExtension
    {
        public delegate bool ReadOnlyState_handler(CfgDoc Doc, bool Set, WorkBook Parent = null);


        public static Dictionary<DocTypes, ReadOnlyState_handler> ReadOnlyOperations = new Dictionary<DocTypes, ReadOnlyState_handler>();

        private static Dictionary<string, bool> ReadOnlyCache = new Dictionary<string, bool>();

        public static void AddReadOnlyOperationHandler(DocTypes DocType, ReadOnlyState_handler Handler)
        {
            ReadOnlyOperations.Add(DocType, Handler);
        }

        public static void RemoveReadOnlyOperationHandler(DocTypes DocType)
        {
            if (ReadOnlyOperations.ContainsKey(DocType))
                ReadOnlyOperations.Remove(DocType);
        }


        public static int CurrentPage(this ICfgDoc Doc)
        {
            SysTabControl32 DocTabControl;
            if (Tools.oConfigurator != null)
                if (Doc is WorkBook)
                {
                    Win32Window activeWindow = new Win32Window(new IntPtr(Tools.oConfigurator.Windows.ActiveWnd.hWnd), false).Parent;
                    var TabControl = activeWindow.Children.FirstOrDefault(t => t.ClassName == nameof(SysTabControl32));
                    if (TabControl != null)
                    {
                        DocTabControl = new SysTabControl32(TabControl.hWnd, false);
                        return DocTabControl.ActiveTab;
                    }
                }
            return 0;
        }

        public static string TFSFileName(this CfgDoc Doc, WorkBook ActiveWorkBook = null)
        {
            return ((ICfgDoc)Doc).TFSFileName(ActiveWorkBook);
        }

        public static string TFSFileName(this ICfgDoc Doc, WorkBook ActiveWorkBook = null)
        {
            string WorkBookPath;
            string WorkBookName;
            string WorkBookDirectory;

            if (ActiveWorkBook != null)
            {
                WorkBookPath = ActiveWorkBook.path;
                WorkBookName = ActiveWorkBook.Name;
                WorkBookDirectory = ActiveWorkBook.TFSDirectory();
            }
            else
            {
                WorkBookPath = Doc.path;
                WorkBookName = Doc.Name;
                WorkBookDirectory = Doc.TFSDirectory();
            }

            string[] Name = Doc.Name.Split('.');

            switch (Doc.Type)
            {
                case DocTypes.docDEdit:
                    DialogDoc thisDialogDoc = (DialogDoc)Doc;
                    switch (Name.Length)
                    {
                        case 1:
                            if (Name[0].Contains("CEditDoc::"))
                                return Path.GetFileName(WorkBookPath) + "/Форма.frm";
                            return Name[0];

                        case 4:
                            if (Name[2].Contains("Форма группы"))
                                return WorkBookDirectory + "/ФормаГруппы/Форма.frm";

                            return WorkBookDirectory + "/" + Name[2] + ".frm";
                        case 5:

                            return WorkBookDirectory + "/" + Name[3] + ".fls/Форма.frm";

                        default:
                            return string.Empty;
                    }


                case DocTypes.docTable:
                    ITableDoc thisTableDoc = (ITableDoc)Doc;

                    switch (Name.Length)
                    {
                        case 1:
                            if (Name[0].Contains("CSheetDoc::"))
                                if (Name[0] == "CSheetDoc::")
                                    return Path.GetFileName(WorkBookPath) + "/Таблица.mxl";
                                else
                                    return Path.GetFileName(WorkBookPath) + "/" + Name[0].Replace("CSheetDoc::", "").Replace(' ', '_').Replace('-', '_') + ".mxl";
                            return Name[0];
                        case 2:
                            return WorkBookDirectory + "/" + Name[1].Replace(' ', '_').Replace('-', '_') + ".mxl";
                        case 4:
                            if (Name[2].Contains("Форма группы"))
                                return WorkBookDirectory + "/ФормаГруппы/" + Name[3].Replace(' ', '_').Replace('-', '_') + ".mxl";

                            return WorkBookDirectory + "/" + Name[3].Replace(' ', '_').Replace('-', '_') + ".mxl";
                        case 5:

                            return WorkBookDirectory + "/" + Name[3] + ".fls/" + Name[4].Replace(' ', '_').Replace('-', '_') + ".mxl";

                        default:
                            return string.Empty;
                    }

                case DocTypes.docText:
                    TextDoc thisTextDoc = (TextDoc)Doc;
                    if (thisTextDoc.IsModule)
                    {

                        if (Doc.Name.Contains("CWBModuleDoc:"))
                            return Path.GetFileName(WorkBookPath) + "/МодульФормы.1s";


                        switch (Name.Length)
                        {
                            case 1:
                                return "ГлобальныйМодуль.1s";
                            case 3:
                                return WorkBookDirectory + "/МодульПроведения.1s";
                            case 4:

                                if (Doc.Name.Contains(".Форма группы."))
                                    return WorkBookDirectory + "/ФормаГруппы/МодульФормы.1s";
                                else
                                    return WorkBookDirectory + "/" + Name[3] + (Doc.Name.Contains(".Форма.") ? "Формы" : "") + ".1s";

                            case 5:
                                return WorkBookDirectory + "/" + Name[3] + ".fls/МодульФормы.1s";
                        }
                        return string.Empty;

                    }
                    else
                    {
                        if (Doc.Name.Contains("CMDDescriptionDoc:"))
                            return Path.GetFileName(WorkBookPath) + "/Описание.txt";

                        return WorkBookDirectory + " /Описание.txt";
                    }
                case DocTypes.docWorkBook:
                    WorkBook thisWorkBook = (WorkBook)Doc;
                    return ((ICfgDoc)thisWorkBook.Page[thisWorkBook.ActivePage]).TFSFileName(thisWorkBook);
                case DocTypes.docUnknown:
                    return  Tools.oConfigurator.MDWnd.GetSelected().Replace("\\","/") + "/Структура.mdp" ;//Doc.Name + ", " + Doc.path;
                default:
                    return string.Empty;
            }
        }

        public static string TFSDirectory(this ICfgDoc Doc)
        {
            if (Doc.ID == -1)
                return Doc.path;

            string[] Name = Doc.Name.Split('.');
            string MetaTypeRes;

            switch (Name[0])
            {
                case "Отчет":
                    MetaTypeRes = "Отчеты/";
                    break;
                case "Обработка":
                    MetaTypeRes = "Обработки/";
                    break;
                case "Справочник":
                    MetaTypeRes = "Справочники/";
                    break;
                case "Документ":
                    MetaTypeRes = "Документы/";
                    break;
                case "Журнал":
                    MetaTypeRes = "ЖурналыДокументов/";
                    break;
                case "Общие таблицы":
                    MetaTypeRes = "ОбщиеТаблицы/";
                    break;
                case "Глобальный модуль":
                    return "ГлобальныйМодуль.1s";
                default:
                    return string.Empty;
            }


            return MetaTypeRes + Name[1];
        }

        public static bool ReadOnly(this CfgDoc Doc, bool Set, WorkBook Parent = null)
        {       
            if (ReadOnlyOperations.Keys.Contains(Doc.Type))
            {
                ReadOnlyCache[Doc.Name] = ReadOnlyOperations[Doc.Type](Doc, Set, Parent);

                return Doc.ReadOnly();
            }
            return false;
        }

        public static bool ReadOnly(this CfgDoc Doc)
        {
            return ReadOnlyCache.ContainsKey(Doc.Name) ? ReadOnlyCache.ContainsKey(Doc.Name) : false;
        }

    }
    #endregion

    #region Интерфейсы OLE
    [Serializable]
    [StructLayout(LayoutKind.Sequential)]
    public struct COMRECT
    {
        public int left;
        public int top;
        public int right;
        public int bottom;
        public bool IsEmpty { get { return left == top && right == bottom; } }

        public System.Windows.RECT ToRECT()
        {
            return new System.Windows.RECT(left, top, right, bottom);
        }

        public override string ToString()
        {
            return "Left = " + left + " Top " + top + " Right = " + right + " Bottom = " + bottom;
        }
    }

    [ComImport, InterfaceType(ComInterfaceType.InterfaceIsIUnknown), Guid("B196B288-BAB4-101A-B69C-00AA00341D07")]
    public interface IOleControl
    {
        [PreserveSig]
        void GetControlInfo([In, Out] ref tagCONTROLINFO pCI);
        [PreserveSig]
        void OnMnemonic([In]System.Windows.Forms.Message pMsg);
        [PreserveSig]
        void OnAmbientPropertyChange([In]int dispID);
        [PreserveSig]
        void FreezeEvents([In, MarshalAs(UnmanagedType.Bool)] bool bFreeze);
    }
    [StructLayout(LayoutKind.Sequential)]
    public struct tagCONTROLINFO
    {
        [MarshalAs(UnmanagedType.U4)]
        int cb;
        [MarshalAs(UnmanagedType.Struct)]
        tagACCEL hAccel;
        [MarshalAs(UnmanagedType.U2)]
        uint cAccel;
        [MarshalAs(UnmanagedType.U4)]
        uint dwFlags;
    }

    [Serializable]
    [StructLayout(LayoutKind.Sequential)]
    public struct SIZEL
    {
        [MarshalAs(UnmanagedType.I4)]
        public int cx;
        [MarshalAs(UnmanagedType.I4)]
        public int cy;
        public SIZEL(int x, int y)
        {
            this.cx = x;
            this.cy = y;
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct tagACCEL
    {
        byte fVirt;
        [MarshalAs(UnmanagedType.U2)]
        uint key;
        [MarshalAs(UnmanagedType.U2)]
        uint cmd;
    }


    public enum OleVerbs : int
    {
        OLEIVERB_PRIMARY = 0,
        OLEIVERB_SHOW = -1,
        OLEIVERB_OPEN = -2,
        OLEIVERB_HIDE = -3,
        OLEIVERB_UIACTIVATE = -4,
        OLEIVERB_INPLACEACTIVATE = -5,
        OLEIVERB_DISCARDUNDOSTATE = -6
    }

    //[ComImport, InterfaceType(ComInterfaceType.InterfaceIsIUnknown), Guid("00000118-0000-0000-C000-000000000046")]
    //public interface IOleClientSite
    //{
    //    [PreserveSig]
    //    [return: MarshalAs(UnmanagedType.Error)]
    //    uint SaveObject();
    //    [PreserveSig]
    //    [return: MarshalAs(UnmanagedType.Error)]
    //    uint GetMoniker(
    //        [In, MarshalAs(UnmanagedType.U4)]uint dwAssign,
    //        [In, MarshalAs(UnmanagedType.U4)] uint dwWhichMoniker,
    //        [Out, MarshalAs(UnmanagedType.Interface)] out System.Runtime.InteropServices.ComTypes.IMoniker ppmk);
    //    [PreserveSig]
    //    [return: MarshalAs(UnmanagedType.Error)]
    //    uint GetContainer(
    //        [Out, MarshalAs(UnmanagedType.Interface)] out Microsoft.VisualStudio.OLE.Interop.IOleContainer ppContainer);
    //    [PreserveSig]
    //    [return: MarshalAs(UnmanagedType.Error)]
    //    uint ShowObject();
    //    [PreserveSig]
    //    [return: MarshalAs(UnmanagedType.Error)]
    //    uint OnShowWindow(
    //        [In, MarshalAs(UnmanagedType.Bool)] bool fShow);
    //    [PreserveSig]
    //    [return: MarshalAs(UnmanagedType.Error)]
    //    uint RequestNewObjectLayout();
    //}

    [ComImport, Guid("00000112-0000-0000-C000-000000000046"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IOleObject
    {
        void SetClientSite(
            [In, MarshalAs(UnmanagedType.Interface)] Microsoft.VisualStudio.OLE.Interop.IOleClientSite pClientSite);
        void GetClientSite(
            [Out, MarshalAs(UnmanagedType.Interface)]out Microsoft.VisualStudio.OLE.Interop.IOleClientSite ppClientSite);
        void SetHostNames(
           [In, MarshalAs(UnmanagedType.LPWStr)] string szContainerApp,
           [In, MarshalAs(UnmanagedType.LPWStr)] string szContainerObj);
        void Close(
           [In, MarshalAs(UnmanagedType.U4)] uint dwSaveOption);
        void SetMoniker(
           [In, MarshalAs(UnmanagedType.U4)] uint dwWhichMoniker,
           [In, MarshalAs(UnmanagedType.Interface)] System.Runtime.InteropServices.ComTypes.IMoniker pmk);
        void GetMoniker(
           [In, MarshalAs(UnmanagedType.U4)] uint dwAssign,
           [In, MarshalAs(UnmanagedType.U4)] uint dwWhichMoniker,
           [Out, MarshalAs(UnmanagedType.Interface)] out System.Runtime.InteropServices.ComTypes.IMoniker ppmk);
        void InitFromData(
           [In, MarshalAs(UnmanagedType.Interface)] System.Runtime.InteropServices.ComTypes.IDataObject pDataObject,
           [In, MarshalAs(UnmanagedType.Bool)] bool fCreation,
           [In, MarshalAs(UnmanagedType.U4)] uint dwReserved);
        void GetClipboardData(
           [In, MarshalAs(UnmanagedType.U4)] uint dwReserved,
           [Out, MarshalAs(UnmanagedType.Interface)]out System.Runtime.InteropServices.ComTypes.IDataObject ppDataObject);
        void DoVerb(
                     OleVerbs iVerb,
                  [In] IntPtr lpmsg,
                    [In, MarshalAs(UnmanagedType.Interface)]
                      Microsoft.VisualStudio.OLE.Interop.IOleClientSite pActiveSite,
                     int lindex,
                     IntPtr hwndParent,
                    [In ] ref System.Windows.RECT lprcPosRect);
        void EnumVerbs(
            [Out, MarshalAs(UnmanagedType.IUnknown)] out object ppEnumOleVerb);
        void Update();
        void IsUpToDate();
        void GetUserClassID(
           [Out, MarshalAs(UnmanagedType.Struct)] out Guid pClsid);
        void GetUserType(
           [In, MarshalAs(UnmanagedType.U4)] uint dwFormOfType,
           [Out, MarshalAs(UnmanagedType.LPWStr)] out string pszUserType);
        void SetExtent(
           [In, MarshalAs(UnmanagedType.U4)] uint dwDrawAspect,
           [In] ref SIZEL psizel);
        void GetExtent(
           [In, MarshalAs(UnmanagedType.U4)] uint dwDrawAspect,
           [Out] out SIZEL psizel);
        void Advise(
           [In, MarshalAs(UnmanagedType.Interface)]  System.Runtime.InteropServices.ComTypes.IAdviseSink pAdvSink,
           [Out, MarshalAs(UnmanagedType.U4)] out uint pdwConnection);
        void Unadvise(
           [In, MarshalAs(UnmanagedType.U4)] uint dwConnection);
        void EnumAdvise(
           [Out, MarshalAs(UnmanagedType.Interface)] out System.Runtime.InteropServices.ComTypes.IEnumSTATDATA ppenumAdvise);
        void GetMiscStatus(
           [In, MarshalAs(UnmanagedType.U4)] uint dwAspect,
           [Out, MarshalAs(UnmanagedType.U4)] out uint pdwStatus);
        void SetColorScheme(
           [In, MarshalAs(UnmanagedType.Struct)] object pLogpal);
    }



    //    [ComConversionLoss]
    //[ComImport, Guid("00000114-0000-0000-C000-000000000046")]
    //[InterfaceType(1)]
    //public interface IOleWindow
    //{
    //    //
    //    // Parameters:
    //    //   fEnterMode:
    //    void ContextSensitiveHelp(int fEnterMode);
    //    //
    //    // Parameters:
    //    //   phwnd:
    //    void GetWindow(out IntPtr phwnd);
    //}

    // [ComConversionLoss]
    //[ComImport, Guid("00000113-0000-0000-C000-000000000046")]
    //[InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    //public interface IOleInPlaceObject : IOleWindow
    //{
    //    //
    //    // Parameters:
    //    //   fEnterMode:
    //    void ContextSensitiveHelp( int fEnterMode);
    //    //
    //    // Parameters:
    //    //   phwnd:
    //    void GetWindow(out IntPtr phwnd);
    //    //
    //    void InPlaceDeactivate();
    //    //
    //    void ReactivateAndUndo();
    //    //
    //    // Parameters:
    //    //   lprcPosRect:
    //    //
    //    //   lprcClipRect:
    //    void SetObjectRects( RECT[] lprcPosRect,  RECT[] lprcClipRect);
    //    //
    //    void UIDeactivate();
    //}

    //[ComImport, Guid("00000113-0000-0000-C000-000000000046"), ]
    //public interface IOleInplaceObject
    //{

    //}
    #endregion

    
    [SecurityCritical]
    #region часть класса Tools реализующая OLE интерфейсы
    public partial class Tools:  IOleControl, Microsoft.VisualStudio.OLE.Interop.IOleInPlaceObject, IOleObject
    {
        Settings SettingsDialog;

        #region OleControl

        Microsoft.VisualStudio.OLE.Interop.IOleClientSite ClientSight = null;
  
       public void SetClientSite([In, MarshalAs(UnmanagedType.Interface)] Microsoft.VisualStudio.OLE.Interop.IOleClientSite pClientSite)
        {
            ClientSight = pClientSite;
            //Debug.Print("SetClientSite");
        }

        public void GetClientSite([MarshalAs(UnmanagedType.Interface), Out] out Microsoft.VisualStudio.OLE.Interop.IOleClientSite ppClientSite)
        {
            ppClientSite = ClientSight;
            //Debug.Print("GetClientSite");
        }

        public void Close([In, MarshalAs(UnmanagedType.U4)] uint dwSaveOption)
        {
            //SettingsDialog.Dialog?.Destroy();
            //SettingsDialog.Dialog = null;
        }

        [HandleProcessCorruptedStateExceptions]
        public void DoVerb([In, MarshalAs(UnmanagedType.I4)] OleVerbs iVerb, [In] IntPtr lpmsg, [In, MarshalAs(UnmanagedType.Interface)]Microsoft.VisualStudio.OLE.Interop.IOleClientSite pActiveSite, [In, MarshalAs(UnmanagedType.I4)] int lindex, IntPtr hwndParent, [In] ref System.Windows.RECT lprcPosRect)
        {
            //Debug.Print("{0}, {1}", iVerb, lprcPosRect);
            switch (iVerb)
            {
                case OleVerbs.OLEIVERB_INPLACEACTIVATE:
                    {
                        SettingsDialog.ParentWindow = hwndParent;
                        SettingsDialog.ShowDialog();
                        foreach (string obj in PendingObjects)
                            SettingsDialog.AddObjectToPendingList(obj);

                        SettingsDialog.Dialog.Position = new System.Windows.RECT(0, 0, pSize.cx, pSize.cy);
                        SettingsDialog.Dialog.Visible = false;
                        SettingsDialog.Dialog.Enable();
                        ClientSight.OnShowWindow(0);
                        break;
                    }
                case OleVerbs.OLEIVERB_UIACTIVATE:
                    if(SettingsDialog.Dialog.Visible)
                       SettingsDialog.Dialog.Position = lprcPosRect;
                    SettingsDialog.Dialog.Visible = true;
                    SettingsDialog.Dialog.Enable();
                    pActiveSite.OnShowWindow(1);
                    break;
                default:
                    //Debug.Print("{0}, {1}", iVerb, lprcPosRect);
                    break;
            }
        }

        public void SetExtent([In, MarshalAs(UnmanagedType.U4)] uint dwDrawAspect, [In] ref SIZEL psizel)
        {
            pSize = new SIZEL(MainWindow.Width, MainWindow.Height);
            psizel = pSize;
        }

        SIZEL pSize;
        public void GetExtent([In, MarshalAs(UnmanagedType.U4)] uint dwDrawAspect, [Out] out SIZEL psizel)
        {
            psizel = pSize;
        }

        public void GetWindow(out IntPtr phwnd)
        {
            //throw new NotImplementedException(); 
            phwnd = SettingsDialog.Dialog.hWnd;
        }

        public void SetObjectRects(Microsoft.VisualStudio.OLE.Interop.RECT[] lprcPosRect, Microsoft.VisualStudio.OLE.Interop.RECT[] lprcClipRect)
        {
            SettingsDialog.Dialog.Position = new System.Windows.RECT(lprcPosRect[0]); //lprcPosRect[0];
        }

        public void InPlaceDeactivate()
        {
            SettingsDialog.Dialog?.Destroy();
            SettingsDialog.Dialog = null;
            //throw new NotImplementedException();
        }

        //void Microsoft.VisualStudio.OLE.Interop.IOleWindow.GetWindow(out IntPtr phwnd)
        //{
        //    //phwnd = SettingsDialog.Dialog;
        //    throw new NotImplementedException();
        //}

        #endregion

        #region Unused 

        public void GetControlInfo(ref tagCONTROLINFO pCI)
        {
            throw new NotImplementedException();
        }

        public void OnMnemonic(Message pMsg)
        {
            throw new NotImplementedException();
        }

        public void OnAmbientPropertyChange(int dispID)
        {
            throw new NotImplementedException();
        }

        public void FreezeEvents(bool bFreeze)
        {
            throw new NotImplementedException();
        }
   
        public void SetHostNames(string szContainerApp, string szContainerObj)
        {
            throw new NotImplementedException();
        }

        public void SetMoniker(uint dwWhichMoniker, System.Runtime.InteropServices.ComTypes.IMoniker pmk)
        {
            throw new NotImplementedException();
        }

        public void GetMoniker(uint dwAssign, uint dwWhichMoniker, out System.Runtime.InteropServices.ComTypes.IMoniker ppmk)
        {
            throw new NotImplementedException();
        }

        public void InitFromData(System.Runtime.InteropServices.ComTypes.IDataObject pDataObject, bool fCreation, uint dwReserved)
        {
            throw new NotImplementedException();
        }

        public void GetClipboardData(uint dwReserved, out System.Runtime.InteropServices.ComTypes.IDataObject ppDataObject)
        {
            throw new NotImplementedException();
        }

        public void EnumVerbs(out object ppEnumOleVerb)
        {
            throw new NotImplementedException();
        }

        public void Update()
        {
           throw new NotImplementedException();
        }

        public  void IsUpToDate()
        {
        }

        public void GetUserClassID(out Guid pClsid)
        {
            throw new NotImplementedException();
        }

        public void GetUserType(uint dwFormOfType, out string pszUserType)
        {
            pszUserType = string.Empty;
        }

        public void Advise(System.Runtime.InteropServices.ComTypes.IAdviseSink pAdvSink, out uint pdwConnection)
        {
            throw new NotImplementedException();
        }

        public void Unadvise(uint dwConnection)
        {
            throw new NotImplementedException();
        }

        public void EnumAdvise(out System.Runtime.InteropServices.ComTypes.IEnumSTATDATA ppenumAdvise)
        {
            throw new NotImplementedException();
        }

        public void GetMiscStatus(uint dwAspect, out uint pdwStatus)
        {
            throw new NotImplementedException();
        }

        public void SetColorScheme(object pLogpal)
        {
            throw new NotImplementedException();
        }

        public void ContextSensitiveHelp(int fEnterMode)
        {
            throw new NotImplementedException();
        }

        
        public void UIDeactivate()
        {
            //Debug.Print("UIDeactivate");// 
            throw new NotImplementedException();
        }



        public void ReactivateAndUndo()
        {
            //Debug.Print("ReactivateAndUndo"); //
            throw new NotImplementedException();
        }



        //public void ContextSensitiveHelp(int fEnterMode)
        //{
        //    throw new NotImplementedException();

        //}

        #endregion
    }
    #endregion
}
