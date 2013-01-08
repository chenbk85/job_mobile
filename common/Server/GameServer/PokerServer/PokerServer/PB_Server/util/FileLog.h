#ifndef __FILELOG_H__
#define __FILELOG_H__

#include "config_all_server.h"

#if !defined(DEF_LINUX)
#include <windows.h>
#endif
#include <string>
#include <ctime>

using namespace std;

class CFileLog
{
public:
	CFileLog(){m_sProjectName.clear();}
	~CFileLog(){};
	
	void Set( char* pProjectName );
	void Set( string sProjectName );
	void DebugLog(LPCTSTR fmt,...);
	void Log(LPCTSTR fmt,...);

	// ��� comment (2008-04-23) : �������� �ְ� �;����� ^^;;;
	void Log_ASSERT( bool bValid, LPCTSTR fmt,...);
	
	// ��� comment (2008-09-05) : DEBUG �� TEST_RELEASE �϶��� �α׸� ����.
	void Log_Test_Release(LPCTSTR fmt,...);

private:	
	void FileWrite(char* buf);
	string m_sProjectName;
};





//class GRC_Timer
//{
//public:
//	GRC_Timer(){Clear_All();}
//	void	Clear_All(){ m_tlist.clear(); m_dwPast=0; m_it=m_tlist.end(); m_dwLast=0;}
//	// gen_count<0 : �ݺ������� ��� �߻��Ѵ�.
//	void	Add_Timer( int TimerID, DWORD dwDue, DWORD	dwInterval );//, int gen_count=0 );
//	void	Remove_Timer( int TimerID );
//	
//	void	Begin_Update();
//	int		Update();
//
//protected:    
//	typedef struct _timer_info{
//		DWORD		dwTimeOut;
//		DWORD		dwInterval;
//		int			TimerID;
//		int			Count;
//	}_TIMER_INFO;
//	
//	std::list<_TIMER_INFO>					m_tlist;
//	std::list<_TIMER_INFO>::iterator		m_it;
//	DWORD									m_dwPast, m_dwLast;
//};









#endif
