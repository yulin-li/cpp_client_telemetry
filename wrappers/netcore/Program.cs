using System;
using System.Runtime.InteropServices;
using System.Text;
using System.IO;
using System.Json;

namespace EventSender
{
    public enum EventCallType
    {
        EVT_OP_LOAD = 0x00000001,
        EVT_OP_UNLOAD = 0x00000002,
        EVT_OP_OPEN = 0x00000003,
        EVT_OP_CLOSE = 0x00000004,
        EVT_OP_CONFIG = 0x00000005,
        EVT_OP_LOG = 0x00000006,
        EVT_OP_PAUSE = 0x00000007,
        EVT_OP_RESUME = 0x00000008,
        EVT_OP_UPLOAD = 0x00000009,
        EVT_OP_FLUSH = 0x0000000A,
        EVT_OP_VERSION = 0x0000000B,
        EVT_OP_OPEN_WITH_PARAMS = 0x0000000C,
        EVT_OP_MAX = EVT_OP_OPEN_WITH_PARAMS + 1
    }

    [StructLayout(LayoutKind.Explicit, Size = 24, CharSet = CharSet.Ansi)]
    public struct EventCallContext
    {
        [FieldOffset(0)] public UInt32 call;
        [FieldOffset(4)] public ulong handle;
        [FieldOffset(12)] public IntPtr data;
        [FieldOffset(16)] public UInt32 result;
        [FieldOffset(20)] public UInt32 size;
    }

    internal static class NativeMethods
    {
        // Conditional compilation: pass different library name depending on target OS?
        const string SDK_LIBRARY_NAME = "libmat";

        [DllImport(SDK_LIBRARY_NAME, EntryPoint = "evt_api_call_default")]
        public static extern UInt32 evt_api_call([In, Out] ref EventCallContext context);
    }

    class Program
    {
        public const string SDK_VERSION = "3.3.0-netcore";

        static string ReadConfiguration(string filename)
        {
            string result = "";
            using (StreamReader sr = new StreamReader(filename))
            {
                result = sr.ReadToEnd();
            }
            return result;
        }

        static ulong evt_open(string cfg)
        {
            EventCallContext context = new EventCallContext
            {
                call = (Byte)EventCallType.EVT_OP_OPEN,
                data = Marshal.StringToHGlobalAnsi(cfg)
            };
            NativeMethods.evt_api_call(ref context);
            return context.handle;
        }

        static ulong evt_close(ulong inHandle)
        {
            EventCallContext context = new EventCallContext
            {
                call = (Byte)EventCallType.EVT_OP_CLOSE,
                handle = inHandle
            };
            return NativeMethods.evt_api_call(ref context);
        }

        static string evt_version()
        {
            byte[] data = Encoding.ASCII.GetBytes(SDK_VERSION);
            var nativeDataPtr = Marshal.AllocHGlobal(data.Length + 1);
            Marshal.Copy(data, 0, nativeDataPtr, data.Length);
            Marshal.WriteByte(nativeDataPtr + data.Length, 0);
            EventCallContext context = new EventCallContext
            {
                call = (Byte)EventCallType.EVT_OP_VERSION,
                data = nativeDataPtr
            };
            NativeMethods.evt_api_call(ref context);
            return Marshal.PtrToStringAnsi(context.data);
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Reading configuration...");
            string cfg = ReadConfiguration("sdk-config.json");

            // Parse to verify it is valid and print it out..
            // Parser should throw if config is invalid.
            JsonObject jsonDoc = (JsonObject)JsonObject.Parse(cfg);
            Console.WriteLine("SDK configuration:\n{0}", jsonDoc.ToString());

            // Obtain SDK version from native library
            Console.WriteLine("SDK version: {0}", evt_version());

            // Initialize
            Console.WriteLine("evt_open...");
            var handle = evt_open(cfg);
            Console.WriteLine("handle={0}", handle);

            // FlushAndTeardown
            Console.WriteLine("evt_close...");
            var result = evt_close(handle);
            Console.WriteLine("result={0}", result);
        }
    }
}
