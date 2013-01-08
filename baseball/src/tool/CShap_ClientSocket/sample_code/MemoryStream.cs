

using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Collections.Generic;
using System.Linq;

using System.IO;
namespace MemStream
{
    class MemStreamApp
    {

        [STAThread]
        static void Main(string[] args)
        {
            // Write some data to a MemoryStream
            byte[] sendByte = new byte[12];
            MemoryStream sendMS = new MemoryStream(sendByte);
            Console.WriteLine(Length: {0}\tPosition: {1}\tCapacity: {2}",sendMS.Length, sendMS.Position, sendMS.Capacity);

            Int64 iData =12345678;
            Int32 iLen = sizeof(Int64);
            sendMS.Write(BitConverter.GetBytes(iLen), 0, sizeof(Int32));

            byte[] sendData  =BitConverter.GetBytes(iData);
            foreach (byte b in sendData)
            {
                sendMS.WriteByte(b);
            }

            byte[] sendRawData = sendMS.ToArray();

            MemoryStream recvMS = new MemoryStream(sendRawData);
            byte[] buf_recvLen = new byte[4];
            recvMS.Read(buf_recvLen,0,sizeof(Int32));
            Int32  iLen2 = BitConverter.ToInt32(buf_recvLen,0);

            byte[] buf_recvData = new byte[iLen2];
            for (int i = 0; i < iLen2; ++i)
            {
                buf_recvData[i] = Convert.ToByte(recvMS.ReadByte());
            }
            //recvMS.Read(buf_recvData, 4, iLen2);
            Int64 iData2 = BitConverter.ToInt64(buf_recvData, 0);

            int ii=0;
            ++ii;

        }
    }
}
