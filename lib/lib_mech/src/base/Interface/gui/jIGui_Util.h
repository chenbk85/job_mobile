/* file : jIGui_Util.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-02-07 14:50:50
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jIGui_Util_header__
#define __jIGui_Util_header__
#pragma once

namespace nMech
{
	namespace nGUI
	{

		namespace jIGui_Util
		{
			struct _jxSetVisible
			{
				bool isVisible , isEnable;
				_jxSetVisible(bool isV, bool isE):isVisible(isV), isEnable(isE){}
				void operator ()(jIE* it)
				{
					if(it->GetType()!=jIVar::ETelement) return;
					if(strncmp(it->GetTagName() ,"jGui", 4) ) return;
					jIGuiControl* pCtrl = (jIGuiControl*)it->GetUserData();
					if(!pCtrl)  return;
					pCtrl->SetVisible(isVisible);
					pCtrl->SetEnabled(isEnable);
				}
			};

			struct _jxSetVisible_WithDepth
			{
				bool isVisible , isEnable;
				char iDepth;
				_jxSetVisible_WithDepth(bool isV, bool isE,char iD):isVisible(isV), isEnable(isE),iDepth(iD){}
				void operator ()(jIE* it)
				{
					if(it->GetDepth()>iDepth) return;
					if(it->GetType()!=jIVar::ETelement) return;
					if(strncmp(it->GetTagName() ,"jGui", 4) ) return;
					jIGuiControl* pCtrl = (jIGuiControl*)it->GetUserData();
					if(!pCtrl)  return;
					pCtrl->SetVisible(isVisible);
					pCtrl->SetEnabled(isEnable);
				}
			};

		};


	}
}


#endif // __jIGui_Util_header__
