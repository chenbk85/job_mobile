#include <stdafx.h>

/*
9 Ŀ���� Ŭ������ ������� RandomAccessContainer �����ϱ�
�� ���� ����� �ִ�. Ŭ���� ��ü�� '<' �����ڸ� �������ִ� ����� �ְ�, �Լ��ڸ� �̿��ϴ� ����� �ִ�. 
#include <algorithm>
#include <vector>

class myclass
{
public:
    string StrKey; // ���ڿ� Ű
    int    IntKey; // ���� Ű

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
std::sort(v.begin(), v.end()); // ���ڿ� ������ ����
std::sort(v.begin(), v.end(), COMPARE_MYCLASS_INT()); // ���� ������ ����
Ŭ���� ��ü�� '<' �����ڸ� �������ִ� ����� ��ü�� �����ͷ� �̷���� �÷��ǿ��� ������ �� �����Ƿ� �Լ��ڸ� �̿��ϴ� ����� ����. �Դٰ� �Լ��ڸ� �������� �θ� �������� ������� ������ �� �ִ�. 

*/