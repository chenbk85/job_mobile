/* 
	filename:	jIElement.h
	coder	:	Cho Hyun Min (icandoit@wemade.com) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	2005-01-14 ���� 3:32:00
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


			// element�� �̸��� sz�̸� true
			virtual bool IsName(tcstr sz)=0;

			// GetVar()�� EDcstrŸ���϶� ������ sz�̸� true
			virtual bool IsContents(tcstr sz)=0;

			// GetVar()�� EDcstr�϶� ��Ʈ��������
			virtual tcstr Get_cstr() =0;
			virtual jIVar::EElementType GetType()=0;

			// �ֻ��� �θ�κ����� ���̰� ����.
			virtual int GetDepth()=0;

			// �����ϰ� �ִ� jIVar��ü ����. ETelementŸ���϶��� �ǹ̾��� ������.
			virtual jIVar* GetVar()=0;

			// element �̸��� ���� xml string ���� id ����.
			virtual StringID			GetTagID()=0;
			// element�� �̸� ����.
			virtual tcstr	GetTagName()=0;

			//jIElement�� �޸� �ڵ鸮��.
			virtual uint32	GetHandle()=0;

			// element�� �̸��� �ٲܶ����.
			virtual void ChangeTagName(tcstr sz)=0;

			//---------------------------------------------------------------
			virtual jIElement* Find(tcstr szElement)=0;
			virtual jIElement* Find(nMech::StringID id)=0;

			virtual jIElement* Find(tcstr szElement,int iDepth)=0;
			virtual jIElement* Find(nMech::StringID id,int iDepth)=0;

			// �˻����н� assert(0)���� �߻���Ŵ.
			virtual jIElement* FindA(tcstr szElement)=0;
			virtual jIElement* FindA(nMech::StringID szElement)=0;

			virtual jIElement* FindA(tcstr szElement, int iDepth)=0;
			virtual jIElement* FindA(nMech::StringID szElement, int iDepth)=0;

			/* 
			FindByPath("-2") - �ڽ��� �������� �� �ܰ����� �θ�
			FindByPath("-3:ABC:3:DFG") �ڽ��� �������� ���ܰ����� �θ𿡼� <ABC>�׸��� ã��
			�ű⼭ ORDER�� 3��°�� �ڽ��� ã�� �״��� <DEF>�� ã�� ���ڽĵ��� ������
			FindByPath(""); �ڱ��ڽ��� ����
			*/
			virtual jIElement* FindByPath(tcstr szElement)=0;

			// �θ���߿��� �ش� �̸��� ã�´�. out���� ã�� ��������� history�� �����.
			virtual jIElement* FindFromParent(tcstr szElement , jvector<jIElement*> *out=0)=0; 
			virtual jIElement* FindFromParent(nMech::StringID iElement,jvector<jIElement*> *out=0)=0;

			// �ڽ��� ������ �θ���� Attribute�� �ش� �̸��� ã�´�.
			virtual jIElement* GetAttrFromParent(tcstr szElement , jIVar** pvOut, jvector<jIElement*> *out=0)=0; 
			virtual jIElement* GetAttrFromParent(nMech::StringID iElement,jIVar** pvOut, jvector<jIElement*> *out=0)=0;

			// �ڽ��߿��� �ش� �ڷ������ε� element�� ã�´�. 
			// v�� �ش� �ڷ���(eT)���� �� ������ �����͸� �Ѱ��ָ� ���� ���Ͽ� �ٸ��� 0�� ����.
			// �ڷ����� EDataType_SIMPLE_INT_END �� EDcstr�����ؼ��� ��ȿ�ϴ�.
			// EDcstr�϶��� :     tcstr sz = "asdf" �϶� v = sz;
			// EDint���ϴ�� :			int i = 23 ; v=&i;
			virtual jIElement* FindByContents(nMech::StringID idxElement, jIVar::EElementType eT , void* v=0)=0;
			virtual jIElement* FindByContents(tcstr szElement, jIVar::EElementType eT , void* v=0)=0;

			// �ش� �Ӽ��̸��� �ڷ������� element�� ã�� v�� ������ ���Ͽ� ã��. 
			//iChildLevel + 1 �ڼձ��� �˻�.  iChildLevel == -1�̸� ��� �ڼտ� ���� �˻�.
			// iChildLevel == 0 �̸� �˻����� �ʰ� �ٷ� ����.
			// 1 �̸� �ٷ� ���� �ڽĿ� ���ؼ��� �˻�����.
			virtual jIElement* FindByFirstAttr(tcstr szAttName, jIVar::EElementType eT , void* v=0,int iChildLevel =-1)=0;
			virtual jIElement* FindByFirstAttr(nMech::StringID szAttName, jIVar::EElementType eT , void* v=0,int iChildLevel =-1)=0;

			// �ش� jIVar�� �ڷ��� elemetn�� ã��. 
			// ã���� �ϴ� szElement�� ��ġ�ϰ� ������ 2��°���ڿ� ��ġ�ϴ� �׸��� ����
			// ã�� ���� "NULL"  jxe(NULL)�̸� �ι�°������ ���� ��ġ�ϴ� ���� ã��jIVar*
			virtual jIElement* FindByContents(nMech::StringID idxElement, jIVar* )=0;
			virtual jIElement* FindByContents(tcstr szElement, jIVar*)=0;

			// 
			virtual jIElement* FindByFirstAttr(tcstr szAttName, jIVar* v=0,int iChildLevel =-1)=0;
			virtual jIElement* FindByFirstAttr(nMech::StringID szAttName, jIVar* v=0,int iChildLevel =-1)=0;

			// Find()�Լ��� ������ �˻��� �ڼ��� ������ ������.
			// iChildLevel�� 1�̸� �ٷ� ���� �ڽĿ� ���ؼ��� �˻�
			virtual jIElement* FindByDepth(int iChildLevel , tcstr szElement)=0;
			virtual jIElement* FindByDepth(int iChildLevel , nMech::StringID iElement)=0;

			virtual jIElement *FindByOrder(uint idx)=0;// �ڽ��߿��� idx��°�� �ڽ��� ����.

			//---------------------------------------------------------------	
			// util �Լ�.
			//----------------------------------------------------------------
			virtual jIAttributeList* GetAttributeList()=0;

			// EDcstr�� �Ӽ��� ������.
			virtual tcstr GetAttr(tcstr szA)=0;
			virtual tcstr GetAttr(nMech::StringID szA)	=0;

			// �ش� �̸��� �Ӽ��� jIVar��ü ����.
			virtual jIVar* GetAttrVar(tcstr szA)=0;
			virtual jIVar* GetAttrVar(nMech::StringID szA)=0;
			virtual jIAttribute* GetAttrNode(tcstr szA)=0;
			virtual jIAttribute* GetAttrNode(nMech::StringID szA)=0;

			// �ֻ��� root== xml���� ��ü ����.
			virtual jIDocument* GetDoc()=0;

			//---------------------------------------------------------------	
			//xml����Ÿ �߰��� �Լ�
			//----------------------------------------------------------------
			virtual void SetUserData(void* v)	=0;
			virtual void* GetUserData()=0;
			virtual void SetContents(tcstr str, jIVar::EElementType type)=0;
			virtual void Set_cstr(tcstr sz)=0;
			virtual void MovePosition(int iOrder)=0;// �������߿��� �ڽ��� iOrder��ġ�� �ű��. -1�̸� �Ǹ��������� �̵�


			virtual jIElement* InsertChild( tcstr szTag, jIVar* v, int index=-1 )=0;// �ڽĵ��� �ش� index�� �ڽ��� �߰�
			virtual jIElement* InsertChildElement(tcstr szTag, int index=-1)=0;
			virtual bool InsertChild(jIE* peB,jIE* peI)=0;// this�� �ڽ��� peB ������ peI�� ���� �ִ´�. assert(this==peB->GetParent()); 
														// peB��NULL�̸� this�� ��ó���ڽ����� ����.


			virtual jIVar* InsertAttr(tcstr szTag)=0; // jStringID�����ؼ��� ���� ����. �ֳĸ� �ӵ� ����.
			virtual void DeleteAttr(tcstr szAttrTag)=0;


			virtual void SetTreeInfo(int iSibling , int iChild,  jIE*_pR ,jIE*_pL , jIE*_pC ,jIE*_pP )=0;

			virtual void detach()=0;
			virtual void redetach()=0;
			virtual void attach(jIE* pNew , jIE* pNext=0)=0;

			// EDcstr�� ���� ��Ʈ���� ������ ��Ÿ���� true;  <name>xml\\asdf.xml<name>�� �����̸� true
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

			virtual void writePacket(nUtil::jMemoryChunk& mc)=0; // network packet��.
			virtual void readPacket(nUtil::jMemoryChunk& mc)=0;

			virtual void* jGetData(tcstr szDataName, void*)=0;
			//---------------------------------------------------------------
			// xpath api
			//----------------------------------------------------------------


			// this�� ����Ű�� xml������ ������ ������ ������
			// <XPATH DOC="xml\db.xml">type@1.2</XPATH>
			//
			//			jIA* pA=0; jIE* pE=0; 
			//			jID* pD = this->XPathFromThis(&pE, &pA);
			//			jID* pD1 = pE->XPathFromThis(buf, pA);
			//			assert(pD==pD1);
			//			assert(!strcmp(buf, this->Get_cstr());
			//
			virtual jIDocument* XPathFromThis(jIElement** ppE , jIAttribute** ppA )=0;
			// xpath�� �ڽ��� order�� �ƴ϶� �̸����� ����.
			virtual jIDocument* SXPathFromThis(jIElement** ppE ,jIAttribute** ppA )=0; // �ش翤����Ʈ�� SXPATH����̴�.
			virtual jIDocument*  XPathToString(TCHAR szOut[1024] , jIAttribute* pA=0 )=0;
			virtual jIDocument*  SXPathToString(TCHAR szOut[1024] , jIAttribute* pA=0 )=0;

			// this�� pE,pA�� xpaht������ �����Ѵ�.  contents=xpath, att::DOC=url
			// this�� ���� ������ <XPATH DOC="xml\db.xml">type@1.2</XPATH>�̰ų�
			//											<SXPATH DOC="xml\db.xml">type@name1.name2</SXPATH>�� �����̴�.
			virtual void SetXPathContents(jIElement* pE, jIAttribute* pA)=0; 

			virtual int GetOrder()=0;// �ڽ��� �����߿��� ���°���� ����.
			virtual bool isRoot()=0;// �ڱⰡ root�̸� true
			virtual bool isBegin()=0;// �ڱⰡ ������ ���̸� true
			virtual bool isEnd()=0;// �ڱⰡ �����̸� true; 
			virtual jIElement* GetRight()=0;// �ڽ��� �ٷ� �� ������ ����.
			virtual jIElement* GetLeft()=0;// �ڽ��� �ٷ��� ���� ����.
			virtual jIElement* GetParent()=0;// �ڽ��� �θ� 
			virtual jIElement* begin()=0;// �ڽ��߿��� ù �ڽ� ����.
			virtual jIElement* end()=0;// �ڽ��� �� ���� �ڽ� ����.
			virtual size_t size()=0;// �ڽ��� ���� ����.
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
				jIE* find_if_child(_Predicate &__pred)   // �ٷ� �ؿ� �ڽĿ� ���ؤ�....
			{
				jIE* it = begin();
				for( ; it ; it=it->GetRight() ) 
				{
					if(__pred(it)) return it;
				}
				return 0;
			}

			template <class _Predicate>
				jIE* find_if(_Predicate &__pred) // ��� �ڽĵ鿡 ����....
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
				void for_each_child(_Predicate &__pred)  // �ٷ� �� �ڽĿ� ���� ����.
			{
				jIE* it = begin();
				for( ; it ; it=it->GetRight() ) 
					__pred(it); 
			}

			template <class _Predicate>
			void for_each(_Predicate &__pred )  // ��� �ڽĵ鿡 ����.... ���� �켱 ����
			{
				jIE* it;
				for( it = begin(); it ; it=it->GetRight() ) 
					__pred(it); 
				for( it = begin() ; it ;  it=it->GetRight())
					it->for_each(__pred);
			}

			template <class _Predicate>
			void for_each_depth(_Predicate &__pred )  // ��� �ڽĵ鿡 ����.... ���� �켱 ����
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
				eCONTINUE,//��� for_each_if����
				eSKIP_CHILD,// ��������� �ڽĵ鿡 ���� for_each_if�� ����ϰ� ����
				eEXIT, // for_each_if�� ��ü ���� ���.
			};

			template <class _Predicate>	// EReturnType �� ���ǿ� ���� for_each�� �����Ҽ� �ִ�.
			EReturnType for_each_if(_Predicate &__pred )  // ��� �ڽĵ鿡 ����.... ���� �켱 ����
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
			virtual wcstr ToString()=0;// ToString()�� ȣ���Ѵ��� �׻� ToString_Free()�� ���ؾ��Ѵ�.
			virtual void  ToString_Free()=0;



			//_Predicate�� �ѱ�� ���ڴ� struct jIA* �̴�.
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
