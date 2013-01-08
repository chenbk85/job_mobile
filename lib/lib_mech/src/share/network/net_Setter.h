/* file : net_Setter.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-03-31 10:46:03
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __net_Setter_header__
#define __net_Setter_header__
#pragma once

namespace nTR_net
{
	inline void jSetter(std::wstring dest, wcstr src){ dest = src;};
	inline void jSetter(std::string dest, acstr src){ dest = src;};

	inline void jSetter(CHAR* dest, acstr src,int itot){ja_strncpy(dest, src,itot-1);dest[itot-1]=0;}
	inline void jSetter(WCHAR* dest, wcstr src,int itot){jw_strncpy(dest, src,itot-1);dest[itot-1]=0;}

	inline acstr jGetter(std::string& v){ return v.c_str();}
	inline wcstr jGetter(std::wstring& v){ return v.c_str();}

	template<typename T> T StringToVal(std::wstring v)
	{ 
		return jw_atoi(v.c_str());
	}
	
	template<> inline float StringToVal<float>(std::wstring v)
	{ 
		return jw_atof(v.c_str());
	}

	inline void jSetter(username_t dest, acstr src){ja_strncpy(dest, src,sizeof(dest)-1);dest[sizeof(dest)-1]=0;}


}


#endif // __net_Setter_header__
