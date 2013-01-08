#include <boost/test/unit_test.hpp>

#include "gateway.h"
#include "proto.h"


using namespace boost::unit_test_framework;



void test_play3()
{
    std::cout << "TEST PLAY #3\n";

    Gateway g;

    if (g.connect("localhost", 13000, 10) == false)
    {
        std::cerr << "gateway1 cannot connect game server\n";
        return;
    }

    {
        // 사용자 로그인 정보
        GReqProtocol request;
        request.set_type(GReqProtocol::GREQGAMEENTER);

        GReqGameEnter *enter;
        enter = request.mutable_reqgameenter();
        enter->set_gameid(100);
        enter->set_categoryid(1);
        enter->set_channelid(1);
        enter->set_roomid(10);

        GameUserInfo user;

        MemberInfo member;  
        member.set_game_id(100);
        member.set_avatar_url("test");
        member.set_nick_name("test");
        member.set_gender_option(true);

        member.SerializeToString(user.mutable_member_info());

        GameInfo* game = user.mutable_game_info();
        game->set_game_id(100);

        user.SerializeToString(enter->mutable_gameuserinfo());
        g.send(request);

        GAnsProtocol answer;
        BOOST_CHECK(g.wait(answer));
        BOOST_CHECK(answer.type() == GAnsProtocol::GANSGAMEENTER);
    }

    {
        GReqProtocol request;
        request.set_type(GReqProtocol::GREQGAMELEAVE);

        GReqGameLeave *leave = request.mutable_reqgameleave();

        leave->set_gameid(100);
        leave->set_kick(true);

        g.send(request);

        GAnsProtocol answer;
        BOOST_CHECK(g.wait(answer));
        BOOST_CHECK(answer.type() == GAnsProtocol::GANSGAMELEAVE);
    }

    g.disconnect();
}
