#include "stdafx.h" 

#include <boost/lexical_cast.hpp> 
#include "baseball_db.h" 
#include "baseball_db_sqlite.h" 
#include "baseball_db_sqlite_query_impl.h" 


namespace nDB
{
#if 1

	//X( RET , TYPE, VALUE)
#	define for_each_nDB_FromString_type(X)\
		X(int64					,db_uid_type_ref		, boost::lexical_cast<int64>(v))\
		X(int64					,Tbl_Quest_id_t	, boost::lexical_cast<int64>(v))\
		X(int64					,Tbl_PitcherSkill_id_t	, boost::lexical_cast<int64>(v))\
		X(int64					,int64					, boost::lexical_cast<int64>(v))\
		X(int32					,int32					, boost::lexical_cast<int32>(v))\
		X(int16					,int16					, boost::lexical_cast<int64>(v))\
		X(int8					,int8					, boost::lexical_cast<int8>(v))\
		X(uint64				,uint64					, boost::lexical_cast<uint64>(v))\
		X(uint32				,uint32					, boost::lexical_cast<uint32>(v))\
		X(uint16				,uint16					, boost::lexical_cast<uint64>(v))\
		X(uint8					,uint8					, boost::lexical_cast<uint8>(v))\
		X(bool					,bool					, boost::lexical_cast<bool>(v))\
		X(acstr					,acstr					, v.c_str())\
		X(acstr					,SYSTEMTIME				, v.c_str())\

#define def_FromString24(RET , TYPE , VALUE) \
	RET FromString_##TYPE(const std::string& v) {return VALUE;}

	for_each_nDB_FromString_type(def_FromString24)

#define def_ToDBType24(RET , TYPE , VALUE) \
	template <typename T>\
	T ToDBType_##TYPE(T val) {return val;}

	for_each_nDB_FromString_type(def_ToDBType24)



#define def_FromString_excel_enum27(enum_tbl,help,root_ns,ns) \
	int32 FromString_##enum_tbl(const std::string& _v) {std::string v=_v;return FromString(v.c_str(),eEND_##enum_tbl) ;}\
	cstr  ToDBType_##enum_tbl(int eVal){return nMech::ToString((enum_tbl)eVal);}\


for_each_nEXCEL_excel_enum_ENUM(def_FromString_excel_enum27)

#else

template <typename T>
T FromString(const std::string& str, T)					{return boost::lexical_cast<T>(str);}

template <>
acstr FromString(const std::string& str, acstr)			{return str.c_str();}
template <>
acstr FromString(const std::string& str, SYSTEMTIME)	{return str.c_str();}

#endif


}//namespace nDB


#define declare_query_string4234(TABLE,EXCEL_TABLE,SELECT_FIELD)\
	const char* SELECT_##TABLE();\
	const char* INSERT_##TABLE();\
	const char* UPDATE_##TABLE();\
	const char* DELETE_##TABLE();

for_each_GameInfo_Excel_Table(declare_query_string4234);



namespace baseball_db 
{

SqliteDb::SqliteDb(const char* filename)
	: db_filename_(filename), db_(NULL), last_error_(0)
{ }

SqliteDb::~SqliteDb()
{ 
	Deinitialize();
}

Error SqliteDb::Initialize()
{
	int ret = sqlite3_open(db_filename_.c_str(), &db_);
	if (SQLITE_OK != ret)
	{
		SET_DB_ERROR(); 
		return kDbFail;
	}

	return kSuccess;
}

void SqliteDb::Deinitialize()
{
	if (NULL == db_)
		return ;

	int ret = sqlite3_close(db_);
	if (SQLITE_OK != ret)
		SET_DB_ERROR();
	else
		db_ = NULL;
}


int SqliteDb::GetLastError() const
{
	return last_error_;
}

const std::string& SqliteDb::GetLastErrorString() const
{
	return last_error_string_;
}

void SqliteDb::ResetLastError()
{
	last_error_ = 0;
	last_error_string_.clear();
}

Error SqliteDb::_SetError(const char* file, int line, const char* function)
{
	last_error_ = sqlite3_errcode(db_);;
	last_error_string_.assign(file);
	last_error_string_.append(":");
	last_error_string_.append(boost::lexical_cast<std::string>(line));
	last_error_string_.append(" ");
	last_error_string_.append(function);
	last_error_string_.append(" ");
	last_error_string_.append(sqlite3_errmsg(db_));
	return kDbFail;
}


// ----------------------------------------------------------
// Insert_##TABLE
// ----------------------------------------------------------
#define bind_field4234(eng_name, name, date_type, field_order, getter_type, setter_type, data_type_simple)\
	baseball_db::sqlite_query::Bind(query, ":" #eng_name , nDB::ToDBType_##setter_type(data.eng_name()));\

#define insert_function4234(TABLE,EXCEL_TABLE,SELECT_FIELD)\
namespace sqlite_query { cstr INSERT_##TABLE(); cstr INSERT_##TABLE##_WITHOUT_PK(); }\
Error SqliteDb::Insert_##TABLE(INOUT s_##TABLE& data)\
{\
	std::string query;\
	if (0 == data.db_id())\
	{\
	    data.set_db_id(nMOB::make_random());\
	}\
	query = baseball_db::sqlite_query::INSERT_##TABLE();\
	_jJOIN_3(for_each_nEXCEL_ ,EXCEL_TABLE ,_STRUCT_FIELD_all_member)(bind_field4234);\
	QueryResult query_result;\
	if (SQLITE_OK != baseball_db::SqliteQuery(db_, query, &query_result))\
	{\
		SET_DB_ERROR();\
		return kDbFail;\
	}\
	return kSuccess;\
}\

for_each_GameInfo_Excel_Table(insert_function4234);



// ----------------------------------------------------------
// Select_##TABLE
// ----------------------------------------------------------
#define parse_field4234(eng_name, name, data_type, field_order, getter_type, setter_type, data_type_simple)\
{	v.set_##eng_name( nDB::FromString_##setter_type(row[idx++]) ); }

#define select_function4234(TABLE,EXCEL_TABLE,SELECT_FIELD)\
namespace sqlite_query { cstr SELECT_##TABLE(); }\
Error SqliteDb::Select_##TABLE(Tbl_User_id_t uid, OUT std::vector<s_##TABLE>& data)\
{\
	std::string query(sqlite_query::SELECT_##TABLE());\
	baseball_db::sqlite_query::Bind(query, ":" #SELECT_FIELD, uid);\
	SelectResult select_result;\
	int ret = baseball_db::SqliteSelect(db_, query, &select_result);\
	if (SQLITE_OK != ret)\
	{\
		SET_DB_ERROR();\
		return kDbFail;\
	}\
	if (select_result.rows.empty())\
		return kNoData;\
	try\
	{\
		for (size_t i = 0; i < select_result.rows.size(); ++i)\
		{\
			std::vector<std::string>& row = select_result.rows[i];\
			data.push_back(s_##TABLE());\
			s_##TABLE& v = data.back();\
			int idx = 0; \
			_jJOIN_3(for_each_nEXCEL_,EXCEL_TABLE,_STRUCT_FIELD_all_member)(parse_field4234);\
		}\
	}\
	catch (boost::bad_lexical_cast& e)\
	{\
		SET_DB_ERROR();\
		return kFailResultParse;\
	}\
	return kSuccess;\
}

for_each_GameInfo_Excel_Table(select_function4234);

// ----------------------------------------------------------
// Update_##TABLE
// ----------------------------------------------------------
#define update_function4234(TABLE,EXCEL_TABLE,SELECT_FIELD)\
namespace sqlite_query { cstr UPDATE_##TABLE(); }\
Error SqliteDb::Update_##TABLE(const s_##TABLE& data)\
{\
	std::string query(baseball_db::sqlite_query::UPDATE_##TABLE());\
	_jJOIN_3(for_each_nEXCEL_ ,EXCEL_TABLE ,_STRUCT_FIELD_all_member)(bind_field4234);\
	QueryResult query_result;\
	if (SQLITE_OK != baseball_db::SqliteQuery(db_, query, &query_result))\
	{\
		SET_DB_ERROR();\
		return kDbFail;\
	}\
	return kSuccess;\
}

for_each_GameInfo_Excel_Table(update_function4234);

// ----------------------------------------------------------
// Delete_##TABLE
// ----------------------------------------------------------
#define delete_function4234(TABLE,EXCEL_TABLE,SELECT_FIELD)\
namespace sqlite_query { cstr DELETE_##TABLE(); }\
Error SqliteDb::Delete_##TABLE(IN EXCEL_TABLE##_id_t db_id)\
{\
	std::string query(baseball_db::sqlite_query::DELETE_##TABLE());\
	baseball_db::sqlite_query::Bind(query, ":db_id" , db_id);\
	QueryResult query_result;\
	if (SQLITE_OK != baseball_db::SqliteQuery(db_, query, &query_result))\
	{\
		SET_DB_ERROR();\
		return kDbFail;\
	}\
	return kSuccess;\
}\


for_each_GameInfo_Excel_Table(delete_function4234);


} /* baseball_db */
