#ifndef _TASIOASYNC_H_
#define _TASIOASYNC_H_

#include <async/TAsync.h>
#include <thrift/transport/TBufferTransports.h>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/shared_array.hpp>
#include <vector>
#include <deque>
#include <thrift/protocol/TProtocol.h>
#include <thrift/TProcessor.h>



namespace apache { namespace thrift { namespace async {

class TAsioInputTransport; // fwd declaration

class TAsioServer : public boost::enable_shared_from_this<TAsioServer> {
  // Class for a Thrift server.
  // The server must be instantiated within a shared_ptr or else it will throw tr1::weak_ptr
 public:
  TAsioServer(boost::asio::io_service& io_service,
	      short port,
	      boost::shared_ptr<protocol::TProtocolFactory> iProtocolFactory,
	      boost::shared_ptr<protocol::TProtocolFactory> oProtocolFactory,
	      boost::shared_ptr<TProcessor> processor) :
    io_service_(io_service),
    acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    iProtocolFactory_(iProtocolFactory),
    oProtocolFactory_(oProtocolFactory),
    processor_(processor)
    {}

  void start() { serve(); }

 private:
  void serve();
  void handleAccept(const boost::system::error_code& error);

  boost::asio::io_service& io_service_;
  boost::asio::ip::tcp::acceptor acceptor_;
  boost::shared_ptr<protocol::TProtocolFactory> iProtocolFactory_;
  boost::shared_ptr<protocol::TProtocolFactory> oProtocolFactory_;
  boost::shared_ptr<TProcessor> processor_;
  boost::shared_ptr<boost::asio::ip::tcp::socket> socket_;
};

class TAsioClient : public boost::enable_shared_from_this<TAsioClient> {
  // Class for client connections

  // This class must be instantiated within a boost::shared_ptr or else it will throw a
  // tr1::weak_ptr upon connect. 
  // Bad:  TAsioClient t(...)
  // Good: boost::shared_ptr<TAsioClient> t(...)

 public:
  TAsioClient(boost::asio::io_service& io_service,
	      boost::shared_ptr<protocol::TProtocolFactory> iProtocolFactory,
	      boost::shared_ptr<protocol::TProtocolFactory> oProtocolFactory
	      ) :
    resolver_(io_service),
    socket_(new boost::asio::ip::tcp::socket(io_service)),
    iProtocolFactory_(iProtocolFactory),
    oProtocolFactory_(oProtocolFactory)
    {}

  template<typename T>
    void connect(const std::string& host, short port, void (&callback)(boost::shared_ptr<T> client)) {
      // Constructor of boost::function seems to be unable to do an automatic cast of raw function pointers, so we provide
      // this convenience method wrapping connect(...).
      boost::function<void (boost::shared_ptr<T> client)> callback2(callback);
      connect(host, port, callback2);
    }

  template<typename T>
    void connect(const std::string& host, short port, boost::function<void (boost::shared_ptr<T> client)> callback) {
    // T is inferred from the type of the callback. I'm not too sure if this is apparent.
    // This function untemplatizes by binding a new callback to build<T> and passing it on to the internal connect code.
    // The reason we need to use templates at all is that we have to construct arbitrary processor objects within the
    // scope of TAsioClient. We couldn't let the user provide us with an processor object since the processor is
    // dependent on internals of TAsioClient (the output transport), and internals of TAsioClient (the input transport)
    // is dependent on the processor. See how build(...) works.
    boost::function<void (void)> finalCallback = boost::bind(&TAsioClient::build<T>, this, callback);
    connectSimple(host, port, finalCallback);
  }

 private:
  template<typename T>
    void build(boost::function<void (boost::shared_ptr<T> client)> callback) {
    // We are connected, let's build the client.
    boost::shared_ptr<T> client(new T(getOutputTransport(), oProtocolFactory_));
    boost::shared_ptr<TProcessor> processor(client); // Simply reinterpreted as a base class (T is derived from TProcessor)

    startReadingInput(processor);

    // Call user-provided callback to signal success.
    callback(client);
  }

  boost::shared_ptr<TAsyncOutputTransport> getOutputTransport();
  void startReadingInput(boost::shared_ptr<TProcessor> processor);

  void handleMessage(const uint8_t* buf, uint32_t len, boost::shared_ptr<TAsioInputTransport> iTransport, boost::shared_ptr<TProcessor> processor);
  void connectSimple(const std::string& host, short port, boost::function<void (void)> callback);
  void handleResolve(const boost::system::error_code& err,
		     boost::asio::ip::tcp::resolver::iterator endpoint_iterator,
		     boost::function<void (void)> callback);
  void handleConnect(const boost::system::error_code& err,
		     boost::asio::ip::tcp::resolver::iterator endpoint_iterator,
		     boost::function<void (void)> callback);


  boost::asio::ip::tcp::resolver resolver_;
  boost::shared_ptr<boost::asio::ip::tcp::socket> socket_;
  boost::shared_ptr<protocol::TProtocolFactory> iProtocolFactory_;
  boost::shared_ptr<protocol::TProtocolFactory> oProtocolFactory_;
};

} } }

#endif
