/* file : test_jIZipBuffer.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-11 16:08:01
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "base/jTestUnit.h"
#include "interface/jIZipUtil.h"

using namespace nMech;
namespace 
{
	jTEST_SUITE_BEGIN(com_util)
		CHAR* test_buffer = ";aslkdfja;sldkfa;sldkfja;lskdfjas\
												dfasdf;lkasdf			asdf;asdfa;sfdlkasdf			dfasdf;lkasdf			asdf;asdfa;sfdlkasdf\
												nUtil::jMemoryChunk mc;mc.init(2048);jxElement::writeChunk(mc);\
												nFileSystem::UFileName fn(szUrl);fname_t szUrl1;		{			fname_t buf;			_tcscpy(buf, fn.ext);			_tcscpy(fn.ext+2 , buf+1);			fname_t szPath1,szName1;			n.GetPath(szPath1);			fn.GetName(szName1);			szUrl = szUrl1;		}		fname_t szName;		fn.GetName(szName);		nFileSystem::jFolder m		dm.GotoStartDir();		if(m_iCloneRef==-1)		{			m_szCloneUrl = szUrl;		dfasdf;lkasdf			dfasdf;lkasdf			asdf;asdfa;sfdlkasdf			asdf;aksd;";

	jTEST(jIZipBuffer_test)
	{
		jCREATE_INTERFACE_AUTO(pZip, nMech::nUtil::jIZipBuffer);
		jCHECK( !pZip.empty());
		if(pZip.empty()) return;

		int org_len= strlen(test_buffer);
		pZip->Init(test_buffer ,  org_len);
		int iZipSize = pZip->GetZipSize();
		jCHECK(iZipSize< org_len);
		char* pZipBuffer = pZip->GetZipBuff();


		jCREATE_INTERFACE_AUTO(pUnZip, nMech::nUtil::jIUnZipBuffer);
		jCHECK( !pUnZip.empty());
		if(pUnZip.empty()) return;
		pUnZip->Init(pZipBuffer, iZipSize);
		jEQUAL(pUnZip->GetUnZipSize() ,org_len );
		jCHECK(!memcmp(pUnZip->GetUnZipBuff() , test_buffer, org_len ) );

	}

	jTEST_SUITE_END(com_util)
}
