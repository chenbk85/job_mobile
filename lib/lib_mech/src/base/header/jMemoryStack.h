/* 
	filename:	jMemoryStack.h
	coder	:	Cho Wook Rea (chowookrea@hotmail)(icq:74456993) 
	comp.	:	-MAEUMNET-
	compiler:	vc++ 6.0
	date	:	2003-10-22오후 6:35:13
	title	:	
*/


#ifndef __jMemoryStack_h__
#define __jMemoryStack_h__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000

#include "header/jCriticalSection.h"

namespace nMech
{
	namespace nDataStruct
	{

		////////////////////////////////////////////////////////////////
		// T는 반드시 jTreeNode를 상속받아야 한다.
		// 또한 T는 맴버변수로  static uint _GetObjSize() , static uint _GetSlotCount() 를 가져야 한다.
		template<class T> class jMemoryStack 
			////////////////////////////////////////////////////////////////
		{
		public:
			nUtil::jCriticalSection m_CS;
			typedef uint size_t;
			typedef T Node_t;
			typedef Node_t*	pNode_t;

			//protected:
			size_t m_iTot;		// 전체 크기
			size_t m_iSize;		// 요소들의 갯수(실제 크기)
			size_t m_iMakedSlotIndex;		// 배열 인텍스

			pNode_t	*m_aSlot;		// node의 포인터를 저장하는 Array
			size_t m_iObjSize;// 최대 요소들의 갯수
			size_t m_iSlotCount;

			pNode_t	m_pTop;			//사용하지 않는 obj에 대한 stack pointer

		public:
			//////////////////////////////////////////////
			// 일반 함수.
			//////////////////////////////////////////////	
			void Del(pNode_t pN)		
			{	
				jAUTO_LOCK_CS(m_CS);
				//pN->T::~T(); 
				pN->Destroy();
				pN->_pL = m_pTop;	// stack에 pN을 붙힌다.
				m_pTop = pN;		// stack포인터 위치이동.
				m_iSize--;		// 실제 크기(list의 크기) 감소
			}

			//-----------------------------------------------------------------------------------
			// name : pNode_t New()
			// decs : 끝에 새로운 노드를 만들어 삽입한다.
			// return : 삽입된 노드의 포인터 리턴
			//-----------------------------------------------------------------------------------
			pNode_t New()
			{
				jAUTO_LOCK_CS(m_CS);
				if ( capacity() <= m_iSize)
				{
					assert(capacity()== m_iTot);
					size_t slotCount= m_iSlotCount;
					m_iSlotCount *=2;
					pNode_t	* pSlot = new pNode_t[m_iSlotCount];
					memset(pSlot , 0 , sizeof(pNode_t)* m_iSlotCount );
					memcpy(pSlot , m_aSlot , sizeof(pNode_t)*slotCount);
					delete m_aSlot;
					m_aSlot = pSlot;
				}

				if( m_iTot <= m_iSize )	// Total사이즈가 실제 사이즈보다 작거나 같으면...
				{
					assert(!m_pTop);
					m_iTot += m_iObjSize;	m_iMakedSlotIndex++;
					m_pTop = new Node_t[m_iObjSize];
					//m_pTop = (Node_t*)malloc(sizeof(Node_t)*m_iObjSize);
					assert(m_pTop);
					m_aSlot[m_iMakedSlotIndex] = m_pTop ;

					// array포인터(m_aSlot)를 연결하고 각각노드 Object포인터를 대입한다.
					m_pTop[0].iHandle = m_iMakedSlotIndex*m_iObjSize;
					size_t i;
					for(i = 1; i <m_iObjSize ; ++i)	
					{	
						m_pTop[i-1]._pL = m_pTop+i;	// 각각의 노드 연결(next만 연결을 하는 이유????)
						m_pTop[i].iHandle = m_iMakedSlotIndex*m_iObjSize+i;
					}
					m_pTop[i-1]._pL = 0;
				}
				//pNode_t newNode = new(m_pTop)T();
				pNode_t newNode = m_pTop;				// stack pointer를 pc에 대입한다.
				m_pTop = (pNode_t)m_pTop->_pL;		// stack pointer의 next를 stack pointer에 대입한다.
				++m_iSize;						// 실제 사이즈 증가.
				newNode->Create();
				return newNode;						// 삽입된 newNode의 포인터 리턴
			}	

		public:
			//------------------------------------------------------------------------------------
			// desc : 'iSlotSizeA'만큼 'm_iObjSize'를 잡으면서 생성된다.
			jMemoryStack()
			{
				jAUTO_LOCK_CS(m_CS);
				m_iTot=0;		// 전체 크기
				m_iSize=0;		// 요소들의 갯수(실제 크기)
				m_iMakedSlotIndex=0;		// 배열 인텍스
				m_iObjSize=0;// 최대 요소들의 갯수
				m_pTop=0;			//사용하지 않는 obj에 대한 stack pointer

				m_iSlotCount = Node_t::_GetSlotCount();
				m_aSlot= new pNode_t[m_iSlotCount];
				memset(m_aSlot , 0 , sizeof(pNode_t)*m_iSlotCount );

				//m_iObjSize = iSlotSizeA;	// Init()내에서 m_iObjSize의 크기를 잡는다.
				// m_aSlot(노드) Array초기화
				Init(Node_t::_GetObjSize());
			}

			~jMemoryStack()										
			{ 
				jAUTO_LOCK_CS(m_CS);
				clear();
				delete m_aSlot;
				m_aSlot =0;
			}
			void clear()
			{  
				jAUTO_LOCK_CS(m_CS);
				// 노드 배열 삭제
				for ( size_t i = 0; i < m_iSlotCount; i++ )
				{
					if ( m_aSlot[i] )
						delete [] m_aSlot[i]; 		
					//free(m_aSlot[i]);
					m_aSlot[i] = 0;
				}		

				m_pTop = 0;

				m_iSize = 0;	m_iTot = 0;	
				//delete m_aSlot;
				//m_aSlot =0;
			}


			//------------------------------------------------------------------------------------
			// desc : s의 갯수만큼 노드와 Object를 할당하여 연결시킨다.
			void Init(size_t iObjSize)		
			{	
				jAUTO_LOCK_CS(m_CS);

				m_iObjSize = iObjSize;
				m_iTot = iObjSize;					// Total = iObjSize
				m_iSize = 0;				// 초기 사이즈 값은 0
				m_iMakedSlotIndex =0;
				assert(!m_aSlot[m_iMakedSlotIndex]);
				// 노드를 iObjSize만큼 할당한하고 노드의 array포인터(m_aSlot)와 stack포인터(m_pTop)에 대입한다.
				m_pTop = m_aSlot[m_iMakedSlotIndex] = new Node_t[iObjSize];	
				//m_pTop = (Node_t*)malloc(sizeof(Node_t)*iObjSize);
				m_aSlot[m_iMakedSlotIndex] = m_pTop;
				// array포인터(m_aSlot)를 연결하고 각각노드 Object포인터를 대입한다.

				m_pTop[0].iHandle = 0;
				size_t i ;
				for(i = 1 ; i < iObjSize ; ++i)	
				{	
					m_pTop[i-1]._pL = m_pTop+i;	
					m_pTop[i].iHandle = i;
				}
				m_pTop[i-1]._pL = 0;	

			}

			/*{chowookrea@hotmail(icq74456993)2003-10-22오후 4:36:49
			//------------------------------------------------------------------------------------
			// desc : 내용을 일반 배열 처럼 사용하기 위한 연산자 오버로딩
			obj_t& operator[](size_t i) const 	
			{ 
			// "m_aSlot[i/m_iObjSize][i%m_iObjSize].o"은 (void *)이기 때문데
			// (obj_t*)로 casting를 한후에 포인터가 가르키는 데이터의 주소를 반환한다.		
			return m_aSlot[i/m_iObjSize][i%m_iObjSize].o;
			}
			//-----------------------------------------------------------------------------------
			// decs : idx를 받아서 idx에 해당하는 Node의 Pointer를 리턴한다.
			}chowookrea@hotmail(icq74456993) 2003-10-22오후 4:36:53*/

			pNode_t GetNode(uint idx)
			{
				// idx가 용랑보다 같거나 클수는 없다.
				assert( capacity() > idx );
				return &m_aSlot[idx/m_iObjSize][idx%m_iObjSize];		
			}


		public:
			size_t capacity() { return (m_iObjSize * m_iSlotCount);}
			size_t size(){ return m_iSize;}
			bool empty(){ 		return (m_iSize==0);	} // 비었는지.
			bool full()							
			{ 
				//return !m_pTop;
				assert( m_iSize <= capacity());
				if ( m_iSize == ( capacity() ) ){			return true;}
				return false;
			}
			// 호출전에 반드시 각 obj에 대한 소멸자 처리(release)를 해야함.

		};//class jMemoryStack 

	}//nHEADER


}

#endif //__jMemoryStack_h__
