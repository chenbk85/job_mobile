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
/// \brief �־��� ���ڿ� ���� �����ϴ� ���ڿ��� �ٸ� ���ڿ��� ġȯ�Ѵ�.
/// \param text ���� ���ڿ�
/// \param find_token ã���� �ϴ� ���ڿ�
/// \param replace_token ġȯ�ϰ��� �ϴ� ���ڿ�
//////////////////////////////////////////////////////////////////////////////
void replace(string& text, const string& find_token, const string& replace_token)
{
    size_t i = 0;
    while ((i = text.find(find_token)) != string::npos)
        text.replace(i, find_token.size(), replace_token);
}

//////////////////////////////////////////////////////////////////////////////
/// \brief ���� ���ο� �������� ��� ���ڸ� �ϳ��� �����.
///
/// �� target�� ' '�� �� ���, �� �� �̻��� ' '�� �ϳ��� ' '�� �����.
/// 
/// \param text ���� ���ڿ�
/// \param target ����� �Ǵ� ����
/// \return string ��ȯ�� ���ڿ�
//////////////////////////////////////////////////////////////////////////////
string squeeze(const string& text, char target)
{
    string str = text;
    replace(str, string(2, target), string(1, target));
    return str;
}



}// namespace jString