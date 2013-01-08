using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using nNWM;
using user_id_t = System.Int64;

namespace nNWM
{
	namespace nDummy
	{
		public struct NetEventArg
		{
			public NetEventPlugin plugin;
			public global::ProtoBuf.IExtensible recvData;//read data
		}

		public abstract class NetEventPlugin 
		{
			public CmdEventManager m_CMD;
			public NetEventManager m_MSG;
			public  MSG.MSGClient m_MSGClient;
			protected user_id_t m_UserID=0;

			~NetEventPlugin()
			{
				if (m_MSGClient != null)
				{
					Debug.Log("m_MSGClient.Close(false);");
					m_MSGClient.Close(false);
				}
				m_MSGClient = null;
			}

			public void SetMSGClient(MSG.MSGClient client){m_MSGClient = client;}
			public MSG.MSGClient GetMSGClient(){return m_MSGClient;}
			public user_id_t db_id(){return m_UserID;}

			//#--------------------------------------------------------------------------
			// send util function
			//#--------------------------------------------------------------------------
			public static T Deserialize<T>(byte[] buffer)
			{
				int size = buffer.Length;
				var ms = new System.IO.MemoryStream(buffer, 0, size);
				return ProtoBuf.Serializer.Deserialize<T>(ms);
			}
		  public static byte[] Serialize<T>(T sd)
      {
				var ms = new System.IO.MemoryStream();
				ProtoBuf.Serializer.Serialize<T>(ms, sd);
				return ms.ToArray();
      }


			public bool send_to_MSG(MSG.AbstractRequest req,string logString=null)
			{
				if (req == null)
				{
					m_CMD.LogError("NetEventPlugin_baseball.Send : req ==null");
					return false;
				}
				if(logString==null)
					logString = nNWM.nUtil.jDumper.NamedDump(req,m_MSG.m_PacketLogType);
				NetLog("[Send:MSG]" + logString,true);
				if(m_MSGClient==null)
				{
					LogError("m_MSGClient == null");
					return false;
				}
				return m_MSGClient.Send(req);
			}


			//#--------------------------------------------------------------------------
			// Log Function
			//#--------------------------------------------------------------------------
			private string make_log_string(string log,bool isTime)
			{
				if (isTime==true){log = System.DateTime.Now.ToLongTimeString() + "["+m_UserID +"]" + log;}
				return log;
			}

			public void Log(string strLog) { m_CMD.Log(strLog); }
			public void LogWarning(string strLog){m_CMD.LogWarning(strLog);}
			public void LogError(string strLog){m_CMD.LogError(strLog);}

			public virtual void NetWarning(string log){m_CMD.LogWarning(make_log_string(log,true) );}
			public virtual void NetError(string log){m_CMD.LogError(make_log_string(log,true));}
			public virtual void NetLog(string log, bool isTime=false){m_CMD.Log(make_log_string(log,isTime));}

			//#--------------------------------------------------------------------------
			// ug.proto Recv interface
			//#--------------------------------------------------------------------------
			abstract public  void OnConnect(); //network connect.
			abstract public  void OnDisconnect(); //network disconnect.

			abstract public  void OnRecv_FromMSG(MSG.AnsConnect rd);/**  ���ӿ� ���� ���� �޽��� */
			abstract public  void OnRecv_FromMSG(MSG.AnsChannel rd);	/**  ä�� ������ ���� ���� �޽� */
			abstract public  void OnRecv_FromMSG(MSG.AnsInfo rd);  /**  ���� ������ ���� ���� �޽��� */
			abstract public  void OnRecv_FromMSG(MSG.AnsAutoJoin rd);  /**  ���� �ڵ� ���忡 ���� ���� �޽��� */
			abstract public  void OnRecv_FromMSG(MSG.AnsLeaveGame rd);  /**  ���� �����⿡ ���� ���� �޽��� */
			abstract public  void OnRecv_FromMSG(MSG.AnsClose rd );  
			abstract public  void OnRecv_FromMSG(MSG.AnsPlug rd);  /**  ������ ��� �޽���  */
			//abstract public  void OnRecv_FromMSG(AnsGatewayProtocol rd); /**  ����Ʈ������ ����� �޽����� ���� ���� */
			abstract public  void OnRecv_FromMSG(MSG.AnsNotice rd);  /**  �������� ���� �޽��� */
			abstract public  void OnRecv_FromMSG(MSG.AnsError rd); /**  ������ �߻����� ����� ó�� */
			abstract public  void OnRecv_FromMSG(MSG.AnsDB rd);  /**  ��� ��û�� ���� ���� �޽��� */
			abstract public  void OnRecv_Unkown(MSG.AnswerMessage ans); // �˼� ���� ug.proto �޼���.

			//#--------------------------------------------------------------------------
			// game logic Recv interface
			//#--------------------------------------------------------------------------
			abstract public  void OnRecv_FromUserGateServer(byte[] recvByte);// usergate�� db �������� ���� �޴� �޼���. 
			abstract public  void OnRecv_FromGameServer(byte[] recvByte);// game server�� ���� �޴� �޼���. 

		}//public abstract class NetEventPlugin 

	}//namespace nDummy
}//namespace nNWM
