/* file : jGlobal.h
Coder : by icandoit (mech12@nate.com)
Date : 2005-06-07 23:14:22
title : 
desc : 

*/

#ifndef __jGlobal_headInterfaceLoaderer__
#define __jGlobal_headInterfaceLoaderer__
#pragma once

namespace nMech
{

	//--------------------------------------------------------------------------
	struct jInterfaceLorder
		//--------------------------------------------------------------------------
	{
		jID* m_pD;
		jInterfaceLorder(jID*);
		virtual ~jInterfaceLorder();
	};

}

#endif // __jGlobal_headInterfaceLoaderer__
