/* file : net_ToString.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-10-30 11:46:04
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __23n32et32_32T32o32S3t32r32ing_header232_2_
#define __23n32et32_32T32o32S3t32r32ing_header232_2_
#pragma once

namespace nMech
{

	inline void jDebugPrint(nMech::tcstr szName, nMech::wcstr msg){	GetjILog()->LogPlus(_T("%s :%s ") , szName, jT(msg));}
	inline void jDebugPrint(nMech::tcstr szName, const std::vector<WCHAR> &msg){jDebugPrint(szName,&msg[0]);	}

	inline void jDebugPrint(nMech::tcstr szName, nMech::acstr msg){	GetjILog()->LogPlus(_T("%s :%s "), szName, jT(msg));}
	inline void jDebugPrint(nMech::tcstr szName, const std::vector<CHAR> &msg){jDebugPrint(szName,&msg[0]);}

	inline void jDebugPrint(nMech::tcstr szName, const std::astring &msg){jDebugPrint(szName ,msg.c_str());}
	inline void jDebugPrint(nMech::tcstr szName, vector<astring>& msg)	{		GetjILog()->LogPlus(_T("%s.size()=%d ") , szName,msg.size());	}


	inline void jDebugPrint(nMech::tcstr szName, const std::wstring &msg){jDebugPrint(szName ,msg.c_str());}
	inline void jDebugPrint(nMech::tcstr szName, vector<wstring>& msg){	GetjILog()->LogPlus(_T("%s.size()=%d") , szName,msg.size());}

	inline void jDebugPrint(nMech::tcstr szName, nMech::int16 msg){GetjILog()->LogPlus(_T("%s:%d "),szName,msg);}
	inline void jDebugPrint(nMech::tcstr szName, nMech::int32 msg){	GetjILog()->LogPlus(_T("%s:%d "),szName,msg);}
	inline void jDebugPrint(nMech::tcstr szName, nMech::uint32 msg)	{		GetjILog()->LogPlus(_T("%s:%u "),szName,msg);	}
	inline void jDebugPrint(nMech::tcstr szName, nMech::uint64 msg)	{		GetjILog()->LogPlus(_T("%s:%u "),szName,msg);	}
	inline void jDebugPrint(nMech::tcstr szName, float msg)	{		GetjILog()->LogPlus(_T("%s:%f "),szName,msg);	}
	inline void jDebugPrint(nMech::tcstr szName, bool msg)	{		GetjILog()->LogPlus(_T("%s:%s "),szName,msg?jS(true):jS(false));	}
	inline void jDebugPrint(nMech::tcstr szName, SYSTEMTIME msg)
	{
		GetjILog()->LogPlus(_T("%s:[%04d-%02d-%02d %02d:%02d:%02d] "),szName
			,msg.wYear , msg.wMonth , msg.wDay , msg.wHour , msg.wMinute , msg.wMilliseconds/1000);
	}
	inline void jDebugPrint(nMech::tcstr szName, nMech::jIE* msg){		if(msg)msg->DebugPrint(true);	}
	inline void jDebugPrint(nMech::tcstr szName, nMech::int64 msg)	{		GetjILog()->LogPlus(_T("%s = %I64d ") , szName,msg);	}
	inline void jDebugPrint(nMech::tcstr szName, std::vector<int8> &msg){}
	inline void jDebugPrint(nMech::tcstr szName, std::vector<int16> &msg){}
	inline void jDebugPrint(nMech::tcstr szName, std::vector<int32> &msg){}
	inline void jDebugPrint(nMech::tcstr szName, std::vector<int64> &msg){}
	inline void jDebugPrint(nMech::tcstr szName, std::vector<uint8> &msg){}
	inline void jDebugPrint(nMech::tcstr szName, std::vector<uint16> &msg){}
	inline void jDebugPrint(nMech::tcstr szName, std::vector<uint32> &msg){}
	inline void jDebugPrint(nMech::tcstr szName, std::vector<uint64> &msg){}
	inline void jDebugPrint(nMech::tcstr szName, DWORD &msg){}

}


#endif // __23n32et32_32T32o32S3t32r32ing_header232_2_
