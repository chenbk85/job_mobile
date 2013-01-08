#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;


void test_play1();
void test_play2();
void test_play3();
//void test_play4();
//void test_play5();

#include "../proto.h"

 #include "../game/excel_baseball_table_db.pb.cc"
 #include "../gameLogic.pb.cc"
 #include "../PT_BaseballServer.pb.cc"



test_suite*
init_unit_test_suite(int argc, char* argv[])
{
  test_suite* baseball = BOOST_TEST_SUITE("Baseball Server Test");


  baseball->add(BOOST_TEST_CASE(&test_play1), 0);

  baseball->add(BOOST_TEST_CASE(&test_play2), 0);

  baseball->add(BOOST_TEST_CASE(&test_play3), 0);


//  baseball->add(BOOST_TEST_CASE(&test_play5), 0);


  framework::master_test_suite().add(baseball);

  return 0;
}
