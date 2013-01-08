//
// game_service.cpp
// ~~~~~~~~~~~~~~
//
//
// 최초 작성 : 2012.08.18. kts123@neowiz.com
// ~~~~~~~~~~
//
#include "stdafx.h"

#include "common_def.hpp"
#include "config.hpp"
#include "game_service.hpp"

#include "backend.hpp"

namespace presence {

using std::vector;
using std::map;
using std::string;
using std::endl;
using std::stringstream;

using boost::shared_ptr;

using boost::tuple;
using boost::make_tuple;
using boost::get;
using boost::tie;

bool GameService::Init(const ServiceInfo& serviceinfo, std::vector<BackEndModule *> * modules)
{
	id_   = serviceinfo.id;
	name_ = serviceinfo.name;
	max_user_per_room_ = serviceinfo.max_user_per_room;

	for (vector<CategoryInfo>::const_iterator iter = serviceinfo.categories.begin();
		iter != serviceinfo.categories.end();	 
		iter++)
	{
		const CategoryInfo& categoriinfo = *iter;
		SpCategory category =create_category(categoriinfo, max_user_per_room_);
		categories_[categoriinfo.id] = category;
	}

	for (vector<std::string>::const_iterator iter = serviceinfo.dep_modules.begin();
		iter != serviceinfo.dep_modules.end();	 
		iter++)
	{
        for (vector<BackEndModule *>::const_iterator iter1 = modules->begin();
		iter1 != modules->end();	 
		iter1++)
        {
            if ((*iter1)->id == *iter)
            {
                //sk68: TODO: get this from Configure class (already defined and used there)
                ModuleInfo mod_info;
                mod_info.name = *iter;
                mod_info.version = (*iter1)->module_version;
                dep_modules_[&mod_info] = *iter1;

                //sk68: if first module, then use this as service entry point
                if (iter == serviceinfo.dep_modules.begin())
                {
                    entry_point = (*iter1)->entry_point;
                    MSG_LOG() << "Set svc(" << *iter << ") entry_point as " << entry_point << std::endl;
                }
            }
        }
	}

	return true;
}

SpUserLocation GameService::find(GameUserID gid) const 
{
	SpUserLocation user_location;

	map<GameUserID, SpUserLocation>::const_iterator iter = users_.find(gid);
	if (iter != users_.end())
		return user_location = iter->second;
	// else user_location == nullptr 

	return user_location;
}

//----------------------------------------------
// login :
//		gid 에 해당하는 사용자의 로그인 요청 처리
//		리턴 : <로그인 수행 여부, state>
tuple<bool, string> GameService::login(GameUserID gid)
{
	// 1. 해당 사용자가 해당 서비스에 이미 로그인되어 있는지 알아본다.
	SpUserLocation user = find(gid);

	// 2. 기존에 없었던 경우에만 유저를 생성하여 유저 맵에 넣는다.
	bool accept_login = (user == NULL ? true : false);
	if (accept_login)
	{
		// 2-1. 엔트리를 만들어
		SpUserLocation user(new UserLocation);
		user->categoryid = kInvalidCategoryId;
		user->rand_roomid = kInvalidRoomId;

		// 2-2. 유저 관리 맵에 추가.
		users_[gid] = user;
	}
	else
	{
		// warning 로그 남기시오.
	}

	// 3. 유저가 있었냐 없었냐에 따라 리턴 값을 다르게 하여 리턴	
	return make_tuple(accept_login, accept_login ? kLobbyState : kUnknownState);
}

//----------------------------------------------
// logout :
//		gid 에 대응되는 유저의 logout 요청 처리
//		리턴 : <로그아웃 수행 여부, state>	
tuple<bool, string> GameService::logout(GameUserID gid)
{
	// 1. 해당 사용자가 해당 서비스에 이미 로그인되어 있는지 알아본다.
	SpUserLocation user = find(gid);
	bool is_already_login = (user != NULL ? true : false);

	// 2. 이미 로그인된 유저에 한해서
	if (is_already_login)
	{
		// 2-2. 룸에 들어가 있는 경우에는 해당 룸에서 사용자를 삭제한다.
		// remark: 정상적이라면 이미 room_leave 가  처리 되었기 때문에
		//	    룸에 아직도 들어가 있는 경우는 없을 것이다.
		//		따라서 Error 처리를 해서 운영시 탐지하도록 해야 한다.			
		if (is_in_valid_room(*user) == true)
		{
			bool is_deleted = categories_[user->categoryid]->delete_user_in_room(user);

			// remark: 어차피 예외 상황 처리였으므로 is_deleted 값은
			//		로그 찍는 곳에서만 사용하면 된다.
			if (is_deleted == false)
				MSG_LOG() << "no user deleted : [" << gid << endl;
		}

		// 2-3. 로그 아웃 처리 후에는 이후 어떤 작업도 일어나서는 안되므로,
		//		유저 관리 맵에서 해당 유저 삭제. 
		users_.erase(gid);
	}
	else
	{
		// error log 남기시오
	} 

	// 3. <이번에 지워 졌는지 여부, logout상태 "U"> 리턴.
	return make_tuple(is_already_login, kUnknownState);
}


//=================================================================
// Category factory
//==================================================================
SpCategory create_category(const CategoryInfo& categoryinfo, size_t  max_user_per_room)
{
	SpCategory category(new Category);

	category->id_   = categoryinfo.id;
	category->name_ = categoryinfo.name;

	vector<ServerInfo>::const_iterator iter;
	for (	iter = categoryinfo.game_servers.begin();
		iter != categoryinfo.game_servers.end();
		iter++)
	{
		const ServerInfo& serverinfo = *iter;

		SpString	ip_string(new string(serverinfo.ip));
		Port	port = serverinfo.port;
		UserCnt usercnt_zero = 0;
		RoomInfo roominfo = boost::make_tuple(usercnt_zero, ip_string, port);


		for (RoomID roomid = serverinfo.begin_roomid;
			roomid != serverinfo.end_roomid; 
			roomid++)
		{
			// load balance 를 위해 roomid 를 랜더마이즈 한다.
			RoomID rand_roomid = randomize(roomid); 

			category->joinable_rooms_.insert(make_tuple(usercnt_zero, rand_roomid));
            static unsigned int cnt;
            MSG_LOG() << "[" << cnt++ << "] added roomid=" 
                                 << rand_roomid << " to category->joinable_rooms_["
                                 << category->name_.c_str() << "]\n";
			category->rooms_[rand_roomid] = roominfo;
		}
	}

	category->max_user_per_room_ = max_user_per_room;
	category->current_user_num_  = 0;

	return category;
}

//=================================================================
// Category 구현
//==================================================================
//----------------------------------------------
// delete_user :

bool Category::delete_user_in_room(const SpUserLocation& user) 
{
	// 2. 몇 명짜리 방이었는지 알아낸다.	
	UserCnt& usercnt = get<0>(rooms_[user->rand_roomid]);	

	// 3. 룸 사용 현황을 업데이트한다.
	//  3-1. 기존 룸 사용 현황 노드를 삭제한다. (max_user 가 아닌 경우만)
	if (usercnt != max_user_per_room_)
		joinable_rooms_.erase(make_tuple(usercnt, user->rand_roomid));
	//  3-2.룸 사용 현황 노드를 새로 추가 한다.	
	joinable_rooms_.insert(make_tuple(usercnt - 1, user->rand_roomid));

	// 4. 카테고리 인원 수, 방 인원수를 감소시킨다.
	current_user_num_--;
	usercnt--;

	// 5. User 정보를 갱신한다.
	user->categoryid  = kInvalidCategoryId;
	user->rand_roomid = kInvalidRoomId;

	return true;
}

tuple<RoomID, string, Port>
	Category::insert_user_in_room_when_auto_join(SpUserLocation& user)
{
	// 2. 방이 모두 고갈된 경우를 처리한다.
	if (joinable_rooms_.size() == 0)
	{
		// 로그 남기시오.
		return make_tuple(kInvalidRoomId, "invalid_ip", kInvalidPort);
	}

	// 3. join 할 room 정보를 얻어온다.
	UserCnt usercnt;
	RandomizedRoomID rand_roomid;
	tie(usercnt, rand_roomid) = *joinable_rooms_.rbegin();

	// 4. 룸 사용 현황을 업데이트한다.
	//  4-1. 기존 룸 사용 현황 노드를 삭제한다. 
	joinable_rooms_.erase(*joinable_rooms_.rbegin());
	//  4-2.룸 사용 현황 노드를 새로 추가 한다.(꽉 차지 않은  경우만)
	usercnt++;
	if (usercnt != max_user_per_room_)
		joinable_rooms_.insert(make_tuple(usercnt, rand_roomid));

	// 5. 카테고리 인원 수, 방 인원수를 증가시킨다.
	current_user_num_++;

	RoomInfo& roominfo = rooms_[rand_roomid];
	get<0>(roominfo)++;

	// 6. 유저 정보를 업데이트한다.
	user->categoryid  = id_;
	user->rand_roomid = rand_roomid;

    MSG_LOG() << "adding user to category=" << id_
        << " rand_roomid=" << rand_roomid << " roomid=" 
        << true_roomid(rand_roomid) << std::endl;
	return boost::make_tuple(true_roomid(rand_roomid), *get<1>(roominfo), get<2>(roominfo));
}

//sk68: TODO: some paging parameters maybe?
string Category::list_rooms()
{
    std::stringstream ss;
    std::map<RandomizedRoomID, RoomInfo >::const_iterator iter;
    for (iter = rooms_.begin(); iter != rooms_.end(); ++iter)
    {
        //typedef boost::tuple<UserCnt, SpString, Port> RoomInfo;
        RoomInfo roominfo = iter->second;
        ss << "[num_users="
            << get<0>(roominfo) // UserCnt
            << ",server_ip="
            << *get<1>(roominfo) // SpString
            << "]\n";
    }
    return ss.str();
}

//=================================================================
// Game Service 구현
//==================================================================

SpGameService GameService::create_service(const ServiceInfo& serviceinfo, std::vector<BackEndModule *> * modules)
{	
	SpGameService service(new  GameService);

	if (service->Init(serviceinfo, modules) == false)
		service.reset();

	return service;
}

//----------------------------------------------
tuple<bool, string, RoomID, string, Port> // <result, state, RoomID, ip, port>
	GameService::room_auto_join(GameUserID gid, CategoryID categoryid)
{
	// 1. 해당 사용자가 해당 서비스에 이미 로그인되어 있는지 알아본다.
	//    로그인 자체가 안되어 있는 경우 false 리턴
	SpUserLocation user = find(gid);	
	if (user == NULL)
	{
		// 로그 남기시오.
		return make_tuple(false, kUnknownState, kInvalidRoomId, "invalid_ip", kInvalidPort);
	}

	// 2. 카테고리를 얻어온다.
	//    잘못된 카테고리로 입장 신청한 경우 false 리턴
	map<CategoryID, SpCategory>::iterator iter = categories_.find(categoryid);
	if (iter == categories_.end())
	{
		// 로그 남기시오.
		return make_tuple(false, kLobbyState, kInvalidRoomId, "invalid_ip", kInvalidPort);
	}

	// 3. 해당 카테고리에 룸에 사용자 추가
	RoomID roomid; string ip; Port port;
	boost::tie(roomid, ip, port) = iter->second->insert_user_in_room_when_auto_join(user);

	// 4. 결과 리턴
	bool is_inserted = (roomid != kInvalidRoomId) ? true : false;
	string userstate = is_inserted ? kGameRoomState : kLobbyState;

	return boost::make_tuple(is_inserted, userstate, roomid, ip, port);
}


//----------------------------------------------
tuple<bool, string>
	GameService::room_leave(GameUserID gid)
{
	// 1. 해당 사용자가 해당 서비스에 이미 로그인되어 있는지 알아본다.
	SpUserLocation user = find(gid);
	bool is_already_login = (user != NULL ? true : false);


	// 2. 로그인 자체가 안되어 있거나, 방에 속에 있지 않은 경우 false 리턴	
	if ((is_already_login && is_in_valid_room(*user)) == false)
	if ((is_already_login && is_in_valid_room(*user)) == false)
		return make_tuple(false, is_already_login ? kLobbyState : kUnknownState);

	// 3.룸에서 사용자를 삭제
	bool is_deleted = categories_[user->categoryid]->delete_user_in_room(user);

	return make_tuple(is_deleted, kLobbyState);
}

//----------------------------------------------
string GameService::current_usernum_per_category() const 
{
	stringstream ss;
	map<CategoryID, SpCategory>::const_iterator iter;
	for (iter = categories_.begin();
		iter != categories_.end();
		iter++)
		ss << iter->second->current_user_num() << ",";

	string info = ss.str();
	info[info.size()-1] = 0;		

	return info;
}

string GameService::list_rooms(CategoryID cid) const 
{
    std::stringstream ss;
    map<CategoryID, SpCategory>::const_iterator iter;
    for (iter = categories_.begin(); iter != categories_.end(); iter++)
    {
        SpCategory cat = iter->second;
        ss << "[" << cat->name() << "]" << cat->list_rooms();
    }
    return ss.str();
}

} //namespace presence
