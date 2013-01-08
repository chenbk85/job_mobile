#include "TAsioAsync.h"

// #define DEBUG_PRINT_PACKETS

namespace apache { namespace thrift { namespace async {

  // namespace { // begin anonymous namespace

struct message {
  int len;
  boost::shared_array<uint8_t> buf;
};

class TAsioOutputTransport : public TAsyncOutputTransport {
  // This class should not be used outside TAsioAsync.cpp, consider moving it there.
 public:
  TAsioOutputTransport(boost::shared_ptr<boost::asio::ip::tcp::socket> socket) :
    socket_(socket),
    isCurrentlyWriting_(false)
    {}

  void write(const uint8_t* buf, uint32_t len) {  // from transport::TTransport
    outData_.insert(outData_.end(), &buf[0], &buf[len]);
  }
  
  void flush() {  // from transport::TTransport
    uint32_t outDataSize = outData_.size();
    message m;
    m.len = outDataSize + 4;
    m.buf = boost::shared_array<uint8_t>(new uint8_t[outDataSize + 4]);
    
    // Put data in the outbuffer
    m.buf[0] = (outDataSize >> 24) & 0xff;
    m.buf[1] = (outDataSize >> 16) & 0xff;
    m.buf[2] = (outDataSize >>  8) & 0xff;
    m.buf[3] = (outDataSize >>  0) & 0xff;
    std::copy(&outData_[0], &outData_[outDataSize], &m.buf[4]);
    
#ifdef DEBUG_PRINT_PACKETS
    printf("output: ");
    for (int i = 0; i < outDataSize; i++)
      printf("%02x ", outData_[i]);
    printf("\n");
#endif

    // Delete internal buffer
    outData_.clear();
    
    // Queue into buffer
    outQueue_.push_back(m);  
  
    // If not currently writing, start
    if (!isCurrentlyWriting_) {
      isCurrentlyWriting_ = true;
      writeNext();
    }
  }
  
  void writeNext() {
    if (!outQueue_.size()) {
      isCurrentlyWriting_ = false;
      return;
    }

    // By passing m.buf as an argument, we are guaranteed that it will remain in memory
    message m = outQueue_.front();
    outQueue_.pop_front();
    boost::asio::async_write(*socket_, boost::asio::buffer(m.buf.get(), m.len), boost::bind(&TAsioOutputTransport::handleWriteFinished, this, boost::asio::placeholders::error, m));
  }
  
  void handleWriteFinished(const boost::system::error_code& error, const message& m) {
    // Temporary memory buffer will be deleted when this scope closes
    
    if (error) {
      std::cout << "An error occurred when writing message" << std::endl;
      return;
    }

    writeNext();
  }

 private:
  boost::shared_ptr<boost::asio::ip::tcp::socket> socket_;
  std::vector<uint8_t> outData_;
  bool isCurrentlyWriting_;
  std::deque<message> outQueue_;
};

class TAsioInputTransport {
 public:
  TAsioInputTransport(boost::shared_ptr<boost::asio::ip::tcp::socket> socket) : 
    socket_(socket)
    {}

  void read(boost::function<void (const uint8_t* buf, uint32_t len)> callback) {
    boost::asio::async_read(*socket_, boost::asio::buffer(length_, 4), boost::bind(&TAsioInputTransport::handleReadLength, this/*shared_from_this()*/, _1, callback));
  }

 private:
  void handleReadLength(const boost::system::error_code& error, boost::function<void (const uint8_t* buf, uint32_t len)> callback) {
    if (error) {
      std::cout << "An error occurred when reading length header" << std::endl;
      return;
      
      // Note on memory: TAsioServerClient is actually owned by a shared_ptr from the callback, so it will be automatically destructed
    }
    uint32_t bufLen =
      ((length_[0] & 0xff) << 24) |
      ((length_[1] & 0xff) << 16) |
      ((length_[2] & 0xff) <<  8) |
      ((length_[3] & 0xff) <<  0);
    
    inData_.resize(bufLen);
    boost::asio::async_read(*socket_, boost::asio::buffer(inData_, bufLen), boost::bind(&TAsioInputTransport::handleReadMessage, this/*shared_from_this()*/, _1, callback));
  }

  void handleReadMessage(const boost::system::error_code& error, boost::function<void (const uint8_t* buf, uint32_t len)> callback) {
    if (error) {
      std::cout << "An error occurred when reading frame" << std::endl;
      return;
      
      // See comment about memory in handleReadLength
    }

    callback(&inData_[0], inData_.size());
    inData_.clear();
  }

  uint8_t length_[4];
  std::vector<uint8_t> inData_;
  boost::shared_ptr<boost::asio::ip::tcp::socket> socket_;
};


class TAsioServerClient : public boost::enable_shared_from_this<TAsioServerClient> {
  // This class should not be used outside TAsioAsync.cpp, consider moving it there.
 public:
  TAsioServerClient(boost::shared_ptr<boost::asio::ip::tcp::socket> socket,
		    boost::shared_ptr<protocol::TProtocolFactory> iProtocolFactory,
		    boost::shared_ptr<protocol::TProtocolFactory> oProtocolFactory,
		    boost::shared_ptr<TProcessor> processor) :
    iProtocolFactory_(iProtocolFactory),
    oProtocolFactory_(oProtocolFactory),
    processor_(processor),
    iTransport_(socket),
    oTransport_(new TAsioOutputTransport(socket))
    { }

  void start() { read(); }
  
  ~TAsioServerClient() { std::cout << "Disconnecting client" << std::endl; }

 private:  
  void read() {
    iTransport_.read(boost::bind(&TAsioServerClient::handleMessage, /* this */shared_from_this(), _1, _2)); // todo: errback
  }
  
  void handleMessage(const uint8_t* buf, uint32_t len) {
    // todo: add error handling
    
    boost::shared_ptr<transport::TTransport> iTransport(new transport::TMemoryBuffer(const_cast<uint8_t*>(buf), len));  // TMemoryBuffer guarantees it will not touch
    boost::shared_ptr<protocol::TProtocol> iProtocol(iProtocolFactory_->getProtocol(iTransport));
    boost::shared_ptr<protocol::TProtocol> oProtocol(oProtocolFactory_->getProtocol(oTransport_));
    
#ifdef DEBUG_PRINT_PACKETS
    printf("input: ");
    for (int i = 0; i < len; i++)
      printf("%02x ", buf[i]);
    printf("\n");
#endif
    
    processor_->process(iProtocol, oProtocol,0);
    read();
  }

  boost::shared_ptr<boost::asio::ip::tcp::socket> socket_;
  boost::shared_ptr<protocol::TProtocolFactory> iProtocolFactory_;
  boost::shared_ptr<protocol::TProtocolFactory> oProtocolFactory_;
  boost::shared_ptr<TProcessor> processor_;
  TAsioInputTransport iTransport_;
  boost::shared_ptr<TAsioOutputTransport> oTransport_;
};

  // } // end anonymous namespace

void TAsioServer::serve() {
  socket_.reset(new boost::asio::ip::tcp::socket(io_service_)); // socket of the next client
  acceptor_.async_accept(*socket_, boost::bind(&TAsioServer::handleAccept, shared_from_this(), boost::asio::placeholders::error));
}

void TAsioServer::handleAccept(const boost::system::error_code& error) {
  if (error) {
    std::cout << "An error occurred while accepting" << std::endl;
    return;
    // We will stop accepting at this point
    // Call errback?
  }
  
  boost::shared_ptr<TAsioServerClient> client(new TAsioServerClient(socket_, iProtocolFactory_, oProtocolFactory_, processor_));
  client->start();
  
  serve(); // next client plz
}

boost::shared_ptr<TAsyncOutputTransport> TAsioClient::getOutputTransport() {
  return boost::shared_ptr<TAsyncOutputTransport>(new TAsioOutputTransport(socket_));
}

void TAsioClient::startReadingInput(boost::shared_ptr<TProcessor> processor) {
  boost::shared_ptr<TAsioInputTransport> iTransport(new TAsioInputTransport(socket_));
    
  // Start read loop. iTransport will stay in memory as long as the loop is still running, since it is being referred
  // to from the shared_ptr in the callback.
  iTransport->read(boost::bind(&TAsioClient::handleMessage, shared_from_this(), _1, _2, iTransport, processor)); // todo: errback
}

void TAsioClient::handleMessage(const uint8_t* buf, uint32_t len, boost::shared_ptr<TAsioInputTransport> iTransport, boost::shared_ptr<TProcessor> processor) {
  // I'm binding iTransport and processor so that these will stay in scope as long as data is read. Not too happy about
  // this, but is there a better way of doing it?

  boost::shared_ptr<transport::TTransport> iTransport2(new transport::TMemoryBuffer(const_cast<uint8_t*>(buf), len));
  boost::shared_ptr<protocol::TProtocol> iProtocol(iProtocolFactory_->getProtocol(iTransport2));
  
  processor->process(iProtocol,0);

  // Read next message
  iTransport->read(boost::bind(&TAsioClient::handleMessage, shared_from_this(), _1, _2, iTransport, processor)); // todo: errback
}

void TAsioClient::connectSimple(const std::string& host, short port, boost::function<void (void)> callback) {
  // Start an asynchronous resolve to translate the server and service names
  // into a list of endpoints.
  std::stringstream ss;
  ss << port;
  boost::asio::ip::tcp::resolver::query query(host, ss.str());
  resolver_.async_resolve(query,
			  boost::bind(&TAsioClient::handleResolve, this,
				      boost::asio::placeholders::error,
				      boost::asio::placeholders::iterator,
				      callback));
}

void TAsioClient::handleResolve(const boost::system::error_code& err,
			    boost::asio::ip::tcp::resolver::iterator endpoint_iterator,
			    boost::function<void (void)> callback) {
  if (!err) {
    // Attempt a connection to the first endpoint in the list. Each endpoint
    // will be tried until we successfully establish a connection.
    boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
    socket_->async_connect(endpoint,
			   boost::bind(&TAsioClient::handleConnect, this,
				       boost::asio::placeholders::error,
				       ++endpoint_iterator,
				       callback));
  } else {
    std::cout << "Error: " << err.message() << std::endl;
  }
}

void TAsioClient::handleConnect(const boost::system::error_code& err,
			    boost::asio::ip::tcp::resolver::iterator endpoint_iterator,
			    boost::function<void (void)> callback) {
  if (!err) {
    // Everything is connected, now let's build the client and etc...
    callback();
    
  } else if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator()) {
    // The connection failed. Try the next endpoint in the list.
    socket_->close();
    boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
    socket_->async_connect(endpoint,
			   boost::bind(&TAsioClient::handleConnect, this,
				       boost::asio::placeholders::error,
				       ++endpoint_iterator,
				       callback));
  } else {
    std::cout << "Error: " << err.message() << std::endl;
    
    // Todo: call user-provided errback
  }
}

} } }
