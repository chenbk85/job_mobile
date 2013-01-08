인터페이스 탬플릿
: jIPacketDispatcher와 jPacketDispatcher를 교체해서 사용하세요



namespace nMech
{
	namespace nNET
	{
#define jINTERFACE_jIPacketDispatch(x) public:	\

		jINTERFACE_END_BASE1(jIPacketDispatch, nInterface::jIInterface);

		// 사용법.
		//	jIPacketDispatch* pjIPacketDispatch= jCREATE_INTERFACE(nMech::nNET::jIPacketDispatch);
		//	SAFE_RELEASE(pjIPacketDispatch);

		// 또는 
		// jCREATE_INTERFACE_AUTO(pjIPacketDispatch, nMech::nNET::jIPacketDispatch);

	}//namespace nNET

}//namespace nMech


namespace nMech
{
	namespace nNET
	{
		struct jPacketDispatch : public jIPacketDispatch
		{
		public:
			jINTERFACE_HEADER(jIInterface);
			jINTERFACE_HEADER(jIPacketDispatch);

			jPacketDispatch();
			~jPacketDispatch();
		};//struct jPacketDispatch


	} //nNET
}//nMech

#include "stdafx.h"
#include "jPacketDispatch.h"

volatile float aaa;
bool g_MsgManager_thread_quit=false;
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{

	aaa++;
	float _aaa = aaa;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

namespace nMech
{

	namespace nNET
	{
		jPacketDispatch g_jPacketDispatch;
		extern "C"
		{
			__declspec(dllexport) void* jCreateInterface(jIE* pE)	{return &g_jPacketDispatch;}
			__declspec(dllexport) void jDeleteInterface()		{}
			__declspec(dllexport) acstr jGetModuleOwnerName()	{return ("icandoit");}
		}

		jCTOR_INTERFACE(nMech::nNET::jIPacketDispatch,jPacketDispatch){return &g_jPacketDispatch;}
		jDTOR_INTERFACE(nMech::nNET::jIPacketDispatch,jPacketDispatch){}
		jPacketDispatch::jPacketDispatch(){}
		jPacketDispatch::~jPacketDispatch(){}
	} //nNET

}//nMech
