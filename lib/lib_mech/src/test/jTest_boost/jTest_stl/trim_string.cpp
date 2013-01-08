#include "stdafx.h"
#include <string>
using namespace std;

namespace jString
{

string trim_right(const string& source, const string& whitespaces=" \t\r\n")
{
    string str = source;
    return str.erase(str.find_last_not_of(whitespaces) + 1);
}

string trim_left(const string& source, const string& whitespaces=" \t\r\n")
{
    string str = source;
    return str.erase(0, str.find_first_not_of(whitespaces));
}
#if 0
string trim(const string& source, const string& whitespaces=" \t\r\n")
{
    string str = source;
    return trim_left(trim_right(source, whitespaces), whitespaces);
}
#else
std::string trim(const std::string& str, const std::string& whitespaces=" \t\r\n")
{
    size_t begin = str.find_first_not_of(whitespaces);
    size_t end = str.find_last_not_of(whitespaces);

    if (begin == std::string::npos)
    {
        if (end == std::string::npos)
            return std::string("");
        else
            begin = 0;
    }
    else if (end == std::string::npos)
    {
        end = str.size();
    }

    return str.substr(begin , end - begin + 1);
}
#endif

wstring trim_right(const wstring& source, const wstring& whitespaces=L" \t\r\n")
{
    wstring str = source;
    return str.erase(str.find_last_not_of(whitespaces) + 1);
}

wstring trim_left(const wstring& source, const wstring& whitespaces=L" \t\r\n")
{
    wstring str = source;
    return str.erase(0, str.find_first_not_of(whitespaces));
}
#if 0
wstring trim(const wstring& source, const wstring& whitespaces=L" \t\r\n")
{
    wstring str = source;
    return trim_left(trim_right(source, whitespaces), whitespaces);
}

#else
std::wstring trim(const std::wstring& str, const std::wstring& whitespaces=L" \t\r\n")
{
    size_t begin = str.find_first_not_of(whitespaces);
    size_t end = str.find_last_not_of(whitespaces);

    if (begin == std::wstring::npos)
    {
        if (end == std::wstring::npos)
            return std::wstring(L"");
        else
            begin = 0;
    }
    else if (end == std::wstring::npos)
    {
        end = str.size();
    }

    return str.substr(begin , end - begin + 1);
}
#endif


/////////////////////////////////////////////////////////////////////////////
/// \brief 주어진 문자열 내에 존재하는 문자열을 다른 문자열로 치환한다.
/// \param text 원본 문자열
/// \param find_token 찾고자 하는 문자열
/// \param replace_token 치환하고자 하는 문자열
//////////////////////////////////////////////////////////////////////////////
void replace(string& text, const string& find_token, const string& replace_token)
{
    size_t i = 0;
    while ((i = text.find(find_token)) != string::npos)
        text.replace(i, find_token.size(), replace_token);
}

//////////////////////////////////////////////////////////////////////////////
/// \brief 문장 내부에 연속적인 대상 문자를 하나로 만든다.
///
/// 즉 target을 ' '로 준 경우, 두 개 이상의 ' '를 하나의 ' '로 만든다.
/// 
/// \param text 원본 문자열
/// \param target 대상이 되는 글자
/// \return string 변환한 문자열
//////////////////////////////////////////////////////////////////////////////
string squeeze(const string& text, char target)
{
    string str = text;
    replace(str, string(2, target), string(1, target));
    return str;
}



}// namespace jString