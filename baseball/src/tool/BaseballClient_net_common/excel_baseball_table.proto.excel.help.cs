
// THIS CODE IS USED FOR unity3d + google protocal buffer + c# + iphone
// by icandoit@neowiz.com
// command line : Excel_Converter.exe D:\svn\baseball\doc\design\excel\code\excel_baseball_table.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_db.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_game.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_item.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_shop.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_string_table.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_etc.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_client.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_animation.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_client_locale_Eng.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_client_locale_kor.txt 



using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using ProtoBuf;
using nEXCEL;
using nPROTO;
using System.Runtime.Serialization;
using System.IO;

// above code is created by app_xml <PROTO_CONTRACT_NAMESPACE>


namespace nEXCEL
{
	public class excel_baseball_table_proto_helper
	{
			//------------------------------------------------
			//	s_sys_base_playerstat
			//------------------------------------------------
			public static byte[] Serialize(s_sys_base_playerstat m) 
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
			public static void Deserialize(ref s_sys_base_playerstat m, byte[] serializationBytes)
			{
				using (var ms = new MemoryStream(serializationBytes))
				{
					BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
					m = psz.Deserialize(ms, null, typeof(s_sys_base_playerstat)) as s_sys_base_playerstat;
				}
			}
			public static void Decoding_FromSocketData(ref s_sys_base_playerstat m, byte[] socketData)
			{
				int iSize = 0;
				byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
				Deserialize(ref m, recvData);
			}
			


			//------------------------------------------------
			//	s_sys_playercard
			//------------------------------------------------
			public static byte[] Serialize(s_sys_playercard m) 
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
			public static void Deserialize(ref s_sys_playercard m, byte[] serializationBytes)
			{
				using (var ms = new MemoryStream(serializationBytes))
				{
					BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
					m = psz.Deserialize(ms, null, typeof(s_sys_playercard)) as s_sys_playercard;
				}
			}
			public static void Decoding_FromSocketData(ref s_sys_playercard m, byte[] socketData)
			{
				int iSize = 0;
				byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
				Deserialize(ref m, recvData);
			}
			


			//------------------------------------------------
			//	s_sys_playerlevel
			//------------------------------------------------
			public static byte[] Serialize(s_sys_playerlevel m) 
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
			public static void Deserialize(ref s_sys_playerlevel m, byte[] serializationBytes)
			{
				using (var ms = new MemoryStream(serializationBytes))
				{
					BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
					m = psz.Deserialize(ms, null, typeof(s_sys_playerlevel)) as s_sys_playerlevel;
				}
			}
			public static void Decoding_FromSocketData(ref s_sys_playerlevel m, byte[] socketData)
			{
				int iSize = 0;
				byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
				Deserialize(ref m, recvData);
			}
			


			//------------------------------------------------
			//	s_sys_playerskillsticker
			//------------------------------------------------
			public static byte[] Serialize(s_sys_playerskillsticker m) 
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
			public static void Deserialize(ref s_sys_playerskillsticker m, byte[] serializationBytes)
			{
				using (var ms = new MemoryStream(serializationBytes))
				{
					BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
					m = psz.Deserialize(ms, null, typeof(s_sys_playerskillsticker)) as s_sys_playerskillsticker;
				}
			}
			public static void Decoding_FromSocketData(ref s_sys_playerskillsticker m, byte[] socketData)
			{
				int iSize = 0;
				byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
				Deserialize(ref m, recvData);
			}
			


			//------------------------------------------------
			//	s_sys_quest
			//------------------------------------------------
			public static byte[] Serialize(s_sys_quest m) 
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
			public static void Deserialize(ref s_sys_quest m, byte[] serializationBytes)
			{
				using (var ms = new MemoryStream(serializationBytes))
				{
					BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
					m = psz.Deserialize(ms, null, typeof(s_sys_quest)) as s_sys_quest;
				}
			}
			public static void Decoding_FromSocketData(ref s_sys_quest m, byte[] socketData)
			{
				int iSize = 0;
				byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
				Deserialize(ref m, recvData);
			}
			


			//------------------------------------------------
			//	s_sys_title
			//------------------------------------------------
			public static byte[] Serialize(s_sys_title m) 
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
			public static void Deserialize(ref s_sys_title m, byte[] serializationBytes)
			{
				using (var ms = new MemoryStream(serializationBytes))
				{
					BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
					m = psz.Deserialize(ms, null, typeof(s_sys_title)) as s_sys_title;
				}
			}
			public static void Decoding_FromSocketData(ref s_sys_title m, byte[] socketData)
			{
				int iSize = 0;
				byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
				Deserialize(ref m, recvData);
			}
			


	}//class excel_baseball_table_proto_helper
}// namespace nEXCEL

