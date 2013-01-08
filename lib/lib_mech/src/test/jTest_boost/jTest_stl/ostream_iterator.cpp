#include<stdafx.h>
#include <windows.h>
#include <iterator>
#include <iostream>
#include <vector>
using namespace std;

int main_ostream_iterator()
{
    ostream_iterator<int> os(cout); //bind iterator to cout
    *os=10; //causes cout<<10
    os++; //prepare for the next output operation
    *os=5; //cout<<5
	return 0;
}

#include <algorithm> //std::copy()
#include <iterator>
#include <iostream>
#include <fstream>
using namespace std;

void file_out_test(const vector<int> &vi)
{
    //open a file in write mode
    ofstream vi_dump("vi.txt");
    if (!vi_dump) //failure?
    {
        cerr<<"couldn't open file";
        exit(1);
    }
    copy(vi.begin(),
        vi.end(),
        ostream_iterator<int> (vi_dump, " "));
}


#include<vector>
#include<fstream>
#include<algorithm>
#include<cstdlib>
#include<iostream>
using namespace std;

int file_to_vector_test()
{
    vector<int> vi;//vector to be filled
    ifstream vi_dump("vi.txt"); //open for read
    if (!vi_dump)
    {
        cerr<<"couldn't open file";
        exit(1);
    }
    copy(istream_iterator<int> (vi_dump),
        istream_iterator<int> (),
        back_inserter(vi));
}

void func()
{
    vector<int> vi(10,35); //fill with 10 int of the value 35
    //write contents of vi to cout, each number on a new line
    std::copy(vi.begin(),
        vi.end(),
        ostream_iterator<int> (cout, "\n"));

	file_out_test(vi);

}

int main_ostream_iterator_copy()
{
	func();

    std::copy(istream_iterator<int> (cin),
        istream_iterator<int> (),
        ostream_iterator<int> (cout, " "));
	return 0;
}
