#include <thrift/protocol/TBinaryProtocol.h>

#include <iostream>
#include <stdexcept>
#include <sstream>

#include <time.h>

#include "../gen-cpp/Calculator.h"

#include <async/TAsioAsync.h>
#include <async/TFuture.h>

using namespace apache::thrift;

using namespace tutorial;
using namespace shared;
namespace asio_thrift
{

	class CalculatorAsyncHandler : public CalculatorAsyncIf {
	public:
		CalculatorAsyncHandler(boost::asio::io_service& io_service) : io_service_(io_service) {}

		virtual ping_shared_future_t ping() {
			printf("ping()\n");

			// This method is declared as "void ping();", but we still want to notify the client
			// that the method was invoked successfully.
			// When we want to return immediately, there are convenience constructors to make this
			// much less tedious. In this case, since void is not a legal type in C++, a dummy
			// boolean has to be used in place of it. The value of the boolean is actually ignored.
			return true;
		}

		virtual add_shared_future_t add(const int32_t num1, const int32_t num2) {
			printf("add(%d,%d)\n", num1, num2);

			// When there is nothing to return yet and we want to defer returning a value, we return
			// a "promise" in its place. This is a way to signal that we promise to return a value
			// at a later point.
			add_shared_promise_t promise;

			// Construct an ASIO timer (we could also fire off a thread here)
			boost::shared_ptr<boost::asio::deadline_timer> timer(new boost::asio::deadline_timer(io_service_, boost::posix_time::seconds(num1 + num2)));

			// The only reason we pass the timer as the argument is that we want it not to be destroyed
			timer->async_wait(boost::bind(&CalculatorAsyncHandler::wait_done, this, num1 + num2, promise, timer));

			return promise;
			// Notice that the signature of the method is add_shared_future_t add(...), i.e. the promise
			// will be cast to a future. Why does this make sense? In English, a "promise" refers to 
			// the same thing regardless of one is making a promise or if one is receiving a promise.
			// In this case, the receiver of the "promise" will take this as a grant that a value will
			// be returned later, which is what we refer to as a future.
		}

		virtual void wait_done(const int32_t sum, add_shared_promise_t promise, boost::shared_ptr<boost::asio::deadline_timer> timer) {
			printf("returning to client\n");

			// The preferred syntax is to write the result straight into the promise by using
			// the method success() returning a reference to the result value.
			promise.success() = sum;
			promise.callback();

			// We could also have simply written promise.callback(sum). For complex types, the
			// former is slightly more efficient, since the value does not have to be copied.
			// If sum was a vector of a million elements, this would have mattered.

			printf("done\n");
			// The timer will fall out of scope now and will be deleted
		}

		virtual calculate_shared_future_t calculate(const int32_t logid, const Work& w) {
			calculate_shared_promise_t promise;

			printf("calculate(%d,{%d,%d,%d})\n", logid, w.op, w.num1, w.num2);
			int32_t val;

			switch (w.op) {
			case ADD:
				val = w.num1 + w.num2;
				break;
			case SUBTRACT:
				val = w.num1 - w.num2;
				break;
			case MULTIPLY:
				val = w.num1 * w.num2;
				break;
			case DIVIDE:
				if (w.num2 == 0) {
					InvalidOperation io;
					io.what = w.op;
					io.why = "Cannot divide by 0";

					// By taking advantage of one of the constructors of the futures, we can
					// throw any exception by returning the corresponding error object.
					return calculate_ouch(io);
				}
				val = w.num1 / w.num2;
				break;
			default:
				return calculate_failure(std::string("Invalid Operation"));
			}

			SharedStruct ss;
			ss.key = logid;
			char buffer[12];
			snprintf(buffer, sizeof(buffer), "%d", val);
			ss.value = buffer;

			log_[logid] = ss;

			printf("val = %d\n", val);

			// The most fundamental and most verbose way to return a value is:
			//
			// calculate_shared_promise_t promise;
			// promise.success() = vale;
			// promise.callback();
			// return promise;
			//
			// By taking advantage of the callback(...) shortcut, we can shorten this to:
			//
			// calculate_shared_promise_t promise;
			// promise.callback(val);
			// return promise;
			//
			// However, since we don't want to defer passing a result back, we can use another
			// shortcut which involves taking advantage of a convenience constructor:

			return val;
		}

		virtual getStruct_shared_future_t getStruct(const int32_t key) {
			printf("getStruct(%d)\n", key);
			return log_[key];
		}

		virtual void zip() {
			printf("zip()\n");
			// Oneway function
		}

	protected:
		boost::asio::io_service& io_service_;
		std::map<int32_t, SharedStruct> log_;
	};

	int main() 
	{
		boost::asio::io_service io_service;

		boost::shared_ptr<protocol::TProtocolFactory> protocolFactory(new protocol::TBinaryProtocolFactory());
		boost::shared_ptr<CalculatorAsyncHandler> handler(new CalculatorAsyncHandler(io_service));
		boost::shared_ptr<TProcessor> processor(new CalculatorAsyncProcessor(handler));

		boost::shared_ptr<apache::thrift::async::TAsioServer> server(
			new apache::thrift::async::TAsioServer(
			io_service,
			9090,
			protocolFactory,
			protocolFactory,
			processor));

		server->start(); // Nonblocking
		io_service.run(); // Blocking

		return 0;
	}

}
