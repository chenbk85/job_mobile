/* 
	filename:	uStringParsor.h
	coder	:	Cho Wook Rea (mech12@dreamwiz.com)(icq:74456993) 
	comp.	:	esofnet 
	compiler:	vc++ 6.0
	date	:	2000-07-14���� 2:33:27
	title	:	
*/


#ifndef __uStringParsor_h__
#define __uStringParsor_h__
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#if 0
/*---------------------------------------------------------------------
CLASS
    StringTokenizer

DESCRIPTION
    java�� StringTokenizer�� �����ϰ� C++�� ����.
  
    Notice: inline���� ������ �κ��� CPP�� �и��ϰ� DEBUG ���� ������ �Ҷ�, 
    warning�� ������ ������ Ŭ���� ���� �ʹ� �� ������ ���̹Ƿ� �����ϵ����Ѵ�. ^_^;
    
    EXAMPLE
        #include "StringTokenizer.h"

        // 1) delimiter�� ������ TCHAR �ΰ��
        StringTokenizer stt("10+20*30/10", "*+-/", true);
        while (!stt.empty()) {
            cout << "token = " << stt.nextToken ().c_str() << " ";
        }
        cout << endl;

        // 2) delimiter�� �� �ܾ��� ���
        StringTokenizer stts ("10::20::30::10", "::", false);
        while (!stts.empty()) {
            cout << "token = " << stts.nextToken ().c_str() << " ";
        }
        cout << endl;

        ���:
            1) 10 20 30 10 
            2) 10 20 30 10 
    END    

AUTHOR
    yonghan, yoon
    contact:
    <address><a href="yonghany@orgio.net">yonghany@orgio.net</a></address>
---------------------------------------------------------------------*/

#endif

/*{hush(icq:74456993)2001-07-10���� 4:44:32
class StringTokenizer : public list < tstring >
{
private:
    tstring         gq, deli;
    bool         isGroup;
    
public:
    ///////////////////////////
    // s          : �Է� ���ڿ�
    // delimeters : ������
    // isGroup    : �������Ͱ� �Ѵܾ� �ΰ� ����, ���ڿ��� ������ �׷� �� ��� true
    StringTokenizer(const std::tstring & src, const std::tstring & delimiter, bool _isGroup=false)
        : gq (src), deli (delimiter), isGroup (_isGroup)
    {
        tstring token;
        while (!(token = parseNext ()).empty()) {
            push_back (token);
        }
    }
    
    ///////////////////////////
    // ��ū�� ������ ����
    int countTokens() const {
        return size();
    }
    
    ///////////////////////////
    // ��ū�� ������ ��ū�� ����
    // Notice: �� �Լ��� ȣ�� �Ҷ����� ���ÿ� �ִ� �����ʹ� ��������.
    tstring nextToken() {
        tstring token;  
        if (hasToken()) {
            token = front ();
            pop_front();
        }

        return token;
    }
    
    ///////////////////////////
    // ��ū�� �ִ°�?(�����ֳ�?)
    bool hasToken() const {
        return (countTokens()>0) ? true : false;
    }
    
    ///////////////////////////
    // s�� ���� ��ū�� �ִ°�?
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
    // delimiter�� �������� ���ڿ��� �ڸ���.
    tstring parseNext () {
        if(gq.length() == 0)
            return tstring(); // Error, return empty
        
        tstring token;
        if (isGroup) {
            if(gq.find_first_of (deli) == -1) {
                if (gq.length()>0) { // ���ڿ��� delimiter�� ������ �ʾ��� ���
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
                if (gq.length()>0) { // ���ڿ��� delimiter�� ������ �ʾ��� ���
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
}hush(icq:74456993) 2001-07-10���� 4:44:36*/

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
// separ�� ��Ÿ�� ���ڵ�� inLine�� ���ڿ��� �m���� out�� ��ġ��Ŵ.
// �߿� ! out�� � ����Ÿ�� ���� ���� �׵���Ÿ �������� �m���� ���ڿ��� �ִ´�.
// �׷��Ƿ� jSplit�� ȣ���ϱ����� out.clear()�� ȣ���ϴ°��� ����.
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
			while ((iStart < N)) 
			{
				iEnd = inLine.find_first_of(Separ, iStart);
				if (iEnd > N) iEnd = N;
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
			while (iStart < N)
			{
				iEnd = inLine.find_first_of(Separ, iStart);
				if (iEnd > N) iEnd = N;
				out.push_back(inLine.substr(iStart, iEnd - iStart));
				iStart = inLine.find_first_not_of(Separ, iEnd+1);
			}
		}

		JBASE_API bool MatchWildcard (acstr  szString, acstr  szWildcard);
		JBASE_API bool MatchWildcard (wcstr  szString, wcstr  szWildcard);


	}//namespace nString

}//namespace nMech

#endif //__uStringParsor_h__
