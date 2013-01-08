
#ifndef DummyServer___DT_RUN_CONSOLE_CMD__ 
#define DummyServer___DT_RUN_CONSOLE_CMD__

#ifndef DummyServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DummyServer(DummyServer);
jxDECL_DummyServer(DT_RUN_CONSOLE_CMD);
#endif //DummyServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nDummyServer
{
	/*[[ isCentral=false이면 모든더미에대해 	
콘솔명령을 실행.&#x0A; ]]*/
	const int pk_DT_RUN_CONSOLE_CMD = /*nMech::nNET::EProtocal_jINet_OGS_END+*/8000+11;
	/* dummy_id_t dummy_id;*/
	/* tname32_t category;*/
	/* tname32_t cmd;*/
	/* tstring arg[-1];*/
	
	struct S_DT_RUN_CONSOLE_CMD;
	bool READ_DT_RUN_CONSOLE_CMD(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DT_RUN_CONSOLE_CMD &param);
	struct S_DT_RUN_CONSOLE_CMD
	{
		dummy_id_t dummy_id;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DummyServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DummyServer

		tname32_t category;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DummyServer
					void set_category(tcstr sz){jt_strncpy(category,nUNI::scb1024_t(sz).getT(), 32);	category[32-1]=0;}
					tcstr get_category(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(category).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DummyServer

		tname32_t cmd;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DummyServer
					void set_cmd(tcstr sz){jt_strncpy(cmd,nUNI::scb1024_t(sz).getT(), 32);	cmd[32-1]=0;}
					tcstr get_cmd(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(cmd).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DummyServer

		std::vector<tstring> arg;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DummyServer
		tcstr get_arg(int i){ return arg[i].c_str();}
		void 	set_arg(int i, tcstr v){ arg[i] = v;}
		void insert_arg(tcstr v){ arg.push_back(v);}
		void clear_arg(){ arg.clear();}
		size_t size_arg(){ return arg.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DummyServer


		#ifndef jNOT_USE_DebugPrint_DummyServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DT_RUN_CONSOLE_CMD > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("dummy_id"),dummy_id);
			jDebugPrint(_T("category"),category);
			jDebugPrint(_T("cmd"),cmd);
			jDebugPrint(_T("arg"),arg);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DT_RUN_CONSOLE_CMD(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_DummyServer
	
	inline bool READ_DT_RUN_CONSOLE_CMD(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DT_RUN_CONSOLE_CMD &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.dummy_id);
		nStream::Read(st,param.category, 32);
		nStream::Read(st,param.cmd, 32);
		nMech::uint16 tempSizearg;
		nStream::Read(st,tempSizearg);
		param.arg.resize(tempSizearg);
		for(nMech::uint16 iTemparg=0;iTemparg<tempSizearg; ++iTemparg){
		nStream::Read(st,param.arg[iTemparg]);
		}
		
		#ifndef jNOT_USE_DebugPrint_DummyServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DT_RUN_CONSOLE_CMD : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_DummyServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_DummyServer
	inline jPacket_Base WRITE_DT_RUN_CONSOLE_CMD(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DT_RUN_CONSOLE_CMD &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.dummy_id);
			nStream::Write(st,param.category);
			nStream::Write(st,param.cmd);
			nMech::uint16 tempSizearg= (nMech::uint16)param.arg.size();
			nStream::Write(st,tempSizearg);
			for(nMech::uint16 iTemparg=0;iTemparg<tempSizearg; ++iTemparg){
			nStream::Write(st,param.arg[iTemparg]);
			}
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DT_RUN_CONSOLE_CMD;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DT_RUN_CONSOLE_CMD :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DT_RUN_CONSOLE_CMD :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DT_RUN_CONSOLE_CMD(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const dummy_id_t &_dummy_id,  tcstr _category,  tcstr _cmd, const std::vector<tstring> &_arg)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_dummy_id);
			nStream::Write(st,_category);
			nStream::Write(st,_cmd);
			nMech::uint16 tempSizearg = (nMech::uint16)_arg.size();
			nStream::Write(st,tempSizearg);
			for(nMech::uint16 iTemparg=0;iTemparg<tempSizearg; ++iTemparg){
			nStream::Write(st,_arg[iTemparg]);
			}
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DT_RUN_CONSOLE_CMD;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DT_RUN_CONSOLE_CMD :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DT_RUN_CONSOLE_CMD :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_DummyServer

}/*nDummyServer */ }/* nNET*/ } //nMech
#endif //DummyServer___DT_RUN_CONSOLE_CMD__