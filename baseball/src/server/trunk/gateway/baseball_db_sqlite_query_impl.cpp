#include "stdafx.h" 

#include "baseball_db_sqlite_query_impl.h" 

#include "baseball_db_sqlite.h" 
#include "excel_baseball_table_db.pb.h"

namespace
{

int select_callback(void* result, int argc, char** argv, char** col_name)
{
	baseball_db::SelectResult* query_result = static_cast<baseball_db::SelectResult*>(result);
	// assert(query_result->column_names.empty() || 
	//        query_result->column_names.size() == argc); 
	if (query_result->column_names.empty())
	{
		for (int i = 0; i < argc; ++i)
			query_result->column_names.push_back(col_name[i]);
	}

	query_result->rows.push_back(std::vector<std::string>());
	std::vector<std::string>& row = query_result->rows.back();
	for (int i = 0; i < argc; ++i)
		row.push_back(argv[i]);

	return SQLITE_OK;
}

int query_callback(void* result, int argc, char** argv, char** col_name)
{
	std::cerr << __FUNCTION__ << std::endl;
	std::cerr << argc << std::endl;
	for (int i = 0; i < argc; ++i)
		std::cerr << col_name[i] << ":" << argv[i] << std::endl;

	return SQLITE_OK;
}

}

namespace baseball_db
{

int SqliteQuery(sqlite3* db, const std::string& query, QueryResult* result)
{
	char* error_message = NULL;
	int ret = sqlite3_exec(db, query.c_str(), query_callback, result, &error_message);
	if (SQLITE_OK != ret)
	{
		sqlite3_free(error_message);
		return ret;
	}

	sqlite3_free(error_message);
	return SQLITE_OK;
}

int SqliteSelect(sqlite3* db, const std::string& query, SelectResult* result)
{
	char* error_message = NULL;
	int ret = sqlite3_exec(db, query.c_str(), select_callback, result, &error_message);
	if (SQLITE_OK != ret)
	{
		sqlite3_free(error_message);
		return ret;
	}

	sqlite3_free(error_message);
	return SQLITE_OK;
}

} /* baseball_db */
