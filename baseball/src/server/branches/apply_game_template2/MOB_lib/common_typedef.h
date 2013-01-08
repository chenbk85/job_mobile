/* file : common_typedef.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-05-21 18:45:52
comp.: www.neowiz.com
title : 
desc : 

테스트 클라 와 서버와 공유하는 typedef구문.


*/

#ifndef __common_typedef_header__
#define __common_typedef_header__
#pragma once

typedef int32 room_id_t;
typedef int32 score_t; //점수
typedef int32 base_runner_state_t;//주자 출루 상태 , bit 0 : 1루  , bit2 : 3루
// TODO : ItemListType 및 equal_db_id_to 함수는 적당한 곳으로 위치 변경 필요함
//typedef ::google::protobuf::RepeatedPtrField< ::s_tbl_item > ItemListType;
typedef int64 exp_t;//경험치
typedef int8 level_t;//선수 경험치.
typedef int8 round_t;//게임의 라운드 카운트.


#endif // __common_typedef_header__
