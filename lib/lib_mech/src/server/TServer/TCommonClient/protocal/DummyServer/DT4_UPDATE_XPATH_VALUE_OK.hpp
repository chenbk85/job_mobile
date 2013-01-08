
#ifndef DummyServer___DT4_UPDATE_XPATH_VALUE_OK__ 
#define DummyServer___DT4_UPDATE_XPATH_VALUE_OK__

#ifndef DummyServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DummyServer(DummyServer);
jxDECL_DummyServer(DT4_UPDATE_XPATH_VALUE_OK);
#endif //DummyServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nDummyServer
{
	const int pk_DT4_UPDATE_XPATH_VALUE_OK = /*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+10;
	/* tname256_t target_name;*/
	/* tname256_t doc;*/
	/* tname256_t xpath;*/
	/* tname256_t value;*/
	
	struct S_DT4_UPDATE_XPATH_VALUE_OK;
	bool READ_DT4_UPDATE_XPATH_VALUE_OK(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DT4_UPDATE_XPATH_VALUE_OK &param);
	struct S_DT4_UPDATE_XPATH_VALUE_OK
	{
		tname256_t target_name;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DummyServer
					void set_target_name(tcstr sz){jt_strncpy(target_name,nUNI::scb1024_t(sz).getT(), 256);	target_name[256-1]=0;}
					tcstr get_target_name(fname_t _buf){jt_strncpy(_buf, nUNI::scb256_t(target_name).getT() , 256);_buf[256-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DummyServer

		tname256_t doc;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DummyServer
					void set_doc(tcstr sz){jt_strncpy(doc,nUNI::scb1024_t(sz).getT(), 256);	doc[256-1]=0;}
					tcstr get_doc(fname_t _buf){jt_strncpy(_buf, nUNI::scb256_t(doc).getT() , 256);_buf[256-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DummyServer

		tname256_t xpath;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DummyServer
					void set_xpath(tcstr sz){jt_strncpy(xpath,nUNI::scb1024_t(sz).getT(), 256);	xpath[256-1]=0;}
					tcstr get_xpath(fname_t _buf){jt_strncpy(_buf, nUNI::scb256_t(xpath).getT() , 256);_buf[256-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DummyServer

		tname256_t value;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DummyServer
					void set_value(tcstr sz){jt_strncpy(value,nUNI::scb1024_t(sz).getT(), 256);	value[256-1]=0;}
					tcstr get_value(fname_t _buf){jt_strncpy(_buf, nUNI::scb256_t(value).getT() , 256);_buf[256-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DummyServer


		#ifndef jNOT_USE_DebugPrint_DummyServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DT4_UPDATE_XPATH_VALUE_OK > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("target_name"),target_name);
			jDebugPrint(_T("doc"),doc);
			jDebugPrint(_T("xpath"),xpath);
			jDebugPrint(_T("value"),value);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DT4_UPDATE_XPATH_VALUE_OK(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_DummyServer
	
	inline bool READ_DT4_UPDATE_XPATH_VALUE_OK(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DT4_UPDATE_XPATH_VALUE_OK &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.target_name, 256);
		nStream::Read(st,param.doc, 256);
		nStream::Read(st,param.xpath, 256);
		nStream::Read(st,param.value, 256);
		
		#ifndef jNOT_USE_DebugPrint_DummyServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DT4_UPDATE_XPATH_VALUE_OK : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_DummyServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_DummyServer
	inline jPacket_Base WRITE_DT4_UPDATE_XPATH_VALUE_OK(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DT4_UPDATE_XPATH_VALUE_OK &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.target_name);
			nStream::Write(st,param.doc);
			nStream::Write(st,param.xpath);
			nStream::Write(st,param.value);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DT4_UPDATE_XPATH_VALUE_OK;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DT4_UPDATE_XPATH_VALUE_OK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DT4_UPDATE_XPATH_VALUE_OK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DT4_UPDATE_XPATH_VALUE_OK(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  tcstr _target_name,  tcstr _doc,  tcstr _xpath,  tcstr _value)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_target_name);
			nStream::Write(st,_doc);
			nStream::Write(st,_xpath);
			nStream::Write(st,_value);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DT4_UPDATE_XPATH_VALUE_OK;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DT4_UPDATE_XPATH_VALUE_OK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DT4_UPDATE_XPATH_VALUE_OK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_DummyServer

}/*nDummyServer */ }/* nNET*/ } //nMech
#endif //DummyServer___DT4_UPDATE_XPATH_VALUE_OK__