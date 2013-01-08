
#ifndef OrbHost___H_HELLO_OK__ 
#define OrbHost___H_HELLO_OK__

#ifndef OrbHost_jNOTUSE_PACKET_JXDEFINE
jxDECL_OrbHost(OrbHost);
jxDECL_OrbHost(H_HELLO_OK);
#endif //OrbHost_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nOrbHost
{
	const int pk_H_HELLO_OK = /*nMech::nNET::EProtocal_jINet_OGS_END+*/1000+5;
	/* tname32_t orbServiceName;*/
	/* tname32_t myName;*/
	/* bool isServerMode;*/
	
	struct S_H_HELLO_OK;
	bool READ_H_HELLO_OK(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_H_HELLO_OK &param);
	struct S_H_HELLO_OK
	{
		tname32_t orbServiceName;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_OrbHost
					void set_orbServiceName(tcstr sz){jt_strncpy(orbServiceName,nUNI::scb1024_t(sz).getT(), 32);	orbServiceName[32-1]=0;}
					tcstr get_orbServiceName(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(orbServiceName).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_OrbHost

		tname32_t myName;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_OrbHost
					void set_myName(tcstr sz){jt_strncpy(myName,nUNI::scb1024_t(sz).getT(), 32);	myName[32-1]=0;}
					tcstr get_myName(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(myName).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_OrbHost

		bool isServerMode;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_OrbHost
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_OrbHost


		#ifndef jNOT_USE_DebugPrint_OrbHost
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< H_HELLO_OK > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("orbServiceName"),orbServiceName);
			jDebugPrint(_T("myName"),myName);
			jDebugPrint(_T("isServerMode"),isServerMode);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_H_HELLO_OK(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_OrbHost
	
	inline bool READ_H_HELLO_OK(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_H_HELLO_OK &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.orbServiceName, 32);
		nStream::Read(st,param.myName, 32);
		nStream::Read(st,param.isServerMode);
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("H_HELLO_OK : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_OrbHost

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_OrbHost
	inline jPacket_Base WRITE_H_HELLO_OK(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_H_HELLO_OK &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.orbServiceName);
			nStream::Write(st,param.myName);
			nStream::Write(st,param.isServerMode);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_H_HELLO_OK;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" H_HELLO_OK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" H_HELLO_OK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_H_HELLO_OK(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  tcstr _orbServiceName,  tcstr _myName, const bool &_isServerMode)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_orbServiceName);
			nStream::Write(st,_myName);
			nStream::Write(st,_isServerMode);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_H_HELLO_OK;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" H_HELLO_OK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" H_HELLO_OK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_OrbHost

}/*nOrbHost */ }/* nNET*/ } //nMech
#endif //OrbHost___H_HELLO_OK__