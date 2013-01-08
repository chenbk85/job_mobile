#include <stdafx.h>
#include <iostream>
#include <boost/utility.hpp>
using namespace std;
 
struct OpAmpOverloaded
{
        void operator&() {}
		int aa;
};
 
int main_addressof()
{
        OpAmpOverloaded obj;
 
        cout << "Address of obj is " << reinterpret_cast<int>(boost::addressof(obj)) << endl;
        cout << "Address of obj is " << (boost::addressof(obj)) << endl;

		//	OpAmpOverloaded * aa = obj;
		//printf(" addr = %d ",&obj);
        
 
        //cout << "Address of obj is " <<
        //  reinterpret_cast<int>(&obj) << endl;
 
        return 0;
}
