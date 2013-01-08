/* file : jScriptClientEntity.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-12-06 22:00:06
title : 
desc : 

*/

#ifndef __jScriptClientEntity_headerasdf232deg3445__
#define __jScriptClientEntity_headerasdf232deg3445__
#pragma once

/*! This class implements script-functions for exposing the scripting system functionalities
	lua객체 이름 jIClientEntity

콘솔에서 명령 예 : 
	#jIClientEntity:ProcessMessage(231,"MoveTo", "DOCIMP:Pos=23,32,23");
	serverindex 231객체에 대해 MoveTo  GetDocImp()->Find(TEXT("Pos")) 의 값에 x=23,y=32,z=23를 세팅후 메세지보냄.


	#jIClientEntity:ProcessMessage(231,"Attack", 222);
	serverindex 231객체가 222객체를 타겟으로 하는 Attack 메세지 호출

*/

namespace nMech
{
	namespace nLUA
	{
		class jScriptClientEntity :
			public _ScriptableEx<jScriptClientEntity> 
		{
		public:
			jScriptClientEntity();
			virtual ~jScriptClientEntity();
			void Init(jILua *); 
			static void InitializeTemplate(jILua *pSS);

			int SendEntity(IFunctionHandler *pH);

			int SendClient(IFunctionHandler *pH);

			int SendGui(IFunctionHandler *pH);

			int SendNet(IFunctionHandler *pH);

			int EntityInfo(IFunctionHandler *pH) ;
			// xml entity의 정보를 출력하거나 세팅할때 사용.
			// #jGame:SetInfoEntity(231,"FIeldPos=32;23;2", "InvSlot=232");

			int Help(IFunctionHandler *pH) ;
		};


	}//nLUA_Sink
}//nMech



#endif // __jScriptClientEntity_headerasdf232deg3445__
