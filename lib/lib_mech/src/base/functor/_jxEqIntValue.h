#ifndef _jxEqIntValu23233223298327e___
#define _jxEqIntValu23233223298327e___

namespace nMech
{
	namespace nFunctor
	{

		struct _jxEqIntValue// element의 int 값으로검색
		{	
			int iVal;	_jxEqIntValue(int pV): iVal(pV){}
			bool operator()(jIE* e)
			{
				if(e->GetVar()->GetType()==jIVar::EDint && e->GetVar()->intValue()==iVal) return true;
				return false;
			}
		};
	}
}

#endif //_jxEqIntValu23233223298327e___