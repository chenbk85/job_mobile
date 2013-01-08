/* file : test_jNet_OGS_util.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-29 16:43:10
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "base/jTestUnit.h"

using namespace nMech;
namespace 
{
	using namespace nMech::nNET;
	jTEST(inet_addr_inet_ntoa)
	{

		#define TEST_IP  _T("127.23.64.234")
		#define TEST_IP_STR _T("127.23.64.234:2389")
		sockaddr_in addr;
		addr.sin_addr.s_addr = nUTIL::inet_addr(TEST_IP);

		in_addr in = addr.sin_addr;
		tname_t szIP;
		nUTIL::inet_ntoa(in , szIP);

		jTEST_CHECK(std::tstring(szIP)== TEST_IP );


		jIP_Address ip = jSOCKADDR_IN::String2Addr(TEST_IP_STR);// network ip를 host ip로 변환 !
		jEQUAL(ip.port , 2389);

		tname_t buf2;
		//jIP_Address는 스트링을 host측의 ulong형 IP와 ushort형 port로 변환된다.
		in_addr test_ip2;

		test_ip2.s_addr = htonl(ip.m_IP.s_addr);
		nUTIL::inet_ntoa(test_ip2,buf2);
		jTEST_CHECK(std::tstring(buf2)== TEST_IP);

		tname_t bufIP;
		tstring strIP = jSOCKADDR_IN::Addr2String(ip,bufIP);
		jTEST_CHECK(strIP== TEST_IP_STR);

		jIP_Address ip2 = jSOCKADDR_IN::String2Addr(strIP.c_str());
		jTEST_CHECK(ip==ip2);
		jEQUAL(ip.m_IP.s_addr , ip2.m_IP.s_addr);
		jEQUAL(ip.port , ip2.port);

	}


	jTEST(jIP_Address_map_test)
	{
		std::map<jIP_Address,std::tstring> testMap;
		jIP_Address ip1(1,2),ip2(3,4);
		testMap[ip1] = _T("ip1");
		bool is = testMap.count(ip2);
		testMap[ip2] = _T("ip2");
		tstring s1 = testMap.find(ip1)->second ;
		tstring s2 = testMap[ip2];
		jTEST_CHECK(s1==std::tstring(_T("ip1")));
		jTEST_CHECK(s2==std::tstring(_T("ip2")));
		jIP_Address ip3 = ip1;
		tstring s3 = testMap[ip3];
		jTEST_CHECK(s3==std::tstring(_T("ip1")));

	}
}


