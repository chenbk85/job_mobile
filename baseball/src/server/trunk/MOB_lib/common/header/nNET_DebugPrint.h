/* file : nNET_DebugPrint.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-11-01 10:38:57
comp.: jgame.co.kr
title : 
desc : 

*/

#ifndef __nNET_DebugPrint_header__
#define __nNET_DebugPrint_header__
#pragma once

#define JVECTOR_DEBUG_PRINT

namespace nMech
{
	namespace nDB_Chaotic
	{
		namespace nCE_Debug
		{
			inline void jDebugPrint(acstr szName,std::vector<uint8> &val)
			{
				jLOG(_T("%s ="),szName);
#if 0
				for(uint i =0; i < val.size(); ++i)
				{
					jLOG(_T("%d : %u"),i, val[i]);
				}
#endif
			}
			inline void jDebugPrint(acstr szName,std::vector<uint16> &val)
			{
				jLOG(_T("%s ="),szName);
#ifdef JVECTOR_DEBUG_PRINT
				for(uint i =0; i < val.size(); ++i)
				{
					jLOG(_T("%d : %u"),i, val[i]);
				}
#endif
			}
			inline void jDebugPrint(acstr szName,std::vector<uint32> &val)
			{
				jLOG(_T("%s ="),szName);
#ifdef JVECTOR_DEBUG_PRINT
				for(uint i =0; i < val.size(); ++i)
				{
					jLOG(_T("%d : %u"),i, val[i]);
				}
#endif
			}

			inline void jDebugPrint(acstr szName, std::vector<int8>& val)
			{
				jLOG(_T("%s ="),szName);
			}
			inline void jDebugPrint(acstr szName, std::vector<int16>& val)
			{
				jLOG(_T("%s ="),szName);
			}
			inline void jDebugPrint(acstr szName, std::vector<int32>& val)
			{
				jLOG(_T("%s ="),szName);
			}

			// bool 타입 디버그 데이터 출력
			inline void jDebugPrint(acstr szName, bool val)
			{
#ifndef NOT_USE_jDebugPrint
				if(val) {
					jLOG(_T("%s is TRUE"), szName);
				} else {
					jLOG(_T("%s is FALSE"), szName);
				}
#endif
			}
			// unsigned integer 타입 디버그데이터 출력
			inline void jDebugPrint(acstr szName, uint8 val)
			{
#ifndef NOT_USE_jDebugPrint
				jLOG(_T("%s=%u"),szName, val);
#endif
			}
			inline void jDebugPrint(acstr szName, uint16 val)
			{
#ifndef NOT_USE_jDebugPrint
				jLOG(_T("%s=%u"),szName, val);
#endif
			}
			inline void jDebugPrint(acstr szName, uint32 val)
			{
#ifndef NOT_USE_jDebugPrint
				jLOG(_T("%s=%u : %d"),szName, val,val);
#endif
			}

			// integer 타입 디버그데이터 출력
			inline void jDebugPrint(acstr szName, int8 val)
			{
#ifndef NOT_USE_jDebugPrint
				jLOG(_T("%s=%d"),szName, val);
#endif
			}
			inline void jDebugPrint(acstr szName, int16 val)
			{
#ifndef NOT_USE_jDebugPrint
				jLOG(_T("%s=%d"),szName, val);
#endif
			}
			inline void jDebugPrint(acstr szName, int32 val)
			{
#ifndef NOT_USE_jDebugPrint
				jLOG(_T("%s=%d"),szName, val);
#endif
			}
			inline void jDebugPrint(acstr szName, float val)
			{
#ifndef NOT_USE_jDebugPrint
				jLOG(_T("%s=%f"),szName, val);
#endif
			}

			// ASCII 타입 디버그데이터 출력
			inline void jDebugPrint(acstr szName, acstr val)
			{
#ifndef NOT_USE_jDebugPrint
				jLOG(_T("%s=%s"),szName, val);
#endif
			}

			// Uni-code 타입 디버그 데이터 출력
			inline void jDebugPrint(acstr szName, wcstr val)
			{
#ifndef NOT_USE_jDebugPrint
				jLOG(_T("%s=%s"),szName, nMech::nUNI::StringConvertBuffer<1024>(val).getA());
#endif
			}

			inline void jDebugPrint(acstr szName, std::wstring val)		{			jDebugPrint(szName, val.c_str());		}
			inline void jDebugPrint(acstr szName, std::string val)		{			jDebugPrint(szName, val.c_str());		}

			inline void jDebugPrint(acstr szName, SYSTEMTIME val)
			{
#ifndef NOT_USE_jDebugPrint
				jLOG(_T("TIME(%s)= (%d:%d:%d %d:%d:%d)"),szName, val.wYear , val.wMonth, val.wDay, val.wHour, val.wMinute, val.wSecond);
#endif
			}


		}//nCE_Debug
	}
}


#endif // __nNET_DebugPrint_header__
