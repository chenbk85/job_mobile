/* file : common_typedef.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-05-21 18:45:52
comp.: www.neowiz.com
title : 
desc : 

�׽�Ʈ Ŭ�� �� ������ �����ϴ� typedef����.


*/

#ifndef __common_typedef_header__
#define __common_typedef_header__
#pragma once

typedef int32 room_id_t;
typedef int32 score_t; //����
typedef int32 base_runner_state_t;//���� ��� ���� , bit 0 : 1��  , bit2 : 3��
// TODO : ItemListType �� equal_db_id_to �Լ��� ������ ������ ��ġ ���� �ʿ���
//typedef ::google::protobuf::RepeatedPtrField< ::s_tbl_item > ItemListType;
typedef int64 exp_t;//����ġ
typedef int8 level_t;//���� ����ġ.
typedef int8 round_t;//������ ���� ī��Ʈ.


#endif // __common_typedef_header__
