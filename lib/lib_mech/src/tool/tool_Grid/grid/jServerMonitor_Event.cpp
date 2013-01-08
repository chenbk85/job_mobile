/* file : jServerMonitor_Event.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-04-29 00:46:56
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jGridCtrl.h"

//jGRIDCRTL_EVENT_ColRow(jServerMonitor,6,11) //DropList
jGRIDCRTL_EVENT(jServerMonitor,DYNAMIC_DROP) //DropList
{
	if(pE->IsName(jS(DropList)))
	{
		switch(msg)
		{
		case UGCT_DROPLISTSTART:
			{
				jIE* peDropList = pE;// pE는 DropList 루트를 가르킴.
				break;
			}
		case UGCT_DROPLISTSELECTEX:
			{
				jIE* it = pE; // pE는 DropList의 선택된 아이템을 가르킴.
				jLOG(jFUNC1 _T("%s , msg=%d, select=%s") , pE->GetParent()->GetAttr(jS(Name)) , msg, it->Get_cstr());
				break;
			}
		}
	}
	else if(pE->IsName(jS(Menu)))
	{
		jLOG(jFUNC1 _T("%s , msg=%d, item=%s") , pE->GetParent()->GetAttr(jS(Name)) , msg, pE->FindByOrder(param)->Get_cstr());
	}
	return TRUE;
}

jGRIDCRTL_EVENT_ColRow(jServerMonitor,6,21) // CheckBox
{
	jLOG(jFUNC1 _T("%s , msg=%d, param=%d") , pE->GetAttr(jS(Value)) , msg, param);
	return TRUE;
}

jGRIDCRTL_EVENT(jServerMonitor,RadioTest) // Radio
//jGRIDCRTL_EVENT_ColRow(jServerMonitor,4,28) // Radio
{
	jLOG(jFUNC1 _T("%s, msg=%d, item=%s") ,pE->GetParent()->GetTagName() , msg , pE->Get_cstr() );
	return TRUE;
}

jGRIDCRTL_EVENT(jServerMonitor,btn_test) // Button
{
	jLOG(jFUNC1 _T("%s, msg=%d, param=%d") ,pE->GetTagName() , msg , param);
	return TRUE;
}

jGRIDCRTL_EVENT(jServerMonitor,ellipsis_test) // EllipsisButton
{
	jLOG(jFUNC1 _T("%s, msg=%d, param=%d") ,pE->GetAttr(jS(Name)) , msg , param);
	return TRUE;
}


jGRIDCRTL_EVENT(jServerMonitor,spin_test) // spin
{
	jLOG(jFUNC1 _T("%s, msg=%d, param=%d") ,pE->GetAttr(jS(Name)) , msg , param);
	return TRUE;
}
