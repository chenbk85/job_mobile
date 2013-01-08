
#ifndef OrbHost___H_DEL_XML_ELEMENT__ 
#define OrbHost___H_DEL_XML_ELEMENT__

#ifndef OrbHost_jNOTUSE_PACKET_JXDEFINE
jxDECL_OrbHost(OrbHost);
jxDECL_OrbHost(H_DEL_XML_ELEMENT);
#endif //OrbHost_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nOrbHost
{
	const int pk_H_DEL_XML_ELEMENT = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+16;
	/* tname256_t szDoc;*/
	/* tname1024_t szXPath;*/
	/* aname32_t szOrbFunc;*/
	
	struct S_H_DEL_XML_ELEMENT;
	bool READ_H_DEL_XML_ELEMENT(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_H_DEL_XML_ELEMENT &param);
	struct S_H_DEL_XML_ELEMENT
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

		aname32_t szOrbFunc;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_OrbHost
					void set_szOrbFunc(tcstr sz){ja_strncpy(szOrbFunc,nUNI::scb1024_t(sz).getA(), 32);	szOrbFunc[32-1]=0;}
					tcstr get_szOrbFunc(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(szOrbFunc).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_OrbHost


		#ifndef jNOT_USE_DebugPrint_OrbHost
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< H_DEL_XML_ELEMENT > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("szDoc"),szDoc);
			jDebugPrint(_T("szXPath"),szXPath);
			jDebugPrint(_T("szOrbFunc"),szOrbFunc);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_H_DEL_XML_ELEMENT(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_OrbHost
	
	inline bool READ_H_DEL_XML_ELEMENT(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_H_DEL_XML_ELEMENT &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.szDoc, 256);
		nStream::Read(st,param.szXPath, 1024);
		nStream::Read(st,param.szOrbFunc, 32);
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("H_DEL_XML_ELEMENT : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_OrbHost

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_OrbHost
	inline jPacket_Base WRITE_H_DEL_XML_ELEMENT(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_H_DEL_XML_ELEMENT &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.szDoc);
			nStream::Write(st,param.szXPath);
			nStream::Write(st,param.szOrbFunc);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_H_DEL_XML_ELEMENT;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" H_DEL_XML_ELEMENT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" H_DEL_XML_ELEMENT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_H_DEL_XML_ELEMENT(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  tcstr _szDoc,  tcstr _szXPath,  acstr _szOrbFunc)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_szDoc);
			nStream::Write(st,_szXPath);
			nStream::Write(st,_szOrbFunc);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_H_DEL_XML_ELEMENT;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" H_DEL_XML_ELEMENT :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" H_DEL_XML_ELEMENT :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_OrbHost

}/*nOrbHost */ }/* nNET*/ } //nMech
#endif //OrbHost___H_DEL_XML_ELEMENT__