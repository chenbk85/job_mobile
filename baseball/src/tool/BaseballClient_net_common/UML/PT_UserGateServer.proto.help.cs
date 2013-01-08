
// 주의 http://code.google.com/p/protobuf-net/ 를 사용할때 쓰는 핼프코드 

using System; //from ProtocalPrototype.xml : protobuf_net : include_namespace
using System.Collections; //from ProtocalPrototype.xml : protobuf_net : include_namespace
using System.Collections.Generic; //from ProtocalPrototype.xml : protobuf_net : include_namespace
using System.Runtime.Serialization; //from ProtocalPrototype.xml : protobuf_net : include_namespace
using System.IO; //from ProtocalPrototype.xml : protobuf_net : include_namespace
using ProtoBuf; //from ProtocalPrototype.xml : protobuf_net : include_namespace
using nPROTO; //from ProtocalPrototype.xml : protobuf_net : include_namespace
using nEXCEL; //from ProtocalPrototype.xml : protobuf_net : include_namespace

namespace nPROTO
{
    public partial class PT_UserGateServer
	{
//////////////////////////////////////////////////
///#-- ug2x_echo
//////////////////////////////////////////////////
		public static s_ug2x_echo Make_ug2x_echo(Int32 type,string msg,Int32 client_time_msec,Int64 ug_time_msec)
		{
			s_ug2x_echo v = new s_ug2x_echo();
			v.type = type;
			v.msg = msg;
			v.client_time_msec = client_time_msec;
			v.ug_time_msec = ug_time_msec;
			return v;
		}
		public static UserGateServer_Client Build(s_ug2x_echo v)
		{
			UserGateServer_Client v2 = new UserGateServer_Client();
			v2.type = UserGateServer_Client.Type.ug2x_echo;
			v2.m_ug2x_echo = v;
			return v2;
		}
		public static UserGateServer_Client Build_ug2x_echo(Int32 type,string msg,Int32 client_time_msec,Int64 ug_time_msec)
		{
			return Build(Make_ug2x_echo(type,msg,client_time_msec,ug_time_msec));
		}
		public static byte[] Serialize(s_ug2x_echo m)
		{
			byte[] b = null;
			using (var ms = new MemoryStream())
			{
				BaseballClient_proto_Serializer protoSerializer = new BaseballClient_proto_Serializer();
				protoSerializer.Serialize(ms, m);
				b = new byte[ms.Position];
				var fullB = ms.GetBuffer();
				Array.Copy(fullB, b, b.Length);
			}
			return b;
		}
		public static void Deserialize(ref s_ug2x_echo m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ug2x_echo)) as s_ug2x_echo;
			}
		}
		public static void Decoding_FromSocketData(ref s_ug2x_echo m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- ans_ug_error
//////////////////////////////////////////////////
		public static s_ans_ug_error Make_ans_ug_error(Int32 sys_error_id)
		{
			s_ans_ug_error v = new s_ans_ug_error();
			v.sys_error_id = sys_error_id;
			return v;
		}
		public static UserGateServer_Client Build(s_ans_ug_error v)
		{
			UserGateServer_Client v2 = new UserGateServer_Client();
			v2.type = UserGateServer_Client.Type.ans_ug_error;
			v2.m_ans_ug_error = v;
			return v2;
		}
		public static UserGateServer_Client Build_ans_ug_error(Int32 sys_error_id)
		{
			return Build(Make_ans_ug_error(sys_error_id));
		}
		public static byte[] Serialize(s_ans_ug_error m)
		{
			byte[] b = null;
			using (var ms = new MemoryStream())
			{
				BaseballClient_proto_Serializer protoSerializer = new BaseballClient_proto_Serializer();
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
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ans_ug_error)) as s_ans_ug_error;
			}
		}
		public static void Decoding_FromSocketData(ref s_ans_ug_error m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- ug2x_client_version
//////////////////////////////////////////////////
		public static s_ug2x_client_version Make_ug2x_client_version(string version)
		{
			s_ug2x_client_version v = new s_ug2x_client_version();
			v.version = version;
			return v;
		}
		public static UserGateServer_Client Build(s_ug2x_client_version v)
		{
			UserGateServer_Client v2 = new UserGateServer_Client();
			v2.type = UserGateServer_Client.Type.ug2x_client_version;
			v2.m_ug2x_client_version = v;
			return v2;
		}
		public static UserGateServer_Client Build_ug2x_client_version(string version)
		{
			return Build(Make_ug2x_client_version(version));
		}
		public static byte[] Serialize(s_ug2x_client_version m)
		{
			byte[] b = null;
			using (var ms = new MemoryStream())
			{
				BaseballClient_proto_Serializer protoSerializer = new BaseballClient_proto_Serializer();
				protoSerializer.Serialize(ms, m);
				b = new byte[ms.Position];
				var fullB = ms.GetBuffer();
				Array.Copy(fullB, b, b.Length);
			}
			return b;
		}
		public static void Deserialize(ref s_ug2x_client_version m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ug2x_client_version)) as s_ug2x_client_version;
			}
		}
		public static void Decoding_FromSocketData(ref s_ug2x_client_version m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


	}//class PT_UserGateServer


    public partial class PT_UserGateServer
	{
//////////////////////////////////////////////////
///#-- x2ug_echo
//////////////////////////////////////////////////
		public static s_x2ug_echo Make_x2ug_echo(Int32 type,string msg,Int32 client_time_msec)
		{
			s_x2ug_echo v = new s_x2ug_echo();
			v.type = type;
			v.msg = msg;
			v.client_time_msec = client_time_msec;
			return v;
		}
		public static Client_UserGateServer Build(s_x2ug_echo v)
		{
			Client_UserGateServer v2 = new Client_UserGateServer();
			v2.type = Client_UserGateServer.Type.x2ug_echo;
			v2.m_x2ug_echo = v;
			return v2;
		}
		public static Client_UserGateServer Build_x2ug_echo(Int32 type,string msg,Int32 client_time_msec)
		{
			return Build(Make_x2ug_echo(type,msg,client_time_msec));
		}
		public static byte[] Serialize(s_x2ug_echo m)
		{
			byte[] b = null;
			using (var ms = new MemoryStream())
			{
				BaseballClient_proto_Serializer protoSerializer = new BaseballClient_proto_Serializer();
				protoSerializer.Serialize(ms, m);
				b = new byte[ms.Position];
				var fullB = ms.GetBuffer();
				Array.Copy(fullB, b, b.Length);
			}
			return b;
		}
		public static void Deserialize(ref s_x2ug_echo m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_x2ug_echo)) as s_x2ug_echo;
			}
		}
		public static void Decoding_FromSocketData(ref s_x2ug_echo m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- x2ug_get_client_version
//////////////////////////////////////////////////
		public static s_x2ug_get_client_version Make_x2ug_get_client_version(string version)
		{
			s_x2ug_get_client_version v = new s_x2ug_get_client_version();
			v.version = version;
			return v;
		}
		public static Client_UserGateServer Build(s_x2ug_get_client_version v)
		{
			Client_UserGateServer v2 = new Client_UserGateServer();
			v2.type = Client_UserGateServer.Type.x2ug_get_client_version;
			v2.m_x2ug_get_client_version = v;
			return v2;
		}
		public static Client_UserGateServer Build_x2ug_get_client_version(string version)
		{
			return Build(Make_x2ug_get_client_version(version));
		}
		public static byte[] Serialize(s_x2ug_get_client_version m)
		{
			byte[] b = null;
			using (var ms = new MemoryStream())
			{
				BaseballClient_proto_Serializer protoSerializer = new BaseballClient_proto_Serializer();
				protoSerializer.Serialize(ms, m);
				b = new byte[ms.Position];
				var fullB = ms.GetBuffer();
				Array.Copy(fullB, b, b.Length);
			}
			return b;
		}
		public static void Deserialize(ref s_x2ug_get_client_version m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_x2ug_get_client_version)) as s_x2ug_get_client_version;
			}
		}
		public static void Decoding_FromSocketData(ref s_x2ug_get_client_version m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


	}//class PT_UserGateServer


}//namespace nPROTO