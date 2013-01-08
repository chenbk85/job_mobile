#ifndef __KEY_H__
#define __KEY_H__

/* 
	filename:	juKEY.H
	coder	:	Cho Wook Rea (mech12@dreamwiz.com)(icq:74456993) 
	comp.	:	EmailPet 
	compiler:	vc++ 6.0
	date	:	2001-05-09오전 10:57:42
	modify : 2003.0306
	title	:	
*/
#ifndef __juKEY_H__
#define __juKEY_H__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000
#include <windows.h>


#endif //__juKEY_H__


namespace nMech
{
	namespace nINPUT
	{
#define KEY_NORMAL			0
#define KEY_SAVE			1
#define KEY_LOAD			2


#define SELECT_KEY			(KEY.GetKeyAsciValue(VK_SPACE) || KEY.GetKeyAsciValue(TEXT('Z')) || KEY.GetKeyAsciValue(TEXT('X')))

		//---------------------------------------------------------------
		class JBASE_API juKey
			//----------------------------------------------------------------
		{
			juKey::juKey()
			{
				memset( m_ks , 0 , sizeof(m_ks) );
				memset( m_bks , 0 , sizeof(m_ks) );
			}
		public:
			BOOL m_start;
			int m_tick;

			DWORD m_ks[256];
			DWORD m_bks[256];

			//int m_flag;					// 0 - normal, 1 - output, 2 - input
			//DWORD m_stack[256];
			//FILE *m_fp;

		public:
			static juKey& Get();

			// "1" ,  "I" 등  알파벳값으르 얻오 올때.
			bool GetKeyDown( int asc ){	return ( m_ks[asc] > 0 && m_bks[asc] == 0 );	}
			bool GetKeyUp( int asc )	{ return ( m_ks[asc] ==0 && m_bks[asc] > 0 ); }

			void Update(void); // key update 함수.
			bool GetKey (int nVK){	return  (short(GetAsyncKeyState( nVK )) & 0x8000) ?  1 : 0;	}
			bool GetKeyScanValue( int scan )	{		return( m_ks[scan] >= 1);	}//  "I" 등  알파벳값으르 얻오 올때.
			bool GetKeyAsciValue( int asc )		{		return ( m_ks[asc] == 1);	}// VK_키값으로 얻어 올때.

			/*{chowookrea@hotmail(icq74456993)2003-03-06오후 3:35:03
			//****************************************************************	
			// key value 얻어오는함수.
			//****************************************************************
			void		VKKeyClear(int event)						{ m_ks[g_pKeySetVK[event]] = m_bks[g_pKeySetVK[event]] = 0; }
			// 현제의 키맵에 새로운 키맵을 세팅한다.
			bool		VKKeyDown(int event)	{ return (m_ks[g_pKeySetVK[event]]) && !(VKKeyOnPrev(event) ); }
			bool		VKKeyUp(int event)		{ return !(m_ks[g_pKeySetVK[event]]) && (VKKeyOnPrev(event) ); }
			bool		VKKeyOn(int event)		{ return (m_ks[g_pKeySetVK[event]] != 0 ); }
			bool		VKKeyOnPrev(int event)	{ return m_bks[g_pKeySetVK[event]] !=0 ; }

			void SetFlag (int flag);
			inline int GetFlag (void) { return m_flag; }

			void Push( void ) { memcpy( m_stack, m_ks, sizeof(DWORD) * 256 ); }
			void Pop( void ) { memcpy( m_ks, m_stack, sizeof(DWORD) * 256 ); }

			DWORD GetValue (int value) { return (m_ks[value]); }
			}chowookrea@hotmail(icq74456993) 2003-03-06오후 3:35:14*/

			inline void Clear (void) { memset (m_ks, 0x00, sizeof(DWORD) * 256); }
		};


		inline void juKey::Update(void)
		{
			short d;
			memcpy(m_bks , m_ks , sizeof(m_ks) );
			for (int i = 1; i < 256; i++)
			{
				d = GetAsyncKeyState( i );
				m_ks[i] = (d & 0x8000) ? m_ks[i] + 1 : 0;
			}
		}

	}//nHEADER

}
#endif
