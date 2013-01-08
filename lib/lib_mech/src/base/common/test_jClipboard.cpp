/* file : test_jClipboard.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-13 18:52:13
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "base/jTestUnit.h"
#include "header/jClipboard.h"

using namespace nMech;
namespace 
{
	jTEST_SUITE_BEGIN(nHEADER_)
	jTEST(jClipboard_)
	{
		tcstr sztest = _T("하하하 호호호");
		nHEADER::jClipboard::SetText(sztest);

		fname_t buf;
		buf[0]=0;
		nHEADER::jClipboard::GetText(buf,sizeof(buf));

		jCHECK(!jt_strcmp(sztest, buf));


	}

	jTEST_SUITE_END(nHEADER_)
}


