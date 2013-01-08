//#include "stdafx.h"
#include "FileLog.h"
#include "mech_lib/header/jFormat.h"

//#include "../../Protocol Buffers/Poker/AdlGameCommon.h"

//using namespace adl;

void CFileLog::Set( char* sProjectName )
{
	//
	//	프로젝트명을 지정한다.
	//

	m_sProjectName.clear();
	if( sProjectName!=NULL )
		m_sProjectName=::format("%s", sProjectName);
}


void CFileLog::Set( string sProjectName )
{
	m_sProjectName.clear();
	if( !sProjectName.empty() )
		m_sProjectName=sProjectName;
}


void CFileLog::DebugLog(LPCTSTR fmt,...)
{
	//
	//	DEBUG 모드일 경우만 로그를 남긴다.
	//

#ifdef _DEBUG
	char buf[1024];
	va_list vl;
	va_start(vl, fmt);
	vsnprintf(buf, 1024, fmt, vl);
	buf[1023]=0;
	va_end(vl);

	FileWrite(buf);
#endif
}

void CFileLog::Log_Test_Release(LPCTSTR fmt,...)
{
#if defined(_DEBUG) || defined(TEST_RELEASE)
	char buf[1024];
	va_list vl;
	va_start(vl, fmt);
	_vsnprintf(buf, 1024, fmt, vl);
	buf[1023]=0;
	va_end(vl);

	FileWrite(buf);
#endif
}

void CFileLog::Log(LPCTSTR fmt,...)
{
	//
	//	DEBUG, RELEASE 모드에 상관없이 로그를 남긴다.
	//

	char buf[1024];
	va_list vl;
	va_start(vl, fmt);
	vsnprintf(buf, 1024, fmt, vl);
	buf[1023]=0;
	va_end(vl);

	FileWrite(buf);
}

void CFileLog::Log_ASSERT( bool bValid, LPCTSTR fmt,...)
{
	jASSERT(bValid);
	if( !bValid ){
		char buf[1024];
		va_list vl;
		va_start(vl, fmt);
		vsnprintf(buf, 1024, fmt, vl);
		buf[1024]=0;
		va_end(vl);

		FileWrite(buf);
	}
}


void CFileLog::FileWrite(char* buf)
{
	//
	//	파일에 스트링을 저장
	//

	if( m_sProjectName.empty() )
		return;

	SYSTEMTIME time;
	GetLocalTime(&time);
	aname1024_t buf12;
	ja_sprintf(buf12, "C:\\Log\\%s\\%sSvr_%02d%02d.txt", m_sProjectName.c_str(),m_sProjectName.c_str(),time.wMonth,time.wDay);
	string sFileName=buf12;

	FILE* fp=NULL;
	fp=fopen(sFileName.c_str(), "a+");
	if(fp==NULL)
	{
		string sDirectoryName;
		sDirectoryName.clear();
		sDirectoryName=::format("C:/Log");
		CreateDirectory(sDirectoryName.c_str(), NULL);
		sDirectoryName+=::format("/%s",m_sProjectName.c_str());
		CreateDirectory(sDirectoryName.c_str(), NULL);
		fp=fopen(sFileName.c_str(), "a+");
		if(fp==NULL)
			return;
	}

	string sText=::format("[%02d:%02d:%02d]: %s\n", time.wHour,time.wMinute,time.wSecond,buf);
	fwrite(sText.c_str(), 1, sText.length(), fp);
	fclose(fp);
}







//void	GRC_Timer::Add_Timer( int TimerID, DWORD dwDue, DWORD	dwInterval )//,  int gen_count )
//{
//	if( TimerID <= 0 ){
//		ASSERT(0);
//		return;
//	}
//
//	int	gen_count=0;
//	if( gen_count==0 ){
//		gen_count=dwInterval>0 ? -1 : 1;
//	}
//
//
//	_TIMER_INFO	_ti;
//	_ti.TimerID=TimerID;
//	_ti.dwInterval=dwInterval;
//	_ti.dwTimeOut=dwDue;
//	_ti.Count=gen_count;
//
//	m_tlist.push_back( _ti );
//}
//
//void	GRC_Timer::Remove_Timer( int TimerID )
//{
//	ForEachElmt( std::list<_TIMER_INFO>, m_tlist, i, j )
//	{
//		if( i->TimerID==TimerID ){
//			m_tlist.erase( i );
//			return;
//		}
//	}
//}
//void	GRC_Timer::Begin_Update()
//{
//	if( m_tlist.empty() || m_dwLast==0 ){
//		m_dwPast=0;
//		m_dwLast=timeGetTime();
//	}
//	else{
//		m_it=m_tlist.begin();
//		DWORD	dwNow=timeGetTime();
//
//		if( dwNow<m_dwLast ) m_dwPast=100;
//		else m_dwPast=dwNow - m_dwLast;
//			
//		m_dwLast=dwNow;
//	}
//}
//
//int		GRC_Timer::Update()
//{
//	int ret_v=-1;
//	if( m_dwPast>0 && m_it!=m_tlist.end() ){
//		std::list<_TIMER_INFO>::iterator _inext=m_it;
//		_inext++;
//
//		if( m_it->dwTimeOut <= m_dwPast ){
//			ret_v=m_it->TimerID;
//			if( m_it->Count>0 ) m_it->Count--;
//
//			if( m_it->Count==0 ){
//				m_tlist.erase( m_it );
//			}
//			else{
//				m_it->dwTimeOut=m_it->dwInterval;
//			}
//		}
//		else{
//			m_it->dwTimeOut	-= m_dwPast;
//		}
//
//		m_it=_inext;
//	}
//	
//	return ret_v;
//}