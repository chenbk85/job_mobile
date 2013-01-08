// jcSoundSystem.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

#ifdef USING_JCGAME_MEMORY_MANAGER
#ifndef _XBOX
_ACCESS_POOL;
#endif //_XBOX
#else //USING_JCGAME_MEMORY_MANAGER
//! Structre filled by call to jcModuleGetMemoryInfo()
extern "C" __declspec(dllexport) void jcModuleGetMemoryInfo( jcModuleMemoryInfo *pMemInfo )
{
#if (defined CS_VERSION_372) || (defined CS_VERSION_361)
  unsigned int nCurrentAlloced;
	unsigned int nMaxAlloced;
#else
  size_t nCurrentAlloced;
	size_t nMaxAlloced;
#endif
  CS_GetMemoryStats(&nCurrentAlloced, &nMaxAlloced);
	pMemInfo->allocated = nMaxAlloced;
	pMemInfo->freed = 0;
	pMemInfo->num_allocations = 0;
};
#endif //USING_JCGAME_MEMORY_MANAGER

#include "DummySound.h"	
#include <jc_Camera.h>
#include "SoundSystem.h"


namespace nMech
{
	StringID g_Current_LogLevel_jStringID = jx(jSound);

	namespace nJC_SOUND
	{

		extern "C" 
		{
			JC_GAMESOUND_API ISoundSystem* CreateSoundSystem(struct ISystem* pSys, void* pInitData)
			{
				//create a brand new sound system
				//g_pISystem
				CSoundSystem* pSoundSystem = new CSoundSystem((HWND)pInitData);

				if (!pSoundSystem || !pSoundSystem->IsOK())
				{
					//if the sound system cannot be created or initialized,
					//create the dummy sound system (NULL sound system, same as for
					//dedicated server)

					if (pSoundSystem)
						pSoundSystem->Release();

					CDummySoundSystem *pDummySound=new CDummySoundSystem((HWND)pInitData);
					g_pISoundSystem = pDummySound;
					return pDummySound;

				}

				g_pISoundSystem = pSoundSystem;
				return pSoundSystem;
			}

			JC_GAMESOUND_API void* jCreateInterface(jIE* pE)
			{
#if 0
				//create a brand new sound system
				CSoundSystem* pSoundSystem =0;
				jID* pDocVar = (jID*)pE->GetDoc()->Find(jS(FILES))->Find(TEXT("jConsoleVar"))->GetUserData();
				assert(pDocVar);
				bool useDummy=pE->GetAttrVar(TEXT("USE_DUMMYSOUND"))->intValue();

				if(!useDummy)
				{
					try{
						pSoundSystem = new CSoundSystem(pDocVar);
						g_pISoundSystem =pSoundSystem; 
					}
					catch(...)
					{
						useDummy=true;
					}
				}

				if (useDummy || !pSoundSystem || !pSoundSystem->IsOK() )
				{
					//if the sound system cannot be created or initialized,
					//create the dummy sound system (NULL sound system, same as for
					//dedicated server)

					if (pSoundSystem)
						pSoundSystem->Release();

					CDummySoundSystem *pDummySound=new CDummySoundSystem(pDocVar);
					g_pISoundSystem = pDummySound;
				}
				return g_pISoundSystem;
#endif
				return 0;
			}

			__declspec(dllexport) void jDeleteInterface()
			{
			}
		}

	} //nJC_SOUND
}//nMech







#ifndef __MWERKS__
#ifndef _XBOX
///////////////////////////////////////////////
BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call,  LPVOID lpReserved)
{
    return TRUE;
}
#endif //_XBOX
#endif

#include <CrtDebugStats.h>
