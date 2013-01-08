#ifndef _SYNCOBJECT
#define _SYNCOBJECT
#include <windows.h>

namespace nMech
{
	namespace nUtil
	{
		namespace nDB
		{

			class CSyncObject
			{
				CRITICAL_SECTION *m_cs;

			public:
				CSyncObject(CRITICAL_SECTION& cs)
				{
					m_cs = &cs;
					::EnterCriticalSection(m_cs);
				}

				~CSyncObject()
				{
					::LeaveCriticalSection(m_cs);
				}
			};

		}// nDB
	}// nUTIL
}// nMech



#endif _SYNCOBJECT