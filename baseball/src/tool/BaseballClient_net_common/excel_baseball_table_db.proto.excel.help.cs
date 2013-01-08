
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
	public class excel_baseball_table_db_proto_helper
	{
			//------------------------------------------------
			//	s_tbl_quest
			//------------------------------------------------
			public static byte[] Serialize(s_tbl_quest m) 
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
			public static void Deserialize(ref s_tbl_quest m, byte[] serializationBytes)
			{
				using (var ms = new MemoryStream(serializationBytes))
				{
					BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
					m = psz.Deserialize(ms, null, typeof(s_tbl_quest)) as s_tbl_quest;
				}
			}
			public static void Decoding_FromSocketData(ref s_tbl_quest m, byte[] socketData)
			{
				int iSize = 0;
				byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
				Deserialize(ref m, recvData);
			}
			


			//------------------------------------------------
			//	s_tbl_result
			//------------------------------------------------
			public static byte[] Serialize(s_tbl_result m) 
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
			public static void Deserialize(ref s_tbl_result m, byte[] serializationBytes)
			{
				using (var ms = new MemoryStream(serializationBytes))
				{
					BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
					m = psz.Deserialize(ms, null, typeof(s_tbl_result)) as s_tbl_result;
				}
			}
			public static void Decoding_FromSocketData(ref s_tbl_result m, byte[] socketData)
			{
				int iSize = 0;
				byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
				Deserialize(ref m, recvData);
			}
			


			//------------------------------------------------
			//	s_tbl_roundresult
			//------------------------------------------------
			public static byte[] Serialize(s_tbl_roundresult m) 
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
			public static void Deserialize(ref s_tbl_roundresult m, byte[] serializationBytes)
			{
				using (var ms = new MemoryStream(serializationBytes))
				{
					BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
					m = psz.Deserialize(ms, null, typeof(s_tbl_roundresult)) as s_tbl_roundresult;
				}
			}
			public static void Decoding_FromSocketData(ref s_tbl_roundresult m, byte[] socketData)
			{
				int iSize = 0;
				byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
				Deserialize(ref m, recvData);
			}
			


			//------------------------------------------------
			//	s_tbl_user
			//------------------------------------------------
			public static byte[] Serialize(s_tbl_user m) 
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
			public static void Deserialize(ref s_tbl_user m, byte[] serializationBytes)
			{
				using (var ms = new MemoryStream(serializationBytes))
				{
					BaseballClient_proto_Serializer psz = new BaseballClient_proto_Serializer();
					m = psz.Deserialize(ms, null, typeof(s_tbl_user)) as s_tbl_user;
				}
			}
			public static void Decoding_FromSocketData(ref s_tbl_user m, byte[] socketData)
			{
				int iSize = 0;
				byte[] recvData = util.DecodingSize_From_Data(ref iSize, socketData);
				Deserialize(ref m, recvData);
			}
			


	}//class excel_baseball_table_db_proto_helper
}// namespace nEXCEL


