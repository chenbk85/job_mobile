using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
//using System.Collections.Generic;
//using System.Runtime.Serialization;


using System.IO;


using ProtoBuf;

namespace nPROTO{
    
    public partial class gs{

        //---------------------------------------------------------------
        public static byte[] Serialize(GameUserInfo m)
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

        public static void Deserialize(ref GameUserInfo m, byte[] serializationBytes)
        {
            using (var ms = new MemoryStream(serializationBytes))
            {
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(GameUserInfo)) as GameUserInfo;
            }
        }

        public static void Decoding_FromSocketData(ref GameUserInfo m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------------------
        public static byte[] Serialize(GameInfo m)
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

        public static void Deserialize(ref GameInfo m, byte[] serializationBytes)
        {
            using (var ms = new MemoryStream(serializationBytes))
            {
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(GameInfo)) as GameInfo;
            }
        }

        public static void Decoding_FromSocketData(ref GameInfo m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------------------
        public static byte[] Serialize(s_game_play_info m)
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

        public static void Deserialize(ref s_game_play_info m, byte[] serializationBytes)
        {
            using (var ms = new MemoryStream(serializationBytes))
            {
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(s_game_play_info)) as s_game_play_info;
            }
        }

        public static void Decoding_FromSocketData(ref s_game_play_info m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------------------
        public static byte[] Serialize(s_result_round m)
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

        public static void Deserialize(ref s_result_round m, byte[] serializationBytes)
        {
            using (var ms = new MemoryStream(serializationBytes))
            {
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(s_result_round)) as s_result_round;
            }
        }

        public static void Decoding_FromSocketData(ref s_result_round m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------------------
        public static byte[] Serialize(s_result_game m)
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

        public static void Deserialize(ref s_result_game m, byte[] serializationBytes)
        {
            using (var ms = new MemoryStream(serializationBytes))
            {
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(s_result_game)) as s_result_game;
            }
        }

        public static void Decoding_FromSocketData(ref s_result_game m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------------------
        public static byte[] Serialize(GameRoomInfo m)
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

        public static void Deserialize(ref GameRoomInfo m, byte[] serializationBytes)
        {
            using (var ms = new MemoryStream(serializationBytes))
            {
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(GameRoomInfo)) as GameRoomInfo;
            }
        }

        public static void Decoding_FromSocketData(ref GameRoomInfo m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------------------
        public static byte[] Serialize(s_vector3 m)
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

        public static void Deserialize(ref s_vector3 m, byte[] serializationBytes)
        {
            using (var ms = new MemoryStream(serializationBytes))
            {
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(s_vector3)) as s_vector3;
            }
        }

        public static void Decoding_FromSocketData(ref s_vector3 m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------------------
        public static byte[] Serialize(s_vector2 m)
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

        public static void Deserialize(ref s_vector2 m, byte[] serializationBytes)
        {
            using (var ms = new MemoryStream(serializationBytes))
            {
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(s_vector2)) as s_vector2;
            }
        }

        public static void Decoding_FromSocketData(ref s_vector2 m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------------------
        public static byte[] Serialize(s_pitcher_throw_info m)
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

        public static void Deserialize(ref s_pitcher_throw_info m, byte[] serializationBytes)
        {
            using (var ms = new MemoryStream(serializationBytes))
            {
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(s_pitcher_throw_info)) as s_pitcher_throw_info;
            }
        }

        public static void Decoding_FromSocketData(ref s_pitcher_throw_info m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------------------
        public static byte[] Serialize(s_better_hit_info m)
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

        public static void Deserialize(ref s_better_hit_info m, byte[] serializationBytes)
        {
            using (var ms = new MemoryStream(serializationBytes))
            {
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(s_better_hit_info)) as s_better_hit_info;
            }
        }

        public static void Decoding_FromSocketData(ref s_better_hit_info m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------------------
        public static byte[] Serialize(GLReqGameProtocol m)
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

        public static void Deserialize(ref GLReqGameProtocol m, byte[] serializationBytes)
        {
            using (var ms = new MemoryStream(serializationBytes))
            {
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(GLReqGameProtocol)) as GLReqGameProtocol;
            }
        }

        public static void Decoding_FromSocketData(ref GLReqGameProtocol m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------------------
        public static byte[] Serialize(GLAnsGameProtocol m)
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

        public static void Deserialize(ref GLAnsGameProtocol m, byte[] serializationBytes)
        {
            using (var ms = new MemoryStream(serializationBytes))
            {
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(GLAnsGameProtocol)) as GLAnsGameProtocol;
            }
        }

        public static void Decoding_FromSocketData(ref GLAnsGameProtocol m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }

        //---------------------------------------------------------------
        //---------------------------------------------------------------
        //---------------------------------------------------------------

        //BaseballServer_Client

        public static byte[] Serialize(BaseballServer_Client m)
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

        public static void Deserialize(ref BaseballServer_Client m, byte[] serializationBytes)
        {
            using (var ms = new MemoryStream(serializationBytes))
            {
                BaseballClient_proto_Serializer BaseballClient_proto_Serializer = new BaseballClient_proto_Serializer();
                m = BaseballClient_proto_Serializer.Deserialize(ms, null, typeof(BaseballServer_Client)) as BaseballServer_Client;
            }
        }

        public static void Decoding_FromSocketData(ref BaseballServer_Client m, byte[] socketData)
        {
            int iSize = 0;
            byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);

            Deserialize(ref m, recvData);
        }
    }

}