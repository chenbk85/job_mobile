#ifndef __BASEBALL_DB_SQLITE_QUERY_IMPL_H_WCOFKQ1X__
#define __BASEBALL_DB_SQLITE_QUERY_IMPL_H_WCOFKQ1X__

#include <stdint.h> 
#include <sqlite3.h> 
#include <string> 

#include "baseball_db.h" 

struct QueryResult;
struct SelectResult;

namespace baseball_db
{

int SqliteQuery(sqlite3* db, const std::string& query, QueryResult* result);

int SqliteSelect(sqlite3* db, const std::string& query, SelectResult* result);
  
} /* nDB */

#endif /* end of include guard: __BASEBALL_DB_SQLITE_QUERY_IMPL_H_WCOFKQ1X__ */
