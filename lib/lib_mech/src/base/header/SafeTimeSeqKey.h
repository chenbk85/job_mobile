//////////////////////////////////////////////////////////////////////////
// Safe Time-based Sequence Key class
// Author: Chunmin Ahn (emocreator@gmail.com)
// Version: 0.1
// History: 
//  2008-11: Initial work
//

#include "header/SafeType.h"
#include "base/SafeDateTime.h"


//////////////////////////////////////////////////////////////////////////
// Customize part
#define BIT_SIGNED				1	// Don't modify
#define BIT_USAGE				4	// Can modify
#define BIT_LOCATION			5	// Can modify
#define BIT_UNIQUE				12	// Can modify
#define BIT_DATETIME			42	// Don't modify

#define MASK_USAGE				0x7800000000000000
#define MASK_LOCATION			0x7C0000000000000
#define MASK_UNIQUE				0x3FFC0000000000
#define MASK_DATETIME			0x3FFFFFFFFFF

#define MIN_BASE_YEAR			2000
//////////////////////////////////////////////////////////////////////////


#define BIT_SHIFT_USAGE			(BIT_LOCATION+BIT_UNIQUE+BIT_DATETIME)
#define BIT_SHIFT_LOCATION		(BIT_UNIQUE+BIT_DATETIME)
#define BIT_SHIFT_UNIQUE		(BIT_DATETIME)
#define BIT_SHIFT_DATETIME		(0)

#define DATETIME_2000_01_01__00_00_00	0x01BF53EB256D4000

#define MAX_TIMESEQ_USAGE		((1 << BIT_USAGE) - 1)
#define MAX_TIMESEQ_LOCATION	((1 << BIT_LOCATION) - 1)
#define MAX_TIMESEQ_UNIQUE		((1 << BIT_UNIQUE) - 1)

#define MILISECOND_FACTOR		10000



class SafeTimeSeqKey
{
public:
	SafeTimeSeqKey() : _uniq(0) { }
	SafeTimeSeqKey(INT uniq) : _uniq(uniq) { }
	SafeTimeSeqKey(const SafeTimeSeqKey& sk) : _uniq(sk._uniq) { }

	INT64 GetNewKey(BYTE usage, BYTE location)
	{
		if (usage > MAX_TIMESEQ_USAGE || location > MAX_TIMESEQ_LOCATION)
			return -10;

		SYSTEMTIME st;
		SafeDateTime sdt(true);
		if (!sdt.GetSysTime(st))
			return -20;

		INT64 key = (sdt.GetDateTime() - DATETIME_2000_01_01__00_00_00) / MILISECOND_FACTOR;
		key |= ((INT64)usage << BIT_SHIFT_USAGE) | ((INT64)location << BIT_SHIFT_LOCATION) | ((INT64)(++_uniq) << BIT_SHIFT_UNIQUE);
		if (_uniq > MAX_TIMESEQ_UNIQUE)
		{
			_uniq = 1;
			key++;
		}
		return key;
	}

	void GetKeyInfo(INT64 key, BYTE& usage, BYTE& location, INT& unique, SafeDateTime& sdt)
	{
		usage    = (BYTE) ((key & MASK_USAGE) >> BIT_SHIFT_USAGE);
		location = (BYTE) ((key & MASK_LOCATION) >> BIT_SHIFT_LOCATION);
		unique   = (int)  ((key & MASK_UNIQUE) >> BIT_SHIFT_UNIQUE);
		sdt.SetDateTime(  ((key & MASK_DATETIME)) * MILISECOND_FACTOR + DATETIME_2000_01_01__00_00_00 );
	}

protected:
	SafeInt	_uniq;
};



//////////////////////////////////////////////////////////////////////////
/* 64-Bit Time-based Sequence Key

��¥�� ��Ʈ ���� ǥ���� ������ ����.

��: 2000~2127�� (0~127: 6��Ʈ, 2000���� ���� ���)
��: 1~12�� (0~15: 4��Ʈ)
��: 1~31�� (0~31: 5��Ʈ)
��: 0~23�� (0~31: 5��Ʈ)
��: 0~59�� (0~63: 6��Ʈ)
��: 0~59�� (0~63: 6��Ʈ)
�и���: 0~999�и��� (0~1024: 10��Ʈ)

�� 42��Ʈ�� �ȴ�.


���� �и��ʸ� ���ڴ����� ǥ���ϴ� ��쿡�� ������ ����.

1�� = 365�� = 8760�ð� = 525600�� = 31536000�� = 31536000000�и���
100�� = 3153600000000�и��� < 139�� = 4398046511103�и��� (42��Ʈ�� ǥ�������� ����)

�ᱹ �� 42��Ʈ������ �Ҹ�ȴ�.


�� 8����Ʈ�� �������� ������ ü�踦 ����� ������ ����.

��ȣ:     (0~1:     1��Ʈ) -- �������� ������� ��������, 1��Ʈ�� ����
����:     (0~15:    4��Ʈ) -- 0:���, 1:����, 2:����Ʈ, 3:ġƮ, 4:����, 5:�̺�Ʈ
ä��:     (0~31:    5��Ʈ) -- 0~9: ����ä��, 10~31: ������ä��(��Ÿ)
��������: (0~4095: 12��Ʈ) -- ������ ���ڰ�
����ð�: (0~xxxx: 42��Ʈ) -- ������ �Ұ��� ����� ��¥����


1�и����̳��� �ִ� 4095���� �������� ������ �� �ְ�,
���� �� ���� �Ѿ�� ��찡 �߻��Ѵٸ�, �и��ʰ��� +1 �����ؼ� ó���ؾ� �Ѵ�.

�� �̿ܿ� ����/ä���� ���� ����Ǿ� �����Ƿ�, ���� Ȯ�忡 �����ؾ� �Ѵ�.
*/
//////////////////////////////////////////////////////////////////////////

