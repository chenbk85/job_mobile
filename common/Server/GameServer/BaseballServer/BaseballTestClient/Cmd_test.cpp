/* file : Cmd_test.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-27 16:19:23
comp.: wiki.test.com
title : 
desc : 

*/

#include "stdafx.h"
#include "excel/code/excel_enum.h"
//#include "proto/test_contract.pb.h"


namespace nCmdTest
{

	// @test.simulate_base_runner_count 1001 eEBHT_ONEHIT
	jCONSOLE_CMD_AUTO(test,simulate_base_runner_count,0,"가상으로 게임결과 계산","<uid> <int ERunnerStateRound> [EBatterHitType]")
	{
#define jCONSOLE_PARAM_simulate_base_runner_count(X,Y) X(uid,tcstr) X(state,int) Y(_type,tcstr ,_T("NULL"))
		jCONSOLE_PARAM_END(simulate_base_runner_count);
		jFIND_USER(peSession,pUser,uid);

		EBatterHitType eType = eBEGIN_EBatterHitType;
		if(tstring(jS(NULL) ) != _type )
		{
			jCCE_ret(true,_type,EBatterHitType);
			eType = e_type;
		}
		else
		{
			eType =  (EBatterHitType)nUtil::Randomi(eBEGIN_EBatterHitType+eEBIT_LEFTFIELDOUT,eEND_EBatterHitType-1);
		}

		if(eType == eEBHT_NO_HIT)
		{
			eType =eEBHT_HOMERUN;
		}

		s_result_round* pRR= pUser->m_GameRoomInfo.add_m_result_round();
		pUser->make_round_result(pRR,eType,(ERunnerStateRound)state);

		return true;
	}

	jCONSOLE_CMD_AUTO(test,proto_contract,0,"proto_contract","")
	{
#if 0
		MyData data;
		fstream in(_T("D:\\svn\\baseball\\src\\tool\\test\\MyTest\\bin\\Debug\\MyModel.bin.data"), ios::in | ios::binary);
		if (!data.ParseFromIstream(&in)) 
		{
			cerr << "Failed to parse person.pb." << endl;
			exit(1);
		}

		if(data.has_int1())
		{
			jLOG(_T("int1 = %d"), data.int1());
		}

		if(data.has_int2())
		{
			jLOG(_T("int2 = %d"), data.int2());
		}
		TestEnum eVal = data.enum1();

		jLOG(_T("eVal = %d"), eVal);

#endif

		FILE* fp = fopen("d:\\UReqConnect.bin", "rb");
		char buf[1024];
		if(!fp) return false;
		int32 iLen=0;
		fread(&iLen,sizeof(iLen),1,fp);
		fread(buf, iLen , 1, fp);

		google::protobuf::io::ArrayInputStream ais(buf, iLen);
		UReqProtocol r;
		r.ParseFromZeroCopyStream(&ais);


// 		UReqConnect rd;
// 		fstream in(_T("d:\\UReqConnect.bin"), ios::in | ios::binary);
// 		int32 iLen;
// 		in >> iLen;
// 		UReqProtocol recvData;
// 		if(!recvData.ParseFromIstream(&in))
// 		{
// 			cerr << "Failed to parse person.pb." << endl;
// 			exit(1);
// 		}
		return true;
	}

	jCONSOLE_CMD_AUTO(test,curr_team_round,0,"curr_team_round","")
	{
		for(int i = 0; i< 18 ; ++i)
		{
			jLOG(_T("curr_team_round(%d) = %d"),i,curr_team_round(i,3) );
			if((1+i)%3==0)
			{
				jLOG(_T(""));
			}
		}
		return true;
	}


}//namespace nCmdTest

#if 0

jCONSOLE_CMD_AUTO(test,asdf,0,""echo message"","<uid>")
{
#define jCONSOLE_PARAM_asdf(X,Y) X(uid,tcstr)
	jCONSOLE_PARAM_END("echo message");
	jFIND_USER(peSession,pUser,uid);

	jMAKE_MESSAGE_X2BS(pUser,sendMsg,sd,"echo message");
	g_pPlugIn->send_to_bs(peSession,sendMsg);

	return true;
}

#endif

