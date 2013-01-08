
#ifndef __AqClient_Bridge_Interface_h__
#define __AqClient_Bridge_Interface_h__


typedef void jNet_CallBack_t(void*);


struct Data_L2X_USER_LOGIN_OK
{
	std::vector<astring> channel_name;
	std::vector<nMech::uint8> buzy_level;
};

struct Data_T2X_AVATAR_SELECT_OK {
	avatarid_t index;
	std::vector<jAvatarItem> item;
	std::vector<jAvatarSkill> skill;
};

struct Data_T2X_AVATAR_SELECT_OK2 {
	avatarid_t index;
};

struct Data_T2X_AVATAR_CREATE_OK {
	avatarid_t index;
	nAQ::Use_Avatar avt;
};

struct Data_T2X_jTownPlayerEnterance {
	userid_t uid;
	nMech::uint16 x;
	nMech::uint16 y;
	avatar_sid_t asid;
	nMech::uint8 dir;
	nMech::uint8 eMovement;
};

struct Data_T2X_jTownPlayerEnterance_LIST{
	std::vector<userid_t> uid;
	std::vector<nMech::uint16> x;
	std::vector<nMech::uint16> y;
	std::vector<avatar_sid_t> asid;
	std::vector<nMech::uint8> dir;
	std::vector<nMech::uint8> eMovement;
};

struct jINetClient
{
	virtual void Set_CallBack(char* szName, jNet_CallBack_t* pFunc)=0;
	virtual bool console_parsor(TCHAR* sz)=0;
	
	// ·ÎÁ÷
	virtual void Send_X2L_USER_LOGIN(const char* world,const char* id, vector<nMech::uint8> &pwd)=0;
	virtual void Send_X2L_CHANNEL_SELECT(const char* channel_name)=0;
	virtual void Send_X2T_AVATAR_SELECT(avatarid_t avatarid)=0;
	virtual void Send_X2T_PR_ENTER_TOWN()=0;
	virtual void Send_X2T_SEND_TO_OTHER_USER(nMech::tname32_t cmd, nMech::tname32_t param, vector<userid_t> uid)=0;
	virtual void Send_X2T_AVATAR_CREATE(avatar_sid_t asid, nMech::wname32_t name)=0;
	virtual void Send_X2T_AVATAR_DELETE(avatarid_t index)=0;

	virtual void Connect_Town()=0;

};

extern jINetClient* g_Net;

#endif //asdlasdfqwerqwerqwerwqe