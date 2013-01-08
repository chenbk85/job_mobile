/* file : jMake_SequenceDiagrams_usd.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-09-12 16:08:17
comp.: jgame.co.kr
title : 
desc : 

*/

#ifndef __jMake_SequenceDiagrams_usd_header__
#define __jMake_SequenceDiagrams_usd_header__
#pragma once


namespace nUSD_FILE
{
	struct jNote_Etc /// enum형 정의등을 umlnote에서 추출할때 사용
	{
		tstring type; // enum
		tstring body;// enum에서 파싱안된 enumlist 가 옴.
		tstring doc; // 언급한 usd파일명.
	};
	struct jNote_Protocal
	{
		tstring name;
		tstring help;
		tstring usdFile;
		vector<std::tstring > option;
		struct _jParam
		{
			tstring name;
			tstring type;
			tstring help;
			int len;
		};
		vector<_jParam> param;
	};

	struct _jxFind_UMLSDOBJ_actBox_id
	{
		jIVar* m_pvID;
		_jxFind_UMLSDOBJ_actBox_id(jIVar* pvID):m_pvID(pvID){ 	}
		jIE* operator()(jIE*it)
		{
			if(!it->IsName(_T("actBox"))) return 0;
			if( !it->GetAttrVar(_T("id") )->IsContents(m_pvID->Get_cstr())) return 0;
			//it->DebugPrint(nInterface::g_pjILog);
			return it;
		}
	};

	struct _jxParse_OPTION
	{
		jNote_Protocal* val;
		_jxParse_OPTION(jNote_Protocal* p1):val(p1){ }
		void operator()(const std::tstring& str)
		{
			vector<std::tstring> out;
			nString::jSplit(str, _T("= \n\t"), out);
			assert(out.size()==2);
			//val->option.push_back(make_pair(out[0],out[1]) );
		}
	};

}


#endif // __jMake_SequenceDiagrams_usd_header__
