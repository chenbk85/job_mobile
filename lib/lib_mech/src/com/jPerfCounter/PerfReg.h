/* file : PerfReg.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-09-03 20:55:18
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __PerfReg_header__
#define __PerfReg_header__
#pragma once

namespace nPerfReg
{
	DWORD	load_LastCounter();
	void	save_LastCounter(DWORD iLast);
	tcstr	get_MyServiceURL(fname_t buf);

	void save_Counter_Contents();
	void load_Counter_Contents();

	BOOL AddString_Help(LPCTSTR addItem);
	BOOL AddDWORD_Help(DWORD addItem);
	DWORD GetIndex_Help(LPCTSTR counterName);
	BOOL GetName_Help(DWORD index, tname32_t counterName);

	BOOL AddString_Data(LPCTSTR addItem);
	BOOL AddDWORD_Data(DWORD addItem);
	DWORD GetIndex_Data(LPCTSTR counterName);
	BOOL GetName_Data(DWORD index, tname32_t counterName);


	bool load_My_ObjectList();
	void save_My_ObjectList();
}


#endif // __PerfReg_header__
