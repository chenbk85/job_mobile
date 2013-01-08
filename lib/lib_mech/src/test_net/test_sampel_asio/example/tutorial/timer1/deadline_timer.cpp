//
// timer.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/timer.hpp>



int main(int argc, char *argv[])
{
	boost::asio::io_service io;

	boost::timer ti;
	boost::asio::deadline_timer dt(io, boost::posix_time::seconds(2));

	dt.wait();
	std::cout << ti.elapsed() << " seconds" << std::endl;

	return 0;
}
#if 0
void f()
{
	progress_timer t;

	start = t.elapsed();
	correct = 0;
	for(unsigned int i = 0; i < count; i++)
	{ 
		if (results[i] == data[i] * data[i]) 
		{ 
			correct++; 
		} 
	} 
	cout << "Second for loop took " << t.elapsed() - start << " seconds \n" << endl; 
	cout << "Computed " << correct << "/" << count << " correct values" << endl; 
	cout << "Computed " << 100.f * (float)correct/(float)count << "% correct values" << endl; 
}
#endif



using namespace std;
#define LOG_PRINT(X) cout<< __FUNCTION__ << " " << GetCurrentThreadId() << ") " << X  << std::endl;

int main1()
{
	boost::asio::io_service io;

	boost::asio::deadline_timer dt(io, boost::posix_time::seconds(5));
	dt.wait();

	std::cout << "Hello, world!\n";

	return 0;
}
