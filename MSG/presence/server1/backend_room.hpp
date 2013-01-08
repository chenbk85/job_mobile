// Presence Server
// Copyright 2012 Neowiz Mobile Inc.  All rights reserved.
// http://nwmsvn.nwinet.co.kr/svn/presence_sk68
//
// Copyright blah blah blah
//
// Author: sk68@neowiz.com (Sung Ho Kim)
//  Original code by Kwon Taek Soon (kts123@neowiz.com)
//
// backend_room.hpp -- Reference header of a module that uses
//                     GameService as a repository to maintain a knowledge
//                     of user allocation in pre-existing game rooms (category)
//
#include "common_def.hpp"
#include "config.hpp"
#include "game_service.hpp"
#include "backend.hpp"

// This class is for internal use by the presence server and by
// presence backend dispatch.  It must not be called
// directly by clients.
//
// This class contains code for implementing the binary protocol buffer
// wire format via reflection.  The WireFormatLite class implements the
// non-reflection based routines.
struct BackEndModuleRoom : public presence::BackEndModule
{
    // TODO: disable copy constructor (because we only want one module per server)
    //       and I don't like singleton stuff
    BackEndModuleRoom();
    ~BackEndModuleRoom();
};
