
#ifndef DBCacheServer___DC2CH_USER_LOGIN_CHANNEL_OK2__ 
#define DBCacheServer___DC2CH_USER_LOGIN_CHANNEL_OK2__

#ifndef DBCacheServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DBCacheServer(DBCacheServer);
jxDECL_DBCacheServer(DC2CH_USER_LOGIN_CHANNEL_OK2);
#endif //DBCacheServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nDBCacheServer
{
	const int pk_DC2CH_USER_LOGIN_CHANNEL_OK2 = /*nMech::nNET::EProtocal_jINet_OGS_END+*/6000+11;
	/* player_id_t pid;*/
	/* nAQ::Use_Hero hero[-1];*/
	/* nAQ::Use_Force force[-1];*/
	
	struct S_DC2CH_USER_LOGIN_CHANNEL_OK2;
	bool READ_DC2CH_USER_LOGIN_CHANNEL_OK2(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DC2CH_USER_LOGIN_CHANNEL_OK2 &param);
	struct S_DC2CH_USER_LOGIN_CHANNEL_OK2
	{
		player_id_t pid;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer

		std::vector<nAQ::Use_Hero> hero;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer
		nAQ::Use_Hero* get_hero(int i){ return &hero[i];}
		void 	set_hero(int i, nAQ::Use_Hero* v){ hero[i] = *v;}
		void insert_hero(nAQ::Use_Hero* v){ hero.push_back(*v);}
		void clear_hero(){ hero.clear();}
		size_t size_hero(){ return hero.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer

		std::vector<nAQ::Use_Force> force;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer
		nAQ::Use_Force* get_force(int i){ return &force[i];}
		void 	set_force(int i, nAQ::Use_Force* v){ force[i] = *v;}
		void insert_force(nAQ::Use_Force* v){ force.push_back(*v);}
		void clear_force(){ force.clear();}
		size_t size_force(){ return force.size();}
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer


		#ifndef jNOT_USE_DebugPrint_DBCacheServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DC2CH_USER_LOGIN_CHANNEL_OK2 > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("pid"),pid);
			jDebugPrint(_T("hero"),hero);
			jDebugPrint(_T("force"),force);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DC2CH_USER_LOGIN_CHANNEL_OK2(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_DBCacheServer
	
	inline bool READ_DC2CH_USER_LOGIN_CHANNEL_OK2(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DC2CH_USER_LOGIN_CHANNEL_OK2 &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.pid);
		nMech::uint16 tempSizehero;
		nStream::Read(st,tempSizehero);
		param.hero.resize(tempSizehero);
		for(nMech::uint16 iTemphero=0;iTemphero<tempSizehero; ++iTemphero){
		nStream::Read(st,param.hero[iTemphero]);
		}
		nMech::uint16 tempSizeforce;
		nStream::Read(st,tempSizeforce);
		param.force.resize(tempSizeforce);
		for(nMech::uint16 iTempforce=0;iTempforce<tempSizeforce; ++iTempforce){
		nStream::Read(st,param.force[iTempforce]);
		}
		
		#ifndef jNOT_USE_DebugPrint_DBCacheServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DC2CH_USER_LOGIN_CHANNEL_OK2 : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_DBCacheServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_DBCacheServer
	inline jPacket_Base WRITE_DC2CH_USER_LOGIN_CHANNEL_OK2(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DC2CH_USER_LOGIN_CHANNEL_OK2 &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.pid);
			nMech::uint16 tempSizehero= (nMech::uint16)param.hero.size();
			nStream::Write(st,tempSizehero);
			for(nMech::uint16 iTemphero=0;iTemphero<tempSizehero; ++iTemphero){
			nStream::Write(st,param.hero[iTemphero]);
			}
			nMech::uint16 tempSizeforce= (nMech::uint16)param.force.size();
			nStream::Write(st,tempSizeforce);
			for(nMech::uint16 iTempforce=0;iTempforce<tempSizeforce; ++iTempforce){
			nStream::Write(st,param.force[iTempforce]);
			}
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DC2CH_USER_LOGIN_CHANNEL_OK2;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC2CH_USER_LOGIN_CHANNEL_OK2 :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC2CH_USER_LOGIN_CHANNEL_OK2 :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DC2CH_USER_LOGIN_CHANNEL_OK2(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const player_id_t &_pid, const std::vector<nAQ::Use_Hero> &_hero, const std::vector<nAQ::Use_Force> &_force)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_pid);
			nMech::uint16 tempSizehero = (nMech::uint16)_hero.size();
			nStream::Write(st,tempSizehero);
			for(nMech::uint16 iTemphero=0;iTemphero<tempSizehero; ++iTemphero){
			nStream::Write(st,_hero[iTemphero]);
			}
			nMech::uint16 tempSizeforce = (nMech::uint16)_force.size();
			nStream::Write(st,tempSizeforce);
			for(nMech::uint16 iTempforce=0;iTempforce<tempSizeforce; ++iTempforce){
			nStream::Write(st,_force[iTempforce]);
			}
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DC2CH_USER_LOGIN_CHANNEL_OK2;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC2CH_USER_LOGIN_CHANNEL_OK2 :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC2CH_USER_LOGIN_CHANNEL_OK2 :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_DBCacheServer

}/*nDBCacheServer */ }/* nNET*/ } //nMech
#endif //DBCacheServer___DC2CH_USER_LOGIN_CHANNEL_OK2__