#ifndef __BASEBALL_PROTOCOL_DUMP_H__
#define __BASEBALL_PROTOCOL_DUMP_H__

#include "proto.h"

void DumpGameInfo(const GameInfo& info, 
                        std::ostream& out = std::cerr);

void DumpGameUserInfo(const GameUserInfo& info, 
                        std::ostream& out = std::cerr );

void DumpGameRoomInfo(const GameRoomInfo& info, 
                            std::ostream& out = std::cerr );

void DumpGLReqGameProtocol(const GLReqGameProtocol& request, 
                                    std::ostream& out = std::cerr );

void DumpGLAnsGameProtocol(const GLAnsGameProtocol& answer, 
                                    std::ostream& out = std::cerr );

#endif
