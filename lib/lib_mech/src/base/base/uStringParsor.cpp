/* 
	filename:	uStringParsor.cpp
	coder	:	Cho Wook Rea (mech12@dreamwiz.com)(icq:74456993) 
	comp.	:	esofnet 
	compiler:	vc++ 6.0
	date	:	2000-07-14���� 2:33:41
	title	:	
*/
//#include "platformWin32/platformWin32.h"
#include "stdafx.h"
#include "uStringParsor.h"
#define COMMANT_STRING _T("//")

namespace nMech
{
	//using namespace mech;
	namespace nString
	{

		// returns true if the tstring matches the wildcard
		JBASE_API bool MatchWildcard (acstr  szString, acstr  szWildcard)
		{
			acstr  pString = szString, pWildcard = szWildcard;
			// skip the obviously the same starting substring
			while (*pWildcard && *pWildcard != '*' && *pWildcard != '?')
				if (*pString != *pWildcard)
					return false; // must be exact match unless there's a wildcard character in the wildcard tstring
				else
					++pString, ++pWildcard;

			if (!*pString)
			{
				// this will only match if there are no non-wild characters in the wildcard
				for(; *pWildcard; ++pWildcard)
					if (*pWildcard != '*' && *pWildcard != '?')
						return false;
				return true;
			}

			switch(*pWildcard)
			{
			case '\0':
				return false; // the only way to match them after the leading non-wildcard characters is !*pString, which was already checked

				// we have a wildcard with wild character at the start.
			case '*':
				{
					// merge consecutive ? and *, since they are equivalent to a single *
					while (*pWildcard == '*' || *pWildcard == '?')
						++pWildcard;

					if (!*pWildcard)
						return true; // the rest of the tstring doesn't matter: the wildcard ends with *

					for (; *pString; ++pString)
						if (MatchWildcard(pString, pWildcard))
							return true;

					return false;
				}
			case '?':
				return MatchWildcard(pString+1, pWildcard + 1) || MatchWildcard(pString, pWildcard+1);
			default:
				assert (0);
				return false;
			}
		}

		// returns true if the tstring matches the wildcard
		JBASE_API bool MatchWildcard (wcstr  szString, wcstr  szWildcard)
		{
			wcstr  pString = szString, pWildcard = szWildcard;
			// skip the obviously the same starting substring
			while (*pWildcard && *pWildcard != '*' && *pWildcard != '?')
				if (*pString != *pWildcard)
					return false; // must be exact match unless there's a wildcard character in the wildcard tstring
				else
					++pString, ++pWildcard;

			if (!*pString)
			{
				// this will only match if there are no non-wild characters in the wildcard
				for(; *pWildcard; ++pWildcard)
					if (*pWildcard != '*' && *pWildcard != '?')
						return false;
				return true;
			}

			switch(*pWildcard)
			{
			case '\0':
				return false; // the only way to match them after the leading non-wildcard characters is !*pString, which was already checked

				// we have a wildcard with wild character at the start.
			case '*':
				{
					// merge consecutive ? and *, since they are equivalent to a single *
					while (*pWildcard == '*' || *pWildcard == '?')
						++pWildcard;

					if (!*pWildcard)
						return true; // the rest of the tstring doesn't matter: the wildcard ends with *

					for (; *pString; ++pString)
						if (MatchWildcard(pString, pWildcard))
							return true;

					return false;
				}
			case '?':
				return MatchWildcard(pString+1, pWildcard + 1) || MatchWildcard(pString, pWildcard+1);
			default:
				assert (0);
				return false;
			}
		}

		////////////////////////////////////////////////////////////////
		//  ��������̸� true���� : ����.
		bool jParsor::IsNullSpace(TCHAR* buf)
			////////////////////////////////////////////////////////////////
		{
			size_t len = jt_strlen(buf);
			if(len==0) return true;
			int isNull= 0;

			for(size_t i = 0; i<len ; i++)
			{ 
				// ����  int i = 0 ; // �ּ�  --> �̺κп� ���� �˻�.
				if(buf[i] != (' '))
					if(buf[i] != ('\t'))
						if(buf[i] != ('\n'))
							return false;
			} 
			return true;
		}

		////////////////////////////////////////////////////////////////
		// buf�� ��ü�� �ڸ�Ʈ�̸� true����.
		bool jParsor::IsCommentLine(TCHAR* buf )
			////////////////////////////////////////////////////////////////
		{
			if(IsNullSpace(buf)) return true;

			TCHAR* pPos = jt_strstr(buf,COMMANT_STRING );
			if(!pPos)		return false; // �ּ��� ���ٸ�.

			int iPos = pPos-buf;
			if (iPos == 0 ){ buf[iPos]=0;					return true;}

			buf[iPos] = NULL; 

			if(IsNullSpace(buf))		return true;

			return false; // �������� �������� ����.
		}


		//****************************************************************
		/* ����  inBuf�� ������

		int i=100; /* �ּ� ����. 

		�϶� true�� �����ϸ� inBuf���� "int i=100; "�� ���� ���õȴ�.
		//****************************************************************
		inBuf�� ������ 

		/* �ּ�����
		�̸� true�� �����ϰ� inBuf�� NULL�̴�.
		*/
		bool jParsor::IsMultiCommentStart(TCHAR* inBuf)
			//****************************************************************
		{
			size_t i=jt_strlen(inBuf);
			for(size_t j=0; j<i;j++)
			{
				if(inBuf[j] ==('/') && (inBuf[j+1]==('*')) )
				{
					inBuf[j]=NULL; 
					return true;
				}
			}
			return false;
		}


		/*
		��Ƽ���� �ּ��� ���� ã�� �������� ���� buf�� ����.
		���� 

		�ּ� �P * /  int i=1000;
		�̶�� ���ϰ��� "int i=1000;"�� �ȴ�.
		���� �ּ��� �� �ƹ� ���ڵ� ���� �����̸� buf�� NULL�� ����.
		*/
		const int jBUF_SIZE = 256;

		//****************************************************************
		void jParsor::SkipMultiComment(FILE* pF,TCHAR* buf)
			//****************************************************************
		{
			TCHAR temp[256];
			TCHAR* p;

			while(1)
			{
				if(!ReadLineFromFile(temp, jBUF_SIZE,pF)) break;
				p = jt_strstr(temp,_T("*/"));
				if(!p) continue;
				jt_strcpy(temp , &p[2]);
				return;
			}
		}
		void jParsor::TrimSpaceChar(TCHAR*szIN, TCHAR*szOut)
			//****************************************************************
		{

			size_t iLen = jt_strlen(szIN);
			size_t iOut=0;
			size_t iFront=0,iEnd=iLen-1;
			size_t i;
			for(i=0; i<iLen; i++)
			{
				if( szIN[i] != (' ') && szIN[i] != ('\t'))
				{	
					iFront= i; 
					break;
				}

			}
			for(i=iLen-1; i>0 ; i--)
			{
				if( szIN[i] != (' ') && szIN[i] != ('\t'))
				{
					iEnd= i;
					break;
				}
			}
			jt_strncpy( szOut , szIN+iFront , iEnd-iFront+1);
			szOut[iEnd-iFront+1]=0;
		}

		void jParsor::GetLineFromScriptFile(FILE* pF , TCHAR* buf, int buf_size)
		{
			while(1)
			{
				memset(buf, 0, buf_size);
				if(!ReadLineFromFile(buf, buf_size, pF)) break;
				if(IsCommentLine(buf)) continue;
				if(!IsMultiCommentStart(buf)) break;
				SkipMultiComment(pF , buf);
				if(buf[0]) break;
			}
			if(*buf)
			{
				TCHAR temp[256];
				jt_strcpy(temp , buf);
				TrimSpaceChar(temp, buf);
			}
		}


		//---------------------------------------------------------------
		//  szIn��  ������ %szWhat%�� szChange�� �ٲ۴�.
		void jParsor::jChangeMacroString(tcstr szIn , tcstr szWhat, tcstr szChange, tfname_t& szOut)
			//----------------------------------------------------------------
		{
			TCHAR szBuf[1024];
			assert(_tcslen(szIn) <1024 );
			_tcscpy(szBuf , szIn);

			TCHAR* chFirst = _tcschr(szBuf, TEXT('%'));

			if(!chFirst)
			{
				assert(0);
				_tcscpy(szOut , szIn);
				return ;
			}

			TCHAR* chSecond ;
			TCHAR* chLater ;
			tfname_t buf12;
			int iLen ;
lbl_do:
			chSecond = _tcschr(chFirst+1, TEXT('%'));
			chLater = chSecond+1;
			iLen = chSecond - (chFirst+1);
			_tcsncpy(buf12, chFirst+1 , iLen);

			buf12[iLen]=0;

			if(!_tcscmp(buf12,szWhat ))
			{
				*chFirst = 0;
				*chSecond=0;

				_tcscpy(szOut, szBuf);
				_tcscat(szOut, szChange);
				_tcscat(szOut, chLater);
				return ;
			}
			else
			{
				chFirst = _tcschr(chLater, TEXT('%'));
				assert(chFirst);
				goto lbl_do;
			}
		}

		//---------------------------------------------------------------
		//  szIn��  ������ szWhat�� szChange�� �ٲ۴�.
		void jParsor::jChangeString(tcstr szIn , tcstr szWhat, tcstr szChange, tfname_t& szOut)
			//----------------------------------------------------------------
		{
			TCHAR szBuf[1024];
			assert(_tcslen(szIn) <1024 );
			//_tcscpy(szBuf , szIn);
			memset(szBuf, 0 , sizeof(szBuf));

			const TCHAR* pFind = _tcsstr(szIn , szWhat);
			if(!pFind) 
			{
				_tcscpy( szOut , szIn);
				return;
			}

			int iN = pFind - szIn;
			if(iN)
			{
				jt_strncpy( szBuf , szIn , iN);
			}
			size_t  len = _tcslen(szWhat);
			len += iN;
			size_t tot = _tcslen(szIn);
			_tcscat( szBuf, szIn+len);
			_tcscpy(szOut , szBuf);
		}

		TCHAR*   jParsor::jStringReplace(TCHAR* szSrc , TCHAR cOrg, TCHAR cReplace)
		{
			TCHAR* sz = szSrc;

			while(sz){
				sz = _tcschr(sz, cOrg);
				if(!sz) break;
				*sz = cReplace;
			};
			return szSrc;
		}
	}//namespace nString
}//namespace nMech
