/* file : jString_mem.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2006-10-27 10:12:33
comp.: pantavision.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jString_mem.h"

namespace nMech
{
	namespace nString
	{
		static size_t g_jStringMemSize[] = { 32, 64,256,512,1024,2048,0};
		static const size_t  g_iTot = ARRAY_SIZE(g_jStringMemSize);
		//#define _DEBUGjString_mem
#define _ORG_NEW

		TCHAR* char_p_new(size_t iLen )
		{
			//assert(sizeof(size_t) ==4);
			g_jStringMemSize[g_iTot] = iLen + iOFFSET;
			
			#define jLAMDA_great12(X,Z) Z(size_t,val)
			jLAMDA_find_if(great12,size_t)
			{
				return it >=val;
			}
			jLAMDA_end();
			
			size_t* it = find_if(&g_jStringMemSize[0], &g_jStringMemSize [g_iTot], great12(iLen+iOFFSET) );
			size_t iRealLen = *it;
			TCHAR* p = new TCHAR[iRealLen];
			p[iRealLen-1]=0;
#ifdef _ORG_NEW
			return p;
#endif
			size_t* hp = (size_t*)p;
			size_t& iSize = *hp;
			size_t capacityLen = iRealLen -iOFFSET;
			iSize = capacityLen ;
			++hp;
			p = (TCHAR*)hp;

#ifdef _DEBUGjString_mem
			size_t  size = char_p_size(p);
			jASSERT0(capacityLen== size);
#endif
			return p;
		}
		void char_p_delete(TCHAR* p )
		{
			static nUtil::jCriticalSection cs;
			jAUTO_LOCK_CS(cs);
#ifdef _ORG_NEW
			delete [] p;	return;
#endif
			size_t* hp = (size_t*)p;
			--hp;
#ifdef _DEBUGjString_mem
			size_t& iSize = *hp;
			jASSERT0(iSize >= strlen(p));
#endif
			p = (TCHAR*)hp;
			delete []p;
		}

		TCHAR* char_p_resize(TCHAR**ppch , size_t iResize)
		{
			if(!*ppch)
			{
				*ppch = char_p_new(iResize);
			}
			else	
			{
				size_t iSize = char_p_size(*ppch) ;
				if( iResize  >iSize || (iSize > 2* iResize))
				{
					char_p_delete( *ppch );
					*ppch = char_p_new(iResize);
					(*ppch)[iResize]=0;
				}
			}
			return *ppch;
		}

		size_t char_p_size(TCHAR* p) 
		{
#ifdef _ORG_NEW
			return jt_strlen(p);
#endif
			size_t * hp = (size_t*)p;
			--hp;
			size_t& iSize = *hp;
			return iSize;
		}
	}//nString
}

