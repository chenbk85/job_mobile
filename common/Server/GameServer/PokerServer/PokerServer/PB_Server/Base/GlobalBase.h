#ifndef GLOBALBASE_H
#define GLOBALBASE_H

#include <GRCGlobal.h>
//#define interface struct

interface IGlobal
{
////////////////////////////////////////////////////////////////
// Timer 이벤트 도착시 THS로부터 불리는 함수
// 리턴 : enum GRCGLOBAL::GLOBAL_ERRORCODE
// 인자 : 타이머를 등록할때 IGlobalManager::SetTimer 의 리턴 값인 타이머 인덱스
//		  이것으로 타이머를 구별한다.
	virtual LONG __stdcall OnTimer(LONG lIndex) = 0;

////////////////////////////////////////////////////////////////
// Global Object의 객체를 생성한 후, 해당 객체의 초기화 작업을 위해 GRC에서 수행하는 함수 
// 리턴 : enum GRCGLOBAL::GLOBAL_ERRORCODE
// 인자 : 타이머를 등록할때 IGlobalManager::SetTimer 의 리턴 값인 타이머 인덱스
//		  이것으로 타이머를 구별한다.
	virtual LONG __stdcall OnInit() = 0;

////////////////////////////////////////////////////////////////
// THS 끼리의 Multicasting 메시지가 도착했을때, Global Object에 Access 해야하는 경우, THS에서 불러주는 함수 
// 리턴 : enum GRCGLOBAL::GLOBAL_ERRORCODE
// 인자 : GRC<->GRC 간의 Payload를 담은 GBuf
	virtual LONG __stdcall OnMulticastMsg(GBuf& gMsgBuf) = 0;
};





#endif //!GLOBALBASE_H