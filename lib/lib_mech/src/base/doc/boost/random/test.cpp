// test.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "test.h"
#include "jRandom.h"



//======================================================================================================
// <����1>
//
// �� ������ ���̰��� ���ϴ� �Լ��̴�. ������ ä�� �־��.
//======================================================================================================

float CalcAngle(const D3DXVECTOR3* vOri, const D3DXVECTOR3* vDst)
{
	using namespace nMech;
	f64 LengthQ=GetLength(vOri)*GetLength(vDst);
	if(LengthQ<0.01) LengthQ=0.01;
	return((f32)(acos(Dot(vOri,vDst)/LengthQ)));
}

//======================================================================================================
// <����2>
//
// �� �������� ���̸� ����ϴ� �Լ��̴�. ������ ä�� �־��.
// Angle�� 360�� �����̸� ���ϰ��� 180�� ���Ͽ��� �Ѵ�.
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
// <����3>
//
// Min, Max���� �־����� �� �ش� �� ������ �������� ���� �Լ��� �ۼ��϶�.
//======================================================================================================

int	GetRandomValue(int nMin, int nMax)
{
	/*
	�ߺ�= 973 Sleep=0,cpu=2618, �����ȷ�����=27, random_my(1,1000);
	�ߺ�= 999 Sleep=0,cpu=758, �����ȷ�����=1, random_api(1,1000);
	�ߺ�= 369 Sleep=0,cpu=4272, �����ȷ�����=631, random_boost(1,1000);

	�ߺ�= 356 Sleep=3,cpu=239034, �����ȷ�����=644, random_my(1,1000);
	�ߺ�= 995 Sleep=3,cpu=238997, �����ȷ�����=5, random_api(1,1000);
	�ߺ�= 376 Sleep=3,cpu=239214, �����ȷ�����=624, random_boost(1,1000);

	�ߺ�= 363 Sleep=11,cpu=287753, �����ȷ�����=637, random_my(1,1000);
	�ߺ�= 987 Sleep=11,cpu=287641, �����ȷ�����=13, random_api(1,1000);
	�ߺ�= 370 Sleep=11,cpu=287597, �����ȷ�����=630, random_boost(1,1000);
	*/
	//return nMech::random_api(nMin,nMax);
	//return nMech::random_boost(nMin,nMax);
	return nMech::random_my(nMin,nMax);
}



//======================================================================================================
// <����4>
//
// ���Ͱ� ������ ��ų�� ����� Ȯ���� ������ ����.
// Skill* pSkill1(15), pSkill2(25), pSkill3(10)
// ������ Ȯ���� 100%�� �������� �ϸ� ������ 15/50, 25/50, 10/50�� �ȴ�.

// pSkill1, pSkill2, pSkill3�� 15, 25, 10�� �Է°����� �����ϰ� �ϳ��� ��ų(pSkill1, 2, 3)�� 
// �����ϴ� �Լ��� �ۼ��϶�. ��, �ݵ�� Ư�� Ÿ���� Ŭ����(Skill)�� �ƴϴ��� ����� ��
// �� �ִ� ������ Utility Ŭ������ �ۼ��϶�. 
//======================================================================================================
struct GetRandomObjInfo
{
	void* pObj; // ���õ� ��ü ������
	int iPercent; // ���� Ȯ�� 
};

void* GetRandomObj(std::vector<GetRandomObjInfo>& in)
{
/*
(1000���� 100���� �ݺ��� ��� ���� ��)

	14.7465			        25.372			        9.8815 

������ �Է� ���ġ��
	15,						25,						10

���õ� ���ġ�� 99% ��Ȯ��.
�׽�Ʈ ������ _tmain()�Լ��� �����ϼ���.

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
// <����5>
//
// Player�� Monster�� ���� �߻�ü�� ���Ȱ� �� �߻�ü�� ���� ���� �����̴� �����̻����̴�.
// �߻�ü�� Player��ġ�κ��� 10m�Ÿ�(��Ÿ�) �ۿ��� ���ư��� Player�� �ӵ��� 5m/s �߻�ü�� �ӵ��� 4m/s�̴�.
// �̶� �߻�ü�� �����̻��� ����� �߽����� Ŭ������ �����϶�.
// �� �� �����̻����� ����� �׽�Ʈ �� �� �ִ� ������ �����ؾ� �ȴ�. 
// ex) Player�� ���� ��ġ�� �߻�ü�� ���� ��ġ ����. ���� Player�� Ư�� �������� �����ϰ� ������.
// �������� ��Ȳ�� �������� ���ؼ� ����� �����ϰ� ������ ���� �ո����̶�� �����ϴ� ��å���� �����ϸ� �ȴ�.
//======================================================================================================
/*

�˼��մϴ�. 
������ �������� ���ӷ����ε� ���� ��հ����� ����Ÿ ����� ��ü ���ư��� �׽�Ʈ ���α׷����� ������� 
�ð��� ���� �ɸ��� ���� �����ϰ� �ͽ��ϴ�. -_-;

�� Ǯ�⸦ ���Ͻø� �ٽ� ������ �ּ���.
�ּ��� ���� ������ Ǯ���� �ϰڽ��ϴ�.

*/ 

//======================================================================================================
// <����6>
//
// �ַ� �������� SendBuffer�� RecvBuffer�� ���� ���Ǵ� RingBuffer�� �����϶�.
// �ʿ��ϴٸ� ���ο� �Լ��� �����ϰų� ���� �Լ��� �����ص� �ȴ�. 
// ������ Write, Read, Peek�� �ݵ�� ������ ��!
//======================================================================================================
#include "jRingBuffer.h"
// ���������δ� �����۸� �Ⱦ���. ��Ŷ����� ��Ŷ Ǯ(128,256,1024,2048,4096, ...)�� �̿��մϴ�.



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

	... �߰� ���� ...

	pSkill	15	625	      pSkill 	25	253	      pSkill 	10	122
	pSkill	15	224	      pSkill 	25	691	      pSkill 	10	85
	pSkill	15	499	      pSkill 	25	3	        pSkill 	10	498
	pSkill	15	172	      pSkill 	25	499	      pSkill 	10	329
	pSkill	15	773	      pSkill 	25	227	      pSkill 	10	0
	pSkill	15	1	        pSkill 	25	758	      pSkill 	10	241
	pSkill	15	2	        pSkill 	25	998	      pSkill 	10	0
	
	
	(1000���� 100���� �ݺ��� ��� ���� ��)
	           14.7465			        25.372			        9.8815 
	������ �Է� ���ġ��
				15,						25,						10
	
	���õ� ���ġ�� 99% ��Ȯ�ϴ�.

	*/
#endif

	return 0;
}


