/* file : jAutoPtr.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-06-24 18:20:16
title : 
desc : 

*/

#ifndef __jAutoPtr_header__
#define __jAutoPtr_header__
#pragma once

namespace nMech
{
	namespace nFunctor
	{
		struct jIVar_AutoPtr
		{
			jIVar_AutoPtr()
			{ 	
				m_pV = GetjIXml()->CreatejVar();
			}
			~jIVar_AutoPtr()
			{
				GetjIXml()->DeletejVar(m_pV);
			}
			jIVar* operator->() const
			{
				return m_pV;
			}
			operator jIVar*() const
			{
				return m_pV;
			}
		private:
			jIVar* m_pV;
		};


		struct jIE_AutoPtr
		{
			jIE_AutoPtr()
			{ 	
				m_pE = GetjIXml()->CreateElement();
			}
			~jIE_AutoPtr()
			{
				GetjIXml()->DeleteElement(m_pE);
			}
			jIE* operator->() const
			{
				return m_pE;
			}
			operator jIE*() const
			{
				return m_pE;
			}

			jIE* m_pE;
		};


		/* *_* by icandoit : 2005-11-17 19:08:24


		class jIVar_AutoPtr
		{
		public:

		jIVar_AutoPtr()
		{
		assert(0);
		}


		jIVar_AutoPtr(const jIVar_AutoPtr& rp)
		{
		assert(0);
		}


		jIVar_AutoPtr(T* ptr)
		{
		if(ptr){ _ptr = ptr;}
		else _ptr = 0;
		}


		~jIVar_AutoPtr()
		{
		if(_ptr) GetjIXml()->DeletejVar(_ptr);
		}


		jIVar_AutoPtr& operator=(const jIVar_AutoPtr& rp)
		{
		assert(0);
		}


		jIVar_AutoPtr& operator=(T* ptr)
		{
		assert(0);
		//
		//		if(_ptr == ptr) return *this;
		//		if(_ptr) _ptr->release();
		//		if(ptr){ _ptr = ptr; _ptr->addRef(); }
		//		else _ptr = 0;

		return *this;
		}


		T* operator->() const
		{
		return _ptr;
		}


		operator T*() const
		{
		assert(0);
		return _ptr;
		}

		private:
		T* _ptr;

		};
		*/ //*_* by icandoit : 2005-11-17 19:08:26

	}//nFunctor

}

#endif // __jAutoPtr_header__
