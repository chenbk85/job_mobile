
#ifndef OrbHost___H_GET_UPDATE_XML_NODE__ 
#define OrbHost___H_GET_UPDATE_XML_NODE__

#ifndef OrbHost_jNOTUSE_PACKET_JXDEFINE
jxDECL_OrbHost(OrbHost);
jxDECL_OrbHost(H_GET_UPDATE_XML_NODE);
#endif //OrbHost_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nOrbHost
{
	/*[[ 원격지의 해당 XML노드의 값으로 새로 업데이트를 요청. 자식포함 ]]*/
	const int pk_H_GET_UPDATE_XML_NODE = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+18;
	/* tname256_t szDoc;*/
	/* tname1024_t szXPath;*/
	/* int8 idx;*/
	/* bool isAttr;*/
	/* tname32_t szTag;*/
	
	struct S_H_GET_UPDATE_XML_NODE;
	bool READ_H_GET_UPDATE_XML_NODE(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_H_GET_UPDATE_XML_NODE &param);
	struct S_H_GET_UPDATE_XML_NODE
	{
		tname256_t szDoc;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_OrbHost
					void set_szDoc(tcstr sz){jt_strncpy(szDoc,nUNI::scb1024_t(sz).getT(), 256);	szDoc[256-1]=0;}
					tcstr get_szDoc(fname_t _buf){jt_strncpy(_buf, nUNI::scb256_t(szDoc).getT() , 256);_buf[256-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_OrbHost

		tname1024_t szXPath;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_OrbHost
					void set_szXPath(tcstr sz){jt_strncpy(szXPath,nUNI::scb1024_t(sz).getT(), 1024);	szXPath[1024-1]=0;}
					tcstr get_szXPath(fname_t _buf){jt_strncpy(_buf, nUNI::scb1024_t(szXPath).getT() , 1024);_buf[1024-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_OrbHost

		int8 idx;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_OrbHost
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_OrbHost

		bool isAttr;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_OrbHost
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_OrbHost

		tname32_t szTag;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_OrbHost
					void set_szTag(tcstr sz){jt_strncpy(szTag,nUNI::scb1024_t(sz).getT(), 32);	szTag[32-1]=0;}
					tcstr get_szTag(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(szTag).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_OrbHost


		#ifndef jNOT_USE_DebugPrint_OrbHost
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< H_GET_UPDATE_XML_NODE > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("szDoc"),szDoc);
			jDebugPrint(_T("szXPath"),szXPath);
			jDebugPrint(_T("idx"),idx);
			jDebugPrint(_T("isAttr"),isAttr);
			jDebugPrint(_T("szTag"),szTag);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_H_GET_UPDATE_XML_NODE(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_OrbHost
	
	inline bool READ_H_GET_UPDATE_XML_NODE(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_H_GET_UPDATE_XML_NODE &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.szDoc, 256);
		nStream::Read(st,param.szXPath, 1024);
		nStream::Read(st,param.idx);
		nStream::Read(st,param.isAttr);
		nStream::Read(st,param.szTag, 32);
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("H_GET_UPDATE_XML_NODE : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_OrbHost

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_OrbHost
	inline jPacket_Base WRITE_H_GET_UPDATE_XML_NODE(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_H_GET_UPDATE_XML_NODE &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.szDoc);
			nStream::Write(st,param.szXPath);
			nStream::Write(st,param.idx);
			nStream::Write(st,param.isAttr);
			nStream::Write(st,param.szTag);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_H_GET_UPDATE_XML_NODE;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" H_GET_UPDATE_XML_NODE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" H_GET_UPDATE_XML_NODE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_H_GET_UPDATE_XML_NODE(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  tcstr _szDoc,  tcstr _szXPath, const int8 &_idx, const bool &_isAttr,  tcstr _szTag)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_szDoc);
			nStream::Write(st,_szXPath);
			nStream::Write(st,_idx);
			nStream::Write(st,_isAttr);
			nStream::Write(st,_szTag);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_H_GET_UPDATE_XML_NODE;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" H_GET_UPDATE_XML_NODE :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" H_GET_UPDATE_XML_NODE :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_OrbHost

}/*nOrbHost */ }/* nNET*/ } //nMech
#endif //OrbHost___H_GET_UPDATE_XML_NODE__