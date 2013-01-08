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

날짜의 비트 압축 표현은 다음과 같다.

년: 2000~2127년 (0~127: 6비트, 2000값을 빼고 계산)
월: 1~12월 (0~15: 4비트)
일: 1~31일 (0~31: 5비트)
시: 0~23시 (0~31: 5비트)
분: 0~59분 (0~63: 6비트)
초: 0~59초 (0~63: 6비트)
밀리초: 0~999밀리초 (0~1024: 10비트)

총 42비트가 된다.


만약 밀리초를 숫자단위로 표현하는 경우에는 다음과 같다.

1년 = 365일 = 8760시간 = 525600분 = 31536000초 = 31536000000밀리초
100년 = 3153600000000밀리초 < 139년 = 4398046511103밀리초 (42비트로 표현가능한 숫자)

결국 총 42비트정도가 소모된다.


총 8바이트를 기준으로 아이템 체계를 만들면 다음과 같다.

기호:     (0~1:     1비트) -- 음수값을 허용하지 않으려고, 1비트는 버림
이유:     (0~15:    4비트) -- 0:드랍, 1:생산, 2:퀘스트, 3:치트, 4:복구, 5:이벤트
채널:     (0~31:    5비트) -- 0~9: 게임채널, 10~31: 컨텐츠채널(기타)
고유숫자: (0~4095: 12비트) -- 고유한 숫자값
현재시간: (0~xxxx: 42비트) -- 위에서 소개된 압축된 날짜정보


1밀리초이내에 최대 4095개의 아이템을 생산할 수 있고,
만약 이 값을 넘어서는 경우가 발생한다면, 밀리초값을 +1 진행해서 처리해야 한다.

그 이외에 이유/채널쪽 값이 제약되어 있으므로, 추후 확장에 주의해야 한다.
*/
//////////////////////////////////////////////////////////////////////////

