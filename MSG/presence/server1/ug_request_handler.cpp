//
// UgRequestHandler.cpp
// ~~~~~~~~~~~~~~
//
#include "stdafx.h"
#include "google/protobuf/io/zero_copy_stream_impl.h"

#include "boost/tuple/tuple.hpp"
#include "boost/shared_ptr.hpp"
#include "../proto/presence.pb.h"
#include "connection.hpp"

//#include "world.hpp"
#include "backend_handler.hpp"

#include "ug_request_handler.hpp"
#include "connection_manager.hpp"

namespace presence {
namespace ug_request_handler{
namespace detail {

using boost::tuples::make_tuple;
using boost::tie;
using boost::shared_ptr;

bool handle_message_(GameUserID gid,	SpConnection& con, const PReqProtocol& proto_req, PAnsProtocol* proto_ans);

void handle_error_(	GameUserID gid, SpConnection& con, const boost::system::error_code& e);

} // namespace detail

void handle_message(	GameUserID gid,
       SpConnection& con,
       const boost::system::error_code& e,
       const boost::asio::const_buffer& buffer)
{
    //0. 에러  체크하기.
    if (is_error(e))
        return detail::handle_error_(gid, con, e);

    // 1. google protobuf 를 디시리얼라이즈 하기
    PReqProtocol proto_req;

    google::protobuf::io::ArrayInputStream input(boost::asio::buffer_cast<const unsigned char*>(buffer), buffer_size(buffer));
    bool is_ok = proto_req.ParseFromZeroCopyStream(&input);

    if (is_ok == false)
        return detail::handle_error_(gid, con, boost::system::error_code());

    // 2. 메시지 처리 메인 로직 수행하고 ans 메시지 구하기
    PAnsProtocol proto_ans;
    is_ok = detail::handle_message_(gid, con, proto_req, &proto_ans);
    if (is_ok == false)
       return detail::handle_error_(gid, con, boost::system::error_code());

    // 3. 시리얼라이즈하기.
    Connection::SpBuffer packet  = the_connection_manager.get_buffer(proto_ans.ByteSize());

    std::vector<char>* buffer1 = packet.get();
    // 필요하면 버퍼를 키운다.
    // capacity 변경되는지 체크하여 로그남겨 봐야 될 수도 있음
    buffer1->resize(proto_ans.ByteSize());

    // google proto buffer 용 버퍼 객체 생성
    google::protobuf::io::ArrayOutputStream output(buffer1->data(), buffer1->size());

    // 시리얼라이즈 수행
    is_ok = proto_ans.SerializeToZeroCopyStream(&output);

    assert(buffer1->size() == std::size_t(output.ByteCount()));

    if (is_ok == false)
       return detail::handle_error_(gid, con, boost::system::error_code());

    // 4. 시리얼라이즈된 메시지 전송하기
    con->send(packet);
    
    return;
}

namespace detail {

bool handle_message_(
						GameUserID gid,
						SpConnection& con,
						const PReqProtocol& proto_req,
						PAnsProtocol* proto_ans)
{
	// 2. 메시지 처리 메인 로직을 수행하여 ug_msg 타입의 ans 값 구하기
	//shared_ptr<P2cAnsBase> p2c_ans = process_message_(*c2p_req);

    boost::shared_ptr<presence::SKSK> entry_func = presence::get_backend().get_entry_point(proto_req.svcid());
     
        MSG_LOG() << "[" << boost::this_thread::get_id() 
                  << "]handle_message with op=" 
	          << proto_req.command() << "|" << proto_req.gameid() << std::endl;

	boost::promise<int> retval;
	boost::unique_future<int> fi(retval.get_future());

    presence::SpGameService service = presence::get_backend().get_service(proto_req.svcid());

    // sk68: TODO: check service != NULL

	entry_func->dispatcher_.post(
          boost::bind(entry_func->handler_, (void *)&proto_req, (void *)proto_ans, service, &retval)
	);

	fi.wait();
	assert(fi.is_ready());
	assert(fi.has_value());
	assert(!fi.has_exception());
	assert(fi.get_state()==boost::future_state::ready);

        MSG_LOG() << "[" << boost::this_thread::get_id() 
                  << "]handle_message got result for op=" 
	          << proto_req.command() << "|" << proto_req.gameid() << "(" 
                  << proto_ans->info() << ")" << std::endl;

	return true;
}


#ifdef SK68
// 로긴 요청 메시지 처리 및 응답 메시지 생성
shared_ptr<P2cLoginAns> process_message_(const C2pLloginReq& c2p_req)
{
	shared_ptr<P2cLoginAns> p2c_ans(new P2cLoginAns);

	p2c_ans->serviceid = c2p_req.serviceid;
	p2c_ans->gid = c2p_req.gid;

	tie(p2c_ans->result, p2c_ans->status) = the_world.login(c2p_req.serviceid, c2p_req.gid);

	return p2c_ans;
}

shared_ptr<P2cLogoutAns> process_message_(const C2pLogoutReq& c2p_req)
{
	shared_ptr<P2cLogoutAns> p2c_ans(new P2cLogoutAns);
	p2c_ans->serviceid = c2p_req.serviceid;
	p2c_ans->gid = c2p_req.gid;
	
	tie(p2c_ans->result, p2c_ans->status) = the_world.logout(c2p_req.serviceid, c2p_req.gid);

	return p2c_ans;
}


shared_ptr<P2cCategoryInfoAns> process_message_ (const C2pCategoryInfoReq& c2p_req)
{
	shared_ptr<P2cCategoryInfoAns> p2c_ans(new P2cCategoryInfoAns);
	p2c_ans->serviceid = c2p_req.serviceid;
	p2c_ans->gid = c2p_req.gid;

	boost::tie(p2c_ans->result, p2c_ans->CategoryInfo)
			=  the_world.current_usernum_per_category(c2p_req.serviceid);

	return p2c_ans;			
}

shared_ptr<P2cRoomAutoJoinAns> process_message_(const C2pRoomAutoJoinReq& c2p_req)
{
	shared_ptr<P2cRoomAutoJoinAns> p2c_ans(new P2cRoomAutoJoinAns);
	p2c_ans->serviceid = c2p_req.serviceid;
	p2c_ans->gid = c2p_req.gid;

	tie(p2c_ans->result, p2c_ans->status, p2c_ans->room_id, p2c_ans->ip, p2c_ans->port)
			= the_world.room_auto_join(c2p_req.serviceid, c2p_req.gid, c2p_req.categoryid);
	
	return p2c_ans;
}

shared_ptr<P2cRoomLeaveAns> process_message_ (const C2pRoomLeaveReq& c2p_req)
{
	shared_ptr<P2cRoomLeaveAns>  p2c_ans(new P2cRoomLeaveAns);
	p2c_ans->serviceid = c2p_req.serviceid;
	p2c_ans->gid = c2p_req.gid;

	boost::tie(p2c_ans->result, p2c_ans->status)
		= the_world.room_leave(c2p_req.serviceid, c2p_req.gid);

	return p2c_ans;
}
#endif // SK68

void set_err_result_(GameUserID gid, PAnsProtocol* proto_ans)
{
	proto_ans->set_seqid(-1);
	proto_ans->set_gameid(int(gid));
	proto_ans->set_svcid(int(kInvalidSvcId));
	proto_ans->set_category(int(kInvalidCategoryId));
	proto_ans->set_result(false);
	proto_ans->set_status(kUnknownState);
	proto_ans->set_detached(false);
}

void handle_error_(
		GameUserID gid, 
		SpConnection& con,
		const boost::system::error_code& e)
{
	if (boost::asio::error::eof != e)
	{
		MSG_LOG() << "request handler error. " << "gid : " << gid << std::endl;
		MSG_LOG() << e.message();

		//PAnsProtocol proto_ans;
		//set_err_result_(gid, &proto_ans);

		//Connection::SpBuffer packet = the_connection_manager.get_buffer(proto_ans.ByteSize());

		//bool is_ok = proto_util::serialize(proto_ans, packet.get());

		//if (is_ok == true)
		//	the_connection_manager.send(con, packet);
	}

	the_connection_manager.stop(con);

	return;
}

} // namespace detail
} // namespace ug_request_handler
}// namespace presence
