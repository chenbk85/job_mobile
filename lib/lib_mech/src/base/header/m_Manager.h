/* 
	filename:	m_Manager.h
	coder	:	Cho Wook Rea (mech12@dreamwiz.com)(icq:74456993) 
	comp.	:	EmailPet 
	compiler:	vc++ 6.0
	date	:	2001-06-19오전 1:10:17
	title	:	
*/


#ifndef __m_Manager_h__
#define __m_Manager_h__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000
#include <assert.h>
#include "yVector.h"

namespace nMech
{
	namespace nDataStruct
	{

		//****************************************************************
		template<class T>  class yVectorTag
			//****************************************************************
		{

		public:
			typedef T obj_t;
			typedef yVector<T> list_t;
			typedef typename list_t::iterator iterator;
#pragma warning(disable : 4251)
			list_t m_aObj;
#pragma warning(default : 4251)
			iterator begin(){ return m_aObj.begin();	}
			iterator end(){ return m_aObj.end();	}
			iterator rbegin() {return m_aObj.rbegin(); }
			iterator rend() { return m_aObj.rend(); }

			iterator erase( iterator it){ return m_aObj.erase(it);	}
			void clear() {m_aObj.clear();	}

			T* push_back(){	return m_aObj.push_back();	}

			/*{chowookrea@hotmail2004-07-20오후 1:58:26
			typedef bool IsLessThen_Func_t(void* pOrderVal,iterator it);
			T* insertByOrder(void* pVal , IsLessThen_Func_t* func)
			{

			iterator it=m_aObj.begin();
			jFOR(m_aObj , it)
			{
			if(func(pVal , it))
			return m_aObj.insert(it);
			}
			return m_aObj.push_back();
			}

			/*{chowookrea@hotmail2004-07-20오후 1:56:50
			typedef void (BaseT::*vfunc2_t)(obj_t*, void*);
			void for_each(vfunc2_t fn,void* pV)
			{
			obj_t* it;
			jFOR(m_aObj ,it)
			{
			(((BaseT*)this)->*(fn))(it , pV);
			}
			}
			}chowookrea@hotmail 2004-07-20오후 1:56:52*/
		}; // template <class T,class BaseT>  class TVectorTag


		//****************************************************************
		template<class T>  class TVectorTag
			//****************************************************************
		{

		public:
			typedef T obj_t;
			typedef jvector<T> list_t; // model class 의 갯수 만큼 잡힌다
			//또한 모델 클래스 id가 인덱스가 됨. ex) 머리 0번 , 얼굴 1번.
			typedef typename list_t::iterator iterator;

#pragma warning(disable : 4251)
			list_t				m_aObj;
#pragma warning(default : 4251)


			void GetBeginEnd(iterator &it,iterator &ie){ it=m_aObj.begin() ; ie=m_aObj.end();}
			iterator begin(){ return m_aObj.begin();	}
			iterator end(){ return m_aObj.end();	}
			iterator erase( iterator it){ return m_aObj.erase(it);	}
			void clear() {m_aObj.clear();	}

			template <class _Predicate>
				iterator find_if(_Predicate __pred) 
			{
				iterator it = begin(), ie = end();
				for( ; it!=ie ; it=it->_pR ) if(__pred(*it)) return it;
				return ie;
			}
			template <class _Predicate>
				iterator for_each(_Predicate __pred) 
			{
				iterator it = begin(), ie = end();
				for( ; it!=ie ; ++it) __pred(*it); 
				return ie;
			}
			T& operator[](uint i) 	{ 		return operator[]((int)i);	}
			T& operator[](int i) 	{ 		jASSERT( i < m_aObj.size() );		return m_aObj[i];	}

		}; // template <class T>  class TVectorTag


		//****************************************************************
		template <class T>  class TListTag
			//****************************************************************
		{
		public:

			typedef T obj_t;
			typedef std::list<T> list_t; // model class 의 갯수 만큼 잡힌다
			//또한 모델 클래스 id가 인덱스가 됨. ex) 머리 0번 , 얼굴 1번.
			typedef typename list_t::iterator iterator;
			list_t				m_aObj;

			void GetBeginEnd(iterator &it,iterator &ie){ it=m_aObj.begin() ; ie=m_aObj.end();}
			iterator begin(){ return m_aObj.begin();	}
			iterator end(){ return m_aObj.end();	}
			iterator erase( iterator it){ return m_aObj.erase(it);	}
			void clear() {m_aObj.clear();	}

			template <class _Predicate>
				iterator find_if(_Predicate __pred) 
			{
				iterator it = begin(), ie = end();
				for( ; it!=ie ; it=it->_pR ) if(__pred(*it)) return it;
				return ie;
			}
			template <class _Predicate>
				iterator for_each(_Predicate __pred) 
			{
				iterator it = begin(), ie = end();
				for( ; it!=ie ; ++it ) __pred(*it); 
				return ie;
			}
		}; // template <class T>  class TListTag



		//****************************************************************
		inline void normailName(tcstr szName , TCHAR* szOut)
			//****************************************************************
		{ // map<>에서 스트링 검색하기 위하여 철자를 소문자로 바꿈.
			assert(_tcslen(szName) < sizeof(tfname_t)/sizeof(TCHAR)-1);
			jt_strncpy(szOut , szName,sizeof(tfname_t)/sizeof(TCHAR)-1);
			_tcslwr(szOut);
		}


		//****************************************************************
		template <class KEY ,class T>  class TMapTag
			//****************************************************************
		{
		public:
			typedef T obj_t;
			typedef KEY key_t;
			typedef std::map<KEY, T> list_t;
			typedef typename list_t::iterator iterator;
			typedef typename list_t::value_type value_type;
			typedef std::pair<iterator , bool>	pair_type;

#pragma warning(disable : 4251)
			list_t m_aObj;
#pragma warning(default : 4251)
			obj_t& operator[](const key_t key) 	{ 		return m_aObj[key];	}
			void GetBeginEnd(iterator &it,iterator &ie){ it=m_aObj.begin() ; ie=m_aObj.end();}
			iterator begin(){ return m_aObj.begin();	}
			iterator end(){ return m_aObj.end();	}
			iterator erase( iterator it){ return m_aObj.erase(it);	}
			void clear() {m_aObj.clear();	}

			/*{chowookrea@hotmail2004-07-20오후 2:03:13
			typedef void (BaseT::*vfunc2_t)(iterator& , void*);
			void for_each2(vfunc2_t  fn,void* pV)
			{
			iterator it ,ie;
			GetBeginEnd(it,ie);
			for( ;it != ie;++it )	
			{
			(((BaseT*)this)->*(fn))(it , pV);
			}
			}
			}chowookrea@hotmail 2004-07-20오후 2:03:16*/
			template <class _Predicate>
				iterator find_if(_Predicate __pred) 
			{
				iterator it = begin(), ie = end();
				for( ; it!=ie ;++it ) if(__pred(it)) return it;
				return ie;
			}
			template <class _Predicate>
				iterator for_each(_Predicate __pred) 
			{
				iterator it = begin(), ie = end();
				for( ; it!=ie ; ++it ) __pred(it); 
				return ie;
			}

		}; // template <class T>  class TMapTag


		//****************************************************************
		template <class KEY , class T>  
		class _TManagerMap : public TMapTag<KEY ,T>
			//****************************************************************
			// T 구조체는 
			// void Load(cstr) , bool  UnLoad(cstr) ,void UnLoad()
		{

		public:

			T* Load(const KEY &key)
			{
				iterator it = m_aObj.find(key);
				if(it==m_aObj.end())
				{
					it = m_aObj.insert(m_aObj.end(), value_type(key, T() ) );
					it->second.Load(key);
				}
				else
				{
					//it->second.AddRef();
				}

				return &(it->second);
			}


			//****************************************************************
			void UnLoad(const KEY &key)
			{
				iterator it = m_aObj.find(key);
				if(it==m_aObj.end())		{			return;		}
				//assert( it==m_aObj.end() );
				it->second.UnLoad();
				m_aObj.erase(it);
			}

			//****************************************************************
			void UnLoadAll(iterator it){ it->second.UnLoad();}
			void UnLoad()
			{
				//for_each(UnLoadAll);
				iterator it ;
				jFOR(m_aObj ,it)			{			it->second.UnLoad();		}
				m_aObj.clear();
			}

			//~_TManagerMap(){UnLoad();}

			//****************************************************************
			T* Insert(const KEY &key) // 해당이름으로 오브젝트를 등록하고 주소를 리턴.
			{
				iterator it = m_aObj.find(key);
				if(it==m_aObj.end())
				{
					it = m_aObj.insert(m_aObj.end(), value_type(key, T() ) );
				}
				return &(it->second);
			}

			//-------------------------------------------------
			T* GetObj(const KEY &key) // 해당 이름의 오브젝트 리턴.
			{
				iterator it = m_aObj.find(key);
				if(it == m_aObj.end() )
				{
					return 0;
				}
				return &(it->second);
			}
		}; // template <struct T>  struct _TManagerMap


		//****************************************************************
		template <class T>  class TManagerMap : public _TManagerMap<std::tstring , T>
			//****************************************************************
			// T 구조체는 
			// void Load(cstr) , bool  UnLoad(cstr) ,void UnLoad()
		{
			// class T의  필요 맴버 Load(cstr) , UnLoad() , 

		public:
			T* Load(const std::tstring& sName){ return Load(sName.c_str());}
			T* Load(cstr szName)
			{
				fname_t szOut;
				normailName(szName, szOut);
				iterator it = m_aObj.find(szOut);
				if(it==m_aObj.end())
				{
					it = m_aObj.insert(m_aObj.end(), value_type(szOut, T() ) );
					it->second.Load(szOut);
				}
				else
				{
					///it->second.AddRef();
				}

				return &(it->second);
			}

			//****************************************************************
			void UnLoad(cstr szName)
			{
				fname_t szOut;
				normailName(szName ,szOut);
				iterator it = m_aObj.find(szOut);
				if(it==m_aObj.end())		{			return;		}
				//assert( it==m_aObj.end() );

				if(it->second.UnLoad() )
				{
					m_aObj.erase(it);
				}
			}

			//****************************************************************
			T* Insert(cstr szName) // 해당이름으로 오브젝트를 등록하고 주소를 리턴.
			{
				fname_t szOut;
				normailName(szName, szOut);
				iterator it = m_aObj.find(szOut);
				if(it==m_aObj.end())
				{
					it = m_aObj.insert(m_aObj.end(), value_type(szOut, T() ) );
				}
				return &(it->second);
			}

			//-------------------------------------------------
			T* GetObj(cstr szName) // 해당 이름의 오브젝트 리턴.
			{
				fname_t szOut;
				normailName(szName, szOut);
				iterator it = m_aObj.find(szOut);
				if(it == m_aObj.end() )
				{
					return 0;
				}
				return &(it->second);
			}
		}; // template <struct T>  struct TManagerMap

	}//nHEADER

}

#pragma warning(default: 4251)

#endif //__m_Manager_h__
