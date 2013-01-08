#include "stdafx.h"

vector<userid_t> c_uid; 

jCALLBACK(L2X_WORLD_LIST)
{
	std::vector<astring> &worlds = *(std::vector<astring>*)_pData;
	vector<nMech::uint8> pwd;
	g_Net->Send_X2L_USER_LOGIN(worlds[0].c_str(), "test1",pwd);

}
jCALLBACK_end(L2X_WORLD_LIST);


jCALLBACK_PARAM(L2X_USER_LOGIN_OK)
{
	g_Net->Send_X2L_CHANNEL_SELECT(Data.channel_name[0].c_str());
}
jCALLBACK_end(L2X_USER_LOGIN_OK);


jCALLBACK(L2X_CHANNEL_SELECT_RESULT)
{
	g_Net->Connect_Town();
}
jCALLBACK_end(L2X_CHANNEL_SELECT_RESULT);

jCALLBACK(T2X_USER_LOGIN_CHANNEL_OK)
{
	std::vector<nAQ::Use_Avatar> &avata = *(std::vector<nAQ::Use_Avatar>*)_pData;
	for(int i=0; i<avata.size(); ++i)
	{
		jw_printf(L"aid=%d , auid=%I64d : %s\n", i+1, avata[i].m_auid_i64.m_db_id ,  avata[i].m_nic_name_w32);	
	}

}
jCALLBACK_end(T2X_USER_LOGIN_CHANNEL_OK);

jCALLBACK(T2X_AVATAR_SELECT_OK)
{
	printf("T2X_AVATAR_SELECT_OK\n");
}
jCALLBACK_end(T2X_AVATAR_SELECT_OK);

jCALLBACK(T2X_AVATAR_SELECT_OK2)
{
	printf("T2X_AVATAR_SELECT_OK2\n");
}
jCALLBACK_end(T2X_AVATAR_SELECT_OK2);

jCALLBACK(T2X_CHANGE_TOWN_ZONE)
{
	nMech::aname32_t &town_zone=*(nMech::aname32_t*)_pData;

	printf("T2X_CHANGE_TOWN_ZONE [TOWN : %s]\n", town_zone);

}
jCALLBACK_end(T2X_CHANGE_TOWN_ZONE);

jCALLBACK(Data_T2X_jTownPlayerEnterance_LIST)
{
	Data_T2X_jTownPlayerEnterance_LIST &_Data =*(Data_T2X_jTownPlayerEnterance_LIST*)_pData;
	printf("[T2X_jTownPlayerEnterance_LIST]\n");
		for(int i=0; i<_Data.uid.size() ; ++i)
		{
			c_uid.push_back(_Data.uid[i]);
			printf("[%d] [uid:%I64d] [x:%d] [y:%d] [asid:%d] [dir:%d] [eMovement:%d]\n", 
				_Data.uid[i], _Data.x[i], _Data.y[i], _Data.asid[i], _Data.dir[i], _Data.eMovement[i]);
		}

}
jCALLBACK_end(Data_T2X_jTownPlayerEnterance_LIST);

jCALLBACK(T2X_jTownPlayerEnterance)
{
	Data_T2X_jTownPlayerEnterance &_Data =*(Data_T2X_jTownPlayerEnterance*)_pData;
	c_uid.push_back(_Data.uid);

	printf("[T2X_jTownPlayerEnterance]\n[uid:%I64d] [x:%d] [y:%d] [asid:%d] [dir:%d] [eMovement:%d]\n", _Data.uid, _Data.x, _Data.y, _Data.asid, _Data.dir, _Data.eMovement);

}
jCALLBACK_end(T2X_jTownPlayerEnterance);

jCALLBACK(T2X_AVATAR_CREATE_OK)
{
	Data_T2X_AVATAR_CREATE_OK &_Data =*(Data_T2X_AVATAR_CREATE_OK*)_pData;

	jw_printf(L"[T2X_AVATAR_CREATE_OK]\n [index :%d] [Name : %s ]\n", _Data.index, _Data.avt.m_nic_name_w32);

}
jCALLBACK_end(T2X_AVATAR_CREATE_OK);

jCALLBACK(T2X_AVATAR_DELETE_OK)
{
	avatarid_t &index = *(avatarid_t*)_pData;

	printf("[T2X_AVATAR_DELETE_OK]\n[DELETE index:%d]\n",index);

}
jCALLBACK_end(T2X_AVATAR_DELETE_OK);


jCALLBACK(T_ERROR)
{
	printf("T ERROR\n");
}
jCALLBACK_end(T_ERROR);



void Set_CallBack()
{
	jSET_CALLBACK(L2X_WORLD_LIST);
	jSET_CALLBACK(L2X_USER_LOGIN_OK);
	jSET_CALLBACK(L2X_CHANNEL_SELECT_RESULT);
	//jSET_CALLBACK(T_ERROR);
	jSET_CALLBACK(T2X_USER_LOGIN_CHANNEL_OK);
	jSET_CALLBACK(T2X_AVATAR_SELECT_OK);
	jSET_CALLBACK(T2X_AVATAR_SELECT_OK2);
	jSET_CALLBACK(T2X_CHANGE_TOWN_ZONE);
	jSET_CALLBACK(T2X_jTownPlayerEnterance);
	jSET_CALLBACK(T2X_AVATAR_CREATE_OK);
	jSET_CALLBACK(T2X_AVATAR_DELETE_OK);

}
void send_Msg()	
{
	g_Net->Send_X2T_SEND_TO_OTHER_USER(_T("move"),_T("232_234"),c_uid);
}

void select_avatar(avatarid_t index)	
{
	g_Net->Send_X2T_AVATAR_SELECT(index);
}

void delete_avatar(avatarid_t index )
{
	g_Net->Send_X2T_AVATAR_DELETE(index);
}

void enter_town()	
{
	g_Net->Send_X2T_PR_ENTER_TOWN();
}