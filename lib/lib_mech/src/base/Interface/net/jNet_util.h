/* file : jNet_OGS_util.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-07-04 18:47:42
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jNet_OGS_util_header__
#define __jNet_OGS_util_header__
#pragma once
#include <Ws2tcpip.h>
#include "Interface/jILog.h"
using namespace nMech;
using namespace nMech::nLOG;

//--------------------------------------------------------------------------
// 참고 자료
//--------------------------------------------------------------------------
#if 0

unsigned short htons(unsigned short);   //Port 정보의 바이트 순서 변경
unsigned short ntohs(unsigned short);  //Port 정보의 바이트 순서 변경
unsigend long htonl(unsigned long);    //IP 주소의 바이트 순서 변경
unsigned long ntohl(unsigned long);    //IP 주소의 바이트 순서 변경

//IPv4의 주소체계를 나타내는 구조체
struct sockaddr_in {
	sa_family_t		sin_family;     /* 주소 체계(AF_INET) */
	uint16_t		sin_port;         /* port 정보 */
	struct in_addr	sin_addr;        /* 32 비트 IP 주소정보 */
	char 		sin_zero[8];    /* 사용되지 않음 */
};
struct in_addr {
	uint32_t		s_addr;	     /* 32비트 IP 주소정보 */
};



#endif


namespace nMech
{
	namespace nNET
	{
		namespace nUTIL
		{
			typedef SOCKADDR_IN _sockaddr_in;
			typedef SOCKADDR _sockaddr;
			//--------------------------------------------------------------------------
			// winsock 유틸함수
			//--------------------------------------------------------------------------

			inline cstr GetLastError()
			{
				return nInterface::g_pjINet_OGS->GetSocketError(WSAGetLastError());
			}

			//32비트 2진수로 된 주소를 “.”이 있는 십진수로 변환할 때 사용
			inline TCHAR* FAR inet_ntoa(struct   in_addr in,tname_t buf)
			{ 
#ifdef UNICODE
				aname_t buf1;
				ja_strcpy(buf1, ::inet_ntoa(in));
				jt_strcpy(buf ,nUNI::scb64_t(buf1).getT());
#else
				ja_strcpy(buf, ::inet_ntoa(in));
#endif
				return buf;
			}
			//(Ipv4) Internet Protocol dotted address into a proper address for the "in_addr" structure.
			//Dotted-Decimal Notation을 Big-Endian 32 비트 정수형 데이터로 표현(네트워크 바이트 순서)
			//“.”이 있는 십진수를 32비트 2진수로 변환할 때 사용
			//성공시 : Big_Endian 32비트 값 	실패시 : INNADDR_NONE
			inline unsigned long inet_addr(tcstr cp)
			{ 
				return ::inet_addr(nUNI::scb64_t(cp).getA());
			}

			//name resolution from an address to the host name.
			inline int getnameinfo(	const sockaddr_in& sa ,	name_n szIPOut,	name_n szPortOut,int flags) 
			{ 
				return ::getnameinfo((const sockaddr*)&sa,sizeof(sa), szIPOut,sizeof(szIPOut)
					, szPortOut ,sizeof(szPortOut), flags);
			}

			//retrieves the name of the peer to which a socket is connected.
			inline SOCKADDR_IN* getpeername(SOCKET s,SOCKADDR_IN* inOut)
			{
				int len = sizeof(SOCKADDR_IN);
				int ret =::getpeername(s,(SOCKADDR*)inOut, &len);
				if(ret) return inOut;
				jERROR(_T("WSAAddressToString() %s" ), GetLastError());
				return 0;
			}

			//retrieves the local inOut for a socket
			//call is especially useful when a connect call has been made without doing a bind first
			inline bool getsockname(SOCKET s,	SOCKADDR_IN* inOut)
			{
				int len = sizeof(sockaddr_in);
				int ret = ::getsockname(s,(sockaddr*)inOut,&len);
				if(ret==0)
					return true;
				jERROR(_T("getsockname() %s" ), GetLastError());
				return false;
			}

			// sockaddr_in -> "211.59.7.36:8888"
			inline bool WSAAddressToString(SOCKADDR_IN* in , tname_t szAddress)
			{
				if( !in ) return false;
				DWORD len = sizeof(name_n);
				INT ret =::WSAAddressToString((LPSOCKADDR )in, sizeof(SOCKADDR_IN)
					, 0, szAddress , &len);
				if(ret==0) 
					return true;
				//jMB("Don't Use WSAAddressToString","error");
				jt_strncpy(szAddress,_T("error WSAAddressToString"),sizeof(szAddress));
				DWORD iErr = WSAGetLastError();
				cstr szError = nInterface::g_pjINet_OGS->GetSocketError(iErr);
				jERROR(_T("WSAAddressToString(%d) %s " ), iErr,szError);
				return false;
			}

			// "211.59.7.36:8888" -> sockaddr_in 
			//--------------------------------------------------------------------------
			inline bool WSAStringToAddress(LPTSTR szAddress,    sockaddr_in* in)
			//--------------------------------------------------------------------------
			{
				int len = sizeof(sockaddr_in);
				in->sin_family = AF_INET;
				INT ret = ::WSAStringToAddress(szAddress, AF_INET, 0,(LPSOCKADDR)in, &len);
				if(ret==0) 
					return true; 
				jMB("Don't Use WSAStringToAddress","error");
				jERROR(_T("WSAStringToAddress() %s" ), GetLastError());
				return false;
			}

			/* 사용법
			sockaddr_in addr;
			jNet_OGS::Make_sockaddr_in("211.59.7.36"),234, addr);
			jNet_OGS::Make_sockaddr_in(0 ,234"), addr);
			*/
			//--------------------------------------------------------------------------
			inline sockaddr_in &Make_sockaddr_in(tcstr szIPin, unsigned short port,sockaddr_in &addr)
			//--------------------------------------------------------------------------
			{
				acstr szIP =0;
				nUNI::scb64_t aBuf;
				if(szIPin)
				{
					if(jt_strlen(szIPin))
					{
						if(!jt_strcmp(szIPin,_T("NULL") ) || !jt_strcmp(szIPin,_T("0.0.0.0") )|| !jt_strcmp(szIPin,_T("127.0.0.1") )  )
						{
							szIP = aBuf.set(nInterface::g_pjINet_OGS->GetHostIpString(0)).getA();
						}
						else
						{
							szIP = aBuf.set(szIPin).getA();
						}
					}
					else
						szIPin=0;
				}

				//struct sockaddr_in addr;  인터넷 주소 정보를 나타내는 구조체 변수 생성
				//char *szIP="211.217.168.13");        //IP 선언
				//char *port="9190");                    //Prot 선언

				memset(&addr, 0, sizeof(addr));  //인자로 전달된 구조체 변수 초기화
				addr.sin_family = AF_INET;                //프로토콜 체계 설정
				if(szIP)
					addr.sin_addr.s_addr = ::inet_addr(szIP);  //IP 주소를 설정
				else
					addr.sin_addr.s_addr = ::htons(INADDR_ANY);  //현재 시스템의 IP를 자동적으로 찾아줌
				addr.sin_port = htons(port); 
				return addr;
			}
			
			//--------------------------------------------------------------------------
			// host_ulong_IP : host측의 ulong 값
			inline sockaddr_in &Make_sockaddr_in(unsigned long  host_ulong_IP, unsigned short port,sockaddr_in &addr)
			//--------------------------------------------------------------------------
			{
				memset(&addr, 0, sizeof(addr));  //인자로 전달된 구조체 변수 초기화
				addr.sin_family = AF_INET;                //프로토콜 체계 설정
				if(host_ulong_IP)
					addr.sin_addr.s_addr = htonl(host_ulong_IP);  //IP 주소를 설정
				else
					addr.sin_addr.s_addr = htons(INADDR_ANY);  //현재 시스템의 IP를 자동적으로 찾아줌
				addr.sin_port = htons(port); 
				return addr;
			}


		}//namespace nUTIL




		namespace nUTIL_SOCKET
		{
			//--------------------------------------------------------------------------
			inline void Set_REUSEADDR(SOCKET listenSocket)
			//--------------------------------------------------------------------------
			{
				int sock_opt = 1;
				if ( setsockopt( listenSocket, SOL_SOCKET, SO_REUSEADDR, ( char * ) & sock_opt, sizeof ( sock_opt ) ) == -1 )
				{
					jERROR(_T("setsockopt(SO_REUSEADDR) failed:Error code - %s" ), GetLastError());
				}
			}
			inline void Set_RecvSend_BufferSize(SOCKET s, int iRecv, int iSend)
			{
				// This doubles the max throughput rate
				//int iRecv=1024*256;
				setsockopt(s, SOL_SOCKET, SO_RCVBUF, ( char * ) & iRecv, sizeof ( iRecv ) );
				// This doesn't make much difference: 10% maybe
				//iSend=1024*16;
				setsockopt(s, SOL_SOCKET, SO_SNDBUF, ( char * ) & iSend, sizeof ( iSend ) );
			}
			inline void Set_NonBlockingMode(SOCKET s)
			{
#ifndef _COMPATIBILITY_2
#ifdef _WIN32
				unsigned long nonblocking = 1;
				// http://www.die.net/doc/linux/man/man7/ip.7.html
				if ( ioctlsocket( s, FIONBIO, &nonblocking ) != 0 )
				{
					assert( 0 );
					//return INVALID_SOCKET;
				}
#else
				if ( fcntl( s, F_SETFL, O_NONBLOCK ) != 0 )
				{
					assert( 0 );
					//return INVALID_SOCKET;
				}
#endif
#endif
			}

			inline void Set_Broadcast_Capable(SOCKET s)
			{
				int sock_opt;
				if ( setsockopt( s, SOL_SOCKET, SO_BROADCAST, ( char * ) & sock_opt, sizeof( sock_opt ) ) == -1 )
				{
					jt_printf( _T("setsockopt(SO_BROADCAST) failed:Error code - %s"), GetLastError());
				}
			}

		}// nNet::nUTIL_SOCKET

		struct jSOCKADDR_IN : public SOCKADDR_IN
		{
			jSOCKADDR_IN(){}
			jSOCKADDR_IN(SOCKET sIn){ Set(sIn);}
			jSOCKADDR_IN(wcstr szIP, u_short port){ Set(nUNI::scb64_t(szIP).getT(),port);}
			jSOCKADDR_IN(acstr szIP, u_short port){ Set(nUNI::scb64_t(szIP).getT(),port);}
			jSOCKADDR_IN(unsigned long host_ulong_IP, u_short port){ Set(host_ulong_IP,port);}

			jSOCKADDR_IN& Set(SOCKET sIn)//소켓으로 부터 주소정보 추출
			{	
				bool isOK = nMech::nNET::nUTIL::getsockname(sIn, this);	
				return *this;
			}
			//호스트 ulong으로 변환된 아이피라고 가정
			jSOCKADDR_IN& Set(unsigned long host_ulong_IP, u_short port)
			{
				nMech::nNET::nUTIL::Make_sockaddr_in(host_ulong_IP, port, *this);
				return *this;
			}
			jSOCKADDR_IN& Set(tcstr szIP, u_short port)
			{
				nMech::nNET::nUTIL::Make_sockaddr_in(szIP, port, *this);
				return *this;
			}
			tcstr ToString(tname_t bufOut) //"211.59.7.36:1234"형태로 주소문자추출
			{	
				sockaddr_in in = *this;
				tname_t szIP;
				nUTIL::inet_ntoa(in.sin_addr,szIP);
				jt_sprintf(bufOut,_T("%s:%d"),szIP,ntohs(in.sin_port));
				//bool isOK = nMech::nNET::nUTIL::WSAAddressToString(  this, bufOut);	
				return bufOut;
			}
			tcstr ToStringByLocalPort(tname_t bufOut) //"211.59.7.36:1234"형태로 주소문자추출. port는 ntohs로 변환하여 추출
			{	
				sockaddr_in in = *this;
				tname_t szIP;
				nUTIL::inet_ntoa(in.sin_addr,szIP);
				jt_sprintf(bufOut,_T("%s:%d"),szIP,ntohs(in.sin_port));
				//bool isOK = nMech::nNET::nUTIL::WSAAddressToString(  this, bufOut);	
				return bufOut;
			}
			tcstr GetIP(tname_t bufOut)
			{ 
				nMech::nNET::nUTIL::WSAAddressToString(  this, bufOut); 
				TCHAR* ch = jt_strchr(bufOut	,':');
				*ch=0;
				return bufOut;
			}
			u_short GetPort(){ return ntohs(sin_port);}
#if 0
			bool operator==( const jSOCKADDR_IN& in) const
			{	
				return (sin_addr.S_addr == in.sin_addr.S_addr) && (sin_port== in.sin_port);
			}
#endif

			static tcstr Addr2String(jIP_Address& pIP,tname_t buf)
			{
				jSOCKADDR_IN in(pIP.m_IP.s_addr,pIP.port);
				return in.ToString(buf);
			}
			static jIP_Address String2Addr(tcstr szIP)//"127.0.0.1:2344"
			{
				jASSERT0(jt_strchr(szIP, ':'));
				std::vector<std::tstring> out;
				nString::jSplit(szIP, _T(":"),out);

				sockaddr_in addr;
				addr.sin_addr.s_addr = nUTIL::inet_addr(out[0].c_str());
				jIP_Address ip;
				ip.m_IP.s_addr = ntohl(addr.sin_addr.s_addr);
				ip.port = jt_atoi(out[1].c_str());
				return ip;
			}

			//"127.0.0.1"  2344
			static jIP_Address String2Addr(tcstr szIP,unsigned short port)
			{
				sockaddr_in addr;
				nUTIL::Make_sockaddr_in(szIP,port, addr);
				jIP_Address ip;
				ip.m_IP.s_addr = ntohl(addr.sin_addr.s_addr);
				ip.port = ntohs(addr.sin_port);
				return ip;
			}


		};//jSOCKADDR_IN

	} //nNET
}//nMech


#endif // __jNet_OGS_util_header__
