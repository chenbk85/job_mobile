/* file : log.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2013-01-04 18:09:03
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "header/lib_poco_header.h"

// using Poco::Logger;
// using Poco::PatternFormatter;
// using Poco::FormattingChannel;
// using Poco::ConsoleChannel;
// using Poco::FileChannel;
// using Poco::Message;

namespace nMSG
{
  Poco::LogStream *g_LogStream;

  void Init_MSG_Log()
  {
    Poco::Logger& logger = Poco::Util::Application::instance().logger();
    g_LogStream = new Poco::LogStream (logger);
    MSG_INFO() << "OK : " << __FUNCTION__ << std::endl;
  }

}//namespace nMSG
