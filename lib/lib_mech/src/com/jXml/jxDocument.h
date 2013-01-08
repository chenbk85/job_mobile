/* 
	filename:	jxDocument.h
	coder	:	Cho Wook Rea (4MLMman@hitel.net)(icq:74456993) 
	compiler:	vc++ 6.0
	date	:	2001-07-05오전 7:28:50
	title	:	 xml -> jxml변환용 클래스.
*/
//

//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JXDOCUMENT_H__5FC9695D_DAD0_4426_96C7_E7B2A0069868__INCLUDED_)
#define AFX_JXDOCUMENT_H__5FC9695D_DAD0_4426_96C7_E7B2A0069868__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "header\\m_Manager.h"
#include "header\\jTreeNode.h"
#include "interface/xml/jIDocument.h"
#include "jxElement.h"

namespace nMech
{
	namespace nXML
	{

		//---------------------------------------------------------------
		class jCommentManager : public nDataStruct::TMapTag< jIE* , jvector<std::tstring> >
			//----------------------------------------------------------------
		{
		public:
			struct _FindCmt{
				jIE* pE;
				_FindCmt(jIE* pe): pE(pe){}
				bool operator()(iterator it) const { return it->first == pE	;}
			};
			void SetComment(jIE* pE , cstr sz)
			{
				m_aObj[pE].clear();
				m_aObj[pE].push_back(sz);
			}
			jvector<std::tstring>* Find(jIE* pE)
			{ 
				if(!pE->GetTagName()) return 0;
				iterator it =find_if(_FindCmt(pE));
				if(it!=m_aObj.end())
					return &it->second;
				else 
					return 0;
			}
		}	;

		//#pragma warning(disable : 4251)
		//****************************************************************
		class  jxDocument  : public jxElement ,public jIDocument
			//****************************************************************
		{
			jINTERFACE_HEADER(jIDocument);

		public:
			union{
				struct {
					int16	 m_iRef;
					int16 m_iCloneRef;
				};
				int m_REF;
			};
			uint					m_iSize;// 전체 트리노드 사이즈.
#pragma warning(disable : 4251)
			tstring	 			m_szUrl; // 파일 이름.
			tstring				m_szCloneUrl;// 클론파일을 저장시 경로저장
			tstring				m_szPath;
			jIE* m_peParentLink;
#pragma warning(default : 4251)
			//fname_t		m_szVer;
			void AddRef(){++m_iRef;}

			jxDocument();
			virtual ~jxDocument()
			{ 
			} // ~jTree()에서 clear()를 반드시 콜해야함.
			bool UnLoad();
			bool jxDocument::LoadjXML(cstr szURL);
			jCommentManager m_jCommentManager;
			int m_iFlag;
			jSET_FLAG(_IsMemoryDoc, jBIT_0);

			friend class jXml;

		private:
			bool check_DONTSAVE()
			{
				jIVar* pV = GetAttrVar(TEXT("SAVE_TYPE"));
				if(pV && pV->IsContents(_T("DONTSAVE")) )
					return true;
				return false;
			}

		}; //class jxDocument  : public jxElement

		typedef jxDocument jxD;


	}
}


//#pragma warning(default : 4251)

#endif // !defined(AFX_JXDOCUMENTa_H__5FC9695D_DAD0_4426_96C7_E7B2A0069868__INCLUDED_)


