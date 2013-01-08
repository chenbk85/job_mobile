/* 
	filename:	m_Util.h
	coder	:	Cho Wook Rea (mech12@dreamwiz.com)(icq:74456993) 
	comp.	:	EmailPet 
	compiler:	vc++ 6.0
	date	:	2001-10-12¿ÀÈÄ 4:03:29
	title	:	
*/


#ifndef __m_Util_h__
#define __m_Util_h__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000
#include "io.h"
#include "base/jWindow_util.h"

namespace nMech
{
	namespace nUtil
	{
		int Random(int nMin, int nMax);

		template<class T>
			void TrimMinMax(T& val , const T& tMin , const T& tMax)
		{
			if(val < tMin) val = tMin;
			if(val > tMax) val = tMax;
		}
		template void TrimMinMax(float&,const float& , const float&);
		template void TrimMinMax(long&,const long& , const long&);
		template void TrimMinMax(double&,const double& , const double&);

		template void TrimMinMax(int8&,const int8& , const int8&);
		template void TrimMinMax(int16&,const int16& , const int16&);
		template void TrimMinMax(int32&,const int32& , const int32&);


		template void TrimMinMax(uint8&,const uint8& , const uint8&);
		template void TrimMinMax(uint16&,const uint16& , const uint16&);
		template void TrimMinMax(uint32&,const uint32& , const uint32&);

	}//nHEADER

}

#endif //__m_Util_h__
