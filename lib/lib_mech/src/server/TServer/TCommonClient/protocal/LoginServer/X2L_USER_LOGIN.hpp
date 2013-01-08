
#ifndef LoginServer___X2L_USER_LOGIN__ 
#define LoginServer___X2L_USER_LOGIN__

#ifndef LoginServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_LoginServer(LoginServer);
jxDECL_LoginServer(X2L_USER_LOGIN);
#endif //LoginServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nLoginServer
{
	/*[[ 클라이언트 로긴접속&#x0A; ]]*/
	const int pk_X2L_USER_LOGIN = /*nMech::nNET::EProtocal_jINet_OGS_END+*/2000+11;
	/* aname32_t world;*/
	/* wname64_t id;*/
	/* uint8 pwd[-1];*/
	/* aname32_t ver;*/
	/* aname32_t cpp_ver;*/
	
	struct S_X2L_USER_LOGIN;
	bool READ_X2L_USER_LOGIN(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_X2L_USER_LOGIN &param);
	struct S_X2L_USER_LOGIN
	{
		aname32_t world;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_LoginServer
					void set_world(tcstr sz){ja_strncpy(world,nUNI::scb1024_t(sz).getA(), 32);	world[32-1]=0;}
					tcstr get_world(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(world).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_LoginServer

		wname64_t id;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_LoginServer
					void set_id(tcstr sz){jw_strncpy(id,nUNI::scb1024_t(sz).getW(), 64);	id[64-1]=0;}
					tcstr get_id(fname_t _buf){jt_strncpy(_buf, nUNI::scb64_t(id).getT() , 64);_buf[64-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_LoginServer

		std::vector<uint8> pwd;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_LoginServer
		uint8* get_pwd(int i){ return &pwd[i];}
		void 	set_pwd(int i, uint8* v){ pwd[i] = *v;}
		void insert_pwd(uint8* v){ pwd.push_back(*v);}
		void clear_pwd(){ pwd.clear();}
		size_t size_pwd(){ return pwd.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_LoginServer

		aname32_t ver;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_LoginServer
					void set_ver(tcstr sz){ja_strncpy(ver,nUNI::scb1024_t(sz).getA(), 32);	ver[32-1]=0;}
					tcstr get_ver(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(ver).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_LoginServer

		aname32_t cpp_ver;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_LoginServer
					void set_cpp_ver(tcstr sz){ja_strncpy(cpp_ver,nUNI::scb1024_t(sz).getA(), 32);	cpp_ver[32-1]=0;}
					tcstr get_cpp_ver(fname_t _buf){jt_strncpy(_buf, nUNI::scb32_t(cpp_ver).getT() , 32);_buf[32-1]=0;return _buf;}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_LoginServer


		#ifndef jNOT_USE_DebugPrint_LoginServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< X2L_USER_LOGIN > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("world"),world);
			jDebugPrint(_T("id"),id);
			jDebugPrint(_T("pwd"),pwd);
			jDebugPrint(_T("ver"),ver);
			jDebugPrint(_T("cpp_ver"),cpp_ver);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_X2L_USER_LOGIN(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_LoginServer
	
	inline bool READ_X2L_USER_LOGIN(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_X2L_USER_LOGIN &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.world, 32);
		nStream::Read(st,param.id, 64);
		nMech::uint16 tempSizepwd;
		nStream::Read(st,tempSizepwd);
		param.pwd.resize(tempSizepwd);
		for(nMech::uint16 iTemppwd=0;iTemppwd<tempSizepwd; ++iTemppwd){
		nStream::Read(st,param.pwd[iTemppwd]);
		}
		nStream::Read(st,param.ver, 32);
		nStream::Read(st,param.cpp_ver, 32);
		
		#ifndef jNOT_USE_DebugPrint_LoginServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("X2L_USER_LOGIN : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_LoginServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_LoginServer
	inline jPacket_Base WRITE_X2L_USER_LOGIN(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_X2L_USER_LOGIN &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.world);
			nStream::Write(st,param.id);
			nMech::uint16 tempSizepwd= (nMech::uint16)param.pwd.size();
			nStream::Write(st,tempSizepwd);
			for(nMech::uint16 iTemppwd=0;iTemppwd<tempSizepwd; ++iTemppwd){
			nStream::Write(st,param.pwd[iTemppwd]);
			}
			nStream::Write(st,param.ver);
			nStream::Write(st,param.cpp_ver);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_X2L_USER_LOGIN;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2L_USER_LOGIN :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2L_USER_LOGIN :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_X2L_USER_LOGIN(nNET::nStream::_jNetStreamWriteBufferBase &buffer ,  acstr _world,  wcstr _id, const std::vector<uint8> &_pwd,  acstr _ver,  acstr _cpp_ver)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_world);
			nStream::Write(st,_id);
			nMech::uint16 tempSizepwd = (nMech::uint16)_pwd.size();
			nStream::Write(st,tempSizepwd);
			for(nMech::uint16 iTemppwd=0;iTemppwd<tempSizepwd; ++iTemppwd){
			nStream::Write(st,_pwd[iTemppwd]);
			}
			nStream::Write(st,_ver);
			nStream::Write(st,_cpp_ver);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_X2L_USER_LOGIN;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" X2L_USER_LOGIN :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" X2L_USER_LOGIN :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_LoginServer

}/*nLoginServer */ }/* nNET*/ } //nMech
#endif //LoginServer___X2L_USER_LOGIN__