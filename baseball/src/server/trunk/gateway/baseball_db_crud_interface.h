#ifndef __BASEBALL_DB_CRUD_WRAPPER_H_IWDY1DMO__
#define __BASEBALL_DB_CRUD_WRAPPER_H_IWDY1DMO__

#include "baseball_db.h" 

#include "excel_baseball_table_db.pb.h"

namespace baseball_db
{
//CRUD Create Read Update Delete
class CRUDWrapperInterface
{
public:
	virtual ~CRUDWrapperInterface(){}
#define CRUDWrapperInterface_interface4234(TABLE,EXCEL_TABLE,SELECT_FIELD)\
	virtual Error Insert_##TABLE(INOUT s_##TABLE& data ) INTERFACE4234_TAG;\
	virtual Error Select_##TABLE(IN Tbl_User_id_t uid, OUT std::vector<s_##TABLE>& data) INTERFACE4234_TAG;\
	virtual Error Update_##TABLE(IN const s_##TABLE& data) INTERFACE4234_TAG;\
	virtual Error Delete_##TABLE(IN EXCEL_TABLE##_id_t db_id) INTERFACE4234_TAG;\

#undef INTERFACE4234_TAG
#define INTERFACE4234_TAG = 0;
	for_each_GameInfo_Excel_Table(CRUDWrapperInterface_interface4234);
};

} /* baseball_db_crud_wrapper */

#endif /* end of include guard: __BASEBALL_DB_CRUD_WRAPPER_H_IWDY1DMO__ */
