using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;
using System.Windows;
using System.Runtime.ExceptionServices;
using System.Security;

public class WindowWrapper : Win32Window, IDisposable
{
    public NativeMenu MainMenu;
    public delegate bool WindowMessageFilter(WindowWrapper Window, NativeMenu.WindowsMessages uMsg, IntPtr wParam, IntPtr lParam);

    public Dictionary<NativeMenu.WindowsMessages, WindowMessageFilter> WindowMessageMap = new Dictionary<NativeMenu.WindowsMessages, WindowMessageFilter>();
    
    public string Caption;
    public bool GetChildren;

    public WindowWrapper(IntPtr handle, NativeMenu.UpdateMenu MenuConstructor = null) : base(handle, false)
    {
        GetChildren = true;
        MainMenu = new NativeMenu(handle, this, MenuConstructor);
        //EnableVisuals();
    }

    public WindowWrapper(IntPtr handle, bool GetChildren, NativeMenu.UpdateMenu MenuConstructor = null) : base(handle, false)
    {
        this.GetChildren = GetChildren;
        MainMenu = new NativeMenu(handle, this, MenuConstructor);
        //EnableVisuals();
    }

    //public IntPtr Handle
    //{
    //    get { return hWnd; }
    //}

    #region IDisposable Support
    private bool disposedValue = false; // To detect redundant calls

    protected virtual void Dispose(bool disposing)
    {
        if (!disposedValue)
        {
            if (disposing)
            {
                // TODO: dispose managed state (managed objects).
            }

            MainMenu.Dispose();
            disposedValue = true;
        }
    }

    // TODO: override a finalizer only if Dispose(bool disposing) above has code to free unmanaged resources.
    // ~WindowWrapper() {
    //   // Do not change this code. Put cleanup code in Dispose(bool disposing) above.
    //   Dispose(false);
    // }

    // This code added to correctly implement the disposable pattern.
    public void Dispose()
    {
        // Do not change this code. Put cleanup code in Dispose(bool disposing) above.
        Dispose(true);
        // TODO: uncomment the following line if the finalizer is overridden above.
        GC.SuppressFinalize(this);
    }
    #endregion
}


public class NativeMenu : IDisposable
{
    public delegate bool MenuItem_Handler(int MenuId);

    public event MenuItem_Handler onMenuClick;

    public delegate void ConfigWindow_MenuChange(IntPtr hMenu, MenuTree mMenuTree);

    public event ConfigWindow_MenuChange onMenuChange = null;

    public delegate SubMenu UpdateMenu(SubMenu Parent, out string ItemAfter);

    public delegate void PopUpMenuInit(SubMenu PopUp);

    public bool Subclassed = false;

    Dictionary<SubMenu, int> MenuCache = new Dictionary<SubMenu, int>();
    public Dictionary<int, MenuItem_Handler> CommandMap = new Dictionary<int, MenuItem_Handler>();
    public UpdateMenu MenuConstrucor;
    public PopUpMenuInit PopUpMenuTracker;
    public IntPtr handle;
    public wndProc eventHandler;
    public IntPtr WndProcId = new IntPtr(0);
    GCHandle WndProcHandler;
    public SubMenu MainMenu = null;
    private WindowWrapper Window;
    
    protected class NativeMethods {

        [DllImport("user32")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool EnumChildWindows(IntPtr window, EnumWindowProc callback, IntPtr i);

        [DllImport("user32.dll", SetLastError = true)]
        static extern uint GetWindowThreadProcessId(IntPtr hWnd, out uint lpdwProcessId);

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        public static extern IntPtr SendMessage(IntPtr hWnd, int wMsg, IntPtr wParam, IntPtr lParam);

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        public static extern bool SendMessage(IntPtr hWnd, uint Msg, int wParam, StringBuilder lParam);

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        public static extern object SendMessage(IntPtr hWnd, uint Msg, object wparam, object lParam);

        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern int RegisterWindowMessage(string lpString);

        [return: MarshalAs(UnmanagedType.Bool)]
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern bool PostMessage(IntPtr hWnd, int wMsg, IntPtr wParam, IntPtr lParam);

        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern IntPtr GetMenu(IntPtr hWnd);

        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern int GetMenuItemID(IntPtr hMenu, int position);

        [return: MarshalAs(UnmanagedType.Bool)]
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern bool AppendMenu(IntPtr hMenu, MenuFlags uFlags, int uIDNewItem, [MarshalAs(UnmanagedType.LPTStr)] string lpNewItem);

        [return: MarshalAs(UnmanagedType.Bool)]
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern bool AppendMenu(IntPtr hMenu, MenuFlags uFlags, int uIDNewItem, IntPtr hBitMap);

        [return: MarshalAs(UnmanagedType.Bool)]
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern bool AppendMenu(IntPtr hMenu, MenuFlags uFlags, IntPtr MenuBitMAp, [MarshalAs(UnmanagedType.LPTStr)] string lpNewItem);

        [return: MarshalAs(UnmanagedType.Bool)]
        [DllImport("user32", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern bool InsertMenu(IntPtr hMenu, int position, MenuFlags flags, IntPtr uIDNewItem, [MarshalAs(UnmanagedType.LPTStr)] string lpNewItem);

        [DllImport("user32.dll")]
        public static extern IntPtr CreatePopupMenu();

        [DllImport("user32.dll", SetLastError = true)]
        public static extern uint EnableMenuItem(IntPtr hMenu, int itemId, MenuFlags uEnable);

        [DllImport("user32.dll")]
        public static extern bool DrawMenuBar(IntPtr hWnd);

        [DllImport("user32.dll", SetLastError = true)]
        public static extern IntPtr GetSubMenu(IntPtr hMenu, int nPos);

        [DllImport("user32.dll")]
        public static extern bool RemoveMenu(IntPtr hMenu, int uPosition, MenuFlags uFlags);

        [DllImport("user32.dll")]
        public static extern bool DestroyMenu(IntPtr hMenu);

        [DllImport("user32.dll")]
        public static extern IntPtr GetSystemMenu(IntPtr hWnd, bool bRevert);

        [DllImport("user32.dll")]
        public static extern bool DeleteMenu(IntPtr hMenu, int uPosition, MenuFlags uFlags);
        [DllImport("user32.dll")]
        public static extern int GetMenuItemCount(IntPtr hMenu);

        [DllImport("user32.dll")]
        public static extern bool GetMenuItemInfo(IntPtr hMenu, uint uItem, bool fByPosition, ref MENUITEMINFO lpmii);

        [DllImport("user32.dll")]
        public static extern bool SetMenuItemInfo(IntPtr hMenu, uint uItem, bool fByPosition, ref MENUITEMINFO lpmii);

        [DllImport("ComCtl32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool GetWindowSubclass(IntPtr hWnd, wndProc pfnSubclass, IntPtr uIdSubclass, out IntPtr dwRefData);


        [DllImport("ComCtl32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool SetWindowSubclass(IntPtr hWnd, wndProc pfnSubclass, IntPtr uIdSubclass, IntPtr dwRefData);

        [DllImport("ComCtl32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool RemoveWindowSubclass(IntPtr hWnd, wndProc pfnSubclass, IntPtr uIdSubclass);

        //[DllImport("ComCtl32.dll")]
        //public static unsafe extern long DefSubclassProc(IntPtr hWnd, uint uMsg, HandleRef wParam, HandleRef lParam);

        [DllImport("ComCtl32.dll")]
        public static unsafe extern IntPtr DefSubclassProc(IntPtr hWnd, uint uMsg, IntPtr wParam, IntPtr lParam);

        [DllImport("user32.dll")]
        public static extern bool SetMenuItemBitmaps(IntPtr hMenu, int uPosition, MenuFlags uFlags,  IntPtr hBitmapUnchecked, IntPtr hBitmapChecked);

    }

    [StructLayout(LayoutKind.Sequential)]
    public struct MENUITEMINFO : IDisposable
    {
        public int cbSize;
        public MenuItemInfofMask fMask;
        public MenuItemInfofType fType;
        public MenuItemInfofState fState;
        public int wID;
        public IntPtr hSubMenu;
        public IntPtr hbmpChecked;
        public IntPtr hbmpUnchecked;
        public IntPtr dwItemData;
        public IntPtr dwTypeData;
        public int cch;
        public IntPtr hbmpItem;

        // return the size of the structure
        public static uint sizeOf
        {
            get { return (uint)Marshal.SizeOf(typeof(MENUITEMINFO)); }
        }

        public string ItemData
        {
            get
            {
                if (dwItemData != IntPtr.Zero)
                {
                    return Marshal.PtrToStringAnsi(dwItemData);
                }
                else
                    return null;
            }
        }

        public string TypeData
        {
            get
            {
                if (dwTypeData != IntPtr.Zero)
                {
                    return Marshal.PtrToStringAnsi(dwTypeData);
                }
                else
                    return null;
            }
        }

        public Bitmap BmpItem
        {
            get
            {
                if (hbmpItem != IntPtr.Zero)
                {
                    return Marshal.PtrToStructure<Bitmap>(hbmpItem);
                }
                else
                    return null;
            }
        }


        public void Dispose()
        {
            
            //Marshal.FreeHGlobal(dwItemData);
            //Marshal.FreeHGlobal(dwTypeData);
            //Marshal.FreeHGlobal(hbmpItem);
            
        }
    }

    public class SubMenu : MenuItem
    {
        internal NativeMenu Owner;

        public MenuTree Children;

        private Dictionary<int, MenuItem_Handler> Handlers = new Dictionary<int, MenuItem_Handler>();

        public void RefillChildrenList()
        {
            this.Children = new MenuTree();
            int Items = NativeMethods.GetMenuItemCount(this);

            for (int i = 0; i < Items; i++)
            {
                MENUITEMINFO ii = new MENUITEMINFO
                {
                    cbSize = Marshal.SizeOf(typeof(MENUITEMINFO)),
                    fMask = MenuItemInfofMask.MIIM_ID | MenuItemInfofMask.MIIM_SUBMENU | MenuItemInfofMask.MIIM_STRING | MenuItemInfofMask.MIIM_DATA | MenuItemInfofMask.MIIM_FTYPE | MenuItemInfofMask.MIIM_BITMAP | MenuItemInfofMask.MIIM_CHECKMARKS,
                    cch = 50,
                    dwTypeData = Marshal.AllocHGlobal(50),
                    dwItemData = Marshal.AllocHGlobal(50),
                    //hbmpChecked = Marshal.AllocHGlobal(150),
                    //hbmpUnchecked = Marshal.AllocHGlobal(150),
                    //hbmpItem = Marshal.AllocHGlobal(150)
                };

                if (NativeMethods.GetMenuItemInfo(this, (uint)i, true, ref ii))
                {

                    if (ii.fType == MenuItemInfofType.MFT_OWNERDRAW)
                        ii.hbmpItem = Marshal.AllocHGlobal(1024);

                    string tt = ii.TypeData;

                    if (!string.IsNullOrEmpty(tt))
                    {
                        if (ii.hSubMenu != IntPtr.Zero)
                            this.Children[tt] = new SubMenu(this, tt, ii, Owner);
                        else
                            this.Children[tt] = new MenuItem(this, tt, ii);

                    }
                    else
                    {
                        tt = i.ToString();
                        this.Children[tt] = new MenuItem(this, tt, ii);
                    }
                    this.Children[tt].Position = i;
                }
            }
        }
        public SubMenu(SubMenu Parent, string MenuText, MENUITEMINFO ItemInfo, NativeMenu Owner) : base(Parent, MenuText, ItemInfo)
        {
            this.Owner = Owner;
            RefillChildrenList();
        }

        public SubMenu GetSubMenu(string MenuText)
        {
            var item = GetItem(MenuText);
            return (SubMenu)( item ?? null);
        }

        public bool Append(MenuItem NewItem)
        {

            var res = false;
            res = (NativeMethods.AppendMenu(this, NewItem.Flags, NewItem.ItemId, NewItem.MenuText));
            if (res)
            {
                Handlers[NewItem.ItemId] = NewItem.Handler;
                if (NewItem.BitMap != null)
                {
                    int position = NativeMethods.GetMenuItemCount(this);
                    res = NativeMethods.SetMenuItemBitmaps(this, position - 1, MenuFlags.MF_BYPOSITION, NewItem.hBitMap, NewItem.hBitMap);
                   // //Debug.Print("{0}, {1}", Marshal.GetLastWin32Error(), res);
                }

                RefillChildrenList();
                return true;
            }
            else
                return false;
        }

        private IntPtr m_hSubMenu;
        private void CreateHandle()
        {
            m_hSubMenu = NativeMethods.CreatePopupMenu();

            this.ItemInfo.Dispose();

            this.ItemInfo = new MENUITEMINFO
            {
                fType = MenuItemInfofType.MFT_STRING,
                fState = MenuItemInfofState.MFS_ENABLED,
                wID = m_hSubMenu.ToInt32(),
                hSubMenu = m_hSubMenu,
                dwItemData = IntPtr.Zero,
                dwTypeData = Marshal.StringToHGlobalAnsi(MenuText),
                cch = MenuText.Length,
                hbmpItem = IntPtr.Zero
            };
        }

        public SubMenu(string MenuText, MenuFlags Flags, NativeMenu Owner)
        {
            this.Owner = Owner;
            this.Flags = Flags;
            this.MenuText = MenuText;
            CreateHandle();
        }

        public bool InsertMenu(SubMenu Child, int Position)
        {
            Child.Flags |= MenuFlags.MF_BYPOSITION;

            if (NativeMethods.InsertMenu(this, Position, Child.Flags, Child, Child.MenuText))
            {
                foreach (var item in Child.Handlers)
                    Owner.CommandMap[item.Key] = item.Value;
                RefillChildrenList();
                return true;
            }
            else
                return false;
        }
        
        public bool Remove(MenuItem ItemToRemove)
        {
            if(NativeMethods.RemoveMenu(this, ItemToRemove.Position, MenuFlags.MF_BYPOSITION))
            {
                RefillChildrenList();
                Handlers.Remove(ItemToRemove.ItemId);
                Owner.CommandMap.Remove(ItemToRemove.ItemId);
                return true;
            }
            return false;
        }

        public bool Remove(int Position)
        {
            //var Item = (SubMenu)this.Children.Values.Where(t => t.Position == Position && t.IsSubmenu).First<MenuItem>();

            //if (Item != null)
            //    foreach (var SubItem in Item.Children)
            //        Item.Remove(SubItem.Value);

            int ItemId = NativeMethods.GetMenuItemID(this, Position);
             // if(NativeMethods.GetSubMenu(this, Position) != null)
            if (NativeMethods.RemoveMenu(this, Position, MenuFlags.MF_BYPOSITION))
            {
                if (Owner.CommandMap.ContainsKey(ItemId))
                {
                    Owner.CommandMap.Remove(ItemId);
                }

                RefillChildrenList();
                return true;
            }
            return false;
        }

        public bool InsertBefore(SubMenu Child, string NameBefore)
        {
            if (this.Children.ContainsKey(NameBefore))
                return InsertMenu(Child, this.Children[NameBefore].Position);
                
            else
                return false;
        }


        public static implicit operator IntPtr(SubMenu self)
        {
            return self == null ? IntPtr.Zero : self.ItemInfo.hSubMenu;
        }


        public MenuItem GetItem(string ItemText)
        {
            return Children.Where(t => t.Value.MenuText == ItemText)?.FirstOrDefault().Value;
        }

        public void EnableItem(string ItemText)
        {
            var item = GetItem(ItemText);
            if(item != null)
                item.Enabled = true;
        }

        public void DisableItem(string ItemText)
        {
            var item = GetItem(ItemText);
            if (item != null)
                item.Enabled = false;  
        }

    }

    public class MenuItem : IDisposable
    {
        public string MenuText;
        public Bitmap BitMap = null;
        public bool Enabled
        {
            get
            {
                return ItemInfo.fState == MenuItemInfofState.MFS_ENABLED;
            }
            set
            {
                MenuFlags flags = MenuFlags.MF_BYPOSITION | (value ? MenuFlags.MF_ENABLED : MenuFlags.MF_GRAYED);
                NativeMethods.EnableMenuItem(Parent, Position, flags);
                NativeMethods.DrawMenuBar(Parent.Owner.handle);
            }
        }
        public Bitmap Picture;
        public int ItemId
        {
            get
            {
                return ItemInfo.wID;
            }
        }
        public int Position;
        public SubMenu Parent;
        public MenuFlags Flags;

        public MenuItemInfofType ItemType { get { return ItemInfo.fType; } }

        internal  MENUITEMINFO ItemInfo;
        public  MenuItem_Handler Handler;

        public bool IsSubmenu { get { return (uint)ItemInfo.hSubMenu == ItemInfo.wID; } }

        public MenuItem(SubMenu Parent, string MenuText, MENUITEMINFO ItemInfo)
        {
            this.Parent = Parent;
            this.MenuText = MenuText;
            this.ItemInfo = ItemInfo;
        }

        public MenuItem(string MenuText, MenuFlags Flags, int ItemId = 0,  MenuItem_Handler Handler = null)
        {
            this.MenuText = MenuText;
            this.Flags = Flags;
            if (ItemId == 0)
                ItemId = ("SFS" + MenuText).GetHashCode();
            this.ItemInfo = new MENUITEMINFO
            {
                wID = ItemId,
                dwTypeData = Marshal.StringToHGlobalAnsi(MenuText),
                dwItemData = new IntPtr(ItemId),
                cch = MenuText.Length + 1,
                fState = MenuItemInfofState.MFS_ENABLED,
                fType = MenuItemInfofType.MFT_STRING
            };
            this.Handler = Handler;
        }

        [DllImport("user32.dll")]
        static extern int GetSystemMetrics(int smIndex);

        public MenuItem(string MenuText, Bitmap BitMap, MenuFlags Flags, int ItemId = 0, MenuItem_Handler Handler = null)
        {
            this.MenuText = MenuText;
            int MenuPictureWidth = GetSystemMetrics(71);
            this.BitMap = new Bitmap(BitMap, new Size(MenuPictureWidth, MenuPictureWidth));

            this.Flags = Flags;
            if (ItemId == 0)
                ItemId = ("SFS" + MenuText).GetHashCode();
            this.ItemInfo = new MENUITEMINFO
            {
                wID = ItemId,
                dwTypeData = Marshal.StringToHGlobalAnsi(MenuText),
                dwItemData = new IntPtr(ItemId),
                cch = MenuText.Length + 1,
                fState = MenuItemInfofState.MFS_CHECKED,
                fType = MenuItemInfofType.MFT_STRING,
                hbmpChecked = this.BitMap.GetHbitmap()
            };
            this.Handler = Handler;
        }

        public IntPtr hBitMap { get { return ItemInfo.hbmpChecked; } }
 

        public MenuItem()
        {

        }

        public void Dispose()
        {
            this.ItemInfo.Dispose();
        }

        ~MenuItem()
        {
            Dispose();
        }
    }

    [ClassInterface(ClassInterfaceType.None)]
    public class MenuTree : Dictionary<string, MenuItem>
    {
        public Dictionary<int, string> Commands
        {
            get
            {
                Dictionary<int, string> Commands = new Dictionary<int, string>();

                foreach (string MenuText in this.Keys)
                {
                    if (this[MenuText].ItemType == MenuItemInfofType.MFT_SEPARATOR)
                        continue;

                    if (this[MenuText].IsSubmenu)
                    {
                        Commands.Add(((IntPtr)((SubMenu)this[MenuText])).ToInt32(), "// Меню " + MenuText);
                        foreach (var it in ((SubMenu)this[MenuText]).Children.Commands)
                            Commands.Add(it.Key, it.Value);
                    }
                    else
                        Commands.Add(this[MenuText].ItemId, MenuText);
                }

                return Commands;
            }
        }
    }


    public delegate IntPtr wndProc(IntPtr hWnd, uint uMsg, IntPtr wParam, IntPtr lParam, IntPtr uIdSubclass, IntPtr dwRefData);

  
    public int HighWord(int number)
    { return (short)(number >> 16); }

    public int LowWord(int number)
    { return (int)(number & 0x00FFFFFF); }


    [DllImport("user32.dll")]
    static extern IntPtr WindowFromPoint(System.Drawing.Point p);

    [DllImport("user32.dll")]
    static extern uint RealGetWindowClass(IntPtr hwnd, IntPtr pszType,  uint cchType);

    [DllImport("user32.dll")]
    static extern uint GetWindowClass(IntPtr hwnd, out StringBuilder pszType, uint cchType);

    [DllImport("user32.dll", SetLastError = true)]
    [return: MarshalAs(UnmanagedType.Bool)]
    static extern bool GetCursorPos(out System.Drawing.Point lpPoint);

    [DllImport("user32.dll", SetLastError = true)]
    static extern int GetWindowText(IntPtr hWnd, IntPtr lpString, int nMaxCount);

    [DllImport("user32.dll", SetLastError = true)]
    static extern int GetClassName(IntPtr hWnd, IntPtr lpString, int nMaxCount);

    [DllImport("user32.dll", SetLastError = true)]
    static extern int GetWindowTextLength(IntPtr hWnd);

    [DllImport("user32.dll")]
    private static extern IntPtr SetParent(IntPtr hWndChild, IntPtr hWndNewParent);


    public  delegate IntPtr WndProc(IntPtr hWnd, uint msg, IntPtr wParam, IntPtr lParam);

    [SecurityCritical]
    [HandleProcessCorruptedStateExceptions]
    public IntPtr MenuProc(IntPtr hWnd, uint uMsg, IntPtr wParam, IntPtr lParam, IntPtr uIdSubclass, IntPtr dwRefData)
    {
        WindowsMessages message = (WindowsMessages)uMsg;
        bool PassToDefault = true;
        if (Window.WindowMessageMap.ContainsKey(message))
        {
            if (!Window.WindowMessageMap[message].Invoke(Window, message, wParam, lParam))
                return IntPtr.Zero;
        }

        //Debug.Print(message.ToString());

        switch (uMsg)
        {
            case (uint)WindowsMessages.WM_COMMAND:
                {
                    //Debug.Print("{0} ({5}) [{1:X8}]: {2} wParam ={3:X8}, lParam= {4:X8}", Window.ClassName, hWnd, message, wParam, lParam, Window.Caption);
                    int CommandId = wParam.ToInt32();
                    PassToDefault = CommandMap.ContainsKey(CommandId) ? (CommandMap[CommandId] != null ? CommandMap[CommandId].Invoke(CommandId) : true) : true;

                    if (PassToDefault && onMenuClick != null)
                        PassToDefault = onMenuClick.Invoke(CommandId);
                    if (!PassToDefault)
                        return IntPtr.Zero;
                    break;
                }
            case (uint)WindowsMessages.WM_INITMENUPOPUP:
                {
                    //Debug.Print("{0} ({5}) [{1:X8}]: {2} wParam ={3:X8}, lParam= {4:X8}", Window.ClassName, hWnd, message, wParam, lParam, Window.Caption);
                    if (PopUpMenuTracker != null && lParam == IntPtr.Zero)
                    {
                        SubMenu PopUp = new SubMenu(null, "Main", new MENUITEMINFO { hSubMenu = wParam }, this);
                        PopUpMenuTracker.Invoke(PopUp);
                    }
                    break;
                }
            case (uint)WindowsMessages.WM_NCCALCSIZE:
                {

                    InitMenu(hWnd);
                    break;
                }
        }

        if (PassToDefault)
            try
            {
                return NativeMethods.DefSubclassProc(hWnd, uMsg, wParam, lParam);
            }
            catch (Exception ex)
            {
                Debug.Print(ex.Message);
                return IntPtr.Zero;
            }
        return IntPtr.Zero;
    }

   
    #region Enums

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

    [Flags]
    public enum MenuItemInfofMask : uint
    {

        MIIM_BITMAP = 0x00000080, //Retrieves or sets the hbmpItem member.
        MIIM_CHECKMARKS = 0x00000008, //Retrieves or sets the hbmpChecked and hbmpUnchecked members.
        MIIM_DATA = 0x00000020, //Retrieves or sets the dwItemData member.
        MIIM_FTYPE = 0x00000100, // Retrieves or sets the fType member.
        MIIM_ID = 0x00000002, // Retrieves or sets the wID member.
        MIIM_STATE = 0x00000001, // Retrieves or sets the fState member.
        MIIM_STRING = 0x00000040, // Retrieves or sets the dwTypeData member.
        MIIM_SUBMENU = 0x00000004, //Retrieves or sets the hSubMenu member.
        MIIM_TYPE = 0x00000010 // Retrieves or sets the fType and dwTypeData members. MIIM_TYPE is replaced by MIIM_BITMAP, MIIM_FTYPE, and MIIM_STRING.

    }

    [Flags]
    public enum MenuItemInfofType : uint
    {
        MFT_BITMAP = 0x00000004,
        MFT_MENUBARBREAK = 0x00000020,
        MFT_MENUBREAK = 0x00000040,
        MFT_OWNERDRAW = 0x00000100,
        MFT_RADIOCHECK = 0x00000200,
        MFT_RIGHTJUSTIFY = 0x00004000,
        MFT_RIGHTORDER = 0x00002000,
        MFT_SEPARATOR = 0x00000800,
        MFT_STRING = 0x00000000
    }

    [Flags]
    public enum MenuItemInfofState : uint
    {
        MFS_CHECKED = 0x00000008,//Checks the menu item. For more information about selected menu items, see the hbmpChecked member.
        MFS_DEFAULT = 0x00001000,//Specifies that the menu item is the default. A menu can contain only one default menu item, which is displayed in bold.
        MFS_DISABLED = 0x00000003,//Disables the menu item and grays it so that it cannot be selected. This is equivalent to MFS_GRAYED.
        MFS_ENABLED = 0x00000000,//Enables the menu item so that it can be selected. This is the default state.
        MFS_HILITE = 0x00000080,//Highlights the menu item.
        MFS_UNCHECKED = 0x00000000,//Unchecks the menu item. For more information about clear menu items, see the hbmpChecked member.
        MFS_UNHILITE = 0x00000000 //Removes the highlight from the menu item. This is the default state.
    }


    [Flags]
    public enum MenuFlags : uint
    {
        MF_BITMAP = 0x00000004,
        MF_BYCOMMAND = 0x00000000,
        MF_BYPOSITION = 0x00000400,
        MF_SEPARATOR = 0x00000800,
        MF_ENABLED = 0x00000000,
        MF_GRAYED = 0x00000001,
        MF_UNCHECKED = 0x00000000,
        MF_CHECKED = 0x00000008,
        MF_STRING = 0x00000000,
        MF_OWNERDRAW = 0x00000100,
        MF_POPUP = 0x00000010,
    }
    #endregion

    public NativeMenu(IntPtr handle, WindowWrapper Window, UpdateMenu MenuConstructor = null)
    {
        this.handle = handle;
        this.Window = Window;
        this.MenuConstrucor = MenuConstructor;
        eventHandler = new wndProc(MenuProc).Invoke;
        WndProcHandler = GCHandle.Alloc(eventHandler);
        Subclassed = NativeMethods.SetWindowSubclass(handle, (wndProc)WndProcHandler.Target, WndProcId, IntPtr.Zero);
        InitMenu(handle);

        //IntPtr buffer = Marshal.AllocHGlobal(200);
        //GetWindowText(handle, buffer, 200);
        //Window.Caption = Marshal.PtrToStringAnsi(buffer);
        //var ctl = new Win32Window(handle);
    }

    public void InitMenu(IntPtr handle)
    {
        IntPtr hMenu = NativeMethods.GetMenu(handle);
        if (hMenu != MainMenu)
        {
            if(MainMenu != null)
                if (MenuCache.ContainsKey(MainMenu))
                {
                    MainMenu.Remove(MenuCache[MainMenu]);
                    MenuCache.Remove(MainMenu);
                }

            MainMenu = new SubMenu(null, "Main", new MENUITEMINFO { hSubMenu = hMenu }, this);

            MenuTree NewMenu = MainMenu.Children;
            onMenuChange?.Invoke(hMenu, NewMenu);

            if (MenuConstrucor != null)
            {
                string ItemAfter = null;
                SubMenu New = MenuConstrucor.Invoke(MainMenu, out ItemAfter);

                if (MainMenu.InsertBefore(New, ItemAfter))
                    MenuCache[MainMenu] = MainMenu.Children[New.MenuText].Position;

                NativeMethods.DrawMenuBar(hMenu);
                
            }
        }
    }

    //public void GetChildWindows()// Returns a list of child windows
    //{
    //    List<IntPtr> result = new List<IntPtr>();
    //    GCHandle listHandle = GCHandle.Alloc(result);
    //    try
    //    {
    //        EnumWindowProc childProc = new EnumWindowProc(EnumWindow);
    //        NativeMethods.EnumChildWindows(handle, childProc, GCHandle.ToIntPtr(listHandle));   //непонятно,почему метод  EnumWindow вызывается 2 раза?  
    //    }
    //    finally
    //    {
    //        if (listHandle.IsAllocated)
    //            listHandle.Free();
    //    }

    //    foreach(var Child in result)
    //    {
    //        //Controls[Child] = new WindowWrapper(Child, false);
    //    }
    //    //return result;
    //}

    //public static bool EnumWindow(IntPtr handle, IntPtr pointer)// Callback method to be used when enumerating windows.
    //{
    //    GCHandle gch = GCHandle.FromIntPtr(pointer);
    //    List<IntPtr> list = gch.Target as List<IntPtr>;
    //    if (list == null)
    //    {
    //        throw new InvalidCastException("GCHandle Target could not be cast as List<IntPtr>");
    //    }
    //    list.Add(handle);
    //    return true;
    //}

    public delegate bool EnumWindowProc(IntPtr hWnd, IntPtr parameter);// Delegate for the EnumChildWindows method

    public void Dispose()
    {

        if (Subclassed)
        {
            NativeMethods.RemoveWindowSubclass(handle, eventHandler, WndProcId);
        }

        foreach (SubMenu Menu in MenuCache.Keys)
        {
            Menu.Remove(MenuCache[Menu]);
        }
        
        if (WndProcHandler.IsAllocated)
            WndProcHandler.Free();

        handle = IntPtr.Zero;

    }




}