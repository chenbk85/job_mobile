// test.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "test.h"
#include "jRandom.h"



//======================================================================================================
// <문제1>
//
// 두 벡터의 사이각을 구하는 함수이다. 내용을 채워 넣어라.
//======================================================================================================

float CalcAngle(const D3DXVECTOR3* vOri, const D3DXVECTOR3* vDst)
{
	using namespace nMech;
	f64 LengthQ=GetLength(vOri)*GetLength(vDst);
	if(LengthQ<0.01) LengthQ=0.01;
	return((f32)(acos(Dot(vOri,vDst)/LengthQ)));
}

//======================================================================================================
// <문제2>
//
// 두 각도간의 차이를 계산하는 함수이다. 내용을 채워 넣어라.
// Angle은 360도 단위이며 리턴값은 180도 이하여야 한다.
//======================================================================================================

float CalcAngleDiff(float Angle1, float Angle2)			
{
	using namespace nMech;
	Angle1=trim_0_360(Angle1);
	Angle2=trim_0_360(Angle2);
	swap_max_min(Angle1, Angle2);

	Angle1 = Angle1- Angle2;
	if(Angle1 > 180)
	{
		Angle1 = Angle1-180;
	}
	return Angle1;

}



//======================================================================================================
// <문제3>
//
// Min, Max값이 주어졌을 때 해당 값 사이의 랜덤값을 얻어내는 함수를 작성하라.
//======================================================================================================

int	GetRandomValue(int nMin, int nMax)
{
	/*
	중복= 973 Sleep=0,cpu=2618, 생성된랜덤수=27, random_my(1,1000);
	중복= 999 Sleep=0,cpu=758, 생성된랜덤수=1, random_api(1,1000);
	중복= 369 Sleep=0,cpu=4272, 생성된랜덤수=631, random_boost(1,1000);

	중복= 356 Sleep=3,cpu=239034, 생성된랜덤수=644, random_my(1,1000);
	중복= 995 Sleep=3,cpu=238997, 생성된랜덤수=5, random_api(1,1000);
	중복= 376 Sleep=3,cpu=239214, 생성된랜덤수=624, random_boost(1,1000);

	중복= 363 Sleep=11,cpu=287753, 생성된랜덤수=637, random_my(1,1000);
	중복= 987 Sleep=11,cpu=287641, 생성된랜덤수=13, random_api(1,1000);
	중복= 370 Sleep=11,cpu=287597, 생성된랜덤수=630, random_boost(1,1000);
	*/
	//return nMech::random_api(nMin,nMax);
	//return nMech::random_boost(nMin,nMax);
	return nMech::random_my(nMin,nMax);
}



//======================================================================================================
// <문제4>
//
// 몬스터가 각각의 스킬을 사용할 확률이 다음과 같다.
// Skill* pSkill1(15), pSkill2(25), pSkill3(10)
// 각각의 확률을 100%를 기준으로 하면 실제로 15/50, 25/50, 10/50이 된다.

// pSkill1, pSkill2, pSkill3와 15, 25, 10의 입력값으로 랜덤하게 하나의 스킬(pSkill1, 2, 3)을 
// 선택하는 함수를 작성하라. 단, 반드시 특정 타입의 클래스(Skill)가 아니더라도 결과를 얻어낼
// 수 있는 형태의 Utility 클래스를 작성하라. 
//======================================================================================================
struct GetRandomObjInfo
{
	void* pObj; // 선택될 객체 포인터
	int iPercent; // 선택 확률 
};

void* GetRandomObj(std::vector<GetRandomObjInfo>& in)
{
/*
(1000번씩 100번을 반복한 평균 선택 수)

	14.7465			        25.372			        9.8815 

각각의 입력 평균치는
	15,						25,						10

선택된 평균치와 99% 정확함.
테스트 과정은 _tmain()함수를 참조하세요.

	*/
	if(in.size()==0) 
	{
		return 0;
	}

	int totPercent=0;
	for(size_t i=0; i < in.size(); ++i)
	{
		totPercent+=in[i].iPercent;
	}
	if(totPercent<=0)
	{
		return 0;
	}
	
	const int iMAX_PERCENT=1000;
	int prevPercent=0;
	int iSelect = (int )nMech::random_my(1,iMAX_PERCENT);
	size_t iCurr=0;
	for(; iCurr < in.size()-1; ++iCurr)
	{
		int iTempPercent = (in[iCurr].iPercent*iMAX_PERCENT)/(totPercent) + prevPercent;
		//printf("iTempPercent =%d ,",iTempPercent);
		if(iTempPercent>=iSelect)
			return in[iCurr].pObj;

		prevPercent += iTempPercent;
	}
	return in[iCurr].pObj;
}



//======================================================================================================
// <문제5>
//
// Player가 Monster를 향해 발사체를 날렸고 이 발사체는 적을 따라 움직이는 유도미사일이다.
// 발사체는 Player위치로부터 10m거리(사거리) 밖에서 날아갔고 Player의 속도는 5m/s 발사체의 속도는 4m/s이다.
// 이때 발사체의 유도미사일 기능을 중심으로 클래스를 구현하라.
// 또 이 유도미사일의 기능을 테스트 할 수 있는 로직도 구현해야 된다. 
// ex) Player의 최초 위치와 발사체의 최초 위치 랜덤. 이후 Player가 특정 방향으로 랜덤하게 움직임.
// 예외적인 상황이 없을지에 대해서 충분히 검토하고 본인이 가장 합리적이라고 생각하는 정책으로 구현하면 된다.
//======================================================================================================
/*

죄송합니다. 
문제가 전형적인 게임로직인데 나름 재밌겠으나 데이타 설계및 전체 돌아가는 테스트 프로그램까지 만들려면 
시간이 많이 걸릴것 같아 포기하고 싶습니다. -_-;

꼭 풀기를 원하시면 다시 답장을 주세요.
최선을 다해 정성껏 풀도록 하겠습니다.

*/ 

//======================================================================================================
// <문제6>
//
// 주로 서버에서 SendBuffer와 RecvBuffer를 위해 사용되는 RingBuffer를 구현하라.
// 필요하다면 새로운 함수를 선언하거나 기존 함수를 제거해도 된다. 
// 하지만 Write, Read, Peek는 반드시 구현할 것!
//======================================================================================================
#include "jRingBuffer.h"
// 개인적으로는 링버퍼를 안쓰며. 패킷사이즈별 패킷 풀(128,256,1024,2048,4096, ...)을 이용합니다.



int _tmain(int argc, _TCHAR* argv[])
{
	using namespace nMech;
#if 0
	{// test CalcAngleDiff
		for(float a1= -400.f ; a1 < 400.f;  a1=a1+3.3f)
		{
			for(float a2= -400.f ; a2 < 400.f;  a2=a2+6.7f)
			{
				float a = CalcAngleDiff(a1,a2);
				assert(a>=0 && a<=180);
				printf("%8.3f = CalcAngleDiff(%8.3f,%8.3f);\n",a,a1,a2);
			}
		}
	}
#endif

#if 0
	{ // test GetRandomValue
		test_random(random_my,"random_my",0);
		test_random(random_api,"random_api",0);
		test_random(random_boost,"random_boost",0);


		test_random(random_my,"random_my",3);
		test_random(random_api,"random_api",3);
		test_random(random_boost,"random_boost",3);

		test_random(random_my,"random_my",11);
		test_random(random_api,"random_api",11);
		test_random(random_boost,"random_boost",11);

	}

#endif

#if 1
	for(int iLoop=0;iLoop<100; ++iLoop)
	{// test GetRandomObj();


		char *obj[3]={"pSkill, 15","pSkill ,25","pSkill ,10"};
		int percent[3]={15,25,10};

		int tot = ArraySize(obj);
		std::vector<GetRandomObjInfo> in;
		for(int i=0; i< tot; ++i)
		{
			GetRandomObjInfo data;
			data.pObj = obj[i];
			data.iPercent = percent[i];
			in.push_back(data);
		}

		int selected[3];
		memset(selected,0,sizeof(selected));
		for( int j=0; j < 1000 ; ++j)
		{
			char* pSelect = (char*)GetRandomObj(in);
			for(int i=0; i< tot; ++i)
			{
				if(obj[i]==pSelect)
				{
					++selected[i];
				}
			}
		}

		for(int i=0; i< tot; ++i)
		{
			printf("%s , %d ,\t", obj[i],selected[i]);
		}
		printf("\n");

	}
	/*
	pSkill	15	9	        pSkill 	25	991	      pSkill 	10	0
	pSkill	15	360	      pSkill 	25	455	      pSkill 	10	185
	pSkill	15	44	       pSkill 	25	424	      pSkill 	10	532
	pSkill	15	371	      pSkill 	25	565	      pSkill 	10	64
	pSkill	15	39	       pSkill 	25	959	      pSkill 	10	2
	pSkill	15	350	      pSkill 	25	646	      pSkill 	10	4
	pSkill	15	3	        pSkill 	25	83	       pSkill 	10	914

	... 중간 생략 ...

	pSkill	15	625	      pSkill 	25	253	      pSkill 	10	122
	pSkill	15	224	      pSkill 	25	691	      pSkill 	10	85
	pSkill	15	499	      pSkill 	25	3	        pSkill 	10	498
	pSkill	15	172	      pSkill 	25	499	      pSkill 	10	329
	pSkill	15	773	      pSkill 	25	227	      pSkill 	10	0
	pSkill	15	1	        pSkill 	25	758	      pSkill 	10	241
	pSkill	15	2	        pSkill 	25	998	      pSkill 	10	0
	
	
	(1000번씩 100번을 반복한 평균 선택 수)
	           14.7465			        25.372			        9.8815 
	각각의 입력 평균치는
				15,						25,						10
	
	선택된 평균치와 99% 정확하다.

	*/
#endif

	return 0;
}


