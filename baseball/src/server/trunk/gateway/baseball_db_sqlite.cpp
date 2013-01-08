#include "stdafx.h"

#include <string> 
#include "baseball_db_sqlite.h" 

namespace baseball_db
{

namespace sqlite_query 
{

//#--------------------------------------------------------------------------
// SELECT_##TABLE
//#--------------------------------------------------------------------------
#define select_query_string4234(TABLE,EXCEL_TABLE,SELECT_FIELD)\
	const char* SELECT_##TABLE()\
	{\
		return "SELECT * FROM " #TABLE " WHERE " #SELECT_FIELD " = \':" #SELECT_FIELD "\' AND is_deleted = 0";\
	} 

for_each_GameInfo_Excel_Table(select_query_string4234)


//#--------------------------------------------------------------------------
// UPDATE_##TABLE
//#--------------------------------------------------------------------------

#define gen_update_expr4234(eng_name, name, date_type, field_order, getter_type, setter_type, data_type_simple) \
	" " #eng_name "=\':" #eng_name "\',"

#define update_query_string4234(TABLE,EXCEL_TABLE,SELECT_FIELD)\
	const char* UPDATE_##TABLE()\
{\
	static std::string s_query;\
	if (!s_query.empty())\
		return s_query.c_str();\
	std::string set_expr = _jJOIN_3(for_each_nEXCEL_,EXCEL_TABLE,_STRUCT_FIELD_all_member)(gen_update_expr4234);\
	set_expr.erase(set_expr.size() - 1);\
	set_expr.replace(set_expr.find("db_id=\':db_id\',"), ::strlen("db_id=\':db_id\',"), "");\
	s_query = "UPDATE " #TABLE " SET ";\
	s_query += set_expr;\
	s_query += " WHERE db_id = \':db_id\'";\
	return s_query.c_str();\
}\



for_each_GameInfo_Excel_Table(update_query_string4234)



//#--------------------------------------------------------------------------
// INSERT_##TABLE
//#--------------------------------------------------------------------------

#define gen_insert_field4234(eng_name, name, date_type, field_order, getter_type, setter_type, data_type_simple)\
	" " #eng_name "," 
#define gen_insert_variable4234(eng_name, name, date_type, field_order, getter_type, setter_type, data_type_simple)\
	"\':" #eng_name "\'," 

#define insert_query_string4234(TABLE,EXCEL_TABLE,SELECT_FIELD)\
	const char* INSERT_##TABLE()\
	{\
		static std::string s_query;\
		if (!s_query.empty())\
			return s_query.c_str();\
		std::string fields		= _jJOIN_3(for_each_nEXCEL_,EXCEL_TABLE,_STRUCT_FIELD_all_member)(gen_insert_field4234);\
		std::string variables	= _jJOIN_3(for_each_nEXCEL_,EXCEL_TABLE,_STRUCT_FIELD_all_member)(gen_insert_variable4234);\
		fields.erase(fields.size() - 1);\
		variables.erase(variables.size() - 1);\
		s_query = "INSERT INTO " #TABLE "(";\
		s_query += fields;\
		s_query += ") VALUES(";\
		s_query += variables;\
		s_query += ")";\
		return s_query.c_str();\
	}\

#define insert_without_pk_query_string4234(TABLE,EXCEL_TABLE,SELECT_FIELD)\
	const char* INSERT_##TABLE##_WITHOUT_PK()\
	{\
		static std::string s_query;\
		if (!s_query.empty())\
			return s_query.c_str();\
		std::string query = INSERT_##TABLE();\
		query.replace(query.find("\':db_id\',"), ::strlen("\':db_id\',"), "");\
		query.replace(query.find("db_id,"), ::strlen("db_id,"), "");\
		s_query = query;\
		return s_query.c_str();\
	}\
 
for_each_GameInfo_Excel_Table(insert_query_string4234)
for_each_GameInfo_Excel_Table(insert_without_pk_query_string4234)
 
//#--------------------------------------------------------------------------
// DELETE_##TABLE
//#--------------------------------------------------------------------------
#define delete_query_string4234(TABLE,EXCEL_TABLE,SELECT_FIELD)\
	const char* DELETE_##TABLE()\
	{\
		return "UPDATE " #TABLE " SET is_deleted = 1 WHERE db_id =\':db_id\'";\
	}\

for_each_GameInfo_Excel_Table(delete_query_string4234)


} /* sqlite_query */

}
