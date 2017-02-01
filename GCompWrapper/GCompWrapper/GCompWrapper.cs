using System;
using System.Runtime.InteropServices;

namespace GComp
{
    [Guid("1C034F6A-1332-4DB8-2049-873373D8C293")]
    [ComVisible(true)]
    public static class GCompWrapper
    {
        /// <summary>
        /// Возможные варианты Compound-Файлов
        /// </summary>
        public enum CompoundTypes
        {
            /// <summary>
            /// Определить по расширению. Нельзя использовать при работе с методами DLL
            /// </summary>
            by_extension = 0, //Do not use this when call DLL functions
            /// <summary>
            /// Внешний отчет
            /// </summary>
            external_report = 1,
            /// <summary>
            /// Конфигурация
            /// </summary>
            meta_data = 2
        };

        /// <summary>
        /// Варианты языков сообщения
        /// </summary>
        public enum Languages
        {
            Rus = 0,
            Eng = 1,
            Translit = 2
        };

        /// <summary>
        /// Способ вывода лога
        /// </summary>
        public enum LogType
        {
            /// <summary>
            /// В Консоль
            /// </summary>
            STDout = 0,
            /// <summary>
            /// В файл
            /// </summary>
            File = 1,
            /// <summary>
            /// В ListBox на форме. В этом случае нужно указать его хэндл в поле hwndLog
            /// </summary>
            ListBox = 2
        };


        /// <summary>
        /// Уровень детализации сообщений
        /// </summary>
        public enum Verbose
        {
            /// <summary>
            /// Не выводить ничего
            /// </summary>
            supress_all_messagess = -1,
            /// <summary>
            /// Только ошибки
            /// </summary>
            errors_only = 0,
            /// <summary>
            /// Только информацию о реальных записях
            /// </summary>
            real_deeds = 1,
            /// <summary>
            /// Все информационные сообщения
            /// </summary>
            all_together = 2
        }


        /// <summary>
        /// Слцужебный тип для совместимости с C++
        /// </summary>
        public enum BOOL
        {
            False = 0,
            True = 1
        };



        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public struct CGCompParameters
        {
            /// <summary>
            /// Имя файла для сборки/разборки
            /// </summary>
            [MarshalAs(UnmanagedType.LPStr)]
            public string CompoundFileName;

            /// <summary>
            /// Каталог для сборки/разборки
            /// </summary>
            [MarshalAs(UnmanagedType.LPStr)]
            public string DirectoryName;

            /// <summary>
            /// Тип файла для сборки/разборки. При вызове из Dll указывать обязательно!
            /// </summary>
            [MarshalAs(UnmanagedType.I4)]
            public CompoundTypes CompoundType;

            /// <summary>
            /// Язык сообщений. Сообщения об ошибках всегда на английском
            /// </summary>
            [MarshalAs(UnmanagedType.I4)]
            public Languages Language;

            /// <summary>
            /// Уровень детализации сообщений
            /// </summary>
            [MarshalAs(UnmanagedType.I4)]
            public Verbose Messaging;

            /// <summary>
            /// Куда выводить лог
            /// </summary>
            [MarshalAs(UnmanagedType.I4)]
            public LogType LogType;

            /// <summary>
            /// Хэндл контрола (Select) для вывода сообщений
            /// </summary>
            public IntPtr hwndLog;


            /// <summary>
            /// Не сохранять порядок объектов в конфигурации. Опция работает только при декомпиляции. 
            /// При компиляции объекты будут располагаться в том порядке, как операционная система выдаст каталоги.
            /// </summary>
            [MarshalAs(UnmanagedType.I4)]
            public BOOL NoOrdering;

            /// <summary>
            /// Пропустить при работе файлы (потоки), с именем Container.Profile
            /// </summary>
            [MarshalAs(UnmanagedType.I4)]
            public BOOL NoProfiles;

            /// <summary>
            /// Не вытаскивать пустые MXL.
            /// </summary>
            [MarshalAs(UnmanagedType.I4)]
            public BOOL NoEmptyMxl;

            /// <summary>
            /// При сборке внешних отчетов заменит поток 'Main MetaData Stream' на пустой
            /// </summary>
            [MarshalAs(UnmanagedType.I4)]
            public BOOL TruncateMMS;

            /// <summary>
            /// Диалоговые формы будут выгружены As Is, без какой либо обработки. При компиляции формат диалогов определяется автоматически.
            /// </summary>
            [MarshalAs(UnmanagedType.I4)]
            public BOOL NotParseForms;

            /// <summary>
            /// Выводятся все параметры выгружаемых объектов. Без этой опции выводится только та информация, которая отличается от значений по умолчанию. Опция действует только при декомпиляции.
            /// </summary>
            [MarshalAs(UnmanagedType.I4)]
            public BOOL NoDefaults; //don't use default values when extracting objects in beauty strings

            /// <summary>
            /// При декомпиляции будет сформирован файл gcomp.ver с информацией о версии gcomp.
            /// </summary>
            [MarshalAs(UnmanagedType.I4)]
            public BOOL SaveVersion;

            /// <summary>
            /// При декомпиляции будут удалены пустые папки (для SVN репозиториев).
            /// </summary>
            [MarshalAs(UnmanagedType.I4)]
            public BOOL NoEmptyFolders;

            /// <summary>
            /// объекты, которые по умолчанию выгружаются в виде одного mdp-файла, будут разобраны по каталогам. Это: константы, перечисления, общие поля документов, нумераторы, графы отбора документов, последовательности документов, регистры, группы расчетов, правила перерасчета, календари
            /// </summary>
            [MarshalAs(UnmanagedType.I4)]
            public BOOL MetadataBySubfolders;

            /// <summary>
            ///Если не NULL, то это фильтр объекта для выгрузки/загрузки. 
            ///Например:
            ///   Справочник\*\МодульФормы
            /// </summary>
            [MarshalAs(UnmanagedType.LPStr)]
            public string MetadataPath;

            /// <summary>
            /// Параметр больше не используется. Оставлен для совместимости
            /// </summary>
            [MarshalAs(UnmanagedType.I4)]
            public BOOL SaveWholeMMS;

            /// <summary>
            /// Объекты приложения пользовательских прав будут отсортированы по типу объекта (Константа, Справочник, Документ и т.д.) и по идентификатору объекта.
            /// </summary>
            [MarshalAs(UnmanagedType.I4)]
            public BOOL SortUserRightsObjects;

            /// <summary>
            /// Сортировать элементы диалоговых форм по идентификатору. Элементы без идентификаторов сортируются по порядку обхода.
            /// </summary>
            [MarshalAs(UnmanagedType.I4)]
            public BOOL SortFormControls;

            //progress reporter parameters
            /// <summary>
            /// Хэндл окна для получения прогресса
            /// </summary>
            public volatile IntPtr hwndInfoReceiver;

            /// <summary>
            /// Параметры WinMsg сообщения прогресса
            /// </summary>
            [MarshalAs(UnmanagedType.U4)]
            public uint InfoMessage;

            /// <summary>
            /// Если внешний процесс установит эту переменную в TRUE, то в момент отправки информационного сообщения работа gcomp.dll будет прервана
            /// </summary>
            [MarshalAs(UnmanagedType.I4)]
            public volatile BOOL CancelWork;

            /// <summary>
            /// Не выгружать объекты прав и интерфейсов, ссылающиеся на отсутствующие метаданные
            /// </summary>
            [MarshalAs(UnmanagedType.I4)]
            public BOOL NoBrokenLinks; // не выгружать объекты прав и интерфейсов, ссылающиеся на отсутствующие метаданные

            /// <summary>
            /// Сохранить все наборы прав в одном csv файле (при компиляции игнорируется)
            /// </summary>
            [MarshalAs(UnmanagedType.I4)]
            public BOOL MakeUserRightsInOneFile; // Создавать единый csv файл со всеми правами сразу (при компиляции игнорируется)

            /// <summary>
            /// При разборке преобразует конец строки в формат UNIX, при сборке преобразует обратно в формат Windows
            /// </summary>
            [MarshalAs(UnmanagedType.I4)]
            public BOOL UnixEOL; // Make dos2unix eol convertation on decompile and unix2dos - on compile
        };


        class NativeCode
        {
            [DllImport(dllName: "GComp.dll", CharSet = CharSet.Unicode)]
            public static extern IntPtr GComp_GetVersion();
            [DllImport(dllName: "GComp.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
            public static extern void GComp_SetDefaults(ref CGCompParameters Parameters);

            [DllImport(dllName: "GComp.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
            public static extern void GComp_ReadSettings(ref CGCompParameters Parameters);

            [DllImport(dllName: "GComp.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
            public static extern void GComp_SaveSettings(ref CGCompParameters Parameters);

            [DllImport(dllName: "GComp.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
            public static extern int GComp_Decompile(ref CGCompParameters Parameters);

            [DllImport(dllName: "GComp.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
            public static extern int GComp_Compile(ref CGCompParameters Parameters);

            [DllImport(dllName: "GComp.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
            public static extern int GComp_ParseMainMetadataStream([MarshalAs(UnmanagedType.LPStr)] string fname, IntPtr hLogWnd);

            [DllImport(dllName: "GComp.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
            public static extern int GComp_DecompileDialogForm([MarshalAs(UnmanagedType.LPStr)] string dest_fname, [MarshalAs(UnmanagedType.LPStr)] string src_fname, int nObjectID);

            [DllImport(dllName: "GComp.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
            public static extern int GComp_ReadObjectNameCache([MarshalAs(UnmanagedType.LPStr)] string fname, IntPtr hLogWnd);

            [DllImport(dllName: "GComp.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
            public static extern int GComp_CompileDialogForm([MarshalAs(UnmanagedType.LPStr)] string dest_fname, [MarshalAs(UnmanagedType.LPStr)] string src_fname);

            [DllImport(dllName: "GComp.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
            public static extern int GComp_AssembleMainMetadataStream([MarshalAs(UnmanagedType.LPStr)] string szDir, [MarshalAs(UnmanagedType.LPStr)] string szDestFileName);

            [DllImport(dllName: "GComp.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
            public static extern int GComp_MakeNamePath(
                [MarshalAs(UnmanagedType.LPTStr)] string srcDir,
                [MarshalAs(UnmanagedType.I4)] int translite,
                [MarshalAs(UnmanagedType.LPStr)] string objName,
                [MarshalAs(UnmanagedType.SysInt)] int buffsize
                );

        }

        //Wrapper
        public static string GetVersion()
        {
            return Marshal.PtrToStringAnsi(NativeCode.GComp_GetVersion()); 
        }

        public static CGCompParameters SetDefaults()
        {
            CGCompParameters Params = new CGCompParameters(); 
            NativeCode.GComp_SetDefaults(ref Params);
            return Params;
        }

        public static  void ReadSettings(ref CGCompParameters Params)
        {
            NativeCode.GComp_ReadSettings(ref Params);
        }


        public static void SaveSettings(ref CGCompParameters Params)
        {
            try
            {
                NativeCode.GComp_SaveSettings(ref Params);
            }
            catch (Exception e)
            {

                throw e;
            }
            
        }

        public static bool Decompile(ref CGCompParameters Params)
        {
            return NativeCode.GComp_Decompile(ref Params) == 1;
        }

        public static bool Decompile(string ConfigurationFilePath, string DestinationPath )
        {
            CGCompParameters Params = SetDefaults();
            Params.CompoundFileName = ConfigurationFilePath;
            Params.DirectoryName = DestinationPath;
            return Decompile(ref Params);
        }

        public static bool Compile(ref CGCompParameters Params)
        {
            NativeCode.GComp_Compile(ref Params);
               return true;
        }

        public static bool Compile(string ConfigurationFilePath, string DestinationPath)
        {
            CGCompParameters Params = SetDefaults();
            Params.CompoundFileName = ConfigurationFilePath;
            Params.DirectoryName = DestinationPath;
            return Compile(ref Params);
        }
    }
}
