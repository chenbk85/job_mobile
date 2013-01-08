#ifndef _jasdf98798sdf8_MEMORY_MANAGER_H_
#define _jasdf98798sdf8_MEMORY_MANAGER_H_

#include <malloc.h>
//#include <jc/platform.h>
#include <stdlib.h>

#ifndef JBASE_API 
	#ifdef JBASE_EXPORTS
		#define JBASE_API __declspec(dllexport)
	#else
		#define JBASE_API __declspec(dllimport)
		//#pragma comment(lib, "jBase.lib")
	#endif
#endif

typedef signed __int64			jc_int64;
typedef unsigned __int64		jc_uint64;

//! Structure filled by call to jcModuleGetMemoryInfo()
struct jcModuleMemoryInfo
{
	//! Total Ammount of memory allocated.
	jc_uint64 allocated;
	//! Total Ammount of memory freed.
	jc_uint64 freed;
	//! Total number of memory allocations.
	int num_allocations;
};
//////////////////////////////////////////////////////////////////////////
// Used by overrided new and delete operators.
//////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
	// C++ methods.
	extern "C"
	{
		void* jcModuleMalloc(size_t size) throw();
		void* jcModuleRealloc(void *memblock,size_t size) throw();
		void  jcModuleFree(void *ptr) throw();
		void* jcModuleReallocSize(void *memblock,size_t oldsize,size_t size);
		void  jcModuleFreeSize(void *ptr,size_t size);
	}
	#else
		// C methods.
		extern void* jcModuleMalloc(size_t size);
		extern void* jcModuleRealloc(void *memblock,size_t size);
		extern void  jcModuleFree(void *ptr);
		extern void* jcModuleReallocSize(void *memblock,size_t oldsize,size_t size);
		extern void  jcModuleFreeSize(void *ptr,size_t size);
#endif //__cplusplus
//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
	extern "C" {
#endif

JBASE_API void *jcMalloc(size_t size);
JBASE_API void *jcRealloc(void *memblock,size_t size);
JBASE_API void *jcReallocSize(void *memblock,size_t oldsize,size_t size);
JBASE_API void jcFree(void *p);
JBASE_API void jcFreeSize(void *p,size_t size);
typedef char							CHAR;
JBASE_API int jcStats(CHAR*buf);
JBASE_API void jcFlushAll();

#ifdef __cplusplus
	}
#endif 

#define _ACCESS_POOL

#if defined(_DEBUG) || defined(DONT_USE_JCGAME_MEMORY_MANAGER)
	#define jcModuleMalloc malloc
	#define jcModuleRealloc realloc
	#define jcModuleFree free
#else
	#ifdef USE_NEWPOOL
		#define USING_JCGAME_MEMORY_MANAGER
		// - check this covers all prototypes
		// - way to check memory in use by old malloc?
		// issues
		// only release
		// - globals with allocs -> can make it possible but rather not
		// - calloc? also malloc -> new
		//////////////////////////////////////////////////////////////////////////
		// _PoolHelper definition.
		//////////////////////////////////////////////////////////////////////////
		#ifdef __cplusplus
		struct _jcMemoryManagerPoolHelper
		{
			jc_uint64 allocatedMemory;
			jc_uint64 freedMemory;
			int numAllocations;
			#if defined(WIN32) || defined(LINUX)
				HMODULE hSystem;
			#endif
			typedef void *(*FNC_jcMalloc)(size_t size);
			typedef void *(*FNC_jcRealloc)(void *memblock,size_t size);
			typedef void *(*FNC_jcReallocSize)(void *memblock,size_t oldsize,size_t size);
			typedef void (*FNC_jcFree)(void *p);
			typedef void (*FNC_jcFreeSize)(void *p,size_t size);
			typedef int (*FNC_jcStats)(char *buf);
			FNC_jcMalloc _jcMalloc;
			FNC_jcRealloc _jcRealloc;
			FNC_jcReallocSize _jcReallocSize;
			FNC_jcFree _jcFree;
			FNC_jcFreeSize _jcFreeSize;

			explicit _jcMemoryManagerPoolHelper( void *pHandle = NULL )
			{
				allocatedMemory = 0;
				freedMemory = 0;
				numAllocations = 0;
				/* *_* by icandoit : 2006-06-02 17:40:48

				if (pHandle)
					hSystem = (HMODULE)pHandle;
				else
					hSystem = LoadLibrary("jBase.dll"); 
				if(hSystem)
				{
					_jcMalloc=(FNC_jcMalloc)GetProcAddress((HINSTANCE)hSystem,"jcMalloc"); 
					_jcRealloc=(FNC_jcRealloc)GetProcAddress((HINSTANCE)hSystem,"jcRealloc"); 
					_jcReallocSize=(FNC_jcReallocSize)GetProcAddress((HINSTANCE)hSystem,"jcReallocSize"); 
					_jcFree=(FNC_jcFree)GetProcAddress((HINSTANCE)hSystem,"jcFree"); 
					_jcFreeSize=(FNC_jcFreeSize)GetProcAddress((HINSTANCE)hSystem,"jcFreeSize"); 
				};
				*/ //*_* by icandoit : 2006-06-02 17:40:51
				hSystem=0;
				_jcMalloc=(FNC_jcMalloc)jcMalloc;
				_jcRealloc=(FNC_jcRealloc)jcRealloc;
				_jcReallocSize=(FNC_jcReallocSize)jcReallocSize;
				_jcFree=(FNC_jcFree)jcFree;
				_jcFreeSize=(FNC_jcFreeSize)jcFreeSize;


				// Not need system anymore.
				if(/*!hSystem || */!_jcMalloc || !_jcRealloc || !_jcReallocSize || !_jcFree || !_jcFreeSize)
				{
					MessageBoxA(NULL, "Could not access jBase.dll (check working directory)", "Memory Manager", MB_OK);
					if (hSystem)
						::FreeLibrary( hSystem );
					exit(1);
				};
				if (hSystem)
					::FreeLibrary( hSystem );
			}
			~_jcMemoryManagerPoolHelper()
			{
			}
			void GetMemoryInfo( jcModuleMemoryInfo *pMmemInfo )
			{
				pMmemInfo->allocated = allocatedMemory;
				pMmemInfo->freed = freedMemory;
				pMmemInfo->num_allocations = numAllocations;
			}
			//////////////////////////////////////////////////////////////////////////
			// Local version of allocations, does memory counting per module.
			//////////////////////////////////////////////////////////////////////////
			__forceinline void*	Malloc(size_t size)
			{
				allocatedMemory += size;
				numAllocations++;
				return _jcMalloc( size );
			}
			//////////////////////////////////////////////////////////////////////////
			__forceinline void*	Realloc(void *memblock,size_t size)
			{
				if (memblock == NULL)
				{
					allocatedMemory += size;
					numAllocations++;
				}
				else
				{
					numAllocations++;
					size_t oldsize = ((int*)memblock)[-1];
					allocatedMemory += size;
					freedMemory += oldsize;
				}
				return _jcRealloc( memblock,size );
			}
			//////////////////////////////////////////////////////////////////////////
			__forceinline void Free( void *memblock )
			{
				if (memblock != 0)
				{
					size_t size = ((int*)memblock)[-1];
					freedMemory += size;
				}
				_jcFree( memblock );
			}
			//////////////////////////////////////////////////////////////////////////
			__forceinline void* ReallocSize(void *memblock,size_t oldsize,size_t size)
			{
				allocatedMemory += size;
				freedMemory += oldsize;
				numAllocations++;
				return _jcReallocSize( memblock,oldsize,size );
			}
			//////////////////////////////////////////////////////////////////////////
			__forceinline void FreeSize( void *memblock,size_t size )
			{
				freedMemory += size;
				_jcFreeSize( memblock,size );
			}
		};
		#endif //__cplusplus

		#ifdef _USRDLL
			#define JC_MEM_USAGE_API extern "C" __declspec(dllexport)
		#else
			#define JC_MEM_USAGE_API
		#endif

		#undef _ACCESS_POOL
		#define _ACCESS_POOL \
		_jcMemoryManagerPoolHelper g_jcMemoryManagerHelper;\
			void* jcModuleMalloc( size_t size ) throw(){ return g_jcMemoryManagerHelper.Malloc(size); };\
			void* jcModuleRealloc( void *ptr,size_t size )  throw(){ return g_jcMemoryManagerHelper.Realloc(ptr,size); };\
			void  jcModuleFree( void *ptr ) throw() { g_jcMemoryManagerHelper.Free(ptr); };\
			void* jcModuleReallocSize(void *ptr,size_t oldsize,size_t size)  { return g_jcMemoryManagerHelper.ReallocSize(ptr,oldsize,size); };\
			void  jcModuleFreeSize(void *ptr,size_t size) { g_jcMemoryManagerHelper.FreeSize(ptr,size); };\
			JC_MEM_USAGE_API void jcModuleGetMemoryInfo( jcModuleMemoryInfo *pMemInfo ) { g_jcMemoryManagerHelper.GetMemoryInfo(pMemInfo); };

		// To be created inside jSystem.
		#define _SYSTEM_POOL( hSystemHandle ) \
			_jcMemoryManagerPoolHelper g_jcMemoryManagerHelper( hSystemHandle );\
			void* jcModuleMalloc( size_t size ) throw() {return g_jcMemoryManagerHelper.Malloc(size); };\
			void* jcModuleRealloc( void *ptr,size_t size ) throw(){ return g_jcMemoryManagerHelper.Realloc(ptr,size); };\
			void  jcModuleFree( void *ptr ) { g_jcMemoryManagerHelper.Free(ptr); };\
			void* jcModuleReallocSize(void *ptr,size_t oldsize,size_t size)  { return g_jcMemoryManagerHelper.ReallocSize(ptr,oldsize,size); };\
			void  jcModuleFreeSize(void *ptr,size_t size) { g_jcMemoryManagerHelper.FreeSize(ptr,size); };\
			JC_MEM_USAGE_API void jcModuleGetMemoryInfo( jcModuleMemoryInfo *pMemInfo ) { g_jcMemoryManagerHelper.GetMemoryInfo(pMemInfo); };

		#ifdef __cplusplus
			#include <new.h>
		#endif


		#undef malloc
		#undef realloc
		#undef free


		#define malloc				jcModuleMalloc
		#define realloc				jcModuleRealloc
		#define free				jcModuleFree
		#define realloc_size		jcModuleReallocSize
		#define free_size			jcModuleFreeSize

		#ifdef __cplusplus
				inline void * __cdecl operator new   (size_t  size) { return jcModuleMalloc(size); } 
				inline void * __cdecl operator new[](size_t size) { return jcModuleMalloc(size); }; 
				inline void __cdecl operator delete  (void *p) { jcModuleFree(p); };
				inline void __cdecl operator delete[](void *p) { jcModuleFree(p); };
		#endif //__cplusplus

	#endif // USE_NEWPOOL

#endif // _DEBUG

#endif //_jasdf98798sdf8_MEMORY_MANAGER_H_
