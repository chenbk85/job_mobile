//
// game_service.hpp
// ~~~~~~~~~~~~~~
//
//
// 최초 작성 : 2012.08.18. kts123@neowiz.com
// ~~~~~~~~~~
//

#ifndef PRESENCE_GAME_SERVICE_HPP
#define PRESENCE_GAME_SERVICE_HPP

#include "common_def.hpp"
#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_comparison.hpp"

#include <boost/asio.hpp>
#include <boost/thread/future.hpp>
#include "config.hpp"

namespace presence {

// forward declaration
struct BackEndModule;

typedef RoomID RandomizedRoomID;
typedef boost::shared_ptr<std::string>	SpString;
typedef boost::tuple<UserCnt, SpString, Port> RoomInfo;

inline RandomizedRoomID randomize(RoomID roomid)  { return ((rand()%256) << 24) | roomid; };
inline RoomID true_roomid(RandomizedRoomID rand_roomid) { return rand_roomid & 0x00ffffff ;};

struct UserLocation
{	
	CategoryID				categoryid;			
	RandomizedRoomID		rand_roomid;
};
typedef boost::shared_ptr<UserLocation>	 SpUserLocation;

class Category
{
private:
	// 디버그 정보 id/name
	int id_;
	std::string name_;

	// 룸 테이블
	std::map<RandomizedRoomID, RoomInfo > rooms_;		

	// 정원이 꽉 차지 않은 룸들을 관리
	std::set< boost::tuple<UserCnt, RandomizedRoomID> > joinable_rooms_;


	// 룸 최대 정원값 : 현재는 서비스별로 유일한 값이나
	// 편의성 및 향후 확장성 등을 고려하여 카테고리에도 추가
	size_t	   max_user_per_room_;

	// 카테고리의 룸에 들어가 있는 유저 수 
	size_t		current_user_num_;

public:
	size_t current_user_num() {return current_user_num_;};

    std::string list_rooms();

    std::string name() const { return name_; };

	bool delete_user_in_room(const SpUserLocation& user);

	boost::tuple<RoomID, std::string, Port> insert_user_in_room_when_auto_join(SpUserLocation& user);

	// factory 함수를 friend 로 선언한다.
	friend boost::shared_ptr<Category> create_category(const CategoryInfo& categoryinfo, size_t  max_user_per_room);
};
typedef boost::shared_ptr<Category> SpCategory;

boost::shared_ptr<Category> create_category(const CategoryInfo& categoryinfo, size_t  max_user_per_room);

inline bool	is_in_valid_room(const UserLocation& user) {return (user.rand_roomid != kInvalidRoomId);}


//=================================================================
// Game Service 구현
//==================================================================
class GameService;
typedef boost::shared_ptr<GameService> SpGameService;

#ifndef OUT
#define IN
#define OUT
#endif
typedef void plugin_entry_point_func_ft(IN void * /*PReqProtocol*/, OUT void * /*PAnsProtocol*/, IN SpGameService, OUT boost::promise<int> *);
typedef boost::asio::detail::wrapped_handler<boost::asio::io_service&, plugin_entry_point_func_ft*> SKSK;

class GameService
{
private:
	// 디버그 정보 id, name
	ServiceID id_;
	std::string name_;

	// 룸당 최대 사용 인원
	size_t max_user_per_room_;

	// 카테고리 맵
	std::map<CategoryID, SpCategory> categories_;

	// 유저 테이블
	std::map<GameUserID, SpUserLocation> users_;

    // dependant modules
    std::map<ModuleInfo *, BackEndModule *> dep_modules_;

public:
	static SpGameService create_service(const ServiceInfo& serviceinfo, std::vector<BackEndModule *> * modules);

public:

	ServiceID id() const { return id_;}

    boost::shared_ptr<presence::SKSK> entry_point;

	bool Init(const ServiceInfo& serviceinfo, std::vector<BackEndModule *> * modules);

	//----------------------------------------------
	// login :	
	//		gid 에 해당하는 사용자의 로그인 요청 처리
	//		리턴 : <로그인 수행 여부, state>
	boost::tuple<bool, std::string> login(GameUserID gid);

	//----------------------------------------------
	// logout :
	//		gid 에 대응되는 유저의 logout 요청 처리
	//		리턴 : <로그아웃 수행 여부, state>	
	boost::tuple<bool, std::string> logout(GameUserID gid);


	//----------------------------------------------
	// room_auto_join :
	//		gid 에 해당하는 사용자를 categoryid 에 대응되는 카테고리에 있는 
	//		적당한(?) 방에 자동 입장시킴
	//		적당한 방 찾기의 현재 정책은  '사용자가 가장 많은 방을 찾기' 임
	//		리턴 : <자동 입장 성공 여부, state, 룸아이디, ip, port>
	boost::tuple<bool, std::string, RoomID, std::string, Port> 
		room_auto_join(GameUserID gid, CategoryID categoryid);

	//----------------------------------------------
	// room_leave :
	// 사용자를 방에서 제거
	boost::tuple<bool, std::string>
		room_leave(GameUserID gid);

	//----------------------------------------------
	// current_usernum_per_category :
	// 카테고리별 사용자 인원수를 알려줌	
	std::string current_usernum_per_category() const;

    std::string list_rooms(CategoryID cid) const;

private:	
	SpUserLocation find(GameUserID gid) const;
};

} // namespace presence

#endif // PRESENCE_GAME_SERVICE_HPP
