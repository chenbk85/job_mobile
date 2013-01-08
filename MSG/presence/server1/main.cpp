
//
// main.cpp
// ~~~~~~~~
//
//
#include "stdafx.h"
#include "server.hpp"
#include "config.hpp"

#include "backend_handler.hpp"
#include "backend_room.hpp"

#include "MSG_presence_task.h"



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
    MSG_LOG() << "Initialize Fail !!! " <<  std::endl;
    MSG_LOG() << "Presence Server stop !!! " <<  std::endl;
    return;
  }
  MSG_LOG() << "World Initialization Success!!! " <<  std::endl;

  //int ret = setup_monitoring();

  presence::Server s("0.0.0.0", "6000", "0.0.0.0", "6001");	  
  MSG_LOG() << "Server Initialization Success!!! " <<  std::endl;
  s.run();

  //unload_monitoring(ret);
  MSG_LOG() << "Presence Server Ended." << std::endl;
}



class MSG_presence_server: public Poco::Util::ServerApplication
{
public:
  MSG_presence_server(): _helpRequested(false)
  {
  }

  ~MSG_presence_server()
  {
  }

protected:
  void initialize(Application& self)
  {
    loadConfiguration(); // load default configuration files, if present
    Poco::Util::ServerApplication::initialize(self);
    logger().information("starting up");
  }

  void uninitialize()
  {
    logger().information("shutting down");
    Poco::Util::ServerApplication::uninitialize();
  }

  void defineOptions(Poco::Util::OptionSet& options)
  {
    Poco::Util::ServerApplication::defineOptions(options);

    options.addOption(
      Poco::Util::Option("help", "h", "display help information on command line arguments")
      .required(false)
      .repeatable(false)
      .callback(Poco::Util::OptionCallback<MSG_presence_server>(this, &MSG_presence_server::handleHelp)));
  }

  void handleHelp(const std::string& name, const std::string& value)
  {
    _helpRequested = true;
    displayHelp();
    stopOptionsProcessing();
  }

  void displayHelp()
  {
    Poco::Util::HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("OPTIONS");
    helpFormatter.setHeader("A sample server application that demonstrates some of the features of the Util::ServerApplication class.");
    helpFormatter.format(std::cout);
  }

  int main(const std::vector<std::string>& args)
  {
    if (_helpRequested) return Application::EXIT_OK;

    nMSG::Init_MSG_Log();

    MSG_INFO() << " begin" << std::endl;

    Poco::TaskManager tm;
    tm.start(new MSG_presence_Task);
    waitForTerminationRequest();
    tm.cancelAll();
    tm.joinAll();
    MSG_INFO() << " end" << std::endl;
    return Application::EXIT_OK;
  }

private:
  bool _helpRequested;
};


POCO_SERVER_MAIN(MSG_presence_server)

