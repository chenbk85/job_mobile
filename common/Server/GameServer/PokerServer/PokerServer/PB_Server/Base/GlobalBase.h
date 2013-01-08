#ifndef GLOBALBASE_H
#define GLOBALBASE_H

#include <GRCGlobal.h>
//#define interface struct

interface IGlobal
{
////////////////////////////////////////////////////////////////
// Timer �̺�Ʈ ������ THS�κ��� �Ҹ��� �Լ�
// ���� : enum GRCGLOBAL::GLOBAL_ERRORCODE
// ���� : Ÿ�̸Ӹ� ����Ҷ� IGlobalManager::SetTimer �� ���� ���� Ÿ�̸� �ε���
//		  �̰����� Ÿ�̸Ӹ� �����Ѵ�.
	virtual LONG __stdcall OnTimer(LONG lIndex) = 0;

////////////////////////////////////////////////////////////////
// Global Object�� ��ü�� ������ ��, �ش� ��ü�� �ʱ�ȭ �۾��� ���� GRC���� �����ϴ� �Լ� 
// ���� : enum GRCGLOBAL::GLOBAL_ERRORCODE
// ���� : Ÿ�̸Ӹ� ����Ҷ� IGlobalManager::SetTimer �� ���� ���� Ÿ�̸� �ε���
//		  �̰����� Ÿ�̸Ӹ� �����Ѵ�.
	virtual LONG __stdcall OnInit() = 0;

////////////////////////////////////////////////////////////////
// THS ������ Multicasting �޽����� ����������, Global Object�� Access �ؾ��ϴ� ���, THS���� �ҷ��ִ� �Լ� 
// ���� : enum GRCGLOBAL::GLOBAL_ERRORCODE
// ���� : GRC<->GRC ���� Payload�� ���� GBuf
	virtual LONG __stdcall OnMulticastMsg(GBuf& gMsgBuf) = 0;
};





#endif //!GLOBALBASE_H