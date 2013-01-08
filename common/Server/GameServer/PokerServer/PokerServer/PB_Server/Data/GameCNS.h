#pragma once

#ifdef CNSRENEWAL_WORK

const LONG	MAX_POINTMONEYKIND = 3;		//점당 머니 종류
const LONG	_gPointMoney[CNS_CHANNEL_MAX][MAX_POINTMONEYKIND] = {
	{   1000,		1*MAN,		10*MAN },		//자유(1천원,1만원,10만원)
	{    500,		  500,		   500 },		//입문(500원)
	{   1000,		 1000,		  1000 },		//입문~초보(1천원)
	{   3000,		 5000,		  3000 },		//하수~중수(3천원,5천원)
	{   3000,		 5000,		  3000 },		//- 미사용 - 
	{  1*MAN,		1*MAN,		 1*MAN },		//중수~고수(1만원)
	{  3*MAN,		5*MAN,		 3*MAN },		//중수~선수(3만원,5만원)
	{  3*MAN,		5*MAN,		 3*MAN },		//- 미사용 - 
	{ 10*MAN,	   30*MAN,		50*MAN },		//선수~제왕(10만원,30만원,50만원)
	{ 10*MAN,	   30*MAN,		50*MAN },		//- 미사용 - 
	{100*MAN,	  300*MAN,	   500*MAN },		//영웅~제왕(100만원,300만원,500만원)
};

const LONG	MAX_ENTERUSERLEVELKIND = 2;		//채널당 입장 가능한 등급 종류
const LONG	gEnterUserLevel[CNS_CHANNEL_MAX][MAX_ENTERUSERLEVELKIND] = {
	{	USER_LEVEL_IPMUN,	USER_LEVEL_EMPEROR	}, //자유(1천원,1만원,10만원)
	{	USER_LEVEL_IPMUN,	USER_LEVEL_IPMUN	}, //입문(500원)
	{	USER_LEVEL_IPMUN,	USER_LEVEL_CHOBO	}, //입문~초보(1천원)
	{	USER_LEVEL_CHOBO,	USER_LEVEL_JUNGSU	}, //하수~중수(3천원,5천원)
	{	USER_LEVEL_NONE,	USER_LEVEL_NONE		}, //- 미사용 - 
	{	USER_LEVEL_JUNGSU,	USER_LEVEL_GOSU		}, //중수~고수(1만원)
	{	USER_LEVEL_JUNGSU,	USER_LEVEL_SUNSU	}, //중수~선수(3만원,5만원)
	{	USER_LEVEL_NONE,	USER_LEVEL_NONE		}, //- 미사용 - 
	{	USER_LEVEL_SUNSU,	USER_LEVEL_EMPEROR	}, //선수~제왕(10만원,30만원,50만원)
	{	USER_LEVEL_NONE,	USER_LEVEL_NONE		}, //- 미사용 - 
	{	USER_LEVEL_HERO,	USER_LEVEL_EMPEROR	}, //영웅~제왕(100만원,300만원,500만원)
};

//입장 가능 금액.
const int MAX_LIMITMONEYKIND = 6; // 최소입장머니 종류. 함수에서 처리함.

//방에 있을 수 있는 최소금액.
const LONGLONG gStayMoney[CNS_CHANNEL_MAX][MAX_POINTMONEYKIND] = {
	{    7000,		7*MAN,		70*MAN },		//자유(1천원,1만원,10만원)
	{    3500,		 3500,		  3500 },		//입문(500원)
	{    7000,		 7000,		  7000 },		//입문~초보(1천원)
	{  15*MAN,	   15*MAN,		15*MAN },		//하수~중수(3천원,5천원)
	{  15*MAN,	   15*MAN,		15*MAN },		//- 미사용 - 
	{  50*MAN,	   50*MAN,		50*MAN },		//중수~고수(1만원)
	{ 150*MAN,	  150*MAN,	   150*MAN },		//중수~선수(3만원,5만원)
	{ 150*MAN,	  150*MAN,	   150*MAN },		//- 미사용 - 
	{2000*MAN,	 2000*MAN,	  2000*MAN },		//선수~제왕(10만원,30만원,50만원)
	{2000*MAN,	 2000*MAN,	  2000*MAN },		//- 미사용 - 
	{    2*UK,       2*UK,        2*UK },		//영웅~제왕(100만원,300만원,500만원)
};

// 등급별 판 키우기 기준 점수 (P)
const int _gJumUpBasePoint[CNS_CHANNEL_MAX] = { 300,300,300,300,300,300,300,300,300,300,300 };

// 등급별 판 키우기 증가액 (A)
const int _gJumUpIncrease[CNS_CHANNEL_MAX][MAX_POINTMONEYKIND] = {
	{   1000,		1*MAN,		10*MAN },		//자유(1천원,1만원,10만원)
	{    500,		  500,		   500 },		//입문(500원)
	{   1000,		 1000,		  1000 },		//입문~초보(1천원)
	{   3000,		 5000,		  3000 },		//하수~중수(3천원,5천원)
	{   3000,		 5000,		  3000 },		//- 미사용 - 
	{  1*MAN,		1*MAN,		 1*MAN },		//중수~고수(1만원)
	{  3*MAN,		5*MAN,		 3*MAN },		//중수~선수(3만원,5만원)
	{  3*MAN,		5*MAN,		 3*MAN },		//- 미사용 - 
	{ 10*MAN,	   30*MAN,		50*MAN },		//선수~제왕(10만원,30만원,50만원)
	{ 10*MAN,	   30*MAN,		50*MAN },		//- 미사용 - 
	{100*MAN,	  300*MAN,	   500*MAN },		//영웅~제왕(100만원,300만원,500만원)
};

// 등급별 판 키우기 상한
const LONG _gJumUpLimit[CNS_CHANNEL_MAX][MAX_POINTMONEYKIND] = {
	{   1000*3,		1*MAN*3,		10*MAN*3 },		//자유(1천원,1만원,10만원)
	{    500*3,		  500*3,		   500*3 },		//입문(500원)
	{   1000*3,		 1000*3,		  1000*3 },		//입문~초보(1천원)
	{   3000*3,		 5000*3,		  3000*3 },		//하수~중수(3천원,5천원)
	{   3000*3,		 5000*3,		  3000*3 },		//- 미사용 - 
	{  1*MAN*3,		1*MAN*3,		 1*MAN*3 },		//중수~고수(1만원)
	{  3*MAN*3,		5*MAN*3,		 3*MAN*3 },		//중수~선수(3만원,5만원)
	{  3*MAN*3,		5*MAN*3,		 3*MAN*3 },		//- 미사용 - 
	{ 10*MAN*3,	   30*MAN*3,		50*MAN*3 },		//선수~제왕(10만원,30만원,50만원)
	{ 10*MAN*3,	   30*MAN*3,		50*MAN*3 },		//- 미사용 - 
	{100*MAN*3,	  300*MAN*3,	   500*MAN*3 },		//영웅~제왕(100만원,300만원,500만원)
};

const int _gRestrictMax[MAX_RESTRICTOPTIONKIND] = {0, 10, 20, 30};
#endif