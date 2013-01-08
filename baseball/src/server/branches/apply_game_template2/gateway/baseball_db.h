#ifndef __BASEBALL_DB_H_IMWRD3AD__
#define __BASEBALL_DB_H_IMWRD3AD__

#include <vector> 
#include <string> 
#include <boost/date_time/posix_time/posix_time.hpp> 

using namespace nMech;
#include "excel/db_uid_type.h" 
#include "excel/code/table_type.h" 

namespace baseball_db
{

/// @brief DB 작업 요청에 따른 에러 
#define for_each_Error(X)\
	X(kSuccess					,"성공")\
	X(kUnknown					,"알수 없는 에러. 아래에 나열된 목록에 포함되지 않는 경우 모두 Unknown")\
	X(kNoData					,"요청된 데이터 없음")\
	X(kDbFail					,"DB 쿼리 오류")\
	X(kFailResultParse			,"결과 파싱 오류")\
	X(kShopNoProduct			,"잘못된 상품 정보")\
	X(kShopInvalidProduct		,"잘못된 상품")\
	X(kShopInvalidItem			,"잘못된 아이템")\
	X(kShopInvalidPackage		,"잘못된 패키지")\
	X(kShopWrongPayment			,"잘못된 잘못된 지불 수단으로 요청되었음")\
	X(kShopNotEnoughMoney		,"게임머니가 부족함")\

jDEFINE_ENUM_CODE2(Error);

struct BuyGameMoneyItem_result_info
{
	std::vector<s_tbl_item> item;
	std::vector<s_tbl_package> package;
	std::vector<s_tbl_pitcherskill> skill;
	game_money_t game_money;			///< 잔여 게임머니.
};

/// @brief Select 쿼리에 대한 결과
struct SelectResult 
{
	std::vector<std::string> column_names;
	std::vector<std::vector<std::string> > rows;
};


/// @brief Select 외의 쿼리에 대한 결과
struct QueryResult 
{
	QueryResult() : result(0) {}

	size_t result;
};


/// @brief 등급 enum 값에 해당하는 문자열를 반환함
//         eIGT_S => "S", eIGT_A => "A"
/// @param grade 아이템 등급
/// @return 등급 문자열 
const char* to_grade_string(EItemGradeType grade);


/// @brief 초기 업그레이드 레벨 enum 값에 해당하는 문자열를 반환함
//         eIGT_S => "SE", eIGT_A => "SA"
/// @param grade 아이템 등급
/// @return 등급 문자열
const char* to_upgrade_base_lev_string(EItemGradeType grade);


/// @brief	boost::posix_time::ptime 을 DB에 저장될 포멧에 맞는 문자열로 변환
///
/// @param time	변환할 시간
///
/// @return 성공 : 변환된 시간 문자열. 실패 : 빈 문자열
std::string time_to_string(const boost::posix_time::ptime& time);


/// @brief	DB에 저장된 시간 문자열을 boost::posix_time::ptime으로 변환
///
/// @param time 시간 문자열
///
/// @return 성공 : time 객체. 
///			실패 : return ptime(not_a_date_time)
///				   is_not_a_date_time() 함수로 체크
boost::posix_time::ptime timetime_to_string(const std::string& time);


} /* nDB */

#endif /* end of include guard: __BASEBALL_DB_H_IMWRD3AD__ */
