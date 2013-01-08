#include "asio_client_server/thrift_handler.hpp"

using namespace tutorial;
using namespace shared;

CalculatorHandler::CalculatorHandler() {}

void CalculatorHandler::ping() {
    printf("ping()\n");
}

int32_t CalculatorHandler::add(const int32_t n1, const int32_t n2) {
    printf("add(%d,%d)\n", n1, n2);
    return n1 + n2;
}

int32_t CalculatorHandler::calculate(const int32_t logid, const Work &work) {
    printf("calculate(%d,{%d,%d,%d})\n", logid, work.op, work.num1, work.num2);
    int32_t val;

    switch (work.op) {
    case Operation::ADD:
        val = work.num1 + work.num2;
        break;
    case Operation::SUBTRACT:
        val = work.num1 - work.num2;
        break;
    case Operation::MULTIPLY:
        val = work.num1 * work.num2;
        break;
    case Operation::DIVIDE:
        if (work.num2 == 0) {
            InvalidOperation io;
            io.what = work.op;
            io.why = "Cannot divide by 0";
            throw io;
        }
        val = work.num1 / work.num2;
        break;
    default:
        InvalidOperation io;
        io.what = work.op;
        io.why = "Invalid Operation";
        throw io;
    }

    SharedStruct ss;
    ss.key = logid;
    char buffer[11];
    sprintf(buffer, "%d", val);
    ss.value = buffer;

    log[logid] = ss;

    return val;
}

void CalculatorHandler::getStruct(SharedStruct &ret, const int32_t logid) {
    printf("getStruct(%d)\n", logid);
    ret = log[logid];
}

void CalculatorHandler::zip() {
    printf("zip()\n");
}
