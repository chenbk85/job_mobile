/* file : jQueue.h
Coder : by icandoit (mech12@nate.com, icandoit@n_jGame_c.net)
Date : 2006-08-11 13:38:57
title : 
desc : 

*/

#ifndef __jQueue_header__
#define __jQueue_header__
#pragma once

namespace nMech
{

// 무한 큐. 버퍼용량 한도내에서 환형으로 돌면서 무한 push_back()할수 있다.
template<typename T> class jCircleQueue_UnLiminit
{
public:
	enum EState 
	{
		eNO_CIRCLED
		,eCIRCLED
	};
	int m_it;
	int m_iNewInsertPos;
	int m_iTot;
	T* m_pArray;
	EState m_eFlag;
public:
	jCircleQueue_UnLiminit()
	{ 
		m_eFlag=eNO_CIRCLED; 
		m_pArray=0; m_iNewInsertPos=0;
	}
	jCircleQueue_UnLiminit(int iCnt)
	{ 
		m_iTot = iCnt;
		m_eFlag=eNO_CIRCLED; 
		m_pArray = new T[m_iTot]; m_iNewInsertPos=0;
	}
	void Init(int iCnt)
	{ 
		Release() ; 
		m_iTot=iCnt;  m_pArray = new T[iCnt] ; m_iNewInsertPos=0;
	}
	void Release()
	{ 
		SAFE_DELETE_ARRAY(m_pArray);
		m_iTot =0; m_iNewInsertPos = 0;
		m_eFlag=eNO_CIRCLED;
	}

	int capacity(){ return m_iTot;}
	int size()
	{ 
		if(m_eFlag==eCIRCLED) return m_iTot;
		return m_iNewInsertPos;
	}
	
	T* push_back()
	{ 
		int i = m_iNewInsertPos; 
		assert(i>=0 && i<m_iTot);
		++m_iNewInsertPos;
		if(m_iNewInsertPos>=m_iTot )
		{
			m_eFlag=eCIRCLED;
			m_iNewInsertPos=0;
		}
		return m_pArray + i;
	}
	
	T* GotoBegin()
	{
		if(m_eFlag==eNO_CIRCLED)
		{
			if(m_iNewInsertPos ==0)
			{
				m_it =-2;
				return 0;
			}
			m_it = 0;
		}
		else
		{
			m_it=m_iNewInsertPos;
		}
		return m_pArray + m_it;
	}

	T* GotoBeginNext()
	{
		if(m_it==-2) return 0;

		++m_it;

		if(m_eFlag==eNO_CIRCLED)
		{
			if( m_it >=m_iNewInsertPos)
				return 0;
		}
		else
		{
			if( m_it >=m_iTot) 
				m_it=0;
			if(m_it == m_iNewInsertPos)
			{
				m_it=-2;
				return 0;
			}
		}

		return m_pArray + m_it;
	}

	T* GotoEnd()
	{
		if(m_eFlag==eNO_CIRCLED)
		{
			if(m_iNewInsertPos==0)
			{
				m_it=-2;
				return 0;
			}

			m_it = m_iNewInsertPos-1;
		}
		else
		{
			m_it = m_iNewInsertPos-1;
			if(m_it<0)
				m_it = m_iTot-1;
		}
		return m_pArray + m_it;
	}
	T* GotoEndPrev()
	{
		if(m_it==-2) return 0;
		--m_it;
		if(m_eFlag == eNO_CIRCLED)
		{
			if(m_it<0)
			{
				m_it =-2;
				return 0;
			}
		}
		else
		{
			if(m_it <0)
			{
				m_it = m_iTot-1;
			}
			if(m_it == (m_iNewInsertPos-1))
			{
				m_it =-2;
				return 0;
			}
		}
		return m_pArray + m_it;
	}
	/* *_* by icandoit : 2006-08-11 15:07:08
	
	z:\src\test\jTest_xml\test_jCircleQueue.cpp
	static void jTest()
	{
		struct _aaa
		{
			fname_t buf;
			int id;
		};
		jCircleQueue_UnLiminit<_aaa> test(5);
		
		for( int i=0; i< 3 ; ++i)
		{
			_aaa* a = test.push_back();
			a->id = i;
			sprintf(a->buf ," id =%d",a->id);
		}

		_aaa* pA = test.GotoBegin();
		for( ; pA ; pA = test.GotBeginNext() )
		{
			printf(" %d => %s \n", pA->id, pA->buf);
		}

		for( int i=10; i< 13 ; ++i)
		{
			_aaa* a = test.push_back();
			a->id = i;
			sprintf(a->buf ," id =%d",a->id);
		}
	}
*/ //*_* by icandoit : 2006-08-11 15:07:10

};

// 환형큐. 해당 갯수만큼만 push_back할수 있다. 버퍼 갯수가 찻을때 pop_front()하지 않으면 push_back하면 NULL을 리턴.
template<typename T> class jCircleQueue_Liminit
{
public:
	enum EState 
	{
		eNO_CIRCLED
		,eCIRCLED
	};
	size_t m_ci ,m_cf;
	size_t m_iTot;
	T* m_pArray;
public:
	jCircleQueue_Liminit() :m_pArray(0)	
	{
		Release();
	}
	void Release()
	{
		SAFE_DELETE_ARRAY(m_pArray);
		m_iTot=m_ci=m_cf=0;
	}
	void Init(size_t tot,bool clear=false)
	{
		if(tot<=0) throw jFUNC1;
		if(m_pArray) throw jFUNC;
		m_pArray = new T[tot];
		if(clear)
			ZeroMemory(m_pArray,sizeof(T)* tot);
		m_iTot = tot;
		m_ci = 0;
		m_cf = tot;
	}
	T *push_back()
	{
		if(m_ci>=m_iTot) 
			return 0;
		T*  p = m_pArray+m_ci;
		if(m_cf>=m_iTot)
			m_cf = m_ci;
		++m_ci;
		if(m_ci >= m_iTot) 
			m_ci = 0;
		if(m_ci == m_cf)
			m_ci = m_iTot;
		return p;
	}
	T* pop_front()
	{
		if(m_cf >=m_iTot)
			return 0;
		T* p = m_pArray+m_cf;
		if(m_ci>=m_iTot)
			m_ci = m_cf;
		++m_cf;
		if(m_cf >=m_iTot)
			m_cf =0;
		if(m_cf==m_ci)
			m_cf=m_iTot;
		return p;
	}
};


}//namespace nMech

#endif // __jQueue_header__
