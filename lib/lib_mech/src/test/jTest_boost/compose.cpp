
#include <stdafx.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include "print.hpp"
#if 0
#include "boost/compose.hpp"

using namespace std;
using namespace boost;

int main_compose()
{
    vector<int> coll;

    //  ��� 1,2,...,9 (��)�� �����Ѵ�
    for (int i=1; i<=9; ++i) {
        coll.push_back(i);
    }
    PRINT_ELEMENTS(coll);

    //  �� ��ҿ�10 (��)�� ���� ���� ��5 �谡 �ȴ�
    transform (coll.begin(),coll.end(),
               ostream_iterator<int>(cout," "),
               compose_f_gx(bind2nd(multiplies<int>(),5),
                            bind2nd(plus<int>(),10)));
    cout << endl;
}
#endif