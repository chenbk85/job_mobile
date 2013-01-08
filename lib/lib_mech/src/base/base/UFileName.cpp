/* file : UFileName.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-01-28 11:29:45
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "base/UFileName.h"


namespace nMech
{
	namespace nFileSystem
	{

		bool UFileName::IsFileExist()
		{
			jFolder dm;
			dm.GotoStartDir();
			return dm.Is_Exist(buffer);
		}

	}//nFileSystem
}//nMech