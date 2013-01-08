#include "dump.h"

#include "protocol/ug.pb.h"
#include "proto.h"

#include <iostream>


using namespace std;

/* -------------------------------------------------------------------------- */

void 
DumpGameInfo(const GameInfo& info, std::ostream& out)
{
  out << "Dump GameInfo -----------------------------\n";
  //out << "  game_id: " << info.game_id() << endl;
//   out << "  index: " << info.index() << endl;
//   out << "  level: " << info.level() << endl;
//   out << "  money: " << info.money() << endl;
//   out << "  win: " << info.win() << endl;
//   out << "  lose: " << info.lose() << endl;
//   out << "  royal_straight_flush: " << info.royal_straight_flush() << endl;
//   out << "  straight_flush: " << info.straight_flush() << endl;
//   out << "  fourcard: " << info.fourcard() << endl;
//   out << "  today_win: " << info.today_win() << endl;
//   out << "  today_lose: " << info.today_lose() << endl;
//   out << "  today_play_time: " << info.today_play_time() << endl;
//   out << "  today_delta_money: " << info.today_delta_money() << endl;
//   out << "  today_event: " << info.today_event() << endl;
//   out << "  today_refill: " << info.today_refill() << endl;
//   out << "  safe_money: " << info.safe_money() << endl;
  out << "-------------------------------------------\n";
}

/* -------------------------------------------------------------------------- */

void 
DumpGameUserInfo(const GameUserInfo& info, std::ostream& out)
{
  out << "Dump GameUserInfo -----------------------------\n";
  out << "  GameInfo\n";
  //out << "    game_id: " << info.game_info().game_id() << endl;
  out << "  MemberInfo\n";
  MemberInfo member;
  member.ParseFromString(info.member_info());
  out << "    game_id: " << member.game_id() << endl;
  out << "    avatar_url: " << member.avatar_url() << endl;
  out << "    nick_name: " << member.nick_name() << endl;
  out << "    gender_option: " << member.gender_option() << endl;
  out << "-------------------------------------------\n";
}

/* -------------------------------------------------------------------------- */

void
DumpGameRoomInfo(const GameRoomInfo& info, std::ostream& out)
{
  out << "Dump GameRoomInfo -------------------------\n";
  out << "  roomid: " << info.room_id() << endl;

#if 0
  for(int i = 0; i < info.game_user_info_size(); i++)
  {
    const GameUserInfo& user_info = info.game_user_info(i);

    out << "  GameUserInfo #" << i << endl;
    out << "    GameInfo\n";
    out << "      game_id: " << userinfo.gameinfo().gameid() << endl;
    out << "      game_index: " << userinfo.gameinfo().gameindex() << endl;
    out << "      level: " << userinfo.gameinfo().level() << endl;
    out << "      exp: " << userinfo.gameinfo().exp() << endl;
    out << "      money: " << userinfo.gameinfo().money() << endl;
    out << "      win_cnt: " << userinfo.gameinfo().wincnt() << endl;
    out << "      lose_cnt: " << userinfo.gameinfo().losecnt() << endl;
    out << "    MemberInfo\n";
    out << "      game_id: " << userinfo.memberinfo().gameid() << endl;
    out << "      nick_name: " << userinfo.memberinfo().nickname() << endl;
  }
#endif

  out << "-------------------------------------------\n";
}

/* -------------------------------------------------------------------------- */

void 
DumpGLReqGameProtocol(const GLReqGameProtocol& request, std::ostream& out)
{
  out << "Dump GLReqGameProtocol --------------------\n";

  out << "-------------------------------------------\n";
}

/* -------------------------------------------------------------------------- */

void 
DumpGLAnsGameProtocol(const GLAnsGameProtocol& answer, std::ostream& out)
{
  out << "Dump GLAnsGameProtocol --------------------\n";

  out << "-------------------------------------------\n";
}

/* -------------------------------------------------------------------------- */
