/* file : _jXE_FindByFile.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-10-29 16:20:26
title : 
desc : 

*/

#ifndef ___jXE_FindByFile_header__
#define ___jXE_FindByFile_header__
#pragma once

//g_pIXmlEntityManager->GetDoc()에서 각ENTITY TEMPLATE파일의 OBJECT3D노드가 szFile인 entity template node를 찾는 functor
struct _jXE_FindByFile 
{
	cstr szFile;
	_jXE_FindByFile(cstr sz):szFile(sz){ 	}
	bool operator()(jIE* pE)
	{
		if(pE->GetType()!=jIVar::EDcstr) return false;
		jID* pD = (jID*)pE->GetUserData();
		if(!pD) return false;
		jIE* peFind = pD->Find(jx(FILES));
		if(!peFind) return false;
		peFind = peFind->Find(_T("OBJECT3D"));

		if(peFind )
		{
			fname_t buf;
			jt_strcpy(buf,peFind->Get_cstr());
			jt_strlwr(buf);
			if(!jt_strcmp(buf,szFile)) return true;
		}
		return false;
	}
};


#endif // ___jXE_FindByFile_header__
