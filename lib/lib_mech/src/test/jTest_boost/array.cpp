
#include <stdafx.h>
/* 클래스 array<>의 단순한 사용 예 
 */
int main_array1()
{
	// 6개짜리 float배열정의
    typedef boost::array<float,6> Array; 

	Array a = { { 42 } };// array 의 생성과 초기화

    // 요소에 접근
    for (unsigned i=1; i<a.size()-1; ++i) {
        a[i] = a[i-1]+1;
    }

    // STL 컨테이너로 공통하는 조작을 몇 개 해본다.
    std::cout << "size:     " << a.size() << std::endl;
    std::cout << "empty:    " << std::boolalpha 
								 << a.empty() << std::endl;
    std::cout << "max_size: " << a.max_size() << std::endl;
    std::cout << "front:    " << a.front() << std::endl;
    std::cout << "back:     " << a.back() << std::endl;
    std::cout << "elems:    ";

    // 모든 요소에 대해서 반복 조작을 해본다.
	Array::const_iterator pos=a.begin();
    for ( ; pos<a.end(); ++pos) {
        std::cout << *pos << ' ';
    }
    std::cout << std::endl;

    // 복사 생성자와 대입 연산자 체크
    Array b(a);
    Array c;
    c = a;

	//assert( a==b && a==c );

    if (a==b && a==c) {
        std::cout 
			<< "복사생성자 & 복사활당OK"
           << std::endl;
    }
    else {
        std::cout 
			<< "복사생성자 & 복사활당 실패"
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
    // 특수한 형을 정의 한다.
    typedef boost::array<float,6> Array;

    // array의 생성과 초기화  주의!!!
    const Array a = { { 12.34 ,23.98} };

    // STL 컨테이너에서 공통으로 하는 조작을 몇 개  해본다. 
    std::cout << "static_size: " << a.size() << std::endl;
    std::cout << "size:        " << a.size() << std::endl;
    std::cout << "empty:       " << std::boolalpha << a.empty() << std::endl;
    std::cout << "max_size:    " << a.max_size() << std::endl;
    std::cout << "front:       " << a.front() << std::endl;
    std::cout << "back:        " << a.back() << std::endl;
    std::cout << "[0]:         " << a[0] << std::endl;
    std::cout << "elems:       ";

    // 모든 요소에 대해서 반복조작을 행한다. 
    for (Array::const_iterator pos=a.begin(); pos<a.end(); ++pos) {
        std::cout << *pos << ' ';
    }
    std::cout << std::endl;
    test_static_size(a);

    // 복사 생성자와 대입 연사자 체크
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

/* 클래스 array<> 의 사용예
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

    // array 의 생성과 초기화
    array<int,10> a = { { 1, 2, 3, 4, 5 } };
	cout << endl << endl;

    print_elements(a); //1 2 3 4 5 0 0 0 0 0

    // 요소를 직접 변경 한다.
    for (unsigned i=0; i<a.size(); ++i) {
        ++a[i];
    }
    print_elements(a);

    // STL 알고리즘을 사용하여 순서를 바꾼다.
    reverse(a.begin(),a.end());
    print_elements(a);

    // STL 프레임 워크를 사용하여 요소의 부정을 취한다.
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
    // 4게절 array 를 만든다.
    boost::array<std::string,4> seasons = {
        { "spring", "summer", "autumn", "winter" }
    };

    // 복사해서 순서를 바꾼다. 
    boost::array<std::string,4> seasons_orig = seasons;
    for (unsigned i=seasons.size()-1; i>0; --i) {
        swap(seasons.at(i),seasons.at((i+1)%seasons.size()));
    }

    std::cout << "one way:   ";
    print_elements(seasons);

    // swap()을 시험해 본다.
    std::cout << "other way: ";
    swap(seasons,seasons_orig);
    print_elements(seasons);

    // 역 반복자를 사용해 본다.
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



/* 클래스 array<> 의 사용예
 */
int main_array4()
{
    // 4계절의 array의 array
    boost::array<boost::array<std::string,4>,2> seasons_i18n = {
        { { { "spring", "summer", "autumn", "winter", } },
          { { "Fruehling", "Sommer", "Herbst", "Winter" } }
        }
    };

    // 모든 array의 사계절을 출력한다. 
    for (unsigned i=0; i<seasons_i18n.size(); ++i) {
        boost::array<std::string,4> seasons = seasons_i18n[i];
        for (unsigned j=0; j<seasons.size(); ++j) {
			std::cout << seasons[j] << " ";
        }
        std::cout << std::endl;
    }

    // 최초의 array의 최초의 요소를 출력한다.
    std::cout << "first element of first array: "
              << seasons_i18n[0][0] << std::endl;

    // 마지막 array의 마지막 요소를 출력한다.
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