/* file : jPlayerList_Dummy.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-11-05 16:27:16
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jPlayerList_Dummy_header__
#define __jPlayerList_Dummy_header__
#pragma once

class jPlayerList_Dummy : public jPlayerList
{
public:
	jServerInfo m_si_Login;

	vector<jWorldServerInfo> m_world_list;
	nEVENT::jIMsgManager* m_pMM;

	void Init();//생성자를 사용하지말것. 왜냐면 전역객체이므로 생성자사용시 dll로딩시 문제있슴.
#define for_each_PT_MEMEBER(func)\
	func(nDummyServer,DT_ONLINE)\
	
	for_each_PT_MEMEBER(jPT_MEMBER);

	dummy_id_t GetDummyID(){ return g_SG.m_MyInfo.m_sid;}//테스트 서버로부터 부여받은 더미클라이언트 아이디, DUMMY아이디(userdb_id_t)와 다름
	tcstr GetTestIDName(){ return g_SG.m_MyInfo.m_szName;}
	fname_t m_DummyName;
	bool m_isEnable;
	nEVENT::jIMessage* m_pMsg_Chat;

	jPlayerObj* find(player_name_ct szID){return (jPlayerObj*)jPlayerList::find(szID);}
	jPlayerObj* find(player_id_t pid){return (jPlayerObj*)jPlayerList::find(pid);}

	void Logout_Dummy_AllSocket(int per_user , DWORD delay );
	void Start_Login_AllDummy(int session_count_for_delay ,int delay_time_msec);

	jPlayerObj* Start_Login(player_name_ct szID,acstr szPWD="0000");
	bool RunDummyFunction(tcstr szID, tr1::function<void (jPlayerBase* pPlayer,DWORD delay_msec)> func ,DWORD delay_msec);
	jIPacketSocket_IOCP* GetUserSocket(player_name_ct szID , EServerType eType, jPlayerObj** ppDummy);
	void Close();
};

extern jPlayerList_Dummy g_PL;


inline jPlayerObj* ToPlayerObj(jIPacketSocket_IOCP* pS)
{	// jPlayerList_Dummy::Start_Login()에서 세팅된 것이다.
	return (jPlayerObj*)pS->Get_jIE()->GetUserData(jS(jPlayerObj));
}


#endif // __jPlayerList_Dummy_header__
