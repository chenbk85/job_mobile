#ifndef __ROOM_LIST_H_JIYACY0W__
#define __ROOM_LIST_H_JIYACY0W__

#include <map> 
#include <boost/detail/lightweight_mutex.hpp> 

namespace baseball 
{

class RoomList
{
public:
	/// @brief 룹 추가. 동일 룸이 있는 경우 덮어씀
	void insert(room_id_t id, Room* room)
	{
		boost::detail::lightweight_mutex::scoped_lock lock(mutex_);
		room_map_[id] = room;
	}

	/// @brief 룸 삭제
	void erase(room_id_t id)
	{
		boost::detail::lightweight_mutex::scoped_lock lock(mutex_);
		room_map_.erase(id);
	}

	/// @brief 룸 검색. 존재하지 않으면 NULL
	Room* get_room(room_id_t id) const
	{
		boost::detail::lightweight_mutex::scoped_lock lock(mutex_);
		std::map<room_id_t, Room*>::const_iterator itr = room_map_.find(id);
		if (room_map_.end() == itr)
			return NULL;
		return itr->second;
	}

	/// @brief 룸 갯수 반환
	size_t count() const
	{
		boost::detail::lightweight_mutex::scoped_lock lock(mutex_);

		return room_map_.size();
	}

private:
	/// @brief 
	mutable boost::detail::lightweight_mutex	mutex_;

	/// @brief 방 목록
	std::map<room_id_t, Room*>			room_map_;
};
	
} /* baseball */

#endif /* end of include guard: __ROOM_LIST_H_JIYACY0W__ */
