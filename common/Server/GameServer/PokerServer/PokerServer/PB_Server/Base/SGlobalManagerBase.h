#ifndef SGLOBALMANAGERBASE_H
#define SGLOBALMANAGERBASE_H




interface ISGlobalManager : public IXObject
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// ������ �ð��� �ش�  GRC�� OnTimer �Լ��� �θ���
	// ���� : GRC�� SSN, Due Time(�и��ʴ���), Period (�и��ʴ���)
	// ���� :enum GRCGLOBAL::GLOBAL_ERRORCODE
	virtual long __stdcall SetTimerInGlobalObject(long lSSN, long* plTimerIndex, long lDueTime, long lPeriod) = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// RemoveTimerInGlobalObject ������ SetTimer���� �����ߴ� Index�� �ִ´�.
	// ���μ��� ����� Ÿ�̸ӵ� ������Ƿ�, RemoveTimerInGlobalObject�� �ʿ��� ��쿡�� ����Ѵ�.
	// ���� : GRC�� SSN, SetTimerInGlobalObject�� ���� Index
	// ���� : enum GRCGLOBAL::GLOBAL_ERRORCODE
	virtual long __stdcall RemoveTimerInGlobalObject(long lSSN, long lIndex) = 0;

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Multicast Message�� ������ ���� �Լ�, 2010.12 ����  �̱��� �Ǿ���
	// ���� : GRC�� SSN, MsgType(SGSSGS.adl�� ����)�ٸ� SGS�� ������ ���� GBuf 
	// ���� : enum GRCGLOBAL::GLOBAL_ERRORCODE
	virtual long __stdcall SendMulticastMsgInGlobalObject(long lSSN, long lMsgType, GBuf& gGRCMsg) = 0;


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// DB Access Interface
	// ���� : ����Ÿ��, SSN, Indata, outdata, result 
	// ���� : TRUE/FALSE
	virtual long __stdcall ExecuteQueryToDBInGlobalObject(long lQueryType, long lDBType, const char* szQuery, long lSize, GBuf& bufReturn, long* plResult) = 0;

};





#endif //!SGLOBALMANAGERBASE_H