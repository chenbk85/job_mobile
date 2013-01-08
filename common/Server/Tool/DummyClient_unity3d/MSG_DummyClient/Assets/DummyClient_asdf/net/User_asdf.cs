using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using nNWM;
using user_id_t = System.Int64;

namespace nNWM
{
	namespace nASDF
	{
		public enum EUserGPS
		{
			eUGPS_LOGOUT					, //- 네트웍접속해제")
			eUGPS_LOGIN					, // -UserGate서버에접속-)")
			eUGPS_DB_LOAD					, // -UserGate서버에접속-)")

			eUGPS_UserGateServer			, //여기까지가 유저게이트서버에서의 상태")
			eUGPS_x2ug_goto_match, //매치창(멀티플레이창)")
			eUGPS_GAMEROOM				, //BaseballServer에접속 대기방상태")
			eUGPS_LABEL_GAME_NOT_QUIT		, // ")
			eUGPS_GAME_READY				, //게임 레디 한 상태")
			eUGPS_GAME_START				, //게임시작")
			eUGPS_GAME_END				, //게임을 모두 끝내고 게임종료패킷 ans_game_end 을 보냈다")
			eUGPS_GAMEROOM_PRE_LEAVE		, //로비로 갈려고 대기중인 상태-")
			eUGPS_BS_USER_IS_ILLEGAL		, //게임서버에 접속된 상태이지만 유저의 정보가 정상이 아님 강제종료대상")
			eUGPS_BS_ABNORMAL_DISCONNECT	, //해당 유저는 클라이언트가 비정상적인 TCP DISCONNECT상태이다.")

			eUGPS_GameServer			, //여기까지가 게임서버접속상태")

		}

		public class User_asdf 
		{
			public EUserGPS m_eEUserGPS = EUserGPS.eUGPS_LOGOUT;
			public NetEventPlugin_asdf m_Plugin;
			public nProtoGLasdf.GameRoomInfo m_GameRoomInfo; // gameLogic.proto첨고 할것.
			public nProtoGLasdf.GameInfo m_GameInfo = new nProtoGLasdf.GameInfo();
			public Dictionary<string, int> m_ServerInfoRecvState = new Dictionary<string, int>();

			public User_asdf(NetEventPlugin_asdf plugin) { m_Plugin = plugin; }
			public void Set_GameRoomInfo(nProtoGLasdf.GameRoomInfo gri)
			{
				m_eEUserGPS = EUserGPS.eUGPS_GAMEROOM;
				m_GameRoomInfo = gri;
			}

		}//public class User_asdf 

	}//namespace nASDF
}//namespace nNWM

