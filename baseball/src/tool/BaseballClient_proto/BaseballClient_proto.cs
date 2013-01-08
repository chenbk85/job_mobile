
using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Collections.Generic;
using System.Runtime.Serialization;


using System.IO;
using ProtoBuf;



namespace nPROTO
{
    public class jException : System.Exception
    {
        public jException(string s)
            : base(s)
        {
            Console.WriteLine("[nPROTO.jException] Logging '{0}'", this.Message);
        }
    }

    public class util
    {
        public static void PrintInfo(MemoryStream sendMS)
        {
            Console.WriteLine("Length: {0}\tPosition: {1}\tCapacity: {2}", sendMS.Length, sendMS.Position, sendMS.Capacity);
        }
        public static byte[] EncodingSize_To_Data(byte[] sendOrgData)
        {
            int iLen = sendOrgData.Length;


            byte[] sendData = null;

            using (MemoryStream os = new MemoryStream())
            {
                os.Write(BitConverter.GetBytes(iLen), 0, sizeof(int));
                foreach (byte b in sendOrgData)
                {
                    os.WriteByte(b);
                }
                sendData = os.ToArray();
            }

            return sendData;
            //PrintInfo(sendData);
        }

        //socketData = [size:4] + [contents_bytes:size]
        public static byte[] DecodingSize_From_Data(ref int iSize, byte[] socketData)
        {
            byte[] buf_recvData = null;
            using (MemoryStream os = new MemoryStream(socketData))
            {
                byte[] buf_recvLen = new byte[4];
                os.Read(buf_recvLen, 0, sizeof(Int32));
                iSize = BitConverter.ToInt32(buf_recvLen, 0);

                buf_recvData = new byte[iSize];
                for (int i = 0; i < iSize; ++i)
                {
                    buf_recvData[i] = Convert.ToByte(os.ReadByte());
                }
            }
            return buf_recvData;
        }

    }//class util



}//namespace nPROTO