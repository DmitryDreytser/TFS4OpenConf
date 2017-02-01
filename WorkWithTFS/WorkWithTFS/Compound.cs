using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.ComTypes;
using System.Security.Cryptography;
using System.Drawing;
using System.Drawing.Imaging;
using System.Text;
using System.Linq;

namespace WorkWithTFS
{
    class DIBitMap
    {

        public enum BitmapCompressionMode : uint
        {
            BI_RGB = 0,
            BI_RLE8 = 1,
            BI_RLE4 = 2,
            BI_BITFIELDS = 3,
            BI_JPEG = 4,
            BI_PNG = 5
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct BITMAPFILEHEADER
        {
            public ushort bfType;
            public uint bfSize;
            public uint bfReserved;
            public uint bfOffBits;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct BITMAPINFOHEADER
        {
            public uint biSize;
            public int biWidth;
            public int biHeight;
            public ushort biPlanes;
            public ushort biBitCount;
            public BitmapCompressionMode biCompression;
            public uint biSizeImage;
            public int biXPelsPerMeter;
            public int biYPelsPerMeter;
            public uint biClrUsed;
            public uint biClrImportant;

            public void Init()
            {
                biSize = (uint)Marshal.SizeOf(this);
            }
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct RGBTriplet
        {
            public byte red;
            public byte green;
            public byte blue;
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct RGBQUAD
        {
            public byte rgbBlue;
            public byte rgbGreen;
            public byte rgbRed;
            public byte rgbReserved;
        }

        [StructLayoutAttribute(LayoutKind.Sequential, Size = 14 + 40 + 256 * 4)] //DIBitmapHeader v3
        public struct DIBINFO
        {
            /// <summary>
            /// A BITMAPINFOHEADER structure that contains information about the dimensions of color format.
            /// </summary>
            public BITMAPINFOHEADER bmiHeader;

            /// <summary>
            /// An array of RGBQUAD. The elements of the array that make up the color table.
            /// </summary>
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 1, ArraySubType = UnmanagedType.Struct)]
            public RGBQUAD[] bmiColors;
        }

        public byte[] pixels = null;
    }

    
    public class Compound
    {
        static class NativeMethods
        {
            [ComImport]
            [Guid("0000000d-0000-0000-C000-000000000046")]
            [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
            public interface IEnumSTATSTG
            {
                // The user needs to allocate an STATSTG array whose size is celt.
                [PreserveSig]
                uint Next(
                    uint celt,
                    [MarshalAs(UnmanagedType.LPArray), Out]
                    System.Runtime.InteropServices.ComTypes.STATSTG[] rgelt,
                    out uint pceltFetched
                );
                void Skip(uint celt);
                void Reset();
                [return: MarshalAs(UnmanagedType.Interface)]
                IEnumSTATSTG Clone();
            }

            [ComImport]
            [Guid("0000000b-0000-0000-C000-000000000046")]
            [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
            public interface IStorage
            {
                void CreateStream(
                    /* [string][in]*/  string pwcsName,
                    /* [in]*/  STGM grfMode,
                    /* [in]*/  uint reserved1,
                    /* [in] */ uint reserved2,
                    /* [out] */ out IStream ppstm);

                void OpenStream(
                    /* [string][in] */ string pwcsName,
                    /* [unique][in] */ IntPtr reserved1,
                    /* [in] */ STGM grfMode,
                    /* [in] */ uint reserved2,
                    /* [out] */ out IStream ppstm);

                void CreateStorage(
                    /* [string][in] */ string pwcsName,
                    /* [in] */ STGM grfMode,
                    /* [in] */ uint reserved1,
                    /* [in] */ uint reserved2,
                    /* [out] */ out IStorage ppstg);

                  void OpenStorage(
                    /* [string][unique][in] */ string pwcsName,
                    /* [unique][in] */ IStorage pstgPriority,
                    /* [in] */ STGM grfMode,
                    /* [unique][in] */ IntPtr snbExclude,
                    /* [in] */ uint reserved,
                    /* [out] */ out IStorage ppstg);

                 void CopyTo(
                    /* [in] */ uint ciidExclude,
                    /* [size_is][unique][in] */ ref Guid rgiidExclude, // should this be an array?
                    /* [unique][in] */ IntPtr snbExclude,
                    /* [unique][in] */ IStorage pstgDest);

                 void MoveElementTo(
                    /* [string][in] */ string pwcsName,
                    /* [unique][in] */ IStorage pstgDest,
                    /* [string][in] */ string pwcsNewName,
                    /* [in] */ uint grfFlags);

                 void Commit(
                    /* [in] */ STGC grfCommitFlags);

                 void Revert();

                 void EnumElements(
                    /* [in] */ uint reserved1,
                    /* [size_is][unique][in] */ IntPtr reserved2,
                    /* [in] */ uint reserved3,
                    /* [out] */out IEnumSTATSTG ppenum);

                 void DestroyElement(
                    /* [string][in] */ string pwcsName);

                 void RenameElement(
                    /* [string][in] */ string pwcsOldName,
                    /* [string][in] */ string pwcsNewName);

                 void SetElementTimes(
                    /* [string][unique][in] */ string pwcsName,
                    /* [unique][in] */ System.Runtime.InteropServices.ComTypes.FILETIME pctime,
                    /* [unique][in] */ System.Runtime.InteropServices.ComTypes.FILETIME patime,
                    /* [unique][in] */ System.Runtime.InteropServices.ComTypes.FILETIME pmtime);

                 void SetClass(
                    /* [in] */ ref Guid clsid);

                 void SetStateBits(
                    /* [in] */ uint grfStateBits,
                    /* [in] */ uint grfMask);

                 void Stat(
                    /* [out] */ out System.Runtime.InteropServices.ComTypes.STATSTG pstatstg,
                    /* [in] */ uint grfStatFlag);

                //////////////////////////////////////////////////////////////////////////////////
                 

            }

            public class Storage 
            {
                private Dictionary<string, NativeMethods.IStorage> STGRefs = new Dictionary<string, NativeMethods.IStorage>();
                public NativeMethods.IStorage RootStorage;

                public Storage(IStorage RootStorage)
                {
                    this.RootStorage = RootStorage;
                    STGRefs["ROOT"] = this.RootStorage;
                }

                public NativeMethods.IStorage GetStorage(string Path)
                {
                    if (STGRefs.ContainsKey(Path.ToUpper()))
                        return STGRefs[Path.ToUpper()];
                    
                    NativeMethods.IStorage newStorage;
                    string[] chunks = Path.Split('\\');
                    string name = chunks.Last();
                    string parentPath = Path.Replace("\\" + name, "");

                    NativeMethods.IStorage parentStorage = GetStorage(parentPath);
                    parentStorage.OpenStorage(name, null, NativeMethods.STGM.READWRITE | NativeMethods.STGM.SHARE_EXCLUSIVE, IntPtr.Zero, 0, out newStorage);
                    STGRefs[Path.ToUpper()] = newStorage;
                    return newStorage;
                }

                ~Storage()
                {
                    foreach(IStorage item in STGRefs.Values)
                    {
                        Marshal.ReleaseComObject(item);
                        Marshal.FinalReleaseComObject(item);
                    }

                    STGRefs.Clear();
                }
            }

            [Flags]
            public enum STGC : int
            {
                DEFAULT = 0,
                OVERWRITE = 1,
                ONLYIFCURRENT = 2,
                DANGEROUSLYCOMMITMERELYTODISKCACHE = 4,
                CONSOLIDATE = 8
            }

            [Flags]
            public enum STGM : int
            {
                DIRECT = 0x00000000,
                TRANSACTED = 0x00010000,
                SIMPLE = 0x08000000,
                READ = 0x00000000,
                WRITE = 0x00000001,
                READWRITE = 0x00000002,
                SHARE_DENY_NONE = 0x00000040,
                SHARE_DENY_READ = 0x00000030,
                SHARE_DENY_WRITE = 0x00000020,
                SHARE_EXCLUSIVE = 0x00000010,
                PRIORITY = 0x00040000,
                DELETEONRELEASE = 0x04000000,
                NOSCRATCH = 0x00100000,
                CREATE = 0x00001000,
                CONVERT = 0x00020000,
                FAILIFTHERE = 0x00000000,
                NOSNAPSHOT = 0x00200000,
                DIRECT_SWMR = 0x00400000,
            }

            [Flags]
            public enum STATFLAG : uint
            {
                STATFLAG_DEFAULT = 0,
                STATFLAG_NONAME = 1,
                STATFLAG_NOOPEN = 2
            }

            [Flags]
            public enum STGTY : int
            {
                STGTY_STORAGE = 1,
                STGTY_STREAM = 2,
                STGTY_LOCKBYTES = 3,
                STGTY_PROPERTY = 4
            }

            //Читает IStream в массив байт
            public static byte[] ReadIStream(IStream pIStream)
            {
                System.Runtime.InteropServices.ComTypes.STATSTG StreamInfo;
                pIStream.Stat(out StreamInfo, 0);
                byte[] data = new byte[StreamInfo.cbSize];
                pIStream.Read(data, (int)StreamInfo.cbSize, IntPtr.Zero);
                Marshal.ReleaseComObject(pIStream);
                Marshal.FinalReleaseComObject(pIStream);
                pIStream = null;
                return data;
            }

            //Читает IStream в массив байт и разжимает
            public static byte[] ReadCompressedIStream(ref IStream pIStream)
            {
                System.Runtime.InteropServices.ComTypes.STATSTG StreamInfo;
                pIStream.Stat(out StreamInfo, 0);
                byte[] data = new byte[StreamInfo.cbSize];
                pIStream.Read(data, (int)StreamInfo.cbSize, IntPtr.Zero);
                
                Marshal.ReleaseComObject(pIStream);
                Marshal.FinalReleaseComObject(pIStream);
                pIStream = null;

                DeflateStream ZLibCompressed = new DeflateStream(new MemoryStream(data), CompressionMode.Decompress, false);
                MemoryStream Decompressed = new MemoryStream();
                ZLibCompressed.CopyTo(Decompressed);
                ZLibCompressed.Dispose();
                data = Decompressed.ToArray();
                Array.Resize(ref data, (int)Decompressed.Length);
                

                return data;
            }

            //Читает IStream в строку
            public static string ReadIStreamToString(ref IStream pIStream)
            {
                System.Runtime.InteropServices.ComTypes.STATSTG StreamInfo;
                pIStream.Stat(out StreamInfo, 0);
                byte[] data = new byte[StreamInfo.cbSize];
                pIStream.Read(data, (int)StreamInfo.cbSize, IntPtr.Zero);
                Marshal.ReleaseComObject(pIStream);
                Marshal.FinalReleaseComObject(pIStream);
                pIStream = null;

                return Encoding.GetEncoding(1251).GetString(data);
            }

            [ComVisible(false)]
            [ComConversionLossAttribute]
            [ComImport, InterfaceType(ComInterfaceType.InterfaceIsIUnknown)] 
            [Guid("0000000A-0000-0000-C000-000000000046")]
            public interface ILockBytes 
            {
                void ReadAt(long ulOffset, System.IntPtr pv, int cb, out UIntPtr pcbRead);
                void WriteAt(long ulOffset, System.IntPtr pv, int cb, out UIntPtr pcbWritten);
                void Flush();
                void SetSize(long cb);
                void LockRegion(long libOffset, long cb, int dwLockType);
                void UnlockRegion(long libOffset, long cb, int dwLockType);
                void Stat(out System.Runtime.InteropServices.ComTypes.STATSTG pstatstg, int grfStatFlag);
            }


            [DllImport("ole32.dll")]
            public static extern int StgIsStorageFile(
                [MarshalAs(UnmanagedType.LPWStr)] string pwcsName);

            [DllImport("ole32.dll")]
            public  static extern int StgOpenStorage(
                [MarshalAs(UnmanagedType.LPWStr)] string pwcsName,
                IStorage pstgPriority,
                STGM grfMode,
                IntPtr snbExclude,
                uint reserved,
                out IStorage ppstgOpen);

            [DllImport("ole32.dll")]
            public static extern int StgCreateDocfile(
                [MarshalAs(UnmanagedType.LPWStr)]string pwcsName,
                STGM grfMode,
                uint reserved,
                out IStorage ppstgOpen);

            [DllImport("ole32.dll")]
            [PreserveSig()]
            public static extern int StgOpenStorageOnILockBytes(ILockBytes plkbyt,
               IStorage pStgPriority, STGM grfMode, IntPtr snbEnclude, uint reserved,
               out IStorage ppstgOpen);

            [DllImport("ole32.dll")]
            public static extern int CreateILockBytesOnHGlobal(IntPtr hGlobal, [MarshalAs(UnmanagedType.Bool)] bool fDeleteOnRelease, out ILockBytes ppLkbyt);
        }

        static class Encryption
        {

            static readonly byte[] MMSKey = { 0x60, 0x46, 0xD2, 0x72, 0x64, 0x25, 0x03, 0x00, 0x09, 
                                              0x89, 0x00, 0xC0, 0xDD, 0x3B, 0xE6, 0x36 };

            static readonly byte[] GMKey =  { 0x34, 0x43, 0x33, 0x43, 0x30, 0x42, 0x46, 0x31, 0x31, 
                                                0x35, 0x46, 0x38, 0x42, 0x39, 0x35, 0x36, 0x36, 0x39, 
                                                0x46, 0x39, 0x46, 0x43, 0x34, 0x42, 0x36, 0x44, 0x33, 
                                                0x41, 0x39, 0x44, 0x36, 0x31, 0x34, 0x31 };

            static readonly byte[] GMHeader = {
                                                0x9E,0x23,0x80,0x48,0xDA,0x12,0x0F,0x11,0x01,0xD2,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x04,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x01,0x03,0x02,0x04,0x06,0x05,0x08,0x05,0x09,0x01,
                                                0x9F,0x23,0x80,0x48,0xDA,0x12,0x0F,0x11,0x01,0xD2};

            public enum Mode
            {
                MetaDataStream,
                TagStream,
                GlobalModule
            }

            public static byte[] Encode(byte[] data, Mode EncryptionMode)
            {
                bool MakeXOR = true;
                byte[] key = null;
                bool decrypt = true;

                switch (EncryptionMode)
                {
                    case Mode.GlobalModule:
                        key = GMKey;
                        MakeXOR = false;
                        decrypt = data[0] == 0x9E;
                        if (decrypt)
                        {
                            Array.Reverse(data);
                            Array.Resize(ref data, data.Length - 510);
                            Array.Reverse(data);
                        }
                        break;
                    case Mode.TagStream:
                    case Mode.MetaDataStream:
                        key = MMSKey;
                        MakeXOR = true;
                        decrypt = data[0] == 0x25 || data[0] == 0x78;
                        break;
                }

                byte[] s = new byte[256];
                int i, j, t;

                for (i = 0; i < 256; i++)
                    s[i] = (byte)i;

                j = 0;
                for (i = 0; i < 256; i++)
                {
                    j = (j + s[i] + key[i % key.Length]) % 256;
                    s[i] ^= s[j];
                    s[j] ^= s[i];
                    s[i] ^= s[j];
                }

                byte tt = s[0];
                i = j = 0;
                for (int x = 0; x < data.Length; x++)
                {
                    i = (i + 1) % 256;
                    j = (j + s[i]) % 256;

                    s[i] ^= s[j];
                    s[j] ^= s[i];
                    s[i] ^= s[j];

                    t = (s[i] + s[j]) % 256;
                    data[x] ^= s[t];

                    if (MakeXOR)
                    {
                        data[x] ^= tt;

                        if (decrypt)
                            tt ^= (byte)(data[x] ^ s[t]);
                        else
                            tt = data[x];
                    }
                }

                if (!decrypt && EncryptionMode == Mode.GlobalModule)
                {
                    byte[] newdata = new byte[data.Length + 510];
                    Array.Copy(GMHeader, newdata, GMHeader.Length);
                    Array.Copy(data,0, newdata, 510, data.Length);
                    data = newdata;
                }

                return data;
            }
        }

        public string MetaDataStream = null;
        public string GlobalModule = null;
        public string TagStream = null;
        public Bitmap AuthorLogo = null;
        public Bitmap AuthorSplash = null;
        public string AuthorName = string.Empty;
        public string AuthorFullName = string.Empty;
        public string FileName;
        public string PasswordHash = null;
        public string CRC = null;
        public bool IsEncrypted = false;
        private readonly Guid EncryptedClass = new Guid("0af60370-754e-11d2-9f21-008048da120f");

        //это ссылка на массив байт в памяти
        private IntPtr hGlobal;                     //при уничтожениии экземпляра нужно освободить память
        private NativeMethods.ILockBytes LockBytes;
        //Это ссылка на открытый компаунд
        private NativeMethods.IStorage RootStorage; //при уничтожениии экземпляра нужно освободить COM-объект
        private NativeMethods.Storage GlobalStorage;
        private readonly Encoding win1251 = Encoding.GetEncoding(1251);
        

        bool OpenStorage(string FileName)
        {
            //Читаем MD в массив байт
            byte[] buffer = File.ReadAllBytes(FileName);
            //Выделяем область в памяти для буфера
            hGlobal = Marshal.AllocHGlobal(buffer.Length);
            //Помещаем считанный файл в буфер.
            Marshal.Copy(buffer, 0, hGlobal, buffer.Length);
            buffer = null;
            NativeMethods.CreateILockBytesOnHGlobal(hGlobal, false, out LockBytes);
            //Открываем считанный файл из памяти
            //GC.Collect(GC.MaxGeneration);
            return NativeMethods.StgOpenStorageOnILockBytes(LockBytes, null, NativeMethods.STGM.READWRITE | NativeMethods.STGM.SHARE_EXCLUSIVE, IntPtr.Zero, 0, out RootStorage) == 0;
        }

        public string ConfigurationHash(string instr)
        {
            string strHash = BitConverter.ToString(new MD5CryptoServiceProvider().ComputeHash(Encoding.Default.GetBytes(instr))).Replace("-", "");
            return (int.Parse(strHash.Substring(0, 3), System.Globalization.NumberStyles.HexNumber).ToString("D") + strHash.Substring(3)).PadLeft(33, '0');
        }

        enum AuthorTags
        {
            _HASH_STRING_,
            _AUTOR_SHOR_STRING_,
            _AUTOR_LONG_STRING_,
            _AUTOR_LOGO_INDEX_,
            _AUTOR_SPLASH_INDEX_,
            _AUTOR_LOGO_PICTURE_POS
        }

        string GetTag(AuthorTags tag)
        {
            string TagName = tag.ToString();
            string tagstring = TagStream.Split(new string[] { "},{" }, StringSplitOptions.RemoveEmptyEntries).First(x => x.Contains(TagName));
            tagstring = tagstring.Split(new string[] { "\",\"" }, StringSplitOptions.RemoveEmptyEntries)[1].Replace("}", "");
            tagstring = tagstring.Substring(0, tagstring.Length - 1);
            return tagstring;
        }

        byte[] bitmapFromUU(string uudata)
        {
            byte[] logoUUData =  win1251.GetBytes(uudata.Replace("\"\"","\""));
            byte[] logoBinData = UU2bin(new MemoryStream(logoUUData));

            GCHandle handle = GCHandle.Alloc(logoBinData, GCHandleType.Pinned);
            DIBitMap.BITMAPINFOHEADER DIBHeader = Marshal.PtrToStructure<DIBitMap.BITMAPINFOHEADER>(handle.AddrOfPinnedObject());
            handle.Free();

            DIBitMap.BITMAPFILEHEADER fileHeader = new DIBitMap.BITMAPFILEHEADER();
            fileHeader.bfType = 19778;
            fileHeader.bfSize = (uint)logoBinData.Length + 14;
            fileHeader.bfOffBits = fileHeader.bfSize - DIBHeader.biSizeImage - 1;

            byte[] tempbuffer = new byte[fileHeader.bfSize];

            int rawsize = Marshal.SizeOf(fileHeader);
            IntPtr buffer = Marshal.AllocHGlobal(rawsize);
            Marshal.StructureToPtr(fileHeader, buffer, false);
            byte[] rawdata = new byte[rawsize];
            Marshal.Copy(buffer, rawdata, 0, rawsize);
            Marshal.FreeHGlobal(buffer);

            Array.Copy(rawdata, tempbuffer, rawdata.Length);
            Array.Copy(logoBinData, 0, tempbuffer, rawdata.Length, logoBinData.Length);

            return tempbuffer;
        }

        string UUFromBitmap(Bitmap bmp)
        {
            ImageConverter converter = new ImageConverter();

            byte[] buffer = (byte[])converter.ConvertTo(bmp, typeof(byte[]));
            byte[] tmp = new byte[buffer.Length - 14];

            Array.Copy(buffer, 14, tmp, 0, tmp.Length);

            return bin2UU(new MemoryStream(tmp));
        }

        public Compound(string MDFilename)
        {
            this.FileName = MDFilename;

            if (!OpenStorage(MDFilename))
                throw new Exception("Не удалось открыть конфигурацию.");
            GlobalStorage = new NativeMethods.Storage(RootStorage);

            System.Runtime.InteropServices.ComTypes.STATSTG MetaDataInfo;
            IStream pIStream;

            GlobalStorage.GetStorage("root\\Metadata").Stat(out MetaDataInfo, 0);
            IsEncrypted = MetaDataInfo.clsid.Equals(EncryptedClass);

            GlobalStorage.GetStorage("root\\Metadata").OpenStream("TagStream", IntPtr.Zero, NativeMethods.STGM.READWRITE | NativeMethods.STGM.SHARE_EXCLUSIVE, 0, out pIStream);
            TagStream = win1251.GetString(Encryption.Encode(NativeMethods.ReadIStream(pIStream), Encryption.Mode.TagStream));
            TagStream = TagStream.Substring(TagStream.IndexOf("{"));
            GlobalStorage.GetStorage("root\\Metadata").OpenStream("Main MetaData Stream", IntPtr.Zero, NativeMethods.STGM.READWRITE | NativeMethods.STGM.SHARE_EXCLUSIVE, 0, out pIStream);
            
            if (IsEncrypted)
                MetaDataStream = win1251.GetString(Encryption.Encode(NativeMethods.ReadIStream(pIStream), Encryption.Mode.MetaDataStream));
            else
                MetaDataStream = NativeMethods.ReadIStreamToString(ref pIStream);

            MetaDataStream = MetaDataStream.Substring(MetaDataStream.IndexOf('{'));
         
            PasswordHash = MetaDataStream.Split(new string[] { "\r\n" }, StringSplitOptions.RemoveEmptyEntries).First(x => x.StartsWith("{\"1\",")).Split(',')[4].Replace("\"","");
            
            if(MetaDataStream.Contains("CRC"))
                CRC = MetaDataStream.Split(new string[] { "\r\n" }, StringSplitOptions.RemoveEmptyEntries).First(x => x.StartsWith("{\"CRC\",")).Split(',')[1].Replace("\"","").Replace("}","");

            GlobalStorage.GetStorage("root\\TypedText\\ModuleText_Number1").OpenStream("MD Programm text", IntPtr.Zero, NativeMethods.STGM.READ | NativeMethods.STGM.SHARE_EXCLUSIVE, 0, out pIStream);
                
            if (IsEncrypted)
                GlobalModule = win1251.GetString(Encryption.Encode(NativeMethods.ReadCompressedIStream(ref pIStream), Encryption.Mode.GlobalModule));
            else
                GlobalModule = win1251.GetString(NativeMethods.ReadCompressedIStream(ref pIStream));

            //вытащим картинки и инфу об авторе
            AuthorName = GetTag(AuthorTags._AUTOR_SHOR_STRING_).Replace("\"\"", "\"");
            AuthorFullName = GetTag(AuthorTags._AUTOR_LONG_STRING_).Replace("\"\"", "\"");

            if (GetTag(AuthorTags._AUTOR_LOGO_INDEX_) != string.Empty)
                AuthorLogo = new Bitmap(new MemoryStream(bitmapFromUU(GetTag(AuthorTags._AUTOR_LOGO_INDEX_))));
            if (GetTag(AuthorTags._AUTOR_SPLASH_INDEX_) != string.Empty)
                AuthorSplash = new Bitmap(new MemoryStream(bitmapFromUU(GetTag(AuthorTags._AUTOR_SPLASH_INDEX_))));

        }

        public void SetPassword(string Password = "")
        {
            if (PasswordHash != string.Empty)
            {
                if (Password != string.Empty)
                {
                    string newPasswordHash = ConfigurationHash(Password.ToUpper().Substring(0, 10));
                    MetaDataStream = MetaDataStream.Replace(PasswordHash, newPasswordHash);
                    PasswordHash = newPasswordHash;
                    IsEncrypted = true;
                }
                else
                {
                    MetaDataStream = MetaDataStream.Replace(PasswordHash, "");
                    PasswordHash = null;
                    IsEncrypted = false;
                }
            }
            else
            {
                if (Password != string.Empty)
                {
                    PasswordHash = ConfigurationHash(Password.ToUpper().Substring(0, 10));
                    string TaskItemDescription = MetaDataStream.Split(new string[] { "\r\n" }, StringSplitOptions.RemoveEmptyEntries).First(x => x.StartsWith("{\"1\","));
                    string[] buffer = TaskItemDescription.Split(',');
                    buffer[4] = string.Format("\"{0}\"", PasswordHash);
                    MetaDataStream = MetaDataStream.Replace(TaskItemDescription, string.Join(",", buffer));
                    IsEncrypted = true;
                }
                else
                {
                    PasswordHash = null;
                    IsEncrypted = false;
                }
            }

            RecalcCRC();
        }

        uint MetaDataStreamCRC(string data)
        {
            int i = 0;
            uint CRC = 0;

            string tmp = data;

            if (tmp.Contains(",\r\n{\"CRC\"")) 
                tmp = tmp.Substring(0, tmp.IndexOf(",\r\n{\"CRC\"")) + "}";
            

            tmp = tmp.Replace("\r\n", "");

            byte[] Data = win1251.GetBytes(tmp);
            byte[] CRCBuffer = new byte[4] { 0, 0, 0, 0 };
            sbyte CurrentChar;
            do
            {
                CurrentChar =   (sbyte)Data[i];
                CRCBuffer[3] += (byte)CurrentChar;                       //BYTE3(CRC) += CurrentChar;
                CRCBuffer[1] ^= (byte)(CurrentChar % 3);                 //BYTE1(CRC) ^= CurrentChar % 3;
                CRCBuffer[2] ^= (byte)(CurrentChar % 7);                 //BYTE2(CRC) ^= Data[i] % 7;
                CRCBuffer[0] ^= (byte)((sbyte)(CurrentChar + i++) % 11); //LOBYTE(CRC) = (Data[i] + j++) % 11 ^ CRC;
            }
            while (i < Data.Length);

            CRC = BitConverter.ToUInt32(CRCBuffer, 0);
            return CRC;
        }

        public static byte[] UU2bin(Stream input)
        {
            if (input == null)
                throw new ArgumentNullException("input");
            int len = (int)input.Length;

            if (len == 0)
                throw new ArgumentNullException("input"); ;

            int resultLength = 3 * len / 4 + 1;
            byte[] output = new byte[resultLength];

            int didx = 0;
            byte A, B, C, D;
            while (didx < resultLength)
            {
                A = (byte)(input.ReadByte() - 0x20);
                B = (byte)(input.ReadByte() - 0x20);
                C = (byte)(input.ReadByte() - 0x20);
                D = (byte)(input.ReadByte() - 0x20);

                try
                {
                    output[didx++] = (byte)((byte)((A << 2)) | (byte)((B >> 4) & 3));
                    output[didx++] = (byte)((byte)((B << 4)) | (byte)((C >> 2) & 0xf));
                    output[didx++] = (byte)((byte)((C << 6)) | (byte)(D & 0x3f));
                }
                catch
                {

                }
            }
            return output;
        }

        public static string bin2UU(Stream input)
        {
            if (input == null)
                throw new ArgumentNullException("input");

            int len = (int)input.Length;

            if (len == 0)
                throw new ArgumentNullException("input");

            int resultLength = 4 * (len - 1) / 3 ;

            byte[] output = new byte[resultLength];

            int didx = 0;
            byte A, B, C;
            while (didx < resultLength)
            {
                A = (byte)input.ReadByte();
                B = (byte)input.ReadByte();
                C = (byte)input.ReadByte();

                try
                {
                    output[didx++] = (byte)(((A >> 2) & 0x3f) + 0x20);
                    output[didx++] = (byte)(((B >> 4) & 0xf | (A << 4) & 0x3f) + 0x20);
                    output[didx++] = (byte)(((C >> 6) & 3 | (B << 2) & 0x3f) + 0x20);
                    output[didx++] = (byte)((C & 0x3f) + 0x20);
                }
                catch
                {

                }
            }
            return Encoding.GetEncoding(1251).GetString(output).Replace("\"","\"\"");
        }

        void RecalcCRC()
        {
            //пересчитаем CRC
            MetaDataStream = MetaDataStream.Replace(",\"10009\",",",\"10011\",");
            string NewCRC = MetaDataStreamCRC(MetaDataStream).ToString("d");

            if (MetaDataStream.Contains(",\r\n{\"CRC\""))
                MetaDataStream = MetaDataStream.Replace(CRC, NewCRC);
            else
            {
                if (!MetaDataStream.Contains(",\"###.###.##\",\"###.###.##\"\r\n"))
                {
                    MetaDataStream = MetaDataStream.Replace(",\"###.###.##\",\r\n", ",\"###.###.##\",\"###.###.##\",\r\n");
                    MetaDataStream = MetaDataStream.Replace(",\"####\",\r\n", ",\"####\",\"####\",\r\n");
                    NewCRC = MetaDataStreamCRC(MetaDataStream).ToString("d");
                }
                MetaDataStream = MetaDataStream.Substring(0, MetaDataStream.Length - 1) + ",\r\n{\"CRC\",\"" + NewCRC + "\"}}\r\n";

            }

            CRC = NewCRC;
        }

        byte[] PrepareMMSData()
        {
            //Составим префикс потока, содержащий длину.
            byte[] MMSLength = new byte[0];
            if (MetaDataStream.Length > short.MaxValue)
                MMSLength = BitConverter.GetBytes(MetaDataStream.Length);
            else
                MMSLength = BitConverter.GetBytes((short)(MetaDataStream.Length));
            byte[] MMSLengthPrefix = new byte[MMSLength.Length * 2 - 1];

            //Префикс длины: FF если длина потока вмещается в WORD, FF FF если в DWORD.
            for (int i = 0; i < MMSLength.Length - 1; i++)
                MMSLengthPrefix[i] = 0xFF;

            Array.Copy(MMSLength, 0, MMSLengthPrefix, MMSLength.Length - 1, MMSLength.Length);

            byte[] data = new byte[MetaDataStream.Length + MMSLengthPrefix.Length];
            Array.Copy(MMSLengthPrefix, data, MMSLengthPrefix.Length);
            Array.Copy(win1251.GetBytes(MetaDataStream), 0, data, MMSLengthPrefix.Length, MetaDataStream.Length);
            
            if (IsEncrypted)
                data = Encryption.Encode(data, Encryption.Mode.MetaDataStream);
            return data;
        }

        byte[] PrepareGMData()
        {
            byte[] data = win1251.GetBytes(GlobalModule);
            DeflateStream ZlibCompressed = null;
            if (IsEncrypted)
            {
                data = Encryption.Encode(data, Encryption.Mode.GlobalModule);
            }
            MemoryStream tempstream = new MemoryStream();

            ZlibCompressed = new DeflateStream(tempstream, CompressionLevel.Optimal, true);
            ZlibCompressed.Write(data, 0, data.Length);
            ZlibCompressed.Close();

            data = tempstream.GetBuffer();
            Array.Resize<byte>(ref data, (int)tempstream.Length);
            return data;
        }

        //Сохранить
        public bool Save(string filename)
        {
            IStream pIStream;
            GlobalStorage.GetStorage("root\\Metadata").DestroyElement("Main MetaData Stream");
            GlobalStorage.GetStorage("root\\Metadata").CreateStream("Main MetaData Stream", NativeMethods.STGM.CREATE | NativeMethods.STGM.READWRITE | NativeMethods.STGM.SHARE_EXCLUSIVE, 0, 0, out pIStream);
            //Storage.OpenStream("Main MetaData Stream", IntPtr.Zero, NativeMethods.STGM.READWRITE | NativeMethods.STGM.SHARE_EXCLUSIVE, 0, out pIStream);
            byte[] data = PrepareMMSData();
            pIStream.Write(data, data.Length, IntPtr.Zero);
            pIStream.Commit((int)NativeMethods.STGC.OVERWRITE);

            Marshal.ReleaseComObject(pIStream);
            Marshal.FinalReleaseComObject(pIStream);
            pIStream = null;
            
            if (!IsEncrypted) // запишем расшифрованный MMS, глобальник и сменим clsid у папки MetaData
                GlobalStorage.GetStorage("root\\Metadata").SetClass(Guid.Empty); //Запишем GUID = "00000000-0000-0000-0000-000000000000"
            else// запишем pашифрованный MMS, глобальник и сменим clsid у папки MetaData
                GlobalStorage.GetStorage("root\\Metadata").SetClass(EncryptedClass); //Запишем GUID = "0af60370-754e-11d2-9f21-008048da120f"

            GlobalStorage.GetStorage("root\\Metadata").Commit(NativeMethods.STGC.OVERWRITE);
            RootStorage.Commit(NativeMethods.STGC.OVERWRITE);

            //RootStorage.OpenStorage("TypedText", null, NativeMethods.STGM.READWRITE | NativeMethods.STGM.SHARE_EXCLUSIVE, IntPtr.Zero, 0, out Storage);
            //Storage.OpenStorage("ModuleText_Number1", null, NativeMethods.STGM.READWRITE | NativeMethods.STGM.SHARE_EXCLUSIVE, IntPtr.Zero, 0, out Storage);
            GlobalStorage.GetStorage("root\\TypedText\\ModuleText_Number1").DestroyElement("MD Programm text");
            GlobalStorage.GetStorage("root\\TypedText\\ModuleText_Number1").CreateStream("MD Programm text", NativeMethods.STGM.CREATE | NativeMethods.STGM.READWRITE | NativeMethods.STGM.SHARE_EXCLUSIVE, 0, 0, out pIStream);

            data = PrepareGMData();
            pIStream.Write(data, data.Length, IntPtr.Zero);
            pIStream.Commit((int)NativeMethods.STGC.OVERWRITE);
            GlobalStorage.GetStorage("root\\TypedText\\ModuleText_Number1").Commit(NativeMethods.STGC.OVERWRITE);
            RootStorage.Commit(NativeMethods.STGC.OVERWRITE);

            NativeMethods.IStorage NewStorage;
            if (NativeMethods.StgCreateDocfile(filename, NativeMethods.STGM.CREATE | NativeMethods.STGM.READWRITE| NativeMethods.STGM.SHARE_EXCLUSIVE, 0, out NewStorage) == 0)
            {
                RootStorage.CopyTo(0, Guid.Empty, IntPtr.Zero, NewStorage);
                NewStorage.Commit(NativeMethods.STGC.DEFAULT);
            }

            Marshal.ReleaseComObject(NewStorage);
            Marshal.FinalReleaseComObject(NewStorage);
            NewStorage = null;

            GlobalStorage = null;

            Marshal.ReleaseComObject(pIStream);
            Marshal.FinalReleaseComObject(pIStream);
            pIStream = null;

            return true;
        }

        ~Compound()
        {
            //Освободим паямть
            Marshal.ReleaseComObject(RootStorage);
            Marshal.FinalReleaseComObject(RootStorage);
            RootStorage = null;

            Marshal.ReleaseComObject(LockBytes);
            Marshal.FinalReleaseComObject(LockBytes);
            LockBytes = null;
            Marshal.FreeHGlobal(hGlobal);
        }
    }
}
