#include "stdafx.h"
#include "fast_serialization.h"

int main_fast_serialization()
{
	const int a[3] = {1, 2, 3};
	int a1[3] = {4, 5, 6};

	std::stringstream ss;
	{   
		fast_binary_oarchive pboa(ss);
		pboa << a;
	}
	{
		fast_binary_iarchive pbia(ss);
		pbia >> a1;
	}
	return (a[0] != a1[0]) || (a[1] != a1[1]) || (a[2] != a1[2]);
}
