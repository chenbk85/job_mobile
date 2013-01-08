using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using nNWM;
using user_id_t = System.Int64;

namespace nNWM
{
	namespace nBaseball
	{
		public class NetEventPlugin_baseball : nDummy.NetEventPlugin
		{
			public jUser m_User;

			public NetEventPlugin_baseball(user_id_t pp_id, CmdEventManager gui, NetEventManager msg)
			{
				m_User = new jUser(this);

				//Debug.Log("NetEventPlugin_baseball create" + pp_id);
				m_UserID = pp_id;
				m_CMD = gui;
				m_MSG = msg;
			}
			~NetEventPlugin_baseball()
			{
				NetLog("NetEventPlugin_baseball detroy :" + m_UserID);
			}

			//#--------------------------------------------------------------------------
			// send용 함수.
			//#--------------------------------------------------------------------------
			public nProtoUG.Client_UserGateServer Make(nProtoUG.Client_UserGateServer.Type eType) { return new nProtoUG.Client_UserGateServer { type = eType }; }
			public bool send_to_ug(nProtoUG.Client_UserGateServer sd)
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

			public nProtoBS.Client_BaseballServer Make(nProtoBS.Client_BaseballServer.Type eType) { return new nProtoBS.Client_BaseballServer { type = eType }; }
			public bool send_to_gs(nProtoBS.Client_BaseballServer sd)
			{
				NetLog("[Send:gs]" + nNWM.nUtil.jDumper.NamedDump(sd.type, m_MSG.m_PacketLogType), true);
				var sendData = new MSG.ReqGameProtocol(Serialize<nProtoBS.Client_BaseballServer>(sd));
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
				m_CMD.ParseCmd("@user.req_db_table " + db_id());
			}
			public override void OnRecv_FromMSG(MSG.AnsChannel rd)	/**  채널 정보에 대한 응답 메시 */
			{
				m_CMD.Log(nNWM.nUtil.jDumper.NamedDump(rd.ChannelInfo));
			}
			public override void OnRecv_FromMSG(MSG.AnsAutoJoin rd)  /**  게임 자동 입장에 대한 응답 메시지 */
			{
				// 매치 성공했다. 이제부터는 plugin.send_to_gs()를 사용해 게임서버와 통신가능.
				m_User.Set_GameRoomInfo( Deserialize<nProtoGL.GameRoomInfo>(rd.GameRoomInfo) );
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
				m_User.m_eEUserGPS = EUserGPS.eUGPS_x2ug_goto_main;
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
				int next_index = rd.ReturnCode;
				if(next_index==19999)
				{
					NetLog("[Recv]AnsDB =>" + nNWM.nUtil.jDumper.NamedDump(rd, m_MSG.m_PacketLogType), true);
					NetError("SERVER ERROR next_index=" + next_index);
					return;
				}
				string sQuery = rd.Query;

				if (sQuery == "ug_game")
				{
					var ug2x = Deserialize<nProtoUG.UserGateServer_Client>(rd.Result);
					NetLog("[Recv:ug] " /* + ug2x.GetType().ToString() + " , " */ + ug2x.type.ToString(),true);

					nNWM.nDummy.NetEventArg arg;//(this,ug2x);
					arg.plugin = this;
					arg.recvData = ug2x;
					m_MSG.CallNetEvent("UserGateServer_Client", ug2x.type.ToString(), arg);
					return;
				}//if (sQuery == "ug_game")

				if (sQuery == "ug_echo")
				{
					NetLog("[Recv]AnsDB.ug_echo : " + rd.Result);
					return;
				}
				// "GameInfo.tbl_user" 으로 DB 테이블 요청시 사용하는경우
				if (sQuery.Contains("GameInfo."))
				{
					onRecv_FromUG_AnsDB_GameInfo(next_index, sQuery, rd);
					return;

				}//if (sQuery.Contains("GameInfo."))

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
				var rd = Deserialize<nProtoBS.BaseballServer_Client>(recvByte);
				NetLog("[Recv:bs]" /* + rd.GetType().ToString() + " , "*/ + rd.type.ToString(),true);

				nNWM.nDummy.NetEventArg arg;
				arg.plugin = this;
				arg.recvData = rd;
				m_MSG.CallNetEvent("BaseballServer_Client", rd.type.ToString(), arg);
			}

			//#--------------------------------------------------------------------------
			//  game logic protocal
			//#--------------------------------------------------------------------------
			private void onRecv_FromUG_AnsDB_GameInfo(int next_index, string sQuery, MSG.AnsDB rd)
			{
				if (next_index == 10000)
				{
					return;// 맨마지막.
				}
				m_User.m_eEUserGPS = EUserGPS.eUGPS_DB_LOAD;

				string tbl = sQuery.Substring(9);
				if (tbl == "tbl_user")
				{
					nProtoExcel.s_tbl_user user = nNWM.nDummy.NetEventPlugin.Deserialize<nProtoExcel.s_tbl_user>(rd.Result);
					NetLog("[Recv:table]" + nUtil.jDumper.NamedDump(user, m_MSG.m_PacketLogType));
					m_User.add_tbl_user(user);
				}

				m_User.Inc_tbl_record(tbl, next_index);
				if (next_index == 9999)
				{
					NetLog("[Recv:finish]"+ tbl + " ");
					return;
				}

				var db = new MSG.ReqDB
				{
					Seq = rd.Seq + 1,
					Query = sQuery,
				};
				db.Params.Add(new MSG.DBIn
				{
					Type = MSG.DBIn.TypeEnum.Int,
					Value = next_index.ToString(),
				});
				send_to_MSG(db, sQuery + ":" + next_index.ToString());
				return;
			}//onRecv_FromUG_AnsDB_GameInfo

		}//public class NetEventPlugin_baseball : nDummy.NetEventPlugin


	}//namespace nBaseball
}//namespace nNWM
