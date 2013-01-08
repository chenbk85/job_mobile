/* 
	filename:	jTreeNode.h
	coder	:	Cho Wook Rea (chowookrea@hotmail)(icq:74456993) 
	comp.	:	-MAEUMNET-
	compiler:	vc++ 6.0
	date	:	2003-10-22오후 4:47:23
	title	:	
*/


#ifndef __jTreeNode_h__
#define __jTreeNode_h__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000
#include "jMemoryStack.h"

namespace nMech
{
	namespace nDataStruct
	{
		//#pragma warning(disable : 4251)
		//---------------------------------------------------------------
		template<class T> class  jTreeNode
			//----------------------------------------------------------------
		{
		public:
			typedef jTreeNode<T> parent_t;
			typedef T Node_t;
			typedef Node_t* pNode_t;

			//---------------------------------------------------------------
			// 메모리관리자.
			//----------------------------------------------------------------
			static jMemoryStack<T>  ms_TreeNodeMemoryManager;

			//---------------------------------------------------------------
			// 초기화 함수.							
			//----------------------------------------------------------------
		public:
			jTreeNode(){}
			void clear()
			{
				if(_pP)
					Erase();
				else
					EraseChild();
				assert(!iChild);
				assert(!_pC);
				//SetTreeInfo(0,0,0,0,0,0);
			}
			size_t CheckSize()
			{
				pNode_t it;
				size_t iSize=0;
				size_t iSubTot=0;
				for(it= _pC; it; it = it->_pR)
				{
					++iSize;
					iSubTot += it->CheckSize();
				}
				assert(iSize==iChild);
				return iSubTot+iSize;

			}

			//---------------------------------------------------------------
			// 삭제 함수.
			//----------------------------------------------------------------
		protected:	pNode_t _EraseFast() 
									// Erase()보다 빠르게 처리됨. EraseChild()에서만 호출됨. 
									//자신의 자식들을 삭제하고 자신도 삭제함. 
									// 자신의 동생 노드를 리턴한다.
								{
									EraseChild();
									assert(iChild==0);
									assert(_pC==0);
									assert(_pP->iChild);
									pNode_t pR1 = _pR;
									--_pP->iChild;
									ms_TreeNodeMemoryManager.Del((pNode_t)this);
									return pR1;
								}
		public:
			void EraseChild()
			{
				pNode_t pN;
				for( pN = _pC; pN ; )
				{
					if(_pP)
						assert(_pP->iChild);

					assert(_pC);
					assert(iChild);

					pN = pN->_EraseFast();
				}
				assert(iChild == 0);
				_pC = 0;
			}

			pNode_t Erase() // 자신의 자식들을 모두 삭제하고 자신도 삭제 시킴. 자신의 다음동생node(right)를 리턴.
			{
				EraseChild();
				assert(_pC==0);
				assert(iChild == 0);
				if(!_pP)
				{
					assert(!_pL && !_pR);
					return 0;
				}

				pNode_t pR1 = _pR;

				if(_pL) 
				{
					_pL->_pR = pR1;// 자기의 바로 옆형에게 자기의 동생노드를 등록.
				}
				else
				{
					_pP->_pC = pR1;// 자기가 형제의 맞이면 부모에게 자기의 동생을 맞이라고 알린다
				}

				if(_pR)
				{
					pR1->_pL = _pL;
					_pR->ReMakeSiblingOrder(iOrder);
				}

				//_pR=_pL=_pP=0;
				//iChild=iOrder=0;
				if(_pP)
					--_pP->iChild;
#ifdef _DEBUG
				_pR=_pC=_pL=_pP =0;
#endif
				ms_TreeNodeMemoryManager.Del((pNode_t)this);
				return pR1;
			}
			void ReMakeSiblingOrder(int idxStart) // this 노드부터 동생들의 형제 order를 새로 매긴다.
			{
				pNode_t pN = (pNode_t)this;
				for( ; pN ; pN = pN->_pR )
				{
					pN->iOrder = idxStart++;
				}
			}

			//---------------------------------------------------------------
			// 추가 함수.
			//----------------------------------------------------------------
			static pNode_t New()
			{
				pNode_t pN = ms_TreeNodeMemoryManager.New();
				pN->SetTreeInfo(0, 0 ,0, 0, 0 , 0);
				return pN;						// 삽입된 _pC의 포인터 리턴
			}
			pNode_t insertRight(){return NewR();	}
			pNode_t NewR()// return : this의 오른쪽에 새로운 노드를 삽입하고 포인터를 리턴
			{
				pNode_t pN = ms_TreeNodeMemoryManager.New();
				pN->SetTreeInfo(iOrder+1, 0 , _pR, (pNode_t)this, 0 , _pP );
				if(_pR)	_pR->_pL = pN;
				_pR = pN;
				pN->ReMakeSiblingOrder( iOrder+1);
				++_pP->iChild;
				//++m_iSize;						// 실제 사이즈 증가.
				return pN;						// 삽입된 _pC의 포인터 리턴
			}

			pNode_t insertLeft(){return NewL()	;}
			pNode_t NewL()// return : this의 왼쪽에 새로운 노드를 삽입하고 포인터를 리턴
			{
				pNode_t pN = ms_TreeNodeMemoryManager.New();
				//								iSibling , iOrder ,  _pR  ,                 _pL ,                _pC ,          _pP
				pN->SetTreeInfo(iOrder, 0 , (pNode_t)this, (pNode_t)_pL , (pNode_t)0 , (pNode_t)_pP );
				if(_pL)	_pL->_pR = pN;
				else
				{
					_pP->_pC = pN;
				}
				_pL = pN;
				ReMakeSiblingOrder( iOrder+1);
				++_pP->iChild;
				return pN;						// 삽입된 _pC의 포인터 리턴
			}

			//-----------------------------------------------------------------------------------
			// decs : this의 자식맨 앞에 노드를 하나 만들고 그 포인터를 리턴.
			pNode_t insertChildBegin(){ return NewCB();}
			pNode_t NewCB()
			{
				pNode_t pN = ms_TreeNodeMemoryManager.New();
				++iChild;
				pN->SetTreeInfo(0 , 0 , _pC, 0, 0 , (pNode_t) this );
				if(_pC)	_pC->_pL = pN;
				_pC = pN;
				pN->ReMakeSiblingOrder(0);
				return pN;						// 삽입된 _pC의 포인터 리턴
			}
			//-----------------------------------------------------------------------------------
			// 자식의 맨뒤에 노드를 추가하고 그노드를 리턴.
			pNode_t insertChildEnd(){return NewCE();}
			pNode_t NewCE() 
			{
				pNode_t pN = ms_TreeNodeMemoryManager.New(), pCE;
				pCE = GetChildEnd();
				pN->SetTreeInfo(iChild, 0 , 0 , pCE , 0 , (pNode_t)this );
				++iChild;
				if(_pC)	
				{
					pCE->_pR = pN;
				}
				else{
					_pC = pN;
				}
				return pN;						// 삽입된 _pC의 포인터 리턴
			}

			//---------------------------------------------------------------
			// tree 맴버변수
			//----------------------------------------------------------------
			pNode_t 
				_pR // 바로 아래의 동생  노드
				,_pL // 바로위의 형 노드 
				,_pC // 자식들의 시작 노드
				,_pP; // 부모노드

			size_t iOrder;  // 형제들중에서 자기의 순서.
			size_t iChild; // 자식의 총갯수
			size_t iHandle; // 실제메모리의 array 인덱스. 외부에서 수정 하면 안됨.

			//---------------------------------------------------------------
			// 일반 함수.
			//----------------------------------------------------------------
			void SetTreeInfo(int iSibling , int iChild,  pNode_t _pR ,pNode_t _pL , pNode_t _pC ,pNode_t _pP )
			{
				this->iChild = iChild;
				this->iOrder = iSibling;
				this->_pR = _pR;
				this->_pL = _pL;
				this->_pP = _pP;
				this->_pC = _pC;
			}

			pNode_t GetRoot()
			{		
				T* pN= static_cast<T*>(this);
				for(;pN;pN=pN->_pP )
					if(!pN->_pP)	
						break;
				return pN;
			}

			pNode_t GetParent(){ return _pP;	}
			pNode_t GetRight(){ return _pR;}
			pNode_t GetLeft(){return _pL;}
			pNode_t GetChild(){ return _pC;}
			pNode_t GetChildEnd() // 자식의 막내리턴.
			{
				pNode_t pN=_pC;
				if(!pN) return 0;
				for( ; pN->_pR; pN= pN->_pR)
					;
				return pN;
			}

			int GetOrder(){ return iOrder;}	
			int GetDepth()
			{
				int i=0;
				T* pN;
				for(pN=(T*)_pP ;pN ;pN=pN->_pP )
					++i;
				return i;
			}

			typedef pNode_t iterator;
			/*
			struct iterator 
			{ 
			public:
			iterator() {} 
			iterator(pNode_t p) : _Ptr(p) {} 
			iterator(iterator &p) : _Ptr(p._Ptr) {} 

			iterator & operator++()			
			{	
			_Ptr = _Ptr->GetRight(); 		
			return *this; 	
			} 
			iterator   operator++(int)		
			{ 
			iterator it = *this; 
			_Ptr = _Ptr->GetRight(); 
			return it; 
			} 
			iterator & operator--()			{ _Ptr = _Ptr->GetLeft(); return *this; } 
			iterator   operator--(int)		{ iterator it= *this; _Ptr = _Ptr->GetLeft(); return it; } 
			bool      operator==(const iterator &p) const { return _Ptr == p._Ptr; } 
			bool      operator!=(const iterator &p) const 
			{ 
			return !(_Ptr== p._Ptr); 
			} 

			pNode_t		operator ->() const		{ return _Ptr; } // ok!
			Node_t&		operator * ()	const	{ return *_Ptr; }
			pNode_t        GetNode() const { return _Ptr; } 

			//private: 
			pNode_t        _Ptr; 
			}; 

			iterator end()		{	return iterator((pNode_t)0);	}
			*/
			pNode_t end(){ return 0;}
			pNode_t begin()	{ return _pC;} // 해당노드의 첫뻔째 자식을 리턴.
			pNode_t rbegin() 	{ return GetChildEnd();	} // 맨마지막 노드
			size_t size() { return iChild;} // 자식의 갯수.
			bool empty(){ return (_pC==0 && _pL==0 && _pR==0 && _pP==0);	} 
			bool isRoot(){ return !_pP;} // 자기가 루트인지.
			bool isBegin(){ return !_pL;} // 형제들중에서 자기가 맞인지.
			bool isEnd(){return !_pR;} // 형제들중에서 자기가 막내인지.
			bool hasChild(){ return _pC!=0;} // 자식들이 있는가.
			bool hasSibling(){ return (_pL || _pR);	}

			template <class _Predicate>
				iterator find_if_child(_Predicate __pred)   // 바로 밑에 자식에 대해ㅣ....
			{
				pNode_t it = begin();
				for( ; it ; it=it->_pR ) 
				{
					if(__pred(it)) return it;
				}
				return 0;
			}

			template <class _Predicate>
				iterator _find_if(_Predicate __pred) // 모든 자식들에 대해....
			{
				pNode_t it = begin();
				for( ; it ; it=it->_pR ) 
				{
					if(__pred(it)) return it;
				}
				pNode_t itRet;
				for( it = begin() ; it ;  it=it->_pR)
				{
					itRet = it->_find_if(__pred);
					if( itRet) return itRet;
				}
				return 0;
			}

			template <class _Predicate>
				void for_each_child(_Predicate __pred)  // 바로 밑 자식에 대해 수행.
			{
				pNode_t it = begin();
				for( ; it ; it=it->_pR ) 
					__pred(it); 
			}

			template <class _Predicate>
				void _for_each(_Predicate __pred )  // 모든 자식들에 대해....
			{
				pNode_t it = begin();
				for( ; it ; it=it->_pR ) 
					__pred(it); 
				for( it = begin() ; it ;  it=it->_pR)
					it->_for_each(__pred);
			}

			pNode_t FindByOrder(uint idx)
			{
				if(idx>=iChild || idx < 0)
					return 0;
				pNode_t it  = begin();
				for( ; idx ; --idx) it= it->_pR;
				return it;
			}

			//---------------------------------------------------------------
			// detach() : 현제노드를 부모의 트리에서 연결을 끊는다. 
			// 부모및 형제들은 자신이 없다고 가정하여 트리구조를 재편함.
			//그러나 자신의 본래 tree정보는 가지고 있음. 
			// 이 정보를 이용해 나중에 redetach()로 다시 복귀될수 있다.
			// 참조되는 tree정보는 _pL , _pR , _pP->iChild , _pP->iOrder , _pP->_pC 이다.
			//----------------------------------------------------------------
			void detach()
			{
				if(!_pP) return;
				if(_pL) _pL->_pR = _pR;
				else _pP->_pC = _pR;

				if(_pR) _pR->_pL = _pL;

				--_pP->iChild;

				if(_pP->iChild >0)
					_pP->_pC->ReMakeSiblingOrder(0);
				else
				{
					_pP->_pC=0;
					_pP->iChild=0;
				}
			}

			// 현재 세팅된 _pR , _pL , _pP정보를 이용하여 attach시킴
			// 보통 detach후 사용한다.
			void redetach() 
			{
				if(!_pP) return;
				++_pP->iChild;
				if(_pL) 
				{
					_pR = _pL->_pR;
					if(_pR)
					{
						_pR->_pL = (pNode_t)this;
					}
					_pL->_pR = (pNode_t)this;
					_pL->ReMakeSiblingOrder(_pL->iOrder);
				}
				else if(_pR)
				{
					_pP->_pC = (pNode_t)this;
					_pR->_pL = (pNode_t)this;
					ReMakeSiblingOrder(0);
				}
				else
				{
					_pP->_pC = (pNode_t)this;
					iOrder=0;
				}

			}

			// pNew을 pNext다음에 추가한다. pNext가 0이면 this의 첫번째 자식으로 추가
			void attach(pNode_t pNew , pNode_t pNext=0) 
			{
				++iChild;
				if(pNext)
				{
					assert(pNext->_pP == this);
					pNew->_pR = pNext->_pR;
					pNew->_pL = pNext;
					pNew->_pP = pNext->_pP;
					pNext->_pR = pNew;
				}
				else
				{
					pNew->_pP = (pNode_t)this;
					pNew->_pL = 0;
					pNew->_pR = _pC;
					_pC = pNew;
				}
				_pC->ReMakeSiblingOrder(0);
			}

		};


		////////////////////////////////////////////////////////////////
		// T는 jTreeNode를 상속받은 클래스여야 한다.
		template<class T> class  jTree :public T
			////////////////////////////////////////////////////////////////
		{
		protected:
			//size_t m_iSize;		//모든 자식 노드들의 갯수.

		public:
			jTree()	{			SetTreeInfo(0,0,0,0,0,0);	}
			~jTree(){ }

		public:

		};//class jTree 

		template<class T> jMemoryStack<T> jTreeNode<T>::ms_TreeNodeMemoryManager; //1000개짜리 슬롯 10개.

	}//nHEADER
}

#endif //__jTreeNode_h__
