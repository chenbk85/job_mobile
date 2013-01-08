/* 
	filename:	jIElement.h
	coder	:	Cho Hyun Min (icandoit@wemade.com) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	2005-01-14 오후 3:32:00
	title	:	
*/


#ifndef __jIElement_h__
#define __jIElement_h__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000
#include "header\\m_stltag.h"
#include "interface/xml/jIVar.h"

namespace nMech
{
	namespace nUtil
	{
		struct jMemoryChunk;
	}
	namespace nXML
	{
		struct jIDocument;
		class jxElement;
		struct jIAttribute;
		struct jIAttributeList;
		typedef bool run_function_t(jIElement* pE, void*);
		//****************************************************************
		struct jIElement
			//****************************************************************
		{
		public:
			virtual ~jIElement(){}


			// element의 이름이 sz이면 true
			virtual bool IsName(tcstr sz)=0;

			// GetVar()가 EDcstr타입일때 내용이 sz이면 true
			virtual bool IsContents(tcstr sz)=0;

			// GetVar()가 EDcstr일때 스트링값리턴
			virtual tcstr Get_cstr() =0;
			virtual jIVar::EElementType GetType()=0;

			// 최상위 부모로부터의 깊이값 리턴.
			virtual int GetDepth()=0;

			// 소유하고 있는 jIVar객체 리턴. ETelement타입일때는 의미없는 값리턴.
			virtual jIVar* GetVar()=0;

			// element 이름에 대한 xml string 고유 id 리턴.
			virtual StringID			GetTagID()=0;
			// element의 이름 리턴.
			virtual tcstr	GetTagName()=0;

			//jIElement의 메모리 핸들리턴.
			virtual uint32	GetHandle()=0;

			// element의 이름을 바꿀때사용.
			virtual void ChangeTagName(tcstr sz)=0;

			//---------------------------------------------------------------
			virtual jIElement* Find(tcstr szElement)=0;
			virtual jIElement* Find(nMech::StringID id)=0;

			virtual jIElement* Find(tcstr szElement,int iDepth)=0;
			virtual jIElement* Find(nMech::StringID id,int iDepth)=0;

			// 검색실패시 assert(0)에러 발생시킴.
			virtual jIElement* FindA(tcstr szElement)=0;
			virtual jIElement* FindA(nMech::StringID szElement)=0;

			virtual jIElement* FindA(tcstr szElement, int iDepth)=0;
			virtual jIElement* FindA(nMech::StringID szElement, int iDepth)=0;

			/* 
			FindByPath("-2") - 자신을 기준으로 두 단계위의 부모
			FindByPath("-3:ABC:3:DFG") 자신을 기준으로 세단계위의 부모에서 <ABC>항목을 찾고
			거기서 ORDER가 3번째인 자식을 찾고 그다음 <DEF>를 찾고 그자식들을 리스팅
			FindByPath(""); 자기자신을 리턴
			*/
			virtual jIElement* FindByPath(tcstr szElement)=0;

			// 부모들중에서 해당 이름을 찾는다. out에는 찾은 조상까지의 history가 저장됨.
			virtual jIElement* FindFromParent(tcstr szElement , jvector<jIElement*> *out=0)=0; 
			virtual jIElement* FindFromParent(nMech::StringID iElement,jvector<jIElement*> *out=0)=0;

			// 자신을 포함한 부모들의 Attribute중 해당 이름을 찾는다.
			virtual jIElement* GetAttrFromParent(tcstr szElement , jIVar** pvOut, jvector<jIElement*> *out=0)=0; 
			virtual jIElement* GetAttrFromParent(nMech::StringID iElement,jIVar** pvOut, jvector<jIElement*> *out=0)=0;

			// 자식중에서 해당 자료형으로된 element를 찾는다. 
			// v에 해당 자료형(eT)으로 된 변수의 포인터를 넘겨주면 값을 비교하여 다르면 0을 리턴.
			// 자료형은 EDataType_SIMPLE_INT_END 과 EDcstr에대해서만 유효하다.
			// EDcstr일때는 :     tcstr sz = "asdf" 일때 v = sz;
			// EDint형일대는 :			int i = 23 ; v=&i;
			virtual jIElement* FindByContents(nMech::StringID idxElement, jIVar::EElementType eT , void* v=0)=0;
			virtual jIElement* FindByContents(tcstr szElement, jIVar::EElementType eT , void* v=0)=0;

			// 해당 속성이름과 자료형으로 element를 찾음 v는 값까지 비교하여 찾음. 
			//iChildLevel + 1 자손까지 검색.  iChildLevel == -1이면 모든 자손에 대해 검색.
			// iChildLevel == 0 이면 검색하지 않고 바로 리턴.
			// 1 이면 바로 밑의 자식에 대해서만 검색수행.
			virtual jIElement* FindByFirstAttr(tcstr szAttName, jIVar::EElementType eT , void* v=0,int iChildLevel =-1)=0;
			virtual jIElement* FindByFirstAttr(nMech::StringID szAttName, jIVar::EElementType eT , void* v=0,int iChildLevel =-1)=0;

			// 해당 jIVar와 자료인 elemetn를 찾음. 
			// 찾고자 하는 szElement가 일치하고 내용이 2번째인자와 일치하는 항목을 리턴
			// 찾는 값이 "NULL"  jxe(NULL)이면 두번째인자의 값이 일치하는 것을 찾음jIVar*
			virtual jIElement* FindByContents(nMech::StringID idxElement, jIVar* )=0;
			virtual jIElement* FindByContents(tcstr szElement, jIVar*)=0;

			// 
			virtual jIElement* FindByFirstAttr(tcstr szAttName, jIVar* v=0,int iChildLevel =-1)=0;
			virtual jIElement* FindByFirstAttr(nMech::StringID szAttName, jIVar* v=0,int iChildLevel =-1)=0;

			// Find()함수와 같으나 검색할 자손의 레벨을 지정함.
			// iChildLevel이 1이면 바로 밑의 자식에 대해서만 검색
			virtual jIElement* FindByDepth(int iChildLevel , tcstr szElement)=0;
			virtual jIElement* FindByDepth(int iChildLevel , nMech::StringID iElement)=0;

			virtual jIElement *FindByOrder(uint idx)=0;// 자식중에서 idx번째의 자식을 리턴.

			//---------------------------------------------------------------	
			// util 함수.
			//----------------------------------------------------------------
			virtual jIAttributeList* GetAttributeList()=0;

			// EDcstr형 속성의 값리턴.
			virtual tcstr GetAttr(tcstr szA)=0;
			virtual tcstr GetAttr(nMech::StringID szA)	=0;

			// 해당 이름의 속성의 jIVar객체 리턴.
			virtual jIVar* GetAttrVar(tcstr szA)=0;
			virtual jIVar* GetAttrVar(nMech::StringID szA)=0;
			virtual jIAttribute* GetAttrNode(tcstr szA)=0;
			virtual jIAttribute* GetAttrNode(nMech::StringID szA)=0;

			// 최상위 root== xml문서 객체 리턴.
			virtual jIDocument* GetDoc()=0;

			//---------------------------------------------------------------	
			//xml데이타 추가용 함수
			//----------------------------------------------------------------
			virtual void SetUserData(void* v)	=0;
			virtual void* GetUserData()=0;
			virtual void SetContents(tcstr str, jIVar::EElementType type)=0;
			virtual void Set_cstr(tcstr sz)=0;
			virtual void MovePosition(int iOrder)=0;// 형제들중에서 자신을 iOrder위치로 옮긴다. -1이면 맨마지막으로 이동


			virtual jIElement* InsertChild( tcstr szTag, jIVar* v, int index=-1 )=0;// 자식들의 해당 index에 자식을 추가
			virtual jIElement* InsertChildElement(tcstr szTag, int index=-1)=0;
			virtual bool InsertChild(jIE* peB,jIE* peI)=0;// this의 자식인 peB 다음에 peI를 집어 넣는다. assert(this==peB->GetParent()); 
														// peB가NULL이면 this의 맨처음자식으로 삽입.


			virtual jIVar* InsertAttr(tcstr szTag)=0; // jStringID에대해서는 구현 안함. 왜냐면 속도 느림.
			virtual void DeleteAttr(tcstr szAttrTag)=0;


			virtual void SetTreeInfo(int iSibling , int iChild,  jIE*_pR ,jIE*_pL , jIE*_pC ,jIE*_pP )=0;

			virtual void detach()=0;
			virtual void redetach()=0;
			virtual void attach(jIE* pNew , jIE* pNext=0)=0;

			// EDcstr에 대해 스트링이 파일을 나타내면 true;  <name>xml\\asdf.xml<name>의 형식이면 true
			virtual tcstr IsXmlFileNode()=0;
			virtual tcstr IsFileNode(tcstr szExt)=0;

			virtual jIElement* Persist( tcstr szName, jIVar::EElementType etype, tcstr szDefaultValue_By_string=0 )=0;
			virtual jIElement* Persist( StringID szName, jIVar::EElementType etype, tcstr szDefaultValue_By_string=0 )=0;
			virtual jIVar* PersistAttr(tcstr szName, jIVar::EElementType etype,tcstr szDefaultValue_By_string=0)=0;
			virtual jIVar* PersistAttr(StringID szName, jIVar::EElementType etype,tcstr szDefaultValue_By_string=0)=0;


#undef _InitPersistElement_j
#define _InitPersistElement_j(X)		virtual jIElement* Persist(const  StringID szName, X defaultValue)=0;\
	virtual jIElement* Persist( tcstr  szName, X defaultValue)=0;
#define _InitPersistAttr_j(X)				virtual jIVar* PersistAttr( const  StringID szName, X defaultValue)=0;\
	virtual jIVar* PersistAttr(  tcstr szName, X defaultValue)=0;
			_for_each_setter_type_jvar(_InitPersistElement_j)
			_for_each_setter_type_jvar(_InitPersistAttr_j)


			virtual void writeChunk(nUtil::jMemoryChunk& mc)=0;
			virtual void readChunk(nUtil::jMemoryChunk& mc)=0;

			virtual void writePacket(nUtil::jMemoryChunk& mc)=0; // network packet용.
			virtual void readPacket(nUtil::jMemoryChunk& mc)=0;

			virtual void* jGetData(tcstr szDataName, void*)=0;
			//---------------------------------------------------------------
			// xpath api
			//----------------------------------------------------------------


			// this가 가르키는 xml문서의 구조가 다음과 같을때
			// <XPATH DOC="xml\db.xml">type@1.2</XPATH>
			//
			//			jIA* pA=0; jIE* pE=0; 
			//			jID* pD = this->XPathFromThis(&pE, &pA);
			//			jID* pD1 = pE->XPathFromThis(buf, pA);
			//			assert(pD==pD1);
			//			assert(!strcmp(buf, this->Get_cstr());
			//
			virtual jIDocument* XPathFromThis(jIElement** ppE , jIAttribute** ppA )=0;
			// xpath가 자식의 order가 아니라 이름으로 지정.
			virtual jIDocument* SXPathFromThis(jIElement** ppE ,jIAttribute** ppA )=0; // 해당엘리먼트는 SXPATH노드이다.
			virtual jIDocument*  XPathToString(TCHAR szOut[1024] , jIAttribute* pA=0 )=0;
			virtual jIDocument*  SXPathToString(TCHAR szOut[1024] , jIAttribute* pA=0 )=0;

			// this에 pE,pA의 xpaht정보를 세팅한다.  contents=xpath, att::DOC=url
			// this의 문서 구조는 <XPATH DOC="xml\db.xml">type@1.2</XPATH>이거나
			//											<SXPATH DOC="xml\db.xml">type@name1.name2</SXPATH>의 형태이다.
			virtual void SetXPathContents(jIElement* pE, jIAttribute* pA)=0; 

			virtual int GetOrder()=0;// 자신이 형제중에서 몇번째인지 리턴.
			virtual bool isRoot()=0;// 자기가 root이면 true
			virtual bool isBegin()=0;// 자기가 형제중 맞이면 true
			virtual bool isEnd()=0;// 자기가 막내이면 true; 
			virtual jIElement* GetRight()=0;// 자신의 바로 밑 형제를 리턴.
			virtual jIElement* GetLeft()=0;// 자신의 바로위 형을 리턴.
			virtual jIElement* GetParent()=0;// 자신의 부모 
			virtual jIElement* begin()=0;// 자식중에서 첫 자식 리턴.
			virtual jIElement* end()=0;// 자식의 맨 막내 자식 리턴.
			virtual size_t size()=0;// 자식의 수를 리턴.
			virtual jIElement* GetRoot()=0;
			virtual void CopyTo(jIElement*pe)=0;
			virtual void CopyTo_Child(jIElement*pe)=0;

			virtual void EraseAttr(nMech::StringID idAttr)=0;
			virtual void EraseAttr(tcstr idAttr)=0;
			virtual jIElement* Erase()=0;
			virtual void EraseChild()=0;
			virtual void Lerp(jIE* pE1 , jIE* pE2, float fLerpRatio)=0;

			virtual void for_each(run_function_t *pFunc, void* pFunc_Arg)=0;

			template <class _Predicate>
				jIE* find_if_child(_Predicate &__pred)   // 바로 밑에 자식에 대해ㅣ....
			{
				jIE* it = begin();
				for( ; it ; it=it->GetRight() ) 
				{
					if(__pred(it)) return it;
				}
				return 0;
			}

			template <class _Predicate>
				jIE* find_if(_Predicate &__pred) // 모든 자식들에 대해....
			{
				jIE* it = begin();
				for( ; it ; it=it->GetRight() ) 
				{
					if(__pred(it)) return it;
				}
				jIE* itRet;
				for( it = begin() ; it ;  it=it->GetRight())
				{
					itRet = it->find_if(__pred);
					if( itRet) return itRet;
				}
				return 0;
			}

			template <class _Predicate>
				void for_each_child(_Predicate &__pred)  // 바로 밑 자식에 대해 수행.
			{
				jIE* it = begin();
				for( ; it ; it=it->GetRight() ) 
					__pred(it); 
			}

			template <class _Predicate>
			void for_each(_Predicate &__pred )  // 모든 자식들에 대해.... 넓이 우선 실행
			{
				jIE* it;
				for( it = begin(); it ; it=it->GetRight() ) 
					__pred(it); 
				for( it = begin() ; it ;  it=it->GetRight())
					it->for_each(__pred);
			}

			template <class _Predicate>
			void for_each_depth(_Predicate &__pred )  // 모든 자식들에 대해.... 깊이 우선 실행
			{
				jIE* it;
				for( it = begin() ; it ; it=it->GetRight() ) 
				{
					__pred(it); 
					it->for_each_depth(__pred);
				}
			}

			enum EReturnType
			{
				eCONTINUE,//계속 for_each_if실행
				eSKIP_CHILD,// 현제노드의 자식들에 대한 for_each_if를 취소하고 리턴
				eEXIT, // for_each_if를 전체 실행 취소.
			};

			template <class _Predicate>	// EReturnType 의 조건에 따라 for_each를 실행할수 있다.
			EReturnType for_each_if(_Predicate &__pred )  // 모든 자식들에 대해.... 깊이 우선 실행
			{
				jIE* it;
				EReturnType eType = eCONTINUE;
				for( it = begin() ; it ; it=it->GetRight() ) 
				{
					eType = __pred(it); 
					switch(eType)
					{
					case eCONTINUE:
						eType = it->for_each_if(__pred);
						continue;
					case eSKIP_CHILD:
						continue;
					case eEXIT:
						return eEXIT;
					}
				}
				return eType;
			}


			virtual void DebugPrint(bool isInsert_CR)=0;
			virtual wcstr ToString()=0;// ToString()을 호출한다음 항상 ToString_Free()를 콜해야한다.
			virtual void  ToString_Free()=0;



			//_Predicate로 넘기는 인자는 struct jIA* 이다.
			template <class _Predicate>
				void for_each_attr(_Predicate &__pred)
			{
				jIAttributeList* pList = GetAttributeList();
				jIAttributeList::iterator it = pList->begin(), ie = pList->end();
				for( ; it!=ie; ++it)	__pred(it);
			}
			virtual void SetUserData(tcstr szTag,void* v)	=0;
			virtual void* GetUserData(tcstr szTag)=0;

		}; // class jIElement
	}//nXML
}


#define xGET_USER_DATA(TYPE,pE) (TYPE*)pE->GetUserData(jS(TYPE))

#endif //__jIElement_h__
