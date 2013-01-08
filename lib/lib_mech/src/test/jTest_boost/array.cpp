
#include <stdafx.h>
/* Ŭ���� array<>�� �ܼ��� ��� �� 
 */
int main_array1()
{
	// 6��¥�� float�迭����
    typedef boost::array<float,6> Array; 

	Array a = { { 42 } };// array �� ������ �ʱ�ȭ

    // ��ҿ� ����
    for (unsigned i=1; i<a.size()-1; ++i) {
        a[i] = a[i-1]+1;
    }

    // STL �����̳ʷ� �����ϴ� ������ �� �� �غ���.
    std::cout << "size:     " << a.size() << std::endl;
    std::cout << "empty:    " << std::boolalpha 
								 << a.empty() << std::endl;
    std::cout << "max_size: " << a.max_size() << std::endl;
    std::cout << "front:    " << a.front() << std::endl;
    std::cout << "back:     " << a.back() << std::endl;
    std::cout << "elems:    ";

    // ��� ��ҿ� ���ؼ� �ݺ� ������ �غ���.
	Array::const_iterator pos=a.begin();
    for ( ; pos<a.end(); ++pos) {
        std::cout << *pos << ' ';
    }
    std::cout << std::endl;

    // ���� �����ڿ� ���� ������ üũ
    Array b(a);
    Array c;
    c = a;

	//assert( a==b && a==c );

    if (a==b && a==c) {
        std::cout 
			<< "��������� & ����Ȱ��OK"
           << std::endl;
    }
    else {
        std::cout 
			<< "��������� & ����Ȱ�� ����"
			<< std::endl;
    }

    return 0;  // makes Visual-C++ compiler happy
}


template <typename T>
void test_static_size (const T& cont)
{
    int tmp[T::static_size];
    for (unsigned i=0; i<T::static_size; ++i) {
        tmp[i] = int(cont[i]);
    }
    for (unsigned i=0; i<T::static_size; ++i) {
        std::cout << tmp[i] << ' ';
    }
    std::cout << std::endl;
}

int main_array()
{
    // Ư���� ���� ���� �Ѵ�.
    typedef boost::array<float,6> Array;

    // array�� ������ �ʱ�ȭ  ����!!!
    const Array a = { { 12.34 ,23.98} };

    // STL �����̳ʿ��� �������� �ϴ� ������ �� ��  �غ���. 
    std::cout << "static_size: " << a.size() << std::endl;
    std::cout << "size:        " << a.size() << std::endl;
    std::cout << "empty:       " << std::boolalpha << a.empty() << std::endl;
    std::cout << "max_size:    " << a.max_size() << std::endl;
    std::cout << "front:       " << a.front() << std::endl;
    std::cout << "back:        " << a.back() << std::endl;
    std::cout << "[0]:         " << a[0] << std::endl;
    std::cout << "elems:       ";

    // ��� ��ҿ� ���ؼ� �ݺ������� ���Ѵ�. 
    for (Array::const_iterator pos=a.begin(); pos<a.end(); ++pos) {
        std::cout << *pos << ' ';
    }
    std::cout << std::endl;
    test_static_size(a);

    // ���� �����ڿ� ���� ������ üũ
    Array b(a);
    Array c;
    c = a;
    if (a==b && a==c) {
        std::cout << "copy construction and copy assignment are OK"
                  << std::endl;
    }
    else {
        std::cout << "copy construction and copy assignment are BROKEN"
                  << std::endl;
    }

	if(sizeof(double) !=sizeof(int))
	{
		printf("\nif(sizeof(double) !=sizeof(int))\n");
	}
    typedef boost::array<double,6> DArray;
    typedef boost::array<int,6> IArray;
    IArray ia = { 1, 2, 3, 4, 5, 6 };
	printf("IArray \n\n");
    for (IArray::const_iterator pos=ia.begin(); pos<ia.end(); ++pos) {
        std::cout << *pos << ' ';
    }

    DArray da;
    da = ia;
	printf("DArray \n\n");
    for (DArray::const_iterator pos1=da.begin(); pos1<da.end(); ++pos1) {
        std::cout << *pos1 << ' ';
    }
    da.assign(42.23432983);
	printf("DArray \n\n");
    for (DArray::const_iterator pos1=da.begin(); pos1<da.end(); ++pos1) {
        std::cout << *pos1 << ' ';
    }


    return 0;  // makes Visual-C++ compiler happy
}
/*

main_array call!!!
static_size: 6
size:        6
empty:       false
max_size:    6
front:       12.34
back:        0
[0]:         12.34
elems:       12.34 23.98 0 0 0 0
12 23 0 0 0 0
copy construction and copy assignment are OK

if(sizeof(double) !=sizeof(int))
IArray

1 2 3 4 5 6 DArray

1 2 3 4 5 6 DArray

42.2343 42.2343 42.2343 42.2343 42.2343 42.2343
*/

/* Ŭ���� array<> �� ��뿹
 */
#include <algorithm>
#include <functional>
#include <boost/array.hpp>
#include "print.hpp"
using namespace std;
using namespace boost;

struct _test2
{
	int i;
	std::string str;
	_test2():i(2),str("asdf"){}

};


int main_array2()
{
    array<_test2,10> test2;
    for (unsigned i=0; i<test2.size(); ++i) {
        cout << test2[i].i << " " << test2[i].str.c_str() << " ,";
    }

    // array �� ������ �ʱ�ȭ
    array<int,10> a = { { 1, 2, 3, 4, 5 } };
	cout << endl << endl;

    print_elements(a); //1 2 3 4 5 0 0 0 0 0

    // ��Ҹ� ���� ���� �Ѵ�.
    for (unsigned i=0; i<a.size(); ++i) {
        ++a[i];
    }
    print_elements(a);

    // STL �˰����� ����Ͽ� ������ �ٲ۴�.
    reverse(a.begin(),a.end());
    print_elements(a);

    // STL ������ ��ũ�� ����Ͽ� ����� ������ ���Ѵ�.
    transform(a.begin(),a.end(),    // source
              a.begin(),            // destination
              negate<int>());       // operation
    print_elements(a);

    return 0;  // makes Visual-C++ compiler happy
}
/*

main_array2 call!!!
2 asdf ,2 asdf ,2 asdf ,2 asdf ,2 asdf ,2 asdf ,2 asdf ,2 asdf ,2 asdf ,2 asdf ,

1 2 3 4 5 0 0 0 0 0
2 3 4 5 6 1 1 1 1 1
1 1 1 1 1 6 5 4 3 2
-1 -1 -1 -1 -1 -6 -5 -4 -3 -2

*/


int main_array3()
{
    // 4���� array �� �����.
    boost::array<std::string,4> seasons = {
        { "spring", "summer", "autumn", "winter" }
    };

    // �����ؼ� ������ �ٲ۴�. 
    boost::array<std::string,4> seasons_orig = seasons;
    for (unsigned i=seasons.size()-1; i>0; --i) {
        swap(seasons.at(i),seasons.at((i+1)%seasons.size()));
    }

    std::cout << "one way:   ";
    print_elements(seasons);

    // swap()�� ������ ����.
    std::cout << "other way: ";
    swap(seasons,seasons_orig);
    print_elements(seasons);

    // �� �ݺ��ڸ� ����� ����.
    std::cout << "reverse:   ";
    for (boost::array<std::string,4>::reverse_iterator pos
           =seasons.rbegin(); pos<seasons.rend(); ++pos) {
        std::cout << " " << *pos;
    }
    std::cout << std::endl;

    return 0;  // makes Visual-C++ compiler happy
}
/*

main_array3 call!!!
one way:   winter spring summer autumn
other way: spring summer autumn winter
reverse:    winter autumn summer spring

*/



/* Ŭ���� array<> �� ��뿹
 */
int main_array4()
{
    // 4������ array�� array
    boost::array<boost::array<std::string,4>,2> seasons_i18n = {
        { { { "spring", "summer", "autumn", "winter", } },
          { { "Fruehling", "Sommer", "Herbst", "Winter" } }
        }
    };

    // ��� array�� ������� ����Ѵ�. 
    for (unsigned i=0; i<seasons_i18n.size(); ++i) {
        boost::array<std::string,4> seasons = seasons_i18n[i];
        for (unsigned j=0; j<seasons.size(); ++j) {
			std::cout << seasons[j] << " ";
        }
        std::cout << std::endl;
    }

    // ������ array�� ������ ��Ҹ� ����Ѵ�.
    std::cout << "first element of first array: "
              << seasons_i18n[0][0] << std::endl;

    // ������ array�� ������ ��Ҹ� ����Ѵ�.
    std::cout << "last element of last array: "
              << seasons_i18n[seasons_i18n.size()-1][seasons_i18n[0].size()-1]
              << std::endl;

    return 0;  // makes Visual-C++ compiler happy
}
/*
main_array4 call!!!
spring summer autumn winter
Fruehling Sommer Herbst Winter
first element of first array: spring
last element of last array: Winter

*/