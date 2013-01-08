/* file : Random.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-08 15:51:42
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __Random_header__
#define __Random_header__
#pragma once

namespace nMech
{
		namespace nUtil
		{
			class JBASE_API CRandom
			{
			public:
				CRandom(VOID);
				virtual ~CRandom(VOID);

			private:
				UINT	mSeed;

			public:
				BOOL	Init(UINT seed);

				INT		Rand(VOID);
				INT		SimpleRandom(VOID);
				INT		ComplexRandom(VOID);
			};
			JBASE_API int Randomi(int min,int max);
			JBASE_API float Randomf(float min,float max);

		}// nNet::nUTIL

}//nMech


#endif // __Random_header__
