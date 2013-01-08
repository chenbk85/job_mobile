#include <boost/test/unit_test.hpp>

#include "gateway.h"


using namespace boost::unit_test_framework;



void test_play1()
{
    std::cout << "TEST PLAY #1\n";

    Gateway g;

    if (g.connect("localhost", 13000, 10) == false)
    {
        std::cerr << "gateway1 cannot connect game server\n";
        return;
    }

    g.disconnect();
}
