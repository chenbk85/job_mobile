#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "../gen-cpp/Calculator.h"

using namespace tutorial;
using namespace shared;

class CalculatorHandler : public CalculatorIf {
public:
    CalculatorHandler();

    void ping();

    int32_t add(const int32_t n1, const int32_t n2);

    int32_t calculate(const int32_t logid, const Work &work);

    void getStruct(SharedStruct &ret, const int32_t logid);

    void zip();

protected:
    std::map<int32_t, SharedStruct> log;

};
#endif // HANDLER_HPP
