/* file : test_UFile.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-01-22 18:43:12
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jTestUnit.h"
#include "base/jFolder.h"

using namespace nMech;

tcstr g_INI_default_text = _T("\
	 ; 주석 앞에 공백이 있으면 에러남.\n\n\
	 [exe]\n\
	 ; 기본 실행시작폴더지정시.  \"..\"는 상위폴더.\n\
	 start_dir = \"..\"\n\
	 ; 실행파일이 여러개 실행가능?\n\
	 multi_run = 0\n\n\
	 ;기본적으로 로딩하는 app_xml이름. 지정안되어 있으면 실행파일명.xml을 로당한다.\
	 default_app_xml = \"\"\n\n\
	 ;TestUnit 실행여부\n\
	 run_test_unit = 0\n");

namespace
{
	jTEST_SUITE_BEGIN(UFile_);
	jTEST(read_file_test)
	{
		//http://www.gosu.net/GosuWeb/Article-detail.aspx?ArticleCode=345
		std::locale::global( std::locale( "kor" ) ); 
		tstring wideString=_T("테스트 문자열 - 유니코드");
		nFileSystem::jFolder dir;
		dir.GotoForce(_T("test"));

		tofstream of(_T("test.ini"),std::ios_base::binary);
		of << g_INI_default_text ;
		of.close();

		tstring sBuf;
		nFileSystem::UFile().read_file(_T("test.ini") , sBuf);
		std::locale::global( std::locale( "kor" ) ); 
		jCHECK(sBuf == g_INI_default_text);
	}
	jTEST_SUITE_END(UFile_);
	

}



#if 0
jTEST( file_uni_ansi)
{
	// Basic use
	FILE* fileBasic = fopen("basic.txt", "wb");

	std::string strBasic1 = "Basic: First line";
	char* szBasic2 = "Basic: Second line";

	jFile_UniAnsi a;

	a.LineToFile(fileBasic, strBasic1);
	a.LineToFile(fileBasic, szBasic2);
	a.LineToFile(fileBasic, "Basic: Third line");

	fclose(fileBasic);
	fileBasic = fopen("basic.txt", "rb");

	std::string strBasic;
	while (a.LineFromFile(fileBasic, strBasic))
	{
		MessageBox(NULL, strBasic.c_str(), "Found string:", 0);
	};
	fclose(fileBasic);


	// ANSI (space as line delimiter, newline as eof - read one word at a time)
	FILE* fileAnsi = fopen("ansi.txt", "wb");

	std::string strAnsi1 = "line1word1";
	char* szAnsi2 = "line1word2";

	a.LineToFile(fileAnsi, strAnsi1, ' ');
	a.LineToFile(fileAnsi, szAnsi2, ' '); // this will make sure that when we read this word with
	a.LineToFile(fileAnsi, "");           // LineFromFile(.., eol=' '), it returns true

	a.LineToFile(fileAnsi, "line2word1", ' ');
	a.LineToFile(fileAnsi, "line2word2", ' ');
	a.LineToFile(fileAnsi, "");

	fclose(fileAnsi);

	fileAnsi = fopen("ansi.txt", "rb");
	std::string strAnsi;
	while (!feof(fileAnsi))
	{
		while (a.LineFromFile(fileAnsi, strAnsi, ' ', '\n'))
		{
			MessageBox(NULL, strAnsi.c_str(), "Found ANSI string:", 0);
		};        
	};
	fclose(fileAnsi);



	// Unicode (simple, including tab and newline)
	FILE* fileUnicode = fopen("unicode.txt", "wb");
	std::wstring szUnicode1 = L"Unicode\n1";
	wchar_t* szUnicode2 = L"Unicode\t2";
	a.LineToFile(fileUnicode, szUnicode1);
	a.LineToFile(fileUnicode, szUnicode2);
	a.LineToFile(fileUnicode, L"");
	a.LineToFile(fileUnicode, L"Unicode 3");
	fclose(fileUnicode);
	fileUnicode = fopen("unicode.txt", "rb");
	std::wstring szUnicode;
	while (a.LineFromFile(fileUnicode, szUnicode))
	{
		MessageBoxW(NULL, szUnicode.c_str(), L"Found UNICODE string:", 0);
	};
	fclose(fileUnicode);
};
#endif