#include "gateway/gateway.hpp"

#include "database.hpp"
#include "../game/dump.h"
#include "protocol/dump.hpp"
#include "../MOB_lib/nMOB.h"

/* -------------------------------------------------------------------------- */

class DatabaseFactory:
    public MSG::Database::Factory
{
public:
    MSG::Database* create(MSG::Gateway& gateway)
    {
		return new ::Database(gateway);
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

	// X(PACKET이름		,허용가능한 반복시간)
#	define for_each_Client_UserGateServer_REPEAT_TIME(X)\
	X(x2ug_echo			,1000)\

#	define __set_repeat_time(PACKET,TIME_MSEC) \
	nMOB::g_allowed_repeat_time[Client_UserGateServer_Type_##PACKET]=TIME_MSEC;

	for_each_Client_UserGateServer_REPEAT_TIME(__set_repeat_time)

	void init_UserGateServer();init_UserGateServer();
    // 게이트웨이 구동
    return MSG::main(argc, argv);
}
