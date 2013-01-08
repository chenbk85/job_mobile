
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

    //  요소 1,2,...,9 (을)를 삽입한다
    for (int i=1; i<=9; ++i) {
        coll.push_back(i);
    }
    PRINT_ELEMENTS(coll);

    //  각 요소에10 (을)를 더해 한층 더5 배가 된다
    transform (coll.begin(),coll.end(),
               ostream_iterator<int>(cout," "),
               compose_f_gx(bind2nd(multiplies<int>(),5),
                            bind2nd(plus<int>(),10)));
    cout << endl;
}
#endif