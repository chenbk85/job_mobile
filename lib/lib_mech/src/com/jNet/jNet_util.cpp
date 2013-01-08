/* file : jNet_util.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2007-07-05 17:05:51
comp.: pantavision.co.kr
title : 
desc : 


[edit]
사설IP (Private IP) #
그럼 여기서 사설IP가 무엇인지 모르는 사람들을 위해서 조금 주저리 주저리 쓰도록 하겠다.
사설아이피는? 말그대로 사설 IP다.
컴퓨터가 인터넷에 접속을 하려면 IP라는 것이 필요하다. 인터넷 주소... 그런데 예전에 인터넷을 처음 설계할때만하더라도 이렇게 까지 컴퓨터가 늘어날것이며 심지어 가전제품에도 인터넷을 꼽아서 홈네트워킹이니 인텔리전트 아파트니 이런것을 만들어낼 것까지는 생각을 못했던 것이였다.
그러나 그러한 것들이 이 사설망으로 해결될 수 있으나... 우선은 그것은 각설하고, 인터넷을 접속하는 ip는 공인된 기관에서 받는것이 마땅하나 사람들이 테스트 네트워크라던가, 아이피가 부족한 곳에다가 쓸수있도록 IP대역을 만들었으니 그것이 바로 사설아이피다.

사설아이피는 말그대로 사설아이피다. 이것으로 직접 공인IP 인터넷으로 나가질 못한다. 이것이 공인아이피로 나가기 위해서는 NAT하는 머신이 필요로 하게된다 게이트웨이를 구성한다고 이야기하기도 하는데, 정확한 말은 NAT이다. NAT는 Network Address Translation 로 사설아이피를 공인IP로 변환하는 역활을 한다.

Internet Assigned Numbers Authority (IANA)는 사설 망용의 3 블럭의 IP주소 공간을 확보해 두고 있다.
10.0.0.0 - 10.255.255.255
172.16.0.0 - 172.31.255.255
192.168.0.0 - 192.168.255.255

사설IP와 공인IP는 IP 숫자를 통해서 구분할 수 있다.



*/

#include "stdafx.h"
#include "jNet.h"
#include "interface/net/jINet_Util.h"

namespace nMech
{
	namespace nNET
	{
		namespace nUTIL
		{
			class jNet_Util : public jINet_Util
			{
				jINTERFACE_HEADER(jINet_Util);
			};

			tcstr jNet_Util::Addr2String(jIP_Address& pIP,tname_t buf)
			{
				return jSOCKADDR_IN::Addr2String(pIP,buf);
			}
			jIP_Address jNet_Util::String2Addr(tcstr szIP)	
			{
#if 0
				jIP_Address ip = jSOCKADDR_IN::String2Addr(szIP);
				ip.m_IP.s_addr = ntohl(ip.m_IP.s_addr);
				ip.port = ntohs(ip.port);
				return ip;
#else
				return jSOCKADDR_IN::String2Addr(szIP);
#endif
			}
			jIP_Address jNet_Util::String2Addr(tcstr szIP,unsigned short port)
			{
#if 0
				jIP_Address ip = jSOCKADDR_IN::String2Addr(szIP,port);
				ip.m_IP.s_addr = ntohl(ip.m_IP.s_addr);
				ip.port = ntohs(ip.port);
				return ip;
#else
				return jSOCKADDR_IN::String2Addr(szIP,port);
#endif
			}


			/*
			사설IP로 할당되어있는

			10.0.0.0 - 10.255.255.255
			172.16.0.0 - 172.31.255.255
			192.168.0.0 - 192.168.255.255

			대역 이외의 IP를 공인IP라고 한다. 
			*/
			bool jNet_Util::isPrivateIP(acstr strIp)
			{
				vector<astring> out;
				nString::jSplitA(strIp, ". ",out);
				if( out.size()!=4) return false;
				int num = ja_atoi(out[0].c_str());
				int num2 = ja_atoi(out[1].c_str());

				if(num==10) 
				{
					//jLOG(_T("%s is private"), jT(strIp));
					return true;
				}
				if(num==172)
				{
					if(num2>=16 && num2 <=31) 
					{
						//jLOG(_T("%s is private"), jT(strIp));
						return true;
					}
					//jLOG(_T("%s is public"), jT(strIp));
					return false;

				}
				else if(num==192 && num2==168) 
				{
					//jLOG(_T("%s is private"), jT(strIp));
					return true;
				}

				//jLOG(_T("%s is public"), jT(strIp));
				return false;
			}

			acstr jNet_Util::GetPrivateIP(aname32_t szBuf)
			{
				char localHostName[256];
				//IN_ADDR in_addr;
				HOSTENT *pHost;

				memset(localHostName, 0x00, 256);
				gethostname( localHostName, 256 );
				pHost = gethostbyname( localHostName );
				for(int i = 0; pHost->h_addr_list[i]; ++i)
				{
					ja_strcpy(szBuf, inet_ntoa(*(struct in_addr *)pHost->h_addr_list[i] ) );
					if(isPrivateIP(szBuf)) 
					{
						//jLOG(_T("private ip returned : %s"), jT(szBuf));
						return szBuf;
					}
				}
				ja_strcpy(szBuf , "127.0.0.1");
				return szBuf;
			}

			acstr jNet_Util::GetPublicIP(aname32_t szBuf)
			{
				char localHostName[256];
				//IN_ADDR in_addr;
				HOSTENT *pHost;
				/*
				사설IP로 할당되어있는

				10.0.0.0 - 10.255.255.255
				172.16.0.0 - 172.31.255.255
				192.168.0.0 - 192.168.255.255

				대역 이외의 IP를 공인IP라고 한다. 
				*/

				memset(localHostName, 0x00, 256);
				gethostname( localHostName, 256 );
				pHost = gethostbyname( localHostName );
				for(int i = 0; pHost->h_addr_list[i]; ++i)
				{
					ja_strcpy(szBuf, inet_ntoa(*(struct in_addr *)pHost->h_addr_list[i]) );
					jLOG(_T("gethostbyname ip = %s") , jT(szBuf) );
					if(isPrivateIP(szBuf )) 
						continue;

					//jLOG(_T("GetPublicIP() :  public ip returned : %s"), jT(szBuf));
					return	szBuf;
				}
				//jLOG(_T("GetPublicIP() :  private ip returned : %s"), jT(szBuf));
				return	GetPrivateIP(szBuf);
			}

		}// nNet::nUTIL
		namespace Impl
		{
			jINet_Util* jNet::GetUtil()			{				static nUTIL::jNet_Util a;		return &a;	}
		}

	} //nNET
}//nMech

