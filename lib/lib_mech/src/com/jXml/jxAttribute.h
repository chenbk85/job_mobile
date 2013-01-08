 /* 
	filename:	jxDocument.h
	coder	:	Cho Wook Rea (4MLMman@hitel.net)(icq:74456993) 
	compiler:	vc++ 6.0
	date	:	2001-07-05오전 7:28:50
	title	:	 xml -> jxml변환용 클래스.
*/
// jxAttributeList.h: interface for the jxDocument class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_jxAttribute_H__5FC9695D_DAD0_4426_96C7_E7B2A0069868__INCLUDED_)
#define AFX_jxAttribute_H__5FC9695D_DAD0_4426_96C7_E7B2A0069868__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "header\\m_Manager.h"
#include "base/jxVar.h"

namespace nMech
{
	namespace nUtil
	{
		struct jMemoryChunk;
	}
	namespace nXML
	{

		//---------------------------------------------------------------
		class jxAttribute : public jIAttribute , public nDataStruct::yVectorNode<jxAttribute> 
			//----------------------------------------------------------------
		{
		public:
			jxAttribute* Base() { return this;}
			jDECLEAR_YVECTOR_MANAGER(jxAttribute );

			jxVar			m_Data;
			StringID		m_iTagIndex;
			cstr		m_pTagName;
			jIVar* GetVar(){ return &m_Data; 	}
			StringID GetTagID(){ return m_iTagIndex; }
			cstr	GetTagName(){ return m_pTagName; 	}
			bool IsName(cstr sz){ return !jt_strcmp(m_pTagName, sz);}
			void ChangeTagName(cstr sz);

			uint GetHandle(){ return iHandle;}
			void CopyFrom(const jxAttribute& xN)
			{
				m_Data = xN.m_Data;
				m_iTagIndex = xN.m_iTagIndex;
				m_pTagName = xN.m_pTagName;
			}
			void Create(){m_Data.clear();}
			void Destroy(){		m_Data.clear(); }

			virtual jIAttribute* GetRight()
			{
				return _pR;
			}
			virtual jIAttribute* GetLeft()
			{
				return _pL;
			}

		};

		//****************************************************************
		class  jxAttributeList : public jIAttributeList
			//****************************************************************
		{
		public:
			typedef jxAttribute obj_t;
			typedef nDataStruct::yVector<obj_t> list_t;
			typedef list_t::iterator iterator;

#pragma warning(disable : 4251)
			list_t m_aObj;
#pragma warning(default : 4251)

		public:
			virtual int size(){return m_aObj.size();}

			virtual jIAttributeList::iterator begin(){ return m_aObj.begin();}
			virtual jIAttributeList::iterator end(){ return m_aObj.end();}

			iterator _begin(){ return m_aObj.begin();	}
			iterator _end(){ return m_aObj.end();	}

			void clear(){ m_aObj.clear();	}
			void erase(iterator it){ m_aObj.erase(it);	}
			void insert(iterator it, iterator ie)	
			{
				for( ; it!=ie ; ++it)
				{
					jxVar* pV = FindVar(it->m_iTagIndex);
					if(pV)	continue;// 중복되는 노드는 복사하지 낳음.
					iterator itNew = m_aObj.push_back() ;
					//*itNew = *it;
					itNew->m_iTagIndex = it->m_iTagIndex;
					itNew->m_pTagName = it->m_pTagName;
					itNew->m_Data = it->m_Data;
				}
			}
			~jxAttributeList(){ clear();}

			//---------------------------------------------------------------	
			struct _jAttEqStr
			{
				cstr sz;
				_jAttEqStr(cstr sz1){sz= sz1;}
				bool operator()(obj_t* attR) const {	return !_tcscmp(attR->m_pTagName, sz);}
			};
			iterator find(cstr szA)
			{
				return m_aObj.find_if(_jAttEqStr(szA) );
			}
			jxVar* FindVar(cstr szA)
			{
				iterator it = find(szA);
				if(it==m_aObj.end() ) return 0;
				return &(it->m_Data);
			}
			cstr Find(cstr szA)
			{
				iterator it = find(szA);
				if(it == m_aObj.end() )		return 0;
				return it->m_Data.Get_cstr();
			}

			//----------------------------------------------------------------
			struct _jAttEqInt
			{
				StringID sz;
				_jAttEqInt(const StringID sz1){sz= sz1;}
				bool operator()(obj_t *attR) const {	return attR->m_iTagIndex==sz;}
			};
			iterator find(const StringID szA)
			{
				return m_aObj.find_if(_jAttEqInt(szA) );
			}
			jxVar* FindVar(const StringID szA)
			{
				iterator it = find(szA);
				if(it==m_aObj.end() ) return 0;
				return &(it->m_Data);
			}
			cstr Find(const StringID szA)
			{
				iterator it = find(szA);
				if(it == m_aObj.end() )		return 0;
				return it->m_Data.Get_cstr();
			}

			jxVar* Insert(cstr key);
			void SaveXML(jXmlFile* fp);
			void writeChunk(nUtil::jMemoryChunk& mc);
			void readChunk(nUtil::jMemoryChunk& mc);

			void writePacket(nUtil::jMemoryChunk& mc); // network packet용.
			void readPacket(nUtil::jMemoryChunk& mc);

			void DebugPrint(bool isInsert_CR);

		}; //struct jxAttributeList 
		typedef jxAttributeList jxAL;

	}
}


//#pragma warning(default : 4251)

#endif // !defined(AFX_jxAttribute_H__5FC9695D_DAD0_4426_96C7_E7B2A0069868__INCLUDED_)

