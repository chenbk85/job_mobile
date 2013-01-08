/* file : jServerMonitor.h
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-04-14 13:40:41
comp.: rocworks.co.kr
title : 
desc : 

*/

#ifndef __jServerMonitor_header__
#define __jServerMonitor_header__
#pragma once

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../tool_Grid/grid/jGridCtrl.h"



class jServerMonitor : public jGridCtrl
{
public:
	jServerMonitor::jServerMonitor(jIE* pE) : jGridCtrl(pE)
	{

	}
	virtual jServerMonitor::~jServerMonitor()
	{

	}

	DECLARE_MESSAGE_MAP()

};


#endif // __jServerMonitor_header__
