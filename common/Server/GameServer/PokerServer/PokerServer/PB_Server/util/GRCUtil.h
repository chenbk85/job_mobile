#pragma once 

#include "../include/Gstring.h"

class CGRCUtil
{
public:
	CGRCUtil();
	virtual ~CGRCUtil();

	std::string GetGRCPath( long lSSN );

	TCHAR m_tcharTokenStringBuffer[1024];
	TCHAR *m_tcharToken;
	TCHAR *m_tcharDelimitString;

	//void SetTokenString( tstring stringTokenString, TCHAR *tcharDelimitString );
	TCHAR *GetToken( void );
};