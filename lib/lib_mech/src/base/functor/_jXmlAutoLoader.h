/* file : _jXmlAutoLoader.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-10-29 15:33:45
title : 
desc : 

*/

#ifndef ___jXmlAutoLoader_header__
#define ___jXmlAutoLoader_header__
#pragma once
namespace nMech
{

	struct _jXmlAutoLoader
	{	
		cstr szDir;
		_jXmlAutoLoader(cstr sz):szDir(sz){}
		void operator()(jIE* e)
		{
			if(!e->IsXmlFileNode()) return;
			nFileSystem::jFileName fn(e->Get_cstr());
			fname_t buf;
			if(!jt_strlen(fn.GetPath(buf)))
			{
				cstr sz = e->Get_cstr();
				jt_sprintf(buf, _T("%s%s"), szDir , sz);
				fn.Init(buf);
			}

			try{
				jID* pD = GetjIXml()->Load(fn.buffer);
				if(!pD) return;
				pD->SetParentLink(e);
				e->SetUserData(pD);
			}		catch(...){ 	}
		}
	};

	struct _jXmlAutoUnLoader
	{	
		_jXmlAutoUnLoader(){}
		void operator()(jIE* e)
		{
			if(!e->IsXmlFileNode()) return;
			jID* pD = (jID*)e->GetUserData();
			if(!pD) return;
			GetjIXml()->UnLoad(pD);
			e->SetUserData(0);
		}
	};

}



#endif // ___jXmlAutoLoader_header__

