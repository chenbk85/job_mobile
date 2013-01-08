#ifndef _BACKEND_HPP_
#define _BACKEND_HPP_

#include <boost/thread.hpp>
#include <boost/any.hpp>
#include <boost/asio.hpp>
#include <boost/thread/future.hpp>

#include "../proto/presence.pb.h"

// Define backend interface

// maybe needed later to differentiate stdall with fastcall...
#define BACKEND_CALL

namespace presence
{

// forward declaration
class GameService;
typedef boost::shared_ptr<GameService> SpGameService;

typedef struct {
    const int op;                                                                                     // operation (e.g. LOGIN, GAMEENTER)
    BACKEND_CALL void (*handler) (void *, void *, SpGameService, boost::promise<int> *);    // corresponding handler to operation
} handler_rec;

typedef boost::asio::detail::wrapped_handler<boost::asio::io_service&, void (*)(void *, void *, SpGameService, boost::promise<int> *)> SKSK;

struct BackEndModule
{
    BACKEND_CALL int (*init_func)();
    BACKEND_CALL int (*config_func)();   // maybe pass ServerConfig to this?
    BACKEND_CALL int (*cleanup_func)();
    // entry point from boost::signal2 event to module
    const char * id;                     // use this for content filter
    int module_version;                  // module's version
    int api_version;                     // server version
    int index;                           // used to ordering module
    bool active;                         // self-explanatory
    const handler_rec *handlers;
    boost::asio::io_service module_io_service;
    boost::shared_ptr<boost::asio::io_service::work> module_work_service_ptr;
    boost::shared_ptr<SKSK> entry_point;
    boost::thread_group worker_thread;

    struct BackEndModule *next;

    BackEndModule() { MSG_LOG() << "creating BackEndModule\n"; };
    virtual ~BackEndModule() { MSG_LOG() << "destroying BackEndModule\n"; };
};

}

#endif
