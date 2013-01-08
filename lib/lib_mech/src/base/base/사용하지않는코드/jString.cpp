/* file : jString.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2006-10-26 19:55:05
comp.: pantavision.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jString.h"

jDEFINE_SIMPLE_MEMORY(jString, 1024,16);
ostream& operator<<(ostream& os, const jString& s)
{
	os<<s.m_str;
	return os;
}

istream& operator>>(istream& is, jString& s)
{
	assert(0);
	char str[1024];
	is>> str;
	s=jString(str);
	return is;
}
