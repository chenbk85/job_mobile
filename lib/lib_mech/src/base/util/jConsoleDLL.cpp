/* file : jConsoleDLL_Net.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-03-10 18:35:53
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jConsoleDLL.h"
#include "interface/jIConsoleCmd.h"
#include "interface/xml/jIXml.h"
#include "interface/net/jINet.h"

#define USE_NOT_AUTO_CMD

namespace nMech
{
	namespace nCONSOLE
	{
		jLIST_TYPEDEF_map(std::tstring, jIE*,g_NetConfigList);
		namespace nIMPL
		{
#ifdef USE_NOT_AUTO_CMD
			bool net_configs(const std::vector<std::tstring>& arg)
#else
			jCONSOLE_CMD_AUTO(net,configs,0,"�ε��� jConsoleDLL_Net��� ����Ʈ ���.","")
#endif
			{
				g_NetConfigList_it it = g_NetConfigList.begin(), ie = g_NetConfigList.end();
				for(; it!=ie; ++it)
				{
					jLOG(_T("\t%s"),it->second->GetTagName());
				}
				return true;
			}

#ifdef USE_NOT_AUTO_CMD
			bool net_start(const std::vector<std::tstring>& arg)
#else
			jCONSOLE_CMD_AUTO(net,start,0,"�ε��� jConsoleDLL_Net��⿡�� ��Ʈ������� ���� �Ѵ�.","<net_config_node>")
#endif
			{
				g_NetConfigList_it it = g_NetConfigList.find(arg[0]);
				if(it==g_NetConfigList.end())
				{
					jWARN(_T("@net.start: %s not found"),arg[0].c_str());
					return false;
				}
				print_memory(jFUNC);
				nInterface::g_pjINet_OGS->RunNetObject(it->second);
				print_memory(jFUNC);
				return true;
			}
#ifdef USE_NOT_AUTO_CMD
			bool net_stop(const std::vector<std::tstring>& arg)
#else
			jCONSOLE_CMD_AUTO(net,stop,0,"�ε��� jConsoleDLL_Net��⿡�� ��Ʈ������� �����Ѵ�.","<net_config_node> [bool:�������]")
#endif
			{
				g_NetConfigList_it it = g_NetConfigList.find(arg[0]);
				if(it==g_NetConfigList.end())
				{
					jWARN(_T("@net.stop : %s not found"),arg[0].c_str());
					return false;
				}
				bool stopIm = true;
				if(arg.size()==2)
				{
					stopIm = jt_atoi(arg[1].c_str());
				}
				print_memory(jFUNC);
				nInterface::g_pjINet_OGS->StopNetObject(it->second,false,stopIm);
				print_memory(jFUNC);
				return true;
			}

#ifdef USE_NOT_AUTO_CMD
			bool con_clear_cmd(const std::vector<std::tstring>& arg)
#else
			jCONSOLE_CMD_AUTO(con , clear_cmd , 0 ,"��ɸ���Ʈ���� �ʱ�ȭ �Ѵ�." ,"")
#endif
			{

				return true;
			}
		}

		bool jConsoleDLL_Net::ParseCmd(tcstr szCommand) 
		{
			return false;
		}
		bool jConsoleDLL_Net::Start(tcstr szNetConfigFile,tcstr szNetConfig_Name) 
		{
			jRETURN_ret(false, szNetConfigFile && jt_strlen(szNetConfigFile));
			jRETURN_ret(false, szNetConfig_Name && jt_strlen(szNetConfig_Name))
			jID* pD = GetjIXml()->Load(szNetConfigFile);
			if(!pD)
			{
				jWARN(_T("%s �ε� ����"),szNetConfigFile);
				return false;
			}
			m_eNetConfig = pD->Find(szNetConfig_Name);
			if(!m_eNetConfig)
			{
				jWARN(_T("%s ���� %s�׸��� �����ϴ�."),szNetConfigFile,szNetConfig_Name);
				return false;
			}
			g_NetConfigList[szNetConfig_Name] = m_eNetConfig;

			if(!nInterface::g_pjINet_OGS)
			{
				jMB("<jINet b_ENABLE='1'>jNet.dll</jINet>�� �߰��Ͻÿ�", "nInterface::g_pjINet_OGS==NULL");
				exit(1);
			}
			bool is = nInterface::g_pjINet_OGS->CreateNetObject(m_eNetConfig);
			if(!is) return false;
			nInterface::g_pjINet_OGS->RunNetObject(m_eNetConfig);
			return true;
		}

		void jConsoleDLL_Net::End() 
		{
			if(m_eNetConfig)
				nInterface::g_pjINet_OGS->StopNetObject(m_eNetConfig, true);

			//jt_sprintf(szBuf , _T("Stoped:_%s"),m_eNetConfig->GetTagName() );
			//nCONSOLE::Get_jIConsoleCmd()->Run(jS(con) , jS(set_title) , szBuf, true);

		}

	}//namespace nCONSOLE
}

