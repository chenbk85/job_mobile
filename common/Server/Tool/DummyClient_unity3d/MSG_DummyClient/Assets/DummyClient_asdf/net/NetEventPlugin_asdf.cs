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
			// send용 함수.
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
			// ug.proto Recv 인터페이스.
			//#--------------------------------------------------------------------------
			public override void OnRecv_FromMSG(MSG.AnsConnect rd)/**  접속에 대한 응답 메시지 */
			{
				var gameInfo = new MSG.ReqInfo { };
				send_to_MSG(gameInfo);
			}

			public override void OnRecv_FromMSG(MSG.AnsInfo rd)  /**  본인 정보에 대한 응답 메시지 */
			{
				//m_CMD.ParseCmd("@user.req_db_table " + db_id());// 디비테이블 정보 요청
			}
			public override void OnRecv_FromMSG(MSG.AnsChannel rd)	/**  채널 정보에 대한 응답 메시 */
			{
				m_CMD.Log(nNWM.nUtil.jDumper.NamedDump(rd.ChannelInfo));
			}
			public override void OnRecv_FromMSG(MSG.AnsAutoJoin rd)  /**  게임 자동 입장에 대한 응답 메시지 */
			{
				// 매치 성공했다. 이제부터는 plugin.send_to_gs()를 사용해 게임서버와 통신가능.
				m_User.Set_GameRoomInfo( Deserialize<nProtoGLasdf.GameRoomInfo>(rd.GameRoomInfo) );
				m_CMD.Log(nUtil.jDumper.NamedDump(m_User.m_GameRoomInfo, m_MSG.m_PacketLogType));
			}
			public override void OnRecv_FromMSG(MSG.AnsLeaveGame rd)  /**  게임 나가기에 대한 응답 메시지 */
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
			public override void OnRecv_FromMSG(MSG.AnsPlug rd)  /**  재접속 허용 메시지  */
			{
			}
			public override void OnRecv_FromMSG(MSG.AnsNotice rd)  /**  공지사항 응답 메시지 */
			{
			}
			public override void OnRecv_FromMSG(MSG.AnsError rd) /**  에러가 발생했을 경우의 처리 */
			{

			}
			public override void OnRecv_FromMSG(MSG.AnsDB rd)  /**  디비 요청에 대한 응답 메시지 */
			{
				NetWarning("[Recv]AnsDB => Unkown data: " + nNWM.nUtil.jDumper.NamedDump(rd, m_MSG.m_PacketLogType));

			}

			public override void OnRecv_Unkown(MSG.AnswerMessage ans) // 알수 없는 ug.proto 메세지.
			{

			}

			//#--------------------------------------------------------------------------
			// game logic Recv interface
			//#--------------------------------------------------------------------------
			public override void OnRecv_FromUserGateServer(byte[] recvByte)// usergate의 db 로직으로 부터 받는 메세지. 
			{
				NetLog("[Recv FromUserGateServer]", true);
			}
			public override void OnRecv_FromGameServer(byte[] recvByte)// game server로 부터 받는 메세지. 
			{
				/* 샘플 코드
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
