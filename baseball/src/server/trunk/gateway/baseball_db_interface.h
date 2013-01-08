#ifndef __BASEBALL_DB_INTERFACE_H_CZ5FMGVQ__
#define __BASEBALL_DB_INTERFACE_H_CZ5FMGVQ__

#include "baseball_db.h" 
#include "baseball_db_crud_interface.h" 
#include "baseball_db_shop_interface.h" 

namespace baseball_db 
{

class DbInterface : 
	public CRUDWrapperInterface,
	public ShopDbInterface
{
public:
	virtual ~DbInterface() {}
	
	virtual Error Initialize() = 0;
	
	virtual void Deinitialize() = 0;
	
	/// @brief  마지막 발생한 에러 반환
	virtual int GetLastError() const = 0;
	
	/// @brief  마지막 발생한 에러 문자열 반환
	virtual const std::string& GetLastErrorString() const = 0;
	
	/// @brief  현재 설정된 에러 문자열 리셋
	virtual void ResetLastError() = 0;
};
	
} /* baseball_db */

#endif /* end of include guard: __BASEBALL_DB_INTERFACE_H_CZ5FMGVQ__ */
