#ifndef __NWM_BASEBALL_GATEWAY_DB_H__
#define __NWM_BASEBALL_GATEWAY_DB_H__

#include "gateway/database.hpp"
#include <boost/scoped_ptr.hpp> 
class Database: 
    public MSG::Database
{
public:
                        Database(MSG::Gateway& gateway);

    virtual             ~Database();

    virtual void        initialize(const std::string& config);

    virtual const std::string&
                        get_gameuserinfo();

    virtual bool        load_user_info(int32_t game_id,
                                       const MemberInfo& member_info);

    int32_t             get_service_id();

    virtual bool        get_channel(UAnsChannel& channels,
                                    const std::string& channel_info);

    virtual bool        get_item_info(UAnsStore& store);

    bool                get_notice(UAnsNotice& notice);

    // 클라이언트에서 오는 쿼리를 수행해줌
    // false 리턴하면 게이트웨이가 터지도록 되어있음
    virtual bool        query_from_client(const ReqDB& query,
                                          AnsDB& result);

    virtual bool        query_from_game(const ReqDB& query,
                                        AnsDB& result);

    virtual void        update_game_info(int idx,
                                         const std::string& info);


// 	template <class _Predicate> 
// 	void run_sql(_Predicate &__pred)
// 	{
// 		boost::scoped_ptr<baseball_db::DbInterface> db(new baseball_db::SqliteDb(s_filename));
// 		jvRETURN_ret(false, baseball_db::kSuccess == db->Initialize() , "%s" , db->GetLastErrorString());
// 		bool is =false;
// 		try
// 		{
// 			is = __pred(&g_jUser);
// 		}
// 		catch (...)
// 		{
// 			jERROR("%s" , __pred.get_name());
// 		}
// 		db->Deinitialize();
// 		return is;
// 	}
};

#endif

