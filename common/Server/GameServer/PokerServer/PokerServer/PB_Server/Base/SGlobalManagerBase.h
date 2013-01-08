#ifndef SGLOBALMANAGERBASE_H
#define SGLOBALMANAGERBASE_H




interface ISGlobalManager : public IXObject
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// 지정된 시간에 해당  GRC의 OnTimer 함수를 부른다
	// 인자 : GRC의 SSN, Due Time(밀리초단위), Period (밀리초단위)
	// 리턴 :enum GRCGLOBAL::GLOBAL_ERRORCODE
	virtual long __stdcall SetTimerInGlobalObject(long lSSN, long* plTimerIndex, long lDueTime, long lPeriod) = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// RemoveTimerInGlobalObject 에서는 SetTimer에서 지정했던 Index를 넣는다.
	// 프로세스 종료시 타이머도 사라지므로, RemoveTimerInGlobalObject는 필요한 경우에만 사용한다.
	// 인자 : GRC의 SSN, SetTimerInGlobalObject시 받은 Index
	// 리턴 : enum GRCGLOBAL::GLOBAL_ERRORCODE
	virtual long __stdcall RemoveTimerInGlobalObject(long lSSN, long lIndex) = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Multicast Message를 보내기 위한 함수, 2010.12 현재  미구현 되었음
	// 인자 : GRC의 SSN, MsgType(SGSSGS.adl에 정의)다른 SGS로 보내기 위한 GBuf 
	// 리턴 : enum GRCGLOBAL::GLOBAL_ERRORCODE
	virtual long __stdcall SendMulticastMsgInGlobalObject(long lSSN, long lMsgType, GBuf& gGRCMsg) = 0;


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// DB Access Interface
	// 인자 : 쿼리타입, SSN, Indata, outdata, result 
	// 리턴 : TRUE/FALSE
	virtual long __stdcall ExecuteQueryToDBInGlobalObject(long lQueryType, long lDBType, const char* szQuery, long lSize, GBuf& bufReturn, long* plResult) = 0;

};





#endif //!SGLOBALMANAGERBASE_H