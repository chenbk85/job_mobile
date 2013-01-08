
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
    public partial class PT_BaseballServer
	{
//////////////////////////////////////////////////
///#-- bs2ug_set_cvar
//////////////////////////////////////////////////
		public static s_bs2ug_set_cvar Make_bs2ug_set_cvar(string name,string val)
		{
			s_bs2ug_set_cvar v = new s_bs2ug_set_cvar();
			v.name = name;
			v.val = val;
			return v;
		}
		public static BaseballServer_UserGateServer Build(s_bs2ug_set_cvar v)
		{
			BaseballServer_UserGateServer v2 = new BaseballServer_UserGateServer();
			v2.type = BaseballServer_UserGateServer.Type.bs2ug_set_cvar;
			v2.m_bs2ug_set_cvar = v;
			return v2;
		}
		public static BaseballServer_UserGateServer Build_bs2ug_set_cvar(string name,string val)
		{
			return Build(Make_bs2ug_set_cvar(name,val));
		}
		public static byte[] Serialize(s_bs2ug_set_cvar m)
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
		public static void Deserialize(ref s_bs2ug_set_cvar m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_bs2ug_set_cvar)) as s_bs2ug_set_cvar;
			}
		}
		public static void Decoding_FromSocketData(ref s_bs2ug_set_cvar m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- bs2ug_game_end
//////////////////////////////////////////////////
		public static s_bs2ug_game_end Make_bs2ug_game_end(s_result_game rg,bool is_better,List<s_result_round> rr)
		{
			s_bs2ug_game_end v = new s_bs2ug_game_end();
			v.rg = rg;
			v.is_better = is_better;
			v.rr = rr;
			return v;
		}
		public static BaseballServer_UserGateServer Build(s_bs2ug_game_end v)
		{
			BaseballServer_UserGateServer v2 = new BaseballServer_UserGateServer();
			v2.type = BaseballServer_UserGateServer.Type.bs2ug_game_end;
			v2.m_bs2ug_game_end = v;
			return v2;
		}
		public static BaseballServer_UserGateServer Build_bs2ug_game_end(s_result_game rg,bool is_better,List<s_result_round> rr)
		{
			return Build(Make_bs2ug_game_end(rg,is_better,rr));
		}
		public static byte[] Serialize(s_bs2ug_game_end m)
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
		public static void Deserialize(ref s_bs2ug_game_end m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_bs2ug_game_end)) as s_bs2ug_game_end;
			}
		}
		public static void Decoding_FromSocketData(ref s_bs2ug_game_end m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- bs2ug_echo
//////////////////////////////////////////////////
		public static s_bs2ug_echo Make_bs2ug_echo(Int32 type,string msg,Int64 bs_time_msec,Int64 ug_time_msec)
		{
			s_bs2ug_echo v = new s_bs2ug_echo();
			v.type = type;
			v.msg = msg;
			v.bs_time_msec = bs_time_msec;
			v.ug_time_msec = ug_time_msec;
			return v;
		}
		public static BaseballServer_UserGateServer Build(s_bs2ug_echo v)
		{
			BaseballServer_UserGateServer v2 = new BaseballServer_UserGateServer();
			v2.type = BaseballServer_UserGateServer.Type.bs2ug_echo;
			v2.m_bs2ug_echo = v;
			return v2;
		}
		public static BaseballServer_UserGateServer Build_bs2ug_echo(Int32 type,string msg,Int64 bs_time_msec,Int64 ug_time_msec)
		{
			return Build(Make_bs2ug_echo(type,msg,bs_time_msec,ug_time_msec));
		}
		public static byte[] Serialize(s_bs2ug_echo m)
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
		public static void Deserialize(ref s_bs2ug_echo m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_bs2ug_echo)) as s_bs2ug_echo;
			}
		}
		public static void Decoding_FromSocketData(ref s_bs2ug_echo m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- bs2ug_error
//////////////////////////////////////////////////
		public static s_bs2ug_error Make_bs2ug_error(Int32 sys_error_id)
		{
			s_bs2ug_error v = new s_bs2ug_error();
			v.sys_error_id = sys_error_id;
			return v;
		}
		public static BaseballServer_UserGateServer Build(s_bs2ug_error v)
		{
			BaseballServer_UserGateServer v2 = new BaseballServer_UserGateServer();
			v2.type = BaseballServer_UserGateServer.Type.bs2ug_error;
			v2.m_bs2ug_error = v;
			return v2;
		}
		public static BaseballServer_UserGateServer Build_bs2ug_error(Int32 sys_error_id)
		{
			return Build(Make_bs2ug_error(sys_error_id));
		}
		public static byte[] Serialize(s_bs2ug_error m)
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
		public static void Deserialize(ref s_bs2ug_error m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_bs2ug_error)) as s_bs2ug_error;
			}
		}
		public static void Decoding_FromSocketData(ref s_bs2ug_error m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- bs2ug_add_discon_tot
//////////////////////////////////////////////////
		public static s_bs2ug_add_discon_tot Make_bs2ug_add_discon_tot(Int64 discon_uid)
		{
			s_bs2ug_add_discon_tot v = new s_bs2ug_add_discon_tot();
			v.discon_uid = discon_uid;
			return v;
		}
		public static BaseballServer_UserGateServer Build(s_bs2ug_add_discon_tot v)
		{
			BaseballServer_UserGateServer v2 = new BaseballServer_UserGateServer();
			v2.type = BaseballServer_UserGateServer.Type.bs2ug_add_discon_tot;
			v2.m_bs2ug_add_discon_tot = v;
			return v2;
		}
		public static BaseballServer_UserGateServer Build_bs2ug_add_discon_tot(Int64 discon_uid)
		{
			return Build(Make_bs2ug_add_discon_tot(discon_uid));
		}
		public static byte[] Serialize(s_bs2ug_add_discon_tot m)
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
		public static void Deserialize(ref s_bs2ug_add_discon_tot m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_bs2ug_add_discon_tot)) as s_bs2ug_add_discon_tot;
			}
		}
		public static void Decoding_FromSocketData(ref s_bs2ug_add_discon_tot m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


	}//class PT_BaseballServer


    public partial class PT_BaseballServer
	{
//////////////////////////////////////////////////
///#-- ans_join_room
//////////////////////////////////////////////////
		public static s_ans_join_room Make_ans_join_room(GameRoomInfo gri)
		{
			s_ans_join_room v = new s_ans_join_room();
			v.gri = gri;
			return v;
		}
		public static BaseballServer_Client Build(s_ans_join_room v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.ans_join_room;
			v2.m_ans_join_room = v;
			return v2;
		}
		public static BaseballServer_Client Build_ans_join_room(GameRoomInfo gri)
		{
			return Build(Make_ans_join_room(gri));
		}
		public static byte[] Serialize(s_ans_join_room m)
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
		public static void Deserialize(ref s_ans_join_room m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ans_join_room)) as s_ans_join_room;
			}
		}
		public static void Decoding_FromSocketData(ref s_ans_join_room m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- ans_room_state
//////////////////////////////////////////////////
		public static s_ans_room_state Make_ans_room_state(GameRoomInfo gri)
		{
			s_ans_room_state v = new s_ans_room_state();
			v.gri = gri;
			return v;
		}
		public static BaseballServer_Client Build(s_ans_room_state v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.ans_room_state;
			v2.m_ans_room_state = v;
			return v2;
		}
		public static BaseballServer_Client Build_ans_room_state(GameRoomInfo gri)
		{
			return Build(Make_ans_room_state(gri));
		}
		public static byte[] Serialize(s_ans_room_state m)
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
		public static void Deserialize(ref s_ans_room_state m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ans_room_state)) as s_ans_room_state;
			}
		}
		public static void Decoding_FromSocketData(ref s_ans_room_state m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- bs2x_echo
//////////////////////////////////////////////////
		public static s_bs2x_echo Make_bs2x_echo(Int32 type,string msg,Int32 client_time_msec,Int64 bs_time_msec)
		{
			s_bs2x_echo v = new s_bs2x_echo();
			v.type = type;
			v.msg = msg;
			v.client_time_msec = client_time_msec;
			v.bs_time_msec = bs_time_msec;
			return v;
		}
		public static BaseballServer_Client Build(s_bs2x_echo v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.bs2x_echo;
			v2.m_bs2x_echo = v;
			return v2;
		}
		public static BaseballServer_Client Build_bs2x_echo(Int32 type,string msg,Int32 client_time_msec,Int64 bs_time_msec)
		{
			return Build(Make_bs2x_echo(type,msg,client_time_msec,bs_time_msec));
		}
		public static byte[] Serialize(s_bs2x_echo m)
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
		public static void Deserialize(ref s_bs2x_echo m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_bs2x_echo)) as s_bs2x_echo;
			}
		}
		public static void Decoding_FromSocketData(ref s_bs2x_echo m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- ans_chat
//////////////////////////////////////////////////
		public static s_ans_chat Make_ans_chat(Int32 type,string msg,string etc)
		{
			s_ans_chat v = new s_ans_chat();
			v.type = type;
			v.msg = msg;
			v.etc = etc;
			return v;
		}
		public static BaseballServer_Client Build(s_ans_chat v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.ans_chat;
			v2.m_ans_chat = v;
			return v2;
		}
		public static BaseballServer_Client Build_ans_chat(Int32 type,string msg,string etc)
		{
			return Build(Make_ans_chat(type,msg,etc));
		}
		public static byte[] Serialize(s_ans_chat m)
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
		public static void Deserialize(ref s_ans_chat m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ans_chat)) as s_ans_chat;
			}
		}
		public static void Decoding_FromSocketData(ref s_ans_chat m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- ans_timer_start
//////////////////////////////////////////////////
		public static s_ans_timer_start Make_ans_timer_start(Int32 count,string msg)
		{
			s_ans_timer_start v = new s_ans_timer_start();
			v.count = count;
			v.msg = msg;
			return v;
		}
		public static BaseballServer_Client Build(s_ans_timer_start v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.ans_timer_start;
			v2.m_ans_timer_start = v;
			return v2;
		}
		public static BaseballServer_Client Build_ans_timer_start(Int32 count,string msg)
		{
			return Build(Make_ans_timer_start(count,msg));
		}
		public static byte[] Serialize(s_ans_timer_start m)
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
		public static void Deserialize(ref s_ans_timer_start m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ans_timer_start)) as s_ans_timer_start;
			}
		}
		public static void Decoding_FromSocketData(ref s_ans_timer_start m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- bs2x_echo2
//////////////////////////////////////////////////
		public static s_bs2x_echo2 Make_bs2x_echo2(Int32 type,string msg,Int32 client_time_msec,Int64 bs_time_msec,Int32 etc)
		{
			s_bs2x_echo2 v = new s_bs2x_echo2();
			v.type = type;
			v.msg = msg;
			v.client_time_msec = client_time_msec;
			v.bs_time_msec = bs_time_msec;
			v.etc = etc;
			return v;
		}
		public static BaseballServer_Client Build(s_bs2x_echo2 v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.bs2x_echo2;
			v2.m_bs2x_echo2 = v;
			return v2;
		}
		public static BaseballServer_Client Build_bs2x_echo2(Int32 type,string msg,Int32 client_time_msec,Int64 bs_time_msec,Int32 etc)
		{
			return Build(Make_bs2x_echo2(type,msg,client_time_msec,bs_time_msec,etc));
		}
		public static byte[] Serialize(s_bs2x_echo2 m)
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
		public static void Deserialize(ref s_bs2x_echo2 m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_bs2x_echo2)) as s_bs2x_echo2;
			}
		}
		public static void Decoding_FromSocketData(ref s_bs2x_echo2 m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- ans_bs_error
//////////////////////////////////////////////////
		public static s_ans_bs_error Make_ans_bs_error(Int32 sys_error_id)
		{
			s_ans_bs_error v = new s_ans_bs_error();
			v.sys_error_id = sys_error_id;
			return v;
		}
		public static BaseballServer_Client Build(s_ans_bs_error v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.ans_bs_error;
			v2.m_ans_bs_error = v;
			return v2;
		}
		public static BaseballServer_Client Build_ans_bs_error(Int32 sys_error_id)
		{
			return Build(Make_ans_bs_error(sys_error_id));
		}
		public static byte[] Serialize(s_ans_bs_error m)
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
		public static void Deserialize(ref s_ans_bs_error m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ans_bs_error)) as s_ans_bs_error;
			}
		}
		public static void Decoding_FromSocketData(ref s_ans_bs_error m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- bs2x_auto_match_ready2
//////////////////////////////////////////////////
		public static s_bs2x_auto_match_ready2 Make_bs2x_auto_match_ready2(Int64 uid,Int32 batter,Int32 pitcher,Int32 other_batter,Int32 other_pitcher)
		{
			s_bs2x_auto_match_ready2 v = new s_bs2x_auto_match_ready2();
			v.uid = uid;
			v.batter = batter;
			v.pitcher = pitcher;
			v.other_batter = other_batter;
			v.other_pitcher = other_pitcher;
			return v;
		}
		public static BaseballServer_Client Build(s_bs2x_auto_match_ready2 v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.bs2x_auto_match_ready2;
			v2.m_bs2x_auto_match_ready2 = v;
			return v2;
		}
		public static BaseballServer_Client Build_bs2x_auto_match_ready2(Int64 uid,Int32 batter,Int32 pitcher,Int32 other_batter,Int32 other_pitcher)
		{
			return Build(Make_bs2x_auto_match_ready2(uid,batter,pitcher,other_batter,other_pitcher));
		}
		public static byte[] Serialize(s_bs2x_auto_match_ready2 m)
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
		public static void Deserialize(ref s_bs2x_auto_match_ready2 m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_bs2x_auto_match_ready2)) as s_bs2x_auto_match_ready2;
			}
		}
		public static void Decoding_FromSocketData(ref s_bs2x_auto_match_ready2 m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- ans_game_start
//////////////////////////////////////////////////
		public static s_ans_game_start Make_ans_game_start(Int64 attack_user,Int32 sid_Sys_Runner_State,Int32 baseball_park)
		{
			s_ans_game_start v = new s_ans_game_start();
			v.attack_user = attack_user;
			v.sid_Sys_Runner_State = sid_Sys_Runner_State;
			v.baseball_park = baseball_park;
			return v;
		}
		public static BaseballServer_Client Build(s_ans_game_start v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.ans_game_start;
			v2.m_ans_game_start = v;
			return v2;
		}
		public static BaseballServer_Client Build_ans_game_start(Int64 attack_user,Int32 sid_Sys_Runner_State,Int32 baseball_park)
		{
			return Build(Make_ans_game_start(attack_user,sid_Sys_Runner_State,baseball_park));
		}
		public static byte[] Serialize(s_ans_game_start m)
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
		public static void Deserialize(ref s_ans_game_start m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ans_game_start)) as s_ans_game_start;
			}
		}
		public static void Decoding_FromSocketData(ref s_ans_game_start m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- ans_game_round_start
//////////////////////////////////////////////////
		public static s_ans_game_round_start Make_ans_game_round_start(Int32 round,Int32 runner_state)
		{
			s_ans_game_round_start v = new s_ans_game_round_start();
			v.round = round;
			v.runner_state = runner_state;
			return v;
		}
		public static BaseballServer_Client Build(s_ans_game_round_start v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.ans_game_round_start;
			v2.m_ans_game_round_start = v;
			return v2;
		}
		public static BaseballServer_Client Build_ans_game_round_start(Int32 round,Int32 runner_state)
		{
			return Build(Make_ans_game_round_start(round,runner_state));
		}
		public static byte[] Serialize(s_ans_game_round_start m)
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
		public static void Deserialize(ref s_ans_game_round_start m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ans_game_round_start)) as s_ans_game_round_start;
			}
		}
		public static void Decoding_FromSocketData(ref s_ans_game_round_start m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- bs2x_match_ready
//////////////////////////////////////////////////
		public static s_bs2x_match_ready Make_bs2x_match_ready(Int64 uid)
		{
			s_bs2x_match_ready v = new s_bs2x_match_ready();
			v.uid = uid;
			return v;
		}
		public static BaseballServer_Client Build(s_bs2x_match_ready v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.bs2x_match_ready;
			v2.m_bs2x_match_ready = v;
			return v2;
		}
		public static BaseballServer_Client Build_bs2x_match_ready(Int64 uid)
		{
			return Build(Make_bs2x_match_ready(uid));
		}
		public static byte[] Serialize(s_bs2x_match_ready m)
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
		public static void Deserialize(ref s_bs2x_match_ready m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_bs2x_match_ready)) as s_bs2x_match_ready;
			}
		}
		public static void Decoding_FromSocketData(ref s_bs2x_match_ready m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- ans_pitcher_throw
//////////////////////////////////////////////////
		public static s_ans_pitcher_throw Make_ans_pitcher_throw(s_pitcher_throw_info info,bool is_auto)
		{
			s_ans_pitcher_throw v = new s_ans_pitcher_throw();
			v.info = info;
			v.is_auto = is_auto;
			return v;
		}
		public static BaseballServer_Client Build(s_ans_pitcher_throw v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.ans_pitcher_throw;
			v2.m_ans_pitcher_throw = v;
			return v2;
		}
		public static BaseballServer_Client Build_ans_pitcher_throw(s_pitcher_throw_info info,bool is_auto)
		{
			return Build(Make_ans_pitcher_throw(info,is_auto));
		}
		public static byte[] Serialize(s_ans_pitcher_throw m)
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
		public static void Deserialize(ref s_ans_pitcher_throw m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ans_pitcher_throw)) as s_ans_pitcher_throw;
			}
		}
		public static void Decoding_FromSocketData(ref s_ans_pitcher_throw m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- ans_better_hit
//////////////////////////////////////////////////
		public static s_ans_better_hit Make_ans_better_hit(s_better_hit_info info,bool is_auto)
		{
			s_ans_better_hit v = new s_ans_better_hit();
			v.info = info;
			v.is_auto = is_auto;
			return v;
		}
		public static BaseballServer_Client Build(s_ans_better_hit v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.ans_better_hit;
			v2.m_ans_better_hit = v;
			return v2;
		}
		public static BaseballServer_Client Build_ans_better_hit(s_better_hit_info info,bool is_auto)
		{
			return Build(Make_ans_better_hit(info,is_auto));
		}
		public static byte[] Serialize(s_ans_better_hit m)
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
		public static void Deserialize(ref s_ans_better_hit m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ans_better_hit)) as s_ans_better_hit;
			}
		}
		public static void Decoding_FromSocketData(ref s_ans_better_hit m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- ans_result_better_hit
//////////////////////////////////////////////////
		public static s_ans_result_better_hit Make_ans_result_better_hit(s_result_round info,Int32 end_type)
		{
			s_ans_result_better_hit v = new s_ans_result_better_hit();
			v.info = info;
			v.end_type = end_type;
			return v;
		}
		public static BaseballServer_Client Build(s_ans_result_better_hit v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.ans_result_better_hit;
			v2.m_ans_result_better_hit = v;
			return v2;
		}
		public static BaseballServer_Client Build_ans_result_better_hit(s_result_round info,Int32 end_type)
		{
			return Build(Make_ans_result_better_hit(info,end_type));
		}
		public static byte[] Serialize(s_ans_result_better_hit m)
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
		public static void Deserialize(ref s_ans_result_better_hit m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ans_result_better_hit)) as s_ans_result_better_hit;
			}
		}
		public static void Decoding_FromSocketData(ref s_ans_result_better_hit m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- bs2x_batter_ready
//////////////////////////////////////////////////
		public static s_bs2x_batter_ready Make_bs2x_batter_ready()
		{
			s_bs2x_batter_ready v = new s_bs2x_batter_ready();
			return v;
		}
		public static BaseballServer_Client Build(s_bs2x_batter_ready v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.bs2x_batter_ready;
			v2.m_bs2x_batter_ready = v;
			return v2;
		}
		public static BaseballServer_Client Build_bs2x_batter_ready()
		{
			return Build(Make_bs2x_batter_ready());
		}
		public static byte[] Serialize(s_bs2x_batter_ready m)
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
		public static void Deserialize(ref s_bs2x_batter_ready m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_bs2x_batter_ready)) as s_bs2x_batter_ready;
			}
		}
		public static void Decoding_FromSocketData(ref s_bs2x_batter_ready m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- ans_change_attack_team
//////////////////////////////////////////////////
		public static s_ans_change_attack_team Make_ans_change_attack_team(Int32 round,Int64 attack_user)
		{
			s_ans_change_attack_team v = new s_ans_change_attack_team();
			v.round = round;
			v.attack_user = attack_user;
			return v;
		}
		public static BaseballServer_Client Build(s_ans_change_attack_team v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.ans_change_attack_team;
			v2.m_ans_change_attack_team = v;
			return v2;
		}
		public static BaseballServer_Client Build_ans_change_attack_team(Int32 round,Int64 attack_user)
		{
			return Build(Make_ans_change_attack_team(round,attack_user));
		}
		public static byte[] Serialize(s_ans_change_attack_team m)
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
		public static void Deserialize(ref s_ans_change_attack_team m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ans_change_attack_team)) as s_ans_change_attack_team;
			}
		}
		public static void Decoding_FromSocketData(ref s_ans_change_attack_team m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- ans_game_end
//////////////////////////////////////////////////
		public static s_ans_game_end Make_ans_game_end(s_result_game rg,s_tbl_user user,Int32 end_type)
		{
			s_ans_game_end v = new s_ans_game_end();
			v.rg = rg;
			v.user = user;
			v.end_type = end_type;
			return v;
		}
		public static BaseballServer_Client Build(s_ans_game_end v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.ans_game_end;
			v2.m_ans_game_end = v;
			return v2;
		}
		public static BaseballServer_Client Build_ans_game_end(s_result_game rg,s_tbl_user user,Int32 end_type)
		{
			return Build(Make_ans_game_end(rg,user,end_type));
		}
		public static byte[] Serialize(s_ans_game_end m)
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
		public static void Deserialize(ref s_ans_game_end m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ans_game_end)) as s_ans_game_end;
			}
		}
		public static void Decoding_FromSocketData(ref s_ans_game_end m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- bs2x_game_end_other_user_info
//////////////////////////////////////////////////
		public static s_bs2x_game_end_other_user_info Make_bs2x_game_end_other_user_info(s_tbl_user other_user)
		{
			s_bs2x_game_end_other_user_info v = new s_bs2x_game_end_other_user_info();
			v.other_user = other_user;
			return v;
		}
		public static BaseballServer_Client Build(s_bs2x_game_end_other_user_info v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.bs2x_game_end_other_user_info;
			v2.m_bs2x_game_end_other_user_info = v;
			return v2;
		}
		public static BaseballServer_Client Build_bs2x_game_end_other_user_info(s_tbl_user other_user)
		{
			return Build(Make_bs2x_game_end_other_user_info(other_user));
		}
		public static byte[] Serialize(s_bs2x_game_end_other_user_info m)
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
		public static void Deserialize(ref s_bs2x_game_end_other_user_info m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_bs2x_game_end_other_user_info)) as s_bs2x_game_end_other_user_info;
			}
		}
		public static void Decoding_FromSocketData(ref s_bs2x_game_end_other_user_info m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- ans_user_disconnect
//////////////////////////////////////////////////
		public static s_ans_user_disconnect Make_ans_user_disconnect(Int64 uid,Int32 sys_error_id)
		{
			s_ans_user_disconnect v = new s_ans_user_disconnect();
			v.uid = uid;
			v.sys_error_id = sys_error_id;
			return v;
		}
		public static BaseballServer_Client Build(s_ans_user_disconnect v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.ans_user_disconnect;
			v2.m_ans_user_disconnect = v;
			return v2;
		}
		public static BaseballServer_Client Build_ans_user_disconnect(Int64 uid,Int32 sys_error_id)
		{
			return Build(Make_ans_user_disconnect(uid,sys_error_id));
		}
		public static byte[] Serialize(s_ans_user_disconnect m)
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
		public static void Deserialize(ref s_ans_user_disconnect m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ans_user_disconnect)) as s_ans_user_disconnect;
			}
		}
		public static void Decoding_FromSocketData(ref s_ans_user_disconnect m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- ans_rematch
//////////////////////////////////////////////////
		public static s_ans_rematch Make_ans_rematch(Int64 uid)
		{
			s_ans_rematch v = new s_ans_rematch();
			v.uid = uid;
			return v;
		}
		public static BaseballServer_Client Build(s_ans_rematch v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.ans_rematch;
			v2.m_ans_rematch = v;
			return v2;
		}
		public static BaseballServer_Client Build_ans_rematch(Int64 uid)
		{
			return Build(Make_ans_rematch(uid));
		}
		public static byte[] Serialize(s_ans_rematch m)
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
		public static void Deserialize(ref s_ans_rematch m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ans_rematch)) as s_ans_rematch;
			}
		}
		public static void Decoding_FromSocketData(ref s_ans_rematch m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- ans_answer_restart_game
//////////////////////////////////////////////////
		public static s_ans_answer_restart_game Make_ans_answer_restart_game(List<Int64> uid,List<bool> ok,Int32 baseball_park,Int64 attack_user)
		{
			s_ans_answer_restart_game v = new s_ans_answer_restart_game();
			v.uid = uid;
			v.ok = ok;
			v.baseball_park = baseball_park;
			v.attack_user = attack_user;
			return v;
		}
		public static BaseballServer_Client Build(s_ans_answer_restart_game v)
		{
			BaseballServer_Client v2 = new BaseballServer_Client();
			v2.type = BaseballServer_Client.Type.ans_answer_restart_game;
			v2.m_ans_answer_restart_game = v;
			return v2;
		}
		public static BaseballServer_Client Build_ans_answer_restart_game(List<Int64> uid,List<bool> ok,Int32 baseball_park,Int64 attack_user)
		{
			return Build(Make_ans_answer_restart_game(uid,ok,baseball_park,attack_user));
		}
		public static byte[] Serialize(s_ans_answer_restart_game m)
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
		public static void Deserialize(ref s_ans_answer_restart_game m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ans_answer_restart_game)) as s_ans_answer_restart_game;
			}
		}
		public static void Decoding_FromSocketData(ref s_ans_answer_restart_game m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


	}//class PT_BaseballServer


    public partial class PT_BaseballServer
	{
//////////////////////////////////////////////////
///#-- ug2bs_ans_set_cvar
//////////////////////////////////////////////////
		public static s_ug2bs_ans_set_cvar Make_ug2bs_ans_set_cvar(string name,string val)
		{
			s_ug2bs_ans_set_cvar v = new s_ug2bs_ans_set_cvar();
			v.name = name;
			v.val = val;
			return v;
		}
		public static UserGateServer_BaseballServer Build(s_ug2bs_ans_set_cvar v)
		{
			UserGateServer_BaseballServer v2 = new UserGateServer_BaseballServer();
			v2.type = UserGateServer_BaseballServer.Type.ug2bs_ans_set_cvar;
			v2.m_ug2bs_ans_set_cvar = v;
			return v2;
		}
		public static UserGateServer_BaseballServer Build_ug2bs_ans_set_cvar(string name,string val)
		{
			return Build(Make_ug2bs_ans_set_cvar(name,val));
		}
		public static byte[] Serialize(s_ug2bs_ans_set_cvar m)
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
		public static void Deserialize(ref s_ug2bs_ans_set_cvar m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ug2bs_ans_set_cvar)) as s_ug2bs_ans_set_cvar;
			}
		}
		public static void Decoding_FromSocketData(ref s_ug2bs_ans_set_cvar m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- ug2bs_game_end
//////////////////////////////////////////////////
		public static s_ug2bs_game_end Make_ug2bs_game_end(s_result_game rg,s_tbl_user user)
		{
			s_ug2bs_game_end v = new s_ug2bs_game_end();
			v.rg = rg;
			v.user = user;
			return v;
		}
		public static UserGateServer_BaseballServer Build(s_ug2bs_game_end v)
		{
			UserGateServer_BaseballServer v2 = new UserGateServer_BaseballServer();
			v2.type = UserGateServer_BaseballServer.Type.ug2bs_game_end;
			v2.m_ug2bs_game_end = v;
			return v2;
		}
		public static UserGateServer_BaseballServer Build_ug2bs_game_end(s_result_game rg,s_tbl_user user)
		{
			return Build(Make_ug2bs_game_end(rg,user));
		}
		public static byte[] Serialize(s_ug2bs_game_end m)
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
		public static void Deserialize(ref s_ug2bs_game_end m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ug2bs_game_end)) as s_ug2bs_game_end;
			}
		}
		public static void Decoding_FromSocketData(ref s_ug2bs_game_end m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- ug2bs_echo
//////////////////////////////////////////////////
		public static s_ug2bs_echo Make_ug2bs_echo(Int32 type,string msg,Int64 bs_time_msec,Int64 ug_time_msec)
		{
			s_ug2bs_echo v = new s_ug2bs_echo();
			v.type = type;
			v.msg = msg;
			v.bs_time_msec = bs_time_msec;
			v.ug_time_msec = ug_time_msec;
			return v;
		}
		public static UserGateServer_BaseballServer Build(s_ug2bs_echo v)
		{
			UserGateServer_BaseballServer v2 = new UserGateServer_BaseballServer();
			v2.type = UserGateServer_BaseballServer.Type.ug2bs_echo;
			v2.m_ug2bs_echo = v;
			return v2;
		}
		public static UserGateServer_BaseballServer Build_ug2bs_echo(Int32 type,string msg,Int64 bs_time_msec,Int64 ug_time_msec)
		{
			return Build(Make_ug2bs_echo(type,msg,bs_time_msec,ug_time_msec));
		}
		public static byte[] Serialize(s_ug2bs_echo m)
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
		public static void Deserialize(ref s_ug2bs_echo m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ug2bs_echo)) as s_ug2bs_echo;
			}
		}
		public static void Decoding_FromSocketData(ref s_ug2bs_echo m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- ug2bs_error
//////////////////////////////////////////////////
		public static s_ug2bs_error Make_ug2bs_error(Int32 sys_error_id)
		{
			s_ug2bs_error v = new s_ug2bs_error();
			v.sys_error_id = sys_error_id;
			return v;
		}
		public static UserGateServer_BaseballServer Build(s_ug2bs_error v)
		{
			UserGateServer_BaseballServer v2 = new UserGateServer_BaseballServer();
			v2.type = UserGateServer_BaseballServer.Type.ug2bs_error;
			v2.m_ug2bs_error = v;
			return v2;
		}
		public static UserGateServer_BaseballServer Build_ug2bs_error(Int32 sys_error_id)
		{
			return Build(Make_ug2bs_error(sys_error_id));
		}
		public static byte[] Serialize(s_ug2bs_error m)
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
		public static void Deserialize(ref s_ug2bs_error m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ug2bs_error)) as s_ug2bs_error;
			}
		}
		public static void Decoding_FromSocketData(ref s_ug2bs_error m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- ug2bs_add_discon_tot
//////////////////////////////////////////////////
		public static s_ug2bs_add_discon_tot Make_ug2bs_add_discon_tot(Int64 discon_uid)
		{
			s_ug2bs_add_discon_tot v = new s_ug2bs_add_discon_tot();
			v.discon_uid = discon_uid;
			return v;
		}
		public static UserGateServer_BaseballServer Build(s_ug2bs_add_discon_tot v)
		{
			UserGateServer_BaseballServer v2 = new UserGateServer_BaseballServer();
			v2.type = UserGateServer_BaseballServer.Type.ug2bs_add_discon_tot;
			v2.m_ug2bs_add_discon_tot = v;
			return v2;
		}
		public static UserGateServer_BaseballServer Build_ug2bs_add_discon_tot(Int64 discon_uid)
		{
			return Build(Make_ug2bs_add_discon_tot(discon_uid));
		}
		public static byte[] Serialize(s_ug2bs_add_discon_tot m)
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
		public static void Deserialize(ref s_ug2bs_add_discon_tot m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_ug2bs_add_discon_tot)) as s_ug2bs_add_discon_tot;
			}
		}
		public static void Decoding_FromSocketData(ref s_ug2bs_add_discon_tot m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


	}//class PT_BaseballServer


    public partial class PT_BaseballServer
	{
//////////////////////////////////////////////////
///#-- req_room_state
//////////////////////////////////////////////////
		public static s_req_room_state Make_req_room_state(Int32 room)
		{
			s_req_room_state v = new s_req_room_state();
			v.room = room;
			return v;
		}
		public static Client_BaseballServer Build(s_req_room_state v)
		{
			Client_BaseballServer v2 = new Client_BaseballServer();
			v2.type = Client_BaseballServer.Type.req_room_state;
			v2.m_req_room_state = v;
			return v2;
		}
		public static Client_BaseballServer Build_req_room_state(Int32 room)
		{
			return Build(Make_req_room_state(room));
		}
		public static byte[] Serialize(s_req_room_state m)
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
		public static void Deserialize(ref s_req_room_state m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_req_room_state)) as s_req_room_state;
			}
		}
		public static void Decoding_FromSocketData(ref s_req_room_state m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- x2bs_echo
//////////////////////////////////////////////////
		public static s_x2bs_echo Make_x2bs_echo(Int32 type,string msg,Int32 client_time_msec)
		{
			s_x2bs_echo v = new s_x2bs_echo();
			v.type = type;
			v.msg = msg;
			v.client_time_msec = client_time_msec;
			return v;
		}
		public static Client_BaseballServer Build(s_x2bs_echo v)
		{
			Client_BaseballServer v2 = new Client_BaseballServer();
			v2.type = Client_BaseballServer.Type.x2bs_echo;
			v2.m_x2bs_echo = v;
			return v2;
		}
		public static Client_BaseballServer Build_x2bs_echo(Int32 type,string msg,Int32 client_time_msec)
		{
			return Build(Make_x2bs_echo(type,msg,client_time_msec));
		}
		public static byte[] Serialize(s_x2bs_echo m)
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
		public static void Deserialize(ref s_x2bs_echo m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_x2bs_echo)) as s_x2bs_echo;
			}
		}
		public static void Decoding_FromSocketData(ref s_x2bs_echo m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- req_chat
//////////////////////////////////////////////////
		public static s_req_chat Make_req_chat(Int32 type,string msg,string etc)
		{
			s_req_chat v = new s_req_chat();
			v.type = type;
			v.msg = msg;
			v.etc = etc;
			return v;
		}
		public static Client_BaseballServer Build(s_req_chat v)
		{
			Client_BaseballServer v2 = new Client_BaseballServer();
			v2.type = Client_BaseballServer.Type.req_chat;
			v2.m_req_chat = v;
			return v2;
		}
		public static Client_BaseballServer Build_req_chat(Int32 type,string msg,string etc)
		{
			return Build(Make_req_chat(type,msg,etc));
		}
		public static byte[] Serialize(s_req_chat m)
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
		public static void Deserialize(ref s_req_chat m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_req_chat)) as s_req_chat;
			}
		}
		public static void Decoding_FromSocketData(ref s_req_chat m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- req_timer_start
//////////////////////////////////////////////////
		public static s_req_timer_start Make_req_timer_start(Int32 term,string msg)
		{
			s_req_timer_start v = new s_req_timer_start();
			v.term = term;
			v.msg = msg;
			return v;
		}
		public static Client_BaseballServer Build(s_req_timer_start v)
		{
			Client_BaseballServer v2 = new Client_BaseballServer();
			v2.type = Client_BaseballServer.Type.req_timer_start;
			v2.m_req_timer_start = v;
			return v2;
		}
		public static Client_BaseballServer Build_req_timer_start(Int32 term,string msg)
		{
			return Build(Make_req_timer_start(term,msg));
		}
		public static byte[] Serialize(s_req_timer_start m)
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
		public static void Deserialize(ref s_req_timer_start m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_req_timer_start)) as s_req_timer_start;
			}
		}
		public static void Decoding_FromSocketData(ref s_req_timer_start m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- req_do_disconnect
//////////////////////////////////////////////////
		public static s_req_do_disconnect Make_req_do_disconnect(string reason)
		{
			s_req_do_disconnect v = new s_req_do_disconnect();
			v.reason = reason;
			return v;
		}
		public static Client_BaseballServer Build(s_req_do_disconnect v)
		{
			Client_BaseballServer v2 = new Client_BaseballServer();
			v2.type = Client_BaseballServer.Type.req_do_disconnect;
			v2.m_req_do_disconnect = v;
			return v2;
		}
		public static Client_BaseballServer Build_req_do_disconnect(string reason)
		{
			return Build(Make_req_do_disconnect(reason));
		}
		public static byte[] Serialize(s_req_do_disconnect m)
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
		public static void Deserialize(ref s_req_do_disconnect m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_req_do_disconnect)) as s_req_do_disconnect;
			}
		}
		public static void Decoding_FromSocketData(ref s_req_do_disconnect m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- x2bs_echo2
//////////////////////////////////////////////////
		public static s_x2bs_echo2 Make_x2bs_echo2(Int32 type,string msg,Int32 client_time_msec)
		{
			s_x2bs_echo2 v = new s_x2bs_echo2();
			v.type = type;
			v.msg = msg;
			v.client_time_msec = client_time_msec;
			return v;
		}
		public static Client_BaseballServer Build(s_x2bs_echo2 v)
		{
			Client_BaseballServer v2 = new Client_BaseballServer();
			v2.type = Client_BaseballServer.Type.x2bs_echo2;
			v2.m_x2bs_echo2 = v;
			return v2;
		}
		public static Client_BaseballServer Build_x2bs_echo2(Int32 type,string msg,Int32 client_time_msec)
		{
			return Build(Make_x2bs_echo2(type,msg,client_time_msec));
		}
		public static byte[] Serialize(s_x2bs_echo2 m)
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
		public static void Deserialize(ref s_x2bs_echo2 m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_x2bs_echo2)) as s_x2bs_echo2;
			}
		}
		public static void Decoding_FromSocketData(ref s_x2bs_echo2 m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- req_get_cvar
//////////////////////////////////////////////////
		public static s_req_get_cvar Make_req_get_cvar(string name)
		{
			s_req_get_cvar v = new s_req_get_cvar();
			v.name = name;
			return v;
		}
		public static Client_BaseballServer Build(s_req_get_cvar v)
		{
			Client_BaseballServer v2 = new Client_BaseballServer();
			v2.type = Client_BaseballServer.Type.req_get_cvar;
			v2.m_req_get_cvar = v;
			return v2;
		}
		public static Client_BaseballServer Build_req_get_cvar(string name)
		{
			return Build(Make_req_get_cvar(name));
		}
		public static byte[] Serialize(s_req_get_cvar m)
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
		public static void Deserialize(ref s_req_get_cvar m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_req_get_cvar)) as s_req_get_cvar;
			}
		}
		public static void Decoding_FromSocketData(ref s_req_get_cvar m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- req_set_cvar
//////////////////////////////////////////////////
		public static s_req_set_cvar Make_req_set_cvar(string name,string val)
		{
			s_req_set_cvar v = new s_req_set_cvar();
			v.name = name;
			v.val = val;
			return v;
		}
		public static Client_BaseballServer Build(s_req_set_cvar v)
		{
			Client_BaseballServer v2 = new Client_BaseballServer();
			v2.type = Client_BaseballServer.Type.req_set_cvar;
			v2.m_req_set_cvar = v;
			return v2;
		}
		public static Client_BaseballServer Build_req_set_cvar(string name,string val)
		{
			return Build(Make_req_set_cvar(name,val));
		}
		public static byte[] Serialize(s_req_set_cvar m)
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
		public static void Deserialize(ref s_req_set_cvar m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_req_set_cvar)) as s_req_set_cvar;
			}
		}
		public static void Decoding_FromSocketData(ref s_req_set_cvar m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- x2bs_auto_match_ready2
//////////////////////////////////////////////////
		public static s_x2bs_auto_match_ready2 Make_x2bs_auto_match_ready2(Int64 uid,Int32 batter,Int32 pitcher)
		{
			s_x2bs_auto_match_ready2 v = new s_x2bs_auto_match_ready2();
			v.uid = uid;
			v.batter = batter;
			v.pitcher = pitcher;
			return v;
		}
		public static Client_BaseballServer Build(s_x2bs_auto_match_ready2 v)
		{
			Client_BaseballServer v2 = new Client_BaseballServer();
			v2.type = Client_BaseballServer.Type.x2bs_auto_match_ready2;
			v2.m_x2bs_auto_match_ready2 = v;
			return v2;
		}
		public static Client_BaseballServer Build_x2bs_auto_match_ready2(Int64 uid,Int32 batter,Int32 pitcher)
		{
			return Build(Make_x2bs_auto_match_ready2(uid,batter,pitcher));
		}
		public static byte[] Serialize(s_x2bs_auto_match_ready2 m)
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
		public static void Deserialize(ref s_x2bs_auto_match_ready2 m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_x2bs_auto_match_ready2)) as s_x2bs_auto_match_ready2;
			}
		}
		public static void Decoding_FromSocketData(ref s_x2bs_auto_match_ready2 m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- x2bs_match_ready
//////////////////////////////////////////////////
		public static s_x2bs_match_ready Make_x2bs_match_ready(Int64 uid)
		{
			s_x2bs_match_ready v = new s_x2bs_match_ready();
			v.uid = uid;
			return v;
		}
		public static Client_BaseballServer Build(s_x2bs_match_ready v)
		{
			Client_BaseballServer v2 = new Client_BaseballServer();
			v2.type = Client_BaseballServer.Type.x2bs_match_ready;
			v2.m_x2bs_match_ready = v;
			return v2;
		}
		public static Client_BaseballServer Build_x2bs_match_ready(Int64 uid)
		{
			return Build(Make_x2bs_match_ready(uid));
		}
		public static byte[] Serialize(s_x2bs_match_ready m)
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
		public static void Deserialize(ref s_x2bs_match_ready m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_x2bs_match_ready)) as s_x2bs_match_ready;
			}
		}
		public static void Decoding_FromSocketData(ref s_x2bs_match_ready m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- req_pitcher_throw
//////////////////////////////////////////////////
		public static s_req_pitcher_throw Make_req_pitcher_throw(s_pitcher_throw_info info,Int32 used_gesturetype,Int32 gesturetype_input_error)
		{
			s_req_pitcher_throw v = new s_req_pitcher_throw();
			v.info = info;
			v.used_gesturetype = used_gesturetype;
			v.gesturetype_input_error = gesturetype_input_error;
			return v;
		}
		public static Client_BaseballServer Build(s_req_pitcher_throw v)
		{
			Client_BaseballServer v2 = new Client_BaseballServer();
			v2.type = Client_BaseballServer.Type.req_pitcher_throw;
			v2.m_req_pitcher_throw = v;
			return v2;
		}
		public static Client_BaseballServer Build_req_pitcher_throw(s_pitcher_throw_info info,Int32 used_gesturetype,Int32 gesturetype_input_error)
		{
			return Build(Make_req_pitcher_throw(info,used_gesturetype,gesturetype_input_error));
		}
		public static byte[] Serialize(s_req_pitcher_throw m)
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
		public static void Deserialize(ref s_req_pitcher_throw m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_req_pitcher_throw)) as s_req_pitcher_throw;
			}
		}
		public static void Decoding_FromSocketData(ref s_req_pitcher_throw m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- req_better_hit
//////////////////////////////////////////////////
		public static s_req_better_hit Make_req_better_hit(s_better_hit_info info)
		{
			s_req_better_hit v = new s_req_better_hit();
			v.info = info;
			return v;
		}
		public static Client_BaseballServer Build(s_req_better_hit v)
		{
			Client_BaseballServer v2 = new Client_BaseballServer();
			v2.type = Client_BaseballServer.Type.req_better_hit;
			v2.m_req_better_hit = v;
			return v2;
		}
		public static Client_BaseballServer Build_req_better_hit(s_better_hit_info info)
		{
			return Build(Make_req_better_hit(info));
		}
		public static byte[] Serialize(s_req_better_hit m)
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
		public static void Deserialize(ref s_req_better_hit m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_req_better_hit)) as s_req_better_hit;
			}
		}
		public static void Decoding_FromSocketData(ref s_req_better_hit m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- req_result_better_hit
//////////////////////////////////////////////////
		public static s_req_result_better_hit Make_req_result_better_hit(s_result_round info,Int32 test)
		{
			s_req_result_better_hit v = new s_req_result_better_hit();
			v.info = info;
			v.test = test;
			return v;
		}
		public static Client_BaseballServer Build(s_req_result_better_hit v)
		{
			Client_BaseballServer v2 = new Client_BaseballServer();
			v2.type = Client_BaseballServer.Type.req_result_better_hit;
			v2.m_req_result_better_hit = v;
			return v2;
		}
		public static Client_BaseballServer Build_req_result_better_hit(s_result_round info,Int32 test)
		{
			return Build(Make_req_result_better_hit(info,test));
		}
		public static byte[] Serialize(s_req_result_better_hit m)
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
		public static void Deserialize(ref s_req_result_better_hit m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_req_result_better_hit)) as s_req_result_better_hit;
			}
		}
		public static void Decoding_FromSocketData(ref s_req_result_better_hit m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- x2bs_batter_ready
//////////////////////////////////////////////////
		public static s_x2bs_batter_ready Make_x2bs_batter_ready()
		{
			s_x2bs_batter_ready v = new s_x2bs_batter_ready();
			return v;
		}
		public static Client_BaseballServer Build(s_x2bs_batter_ready v)
		{
			Client_BaseballServer v2 = new Client_BaseballServer();
			v2.type = Client_BaseballServer.Type.x2bs_batter_ready;
			v2.m_x2bs_batter_ready = v;
			return v2;
		}
		public static Client_BaseballServer Build_x2bs_batter_ready()
		{
			return Build(Make_x2bs_batter_ready());
		}
		public static byte[] Serialize(s_x2bs_batter_ready m)
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
		public static void Deserialize(ref s_x2bs_batter_ready m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_x2bs_batter_ready)) as s_x2bs_batter_ready;
			}
		}
		public static void Decoding_FromSocketData(ref s_x2bs_batter_ready m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- req_rematch
//////////////////////////////////////////////////
		public static s_req_rematch Make_req_rematch(Int64 uid)
		{
			s_req_rematch v = new s_req_rematch();
			v.uid = uid;
			return v;
		}
		public static Client_BaseballServer Build(s_req_rematch v)
		{
			Client_BaseballServer v2 = new Client_BaseballServer();
			v2.type = Client_BaseballServer.Type.req_rematch;
			v2.m_req_rematch = v;
			return v2;
		}
		public static Client_BaseballServer Build_req_rematch(Int64 uid)
		{
			return Build(Make_req_rematch(uid));
		}
		public static byte[] Serialize(s_req_rematch m)
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
		public static void Deserialize(ref s_req_rematch m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_req_rematch)) as s_req_rematch;
			}
		}
		public static void Decoding_FromSocketData(ref s_req_rematch m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


//////////////////////////////////////////////////
///#-- req_answer_restart_game
//////////////////////////////////////////////////
		public static s_req_answer_restart_game Make_req_answer_restart_game(Int64 uid,bool ok)
		{
			s_req_answer_restart_game v = new s_req_answer_restart_game();
			v.uid = uid;
			v.ok = ok;
			return v;
		}
		public static Client_BaseballServer Build(s_req_answer_restart_game v)
		{
			Client_BaseballServer v2 = new Client_BaseballServer();
			v2.type = Client_BaseballServer.Type.req_answer_restart_game;
			v2.m_req_answer_restart_game = v;
			return v2;
		}
		public static Client_BaseballServer Build_req_answer_restart_game(Int64 uid,bool ok)
		{
			return Build(Make_req_answer_restart_game(uid,ok));
		}
		public static byte[] Serialize(s_req_answer_restart_game m)
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
		public static void Deserialize(ref s_req_answer_restart_game m, byte[] serializationBytes)
		{
			using (var ms = new MemoryStream(serializationBytes))
			{
				BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
				m = psz.Deserialize(ms, null, typeof(s_req_answer_restart_game)) as s_req_answer_restart_game;
			}
		}
		public static void Decoding_FromSocketData(ref s_req_answer_restart_game m, byte[] socketData)
		{
			int iSize = 0;
			byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
		
			Deserialize(ref m, recvData);
		}
		


	}//class PT_BaseballServer


}//namespace nPROTO