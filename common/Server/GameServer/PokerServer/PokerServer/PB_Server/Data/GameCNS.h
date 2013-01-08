#pragma once

#ifdef CNSRENEWAL_WORK

const LONG	MAX_POINTMONEYKIND = 3;		//���� �Ӵ� ����
const LONG	_gPointMoney[CNS_CHANNEL_MAX][MAX_POINTMONEYKIND] = {
	{   1000,		1*MAN,		10*MAN },		//����(1õ��,1����,10����)
	{    500,		  500,		   500 },		//�Թ�(500��)
	{   1000,		 1000,		  1000 },		//�Թ�~�ʺ�(1õ��)
	{   3000,		 5000,		  3000 },		//�ϼ�~�߼�(3õ��,5õ��)
	{   3000,		 5000,		  3000 },		//- �̻�� - 
	{  1*MAN,		1*MAN,		 1*MAN },		//�߼�~���(1����)
	{  3*MAN,		5*MAN,		 3*MAN },		//�߼�~����(3����,5����)
	{  3*MAN,		5*MAN,		 3*MAN },		//- �̻�� - 
	{ 10*MAN,	   30*MAN,		50*MAN },		//����~����(10����,30����,50����)
	{ 10*MAN,	   30*MAN,		50*MAN },		//- �̻�� - 
	{100*MAN,	  300*MAN,	   500*MAN },		//����~����(100����,300����,500����)
};

const LONG	MAX_ENTERUSERLEVELKIND = 2;		//ä�δ� ���� ������ ��� ����
const LONG	gEnterUserLevel[CNS_CHANNEL_MAX][MAX_ENTERUSERLEVELKIND] = {
	{	USER_LEVEL_IPMUN,	USER_LEVEL_EMPEROR	}, //����(1õ��,1����,10����)
	{	USER_LEVEL_IPMUN,	USER_LEVEL_IPMUN	}, //�Թ�(500��)
	{	USER_LEVEL_IPMUN,	USER_LEVEL_CHOBO	}, //�Թ�~�ʺ�(1õ��)
	{	USER_LEVEL_CHOBO,	USER_LEVEL_JUNGSU	}, //�ϼ�~�߼�(3õ��,5õ��)
	{	USER_LEVEL_NONE,	USER_LEVEL_NONE		}, //- �̻�� - 
	{	USER_LEVEL_JUNGSU,	USER_LEVEL_GOSU		}, //�߼�~���(1����)
	{	USER_LEVEL_JUNGSU,	USER_LEVEL_SUNSU	}, //�߼�~����(3����,5����)
	{	USER_LEVEL_NONE,	USER_LEVEL_NONE		}, //- �̻�� - 
	{	USER_LEVEL_SUNSU,	USER_LEVEL_EMPEROR	}, //����~����(10����,30����,50����)
	{	USER_LEVEL_NONE,	USER_LEVEL_NONE		}, //- �̻�� - 
	{	USER_LEVEL_HERO,	USER_LEVEL_EMPEROR	}, //����~����(100����,300����,500����)
};

//���� ���� �ݾ�.
const int MAX_LIMITMONEYKIND = 6; // �ּ�����Ӵ� ����. �Լ����� ó����.

//�濡 ���� �� �ִ� �ּұݾ�.
const LONGLONG gStayMoney[CNS_CHANNEL_MAX][MAX_POINTMONEYKIND] = {
	{    7000,		7*MAN,		70*MAN },		//����(1õ��,1����,10����)
	{    3500,		 3500,		  3500 },		//�Թ�(500��)
	{    7000,		 7000,		  7000 },		//�Թ�~�ʺ�(1õ��)
	{  15*MAN,	   15*MAN,		15*MAN },		//�ϼ�~�߼�(3õ��,5õ��)
	{  15*MAN,	   15*MAN,		15*MAN },		//- �̻�� - 
	{  50*MAN,	   50*MAN,		50*MAN },		//�߼�~���(1����)
	{ 150*MAN,	  150*MAN,	   150*MAN },		//�߼�~����(3����,5����)
	{ 150*MAN,	  150*MAN,	   150*MAN },		//- �̻�� - 
	{2000*MAN,	 2000*MAN,	  2000*MAN },		//����~����(10����,30����,50����)
	{2000*MAN,	 2000*MAN,	  2000*MAN },		//- �̻�� - 
	{    2*UK,       2*UK,        2*UK },		//����~����(100����,300����,500����)
};

// ��޺� �� Ű��� ���� ���� (P)
const int _gJumUpBasePoint[CNS_CHANNEL_MAX] = { 300,300,300,300,300,300,300,300,300,300,300 };

// ��޺� �� Ű��� ������ (A)
const int _gJumUpIncrease[CNS_CHANNEL_MAX][MAX_POINTMONEYKIND] = {
	{   1000,		1*MAN,		10*MAN },		//����(1õ��,1����,10����)
	{    500,		  500,		   500 },		//�Թ�(500��)
	{   1000,		 1000,		  1000 },		//�Թ�~�ʺ�(1õ��)
	{   3000,		 5000,		  3000 },		//�ϼ�~�߼�(3õ��,5õ��)
	{   3000,		 5000,		  3000 },		//- �̻�� - 
	{  1*MAN,		1*MAN,		 1*MAN },		//�߼�~���(1����)
	{  3*MAN,		5*MAN,		 3*MAN },		//�߼�~����(3����,5����)
	{  3*MAN,		5*MAN,		 3*MAN },		//- �̻�� - 
	{ 10*MAN,	   30*MAN,		50*MAN },		//����~����(10����,30����,50����)
	{ 10*MAN,	   30*MAN,		50*MAN },		//- �̻�� - 
	{100*MAN,	  300*MAN,	   500*MAN },		//����~����(100����,300����,500����)
};

// ��޺� �� Ű��� ����
const LONG _gJumUpLimit[CNS_CHANNEL_MAX][MAX_POINTMONEYKIND] = {
	{   1000*3,		1*MAN*3,		10*MAN*3 },		//����(1õ��,1����,10����)
	{    500*3,		  500*3,		   500*3 },		//�Թ�(500��)
	{   1000*3,		 1000*3,		  1000*3 },		//�Թ�~�ʺ�(1õ��)
	{   3000*3,		 5000*3,		  3000*3 },		//�ϼ�~�߼�(3õ��,5õ��)
	{   3000*3,		 5000*3,		  3000*3 },		//- �̻�� - 
	{  1*MAN*3,		1*MAN*3,		 1*MAN*3 },		//�߼�~���(1����)
	{  3*MAN*3,		5*MAN*3,		 3*MAN*3 },		//�߼�~����(3����,5����)
	{  3*MAN*3,		5*MAN*3,		 3*MAN*3 },		//- �̻�� - 
	{ 10*MAN*3,	   30*MAN*3,		50*MAN*3 },		//����~����(10����,30����,50����)
	{ 10*MAN*3,	   30*MAN*3,		50*MAN*3 },		//- �̻�� - 
	{100*MAN*3,	  300*MAN*3,	   500*MAN*3 },		//����~����(100����,300����,500����)
};

const int _gRestrictMax[MAX_RESTRICTOPTIONKIND] = {0, 10, 20, 30};
#endif