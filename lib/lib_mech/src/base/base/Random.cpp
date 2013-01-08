#include "StdAfx.h"
#include ".\random.h"
#include "mmsystem.h"


namespace nMech
{
		namespace nUtil
		{

			CRandom::CRandom(VOID)
			{
			}

			CRandom::~CRandom(VOID)
			{
			}

			BOOL CRandom::Init(UINT seed)
			{
				mSeed = seed;

				return TRUE;
			}

			INT CRandom::Rand(VOID)
			{
				return( ((mSeed = mSeed * 214013L + 2531011L) >> 16) & 0x7FFF );
			}

			INT CRandom::SimpleRandom(VOID)
			{
				return( ((mSeed = mSeed + 2531011L) >> 3) & 0x7FFF );
			}

			INT CRandom::ComplexRandom(VOID)
			{
				UINT next = mSeed;
				INT  result;

				next *= 1103515245;
				next += 12345;
				result = (UINT) (next / 65536) % 2048;

				next *= 1103515245;
				next += 12345;
				result <<= 10;
				result ^= (UINT) (next / 65536) % 1024;

				next *= 1103515245;
				next += 12345;
				result <<= 10;
				result ^= (UINT) (next / 65536) % 1024;

				mSeed = next;
				return result;
			}


			JBASE_API int Randomi(int min,int max)
			{
				if(min > max)
				{
					SWAP(min,max);
				}
				if(min==max)return min;
				int ival = min;
#if 0
				srand( (unsigned)time( NULL )+ival );
				int val = rand() % (max-min);
#else
				nUtil::CRandom r;
				int asdf1[]={233,745,89,2389,3983,398,2,3,1234,3,231,554,4567,67,6237,657,123,382,64,275,275,254,2546,345};
				static int asdf = timeGetTime();
				asdf = asdf1[asdf%ARRAY_SIZE(asdf1)];
				r.Init((unsigned)::timeGetTime()*ival*asdf);
				r.Rand();
				int val = r.ComplexRandom() %(max-min);
				asdf = val* (val*val*asdf);
#endif
				return min+val;
			}
			JBASE_API float Randomf(float min,float max)
			{
				if(min > max)
				{
					SWAP(min,max);
				}
				if(min==max) return min;
#if 0
				srand( (unsigned)time( NULL ) );
				int val = rand() % ((int)((max-min)*1000));
#else
				nUtil::CRandom r;
				int asdf1[]={233,745,89,2389,3983,398,2,3,1234,3,231,554,4567,67,6237,657,123,382,64,275,275,254,2546,345};
				static int asdf = timeGetTime();
				asdf = asdf1[asdf%ARRAY_SIZE(asdf1)];
				r.Init((unsigned)::timeGetTime()*asdf);
				r.Rand();
				int val = r.ComplexRandom() % ((int)((max-min)*1000));
#endif
				int iMin = (int)(min*1000);
				return ((float)(val+iMin))/1000.f;
			}

		}// nNet::nUTIL
}//nMech


