//
//  DualGoInclude.h
//  DualGoServer
//
//  Created by jin young park on 11. 11. 23..
//  Copyright (c) 2011년 집. All rights reserved.
//

#ifndef DualGoServer_DualGoInclude_h
#define DualGoServer_DualGoInclude_h

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>                               
#include <boost/date_time/posix_time/posix_time.hpp>    //타이머 사용을 위해

#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include "GoStopInclude.h"
#include "LogicMultiCommand.h"          //멀티 로직 제어부

#include <google/protobuf/io/zero_copy_stream_impl.h>

#include "gameLogic.pb.h"
#include "game.pb.h"
#include "ug.pb.h"
#include "db.pb.h"

#include "MultiGoDefine.h"
#include "MultiRoom.h"
#include "MultiUser.h"
#include "MultiGoManager.h"

typedef boost::shared_ptr<CMultiUser> user_ptr;
typedef std::list<user_ptr> user_list;


#endif
