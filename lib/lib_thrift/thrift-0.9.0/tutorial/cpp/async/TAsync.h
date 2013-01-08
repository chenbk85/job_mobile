#ifndef _TASYNC_H_
#define _TASYNC_H_ 1

#include <boost/function.hpp>
#include <thrift/transport/TTransport.h>
#include <boost/shared_ptr.hpp>

namespace apache { namespace thrift { namespace async {

class TAsyncOutputTransport : public transport::TTransport {
  // Asynchronous transport.
  //
  // The asynchronousity gives us an interesting asymmetry. We are
  // free to write to an underlying socket at any time, but cannot
  // read from it in any way. This class is simply meant to be a
  // superclass of unidirectional nonblocking out transports,
  // disallowing the read method.

 public:
  virtual void write(const uint8_t* /* buf */, uint32_t /* len */) = 0;
  virtual void flush() = 0;

  virtual uint32_t read(uint8_t* /* buf */, uint32_t /* len */) {
    // This method should not be overridden!!
    throw transport::TTransportException(transport::TTransportException::NOT_OPEN, "Asynchronous transports cannot read.");
  }

  virtual ~TAsyncOutputTransport() {}
};

// More stuff should go here, so far not enough generalization has been done

} } }

#endif
