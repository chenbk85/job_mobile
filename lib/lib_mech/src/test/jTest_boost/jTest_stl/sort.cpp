#include <stdafx.h>

/*
9 커스텀 클래스로 만들어진 RandomAccessContainer 정렬하기
두 가지 방법이 있다. 클래스 자체에 '<' 연산자를 정의해주는 방법이 있고, 함수자를 이용하는 방법이 있다. 
#include <algorithm>
#include <vector>

class myclass
{
public:
    string StrKey; // 문자열 키
    int    IntKey; // 정수 키

public:
    myclass(const string& skey, int ikey) 
    : StrKey(skey), IntKey(ikey) {}

public:
    bool operator < (const myclass& arg) {
        return StrKey < arg.StrKey;
    }
};

struct COMPARE_MYCLASS_INT
{
    bool operator < (const myclass& lhs, const myclass& rhs) {
        return rhs.IntKey < rhs.IntKey;
    }
};
...
vector<myclass> v;
std::sort(v.begin(), v.end()); // 문자열 순으로 정렬
std::sort(v.begin(), v.end(), COMPARE_MYCLASS_INT()); // 정수 순으로 정렬
클래스 자체에 '<' 연산자를 정의해주는 방법은 객체의 포인터로 이루어진 컬렉션에는 적용할 수 없으므로 함수자를 이용하는 방법이 낫다. 게다가 함수자를 여러가지 두면 여러가지 방법으로 정렬할 수 있다. 

*/