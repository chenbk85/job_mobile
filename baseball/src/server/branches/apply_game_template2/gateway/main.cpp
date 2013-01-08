#include "gateway/gateway.hpp"

#include "database.hpp"
#include "../game/dump.h"
#include "protocol/dump.hpp"

/* -------------------------------------------------------------------------- */

class DatabaseFactory:
    public MSG::Database::Factory
{
public:
    MSG::Database* create(MSG::Gateway& gateway)
    {
        return new Database(gateway);
    }
};

#if 0
/* -------------------------------------------------------------------------- */

static void
DumpGameReqProtocol(const std::string& data, std::stream& out)
{
    GLReqGameProtocol req;

    if (req.ParseFromString(data))
    {
        DumpGLReqGameProtocol(req, log);
    }
}

/* -------------------------------------------------------------------------- */

static void
DumpGameAnsProtocol(const std::string& data, std::stream& out)
{
    GLAnsGameProtocol ans;

    if (ans.ParseFromString(data))
    {
        DumpGLAnsGameProtocol(ans, out);
    }
}

/* -------------------------------------------------------------------------- */
#endif


int 
main(int argc, const char* argv[])
{
    // 데이터베이스 팩토리 설정
    DatabaseFactory db;

    MSG::Database::set_factory(&db);

//    MSG::dump_game_req_protocol = DumpGameReqProtocol;
//    MSG::dump_game_ans_protocol = DumpGameAnsProtocol; 

    // 게이트웨이 구동
    return MSG::main(argc, argv);
}
