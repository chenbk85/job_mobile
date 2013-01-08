using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
//using System.Collections.Generic;
//using System.Runtime.Serialization;


using System.IO;


using ProtoBuf;

namespace nPROTO
{
    public class nTest
    {

        //#--------------------------------------------------------------------------
        // UAnsProtocol
        //#--------------------------------------------------------------------------
        public static byte[] Serialize(UAnsProtocol m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {
                BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
                psz.Serialize(ms, m);
                b = new byte[ms.Position];
                var fullB = ms.GetBuffer();
                Array.Copy(fullB, b, b.Length);
            }
            return b;
        }

        public static byte[] Encoding_ToSocketData(UAnsConnect v)
        {
            UAnsProtocol sendMsg = new UAnsProtocol();
            sendMsg.type = (UAnsProtocol.Type.UANSCONNECT);
            sendMsg.ansConnect = (v);

            byte[] ret0 = Serialize(sendMsg);
            byte[] ret = util.EncodingSize_To_Data(ret0);

            return ret;
        }

        public static UAnsConnect Make_UAnsConnect(Int32 svcID, Int64 gameID, Int32 status, string ip, Int32 port, string passwd)
        {//테스트용 코드.
            UAnsConnect v = new UAnsConnect();
            v.svcID = (svcID);
            v.gameID = (gameID);
            v.status = (status);
            v.ip = (ip);
            v.port = (port);
            v.passwd = (passwd);
            return v;
        }
    }
    public partial class ug
    {
        //#--------------------------------------------------------------------------
        // UReqProtocol
        //#--------------------------------------------------------------------------
        public static byte[] Serialize(UReqProtocol m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {
                BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
                psz.Serialize(ms, m);
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
                BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
                m = psz.Deserialize(ms, null, typeof(UReqProtocol)) as UReqProtocol;
            }
        }
        public static void Decoding_FromSocketData(ref UReqProtocol m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //#--------------------------------------------------------------------------
        // UAnsProtocol
        //#--------------------------------------------------------------------------
        public static byte[] Serialize(UAnsProtocol m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {
                BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
                psz.Serialize(ms, m);
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
                BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
                m = psz.Deserialize(ms, null, typeof(UAnsProtocol)) as UAnsProtocol;
            }
        }
        public static void Decoding_FromSocketData(ref UAnsProtocol m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }



        //#--------------------------------------------------------------------------
        // Client_BaseballServer
        //#--------------------------------------------------------------------------
        public static byte[] Serialize(Client_BaseballServer m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {
                BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
                psz.Serialize(ms, m);
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
                BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
                m = psz.Deserialize(ms, null, typeof(Client_BaseballServer)) as Client_BaseballServer;
            }
        }

        public static void Send(Socket s, nPROTO.Client_BaseballServer v)
        {
            UReqProtocol sendMsg = new UReqProtocol();
            if (sendMsg == null)
            {
                throw new System.Exception("ug.Send sendMsg = new UReqProtocol(); 172");
            }

            sendMsg.type = (UReqProtocol.Type.GLREQGAMEPROTOCOL);
            sendMsg.reqGameProtocol = ug.Serialize(v);

            byte[] sendData2;
            try
            {
                sendData2 = Serialize(sendMsg);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.Send : sendData2 = Serialize(sendMsg); 2");
            }

            if (sendData2 == null)
            {
                throw new System.Exception("ug.Send sendData2 = Serialize(sendMsg); 172");
            }

            byte[] sendOrgData ;
            try
            {
                sendOrgData = util.EncodingSize_To_Data(sendData2);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.Send : util.EncodingSize_To_Data(Serialize(sendMsg)); 2");
            }

            if (sendOrgData == null)
            {
                throw new System.Exception("ug.Send(sendOrgData == null) 172");
            }

            try
            {
                s.Send(sendOrgData);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + " : ug.Send s.Send(sendOrgData); 3");
            }
        }
        public static void Recv(ref nPROTO.BaseballServer_Client v, UAnsProtocol r)
        {
            using (var ms = new MemoryStream(r.ansGameProtocol))
            {
                BaseballClient_proto_Serializer p = new BaseballClient_proto_Serializer();
                try
                {
                    v = p.Deserialize(ms, null, typeof(nPROTO.BaseballServer_Client)) as nPROTO.BaseballServer_Client;
                }
                catch (System.Exception ex)
                {
                    string err = ex.ToString();
                    throw new System.Exception(err + " Recv(ref nPROTO.BaseballServer_Client v, UAnsProtocol r) ");
                }
            }
        }

        //#--------------------------------------------------------------------------
        // Client_UserGateServer
        //#--------------------------------------------------------------------------
        public static byte[] Serialize(Client_UserGateServer m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {
                BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
                psz.Serialize(ms, m);
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
                BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
                m = psz.Deserialize(ms, null, typeof(Client_UserGateServer)) as Client_UserGateServer;
            }
        }

        public static void Send2UG(Socket s, nPROTO.Client_UserGateServer v)
        {
            ReqDB reqDB = new ReqDB();
            reqDB.seq = (0);
            reqDB.query = ("ug_game");
            reqDB.options = Serialize(v);

            UReqProtocol sendMsg = new UReqProtocol();
            sendMsg.type = (UReqProtocol.Type.UREQDB);
            sendMsg.reqDB = (reqDB);

            byte[] buf11;
            byte[] buf12;

            try
            {
                buf11 = Serialize(sendMsg);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.Send2UG :1 ");
            }
            if (buf11== null)
            {
                throw new System.Exception("ug.Send2UG 11");
            }

            try
            {
                buf12 = util.EncodingSize_To_Data(buf11);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.Send2UG :2 ");
            }
            if (buf12 == null)
            {
                throw new System.Exception("ug.Send2UG 12");
            }
            try
            {
                s.Send(buf12);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.Send2UG :3 ");

            }
        }


        //#--------------------------------------------------------------------------
        // Client_DB
        //#--------------------------------------------------------------------------
        public static void Send(Socket s, ReqDB v)
        {
            UReqProtocol sendMsg = new UReqProtocol();
            sendMsg.type = (UReqProtocol.Type.UREQDB);
            sendMsg.reqDB = (v);

            byte[] buf11;
            byte[] buf12;

            try
            {
                buf11 = Serialize(sendMsg);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.ReqDB :1 ");
            }
            if (buf11 == null)
            {
                throw new System.Exception("ug.ReqDB 11");
            }

            try
            {
                buf12 = util.EncodingSize_To_Data(buf11);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.ReqDB :2 ");
            }
            if (buf12 == null)
            {
                throw new System.Exception("ug.ReqDB 12");
            }
            try
            {
                s.Send(buf12);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.ReqDB :3 ");

            }
        }
        public static DBIn Make_DBIn(DBIn.Type type, string val)
        {
            DBIn v = new DBIn();
            v.type = type;
            v.val = val;
            return v;
        }

        public static ReqDB Make_UReqGameInfo(Int32 iSeq, string szTable)
        {
            string sREQ = "GameInfo." + szTable;

            ReqDB v = new ReqDB();
            v.seq = (iSeq);
            v.query = (sREQ);
            v._params.Add(Make_DBIn(DBIn.Type.INT, "0"));
            return v;
        }

        public static ReqDB Make_UReqGameInfo(Int32 iSeq, string szQuery, int iNextIndex)
        {

            ReqDB v = new ReqDB();
            v.seq = (iSeq);
            v.query = (szQuery);
            v._params.Add(Make_DBIn(DBIn.Type.INT, iNextIndex.ToString()));

            return v;
        }

        //#--------------------------------------------------------------------------
        // UReqInfo
        //#--------------------------------------------------------------------------
        public static UReqInfo Make_UReqInfo()
        {
            UReqInfo v = new UReqInfo();
            return v;
        }

        public static void Send(Socket s, UReqInfo v)
        {
            UReqProtocol sendMsg = new UReqProtocol();
            sendMsg.type = (UReqProtocol.Type.UREQINFO);
            sendMsg.reqInfo = (v);

            //s.Send(util.EncodingSize_To_Data(Serialize(sendMsg)));
            byte[] buf11;
            byte[] buf12;

            try
            {
                buf11 = Serialize(sendMsg);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqInfo :1 ");
            }
            if (buf11 == null)
            {
                throw new System.Exception("ug.UReqInfo 11");
            }

            try
            {
                buf12 = util.EncodingSize_To_Data(buf11);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqInfo :2 ");
            }
            if (buf12 == null)
            {
                throw new System.Exception("ug.UReqInfo 12");
            }
            try
            {
                s.Send(buf12);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqInfo :3 ");

            }
        }

        public static UReqPong Make_UReqPong(int iSeq)
        {
            UReqPong v = new UReqPong();
            v.seq = (iSeq);
            return v;
        }

        public static void Send(Socket s, UReqPong v)
        {
            UReqProtocol sendMsg = new UReqProtocol();
            sendMsg.type = (UReqProtocol.Type.UREQPONG);
            sendMsg.reqPong = (v);

            //s.Send(util.EncodingSize_To_Data(Serialize(sendMsg)));
                        byte[] buf11;
            byte[] buf12;

            try
            {
                buf11 = Serialize(sendMsg);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqPong :1 ");
            }
            if (buf11 == null)
            {
                throw new System.Exception("ug.UReqPong 11");
            }

            try
            {
                buf12 = util.EncodingSize_To_Data(buf11);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqPong :2 ");
            }
            if (buf12 == null)
            {
                throw new System.Exception("ug.UReqPong 12");
            }
            try
            {
                s.Send(buf12);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqPong :3 ");

            }
        }

        //#--------------------------------------------------------------------------
        // UReqChannel
        //#--------------------------------------------------------------------------
        public static void Send(Socket s, UReqChannel v)
        {
            UReqProtocol sendMsg = new UReqProtocol();
            sendMsg.type = (UReqProtocol.Type.UREQCHANNEL);
            sendMsg.reqChannel = (v);

           // s.Send(util.EncodingSize_To_Data(Serialize(sendMsg)));
            byte[] buf11;
            byte[] buf12;

            try
            {
                buf11 = Serialize(sendMsg);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqChannel :1 ");
            }
            if (buf11 == null)
            {
                throw new System.Exception("ug.UReqChannel 11");
            }

            try
            {
                buf12 = util.EncodingSize_To_Data(buf11);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqChannel :2 ");
            }
            if (buf12 == null)
            {
                throw new System.Exception("ug.UReqChannel 12");
            }
            try
            {
                s.Send(buf12);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqChannel :3 ");

            }
        }

        public static UReqChannel Make_UReqChannel()
        {
            UReqChannel v = new UReqChannel();
            return v;
        }

        //#--------------------------------------------------------------------------
        // UReqNotice
        //#--------------------------------------------------------------------------
        public static void Send(Socket s, UReqNotice v)
        {
            UReqProtocol sendMsg = new UReqProtocol();
            sendMsg.type = (UReqProtocol.Type.UREQNOTICE);
            sendMsg.reqNotice = (v);

            //s.Send(util.EncodingSize_To_Data(Serialize(sendMsg)));
            byte[] buf11;
            byte[] buf12;

            try
            {
                buf11 = Serialize(sendMsg);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqNotice :1 ");
            }
            if (buf11 == null)
            {
                throw new System.Exception("ug.UReqNotice 11");
            }

            try
            {
                buf12 = util.EncodingSize_To_Data(buf11);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqNotice :2 ");
            }
            if (buf12 == null)
            {
                throw new System.Exception("ug.UReqNotice 12");
            }
            try
            {
                s.Send(buf12);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqNotice :3 ");

            }
        }

        public static UReqNotice Make_UReqNotice()
        {
            UReqNotice v = new UReqNotice();
            return v;
        }


        //#--------------------------------------------------------------------------
        // UReqAutoJoin
        //#--------------------------------------------------------------------------
        public static void Send(Socket s, UReqAutoJoin v)
        {
            UReqProtocol sendMsg = new UReqProtocol();
            sendMsg.type = (UReqProtocol.Type.UREQAUTOJOIN);
            sendMsg.reqAutoJoin = (v);

            //s.Send(util.EncodingSize_To_Data(Serialize(sendMsg)));
            byte[] buf11;
            byte[] buf12;

            try
            {
                buf11 = Serialize(sendMsg);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqAutoJoin :1 ");
            }
            if (buf11 == null)
            {
                throw new System.Exception("ug.UReqAutoJoin 11");
            }

            try
            {
                buf12 = util.EncodingSize_To_Data(buf11);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqAutoJoin :2 ");
            }
            if (buf12 == null)
            {
                throw new System.Exception("ug.UReqAutoJoin 12");
            }
            try
            {
                s.Send(buf12);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqAutoJoin :3 ");

            }
        }
        public static UReqAutoJoin Make_UReqAutoJoin(Int32 categoryID, Int32 channelID)
        {
            UReqAutoJoin v = new UReqAutoJoin();
            v.categoryID = (categoryID);
            v.channelID = (channelID);
            return v;
        }

        //#--------------------------------------------------------------------------
        // UReqConnect
        //#--------------------------------------------------------------------------
        public static void Send(Socket s, UReqConnect v)
        {
            UReqProtocol sendMsg = new UReqProtocol();
            sendMsg.reqConnect = (v);
            sendMsg.type = (UReqProtocol.Type.UREQCONNECT);
            //s.Send(util.EncodingSize_To_Data(Serialize(sendMsg)));
            byte[] buf11;
            byte[] buf12;

            try
            {
                buf11 = Serialize(sendMsg);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqConnect :1 ");
            }
            if (buf11 == null)
            {
                throw new System.Exception("ug.UReqConnect 11");
            }

            try
            {
                buf12 = util.EncodingSize_To_Data(buf11);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqConnect :2 ");
            }
            if (buf12 == null)
            {
                throw new System.Exception("ug.UReqConnect 12");
            }
            try
            {
                s.Send(buf12);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqConnect :3 ");

            }
        }

        public static UReqConnect Make_UReqConnect(Int32 svcID, Int64 gameID, Int32 lastCloseTime, Version version, MemberInfo memberInfo)
        {
            UReqConnect v = new UReqConnect();
           v.svcID = (svcID);
           v.gameID = (gameID);
           v.lastCloseTime = (lastCloseTime);
           v.version = (version);
           v.memberInfo = (memberInfo);
            return v;
        }



        //#--------------------------------------------------------------------------
        // UReqClose
        //#--------------------------------------------------------------------------
        public static UReqClose Make_UReqClose()
        {
            UReqClose v = new UReqClose();
            return v;
        }

        public static void Send(Socket s, UReqClose v)
        {
            UReqProtocol sendMsg = new UReqProtocol();
            sendMsg.type = (UReqProtocol.Type.UREQCLOSE);
            sendMsg.reqClose = (v);

            //s.Send(util.EncodingSize_To_Data(Serialize(sendMsg)));
            byte[] buf11;
            byte[] buf12;

            try
            {
                buf11 = Serialize(sendMsg);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqClose :1 ");
            }
            if (buf11 == null)
            {
                throw new System.Exception("ug.UReqClose 11");
            }

            try
            {
                buf12 = util.EncodingSize_To_Data(buf11);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqClose :2 ");
            }
            if (buf12 == null)
            {
                throw new System.Exception("ug.UReqClose 12");
            }
            try
            {
                s.Send(buf12);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqClose :3 ");

            }
        }


        //#--------------------------------------------------------------------------
        // 유틸 코드들.
        //#--------------------------------------------------------------------------

        public static MemberInfo Make_MemberInfo(Int64 game_id, string avatar_url, string nick_name, bool gender_option)
        {
            MemberInfo v = new MemberInfo();
            v.game_id = (game_id);
            v.avatar_url = (avatar_url);
            v.nick_name = (nick_name);
            v.gender_option = (gender_option);
            return v;
        }

        const int SVNVERSION = 270; //t:\svn\msg\src\svn_version.hpp를 참조하시오.
        const int BASE_BALL_GATEWAY_VERSION = 1234;// T:\svn\baseball\MOB_lib\DBHelper.h의 #define BASE_BALL_GATEWAY_VERSION 1234와 동일.

        public static Version Make_Version()
        {
            Version v = new Version();
            v.framework = (SVNVERSION);
            v.service = (BASE_BALL_GATEWAY_VERSION);
            return v;
        }

        public static UReqLeaveGame Make_UReqLeaveGame(Int64 game_id, bool is_kick)
        {
            UReqLeaveGame v = new UReqLeaveGame();
            v.gameID = (game_id);
            v.kick = (is_kick);
            return v;
        }

        //#--------------------------------------------------------------------------
        // UReqLeaveGame
        //#--------------------------------------------------------------------------
        public static void Send(Socket s, UReqLeaveGame v)
        {
            UReqProtocol sendMsg = new UReqProtocol();

            sendMsg.type = (UReqProtocol.Type.UREQLEAVEGAME);
            sendMsg.reqLeaveGame = (v);
            //s.Send(nPROTO.util.EncodingSize_To_Data(Serialize(sendMsg)));
            byte[] buf11;
            byte[] buf12;

            try
            {
                buf11 = Serialize(sendMsg);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqLeaveGame :1 ");
            }
            if (buf11 == null)
            {
                throw new System.Exception("ug.UReqLeaveGame 11");
            }

            try
            {
                buf12 = util.EncodingSize_To_Data(buf11);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqLeaveGame :2 ");
            }
            if (buf12 == null)
            {
                throw new System.Exception("ug.UReqLeaveGame 12");
            }
            try
            {
                s.Send(buf12);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + ": ug.UReqLeaveGame :3 ");

            }
        }
        public static UAnsProtocol Recv_UAnsProtocol(Socket s)
        {
            byte[] recvBuff = new byte[2048];
            try
            {
                s.Receive(recvBuff);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + " Recv_UAnsProtocol ");
            }

            UAnsProtocol ans = new UAnsProtocol();

            try
            {
                Decoding_FromSocketData(ref ans, recvBuff);
            }
            catch (System.Exception ex)
            {
                string err = ex.ToString();
                throw new System.Exception(err + " Recv_UAnsProtocol 2");
            }
            
            return ans;
        }

        //---------------------------------------------------

        public static byte[] Serialize(Error m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                BaseballClient_proto_Serializer.Serialize(ms, m);
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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(Error)) as Error;
            }
        }

        public static void Decoding_FromSocketData(ref Error m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(Desc m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(Desc)) as Desc;
            }
        }

        public static void Decoding_FromSocketData(ref Desc m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(Notice m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(Notice)) as Notice;
            }
        }

        public static void Decoding_FromSocketData(ref Notice m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UError m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UError)) as UError;
            }
        }

        public static void Decoding_FromSocketData(ref UError m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UReqConnect m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UReqConnect)) as UReqConnect;
            }
        }

        public static void Decoding_FromSocketData(ref UReqConnect m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UAnsConnect m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UAnsConnect)) as UAnsConnect;
            }
        }

        public static void Decoding_FromSocketData(ref UAnsConnect m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UReqNotice m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UReqNotice)) as UReqNotice;
            }
        }

        public static void Decoding_FromSocketData(ref UReqNotice m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UAnsNotice m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UAnsNotice)) as UAnsNotice;
            }
        }

        public static void Decoding_FromSocketData(ref UAnsNotice m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UReqChannel m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UReqChannel)) as UReqChannel;
            }
        }

        public static void Decoding_FromSocketData(ref UReqChannel m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UAnsChannel m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UAnsChannel)) as UAnsChannel;
            }
        }

        public static void Decoding_FromSocketData(ref UAnsChannel m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UErrChannel m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UErrChannel)) as UErrChannel;
            }
        }

        public static void Decoding_FromSocketData(ref UErrChannel m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UReqStore m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UReqStore)) as UReqStore;
            }
        }

        public static void Decoding_FromSocketData(ref UReqStore m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UAnsStore m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UAnsStore)) as UAnsStore;
            }
        }

        public static void Decoding_FromSocketData(ref UAnsStore m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UReqInfo m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UReqInfo)) as UReqInfo;
            }
        }

        public static void Decoding_FromSocketData(ref UReqInfo m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UAnsInfo m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UAnsInfo)) as UAnsInfo;
            }
        }

        public static void Decoding_FromSocketData(ref UAnsInfo m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UReqAutoJoin m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UReqAutoJoin)) as UReqAutoJoin;
            }
        }

        public static void Decoding_FromSocketData(ref UReqAutoJoin m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UAnsAutoJoin m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UAnsAutoJoin)) as UAnsAutoJoin;
            }
        }

        public static void Decoding_FromSocketData(ref UAnsAutoJoin m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UReqLeaveGame m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UReqLeaveGame)) as UReqLeaveGame;
            }
        }

        public static void Decoding_FromSocketData(ref UReqLeaveGame m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UAnsLeaveGame m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UAnsLeaveGame)) as UAnsLeaveGame;
            }
        }

        public static void Decoding_FromSocketData(ref UAnsLeaveGame m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UReqClose m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UReqClose)) as UReqClose;
            }
        }

        public static void Decoding_FromSocketData(ref UReqClose m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UAnsClose m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UAnsClose)) as UAnsClose;
            }
        }

        public static void Decoding_FromSocketData(ref UAnsClose m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UReqPong m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UReqPong)) as UReqPong;
            }
        }

        public static void Decoding_FromSocketData(ref UReqPong m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UAnsPing m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UAnsPing)) as UAnsPing;
            }
        }

        public static void Decoding_FromSocketData(ref UAnsPing m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UReqPlug m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UReqPlug)) as UReqPlug;
            }
        }

        public static void Decoding_FromSocketData(ref UReqPlug m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        public static byte[] Serialize(UAnsPlug m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UAnsPlug)) as UAnsPlug;
            }
        }

        public static void Decoding_FromSocketData(ref UAnsPlug m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------

        //public static byte[] Serialize(UReqProtocol m)
        //{
        //    byte[] b = null;
        //    using (var ms = new MemoryStream())
        //    {

        //        BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

        //        BaseballClient_proto_Serializer.Serialize(ms, m);

        //        b = new byte[ms.Position];
        //        var fullB = ms.GetBuffer();
        //        Array.Copy(fullB, b, b.Length);
        //    }
        //    return b;
        //}

        //public static void Deserialize(ref UReqProtocol m, byte[] serializationBytes)
        //{
        //    using (var ms = new MemoryStream(serializationBytes))
        //    {
        //        BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
        //        m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UReqProtocol)) as UReqProtocol;
        //    }
        //}

        //public static void Decoding_FromSocketData(ref UReqProtocol m, byte[] socketData)
        //{
        //    int iSize = 0;
        //    byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        //    Deserialize(ref m, recvData);
        //}

        //---------------------------------------------------

        //public static byte[] Serialize(UAnsProtocol m)
        //{
        //    byte[] b = null;
        //    using (var ms = new MemoryStream())
        //    {

        //        BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

        //        BaseballClient_proto_Serializer.Serialize(ms, m);

        //        b = new byte[ms.Position];
        //        var fullB = ms.GetBuffer();
        //        Array.Copy(fullB, b, b.Length);
        //    }
        //    return b;
        //}

        //public static void Deserialize(ref UAnsProtocol m, byte[] serializationBytes)
        //{
        //    using (var ms = new MemoryStream(serializationBytes))
        //    {
        //        BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
        //        m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UAnsProtocol)) as UAnsProtocol;
        //    }
        //}

        //public static void Decoding_FromSocketData(ref UAnsProtocol m, byte[] socketData)
        //{
        //    int iSize = 0;
        //    byte[] recvData = DecodingSize_From_Data(ref iSize, socketData);

        //    Deserialize(ref m, recvData);
        //}

        //---------------------------------------------------

        public static byte[] Serialize(MemberInfo m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(MemberInfo)) as MemberInfo;
            }
        }

        public static void Decoding_FromSocketData(ref MemberInfo m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------
        //UserGateServer_Client

        public static byte[] Serialize(UserGateServer_Client m)
        {
            byte[] b = null;
            using (var ms = new MemoryStream())
            {

                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();

                BaseballClient_proto_Serializer.Serialize(ms, m);

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
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(UserGateServer_Client)) as UserGateServer_Client;
            }
        }

        public static void Decoding_FromSocketData(ref UserGateServer_Client m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------


    }//public class util

}//namespace nPROTO


