/* 
	filename:	jTreeNode.h
	coder	:	Cho Wook Rea (chowookrea@hotmail)(icq:74456993) 
	comp.	:	-MAEUMNET-
	compiler:	vc++ 6.0
	date	:	2003-10-22���� 4:47:23
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
			// �޸𸮰�����.
			//----------------------------------------------------------------
			static jMemoryStack<T>  ms_TreeNodeMemoryManager;

			//---------------------------------------------------------------
			// �ʱ�ȭ �Լ�.							
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
			// ���� �Լ�.
			//----------------------------------------------------------------
		protected:	pNode_t _EraseFast() 
									// Erase()���� ������ ó����. EraseChild()������ ȣ���. 
									//�ڽ��� �ڽĵ��� �����ϰ� �ڽŵ� ������. 
									// �ڽ��� ���� ��带 �����Ѵ�.
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

			pNode_t Erase() // �ڽ��� �ڽĵ��� ��� �����ϰ� �ڽŵ� ���� ��Ŵ. �ڽ��� ��������node(right)�� ����.
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
					_pL->_pR = pR1;// �ڱ��� �ٷ� �������� �ڱ��� ������带 ���.
				}
				else
				{
					_pP->_pC = pR1;// �ڱⰡ ������ ���̸� �θ𿡰� �ڱ��� ������ ���̶�� �˸���
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
			void ReMakeSiblingOrder(int idxStart) // this ������ �������� ���� order�� ���� �ű��.
			{
				pNode_t pN = (pNode_t)this;
				for( ; pN ; pN = pN->_pR )
				{
					pN->iOrder = idxStart++;
				}
			}

			//---------------------------------------------------------------
			// �߰� �Լ�.
			//----------------------------------------------------------------
			static pNode_t New()
			{
				pNode_t pN = ms_TreeNodeMemoryManager.New();
				pN->SetTreeInfo(0, 0 ,0, 0, 0 , 0);
				return pN;						// ���Ե� _pC�� ������ ����
			}
			pNode_t insertRight(){return NewR();	}
			pNode_t NewR()// return : this�� �����ʿ� ���ο� ��带 �����ϰ� �����͸� ����
			{
				pNode_t pN = ms_TreeNodeMemoryManager.New();
				pN->SetTreeInfo(iOrder+1, 0 , _pR, (pNode_t)this, 0 , _pP );
				if(_pR)	_pR->_pL = pN;
				_pR = pN;
				pN->ReMakeSiblingOrder( iOrder+1);
				++_pP->iChild;
				//++m_iSize;						// ���� ������ ����.
				return pN;						// ���Ե� _pC�� ������ ����
			}

			pNode_t insertLeft(){return NewL()	;}
			pNode_t NewL()// return : this�� ���ʿ� ���ο� ��带 �����ϰ� �����͸� ����
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
				return pN;						// ���Ե� _pC�� ������ ����
			}

			//-----------------------------------------------------------------------------------
			// decs : this�� �ڽĸ� �տ� ��带 �ϳ� ����� �� �����͸� ����.
			pNode_t insertChildBegin(){ return NewCB();}
			pNode_t NewCB()
			{
				pNode_t pN = ms_TreeNodeMemoryManager.New();
				++iChild;
				pN->SetTreeInfo(0 , 0 , _pC, 0, 0 , (pNode_t) this );
				if(_pC)	_pC->_pL = pN;
				_pC = pN;
				pN->ReMakeSiblingOrder(0);
				return pN;						// ���Ե� _pC�� ������ ����
			}
			//-----------------------------------------------------------------------------------
			// �ڽ��� �ǵڿ� ��带 �߰��ϰ� �׳�带 ����.
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
				return pN;						// ���Ե� _pC�� ������ ����
			}

			//---------------------------------------------------------------
			// tree �ɹ�����
			//----------------------------------------------------------------
			pNode_t 
				_pR // �ٷ� �Ʒ��� ����  ���
				,_pL // �ٷ����� �� ��� 
				,_pC // �ڽĵ��� ���� ���
				,_pP; // �θ���

			size_t iOrder;  // �������߿��� �ڱ��� ����.
			size_t iChild; // �ڽ��� �Ѱ���
			size_t iHandle; // �����޸��� array �ε���. �ܺο��� ���� �ϸ� �ȵ�.

			//---------------------------------------------------------------
			// �Ϲ� �Լ�.
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
			pNode_t GetChildEnd() // �ڽ��� ��������.
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
			pNode_t begin()	{ return _pC;} // �ش����� ù��° �ڽ��� ����.
			pNode_t rbegin() 	{ return GetChildEnd();	} // �Ǹ����� ���
			size_t size() { return iChild;} // �ڽ��� ����.
			bool empty(){ return (_pC==0 && _pL==0 && _pR==0 && _pP==0);	} 
			bool isRoot(){ return !_pP;} // �ڱⰡ ��Ʈ����.
			bool isBegin(){ return !_pL;} // �������߿��� �ڱⰡ ������.
			bool isEnd(){return !_pR;} // �������߿��� �ڱⰡ ��������.
			bool hasChild(){ return _pC!=0;} // �ڽĵ��� �ִ°�.
			bool hasSibling(){ return (_pL || _pR);	}

			template <class _Predicate>
				iterator find_if_child(_Predicate __pred)   // �ٷ� �ؿ� �ڽĿ� ���ؤ�....
			{
				pNode_t it = begin();
				for( ; it ; it=it->_pR ) 
				{
					if(__pred(it)) return it;
				}
				return 0;
			}

			template <class _Predicate>
				iterator _find_if(_Predicate __pred) // ��� �ڽĵ鿡 ����....
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
				void for_each_child(_Predicate __pred)  // �ٷ� �� �ڽĿ� ���� ����.
			{
				pNode_t it = begin();
				for( ; it ; it=it->_pR ) 
					__pred(it); 
			}

			template <class _Predicate>
				void _for_each(_Predicate __pred )  // ��� �ڽĵ鿡 ����....
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
			// detach() : ������带 �θ��� Ʈ������ ������ ���´�. 
			// �θ�� �������� �ڽ��� ���ٰ� �����Ͽ� Ʈ�������� ������.
			//�׷��� �ڽ��� ���� tree������ ������ ����. 
			// �� ������ �̿��� ���߿� redetach()�� �ٽ� ���͵ɼ� �ִ�.
			// �����Ǵ� tree������ _pL , _pR , _pP->iChild , _pP->iOrder , _pP->_pC �̴�.
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

			// ���� ���õ� _pR , _pL , _pP������ �̿��Ͽ� attach��Ŵ
			// ���� detach�� ����Ѵ�.
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

			// pNew�� pNext������ �߰��Ѵ�. pNext�� 0�̸� this�� ù��° �ڽ����� �߰�
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
		// T�� jTreeNode�� ��ӹ��� Ŭ�������� �Ѵ�.
		template<class T> class  jTree :public T
			////////////////////////////////////////////////////////////////
		{
		protected:
			//size_t m_iSize;		//��� �ڽ� ������ ����.

		public:
			jTree()	{			SetTreeInfo(0,0,0,0,0,0);	}
			~jTree(){ }

		public:

		};//class jTree 

		template<class T> jMemoryStack<T> jTreeNode<T>::ms_TreeNodeMemoryManager; //1000��¥�� ���� 10��.

	}//nHEADER
}

#endif //__jTreeNode_h__
