
#ifndef OrbHost___H_SAVE_DOC__ 
#define OrbHost___H_SAVE_DOC__

#ifndef OrbHost_jNOTUSE_PACKET_JXDEFINE
jxDECL_OrbHost(OrbHost);
jxDECL_OrbHost(H_SAVE_DOC);
#endif //OrbHost_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nOrbHost
{
	const int pk_H_SAVE_DOC = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+13;
	/* tname256_t doc;*/
	
	struct S_H_SAVE_DOC;
	bool READ_H_SAVE_DOC(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_H_SAVE_DOC &param);
	struct S_H_SAVE_DOC
	{
		tname256_t doc;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_OrbHost
					void set_doc(tcstr sz){jt_strncpy(doc,nUNI::scb1024_t(sz).getT(), 256);	doc[256-1]=0;}
					tcstr get_doc(fname_t _buf){jt_strncpy(_buf, nUNI::scb256_t(doc).getT() , 256);_buf[256-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_OrbHost


		#ifndef jNOT_USE_DebugPrint_OrbHost
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< H_SAVE_DOC > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("doc"),doc);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_H_SAVE_DOC(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_OrbHost
	
	inline bool READ_H_SAVE_DOC(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_H_SAVE_DOC &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.doc, 256);
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("H_SAVE_DOC : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_OrbHost

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_OrbHost
	inline jPacket_Base WRITE_H_SAVE_DOC(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_H_SAVE_DOC &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.doc);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_H_SAVE_DOC;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" H_SAVE_DOC :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" H_SAVE_DOC :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_H_SAVE_DOC(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  tcstr _doc)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_doc);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_H_SAVE_DOC;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" H_SAVE_DOC :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" H_SAVE_DOC :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_OrbHost

}/*nOrbHost */ }/* nNET*/ } //nMech
#endif //OrbHost___H_SAVE_DOC__