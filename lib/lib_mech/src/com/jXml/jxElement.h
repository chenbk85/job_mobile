 /* 
	filename:	jxDocument.h
	coder	:	Cho Wook Rea (4MLMman@hitel.net)(icq:74456993) 
	compiler:	vc++ 6.0
	date	:	2001-07-05오전 7:28:50
	title	:	 xml -> jxml변환용 클래스.

   
*/
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_jxElement_H__5FC9695D_DAD0_4426_96C7_E7B2A0069868__INCLUDED_)
#define AFX_jxElement_H__5FC9695D_DAD0_4426_96C7_E7B2A0069868__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning(disable : 4251)

#include "header/m_Manager.h"
#include "header/jTreeNode.h"
#include "base/jxVar.h"
#include "jxAttribute.h"

jLIST_TYPEDEF_map_typedef(tstring,void*,m_mapUserData);

namespace nMech
{
	namespace nXML
	{

		class jxDocument;
		typedef bool compare_func_t(jxVar&);
		//#define ELEMENT_TYPE_LIST
		class jxElement;
		typedef jxElement jxE;

		//****************************************************************
		class  jxElement : public jIElement,public nDataStruct::jTreeNode<jxElement> 
			//****************************************************************
		{
		public:
			jIE *FindByOrder(uint idx){ return nDataStruct::jTreeNode<jxElement>::FindByOrder(idx);}
			int GetOrder(){ return nDataStruct::jTreeNode<jxElement>::GetOrder();}	
			bool isRoot(){ return nDataStruct::jTreeNode<jxElement>::isRoot();}
			bool isBegin(){ return nDataStruct::jTreeNode<jxElement>::isBegin();} // 형제들중에서 자기가 맞인지.
			bool isEnd(){return nDataStruct::jTreeNode<jxElement>::isEnd();} // 형제들중에서 자기가 막내인지.
			jIE* GetRight(){ return nDataStruct::jTreeNode<jxElement>::GetRight();}
			jIE* GetLeft(){ return nDataStruct::jTreeNode<jxElement>::GetLeft();}
			jIE* GetParent(){ return nDataStruct::jTreeNode<jxElement>::GetParent();}
			jIE* GetRoot(){ return nDataStruct::jTreeNode<jxElement>::GetRoot();}
			size_t size(){ return nDataStruct::jTreeNode<jxElement>::size();}
			jIElement* begin(){return nDataStruct::jTreeNode<jxElement>::begin();}
			jIElement* end(){ return nDataStruct::jTreeNode<jxElement>::end();}

			void EraseAttr(nMech::StringID idAttr);
			void EraseAttr(cstr idAttr);

			jIE* Erase(){ return nDataStruct::jTreeNode<jxElement>::Erase();}
			void EraseChild(){ nDataStruct::jTreeNode<jxElement>::EraseChild();}
			uint32	GetHandle(){ return nDataStruct::jTreeNode<jxElement>::iHandle; }
			int GetDepth(){ return nDataStruct::jTreeNode<jxElement>::GetDepth();}
			void SetTreeInfo(int iSibling , int iChild,  jIE*_pR ,jIE*_pL , jIE*_pC ,jIE*_pP )
			{		nDataStruct::jTreeNode<jxElement>::SetTreeInfo(iSibling , iChild,(jxE*)_pR ,(jxE*)_pL , (jxE*)_pC ,(jxE*)_pP );	}

			void detach(){ nDataStruct::jTreeNode<jxElement>::detach();}
			void redetach(){nDataStruct::jTreeNode<jxElement>::redetach();}
			void attach(jIE* pNew , jIE* pNext=0){ nDataStruct::jTreeNode<jxElement>::attach((jxE*)pNew,(jxE*)pNext);}

			static uint _GetObjSize();
			static uint _GetSlotCount();

			void CopyTo(jIElement*);
			void CopyTo_Child(jIElement*pE);

			void Create();
			void Destroy()
			{
				m_Data.clear();
				m_AttMap.clear();
				m_pTagName=0;
				SAFE_DELETE(m_mapUserData);
			}


			jxVar			m_Data;
			StringID				m_iTagIndex;
			cstr		m_pTagName;
			jxAttributeList		m_AttMap;
			virtual jIAttributeList* GetAttributeList()	{		return &m_AttMap;	}

			friend class jxSchema;

		public:
			bool IsName(cstr sz){ return !_tcscmp(GetTagName() , sz);	}
			bool IsContents(cstr sz){ return !_tcscmp(Get_cstr(), sz);	}
			cstr Get_cstr() ;
			jIVar::EElementType GetType(){ return m_Data.GetType();}

			jIVar* GetVar(){return &m_Data;	}
			float* GetFloatP(){return GetVar()->GetFloatP();}
			float&	 GetFloat(int i){return GetVar()->GetFloat(i);}
			int*	 GetIntP(){return GetVar()->GetIntP();}
			int&	 GetInt(int i){return GetVar()->GetInt(i);}
			int &GetR(){ return GetVar()->GetInt(0);}
			int &GetG(){ return GetVar()->GetInt(1);}
			int &GetB(){ return GetVar()->GetInt(2);}
			int &GetA(){ return GetVar()->GetInt(3);}
			uint Get_ARGB()	{ return m_Data.Get_ARGB();}
			StringID			GetTagID(){ return m_iTagIndex;} // element이름에 대한 빠른 검색인댁스
			cstr	GetTagName(){	return m_pTagName;}	// element 이름
			virtual void ChangeTagName(cstr sz);

			RECT GetRect(){ return m_Data.GetRect();}

		public:
			void Init(cstr szName);
			jxElement();
			jxElement(cstr szName){Init(szName);}
			jxElement(jIE* pE)
			{
				Init(pE->GetTagName());
				pE->CopyTo(this);
			}
			virtual ~jxElement()		{	}

			//---------------------------------------------------------------
			jIElement* jxElement::FindElementDepth(cstr szElement);
			jIElement* jxElement::FindElementDepth(nMech::StringID idx);


			jIElement* jxElement::Find(cstr szElement);
			jIElement* jxElement::Find(nMech::StringID id);
			jIElement* jxElement::FindA(cstr szElement);
			jIElement* jxElement::FindA(nMech::StringID szElement);

			jIElement* jxElement::Find(cstr szElement,int iDepth);
			jIElement* jxElement::Find(nMech::StringID id,int iDepth);
			jIElement* jxElement::FindA(cstr szElement, int iDepth);
			jIElement* jxElement::FindA(nMech::StringID szElement, int iDepth);


			jIElement* FindByPath(cstr szElement);

			// 부모들중에서 해당 이름을 찾는다.
			jIElement* jxElement::FindFromParent(cstr szElement , jvector<jIElement*> *out=0); 
			jIElement* jxElement::FindFromParent(nMech::StringID iElement,jvector<jIElement*> *out=0);

			// 자신을 포함한 부모들의 Attribute중 해당 이름을 찾는다.
			jIElement* jxElement::GetAttrFromParent(cstr szElement , jIVar** pvOut, jvector<jIElement*> *out=0); 
			jIElement* jxElement::GetAttrFromParent(nMech::StringID iElement,jIVar** pvOut, jvector<jIElement*> *out=0);

			jIElement* FindByContents(nMech::StringID idxElement, jIVar::EElementType eT , void* v=0);
			jIElement* FindByContents(cstr szElement, jIVar::EElementType eT , void* v=0);
			jIElement* FindByFirstAttr(cstr szAttName, jIVar::EElementType eT , void* v=0,int iChildLevel =-1);
			jIElement* FindByFirstAttr(nMech::StringID szAttName, jIVar::EElementType eT , void* v=0,int iChildLevel =-1);


			jIElement* jxElement::FindByContents(nMech::StringID idxElement, jIVar* );
			jIElement* jxElement::FindByContents(cstr szElement, jIVar*);
			jIElement* jxElement::FindByFirstAttr(cstr szAttName, jIVar* v=0,int iChildLevel =-1);
			jIElement* jxElement::FindByFirstAttr(nMech::StringID szAttName, jIVar* v=0,int iChildLevel =-1);

			jIElement* jxElement::FindByDepth(int iChildLevel , cstr szElement);
			jIElement* jxElement::FindByDepth(int iChildLevel , nMech::StringID iElement);

			//---------------------------------------------------------------	
			// util 함수.
			//----------------------------------------------------------------

			void DebugIndent(int cnt,bool isInsertCR);
			void SaveIndent(jXmlFile* fp, int cnt =0);

			cstr GetAttr(cstr szA)	{		return m_AttMap.Find(szA);	}
			cstr GetAttr(nMech::StringID szA)	{		return m_AttMap.Find(szA);	}

			jIVar* GetAttrVar(cstr szA){return m_AttMap.FindVar(szA);}
			jIVar* GetAttrVar(nMech::StringID szA){return m_AttMap.FindVar(szA);}

			jIAttribute* GetAttrNode(cstr szA)
			{
				jxAttributeList::iterator it = m_AttMap.find(szA);
				if( it == m_AttMap.end()) return 0;
				return &(*it);
			}
			jIAttribute* GetAttrNode(nMech::StringID szA)
			{
				jxAttributeList::iterator it = m_AttMap.find(szA);
				if( it == m_AttMap.end()) return 0;
				return &(*it);
			}
			jIDocument* GetDoc();

			void jxElement::SaveXML(jXmlFile*fp);
			void jxElement::DebugPrint(bool isInsert_CR);

			//---------------------------------------------------------------	
			//xml데이타 추가용 함수
			//----------------------------------------------------------------
			void SetUserData(void* v)	
			{		
				m_Data.SetUserData(v);	
			}
			void* GetUserData()
			{ 
				return m_Data.GetUserData();	
			}

			void SetContents(cstr str, jxVar::EElementType type)	
			{		
				assert( type < jxVar::EDataType_MAX );		
				m_Data.InitValue(str,type);	
			}
			void Set_cstr(cstr sz);

			void MovePosition(int iOrder);// 형제들중에서 자신을 iOrder위치로 옮긴다. -1이면 맨마지막으로 이동
			jIElement* jxElement::InsertChild( cstr szTag, jIVar* v, int index=-1 );// 자식들의 해당 index에 자식을 추가
			jIElement* jxElement::InsertChildElement(cstr szTag, int index=-1)
			{
				jxVar v;
				v.m_eType = jxVar::ETelement;
				return InsertChild(szTag , &v ,index);
			}
			bool jxElement::InsertChild(jIE* peB,jIE* peInsert);

			jIVar* InsertAttr(cstr szTag){ return m_AttMap.Insert(szTag); }
			void DeleteAttr(cstr szAttrTag);

			cstr IsXmlFileNode();
			cstr IsFileNode(cstr szExt);

			void jxElement::writeChunk(nUtil::jMemoryChunk& mc);
			void jxElement::readChunk(nUtil::jMemoryChunk& mc);

			void writePacket(nUtil::jMemoryChunk& mc); // network packet용.
			void readPacket(nUtil::jMemoryChunk& mc);

			void jxElement::for_each(run_function_t *pFunc,void*);

			jIElement* jxElement::Persist( cstr szName, jxVar::EElementType etype, cstr szDefaultValue=0 );
			jIElement* jxElement::Persist( StringID szName, jxVar::EElementType etype, cstr szDefaultValue=0 );
			jIVar* jxElement::PersistAttr(cstr szName, jxVar::EElementType etype,cstr szDefaultValue=0);
			jIVar* jxElement::PersistAttr(StringID szName, jxVar::EElementType etype,cstr szDefaultValue=0);

#define _InitPersistElement_j333(X)		virtual jIElement* Persist( cstr szName, X defaultValue);\
	virtual jIElement* Persist( const StringID szName, X defaultValue);
#define _InitPersistAttr_j12342233(X)		virtual jIVar* PersistAttr( cstr szName, X defaultValue);\
	virtual jIVar* PersistAttr( const StringID szName, X defaultValue);

			_for_each_setter_type_jvar(_InitPersistElement_j333)
				_for_each_setter_type_jvar(_InitPersistAttr_j12342233)

				//---------------------------------------------------------------
				// xpath api
				//----------------------------------------------------------------
				jIDocument* XPathFromThis(jIE** ppE , jIAttribute** ppA );
			jIDocument* SXPathFromThis(jIE** ppE ,jIAttribute** ppA ); // 해당엘리먼트는 SXPATH노드이다.

			jIDocument*  XPathToString(TCHAR szOut[1024] , jIAttribute* pA=0 );
			jIDocument*  SXPathToString(TCHAR szOut[1024] , jIAttribute* pA=0 );
			void SetXPathContents(jIE* pE, jIAttribute* pA); // this에 pE,pA의 xpaht정보를 세팅한다.  contents=xpath, att::DOC=url
			void Lerp(jIE* pE1 , jIE* pE2, float fLerpRatio);


			static jIE* New()
			{
				jxE* pE = parent_t::New();
				pE->m_pTagName=0;
				return pE;
			}
			virtual void* jGetData(cstr szDataName, void*);
			
			void SetUserData(tcstr szTag,void* v);
			void* GetUserData(tcstr szTag);

			wcstr ToString();// ToString()을 호출한다음 항상 ToString_Free()를 콜해야한다.
			void  ToString_Free();

		private:
			m_mapUserData_t *m_mapUserData;
		}; // class jxElement

		//---------------------------------------------------------------
		// 함수자.
		//----------------------------------------------------------------
		struct _jxEqContents // element의 내용으로 찾을때.
		{	
			jxVar* m_pV;
			_jxEqContents(jxVar* pV): m_pV(pV){}
			bool operator()(jIE* e)
			{
				if(e->GetVar()->GetType()==m_pV->m_eType)
					return *(e->GetVar()->Base()) == *(m_pV->Base() );
				return false;
			}
		};


	}
}

#pragma warning(default: 4251)

#endif // !defined(AFX_jxElement_H__5FC9695D_DAD0_4426_96C7_E7B2A0069868__INCLUDED_)
