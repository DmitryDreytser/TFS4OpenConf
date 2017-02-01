using System.Runtime.InteropServices;

namespace WorkWithTFS
{
    [Guid("1C034F6A-1332-4DB8-2049-873373D8C293")]
    [InterfaceType(ComInterfaceType.InterfaceIsDual)]
    public interface IGCompTools
    {
        void CompileConfiguration(string ConfigurationFilePath, string SourcePath);
        void CompileExternalReport(string ExternalReportPath, string DestReport);
        void DecompileConfiguration(string ConfigurationFilePath, string DestinationPath);
        void DecompileExternalReport(string ExternalReportFile, string DestReportPath);
        int Init();
    }
}