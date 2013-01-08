#include <boost/test/unit_test.hpp>

#include "gateway.h"
#include "proto.h"


using namespace boost::unit_test_framework;



void test_play4()
{
    std::cout << "TEST PLAY #4\n";

    Gateway g1;

    if (g1.connect("localhost", 13000, 10) == false)
    {
        std::cerr << "gateway1 cannot connect game server\n";
        return;
    }

    Gateway g2;

    if (g2.connect("localhost", 13000, 10) == false)
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
        g1.send(request);

        GAnsProtocol answer;
        BOOST_CHECK(g1.wait(answer));
        BOOST_CHECK(answer.type() == GAnsProtocol::GANSGAMEENTER);
    }


    {
        // 사용자 로그인 정보
        GReqProtocol request;
        request.set_type(GReqProtocol::GREQGAMEENTER);

        GReqGameEnter *enter;
        enter = request.mutable_reqgameenter();
        enter->set_gameid(101);
        enter->set_categoryid(1);
        enter->set_channelid(1);
        enter->set_roomid(10);

        GameUserInfo user;

        MemberInfo member;  
        member.set_game_id(101);
        member.set_avatar_url("test");
        member.set_nick_name("test");
        member.set_gender_option(true);

        member.SerializeToString(user.mutable_member_info());

        GameInfo* game = user.mutable_game_info();
        game->set_game_id(101);

        user.SerializeToString(enter->mutable_gameuserinfo());
        g2.send(request);

        GAnsProtocol answer;
        BOOST_CHECK(g2.wait(answer));
        BOOST_CHECK(answer.type() == GAnsProtocol::GANSGAMEENTER);
    }


    {
        // 다른 유저가 들어올때 s_ans_join_room을 받는지 확인

        // Gateway1은 GLAnsGameProtocol을 받아야 하고, 
        // 내용은 s_ans_join_room임
        GAnsProtocol answer; 
        BOOST_CHECK(g1.wait(answer));
        BOOST_CHECK(answer.type() == GAnsProtocol::GLANSGAMEPROTOCOL);
    }


    {
        // Gateway2 퇴장
        GReqProtocol request;
        request.set_type(GReqProtocol::GREQGAMELEAVE);

        GReqGameLeave *leave = request.mutable_reqgameleave();

        leave->set_gameid(101);
        leave->set_kick(true);

        g2.send(request);

        GAnsProtocol answer;
        BOOST_CHECK(g2.wait(answer));
        BOOST_CHECK(answer.type() == GAnsProtocol::GANSGAMELEAVE);
    }


    {
        // Gateway1 퇴장
        GReqProtocol request;
        request.set_type(GReqProtocol::GREQGAMELEAVE);

        GReqGameLeave *leave = request.mutable_reqgameleave();

        leave->set_gameid(100);
        leave->set_kick(true);

        g1.send(request);

        GAnsProtocol answer;
        BOOST_CHECK(g1.wait(answer));
        BOOST_CHECK(answer.type() == GAnsProtocol::GANSGAMELEAVE);
    }

    g1.disconnect();
    g2.disconnect();
}
