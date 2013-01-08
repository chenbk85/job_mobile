/* file : Recv_OrbHost.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-10-30 13:51:27
comp.: pantavision.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_Orb.h"
#include "header/file_util.h"

#define READ_PACKET_ORB(X) READ_PACKET(X) nswb1024_t buf; \
	jOrbNode* pOrb=g_jOrb.findByIP(*pFromIP);if(!pOrb)return; PlugIn_Orb*pPO = g_pCurrPlugIn;

#define READ_PACKET_ORB_Data(X,Data) READ_PACKET_Data(X,Data) nswb1024_t buf; \
	jOrbNode* pOrb=g_jOrb.findByIP(*pFromIP); if(!pOrb)return;PlugIn_Orb*pPO = g_pCurrPlugIn;

// xml은 패킷중의 jIE*에 해당하는 변수명.
#define READ_PACKET_ORB_xml(PACKET,xml) S_##PACKET Data; Data.xml=GetjIXml()->CreateElement(); READ_PACKET_ORB_Data(PACKET,Data)

jNET_EVENT_BEGIN(PlugIn_Orb)
{
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn jIP_Address* pFromIP
	jNET_EVENT_RECEIVER(H_ECHO)
	{
		// PlugIn_Orb*pPO , nswb1024_t buf; jOrbNode* pOrb 
		READ_PACKET_ORB(H_ECHO);
		assert(pOrb);
	}
	
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn jIP_Address* pFromIP
	jNET_EVENT_RECEIVER(H_HELLO)
	{
		READ_PACKET(H_HELLO);

		jOrbNode* pOrb = g_jOrb.OrbNode_push_back(pS,*pFromIP,Data.orbServiceName,Data.myName,Data.isServerMode);
		if(!pOrb) return;
		nswb256_t buf;
		bool isMeServerMode = !pOrb->m_isRemoteServerMode ;// pOrb(원격지)가 서버모드이므로 현제 나는 클라이언트 모드이다.
		pOrb->Write_Packet(WRITE_H_HELLO_OK(buf,pOrb->GetService()->GetTagName(),Get_Uniq_AppNicName(),isMeServerMode));
		pOrb->_localCall(jS(H_HELLO),0);

	}

	jNET_EVENT_RECEIVER(H_HELLO_OK)
	{
		READ_PACKET(H_HELLO_OK);

		jOrbNode* pOrb = g_jOrb.OrbNode_push_back(pS,*pFromIP,Data.orbServiceName,Data.myName,Data.isServerMode );
		if(!pOrb) return;
		nswb256_t buf;
		pOrb->Write_Packet(WRITE_H_ECHO(buf, 0,_T("test echo")));
		pOrb->_localCall(jS(H_HELLO_OK),0);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn jIP_Address* pFromIP
	jNET_EVENT_RECEIVER(ORB_IS_ALIVE)
	{
		// PlugIn_Orb*pPO , nswb1024_t buf; jOrbNode* pOrb 
		READ_PACKET_ORB(ORB_IS_ALIVE);
		pOrb->Write_Packet(WRITE_ORB_ALIVE(buf));
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn jIP_Address* pFromIP
	jNET_EVENT_RECEIVER(ORB_ALIVE)
	{
		// PlugIn_Orb*pPO , nswb1024_t buf; jOrbNode* pOrb 
		READ_PACKET_ORB(ORB_ALIVE);
		pOrb->m_IsAlive.Set();
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn jIP_Address* pFromIP
	jNET_EVENT_RECEIVER(ORB_SEND_XML)
	{
		// PlugIn_Orb*pPO , nswb1024_t buf; jOrbNode* pOrb 
		READ_PACKET_ORB_xml(ORB_SEND_XML,xml);
		pOrb->_localCall(Data.xml->GetTagName(),Data.xml);
		GetjIXml()->DeleteElement(Data.xml);
	}
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn jIP_Address* pFromIP
	jNET_EVENT_RECEIVER(ORB_SEND_DATA)
	{
		// PlugIn_Orb*pPO , nswb1024_t buf; jOrbNode* pOrb 
		READ_PACKET_ORB(ORB_SEND_DATA);
		pOrb->_localCall(Data.name,(jIE*)&Data.data[0]);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn jIP_Address* pFromIP
	jNET_EVENT_RECEIVER(H_DISCONNECT)
	{
		// PlugIn_Orb*pPO , nswb1024_t buf; jOrbNode* pOrb 
		READ_PACKET_ORB(H_DISCONNECT);
		pOrb->_localCall(jS(H_DISCONNECT),0);
	}
	
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn jIP_Address* pFromIP
	jNET_EVENT_RECEIVER(H_SAVE_DOC)
	{
		// PlugIn_Orb*pPO , nswb1024_t buf; jOrbNode* pOrb 
		READ_PACKET_ORB(H_SAVE_DOC);
		jID* pD = GetjIXml()->GetObj(Data.doc);
		if(!pD) 
		{
			jLOG(jFUNC1 _T("error not found xml : %s"), Data.doc);
			return;
		}
		pD->Save();
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn jIP_Address* pFromIP
	jNET_EVENT_RECEIVER(H_COPY_XML_ELEMENT)
	{
		// PlugIn_Orb*pPO , nswb1024_t buf; jOrbNode* pOrb 
		READ_PACKET_ORB_xml(H_COPY_XML_ELEMENT,xml);
		jID* pD = GetjIXml()->GetObj(Data.szDoc);
		if(!pD)
		{
			jWARN(_T("ERROR jeORB::Recv_XML(%s) Doc not found"), Data.szDoc);
			return;
		}
		jIE* pE = pD->GetXPathNode(Data.szXPath, 0);
		if(!pE)
		{
			jWARN(_T("ERROR jeORB::Recv_XML(%s) Doc not found"), Data.szDoc);
			return;
		}
		jIE* peNew =0;
		if(Data.isInsertMode)
		{
			peNew = pE->InsertChildElement(_T("NULL"),Data.idx);
		}
		else
			peNew = pE->FindByOrder(Data.idx);

		if(!peNew)
		{
			peNew = pE->Persist(g_XmlNULL, jIVar::ETelement);
		}
		Data.xml->CopyTo(peNew);
		pOrb->_localCall(jT(Data.szOrbFunc),peNew);
		GetjIXml()->DeleteElement(Data.xml);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn jIP_Address* pFromIP
	jNET_EVENT_RECEIVER(H_DEL_XML_ELEMENT)
	{
		// PlugIn_Orb*pPO , nswb1024_t buf; jOrbNode* pOrb 
		READ_PACKET_ORB(H_DEL_XML_ELEMENT);
		
		jID* pD = GetjIXml()->GetObj(Data.szDoc);
		if(!pD)
		{
			jWARN(_T("ERROR jeORB::Recv_XML(%s) Doc not found"), Data.szDoc);
			return;
		}
		jIA* paDel=0;
		jIE* peDel = pD->GetXPathNode(Data.szXPath, &paDel);
		if(!peDel)
		{
			jWARN(_T("ERROR jeORB::Recv_XML(%s) Doc not found : %s"), Data.szDoc, Data.szXPath);
			return;
		}

		pOrb->_localCall(jT(Data.szOrbFunc),peDel);

		if(paDel)
		{
			peDel->EraseAttr(paDel->GetTagID() );
		}
		else
			peDel->Erase();
	}


	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn jIP_Address* pFromIP
	jNET_EVENT_RECEIVER(H_CHANGE_XML_NODE)
	{
		// PlugIn_Orb*pPO , nswb1024_t buf; jOrbNode* pOrb 
		READ_PACKET_ORB(H_CHANGE_XML_NODE);

		jID* pD = GetjIXml()->GetObj(Data.szDoc);
		if(!pD)
		{
			pD = GetjIXml()->Load(Data.szDoc);
			if(!pD)
			{
				jWARN(_T("ERROR jeORB::Recv_XML(%s) Doc not found"), Data.szDoc);
				return;
			}
		}
		jIE* pE = pD->GetXPathNode(Data.szXPath,0);
		if(!pE)
		{
			jWARN(_T("ERROR jeORB::Recv_XML(%s) Doc not found"), Data.szDoc);
			return;
		}
		jIE* peNew = pE->FindByOrder(Data.idx);
		assert(peNew);
		jIVar* pvTarget=0;
		jIA* pA =0;
		if(Data.isAttr)
		{
			pA = peNew->GetAttrNode(Data.szTag);
			pvTarget= pA->GetVar();
		}
		else
		{
			peNew->ChangeTagName(Data.szTag);
			pvTarget= peNew->GetVar();
		}

		if(Data.iType!=jIVar::ETelement)
		{
			pvTarget->FromString(Data.szData);
		}

		fname_t szBuf;
		if(pA)
		{
			jLOG(_T("값수정적용 속성 %s : %s=%s") , peNew->GetTagName()
				, pA->GetTagName() , pA->GetVar()->ToString(szBuf));
		}
		else
		{
			jLOG(_T("값수정적용 , %s=%s") , peNew->GetTagName()
				,peNew->GetVar()->ToString(szBuf) );
		}

		std::pair<jIE*, jIA*> newdata = make_pair(peNew,pA );
		pOrb->_localCall(jS(H_CHANGE_XML_NODE), (jIE*)&newdata);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn jIP_Address* pFromIP
	jNET_EVENT_RECEIVER(H_GET_UPDATE_XML_NODE)
	{
		// PlugIn_Orb*pPO , nswb1024_t buf; jOrbNode* pOrb 
		READ_PACKET_ORB(H_GET_UPDATE_XML_NODE);

		jID* pD = GetjIXml()->GetObj(Data.szDoc);
		if(!pD)
		{
			pD = GetjIXml()->Load(Data.szDoc);
			if(!pD)
			{
				jWARN(_T("ERROR jeORB::Recv_XML(%s) Doc not found"), Data.szDoc);
				return;
			}
		}
		assert(pD);
		jIE* pE = pD->GetXPathNode(Data.szXPath,0);
		if(!pE)
		{
			jLOG(_T("ERROR jeORB::Recv_XML(%s) Doc not found"), Data.szDoc);
			return;
		}
		jIE* peNew = pE->FindByOrder(Data.idx);
		jASSERT0(peNew && jFUNC );
		jIA* pA=0;
		if(Data.isAttr)
		{
			pA= peNew->GetAttrNode(Data.szTag);
		}
		pOrb->Notify_H_CHANGE_XML_NODE(pE, pA);
	}

	
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn jIP_Address* pFromIP
	jNET_EVENT_RECEIVER(H_GET_XML)
	{
		// PlugIn_Orb*pPO , nswb1024_t buf; jOrbNode* pOrb 
		READ_PACKET_ORB(H_GET_XML);

		jID* pD = GetjIXml()->GetObj(Data.szXml);
		if(!pD)jWARN(_T("ERROR : Receive_eGET_XML( %s )  xmlfile not found"),Data.szXml);

		afname_t szBuf;
		fname_t szBuf1;
		GetTempPathA(sizeof(szBuf), szBuf);
		jt_sprintf(szBuf1, _T("%s%s.xml"), jT(szBuf), pOrb->GetService()->GetTagName() );
		pD->SaveAsXML(szBuf1);

		{
			nswb1024_t szBuf;
			pOrb->Write_Packet(WRITE_H_PUT_XML(szBuf, szBuf1,Data.szXml));
		}
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn jIP_Address* pFromIP
	jNET_EVENT_RECEIVER(H_PUT_XML)
	{
		// PlugIn_Orb*pPO , nswb1024_t buf; jOrbNode* pOrb 
		READ_PACKET_ORB(H_PUT_XML);

		tstring sBuf;
		asdf_read_file(Data.szTempFile,sBuf);

		fname_t szBuf;
		jt_sprintf(szBuf,_T("%s=%s"),pOrb->GetRemoteAppName(), Data.szXml);
		jID* pD  = GetjIXml()->GetObj(szBuf);
		if(pD) GetjIXml()->UnLoad(pD);
		pD = GetjIXml()->Load(szBuf, &sBuf[0]);

		pOrb->call_XmlEvent(Data.szXml,pD);
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn jIP_Address* pFromIP
	jNET_EVENT_RECEIVER(H_NOTIFY_HWND)
	{
		// PlugIn_Orb*pPO , nswb1024_t buf; jOrbNode* pOrb 
		READ_PACKET_ORB(H_NOTIFY_HWND);
		pOrb->m_hWndTarget = (HWND)Data.hWnd;
		if(Data.hWnd)
			pOrb->_localCall(jS(H_NOTIFY_HWND),0);

		pOrb->Write_Packet(WRITE_H_NOTIFY_HWND_OK(buf, (uint32)g_jOrb.m_hWnd));
	}

	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn jIP_Address* pFromIP
	jNET_EVENT_RECEIVER(H_SEND_LOG)
	{
		// PlugIn_Orb*pPO , nswb1024_t buf; jOrbNode* pOrb 
		READ_PACKET_ORB(H_SEND_LOG);
		std::pair<tcstr,bool> arg;
		arg.first = Data.msg;
		arg.second = Data.type;
		pOrb->_localCall(jS(H_SEND_LOG),(jIE*)&arg);
	}

	
#if 0
	//jIPacketSocket_IOCP* pS,B YTE *pReadBuff_, jPacketLen_t dwLen, void* pPlugIn jIP_Address* pFromIP
	jNET_EVENT_RECEIVER(aaa)
	{
		// PlugIn_Orb*pPO , nswb1024_t buf; jOrbNode* pOrb 
		READ_PACKET_ORB(aaa);
	}
#endif
}
jNET_EVENT_END(PlugIn_Orb);
