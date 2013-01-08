// Presence Server
// Copyright 2012 Neowiz Mobile Inc.  All rights reserved.
// http://nwmsvn.nwinet.co.kr/svn/presence_sk68
//
// Copyright blah blah blah
//
// Author: sk68@neowiz.com (Sung Ho Kim)
//  Original code by Kwon Taek Soon (kts123@neowiz.com)
//
// backend_room.cpp -- Reference implementation of a module that uses
//                     GameService as a repository to maintain a knowledge
//                     of user allocation in pre-existing game rooms (category)
//
//                     Receives a PReqProtocol req, parses the corresponding
//                     PresenceCommand within req and activates a handler from
//                     a pool of pre-existing handler threads.  All logic for 
//                     a specific PresenceCommand type is contained in the handler
//                     code (and in GameService)
//
#include "stdafx.h"

#include "../proto/presence.pb.h"
#include "backend_room.hpp"


template<class To, class From>
To any_cast(From v)
{
    return static_cast<To>(static_cast<void*>(v));
}

// Thread pool
boost::asio::io_service op1_io_service;
boost::thread_group op1_handler_threadpool;
boost::shared_ptr<boost::asio::io_service::work> work1(new boost::asio::io_service::work(op1_io_service));

boost::asio::io_service op3_io_service;
boost::thread_group op3_handler_threadpool;
boost::shared_ptr<boost::asio::io_service::work> work3(new boost::asio::io_service::work(op3_io_service));

boost::asio::io_service op2_io_service;
boost::thread_group op2_handler_threadpool;
boost::shared_ptr<boost::asio::io_service::work> work2(new boost::asio::io_service::work(op2_io_service));

boost::asio::io_service op4_io_service;
boost::thread_group op4_handler_threadpool;
boost::shared_ptr<boost::asio::io_service::work> work4(new boost::asio::io_service::work(op4_io_service));

boost::asio::io_service op8_io_service;
boost::thread_group op8_handler_threadpool;
boost::shared_ptr<boost::asio::io_service::work> work8(new boost::asio::io_service::work(op8_io_service));

typedef void (*handler_func)(void *, void *, presence::SpGameService, boost::promise<int> *);

struct assoc_ios_handler
{
    boost::asio::io_service * ios_ptr;
    handler_func handler;
};
std::map<int, assoc_ios_handler> handlers;

// TODO: templatize
void enqueue(PReqProtocol * prp, PAnsProtocol * pap, presence::SpGameService svc, boost::promise<int> * retval)
{
    int op = prp->command(); //implicit conversion from PresenceCommand to int

    std::map<int, assoc_ios_handler>::iterator it = handlers.find( op );
    if (it == handlers.end())
    {
        MSG_LOG() << "[" << boost::this_thread::get_id() << "]enqueue: no handlers found for op=" << op << std::endl;
        // set error code and return!
        //retval->set_exception(boost::unknown_exception());
        retval->set_value(-1);
	return;
    }
    MSG_LOG() << "[" << boost::this_thread::get_id() << "]enqueue:handler found for op=" << op << std::endl;

    /*
    time_t now = time(NULL);
    // format hours, minutes, seconds, and write it to SHM seg
    strftime(mylogpt, 60, "%H:%M.%S", localtime(&now));
    */
    assoc_ios_handler assoc_struct = it->second;

    assoc_struct.ios_ptr->post(boost::bind(assoc_struct.handler, prp, pap, svc, retval));
}

// add throttling and stuff later
// default thread pool size?
// maybe should have used signals2?
// threadpools should be chainable?
template <typename TFunc>
bool initialize(TFunc fun, int op_num, boost::asio::io_service& ios, boost::thread_group * tg)
{
    int poolSize = 10;

    // create a map of handlers (which are themselves thread groups)
    for ( int i = 0; i < poolSize; ++i)
        tg->create_thread( boost::bind(&boost::asio::io_service::run, &ios) );

    assoc_ios_handler tmp;
    tmp.ios_ptr = &ios;
    tmp.handler = fun;

    handlers.insert(
        std::pair<int, assoc_ios_handler>(op_num, tmp)
    );

    // initialization done
    return true;
}

void bem_login_handler(void * req, void * ans, presence::SpGameService svc, boost::promise<int> * err)
{
    MSG_LOG() << "[" << boost::this_thread::get_id() << "]bem_login_handler: (op=";

    //we should be able to catch casting(1) & protobuf member access(2) exceptions
    PReqProtocol * tmp = static_cast<PReqProtocol*>(req);  // 1
    PresenceCommand pc = tmp->command();  // 2
    PAnsProtocol * resp = static_cast<PAnsProtocol*>(ans);
    resp->set_info("LOGIN response");
    resp->set_result(false);
    resp->set_status("U");
    resp->set_command(LOGIN);
    resp->set_detached(false);
    resp->set_category(1);
    resp->set_seqid(1);
    resp->set_gameid(1);
    resp->set_svcid(1);

    if (svc != NULL)
    {
        boost::tuple<bool, std::string> rv = svc->login(tmp->gameid());
        resp->set_result(rv.get<0>());
        resp->set_status(rv.get<1>());
    }

    MSG_LOG() << pc << "," << tmp->gameid() << ")" << std::endl;

    MSG_LOG() << "[" << boost::this_thread::get_id() 
              << "]bem_login_handler sleeping for 10 seconds" << std::endl;
    boost::this_thread::sleep(boost::posix_time::seconds(10));
    err->set_value(0);
}

void bem_logout_handler(void * req, void * ans, presence::SpGameService svc, boost::promise<int> * err)
{
    MSG_LOG() << "[" << boost::this_thread::get_id() << "]bem_logout_handler: (op=";

    //we should be able to catch casting(1) & protobuf member access(2) exceptions
    PReqProtocol * tmp = static_cast<PReqProtocol*>(req);  // 1
    PresenceCommand pc = tmp->command();  // 2
    PAnsProtocol * resp = static_cast<PAnsProtocol*>(ans);
    resp->set_info("LOGOUT response");
    resp->set_result(false);
    resp->set_status("U");
    resp->set_command(LOGOUT);
    resp->set_detached(false);
    resp->set_category(1);
    resp->set_seqid(1);
    resp->set_gameid(1);
    resp->set_svcid(1);

    if (svc != NULL)
    {
        boost::tuple<bool, std::string> rv = svc->logout(tmp->gameid());
        resp->set_result(rv.get<0>());
        resp->set_status(rv.get<1>());
    }

    MSG_LOG() << pc << "," << tmp->gameid() << ")" << std::endl;
    err->set_value(0);
}

void bem_gameenter_handler(void * req, void * ans, presence::SpGameService svc, boost::promise<int> * err)
{
    MSG_LOG() << "[" << boost::this_thread::get_id() << "]bem_gameenter_handler: (op=";
    //we should be able to catch casting(1) & protobuf member access(2) exceptions
    PReqProtocol * tmp = static_cast<PReqProtocol*>(req);  // 1
    PresenceCommand pc = tmp->command();  // 2
    PAnsProtocol * resp = static_cast<PAnsProtocol*>(ans);
    resp->set_info("GAMEENTER response");
    resp->set_result(false);
    resp->set_status("U");
    resp->set_command(GAMEENTER);
    resp->set_detached(false);
    resp->set_category(1);
    resp->set_seqid(1);
    resp->set_gameid(1);
    resp->set_svcid(1);
    resp->set_roomid(presence::kInvalidRoomId);
    resp->set_ip(std::string("invalid_ip"));
    resp->set_port(presence::kInvalidPort);

    if ( svc != NULL )
    {
        boost::tuple<bool, std::string, presence::RoomID, std::string, presence::Port> rv  
            = svc->room_auto_join(tmp->gameid(), tmp->category());
        resp->set_result(rv.get<0>());
        resp->set_status(rv.get<1>());
        resp->set_roomid(rv.get<2>());
        resp->set_ip(rv.get<3>());
        resp->set_port(rv.get<4>());
    }

    MSG_LOG() << pc << "," << tmp->gameid() << ")" << std::endl;
    err->set_value(0);
}

void bem_gameleave_handler(void * req, void * ans, presence::SpGameService svc, boost::promise<int> * err)
{
    MSG_LOG() << "[" << boost::this_thread::get_id() << "]bem_gameleave_handler: (op=";
    //we should be able to catch casting(1) & protobuf member access(2) exceptions
    PReqProtocol * tmp = static_cast<PReqProtocol*>(req);  // 1
    PresenceCommand pc = tmp->command();  // 2
    PAnsProtocol * resp = static_cast<PAnsProtocol*>(ans);
    resp->set_info("GAMELEAVE response");
    resp->set_result(false);
    resp->set_status("U");
    resp->set_command(GAMELEAVE);
    resp->set_detached(false);
    resp->set_category(1);
    resp->set_seqid(1);
    resp->set_gameid(1);
    resp->set_svcid(1);
    resp->set_roomid(presence::kInvalidRoomId);
    resp->set_ip(std::string("invalid_ip"));
    resp->set_port(presence::kInvalidPort);

    if ( svc != NULL )
    {
        boost::tuple<bool, std::string> rv = svc->room_leave(tmp->gameid());
        resp->set_result(rv.get<0>());
        resp->set_status(rv.get<1>());
    }

    MSG_LOG() << pc << "," << tmp->gameid() << ")" << std::endl;
    err->set_value(0);
}

void bem_category_handler(void * req, void * ans, presence::SpGameService svc, boost::promise<int> * err)
{
    MSG_LOG() << "[" << boost::this_thread::get_id() << "]bem_category_handler: (op=";
    //we should be able to catch casting(1) & protobuf member access(2) exceptions
    PReqProtocol * tmp = static_cast<PReqProtocol*>(req);  // 1
    PresenceCommand pc = tmp->command();  // 2
    PAnsProtocol * resp = static_cast<PAnsProtocol*>(ans);
    resp->set_info("CATEGORY response");
    resp->set_result(false);
    resp->set_status("U");
    resp->set_command(CATEGORY);
    resp->set_detached(false);
    resp->set_category(1);
    resp->set_seqid(1);
    resp->set_gameid(1);
    resp->set_svcid(1);
    resp->set_roomid(presence::kInvalidRoomId);
    resp->set_ip(std::string("invalid_ip"));
    resp->set_port(presence::kInvalidPort);

    if ( svc != NULL )
    {
        resp->set_result(true);
        resp->set_status(svc->current_usernum_per_category());
    }

    MSG_LOG() << pc << "," << tmp->gameid() << ")" << std::endl;
    err->set_value(0);
}

void bem_roomlist_handler(void * req, void * ans, presence::SpGameService svc, boost::promise<int> * err)
{
    MSG_LOG() << "[" << boost::this_thread::get_id() << "]bem_roomlist_handler: (op=";
    //we should be able to catch casting(1) & protobuf member access(2) exceptions
    PReqProtocol * tmp = static_cast<PReqProtocol*>(req);  // 1
    PresenceCommand pc = tmp->command();  // 2
    PAnsProtocol * resp = static_cast<PAnsProtocol*>(ans);
    //resp->set_info("ROOMLIST response");
    resp->set_result(false);
    resp->set_status("U");
    resp->set_command(ROOMLIST);
    resp->set_detached(false);
    resp->set_category(1);
    resp->set_seqid(1);
    resp->set_gameid(1);
    resp->set_svcid(1);
    resp->set_roomid(presence::kInvalidRoomId);
    resp->set_ip(std::string("invalid_ip"));
    resp->set_port(presence::kInvalidPort);

    if ( svc != NULL )
    {
        resp->set_result(true);
        resp->set_info(svc->list_rooms(tmp->category()));
    }

    MSG_LOG() << pc << "," << tmp->gameid() << ")" << std::endl;
    err->set_value(0);
}

static const presence::handler_rec bem_handlers[] =
{
    {1, bem_login_handler},
    {2, bem_logout_handler},
    {3, bem_gameenter_handler},
    {4, bem_gameleave_handler},
    {8, bem_roomlist_handler},
    {NULL}
};

// module initialization
int bem_init_func()
{
    MSG_LOG() << "backend_room::initialize" << std::endl;
    initialize(bem_login_handler, 1, op1_io_service, &op1_handler_threadpool);
    initialize(bem_gameenter_handler, 3, op3_io_service, &op3_handler_threadpool);

    initialize(bem_gameleave_handler, 4, op4_io_service, &op4_handler_threadpool);
    initialize(bem_logout_handler, 2, op2_io_service, &op2_handler_threadpool);

    initialize(bem_roomlist_handler, 8, op8_io_service, &op8_handler_threadpool);
    return 0;
}

// module configuration
int bem_config_func()
{
    return 0;
}

// module cleanup
int bem_cleanup_func()
{
    work1.reset();
    work2.reset();
    work3.reset();
    work4.reset();
    work8.reset();

    op1_io_service.stop();
    op2_io_service.stop();        
    op3_io_service.stop();
    op4_io_service.stop();
    op8_io_service.stop();    

    op1_handler_threadpool.join_all();
    op2_handler_threadpool.join_all();
    op3_handler_threadpool.join_all();
    op4_handler_threadpool.join_all();
    op8_handler_threadpool.join_all();

    return 0;
}

/*
    init_func = NULL;
    config_func = NULL;
    cleanup_func = NULL;
    const char * id;
    int module_version;
    int api_version;
    int index;
    const handler_rec *handlers;
    struct BackEndModule *next;
*/

void bem_entry_point(void * prp, void * pap, presence::SpGameService svc, boost::promise<int> * retval)
{
    enqueue(any_cast<PReqProtocol*>(prp), any_cast<PAnsProtocol*>(pap), svc, retval);
}

void WorkerThread(boost::shared_ptr<boost::asio::io_service::work> work)
{
    MSG_LOG() << "Main module thread[" << boost::this_thread::get_id() << "] <start>\n";
    work->get_io_service().run();
    MSG_LOG() << "Main module thread[" << boost::this_thread::get_id() << "] <finish>\n";
 }

//TODO: assigning function pointer to global function can result in
//in undefined behavior when function name collides with a pre-existing
//function (in a library, etc. )
BackEndModuleRoom::BackEndModuleRoom()

{
    MSG_LOG() << "creating BackEndModuleRoom" << std::endl;
    init_func = bem_init_func;
    config_func = bem_config_func;
    cleanup_func = bem_cleanup_func;
    id = "modroom";
    module_version = 65;
    next = NULL;
    handlers = bem_handlers;
    module_work_service_ptr.reset(new boost::asio::io_service::work(module_io_service));
    entry_point = boost::make_shared<presence::SKSK>(module_io_service.wrap(bem_entry_point));
    worker_thread.create_thread( boost::bind(&WorkerThread, module_work_service_ptr) );
}

BackEndModuleRoom::~BackEndModuleRoom()
{
    MSG_LOG() << "destroying BackEndModuleRoom" << std::endl;
    module_work_service_ptr.reset();
    module_io_service.stop();
    worker_thread.join_all();
    bem_cleanup_func();
}
