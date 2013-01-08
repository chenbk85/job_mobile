#include <stdafx.h>
#include <iostream>
#include <string>
#include <boost/regex.hpp>
using namespace std;

/*

*/

bool validate_card_format(const std::string s)
{
   static const boost::regex e("(\\d{4}[- ]){3}\\d{4}");
   /* ����1 : 
		\d���ڰ� ��Ȯ�� 4�� ���� "-" or " "�� �� �׸���
	 �׸��� ����1�� �ٽ� ��Ȯ�� 3������ �������� \d(����)�� �ٽ� 4����*/
   return regex_match(s, e);
}

// match any format with the regular expression:
const boost::regex e("\\A(\\d{3,4})[- ]?(\\d{4})[- ]?(\\d{4})[- ]?(\\d{4})\\z");
const std::string machine_format("\\1\\2\\3\\4");
const std::string human_format("\\1-\\2-\\3-\\4");

std::string machine_readable_card_number(const std::string s)
{ 
   return regex_replace(s, e, machine_format, boost::match_default | boost::format_sed);
}

std::string human_readable_card_number(const std::string s)
{
   return regex_replace(s, e, human_format, boost::match_default | boost::format_sed);
}


int main_regex()
{
	cout << "1234-1234 6344 5654 = " << validate_card_format("1234-1234 6344 5654") << endl;
	cout << "123451234 6344 5654 = " << validate_card_format("123451234 6344 5654") << endl;

	std::string sz1 ="1234-1234-6344-5654";
	std::string s1 =machine_readable_card_number(sz1);
	cout <<"machine_readable_card_number(sz1)" << s1 << endl;
	cout <<"human_readable_card_number(s1)" << human_readable_card_number(s1) << endl;


	// <�� ���۵Ǿ� >�׸��� ������ ���ڿ��� ��ġ�ϴ� ���� ǥ������ �˻�
	boost::regex  r( "<[^>]+>" );
	boost::smatch m;
	string str1 = "The HTML tag <title > means that ...";

	if( boost::regex_search(str1, m, r) )
	{
		cout << "found (pos=" << m.position() << ")" << endl;
		cout << " ==> " << m.str() << endl;
	}

	// ��ġ�� �κ���, ���Ŀ�#(��)�� ���� ���ڿ��� ġȯ�Ѵ�
	boost::regex r2( "A([1-9]*|[a-z]*)A" );
	string str2 = "A123A AaaaA A3b3A A9A";

	{
		cout <<
			boost::regex_replace(
			  str2, r2, "#$0#", boost::format_all )
		<< endl;
	}
	return 0;
}




int main_regix2()
{
    try
    {
        const boost::regex e("([A-Z][a-z]+[A-Z][a-z]+|\\[.*\\])");
        std::string text = 
            "TestCase is WikiName. but TESTCase is not WikiName! Is [this] WikiName?";

        boost::match_results<std::string::const_iterator> m;
        std::string::const_iterator start = text.begin();
        std::string::const_iterator end = text.end();

        while (boost::regex_search(start, end, m, e))
        {
            // m[0]�� ��ġ�ϴ� �κ� ���ڿ��� ��Ÿ����,
            // m[0].first�� ��ġ�ϴ� �κ��� ���� ��ġ,
            // m[0].second�� ��ġ�ϴ� �κ��� ���� ��Ÿ����.
            // m[n]�� ���� ǥ����(��ȣ�� �ѷ����� ǥ����)�� ��Ÿ���µ�, 
            // ���� ���� ǥ���Ŀ� ���� ǥ������ �������� �ʱ� ������, 
            // ���⼭�� [0] �ۿ��� �� ���� ����.
            cout << m[0] << " = "
                << m[0].first - text.begin() << "~"
                << m[0].second - text.begin() << endl;

            start = m[0].second;
        }
    }
    catch (std::exception& e)
    {
        cerr << e.what() << endl;
    }

	cout << endl<< endl<< "main_regex3()" << endl;
	int main_regex3(); main_regex3();
    
    return 0;
}
#include <boost/regex.hpp>
#include <iostream>
#include <sstream>

int main_regex3()
{
    try
    {
        const boost::regex e("([A-Z][a-z]+[A-Z][a-z]+|\\[.*\\])");
        std::string text = 
            "TestCase is WikiName. but TESTCase is not WikiName! Is [this] WikiName?";

        std::string::const_iterator start = text.begin();
        std::string::const_iterator end = text.end();
        std::stringstream result;
        std::ostream_iterator<char, char> oi(result);

        // $0�� ���� ǥ���Ŀ� ��ġ�ϴ� �κ� ��ü�� �ǹ��Ѵ�. 
        // �ڼ��� ���� ��(perl) ������ ����.
        boost::regex_replace(oi, start, end,
            e, "{{$0}}", boost::match_default | boost::format_all);

        cout << result.str() << endl;

        // �̷� ����� �����ϴ�.
        // cout << boost::regex_replace(text,
        //     e, "{{$0}}", boost::match_default | boost::format_all);
    }
    catch (std::exception& e)
    {
        cerr << "Exception: " << e.what() << endl;
    }
    
    return 0;
}
/*
const boost::regex e("([A-Z][a-z]+[A-Z][a-z]+|\\[.*\\])");
std::string text = 
"TestCase is WikiName. but TESTCase is not WikiName! Is [this] WikiName?";
 cout << boost::regex_replace(text, e
	 , "{{$0}}", boost::match_default | boost::format_all);
*/