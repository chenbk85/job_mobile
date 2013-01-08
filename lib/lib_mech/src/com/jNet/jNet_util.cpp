/* file : jNet_util.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2007-07-05 17:05:51
comp.: pantavision.co.kr
title : 
desc : 


[edit]
�缳IP (Private IP) #
�׷� ���⼭ �缳IP�� �������� �𸣴� ������� ���ؼ� ���� ������ ������ ������ �ϰڴ�.
�缳�����Ǵ�? ���״�� �缳 IP��.
��ǻ�Ͱ� ���ͳݿ� ������ �Ϸ��� IP��� ���� �ʿ��ϴ�. ���ͳ� �ּ�... �׷��� ������ ���ͳ��� ó�� �����Ҷ����ϴ��� �̷��� ���� ��ǻ�Ͱ� �þ���̸� ������ ������ǰ���� ���ͳ��� �žƼ� Ȩ��Ʈ��ŷ�̴� ���ڸ���Ʈ ����Ʈ�� �̷����� ���� �ͱ����� ������ ���ߴ� ���̿���.
�׷��� �׷��� �͵��� �� �缳������ �ذ�� �� ������... �켱�� �װ��� �����ϰ�, ���ͳ��� �����ϴ� ip�� ���ε� ������� �޴°��� �����ϳ� ������� �׽�Ʈ ��Ʈ��ũ�����, �����ǰ� ������ �����ٰ� �����ֵ��� IP�뿪�� ��������� �װ��� �ٷ� �缳�����Ǵ�.

�缳�����Ǵ� ���״�� �缳�����Ǵ�. �̰����� ���� ����IP ���ͳ����� ������ ���Ѵ�. �̰��� ���ξ����Ƿ� ������ ���ؼ��� NAT�ϴ� �ӽ��� �ʿ�� �ϰԵȴ� ����Ʈ���̸� �����Ѵٰ� �̾߱��ϱ⵵ �ϴµ�, ��Ȯ�� ���� NAT�̴�. NAT�� Network Address Translation �� �缳�����Ǹ� ����IP�� ��ȯ�ϴ� ��Ȱ�� �Ѵ�.

Internet Assigned Numbers Authority (IANA)�� �缳 ������ 3 ���� IP�ּ� ������ Ȯ���� �ΰ� �ִ�.
10.0.0.0 - 10.255.255.255
172.16.0.0 - 172.31.255.255
192.168.0.0 - 192.168.255.255

�缳IP�� ����IP�� IP ���ڸ� ���ؼ� ������ �� �ִ�.



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
			�缳IP�� �Ҵ�Ǿ��ִ�

			10.0.0.0 - 10.255.255.255
			172.16.0.0 - 172.31.255.255
			192.168.0.0 - 192.168.255.255

			�뿪 �̿��� IP�� ����IP��� �Ѵ�. 
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
				�缳IP�� �Ҵ�Ǿ��ִ�

				10.0.0.0 - 10.255.255.255
				172.16.0.0 - 172.31.255.255
				192.168.0.0 - 192.168.255.255

				�뿪 �̿��� IP�� ����IP��� �Ѵ�. 
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

