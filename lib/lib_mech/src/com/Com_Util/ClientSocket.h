/* file : ClientSocket.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-13 16:56:48
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __ClientSocket_header__
#define __ClientSocket_header__
#pragma once


#pragma  comment(lib, "ws2_32.lib")

#include <Winsock2.h>
#include <Windows.h>
#include <stdio.h>
namespace nMech
{
	namespace nUtil
	{
		namespace nDebug
		{

			class ClientSocket
			{
			public:
				ClientSocket();
				~ClientSocket();

				bool		Connect( acstr ipAddress, u_short portNo );
				void		Close();

				int			Send( LPVOID buffer, int size );
				int			Recv( LPVOID buffer, int size );

			private:
				SOCKET		m_socketValue;
			};

		}
	}

}

#endif // __ClientSocket_header__
