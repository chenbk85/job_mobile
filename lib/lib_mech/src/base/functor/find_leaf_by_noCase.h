/* file : find_leaf_by_noCase.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-01-30 18:48:02
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef ___jxFindNoCase_leaf_header__
#define ___jxFindNoCase_leaf_header__
#pragma once

namespace nMech
{
	namespace nXML
	{
		namespace nFunctor
		{
			//--------------------------------------------------------------------------
			// �ش� �̸��� ��ҹ��� ���о��ϰ� xml���� ��� �ָ��� ��忡 ���� �˻�
			struct find_leaf_by_noCase 
				//--------------------------------------------------------------------------
			{
				cstr szName;
				find_leaf_by_noCase(cstr sz):szName(sz){ 	}
				bool operator()(jIE* itE)
				{
					if(itE->GetType() == jIVar::ETelement) return false;
#ifdef find_leaf_by_noCase_CHECK_jMX_SKIP_THIS
					jIE* pP = itE->GetParent();
					while(pP)//�����θ� jMX_SKIP_THIS �Ӽ��� ���õǸ� �ڽĵ� ��� ��ŵ
					{
						jIVar* pV = pP->GetAttrVar(_T("jMX_SKIP_THIS"));
						if(pV && pV->Get_bool()) return false;
						pP = pP->GetParent(); 
					}
#endif
					cstr sz = itE->GetTagName();
					return !jt_stricmp(sz,szName);
				}
			};

		}//namespace nFunctor
	}//namespace nXML
}

#endif // ___jxFindNoCase_leaf_header__
