using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using nNWM;
using user_id_t = System.Int64;

namespace nNWM
{
	namespace nASDF
	{
		public class NetEventPlugin_asdf : nNWM.nDummy.NetEventPlugin
		{
			public User_asdf m_User;

			public NetEventPlugin_asdf(user_id_t pp_id, CmdEventManager gui, NetEventManager msg)
			{
				m_User = new User_asdf(this);

				m_UserID = pp_id;
				m_CMD = gui;
				m_MSG = msg;
			}
			~NetEventPlugin_asdf()
			{
				NetLog("NetEventPlugin_asdf detroy :" + m_UserID);
			}


			//#--------------------------------------------------------------------------
			// send�� �Լ�.
			//#--------------------------------------------------------------------------
			public nProtoUGasdf.Client_UserGateServer Make(nProtoUGasdf.Client_UserGateServer.Type eType) { return new nProtoUGasdf.Client_UserGateServer { type = eType }; }
			public bool send_to_ug(nProtoUGasdf.Client_UserGateServer sd)
			{
				NetLog("[Send:ug]" + nNWM.nUtil.jDumper.NamedDump(sd.type, m_MSG.m_PacketLogType), true);
				var db = new MSG.ReqDB
				{
					Seq = 0,
					Query = "ug_game",
					Options = Serialize(sd),
				};
				return m_MSGClient.Send(db);
			}

			public nProtoGSasdf.Client_GameServer Make(nProtoGSasdf.Client_GameServer.Type eType) { return new nProtoGSasdf.Client_GameServer { type = eType }; }
			public bool send_to_gs(nProtoGSasdf.Client_GameServer sd)
			{
				NetLog("[Send:gs]" + nNWM.nUtil.jDumper.NamedDump(sd.type, m_MSG.m_PacketLogType), true);
				var sendData = new MSG.ReqGameProtocol(Serialize<nProtoGSasdf.Client_GameServer>(sd));
				return m_MSGClient.Send(sendData);
			}

			//#--------------------------------------------------------------------------
			// NetEventPlugin interface.
			//#--------------------------------------------------------------------------

			public override void OnConnect() //network connect.
			{
				//m_CMD.ParseCmd("@user.ReqConnect " + db_id());
				m_User.m_eEUserGPS = EUserGPS.eUGPS_LOGIN;
			}
			public override void OnDisconnect() //network disconnect.
			{

			}

			//#--------------------------------------------------------------------------
			// ug.proto Recv �������̽�.
			//#--------------------------------------------------------------------------
			public override void OnRecv_FromMSG(MSG.AnsConnect rd)/**  ���ӿ� ���� ���� �޽��� */
			{
				var gameInfo = new MSG.ReqInfo { };
				send_to_MSG(gameInfo);
			}

			public override void OnRecv_FromMSG(MSG.AnsInfo rd)  /**  ���� ������ ���� ���� �޽��� */
			{
				//m_CMD.ParseCmd("@user.req_db_table " + db_id());// ������̺� ���� ��û
			}
			public override void OnRecv_FromMSG(MSG.AnsChannel rd)	/**  ä�� ������ ���� ���� �޽� */
			{
				m_CMD.Log(nNWM.nUtil.jDumper.NamedDump(rd.ChannelInfo));
			}
			public override void OnRecv_FromMSG(MSG.AnsAutoJoin rd)  /**  ���� �ڵ� ���忡 ���� ���� �޽��� */
			{
				// ��ġ �����ߴ�. �������ʹ� plugin.send_to_gs()�� ����� ���Ӽ����� ��Ű���.
				m_User.Set_GameRoomInfo( Deserialize<nProtoGLasdf.GameRoomInfo>(rd.GameRoomInfo) );
				m_CMD.Log(nUtil.jDumper.NamedDump(m_User.m_GameRoomInfo, m_MSG.m_PacketLogType));
			}
			public override void OnRecv_FromMSG(MSG.AnsLeaveGame rd)  /**  ���� �����⿡ ���� ���� �޽��� */
			{
				if (rd.LeaveInfo == null)
				{
					m_CMD.Log("LeaveInfo = null");
				}
				else if(rd.LeaveInfo.Length>1)
				{
					string str = Deserialize<string>(rd.LeaveInfo);
					m_CMD.Log("LeaveInfo="+ str);
				}
			}
			public override void OnRecv_FromMSG(MSG.AnsClose rd)
			{
				m_User.m_eEUserGPS = EUserGPS.eUGPS_LOGOUT;
				m_MSG.Logout(this);
			}
			public override void OnRecv_FromMSG(MSG.AnsPlug rd)  /**  ������ ��� �޽���  */
			{
			}
			public override void OnRecv_FromMSG(MSG.AnsNotice rd)  /**  �������� ���� �޽��� */
			{
			}
			public override void OnRecv_FromMSG(MSG.AnsError rd) /**  ������ �߻����� ����� ó�� */
			{

			}
			public override void OnRecv_FromMSG(MSG.AnsDB rd)  /**  ��� ��û�� ���� ���� �޽��� */
			{
				NetWarning("[Recv]AnsDB => Unkown data: " + nNWM.nUtil.jDumper.NamedDump(rd, m_MSG.m_PacketLogType));

			}

			public override void OnRecv_Unkown(MSG.AnswerMessage ans) // �˼� ���� ug.proto �޼���.
			{

			}

			//#--------------------------------------------------------------------------
			// game logic Recv interface
			//#--------------------------------------------------------------------------
			public override void OnRecv_FromUserGateServer(byte[] recvByte)// usergate�� db �������� ���� �޴� �޼���. 
			{
				NetLog("[Recv FromUserGateServer]", true);
			}
			public override void OnRecv_FromGameServer(byte[] recvByte)// game server�� ���� �޴� �޼���. 
			{
				/* ���� �ڵ�
				var rd = Deserialize<nProtoGSasdf.GameServer_Client>(recvByte);
				NetLog("[Recv:bs]" + rd.type.ToString(),true);

				nNWM.nDummy.NetEventArg arg;
				arg.plugin = this;
				arg.recvData = rd;
				m_MSG.CallNetEvent("GameServer_Client", rd.type.ToString(), arg);
				*/
			}

			//#--------------------------------------------------------------------------
			//  game logic protocal
			//#--------------------------------------------------------------------------
			private void onRecv_FromUG_AnsDB_GameInfo(int next_index, string sQuery, MSG.AnsDB rd)
			{

				return;
			}//onRecv_FromUG_AnsDB_GameInfo

		}//public class NetEventPlugin_asdf : nDummy.NetEventPlugin


	}//namespace nASDF
}//namespace nNWM
