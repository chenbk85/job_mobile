/* file : jSQ_bind_jINet.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-25 12:29:22
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __jSQ_bind_jINet_header__
#define __jSQ_bind_jINet_header__
#pragma once


using namespace nMech::nNET;
DECLARE_INSTANCE_TYPE(jPacket_Base);
DECLARE_INSTANCE_TYPE(jIP_Address);
DECLARE_INSTANCE_TYPE(jIPacketSocket_IOCP);
DECLARE_INSTANCE_TYPE(jIPlugIn_Net);
namespace nMech
{
	namespace nSQ
	{
		template<typename DerivedT,typename BaseT>
		struct jIPlugIn_Net_SQ : public BaseT
		{
			SquirrelObject m_sqNET_EVENT_TABLE;
			virtual SquirrelObject* GetSQTable()
			{
				return m_sqNET_EVENT_TABLE.IsNull()? 0 : &m_sqNET_EVENT_TABLE;
			}
			virtual tcstr GetPlugInNicName(){ return m_pE->GetTagName();}
			virtual bool Load_SQ()
			{
				nFileSystem::jFolder dir;
				fname_t szFile;
				jt_sprintf(szFile, _T("sq\\net\\%s.nut"), GetPlugInNicName() );
				if(!dir.Is_Exist( szFile ) )
				{
					jLOG(jFUNC1 _T("loading skip : %s"),szFile);
					return false;
				}
				try
				{
					GetjISQ()->VM_RunScript(GetjISQ()->VM_CompileScript(szFile));

					SquirrelObject root = GetjISQ()->VM_GetRootTable();
					jt_sprintf(szFile , _T("jNET_EVENT_TABLE_%s"), GetPlugInNicName() );
					m_sqNET_EVENT_TABLE = root.GetValue(szFile);
					if(m_sqNET_EVENT_TABLE.IsNull()) return false;

					fname_t szSQName;
					jt_sprintf(szSQName, _T("m_%s"),m_pE->GetAttr(jS(NAME)) );
					BindVariable(m_sqNET_EVENT_TABLE, ((DerivedT*)this), szSQName);
				}
				jSQ_CATCH_ERROR();
				return true;
			}
		};//struct jIPlugIn_Net_SQ : public BaseT
	}//namespace nSQ
}//namespace nMech

#define jSQ_REGIST_BIND_jINetPlugIn_SERVER(PLUGIN,USER_CLASS,KEY)\
						DECLARE_INSTANCE_TYPE(USER_CLASS);\
						DECLARE_INSTANCE_TYPE(PLUGIN);\
						jSQ_gfn_DEF2(tcstr,USER_CLASS,GetName)(USER_CLASS* pThis){return pThis->GetName();}\
						jSQ_gfn_DEF2(USER_CLASS*,PLUGIN,GetUser)(PLUGIN* pThis,KEY pS){return pThis->GetUser(pS);}\
						jSQ_gfn_DEF(bool, PLUGIN,for_each_UserSocket)\
						{	jSQ_init_pThis(PLUGIN);pThis->for_each_UserSocket(sa.GetObjectHandle(arg_Start++));return true;}\
						jSQ_REGIST_BIND(PLUGIN)\

#define jSQ_REGIST_BIND_jINetPlugIn_CLIENT(PLUGIN)\
	DECLARE_INSTANCE_TYPE(PLUGIN);\
	jSQ_REGIST_BIND(PLUGIN)\


#define jSQ_Interface_jINetPlugIn_SERVER(PLUGIN)\
					jSQ_Interface(PLUGIN);\
					jSQ_gfn(PLUGIN,GetUser,"","");\
					jSQ_gfn(PLUGIN,for_each_UserSocket,"function f(pS)","")\


#endif // __jSQ_bind_jINet_header__
