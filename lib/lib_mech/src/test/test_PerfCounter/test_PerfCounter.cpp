// test_template.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <locale>
//#include "base/uStringParsor.h"
#include "base/uString_stl.h"


static bool ReadLineFromFile(TCHAR* buf, int buf_size, FILE* pF)
{
	if( jt_fgets( buf, buf_size-1, pF ) == NULL)
	{
		buf=NULL; return false;
	}
	size_t len = jt_strlen(buf);
	buf[len-1] = NULL; // ������� file�� ���� �Ѷ��� �о ������ �� ���๮�ڸ� ����.
	return true;
}


void �����Է��۾�()
{
	nFileSystem::jFolder dir;
	dir.Goto(_T("C:\\prime\\doc\\�۾���Ʈ\\2010-0907-�����۾�"));
	nFileSystem::UFile fpWR(_T("100907_�����_�Ǽ���_1����.sql"), _T("w"));
	nFileSystem::UFile fpWT(_T("100907_�����_�׽�Ʈ_5õ��.sql"), _T("w"));
	nFileSystem::UFile fpR(_T("100907_�����_�Ǽ���_1����.txt"), _T("r"));
	nFileSystem::UFile fpT(_T("100907_�����_�׽�Ʈ_5õ��.txt"), _T("r"));
	fname_t buf;
	int iCount=0;
	while(ReadLineFromFile(buf,_countof(buf) , fpR) )
	{

		tstring buf1 = buf;
		nSTL::trim(buf1);
		iCount++;
		fname_t bufF;
		jt_sprintf(bufF,_T("INSERT INTO Tbl_Coupon  VALUES ( N'%s',0,N'event_coupon_warptohub_town')\n"),buf1.c_str());
		jt_fprintf(fpWR,bufF);
	}
	printf("count = %d", iCount);

	iCount=0;
	while(ReadLineFromFile(buf,_countof(buf) , fpT) )
	{
		tstring buf1 = buf;
		nSTL::trim(buf1);
		iCount++;
		fname_t bufF;
		jt_sprintf(bufF,_T("INSERT INTO Tbl_Coupon  VALUES ( N'%s',0,N'event_coupon_warptohub_town')\n"),buf1.c_str());
		jt_fprintf(fpWT,bufF);
	}
	printf("count = %d", iCount);


}

int _tmain(int argc, _TCHAR* argv[])
{
	//void test_displaying(void);	test_displaying();
	jMech_Init();
	
	//�����Է��۾�();

#if 1
	jDllLoader_Mech dll(_T("jPerfCounter.dll"));
	nLOG::jIPerfCounter* pPC = (nLOG::jIPerfCounter*)dll.jCreateInterface(0);

	pPC->Begin(_T("jMech Lib"));
	pPC->AddCounter(jS(asdf),_T("asdf ������"));
	pPC->AddCounter(jS(asdf1),_T("asdf1 ������"));
	pPC->AddCounter(jS(sdfqweasdf1),_T("fewsdasd asdf������"));
	DWORD i=0;
	while(1)
	{
		++i;
		pPC->UpdateCounter(jS(asdf) , i);
		pPC->UpdateCounter(jS(asdf1) , i+100);
		pPC->UpdateCounter(jS(sdfqweasdf1) , 50);
		Sleep(500);
		if(i>999)
		{
			i=0;
		}
		printf("asdf = %d",i);
	}
#endif

	jMech_Close();

}

