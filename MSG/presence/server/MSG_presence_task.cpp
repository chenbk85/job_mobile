/* file : MSG_presence_task.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2013-01-08 11:41:52
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "MSG_presence_task.h"


#include "server.hpp"
#include "config.hpp"

#include "backend_handler.hpp"
#include "backend_room.hpp"


void MSG_presence_Task::runTask()
{
  Poco::Util::Application& app = Poco::Util::Application::instance();

  MSG_INFO() << "busy doing nothing... " + Poco::DateTimeFormatter::format(app.uptime());

  BackEndModuleRoom bem;
  std::vector<presence::BackEndModule *> modules;
  modules.push_back(&bem);

  bool is_ok = (0 > presence::get_backend().init(&modules)) ? false : true;

  if (is_ok == false)
  {
    MSG_ERROR() << "Initialize Fail !!! " <<  std::endl;
    MSG_ERROR() << "Presence Server stop !!! " <<  std::endl;
    return;
  }
  MSG_INFO() << "World Initialization Success!!! " <<  std::endl;

  //int ret = setup_monitoring();

  presence::Server s("0.0.0.0", "6000", "0.0.0.0", "6001");	  
  MSG_INFO() << "Server Initialization Success!!! " <<  std::endl;
  s.run();

  //unload_monitoring(ret);
  MSG_LOG() << "Presence Server Ended." << std::endl;
}
