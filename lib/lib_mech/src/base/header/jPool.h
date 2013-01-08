
/* 
	filename:	jPool.h
	coder	:	Cho Hyun Min (by icandoit) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	4337-10-16 ���� 10:48:55
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
//        Purpose:        �޸� ����ȭ�� ���̱� ���� Ŀ�ٶ� ������ �޸𸮸� �̸� �Ҵ��س��� (as list of chunk) 
//                                �� �޸� �ȿ��� ������Ʈ�� O(1) �� �Ҵ�, �����ϵ��� �Ѵ� 
// 
//        Usage:                testPool.cpp ���� 
// 
//        Warning:        ����Ϸ��� �ϴ� Ŭ������ �ν��Ͻ��� ũ�Ⱑ chunk::size ���� ũ�� �ȵȴ� 
// 
//        Note:                ���ø��� �̿��ϵ��� �� 
//                                �̱��� Ǯ ������, ��ü���� �ڵ� ����, �Ҹ��� ���� ���� ��ũ�� 
//                                DECLARE_POOL ��ũ�θ� �̿��ؼ� �ڵ� ������ �ϴ� ��� �����Ϸ��� (C4291) ���޽����� 
//                                �߻��Ѵ�. �̰��� �������� throw() �� �����ڿ� �ٿ��ָ� �ȴ�. testPool.cpp line 8 ���� 
// 
//        Todo:                -- 
// 
//        Reference:        [1]        Bjarne Stroustrup's The C++ Programming Language 
//                                [2]        Flipcode: ChrisC's object pool lite 
// 
//        History:              neolith                note �� warning ���Ź� 2 �� �߰� 

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

		//        �����ϰ� Ǯ �����̳� (singleton) �� �����ϰ� 
		//        ��� ������Ʈ�� ����, �Ҹ��� Ǯ���� �����ϵ��� ���ִ� ��ũ�� 
		//        [2] ���� 

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
