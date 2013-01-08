   ///////////////////////////////////////////////////////////////////////////////////////////
//	filename:	yVector.h
//	coder	:	Yeon Woo Jin (yblack@hanmail.net)
//  modify : cho wook rea ( mech12@nate.com )
//	comp.	:	-MAEUMNET-
//	compiler:	vc++ 6.0
//	date	:	2003 / 
//	title	:	yVector templete class
//	desc	:	������ TVector�� ����ϴ°͵� ����� �������̽��� ������ �ְ�,
//		  
//				���������δ� ����� ������ ������ ���� Node Array�� (��������)�����Ѵ�.
//				TVector�� Node Array�� �Ѱ����̰�, yVector�� Node Array�� ������ ������ �ִ�.
/*
 �ſ� �ſ� �ſ� �ſ� �߿� : 


 struct TConnectedServerNode 
 : public jServerInfo
 , public jConnectUser<jIPacketSocket_IOCP*,serverid_t> 
 , public nDataStruct::yVectorNode<TConnectedServerNode> 
{
}

���� ���� �׻� ySimpleNode, yVectorNode... ���ø��� �� �������� ��ӹ�����.



*/
///////////////////////////////////////////////////////////////////////////////////////////



#if !defined(AFX_yVector_H__E10AE809_32F4_4017_AB00_2EABC305182A__INCLUDED_)
#define AFX_yVector_H__E10AE809_32F4_4017_AB00_2EABC305182A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "assert.h"
#include <MEMORY>
#pragma warning(disable : 4251)

#ifndef _WIN32
#define _WIN32
#endif

#include "jMemoryStack.h"

namespace nMech
{
	namespace nDataStruct
	{
		typedef void* object_t;

		template<class T> 
		class ySimpleNode
		{
		public:
			typedef uint 	size_t;

			ySimpleNode(){}
			~ySimpleNode(){}

			typedef T Node_t ;
			typedef Node_t* pNode_t;
			pNode_t _pL;
			size_t iHandle;  // �迭 �ε���. -> ��ü�� �ڵ�� ����ϸ� ��.

			ySimpleNode& operator=(const ySimpleNode & yV)
			{
				pNode_t _pL1=_pL;
				size_t iHandle1 = iHandle;

				((T*)this)->CopyFrom(((const T&)yV));
				_pL = _pL1;
				iHandle = iHandle1;

				return *this;
			}
			ySimpleNode(const ySimpleNode& yV)
			{
				pNode_t _pL1=_pL;
				uint iHandle1 = iHandle;

				*this = yV;
				_pL = _pL1;
				iHandle = iHandle1;

				return;
			}
			pNode_t NextNode(int i)
			{
				assert(i>0);
				pNode_t pN = _pL;
				for( --i; i ; --i)
				{
					pN = pN->_pL;
				}
				return pN;
			}
		};


#define jDECLEAR_SIMPLE_MEMORY(T)\
	static uint T::_size();\
	static void T::_erase(T* it);\
	static void T::_clear();\
	static T* T::_push_back();\
	static uint T::_GetObjSize();\
	static uint T::_GetSlotCount();\
	static T* T::_GetNode(uint idx);\
	static uint T::_capacity();


								// slot[0]= new T[OBJ_SIZE]    T* slot = new T*[SLOT_COUNT]
#define jDEFINE_SIMPLE_MEMORY(T		,OBJ_SIZE		, SLOT_COUNT) \
	static nMech::nUtil::jCriticalSection __ms_cs##T;\
	nMech::nDataStruct::jMemoryStack<T>& _jGet##T(){ static nMech::nDataStruct::jMemoryStack<T> g_Pool; return g_Pool;}\
	uint T::_GetObjSize(){ return OBJ_SIZE;}\
	uint T::_GetSlotCount(){ return SLOT_COUNT;}\
	uint T::_size(){ return _jGet##T().size();}\
	void T::_erase(T* it){	nMech::nUtil::jCriticalSection::Auto a(&__ms_cs##T); _jGet##T().Del(it);}\
	void T::_clear(){ nMech::nUtil::jCriticalSection::Auto a(&__ms_cs##T);_jGet##T().clear();}\
	T* T::_push_back(){	nMech::nUtil::jCriticalSection::Auto a(&__ms_cs##T); return _jGet##T().New();}\
	uint T::_capacity() { return _jGet##T().capacity();}



		// class T�� �׻� yVectorNode�� ��� �޾ƾ��Ѵ�.
		// class T�� Create(), Delete() �Լ��� �����Ǿ� �Ѵ�.
		// T�� 	static uint _GetObjSize(), static uint _GetSlotCount()�� �����Ǿ� �Ѵ�.
		template<class T> 
		class yVectorNode
		{
		public:
			typedef uint 	size_t;

			yVectorNode(){}
			~yVectorNode(){}
			//void _init(){ ((T*)this)->T();}

			typedef T Node_t ;
			typedef Node_t* pNode_t;
			pNode_t _pR , _pL;
			size_t iHandle;  // �迭 �ε���. -> ��ü�� �ڵ�� ����ϸ� ��.

			yVectorNode& operator=(const yVectorNode & yV)
			{
				pNode_t _pR1 = _pR , _pL1=_pL;
				size_t iHandle1 = iHandle;
				((T*)this)->CopyFrom(((const T&)yV));
				_pR = _pR1 ;		_pL = _pL1;
				iHandle = iHandle1;
				return *this;
			}
			yVectorNode(const yVectorNode& yV)
			{
				pNode_t _pR1 = _pR , _pL1=_pL;
				uint iHandle1 = iHandle;
				*this = yV;
				_pR = _pR1 ;		_pL = _pL1;
				iHandle = iHandle1;
				return;
			}

			pNode_t Next(int i)
			{
				assert(i>0);
				pNode_t pN = _pR;
				for( --i; i ; --i)
				{
					pN = pN->_pR;
				}
				return pN;
			}

			pNode_t Prev(int i)
			{
				assert(i>0);
				pNode_t pN = _pL;
				for( --i; i ; --i)
				{
					pN = pN->_pL;
				}
				return pN;
			}
			//friend class yVector;
		};

#define jDECLEAR_YVECTOR_MANAGER(T)\
	static uint T::_size();\
	static void T::_erase(T* it);\
	static void T::_erase(T* it, int i);\
	static void T::_clear();\
	static T* T::_push_back();\
	static T* T::_push_back(int i);\
	static uint T::_GetObjSize();\
	static uint T::_GetSlotCount();\
	static T* T::_GetNode(uint idx);\
	static uint T::_capacity();

#define jDECLEAR_YVECTOR_MANAGER2(T)\
	jDECLEAR_YVECTOR_MANAGER(T)\
	void Create();\
	void Destory();

#define jDEFINE_YVECTOR_MANAGER(T,OBJ_SIZE, SLOT_COUNT) \
	static nMech::nUtil::jCriticalSection __ms_cs##T;\
	nDataStruct::yVector<T>& _yGet##T(){ static nDataStruct::yVector<T> g_Pool; return g_Pool;}\
	uint T::_GetObjSize(){ return OBJ_SIZE;}\
	uint T::_GetSlotCount(){ return SLOT_COUNT;}\
	uint T::_size(){ return _yGet##T().size();}\
	void T::_erase(T* it){	nMech::nUtil::jCriticalSection::Auto a(&__ms_cs##T); _yGet##T().erase(it);}\
	void T::_erase(T* it, int i){	nMech::nUtil::jCriticalSection::Auto a(&__ms_cs##T); _yGet##T().erase(it,i);}\
	void T::_clear(){ nMech::nUtil::jCriticalSection::Auto a(&__ms_cs##T); _yGet##T().clear();}\
	T* T::_push_back(){	nMech::nUtil::jCriticalSection::Auto a(&__ms_cs##T); return _yGet##T().push_back();}\
	T* T::_push_back(int i){	nMech::nUtil::jCriticalSection::Auto a(&__ms_cs##T); return _yGet##T().push_back(i);}\
	T* T::_GetNode(uint idx){ return _yGet##T().GetNode(idx);}\
	uint T::_capacity() { return _yGet##T().capacity();}


		////////////////////////////////////////////////////////////////
		// class T�� �׻� yVectorNode�� ��� �޾ƾ��Ѵ�.
		template <typename T > class yVector 
			////////////////////////////////////////////////////////////////
		{
		public:
			typedef uint 	size_t;
			static jMemoryStack<T>  ms_VectorNodeMemoryManager;
			typedef T obj_t;

		protected:
			typedef T Node_t;
			typedef Node_t* pNode_t;

		public:
			nUtil::jCriticalSection m_CS;
			size_t m_iSize;
			Node_t m_B,m_E;		//list�� ���� ,�� ,curr node
		public:

			//	#define sizeAssert()
#ifdef _DEBUG
			void sizeAssert()
			{
				/*{chowookrea@hotmail2004-07-20���� 2:54:17
				jAUTO_LOCK_CS(m_CS);
				uint iS=0;
				pNode_t it= (pNode_t)m_B._pR , ie = (pNode_t)&m_E;
				assert( ie->iHandle == 9999);
				assert( it->_pL->iHandle  == 1111 );
				for( ; it != ie; it = (pNode_t)it->_pR )
				{
				++iS;
				}
				assert(iS==m_iSize);
				}chowookrea@hotmail 2004-07-20���� 2:54:21*/
			}
#else
#define sizeAssert()
#endif
			//---------------------------------------------------------------
			yVector(const yVector& yV)
			{
				jAUTO_LOCK_CS(m_CS);
				m_iSize = 0; 
				m_B._pL = (pNode_t)m_E._pR =0; 
				m_B._pR = (pNode_t)&m_E; 
				m_E._pL = (pNode_t)&m_B; 
				m_B.iHandle=1111;m_E.iHandle=9999;

				pNode_t it,itV;
				for(it = yV.m_B._pR; it != &yV.m_E ; it= (pNode_t)it->_pR)
				{
					itV = push_back();
					*itV = *it;
				}
				assert(yV.m_iSize == m_iSize);
				sizeAssert();
			}
			yVector& operator=(const yVector & yV)
			{
				assert(0);
				jAUTO_LOCK_CS(m_CS);
				sizeAssert();
				clear();
				pNode_t  it,itV;
				for(it = yV.m_B._pR; it != &yV.m_E ; it= (pNode_t)it->_pR)
				{
					itV = push_back();
					*itV = *it;
				}
				assert(yV.m_iSize == m_iSize);
				sizeAssert();
				return *this;
			}
			yVector() 
			{
				jAUTO_LOCK_CS(m_CS);
				m_iSize = 0; 
				m_B._pL = m_E._pR =0; 
				m_B._pR = (pNode_t)&m_E; 
				m_E._pL = (pNode_t)&m_B; 
				m_B.iHandle=1111;m_E.iHandle=9999;
			}

			~yVector() {/*clear()*/;}
			void clear()
			{
				jAUTO_LOCK_CS(m_CS);

				sizeAssert();
				if(!m_iSize)return;
				for(pNode_t it= begin() ; it!=end() ; )
				{
					sizeAssert();
					assert(m_iSize);
					it = erase(it) ;
					sizeAssert();
				}
				sizeAssert();
				assert(!m_iSize);
				m_iSize = 0; m_B._pR = (pNode_t)&m_E; m_E._pL = (pNode_t)&m_B;
			}
			//---------------------------------------------------------------
			// ���� �Լ�. 
			//----------------------------------------------------------------

			// memory array index�� �̿��� �����ϰ� ���� ��� ����.
			//pNode_t erase(size_t i)				{ 		pNode_t pN = GetNode(i);		return erase (pN);	}

			//it�� ������ ���� ��带 ����.
			pNode_t erase(pNode_t it)
			{
				jAUTO_LOCK_CS(m_CS);

				sizeAssert();
				assert( it!= &m_E);
				assert( it!= &m_B);

				it->_pR->_pL = (pNode_t)it->_pL;
				it->_pL->_pR = (pNode_t)it->_pR;
				pNode_t pRet = (pNode_t)it->_pL->_pR ;
				ms_VectorNodeMemoryManager.Del(it);
				sizeAssert();
				--m_iSize;
				return pRet;
			}
			pNode_t erase(pNode_t it , int iSize)
			{// it�� ���� ������ ���� 3���� �������� ����.
				jAUTO_LOCK_CS(m_CS);

				pNode_t pN = it;
				sizeAssert();
				for( ; iSize ; --iSize)
				{
					assert(pN!= &m_E);
					assert(pN!=&m_B);
					//	assert(pN!=end());
					//assert(pN!=begin());
					pN = erase(pN);
				}
				sizeAssert();
				return pN;
			}
			// it���� ie�ձ��� �����. ie�� ����.
			pNode_t erase(pNode_t it , pNode_t ie)
			{
				jAUTO_LOCK_CS(m_CS);

				//pNode_t pN = it->_pR;
				pNode_t pN = it;
				sizeAssert();
				for( ; pN!=ie;)
				{
					if(pN== &m_E)
						break;
					if(pN==&m_B)
					{
						pN = pN->_pR;
						continue;
					}
					//	assert(pN!=end());
					//assert(pN!=begin());
					pN = erase(pN);
				}
				sizeAssert();
				return pN;
			}

			//---------------------------------------------------------------
			// �߰� �Լ�
			//----------------------------------------------------------------
			pNode_t push_back(int iSize) // �������ε� ���ο� node 3���� ù��° ��带 ����.
			{
				jAUTO_LOCK_CS(m_CS);

				pNode_t pN = push_back();
				sizeAssert();
				for(--iSize; iSize; --iSize)
				{
					pN = insert(pN);
				}
				sizeAssert();
				return pN;
			}

			pNode_t push_back(){ return insert(end());}

			// it�տ� ���ο� ����߰��� �ּҸ���.
			pNode_t insert(pNode_t it) 
			{
				jAUTO_LOCK_CS(m_CS);

				sizeAssert();
				++m_iSize;
				pNode_t pN = ms_VectorNodeMemoryManager.New();
				pN->_pR = (pNode_t)it;
				pN->_pL = (pNode_t)it->_pL;
				it->_pL->_pR = (pNode_t)pN;
				it->_pL = (pNode_t)pN;
				sizeAssert();
				return (pN);
			}
			void insert(pNode_t it, pNode_t ie)
			{
				jAUTO_LOCK_CS(m_CS);

				pNode_t pN;
				while(it!=ie)
				{
					pN = push_back();
					*pN = *it;
					it = (pNode_t)it->_pR;
				}
			}
		public:

			// decs : idx�� �޾Ƽ� idx�� �ش��ϴ� Object�� Pointer�� �����Ѵ�.
			pNode_t GetNode(uint iiHandle)	
			{		
				return ms_VectorNodeMemoryManager.GetNode(iiHandle);
			}

		public:
			//---------------------------------------------------------------
			// ���� �Ʒ��� ������� stl�������� ����ϱ� ���� ��ƾ���̴�.
			//---------------------------------------------------------------
			struct iterator // �ݺ���
			{
				pNode_t _Ptr;

				iterator() {}
				iterator(pNode_t _pL):_Ptr(_pL) {}

				iterator&	operator = (pNode_t _pL)	{ _Ptr=(pNode_t)_pL; return *this; }
				iterator&	operator ++()			
				{ 
					_Ptr=(pNode_t)_Ptr->_pR; 
					return *this; 
				}
				iterator&	operator --()			{ _Ptr=(pNode_t)_Ptr->_pL; return *this; }
				iterator	operator ++(int)		
				{ 
					iterator it = *this; 
					_Ptr=(pNode_t)_Ptr->_pR; 
					return it; 
				}
				iterator	operator --(int)		{ iterator it = *this; _Ptr=(pNode_t)_Ptr->_pL; return it; }
				pNode_t		operator ->() const		{ return _Ptr; } // ok!
				Node_t&		operator * ()	const	{ return *_Ptr; }
				bool		operator ! ()			{ return !_Ptr; }
				bool		operator !=(iterator it){ return (_Ptr!=it._Ptr); }
				bool		operator ==(iterator it){ return (_Ptr==it._Ptr); }
				bool		operator ==(pNode_t it){ return (_Ptr==it); }
				bool		operator >=(iterator it){ return (_Ptr>=it._Ptr); }
				bool		operator <=(iterator it){ return (_Ptr<=it._Ptr); }
				operator pNode_t(){ return _Ptr;		}
				//obj_t&		operator [](int i) const{ return m_paObj[i]; }
				const size_t index(iterator it) const 
				{ 
					return it._Ptr->i;
				}
			};	// �ݺ���.
			pNode_t erase(iterator it)	{return erase(it._Ptr);}

			pNode_t begin(){		return (pNode_t)m_B._pR;		}
			pNode_t end()	{		return &m_E;	}
			pNode_t rbegin(){ return (pNode_t)m_E._pL; }
			pNode_t rend()	{ return &m_B; 	}

			// desc : ���� ũ��(������ ����)�� ��ȯ
			size_t size() 	{ 		return m_iSize;	}

			size_t capacity() 	{ 		return 	ms_VectorNodeMemoryManager.capacity();	}

			// desc : ������ Ȯ���Ѵ�.(�������� true ����)
			bool empty()							
			{ 
				if( m_B._pR == (pNode_t)&m_E )
					return true;
				assert(m_iSize!=0);
				return false;
			} // �������.

			Node_t& operator[](size_t idx) 	
			{ 
				// "m_aSlot[i/m_iObjSize][i%m_iObjSize].o"�� (void *)�̱� ������
				// (obj_t*)�� casting�� ���Ŀ� �����Ͱ� ����Ű�� �������� �ּҸ� ��ȯ�Ѵ�.		
				return *GetNode(idx);
			}

			template <class _Predicate>
				iterator find_if(_Predicate __pred) 
			{
				jAUTO_LOCK_CS(m_CS);

				pNode_t it = begin(), ie = end();
				for( ; it!=ie ; it=it->_pR ) if(__pred(it)) return it;
				return ie;
			}
			template <class _Predicate>
				iterator for_each(_Predicate __pred) 
			{
				jAUTO_LOCK_CS(m_CS);

				pNode_t it = begin(), ie = end();
				for( ; it!=ie ; it=it->_pR ) __pred(it); 
				return ie;
			}


		};//class yVector 

		template<class T> jMemoryStack<T> yVector<T>::ms_VectorNodeMemoryManager;

	}//nHEADER

}
#pragma warning(default: 4251)

#endif // !defined(AFX_yVector_H__E10AE809_32F4_4017_AB00_2EABC305182A__INCLUDED_)


