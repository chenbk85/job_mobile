/* file : log.hpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2013-01-04 18:07:51
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"

namespace nMSG
{
  extern void Init_MSG_Log();

  extern Poco::LogStream *g_LogStream;

}//namespace nMSG

#define MSG_ERROR() nMSG::g_LogStream->information(__FUNCTION__)
#define MSG_WARN() nMSG::g_LogStream->warning(__FUNCTION__)
#define MSG_INFO() nMSG::g_LogStream->information(__FUNCTION__)
#define MSG_LOG() nMSG::g_LogStream->debug(__FUNCTION__)

