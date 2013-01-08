#ifndef __BASEBALL_DB_SHOP_INTERFACE_H_7E1P40JL__
#define __BASEBALL_DB_SHOP_INTERFACE_H_7E1P40JL__

#include "baseball_db.h" 
#include "excel_baseball_table_db.pb.h" 

namespace baseball_db 
{

class ShopDbInterface 
{
public:
	virtual ~ShopDbInterface(){}

	/// @brief	게임 머니로 판매하는 아이템을 구매함
	///			구매 성공 시, 유저 테이블에서 게임 머니가 차감되고, 
	///			구매 요청한 아이템이 지급됨
	///
	/// @param result	구매 한 아이템 or 패키지, 잔여 머니 등의 결과 정보가 저장될 변수
	/// @param uid		구매 유저 아이디
	/// @param shop_sid	상품 아이디	
	/// @param etc_info	추가 입력 정보. 예> 등번호 아이템에서 설정된 등번호
	///
	/// @return	성공 - kSuccess
	///			실패 시, Error 번호
	virtual Error BuyGameMoneyItem(OUT BuyGameMoneyItem_result_info& result,
								   IN Tbl_User_id_t uid,
								   IN Sys_Shop_id_t shop_sid, 
								   IN cstr etc_info) = 0;
};
	
} /* baseball_db */

#endif /* end of include guard: __BASEBALL_DB_SHOP_INTERFACE_H_7E1P40JL__ */
