#include "stdafx.h"

#include "GRCUtil.h"
#include <map>
#include <vector>
#include <string>

using namespace std;

CGRCUtil::CGRCUtil()
{
	m_tcharDelimitString=NULL;
	m_tcharToken=NULL;
	memset( m_tcharTokenStringBuffer, 0, 1024 );
}

CGRCUtil::~CGRCUtil()
{

}


std::string CGRCUtil::GetGRCPath( long lSSN )
{
	std::string stringPath;
	std::map<long,std::string> mapSSNPath;
	std::vector<long> vectorSSN;
	std::vector<std::string> vectorPath;
	TCHAR tcharTempBuffer[512];
	TCHAR tcharSSNBuffer[512];
	DWORD dwRet=::GetPrivateProfileString( _T("GRC"), NULL, _T("GRC"), tcharSSNBuffer, sizeof(tcharSSNBuffer), _T("GRCConfig.INI") );
	DWORD dwRead=0;
	TCHAR *tcharSSN=tcharSSNBuffer;
	while( dwRead<dwRet ){
		::GetPrivateProfileString( _T("GRC"), tcharSSN, _T("GRC"), tcharTempBuffer, sizeof(tcharTempBuffer), _T("GRCConfig.INI") );
		// write dll name
		long lSSN=::atol( tcharSSN );
		long lLen=(long)strlen(tcharSSN) + 1;
		dwRead+=lLen;
		tcharSSN+=lLen;

		mapSSNPath[lSSN]=tcharTempBuffer;
	}

	return mapSSNPath[lSSN];
}

/*
void CGRCUtil::SetTokenString( tstring stringTokenString, TCHAR *tcharDelimitString )
{
	memset( m_tcharTokenStringBuffer, 0, 1024 );

	strcpy( m_tcharTokenStringBuffer, stringTokenString.c_str() );

	m_tcharToken=NULL;
	m_tcharDelimitString=tcharDelimitString;
}
*/

TCHAR *CGRCUtil::GetToken( void )
{
	if( m_tcharToken==NULL ){
		m_tcharToken=strtok( m_tcharTokenStringBuffer, m_tcharDelimitString );
	}else{
		m_tcharToken=strtok( NULL, m_tcharDelimitString );
	}

	return m_tcharToken;
}

