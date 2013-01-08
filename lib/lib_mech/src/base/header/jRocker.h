/* file : jRocker_ReadWrite.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-03-06 14:44:55
comp.: www.actoz.com
title : 
desc : 

http://symlink.tistory.com/50

������ ����ȭ ó���� ���� rwlock(read/write)�� �ʿ��Ҷ��� �ִ�. ���� �̷��� ���� �ҽ��� ã�� ���� ���� 
���ͳ��� ���� �ٴϴ� GDK���� ����Ʈ���� ���� �ҽ��� ���� ������ ����Ѵ�.

rwlock�� �ִ� ������ read�� �ߺ��ؼ� lock�� �����ɼ� ������, write���� CRITICAL_SECTION ó�� ��
�ϳ��� lock�� ó���� ȿ���� ���̴µ� ���ɼ� �ִ�

*/

#ifndef __jRocker_ReadWrite_header__
#define __jRocker_ReadWrite_header__
#pragma once


namespace nMech
{
	namespace nEVENT
	{
		struct jRocker_RW{
			HANDLE write_mutex;
			HANDLE read_event;
			LONG   readers;
			jRocker_RW()
			{
				readers = 0;
				read_event = CreateEvent(NULL, TRUE, FALSE, NULL);
				write_mutex = CreateMutex(NULL, FALSE, NULL);
			}
			~jRocker_RW()
			{
				CloseHandle(read_event);
				CloseHandle(write_mutex);
			}

			int ReadLock(DWORD milliseconds)
			{
				DWORD code = WaitForSingleObject( this->write_mutex, milliseconds);

				switch (code)
				{
				case WAIT_TIMEOUT: 
					return 0;

				case WAIT_FAILED : 
					return -1;

				default          : 
					InterlockedIncrement(&this->readers);
					if (!ResetEvent( this->read_event) || !ReleaseMutex( this->write_mutex))
						return -1;
				} 
				return 1;
			}

			int WriteLock(DWORD milliseconds)
			{
				DWORD code = WaitForSingleObject( this->write_mutex, milliseconds); 
				switch (code)
				{
				case WAIT_TIMEOUT: 
					return 0;

				case WAIT_FAILED: 
					return -1;

				default          :
					if (this->readers) 
					{
						code = milliseconds 
							? WaitForSingleObject( this->read_event, milliseconds)
							: WAIT_TIMEOUT;        
						if ((code == WAIT_FAILED) || (code == WAIT_TIMEOUT)) 
						{
							/* Unable to wait for readers to finish, release write lock: */
							if (!ReleaseMutex( this->write_mutex))
							{
								return -1;
							}
							return ((code == WAIT_TIMEOUT) ? 0: -1);           
						}
					}
				}//switch (code)
				return 1;
			}
		};
		struct jEvent
		{
			HANDLE m_Event;
			jEvent():m_Event(INVALID_HANDLE_VALUE){	}
			~jEvent(){ if(m_Event!=INVALID_HANDLE_VALUE) CloseHandle(m_Event);}
			void Init()
			{
				m_Event = CreateEvent(0, FALSE, FALSE, 0);
				jASSERT0(m_Event!=INVALID_HANDLE_VALUE);
			}
			void Reset(){ ResetEvent(m_Event);}
			void Set(){	SetEvent(m_Event);	}
			bool Wait(DWORD dwTime) 
			{ 
				DWORD code = WaitForSingleObject(m_Event, dwTime); 
				switch (code)
				{
				case WAIT_TIMEOUT: 			return false;
				case WAIT_FAILED : 			return false;
				}
				ResetEvent(m_Event);
				return true;
			}
		};
	}
}

#endif // __jRocker_ReadWrite_header__
