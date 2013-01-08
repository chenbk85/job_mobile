#ifndef __BASEBALL_DB_SQLITE_H_PUG5GRBO__
#define __BASEBALL_DB_SQLITE_H_PUG5GRBO__

#include <string> 
#include <boost/lexical_cast.hpp> 
#include <sqlite3.h> 
#include "baseball_db_interface.h" 

/// @remakr 쿼리 생성 매르로 로직으로 인해 각 테이블은 반드시 db_id 필드를 primary key 필드로 가져야 하며,
//			db_id 필드는 테이블의 첫번째 필드로 명시되어야 한다.
//			(정확히는 마지막 필드만 아니면 되지만 첫번째 필드로 통일하는 것이 좋을 것 같음)
namespace baseball_db
{

#define SET_DB_ERROR() \
	_SetError(__FILE__, __LINE__, __FUNCTION__)

namespace sqlite_query
{

template <typename T>
inline void Bind(std::string& query, const char* variable, T value)
{
	size_t pos = 0;
	while (true)
	{
		std::string tmp_variable("\'"); 
		tmp_variable += variable; 
		tmp_variable += "\'";
		std::string tmp_value("\'"); 
		tmp_value += boost::lexical_cast<std::string>(value);
		tmp_value += "\'";

		pos = query.find(tmp_variable, pos);
		if (pos == std::string::npos)
			break;

		query.replace(pos, tmp_variable.size(), tmp_value);
	};
}

} /* sqlite_queries */

struct GiftValue 
{
	GiftValue(EGiftType type_ = eEGT_NULL, int32_t value_ = 0)
		: type(type_), value(value_)
	{ }
	EGiftType type;
	int32_t value;
};

class SqliteDb : public DbInterface
{
public:
	SqliteDb (const char* filename);

	virtual ~SqliteDb ();

	virtual Error Initialize();

	virtual void Deinitialize();

#undef INTERFACE4234_TAG
#define INTERFACE4234_TAG 
	for_each_GameInfo_Excel_Table(CRUDWrapperInterface_interface4234);

	virtual int GetLastError() const;

	virtual const std::string& GetLastErrorString() const;

	virtual void ResetLastError();

	virtual Error BuyGameMoneyItem(OUT BuyGameMoneyItem_result_info& result,
								   IN Tbl_User_id_t uid,
								   IN Sys_Shop_id_t shop_sid, 
								   IN cstr etc_info);

private:

	Error _SetError(const char* file, int line, const char* function);

	// _SIMPLE_MODE
	/*
	bool _FillItemInfo(Tbl_User_id_t uid, Sys__ItemBase_id_t item_id, EItemCategory eItemCategory, 
						const std::string& etc_info, s_tbl_item* item) const;
	bool _FillPackageInfo(Tbl_User_id_t uid, Sys_Package_id_t package_sid, 
						const std::string& etc_info, s_tbl_package* package) const;
	*/
	Error _GiveGift(Tbl_User_id_t uid, GiftValue gift);

	std::string db_filename_;
	sqlite3*    db_;
	int         last_error_;
	std::string last_error_string_;
};

} /* baseball_db */

#endif /* end of include guard: __BASEBALL_DB_SQLITE_H_PUG5GRBO__ */
