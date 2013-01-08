/* file : MOB_net.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2011-12-26 16:34:07
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __MOB_net_header__
#define __MOB_net_header__
#pragma once


#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>    //타이머 사용을 위해

#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

using boost::asio::ip::tcp;

#include "MOB_net_interface.h"



#endif // __MOB_net_header__
