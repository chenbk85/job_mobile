#include "../stdafx.h" 
#include <unistd.h> 
#include <iostream> 

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN 
#define BOOST_TEST_NO_MAIN 
#include <boost/test/unit_test.hpp> 

#define BOOST_TEST_MODULE baseball_db_test

int
main( int argc, char* argv[] )
{
	if (chdir("./.."))
	{
		std::cerr << "chdir fail " << std::endl;
		return -1;
	}

	Load_Common_CSV();

    return ::boost::unit_test::unit_test_main( &init_unit_test, argc, argv );
}





