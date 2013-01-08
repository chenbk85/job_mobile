/* 
	filename:	jRtti_util.h
	coder	:	Cho Hyun Min (icandoit@wemade.com) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	4337-12-31 ¿ÀÈÄ 2:32:50
	title	:	
*/


#ifndef __jRtti_util_hasdf32k2sdkfds9ds88sd__
#define __jRtti_util_hasdf32k2sdkfds9ds88sd__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000
namespace nMech
{
	namespace nXML
	{
		typedef void jxElementList_init_func_t(jIE*, void*);
		template <class T> class jxElementList
		{
		public:
			jIE* m_pE;
			jIE* m_peCurr;
			cstr m_szItemName;
			jxElementList():m_pE(0), m_peCurr(0) {	}
			jxElementList_init_func_t* m_pInitFn;

			void clear() 
			{ 
				if(!m_pE) return;
				jIE* it = m_pE->begin();
				jrFOR(it)
				{
					T* pO = (T*)it->GetUserData();
					T::_erase(pO);
				}
				m_pE=0;m_peCurr=0;
			}
			size_t size(){ return m_pE? m_pE->size() : 0 ;}
			void Init(jIE* pE, jxElementList_init_func_t* pFn,cstr szItemName)
			{ 
				m_szItemName = szItemName;
				m_pInitFn = pFn;
				m_pE=pE;
				jIE* it = pE->begin();
				m_peCurr = it;
				jrFOR(it)
				{
					T* pO = T::_push_back();
					it->SetUserData(pO);
					pFn(it, pO );
				}
			}
			T* GetCurr(){ return m_peCurr ? GetObj(m_peCurr) : 0;}
			static T* GetObj(jIE* pE)
			{
				assert(pE->GetUserData());
				return (T*)pE->GetUserData();
			}
			T* Get(int i)
			{
				jIE* pE = m_pE->FindByOrder(i);
				if(!pE) return 0;
				GetObj(pE);
			}

			T* Add(int i)
			{
				jIE* pE = m_pE->InsertChild(m_szItemName, 0 , i);
				T* pT = T::_push_back();
				pE->SetUserData(pT);
				m_pInitFn(pE, pT);
				m_peCurr=m_pE->begin();
				return pT;
			}
			void Del(int i)
			{
				jIE* pE = m_pE->FindByOrder(i);
				if(!pE) return;
				T::_erase(GetObj(pE));
				pE->Erase();
				m_peCurr=m_pE->begin();
			}

		};

	}//nXML


}

#endif //__jRtti_util_hasdf32k2sdkfds9ds88sd__
