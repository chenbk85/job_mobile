using System.Collections.Generic;
using System;
using System.IO;

using nPROTO;
//using nPROTOCOL;

//using ProtoBuf;
//using ProtoBuf.Meta;


public class read_binary
{
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

    //----------------------------------------------------------------------------
    //- ug.cs
    //----------------------------------------------------------------------------
    public static byte[] Serialize(nPROTO.Version m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref nPROTO.Version m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(nPROTO.Version)) as nPROTO.Version;
        }
    }

    public static void Decoding_FromSocketData(ref nPROTO.Version m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }

    //----------------------------------------------------------------------------

    public static byte[] Serialize(Error m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref Error m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(Error)) as Error;
        }
    }

    public static void Decoding_FromSocketData(ref Error m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(Desc m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref Desc m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(Desc)) as Desc;
        }
    }

    public static void Decoding_FromSocketData(ref Desc m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(Notice m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref Notice m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(Notice)) as Notice;
        }
    }

    public static void Decoding_FromSocketData(ref Notice m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(UError m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UError m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UError)) as UError;
        }
    }

    public static void Decoding_FromSocketData(ref UError m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(UReqConnect m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UReqConnect m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UReqConnect)) as UReqConnect;
        }
    }

    public static void Decoding_FromSocketData(ref UReqConnect m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(UAnsConnect m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UAnsConnect m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UAnsConnect)) as UAnsConnect;
        }
    }

    public static void Decoding_FromSocketData(ref UAnsConnect m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(UReqNotice m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UReqNotice m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UReqNotice)) as UReqNotice;
        }
    }

    public static void Decoding_FromSocketData(ref UReqNotice m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(UAnsNotice m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UAnsNotice m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UAnsNotice)) as UAnsNotice;
        }
    }

    public static void Decoding_FromSocketData(ref UAnsNotice m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(UReqChannel m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UReqChannel m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UReqChannel)) as UReqChannel;
        }
    }

    public static void Decoding_FromSocketData(ref UReqChannel m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(UAnsChannel m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UAnsChannel m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UAnsChannel)) as UAnsChannel;
        }
    }

    public static void Decoding_FromSocketData(ref UAnsChannel m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(UErrChannel m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UErrChannel m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UErrChannel)) as UErrChannel;
        }
    }

    public static void Decoding_FromSocketData(ref UErrChannel m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(UReqStore m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UReqStore m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UReqStore)) as UReqStore;
        }
    }

    public static void Decoding_FromSocketData(ref UReqStore m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(UAnsStore m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UAnsStore m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UAnsStore)) as UAnsStore;
        }
    }

    public static void Decoding_FromSocketData(ref UAnsStore m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(UReqInfo m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UReqInfo m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UReqInfo)) as UReqInfo;
        }
    }

    public static void Decoding_FromSocketData(ref UReqInfo m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(UAnsInfo m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UAnsInfo m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UAnsInfo)) as UAnsInfo;
        }
    }

    public static void Decoding_FromSocketData(ref UAnsInfo m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------


    public static byte[] Serialize(UReqAutoJoin m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UReqAutoJoin m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UReqAutoJoin)) as UReqAutoJoin;
        }
    }

    public static void Decoding_FromSocketData(ref UReqAutoJoin m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(UAnsAutoJoin m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UAnsAutoJoin m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UAnsAutoJoin)) as UAnsAutoJoin;
        }
    }

    public static void Decoding_FromSocketData(ref UAnsAutoJoin m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(UReqLeaveGame m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UReqLeaveGame m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UReqLeaveGame)) as UReqLeaveGame;
        }
    }

    public static void Decoding_FromSocketData(ref UReqLeaveGame m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(UAnsLeaveGame m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UAnsLeaveGame m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UAnsLeaveGame)) as UAnsLeaveGame;
        }
    }

    public static void Decoding_FromSocketData(ref UAnsLeaveGame m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(UReqClose m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UReqClose m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UReqClose)) as UReqClose;
        }
    }

    public static void Decoding_FromSocketData(ref UReqClose m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(UAnsClose m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UAnsClose m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UAnsClose)) as UAnsClose;
        }
    }

    public static void Decoding_FromSocketData(ref UAnsClose m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(UReqPong m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UReqPong m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UReqPong)) as UReqPong;
        }
    }

    public static void Decoding_FromSocketData(ref UReqPong m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(UAnsPing m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UAnsPing m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UAnsPing)) as UAnsPing;
        }
    }

    public static void Decoding_FromSocketData(ref UAnsPing m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(UReqPlug m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UReqPlug m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UReqPlug)) as UReqPlug;
        }
    }

    public static void Decoding_FromSocketData(ref UReqPlug m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(UAnsPlug m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UAnsPlug m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UAnsPlug)) as UAnsPlug;
        }
    }

    public static void Decoding_FromSocketData(ref UAnsPlug m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(UReqProtocol m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UReqProtocol m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UReqProtocol)) as UReqProtocol;
        }
    }

    public static void Decoding_FromSocketData(ref UReqProtocol m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(UAnsProtocol m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UAnsProtocol m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UAnsProtocol)) as UAnsProtocol;
        }
    }

    public static void Decoding_FromSocketData(ref UAnsProtocol m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(MemberInfo m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref MemberInfo m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(MemberInfo)) as MemberInfo;
        }
    }

    public static void Decoding_FromSocketData(ref MemberInfo m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    //----------------------------------------------------------------------------
    //- db.cs
    //----------------------------------------------------------------------------

    public static byte[] Serialize(DBIn m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref DBIn m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(DBIn)) as DBIn;
        }
    }

    public static void Decoding_FromSocketData(ref DBIn m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(ReqDB m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref ReqDB m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(ReqDB)) as ReqDB;
        }
    }

    public static void Decoding_FromSocketData(ref ReqDB m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(AnsDB m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref AnsDB m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(AnsDB)) as AnsDB;
        }
    }

    public static void Decoding_FromSocketData(ref AnsDB m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    //----------------------------------------------------------------------------
    //- excel_baseball_table_db.cs
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_tbl__playerbase m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_tbl__playerbase m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_tbl__playerbase)) as s_tbl__playerbase;
        }
    }

    public static void Decoding_FromSocketData(ref s_tbl__playerbase m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_tbl_friend m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_tbl_friend m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_tbl_friend)) as s_tbl_friend;
        }
    }

    public static void Decoding_FromSocketData(ref s_tbl_friend m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_tbl_item m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_tbl_item m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_tbl_item)) as s_tbl_item;
        }
    }

    public static void Decoding_FromSocketData(ref s_tbl_item m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_tbl_item_admin m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_tbl_item_admin m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_tbl_item_admin)) as s_tbl_item_admin;
        }
    }

    public static void Decoding_FromSocketData(ref s_tbl_item_admin m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_tbl_pitcherskill m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_tbl_pitcherskill m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_tbl_pitcherskill)) as s_tbl_pitcherskill;
        }
    }

    public static void Decoding_FromSocketData(ref s_tbl_pitcherskill m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_tbl_playerbetter m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_tbl_playerbetter m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_tbl_playerbetter)) as s_tbl_playerbetter;
        }
    }

    public static void Decoding_FromSocketData(ref s_tbl_playerbetter m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_tbl_playerpitcher m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_tbl_playerpitcher m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_tbl_playerpitcher)) as s_tbl_playerpitcher;
        }
    }

    public static void Decoding_FromSocketData(ref s_tbl_playerpitcher m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_tbl_result m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_tbl_result m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_tbl_result)) as s_tbl_result;
        }
    }

    public static void Decoding_FromSocketData(ref s_tbl_result m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_tbl_roundresult m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_tbl_roundresult m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_tbl_roundresult)) as s_tbl_roundresult;
        }
    }

    public static void Decoding_FromSocketData(ref s_tbl_roundresult m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_tbl_team m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_tbl_team m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_tbl_team)) as s_tbl_team;
        }
    }

    public static void Decoding_FromSocketData(ref s_tbl_team m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_tbl_user m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_tbl_user m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_tbl_user)) as s_tbl_user;
        }
    }

    public static void Decoding_FromSocketData(ref s_tbl_user m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    //----------------------------------------------------------------------------
    //- game.cs
    //----------------------------------------------------------------------------

    public static byte[] Serialize(GReqGameEnter m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref GReqGameEnter m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(GReqGameEnter)) as GReqGameEnter;
        }
    }

    public static void Decoding_FromSocketData(ref GReqGameEnter m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(GAnsGameEnter m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref GAnsGameEnter m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(GAnsGameEnter)) as GAnsGameEnter;
        }
    }

    public static void Decoding_FromSocketData(ref GAnsGameEnter m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(GReqGameLeave m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref GReqGameLeave m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(GReqGameLeave)) as GReqGameLeave;
        }
    }

    public static void Decoding_FromSocketData(ref GReqGameLeave m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(GAnsGameLeave m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref GAnsGameLeave m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(GAnsGameLeave)) as GAnsGameLeave;
        }
    }

    public static void Decoding_FromSocketData(ref GAnsGameLeave m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(GReqDetach m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref GReqDetach m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(GReqDetach)) as GReqDetach;
        }
    }

    public static void Decoding_FromSocketData(ref GReqDetach m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(GAnsDetach m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref GAnsDetach m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(GAnsDetach)) as GAnsDetach;
        }
    }

    public static void Decoding_FromSocketData(ref GAnsDetach m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(GReqPlug m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref GReqPlug m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(GReqPlug)) as GReqPlug;
        }
    }

    public static void Decoding_FromSocketData(ref GReqPlug m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(GAnsPlug m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref GAnsPlug m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(GAnsPlug)) as GAnsPlug;
        }
    }

    public static void Decoding_FromSocketData(ref GAnsPlug m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(GError m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref GError m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(GError)) as GError;
        }
    }

    public static void Decoding_FromSocketData(ref GError m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(GErrPlug m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref GErrPlug m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(GErrPlug)) as GErrPlug;
        }
    }

    public static void Decoding_FromSocketData(ref GErrPlug m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(GAnsUserUpdate m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref GAnsUserUpdate m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(GAnsUserUpdate)) as GAnsUserUpdate;
        }
    }

    public static void Decoding_FromSocketData(ref GAnsUserUpdate m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(GAnsStatus m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref GAnsStatus m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(GAnsStatus)) as GAnsStatus;
        }
    }

    public static void Decoding_FromSocketData(ref GAnsStatus m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(GReqStatus m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref GReqStatus m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(GReqStatus)) as GReqStatus;
        }
    }

    public static void Decoding_FromSocketData(ref GReqStatus m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(GReqProtocol m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref GReqProtocol m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(GReqProtocol)) as GReqProtocol;
        }
    }

    public static void Decoding_FromSocketData(ref GReqProtocol m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(GAnsProtocol m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref GAnsProtocol m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(GAnsProtocol)) as GAnsProtocol;
        }
    }

    public static void Decoding_FromSocketData(ref GAnsProtocol m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    //----------------------------------------------------------------------------
    //- gameLogic.cs
    //----------------------------------------------------------------------------
    /*
    public static byte[] Serialize(EUserGPS m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref EUserGPS m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(EUserGPS)) as EUserGPS;
        }
    }

    public static void Decoding_FromSocketData(ref EUserGPS m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
     * */
    //----------------------------------------------------------------------------

    public static byte[] Serialize(GameUserInfo m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref GameUserInfo m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(GameUserInfo)) as GameUserInfo;
        }
    }

    public static void Decoding_FromSocketData(ref GameUserInfo m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(GameInfo m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref GameInfo m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(GameInfo)) as GameInfo;
        }
    }

    public static void Decoding_FromSocketData(ref GameInfo m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(s_game_play_info m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_game_play_info m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_game_play_info)) as s_game_play_info;
        }
    }

    public static void Decoding_FromSocketData(ref s_game_play_info m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(s_result_round m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_result_round m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_result_round)) as s_result_round;
        }
    }

    public static void Decoding_FromSocketData(ref s_result_round m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(s_result_game m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_result_game m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_result_game)) as s_result_game;
        }
    }

    public static void Decoding_FromSocketData(ref s_result_game m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(GameRoomInfo m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref GameRoomInfo m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(GameRoomInfo)) as GameRoomInfo;
        }
    }

    public static void Decoding_FromSocketData(ref GameRoomInfo m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(s_vector3 m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_vector3 m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_vector3)) as s_vector3;
        }
    }

    public static void Decoding_FromSocketData(ref s_vector3 m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(s_vector2 m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_vector2 m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_vector2)) as s_vector2;
        }
    }

    public static void Decoding_FromSocketData(ref s_vector2 m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(s_pitcher_throw_info m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_pitcher_throw_info m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_pitcher_throw_info)) as s_pitcher_throw_info;
        }
    }

    public static void Decoding_FromSocketData(ref s_pitcher_throw_info m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(s_pitcher_throw_info_verify m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_pitcher_throw_info_verify m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_pitcher_throw_info_verify)) as s_pitcher_throw_info_verify;
        }
    }

    public static void Decoding_FromSocketData(ref s_pitcher_throw_info_verify m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(s_better_hit_info m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_better_hit_info m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_better_hit_info)) as s_better_hit_info;
        }
    }

    public static void Decoding_FromSocketData(ref s_better_hit_info m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(s_better_hit_info_verify m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_better_hit_info_verify m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_better_hit_info_verify)) as s_better_hit_info_verify;
        }
    }

    public static void Decoding_FromSocketData(ref s_better_hit_info_verify m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(GLReqGameProtocol m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref GLReqGameProtocol m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(GLReqGameProtocol)) as GLReqGameProtocol;
        }
    }

    public static void Decoding_FromSocketData(ref GLReqGameProtocol m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    public static byte[] Serialize(GLAnsGameProtocol m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref GLAnsGameProtocol m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(GLAnsGameProtocol)) as GLAnsGameProtocol;
        }
    }

    public static void Decoding_FromSocketData(ref GLAnsGameProtocol m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    //----------------------------------------------------------------------------
    //- presence.cs
    //----------------------------------------------------------------------------
    public static byte[] Serialize(PAnsProtocol m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref PAnsProtocol m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(PAnsProtocol)) as PAnsProtocol;
        }
    }

    public static void Decoding_FromSocketData(ref PAnsProtocol m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    /*
    public static byte[] Serialize(PresenceCommand m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref PresenceCommand m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(PresenceCommand)) as PresenceCommand;
        }
    }

    public static void Decoding_FromSocketData(ref PresenceCommand m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    */
    //----------------------------------------------------------------------------

    public static byte[] Serialize(PReqProtocol m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref PReqProtocol m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(PReqProtocol)) as PReqProtocol;
        }
    }

    public static void Decoding_FromSocketData(ref PReqProtocol m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    //----------------------------------------------------------------------------
    //- protocol.cs
    //----------------------------------------------------------------------------
    public static byte[] Serialize(nPROTOCOL.GameUserInfo m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref nPROTOCOL.GameUserInfo m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(nPROTOCOL.GameUserInfo)) as nPROTOCOL.GameUserInfo;
        }
    }

    public static void Decoding_FromSocketData(ref nPROTOCOL.GameUserInfo m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(nPROTOCOL.GameRoomInfo m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref nPROTOCOL.GameRoomInfo m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(nPROTOCOL.GameRoomInfo)) as nPROTOCOL.GameRoomInfo;
        }
    }

    public static void Decoding_FromSocketData(ref nPROTOCOL.GameRoomInfo m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(nPROTOCOL.GameInfo m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref nPROTOCOL.GameInfo m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(nPROTOCOL.GameInfo)) as nPROTOCOL.GameInfo;
        }
    }

    public static void Decoding_FromSocketData(ref nPROTOCOL.GameInfo m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(nPROTOCOL.AnsJoinUser m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref nPROTOCOL.AnsJoinUser m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(nPROTOCOL.AnsJoinUser)) as nPROTOCOL.AnsJoinUser;
        }
    }

    public static void Decoding_FromSocketData(ref nPROTOCOL.AnsJoinUser m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(nPROTOCOL.AnsLeaveUser m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref nPROTOCOL.AnsLeaveUser m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(nPROTOCOL.AnsLeaveUser)) as nPROTOCOL.AnsLeaveUser;
        }
    }

    public static void Decoding_FromSocketData(ref nPROTOCOL.AnsLeaveUser m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(nPROTOCOL.ReqPurgeUser m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref nPROTOCOL.ReqPurgeUser m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(nPROTOCOL.ReqPurgeUser)) as nPROTOCOL.ReqPurgeUser;
        }
    }

    public static void Decoding_FromSocketData(ref nPROTOCOL.ReqPurgeUser m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(nPROTOCOL.GLReqGameProtocol m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref nPROTOCOL.GLReqGameProtocol m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(nPROTOCOL.GLReqGameProtocol)) as nPROTOCOL.GLReqGameProtocol;
        }
    }

    public static void Decoding_FromSocketData(ref nPROTOCOL.GLReqGameProtocol m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(nPROTOCOL.GLAnsGameProtocol m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref nPROTOCOL.GLAnsGameProtocol m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(nPROTOCOL.GLAnsGameProtocol)) as nPROTOCOL.GLAnsGameProtocol;
        }
    }

    public static void Decoding_FromSocketData(ref nPROTOCOL.GLAnsGameProtocol m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    //----------------------------------------------------------------------------
    //- PT_BaseballServer.cs
    //----------------------------------------------------------------------------
    /*
    public static byte[] Serialize(EUserGPS_notuse m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref EUserGPS_notuse m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(EUserGPS_notuse)) as EUserGPS_notuse;
        }
    }

    public static void Decoding_FromSocketData(ref EUserGPS_notuse m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    */
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_ping1 m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_ping1 m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_ping1)) as s_req_ping1;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_ping1 m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_pong1 m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_pong1 m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_pong1)) as s_ans_pong1;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_pong1 m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_chat m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_chat m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_chat)) as s_req_chat;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_chat m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_chat m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_chat m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_chat)) as s_ans_chat;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_chat m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_timer_start m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_timer_start m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_timer_start)) as s_ans_timer_start;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_timer_start m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_timer_start m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_timer_start m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_timer_start)) as s_req_timer_start;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_timer_start m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_do_disconnect m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_do_disconnect m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_do_disconnect)) as s_req_do_disconnect;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_do_disconnect m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_ping2 m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_ping2 m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_ping2)) as s_req_ping2;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_ping2 m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_pong2 m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_pong2 m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_pong2)) as s_ans_pong2;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_pong2 m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_bs_error m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_bs_error m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_bs_error)) as s_ans_bs_error;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_bs_error m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_get_cvar m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_get_cvar m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_get_cvar)) as s_req_get_cvar;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_get_cvar m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_set_cvar m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_set_cvar m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_set_cvar)) as s_req_set_cvar;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_set_cvar m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_join_room m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_join_room m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_join_room)) as s_ans_join_room;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_join_room m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_room_state m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_room_state m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_room_state)) as s_req_room_state;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_room_state m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_room_state m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_room_state m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_room_state)) as s_ans_room_state;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_room_state m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_team_match_ready m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_team_match_ready m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_team_match_ready)) as s_req_team_match_ready;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_team_match_ready m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_team_match_ready m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_team_match_ready m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_team_match_ready)) as s_ans_team_match_ready;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_team_match_ready m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_game_start m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_game_start m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_game_start)) as s_ans_game_start;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_game_start m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_game_round_start m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_game_round_start m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_game_round_start)) as s_ans_game_round_start;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_game_round_start m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_pitcher_throw m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_pitcher_throw m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_pitcher_throw)) as s_req_pitcher_throw;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_pitcher_throw m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_pitcher_throw m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_pitcher_throw m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_pitcher_throw)) as s_ans_pitcher_throw;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_pitcher_throw m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_better_hit m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_better_hit m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_better_hit)) as s_req_better_hit;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_better_hit m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_better_hit m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_better_hit m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_better_hit)) as s_ans_better_hit;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_better_hit m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_result_better_hit m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_result_better_hit m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_result_better_hit)) as s_req_result_better_hit;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_result_better_hit m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_result_better_hit m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_result_better_hit m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_result_better_hit)) as s_ans_result_better_hit;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_result_better_hit m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_change_attack_team m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_change_attack_team m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_change_attack_team)) as s_ans_change_attack_team;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_change_attack_team m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_game_end m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_game_end m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_game_end)) as s_ans_game_end;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_game_end m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_user_disconnect m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_user_disconnect m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_user_disconnect)) as s_ans_user_disconnect;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_user_disconnect m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(BaseballServer_Client m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref BaseballServer_Client m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(BaseballServer_Client)) as BaseballServer_Client;
        }
    }

    public static void Decoding_FromSocketData(ref BaseballServer_Client m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(Client_BaseballServer m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref Client_BaseballServer m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(Client_BaseballServer)) as Client_BaseballServer;
        }
    }

    public static void Decoding_FromSocketData(ref Client_BaseballServer m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    //----------------------------------------------------------------------------
    //- PT_UserGateServer.cs
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_add_item m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_add_item m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_add_item)) as s_ans_add_item;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_add_item m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_admin_add_item m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_admin_add_item m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_admin_add_item)) as s_req_admin_add_item;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_admin_add_item m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_item_buy m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_item_buy m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_item_buy)) as s_req_item_buy;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_item_buy m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_player_create_better m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_player_create_better m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_player_create_better)) as s_req_player_create_better;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_player_create_better m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_player_create_better m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_player_create_better m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_player_create_better)) as s_ans_player_create_better;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_player_create_better m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_player_delete m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_player_delete m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_player_delete)) as s_req_player_delete;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_player_delete m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_player_delete m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_player_delete m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_player_delete)) as s_ans_player_delete;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_player_delete m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_echo_to_ug m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_echo_to_ug m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_echo_to_ug)) as s_req_echo_to_ug;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_echo_to_ug m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_echo_from_ug m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_echo_from_ug m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_echo_from_ug)) as s_ans_echo_from_ug;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_echo_from_ug m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_player_create_pitcher m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_player_create_pitcher m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_player_create_pitcher)) as s_req_player_create_pitcher;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_player_create_pitcher m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_player_create_pitcher m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_player_create_pitcher m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_player_create_pitcher)) as s_ans_player_create_pitcher;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_player_create_pitcher m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_ug_error m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_ug_error m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_ug_error)) as s_ans_ug_error;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_ug_error m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_add_tbl_pitcherskill m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_add_tbl_pitcherskill m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_add_tbl_pitcherskill)) as s_req_add_tbl_pitcherskill;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_add_tbl_pitcherskill m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_add_tbl_pitcherskill m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_add_tbl_pitcherskill m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_add_tbl_pitcherskill)) as s_ans_add_tbl_pitcherskill;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_add_tbl_pitcherskill m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_team_create m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_team_create m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_team_create)) as s_req_team_create;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_team_create m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_team_create m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_team_create m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_team_create)) as s_ans_team_create;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_team_create m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_team_delete m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_team_delete m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_team_delete)) as s_req_team_delete;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_team_delete m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_team_delete m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_team_delete m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_team_delete)) as s_ans_team_delete;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_team_delete m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_req_team_select m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_req_team_select m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_req_team_select)) as s_req_team_select;
        }
    }

    public static void Decoding_FromSocketData(ref s_req_team_select m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(s_ans_team_select m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref s_ans_team_select m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(s_ans_team_select)) as s_ans_team_select;
        }
    }

    public static void Decoding_FromSocketData(ref s_ans_team_select m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(UserGateServer_Client m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref UserGateServer_Client m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(UserGateServer_Client)) as UserGateServer_Client;
        }
    }

    public static void Decoding_FromSocketData(ref UserGateServer_Client m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------
    public static byte[] Serialize(Client_UserGateServer m)
    {
        byte[] b = null;
        using (var ms = new MemoryStream())
        {

            ProtoSerializer protoSerializer = new ProtoSerializer();

            protoSerializer.Serialize(ms, m);

            b = new byte[ms.Position];
            var fullB = ms.GetBuffer();
            Array.Copy(fullB, b, b.Length);
        }
        return b;
    }

    public static void Deserialize(ref Client_UserGateServer m, byte[] serializationBytes)
    {
        using (var ms = new MemoryStream(serializationBytes))
        {
            ProtoSerializer protoSerializer = new ProtoSerializer();
            m = protoSerializer.Deserialize(ms, null, typeof(Client_UserGateServer)) as Client_UserGateServer;
        }
    }

    public static void Decoding_FromSocketData(ref Client_UserGateServer m, byte[] socketData)
    {
        int iSize = 0;
        byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        Deserialize(ref m, recvData);
    }
    //----------------------------------------------------------------------------

    //----------------------------------------------------------------------------
    static void CopySerialize(ref UAnsProtocol dest, ref UAnsProtocol src)
    {

        byte[] byte_data = EncodingSize_To_Data(Serialize(src));

        Deserialize( ref dest, byte_data );

    }
    //----------------------------------------------------------------------------
}

