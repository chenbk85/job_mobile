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
	lua��ü �̸� jIClientEntity

�ֿܼ��� ��� �� : 
	#jIClientEntity:ProcessMessage(231,"MoveTo", "DOCIMP:Pos=23,32,23");
	serverindex 231��ü�� ���� MoveTo  GetDocImp()->Find(TEXT("Pos")) �� ���� x=23,y=32,z=23�� ������ �޼�������.


	#jIClientEntity:ProcessMessage(231,"Attack", 222);
	serverindex 231��ü�� 222��ü�� Ÿ������ �ϴ� Attack �޼��� ȣ��

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
			// xml entity�� ������ ����ϰų� �����Ҷ� ���.
			// #jGame:SetInfoEntity(231,"FIeldPos=32;23;2", "InvSlot=232");

			int Help(IFunctionHandler *pH) ;
		};


	}//nLUA_Sink
}//nMech



#endif // __jScriptClientEntity_headerasdf232deg3445__
