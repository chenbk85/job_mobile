/* 
	filename:	jMemoryStack.h
	coder	:	Cho Wook Rea (chowookrea@hotmail)(icq:74456993) 
	comp.	:	-MAEUMNET-
	compiler:	vc++ 6.0
	date	:	2003-10-22���� 6:35:13
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
		// T�� �ݵ�� jTreeNode�� ��ӹ޾ƾ� �Ѵ�.
		// ���� T�� �ɹ�������  static uint _GetObjSize() , static uint _GetSlotCount() �� ������ �Ѵ�.
		template<class T> class jMemoryStack 
			////////////////////////////////////////////////////////////////
		{
		public:
			nUtil::jCriticalSection m_CS;
			typedef uint size_t;
			typedef T Node_t;
			typedef Node_t*	pNode_t;

			//protected:
			size_t m_iTot;		// ��ü ũ��
			size_t m_iSize;		// ��ҵ��� ����(���� ũ��)
			size_t m_iMakedSlotIndex;		// �迭 ���ؽ�

			pNode_t	*m_aSlot;		// node�� �����͸� �����ϴ� Array
			size_t m_iObjSize;// �ִ� ��ҵ��� ����
			size_t m_iSlotCount;

			pNode_t	m_pTop;			//������� �ʴ� obj�� ���� stack pointer

		public:
			//////////////////////////////////////////////
			// �Ϲ� �Լ�.
			//////////////////////////////////////////////	
			void Del(pNode_t pN)		
			{	
				jAUTO_LOCK_CS(m_CS);
				//pN->T::~T(); 
				pN->Destroy();
				pN->_pL = m_pTop;	// stack�� pN�� ������.
				m_pTop = pN;		// stack������ ��ġ�̵�.
				m_iSize--;		// ���� ũ��(list�� ũ��) ����
			}

			//-----------------------------------------------------------------------------------
			// name : pNode_t New()
			// decs : ���� ���ο� ��带 ����� �����Ѵ�.
			// return : ���Ե� ����� ������ ����
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

				if( m_iTot <= m_iSize )	// Total����� ���� ������� �۰ų� ������...
				{
					assert(!m_pTop);
					m_iTot += m_iObjSize;	m_iMakedSlotIndex++;
					m_pTop = new Node_t[m_iObjSize];
					//m_pTop = (Node_t*)malloc(sizeof(Node_t)*m_iObjSize);
					assert(m_pTop);
					m_aSlot[m_iMakedSlotIndex] = m_pTop ;

					// array������(m_aSlot)�� �����ϰ� ������� Object�����͸� �����Ѵ�.
					m_pTop[0].iHandle = m_iMakedSlotIndex*m_iObjSize;
					size_t i;
					for(i = 1; i <m_iObjSize ; ++i)	
					{	
						m_pTop[i-1]._pL = m_pTop+i;	// ������ ��� ����(next�� ������ �ϴ� ����????)
						m_pTop[i].iHandle = m_iMakedSlotIndex*m_iObjSize+i;
					}
					m_pTop[i-1]._pL = 0;
				}
				//pNode_t newNode = new(m_pTop)T();
				pNode_t newNode = m_pTop;				// stack pointer�� pc�� �����Ѵ�.
				m_pTop = (pNode_t)m_pTop->_pL;		// stack pointer�� next�� stack pointer�� �����Ѵ�.
				++m_iSize;						// ���� ������ ����.
				newNode->Create();
				return newNode;						// ���Ե� newNode�� ������ ����
			}	

		public:
			//------------------------------------------------------------------------------------
			// desc : 'iSlotSizeA'��ŭ 'm_iObjSize'�� �����鼭 �����ȴ�.
			jMemoryStack()
			{
				jAUTO_LOCK_CS(m_CS);
				m_iTot=0;		// ��ü ũ��
				m_iSize=0;		// ��ҵ��� ����(���� ũ��)
				m_iMakedSlotIndex=0;		// �迭 ���ؽ�
				m_iObjSize=0;// �ִ� ��ҵ��� ����
				m_pTop=0;			//������� �ʴ� obj�� ���� stack pointer

				m_iSlotCount = Node_t::_GetSlotCount();
				m_aSlot= new pNode_t[m_iSlotCount];
				memset(m_aSlot , 0 , sizeof(pNode_t)*m_iSlotCount );

				//m_iObjSize = iSlotSizeA;	// Init()������ m_iObjSize�� ũ�⸦ ��´�.
				// m_aSlot(���) Array�ʱ�ȭ
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
				// ��� �迭 ����
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
			// desc : s�� ������ŭ ���� Object�� �Ҵ��Ͽ� �����Ų��.
			void Init(size_t iObjSize)		
			{	
				jAUTO_LOCK_CS(m_CS);

				m_iObjSize = iObjSize;
				m_iTot = iObjSize;					// Total = iObjSize
				m_iSize = 0;				// �ʱ� ������ ���� 0
				m_iMakedSlotIndex =0;
				assert(!m_aSlot[m_iMakedSlotIndex]);
				// ��带 iObjSize��ŭ �Ҵ����ϰ� ����� array������(m_aSlot)�� stack������(m_pTop)�� �����Ѵ�.
				m_pTop = m_aSlot[m_iMakedSlotIndex] = new Node_t[iObjSize];	
				//m_pTop = (Node_t*)malloc(sizeof(Node_t)*iObjSize);
				m_aSlot[m_iMakedSlotIndex] = m_pTop;
				// array������(m_aSlot)�� �����ϰ� ������� Object�����͸� �����Ѵ�.

				m_pTop[0].iHandle = 0;
				size_t i ;
				for(i = 1 ; i < iObjSize ; ++i)	
				{	
					m_pTop[i-1]._pL = m_pTop+i;	
					m_pTop[i].iHandle = i;
				}
				m_pTop[i-1]._pL = 0;	

			}

			/*{chowookrea@hotmail(icq74456993)2003-10-22���� 4:36:49
			//------------------------------------------------------------------------------------
			// desc : ������ �Ϲ� �迭 ó�� ����ϱ� ���� ������ �����ε�
			obj_t& operator[](size_t i) const 	
			{ 
			// "m_aSlot[i/m_iObjSize][i%m_iObjSize].o"�� (void *)�̱� ������
			// (obj_t*)�� casting�� ���Ŀ� �����Ͱ� ����Ű�� �������� �ּҸ� ��ȯ�Ѵ�.		
			return m_aSlot[i/m_iObjSize][i%m_iObjSize].o;
			}
			//-----------------------------------------------------------------------------------
			// decs : idx�� �޾Ƽ� idx�� �ش��ϴ� Node�� Pointer�� �����Ѵ�.
			}chowookrea@hotmail(icq74456993) 2003-10-22���� 4:36:53*/

			pNode_t GetNode(uint idx)
			{
				// idx�� ������� ���ų� Ŭ���� ����.
				assert( capacity() > idx );
				return &m_aSlot[idx/m_iObjSize][idx%m_iObjSize];		
			}


		public:
			size_t capacity() { return (m_iObjSize * m_iSlotCount);}
			size_t size(){ return m_iSize;}
			bool empty(){ 		return (m_iSize==0);	} // �������.
			bool full()							
			{ 
				//return !m_pTop;
				assert( m_iSize <= capacity());
				if ( m_iSize == ( capacity() ) ){			return true;}
				return false;
			}
			// ȣ������ �ݵ�� �� obj�� ���� �Ҹ��� ó��(release)�� �ؾ���.

		};//class jMemoryStack 

	}//nHEADER


}

#endif //__jMemoryStack_h__
