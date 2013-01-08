//
// UgRequestHandler.hpp
// ~~~~~~~~~~~~~~
////
// 최초 작성 : 2012.07.30. kts123@neowiz.com
// ~~~~~~~~~~
//
#ifndef PRESENCE_UG_REQUEST_HANDLER_HPP
#define PRESENCE_UG_REQUEST_HANDLER_HPP

#include "boost/system/error_code.hpp"
#include "boost/asio.hpp"

#include "common_def.hpp"

namespace presence {
class Connection;

namespace ug_request_handler{	

// connectin 에서 호출할 메시지 핸들러
void handle_message(GameUserID gid,
					boost::shared_ptr<Connection>& con,
					const boost::system::error_code& e,
					const boost::asio::const_buffer& buffer);

} // namespace ug_request_handler
} // namespace presence 

#endif //PRESENCE_UG_REQUEST_HANDLER_HPP
