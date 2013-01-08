// support for leak dumping and statistics gathering using vs Crt Debug
// should be included in every DLL below DllMain()
#ifdef WIN32

#ifdef _DEBUG

#include "interface/ILog.h"
#include <crtdbg.h>
#include <algorithm>
#include <vector>

// copied from DBGINT.H (not a public header!)

#define nNoMansLandSize 4

typedef struct _CrtMemBlockHeader
{
        struct _CrtMemBlockHeader * pBlockHeaderNext;
        struct _CrtMemBlockHeader * pBlockHeaderPrev;
        char *                      szFileName;
        int                         nLine;
        size_t                      nDataSize;
        int                         nBlockUse;
        long                        lRequest;
        unsigned char               gap[nNoMansLandSize];
        /* followed by:
         *  unsigned char           data[nDataSize];
         *  unsigned char           anotherGap[nNoMansLandSize];
         */
} _CrtMemBlockHeader;

struct SFileInfo
{
	int blocks; INT_PTR bytes;							//AMD Port
	SFileInfo(INT_PTR b) { blocks = 1; bytes = b; };	//AMD Port
};

_CrtMemState lastcheckpoint;
bool checkpointset = false;

extern "C" void __declspec(dllexport) CheckPoint()
{
	_CrtMemCheckpoint(&lastcheckpoint); 
	checkpointset = true;
};

bool pairgreater( const std::pair<string, SFileInfo> &elem1, const std::pair<string, SFileInfo> &elem2)
{
   return elem1.second.bytes > elem2.second.bytes;
}

extern "C" void __declspec(dllexport) UsageSummary(ILog *log, char *modulename, int *extras)
{
};

#endif

#if !defined(_RELEASE) && !defined(_DLL)
extern "C" HANDLE _crtheap;
extern "C" HANDLE __declspec(dllexport) GetDLLHeap() { return _crtheap; };
#endif

#endif //WIN32
