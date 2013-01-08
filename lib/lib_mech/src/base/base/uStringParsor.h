/* 
	filename:	uStringParsor.h
	coder	:	Cho Wook Rea (mech12@dreamwiz.com)(icq:74456993) 
	comp.	:	esofnet 
	compiler:	vc++ 6.0
	date	:	2000-07-14오전 2:33:27
	title	:	
*/


#ifndef __uStringParsor_h__
#define __uStringParsor_h__
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*---------------------------------------------------------------------
CLASS
    StringTokenizer

DESCRIPTION
    java의 StringTokenizer를 간단하게 C++로 구현.
  
    Notice: inline으로 구현된 부분을 CPP로 분리하고 DEBUG 모드로 컴파일 할때, 
    warning이 나오는 이유는 클래스 명이 너무 길어서 나오는 것이므로 무시하도록한다. ^_^;
    
    EXAMPLE
        #include "StringTokenizer.h"

        // 1) delimiter가 여러개 TCHAR 인경우
        StringTokenizer stt("10+20*30/10", "+-/*", true);
        while (!stt.empty()) {
            cout << "token = " << stt.nextToken ().c_str() << " ";
        }
        cout << endl;

        // 2) delimiter가 한 단어인 경우
        StringTokenizer stts ("10::20::30::10", "::", false);
        while (!stts.empty()) {
            cout << "token = " << stts.nextToken ().c_str() << " ";
        }
        cout << endl;

        결과:
            1) 10 20 30 10 
            2) 10 20 30 10 
    END    

AUTHOR
    yonghan, yoon
    contact:
    <address><a href="yonghany@orgio.net">yonghany@orgio.net</a></address>
---------------------------------------------------------------------*/

/*{hush(icq:74456993)2001-07-10오전 4:44:32
class StringTokenizer : public list < tstring >
{
private:
    tstring         gq, deli;
    bool         isGroup;
    
public:
    ///////////////////////////
    // s          : 입력 문자열
    // delimeters : 구분자
    // isGroup    : 딜리미터가 한단어 인가 여부, 문자열이 구분자 그룹 일 경우 true
    StringTokenizer(const std::tstring & src, const std::tstring & delimiter, bool _isGroup=false)
        : gq (src), deli (delimiter), isGroup (_isGroup)
    {
        tstring token;
        while (!(token = parseNext ()).empty()) {
            push_back (token);
        }
    }
    
    ///////////////////////////
    // 토큰의 갯수를 리턴
    int countTokens() const {
        return size();
    }
    
    ///////////////////////////
    // 토큰이 있으면 토큰을 리턴
    // Notice: 이 함수를 호출 할때마다 스택에 있는 데이터는 없어진다.
    tstring nextToken() {
        tstring token;  
        if (hasToken()) {
            token = front ();
            pop_front();
        }

        return token;
    }
    
    ///////////////////////////
    // 토큰이 있는가?(남아있나?)
    bool hasToken() const {
        return (countTokens()>0) ? true : false;
    }
    
    ///////////////////////////
    // s와 같은 토큰이 있는가?
    bool hasToken(const std::tstring & s) {
        list<std::tstring>::iterator iter;
        for (iter = begin(); iter != end(); iter++) {
            if (*iter == s)
                return true;
        }

        return false;
    }
    
private:
    ///////////////////////////
    // delimiter를 기준으로 문자열을 자른다.
    tstring parseNext () {
        if(gq.length() == 0)
            return tstring(); // Error, return empty
        
        tstring token;
        if (isGroup) {
            if(gq.find_first_of (deli) == -1) {
                if (gq.length()>0) { // 문자열이 delimiter로 끝나지 않았을 경우
                    token = gq;
                    gq = tstring();
                    return token;
                }
                return tstring(); // Error, return empty
            }
            token = gq.substr (0, gq.find_first_of (deli));
            gq = gq.substr(gq.find_first_of  (deli) + 1);
        }
        else {
            if(gq.find (deli) == -1) {
                if (gq.length()>0) { // 문자열이 delimiter로 끝나지 않았을 경우
                    token = gq;
                    gq = tstring();
                    return token;
                }
                return tstring(); // Error, return empty
            }
            token = gq.substr (0, gq.find (deli));
            gq = gq.substr(gq.find (deli) + deli.length());
        }
        return token;
    }
};
}hush(icq:74456993) 2001-07-10오전 4:44:36*/

//void nString::jSplit(TCHAR* inLine, TCHAR* Separ, stringList& out){ tstring in(inLine);tstring Vsep(Separ); nString::jSplit(in,Separ,out); }
//  // a;lsdkfjasdf;al
// tstring inLine="move -15; // aslkjfa;lsdfja;lkfs";
// tstring Sepr("\t\n, ");
// stringList strList;
// tstring s="asd f;l , lasdkfj, lwer, kjasd"
// strList.insert(s);
// insert.....
// stringList_it i = strList.find(s);
// cout << *i;
//
// nString::jSplit( inLine, 

////////////////////////////////////////////////////////////////
// separ에 나타난 문자들로 inLine의 문자열을 쫗개여 out에 배치시킴.
// 중요 ! out에 어떤 데이타가 있을 때는 그데이타 마지막에 쫗게진 문자열을 넣는다.
// 그러므로 jSplit를 호출하기전에 out.clear()를 호출하는것이 좋다.
namespace nMech
{

	namespace nString
	{

#ifdef UNICODE
#define jSplit jSplitW
#else
#define jSplit jSplitA
#endif
		inline void jSplitA(const std::string& inLine, const std::string& Separ, std::vector<std::string>& out)
			////////////////////////////////////////////////////////////////
		{
			const size_t N = inLine.length();
			size_t iStart, iEnd;

			iStart = inLine.find_first_not_of(Separ);
			while ((iStart >= 0) && (iStart < N)) 
			{
				iEnd = inLine.find_first_of(Separ, iStart);
				if ((iEnd < 0) || (iEnd > N)) iEnd = N;
				out.push_back(inLine.substr(iStart, iEnd - iStart));
				iStart = inLine.find_first_not_of(Separ, iEnd+1);
			}
		}
		inline void jSplitW(const std::wstring& inLine, const std::wstring& Separ, std::vector<std::wstring>& out)
			////////////////////////////////////////////////////////////////
		{
			const size_t N = inLine.length();
			size_t iStart, iEnd;

			iStart = inLine.find_first_not_of(Separ);
			while ((iStart >= 0) && (iStart < N)) 
			{
				iEnd = inLine.find_first_of(Separ, iStart);
				if ((iEnd < 0) || (iEnd > N)) iEnd = N;
				out.push_back(inLine.substr(iStart, iEnd - iStart));
				iStart = inLine.find_first_not_of(Separ, iEnd+1);
			}
		}

		JBASE_API bool MatchWildcard (acstr  szString, acstr  szWildcard);
		JBASE_API bool MatchWildcard (wcstr  szString, wcstr  szWildcard);


		class JBASE_API jParsor
		{
		public:
			////////////////////////////////////////////////////////////////
			//  공백라인이면 true리턴 : 빈줄.
			static bool IsNullSpace(TCHAR* buf);

			////////////////////////////////////////////////////////////////
			// buf의 전체가 코멘트이면 true리턴.
			static bool IsCommentLine(TCHAR* buf );

			// 한라인 을 읽는다.
			// false를 리턴하면 파일끝이다.
			static bool ReadLineFromFile(TCHAR* buf, int buf_size, FILE* pF)
			{
				if( jt_fgets( buf, buf_size-1, pF ) == NULL)
				{
					buf[0]=NULL; return false;
				}
				size_t len = jt_strlen(buf);
				if(buf[len-1]=='\n' || buf[len-1]=='\r')
					buf[len-1] = NULL; // 여기까지 file로 부터 한라인 읽어서 마지막 의 개행문자를 제거.
				return true;
			}

			static bool IsMultiCommentStart(TCHAR* inBuf);
			static void SkipMultiComment(FILE* pF,TCHAR* buf);

			// 문자열의 앞뒤에 있는 공백이나 탭 문자를 제거. 중간에 있는것은 제거 안한다.
			// jstring의 앞뒤에 있는 공백문자를 제거.
			static void jParsor::TrimSpaceChar(TCHAR*szIN, TCHAR*szOut);

			static void GetLineFromScriptFile(FILE* pF , TCHAR* buf, int buf_size);
			//  szIn의  내용중  %szWhat% 을 szChange로 바꾼다.
			static void jChangeMacroString(tcstr szIn , tcstr szWhat, tcstr szChange, tfname_t& szOut);
			//  szIn의  내용중 szWhat을 szChange로 바꾼다.
			static void jChangeString(tcstr szIn , tcstr szWhat, tcstr szChange, tfname_t& szOut);

			static TCHAR*   jStringReplace(TCHAR* szSrc , TCHAR cOrg, TCHAR cReplace);

		};
		class JBASE_API jTxtScript
		{
		public:
			//****************************************************************
			inline void GetSV(FILE* fp , TCHAR* szP)
				//****************************************************************
			{
				TCHAR buf[1024];
				jParsor::GetLineFromScriptFile(fp,buf,sizeof(buf));	
				if(buf[0]==0) throw false;
				jt_strcpy_s(szP ,255, buf);
				if( !jt_strncmp(buf,_T("NULL") ,jt_strlen(_T("NULL")) ) )
				{
					szP[0]=0;
				}
			}

			//****************************************************************
			inline void GetSV(FILE* fp ,int & i)
				//****************************************************************
			{
				TCHAR buf[1024];
				jParsor::GetLineFromScriptFile(fp,buf,sizeof(buf));	
				if(buf[0]==0) throw false;
				i = jt_atoi(buf);
			}
#pragma warning (disable : 4244)
			//****************************************************************
			inline void GetSV(FILE* fp ,float & i)
				//****************************************************************
			{
				TCHAR buf[1024];
				jParsor::GetLineFromScriptFile(fp,buf,sizeof(buf));	
				if(buf[0]==0) throw false;
				i = (int)jt_atof(buf);
			}
#pragma warning (disable : 4244)
			inline void GetSV(FILE* fp ,TCHAR& i){ int ii; GetSV(fp,ii); i = ii;}
			//inline void GetSV(FILE* fp ,uchar& i){ int ii; GetSV(fp,ii); i = ii;}
			inline void GetSV(FILE* fp ,int16& i){ int ii; GetSV(fp,ii); i = ii;}
			inline void GetSV(FILE* fp ,uint& i){ int ii; GetSV(fp,ii); i = ii;}
# pragma warning(disable:4800) 
			inline void GetSV(FILE* fp ,bool& i){ int ii; GetSV(fp,ii); i = ii;}


			//****************************************************************
			inline void PutSV(FILE* fp, int i , TCHAR* desc = 0)
				//****************************************************************
			{
				_ftprintf(fp, TEXT("%d \t//%s\n") , i, desc);
			}
			//****************************************************************
			inline void PutSV(FILE* fp, float i , TCHAR* desc = 0)
				//****************************************************************
			{
				_ftprintf(fp, TEXT("%f \t//%s\n") , i, desc);
			}

			inline void PutSV(FILE* fp, TCHAR i , TCHAR* desc = 0) {int ii = (int)i; PutSV(fp, ii , desc);}
			//inline void PutSV(FILE* fp, uchar i , TCHAR* desc = 0) {int ii = (int)i; PutSV(fp, ii , desc);}
			inline void PutSV(FILE* fp, int16 i , TCHAR* desc = 0) {int ii = (int)i; PutSV(fp, ii , desc);}
			inline void PutSV(FILE* fp, uint32 i , TCHAR* desc = 0) {int ii = (int)i; PutSV(fp, ii , desc);}
			inline void PutSV(FILE* fp, bool i , TCHAR* desc = 0) {int ii = (int)i; PutSV(fp, ii , desc);}

			//****************************************************************
			inline void PutSV(FILE* fp, TCHAR* sz,TCHAR* szDesc = 0)
				//****************************************************************
			{
				if(!sz[0])
					_ftprintf(fp, TEXT("NULL \t// %s\n") , szDesc);
				else 
					_ftprintf(fp, TEXT("%s \t// %s\n") , sz,szDesc);
			}
		};


		//String Hash 코드
		//http://extremendl.net/bbs/zboard.php?id=v3_codelibrary&page=1&sn1=&divpage=1&sn=off&ss=on&sc=on&select_arrange=headnum&desc=asc&no=9
		inline DWORD StringToHash( TCHAR* source )
		{
			DWORD                i, len, ch;
			DWORD                result, xor;

			len                = ( DWORD )jt_strlen( source );
			result        = 0;
			xor                = 0;
			for( i = 0 ; i < len ; i++ )
			{
				ch                = ( DWORD )source[i];
				result        = ( ( result << 8 ) | ch ) % 16777213UL;
				xor ^= ch;
			}

			return ( result | ( xor << 24 ) );
		}
	}//namespace nString

}//namespace nMech

#endif //__uStringParsor_h__
