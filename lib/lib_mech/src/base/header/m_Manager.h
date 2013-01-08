/* 
	filename:	m_Manager.h
	coder	:	Cho Wook Rea (mech12@dreamwiz.com)(icq:74456993) 
	comp.	:	EmailPet 
	compiler:	vc++ 6.0
	date	:	2001-06-19���� 1:10:17
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

			/*{chowookrea@hotmail2004-07-20���� 1:58:26
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

			/*{chowookrea@hotmail2004-07-20���� 1:56:50
			typedef void (BaseT::*vfunc2_t)(obj_t*, void*);
			void for_each(vfunc2_t fn,void* pV)
			{
			obj_t* it;
			jFOR(m_aObj ,it)
			{
			(((BaseT*)this)->*(fn))(it , pV);
			}
			}
			}chowookrea@hotmail 2004-07-20���� 1:56:52*/
		}; // template <class T,class BaseT>  class TVectorTag


		//****************************************************************
		template<class T>  class TVectorTag
			//****************************************************************
		{

		public:
			typedef T obj_t;
			typedef jvector<T> list_t; // model class �� ���� ��ŭ ������
			//���� �� Ŭ���� id�� �ε����� ��. ex) �Ӹ� 0�� , �� 1��.
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
			typedef std::list<T> list_t; // model class �� ���� ��ŭ ������
			//���� �� Ŭ���� id�� �ε����� ��. ex) �Ӹ� 0�� , �� 1��.
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
		{ // map<>���� ��Ʈ�� �˻��ϱ� ���Ͽ� ö�ڸ� �ҹ��ڷ� �ٲ�.
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

			/*{chowookrea@hotmail2004-07-20���� 2:03:13
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
			}chowookrea@hotmail 2004-07-20���� 2:03:16*/
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
			// T ����ü�� 
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
			T* Insert(const KEY &key) // �ش��̸����� ������Ʈ�� ����ϰ� �ּҸ� ����.
			{
				iterator it = m_aObj.find(key);
				if(it==m_aObj.end())
				{
					it = m_aObj.insert(m_aObj.end(), value_type(key, T() ) );
				}
				return &(it->second);
			}

			//-------------------------------------------------
			T* GetObj(const KEY &key) // �ش� �̸��� ������Ʈ ����.
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
			// T ����ü�� 
			// void Load(cstr) , bool  UnLoad(cstr) ,void UnLoad()
		{
			// class T��  �ʿ� �ɹ� Load(cstr) , UnLoad() , 

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
			T* Insert(cstr szName) // �ش��̸����� ������Ʈ�� ����ϰ� �ּҸ� ����.
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
			T* GetObj(cstr szName) // �ش� �̸��� ������Ʈ ����.
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
