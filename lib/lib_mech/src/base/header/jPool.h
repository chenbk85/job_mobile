
/* 
	filename:	jPool.h
	coder	:	Cho Hyun Min (by icandoit) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	4337-10-16 오후 10:48:55
	title	:	

	http://leechen.wzsoft.com/main.php?id=lc_lecture_other&no=34&mode=1

*/


#ifndef __jPool_h__
#define __jPool_h__
//#if _MSC_VER > 1000
#pragma once



#ifndef        __jPOOL_h 
#define        __jPOOL_h 

//        pool<T> 
//        ------- 
// 
//        Purpose:        메모리 단편화를 줄이기 위해 커다란 영역의 메모리를 미리 할당해놓고 (as list of chunk) 
//                                그 메모리 안에서 오브젝트를 O(1) 로 할당, 해제하도록 한다 
// 
//        Usage:                testPool.cpp 참조 
// 
//        Warning:        사용하려고 하는 클래스의 인스턴스의 크기가 chunk::size 보다 크면 안된다 
// 
//        Note:                템플릿을 이용하도록 함 
//                                싱글턴 풀 생성과, 개체들의 자동 생성, 소멸을 위한 보조 매크로 
//                                DECLARE_POOL 매크로를 이용해서 자동 관리를 하는 경우 컴파일러는 (C4291) 경고메시지를 
//                                발생한다. 이것을 막으려면 throw() 를 생성자에 붙여주면 된다. testPool.cpp line 8 참조 
// 
//        Todo:                -- 
// 
//        Reference:        [1]        Bjarne Stroustrup's The C++ Programming Language 
//                                [2]        Flipcode: ChrisC's object pool lite 
// 
//        History:              neolith                note 에 warning 제거법 2 줄 추가 

namespace nMech
{
	namespace nDataStruct
	{
		//---------------------------------------------------------------
		template <class        T>  class        pool 
			//----------------------------------------------------------------
		{ 
		public: 
			pool(); 
			~pool(); 
			void *        Alloc(); 
			void        Free(void *b); 

		private: 
			struct        link { link *next; }; 
			struct        chunk { 
				enum { size = 8*1024-16 }; 
				TCHAR        mem[size]; 
				chunk *        next; 
			}; 
			const unsigned int        esize; 
			chunk *        m_chunks; 
			link *        m_head; 
			pool(pool &); 
			void        operator = (pool &); 
			void        Grow(); 
		}; 

		template <class        T> 
			inline        pool<T> :: pool() 
			: esize(sizeof(T)<sizeof(link)?sizeof(link):sizeof(T)) 
		{ 
			m_head = 0; 
			m_chunks = 0; 
		} 

		template <class        T> 
			inline        pool<T> :: ~pool() 
		{ 
			chunk *        n = m_chunks; 
			while (n) { 
				chunk *        p = n; 
				n = n->next; 
				delete        p; 
			} 
		} 

		template <class        T> 
			inline        void *        pool<T> :: Alloc() 
		{ 
			if (m_head == 0) 
				Grow(); 
			link *        p = m_head; 
			m_head = p->next; 
			return        p; 
		} 

		template <class        T> 
			inline        void         pool<T> :: Free(void *b) 
		{ 
			link *        p = static_cast<link *>(b); 
			p->next = m_head; 
			m_head = p; 
		} 

		template <class        T> 
			inline        void         pool<T> :: Grow() 
		{ 
			chunk *        n = new chunk; 
			n->next = m_chunks; 
			m_chunks = n; 

			const int        nelem = chunk::size/esize; 
			TCHAR *        start = n->mem; 
			TCHAR *        last = &start[(nelem-1)*esize]; 
			for (TCHAR *p = start; p<last; p+=esize) 
				reinterpret_cast<link *>(p)->next = reinterpret_cast<link *>(p+esize); 
			reinterpret_cast<link *>(last)->next = 0; 
			m_head = reinterpret_cast<link *>(start); 
		} 

		//        간단하게 풀 컨테이너 (singleton) 를 선언하고 
		//        모든 오브젝트의 생성, 소멸을 풀에서 관리하도록 해주는 매크로 
		//        [2] 참조 

#define DECLARE_POOL(classname) \ 
	public:\ 
					 void* operator new(size_t size) { return g_pool.Alloc(); } \ 
					 void operator delete(void* ptr, size_t size) { g_pool.Free(ptr); } \ 
					 static pool<classname> g_pool; 

#define DEFINE_POOL(classname) \ 
				 pool<classname> classname::g_pool; 

#endif 


				 //#endif // _MSC_VER > 1000

	}//nHEADER

}

#endif //__jPool_h__
