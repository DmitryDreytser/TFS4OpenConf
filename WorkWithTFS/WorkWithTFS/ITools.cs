using Microsoft.TeamFoundation.Client;
using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
using OpenConf;

namespace WorkWithTFS
{

    [ComImport]
    [Guid("B196B283-BAB4-101A-B69C-00AA00341D07")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IProvideClassInfo
    {
        [PreserveSig]
        int GetClassInfo(out IntPtr typeInfo);
    }

    [Guid("1C034F6A-1332-4DB8-B009-B73873D8C297")]
    [InterfaceType(ComInterfaceType.InterfaceIsDual)]
    public interface ITools  : IDisposable, IConfigPlugin //, IProvideClassInfo//, IDispatch
    {
        string CompileConfiguration(string ConfigurationFilePath, string SourcePath);

        string DeCompileConfiguration(string ConfigurationFilePath, string SourcePath);

        string CompileConfiguration(string ConfigurationFilePath, string SourcePath, string PassWord);
        void GetLastVersionOfConfiguration();
        string GetLastVersionOfExternalReport(string ObjectName);
        string GetObjectFromTFS(string ObjectName);
        string GetWorkFolder(string WorkSpaceName = "", string Owner = "");
        bool InitConnectionToTFS(string pProjectServerName);
        string MapObject(string ObjectName, string DestObject = "");
        string SelectExternalReportFromTFS(string SourceFolder = "");
        string SelectFolderInTFS(string SourceFolder = "");
        string SendReportToTFS(string ExternalReportFile, string SelectedFolderTFS);
    }
}