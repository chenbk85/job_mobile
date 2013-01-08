/* file : jClientSession_Asio.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-03-19 19:09:58
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"

#include "jClientSession_Asio.h"

#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>    //타이머 사용을 위해

#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#ifdef _DEBUG
#define ASIO_DEBUG_LOG(...)
//#define ASIO_DEBUG_LOG jWARN
#else
#define ASIO_DEBUG_LOG(...)
#endif


using namespace nMech::nNET;
DECLARE_INSTANCE_TYPE(jIPlugin_jIClientSession_Asio);

namespace nMech
{
	namespace nNET
	{
		typedef boost::asio::deadline_timer MOB_Timer;

		//namespace Impl		{

			using boost::asio::ip::tcp;

			static void default_timer_handle(int term ,tstring sName, MOB_Timer* pTimer,const boost::system::error_code& error)
			{
				if (error == boost::asio::error::operation_aborted) 
				{
					ASIO_DEBUG_LOG(_T("Timer was canceled"));
					return;
				}
				ASIO_DEBUG_LOG(_T("default_timer_handle was called %s"),sName.c_str());
				pTimer->expires_at(pTimer->expires_at() + boost::posix_time::seconds(term));
				pTimer->async_wait(boost::bind(default_timer_handle,term,sName, pTimer,boost::asio::placeholders::error));
			}

			//#--------------------------------------------------------------------------
			struct jIO_Service
				//#--------------------------------------------------------------------------
			{
				tstring m_sName;
				boost::asio::io_service m_io_service;
				boost::thread *m_thread;
				MOB_Timer* m_pTimer;
				jIO_Service(cstr szName):m_sName(szName) ,m_thread(0) , m_pTimer(0)
				{
					const int term =10;
					m_pTimer= new MOB_Timer(m_io_service, boost::posix_time::seconds(term));
					m_pTimer->async_wait(boost::bind(default_timer_handle, term,m_sName, m_pTimer , boost::asio::placeholders::error));
					run_thread();
				}
				~jIO_Service()
				{ 
					m_pTimer->cancel();
					SAFE_DELETE(m_pTimer);
					SAFE_DELETE(m_thread); 
				}
				void run_thread()
				{
					if(m_thread) return;
					m_thread = new boost::thread(boost::bind(&boost::asio::io_service::run, &m_io_service) );
				}
			};
			typedef boost::shared_ptr<jIO_Service> jIO_Service_sp_t;


#define jCHECK_ERROR_AND_CLOSE(error)\
if (error)\
{\
	jWARN(jFUNC _T("error=%s"),error.message().c_str());do_close();\
	return;\
}\

			struct jPacketData
			{
			public:
				enum { HEADER_LENGTH = sizeof(asio_header_type_t) };

				jPacketData()		: body_length_(0)	{	}
				size_t		get_length() const	{		return HEADER_LENGTH + body_length_;	}
				char*		get_body(){ return data_+HEADER_LENGTH;}

				void set_body_length(size_t new_length)
				{
					body_length_ = new_length;
					if (body_length_ > MAX_BODY_LENGTH)
						throw astring(__FUNCTION__) + astring (">body_length_ > MAX_BODY_LENGTH ");
				}

				bool decode_header()
				{
					using namespace std; // For strncat and atoi.
					asio_header_type_t iLen=0;
					memcpy(&iLen, data_,sizeof(iLen));
					body_length_ = iLen;
					if (body_length_ > MAX_BODY_LENGTH)
					{
						throw astring(__FUNCTION__) + astring ("> body_length_ > MAX_BODY_LENGTH ");
					}
					return true;
				}

				void encode_header()
				{
					using namespace std; // For sprintf and memcpy.
					asio_header_type_t iLen = body_length_;
					memcpy(data_ , &iLen,sizeof(iLen));
				}

				char data_[HEADER_LENGTH + MAX_BODY_LENGTH];
				size_t body_length_;
			};

			typedef std::deque<jPacketData> jPacketData_queue;
			static int s_ijClientSession_Asio =0;
			//#--------------------------------------------------------------------------
			class jClientSession_Asio 
				:public boost::enable_shared_from_this<jClientSession_Asio>
				,private boost::noncopyable

			//#--------------------------------------------------------------------------
			{
			public:
				jIE* m_pE;
				jIO_Service_sp_t m_jIO_Service;
				tcp::resolver::iterator endpoint_iterator;


				jClientSession_Asio(jIO_Service_sp_t pIO
					,tcp::resolver::iterator et
					,jIPlugin_jIClientSession_Asio* pPlugIn
					,jIE* peSession
					)
					:socket_(pIO->m_io_service)
					,m_jIO_Service(pIO)
					,m_pPlugIn(pPlugIn)
					,m_pE(peSession)
					,endpoint_iterator(et)

				{
				}

				void do_connect()
				{
					++s_ijClientSession_Asio;
					jLOG(jFUNC1 _T("create : %d"),s_ijClientSession_Asio);
					boost::asio::async_connect(socket_, endpoint_iterator,
						boost::bind(&jClientSession_Asio::handle_connect, this,
						boost::asio::placeholders::error));

				}
				~jClientSession_Asio()
				{
					--s_ijClientSession_Asio;
					jLOG(jFUNC1 _T("delete : %d"),s_ijClientSession_Asio);
				}

			private:

				void handle_connect(const boost::system::error_code& error)
				{
					jCHECK_ERROR_AND_CLOSE(error );

					if( !m_pPlugIn->OnConnect(m_pE)) return;

					boost::asio::async_read(socket_,
						boost::asio::buffer(m_ReadPacket.data_, jPacketData::HEADER_LENGTH),
						boost::bind(&jClientSession_Asio::handle_read_header, shared_from_this(),
						boost::asio::placeholders::error));
				}

				void handle_read_header(const boost::system::error_code& error)
				{
					jCHECK_ERROR_AND_CLOSE(error);
					if(!m_ReadPacket.decode_header())
					{
						ASIO_DEBUG_LOG(jFUNC1 _T("reason=> if(!m_ReadPacket.decode_header())") ); do_close();
						return ;
					}

					boost::asio::async_read(socket_,
						boost::asio::buffer(m_ReadPacket.data_ + jPacketData::HEADER_LENGTH, m_ReadPacket.body_length_),
						boost::bind(&jClientSession_Asio::handle_read_body, shared_from_this(),
						boost::asio::placeholders::error));
				}

				void handle_read_body(const boost::system::error_code& error)
				{
					jCHECK_ERROR_AND_CLOSE(error);

					if(!m_pPlugIn->OnRead(m_pE, m_ReadPacket.get_body() , m_ReadPacket.body_length_))
					{
						Close();
						return;
					}

					boost::asio::async_read(socket_,
						boost::asio::buffer(m_ReadPacket.data_, jPacketData::HEADER_LENGTH),
						boost::bind(&jClientSession_Asio::handle_read_header, shared_from_this(),
						boost::asio::placeholders::error));
				}

				void do_write(jPacketData msg)
				{
					bool write_in_progress = !m_WritePacketList.empty();
					m_WritePacketList.push_back(msg);
					if (write_in_progress) return;

					jPacketData& sendPacket = m_WritePacketList.front();
					boost::asio::async_write(socket_, boost::asio::buffer(sendPacket.data_,sendPacket.get_length()) 
						,boost::bind(&jClientSession_Asio::handle_write, shared_from_this() 
									, boost::asio::placeholders::error)
					);
				}

				void handle_write(const boost::system::error_code& error)
				{
					jCHECK_ERROR_AND_CLOSE(error);

					m_WritePacketList.pop_front();
					if (m_WritePacketList.empty()) return;

					jPacketData& sendData = m_WritePacketList.front();

					boost::asio::async_write(socket_,
						boost::asio::buffer(sendData.data_,sendData.get_length()),
						boost::bind(&jClientSession_Asio::handle_write, shared_from_this(),boost::asio::placeholders::error)
					);
				}
				void do_close();
			private:

				boost::asio::io_service& get_io_service(){ return m_jIO_Service->m_io_service;}
				tcp::socket socket_;
				jPacketData m_ReadPacket;
				jPacketData_queue m_WritePacketList;
			public:
				jIPlugin_jIClientSession_Asio *m_pPlugIn;



				jIE* jClientSession_Asio::Get_jIE(){ return m_pE;}
				jIPlugin_jIClientSession_Asio* jClientSession_Asio::GetPlugIn(){ return m_pPlugIn;}
				bool jClientSession_Asio::IsConnected(){ return socket_.is_open();}

				void jClientSession_Asio::Close()	
				{	
					ASIO_DEBUG_LOG(jFUNC);
					get_io_service().post(boost::bind(&jClientSession_Asio::do_close, shared_from_this()));
				}
				void jClientSession_Asio::Send(char* sendData,asio_header_type_t iLen)
				{
					jPacketData msg;
					msg.set_body_length(iLen);
					memcpy(msg.get_body(), sendData, iLen);
					msg.encode_header();

					get_io_service().post(boost::bind(&jClientSession_Asio::do_write, this, msg));
				}
			};

			typedef boost::shared_ptr<jClientSession_Asio> jClientSession_Asio_sp_t;
			

			//#--------------------------------------------------------------------------
			class jClientSessionManager_Asio : public jIClientSessionManager
			//#--------------------------------------------------------------------------
			{
				jINTERFACE_HEADER(jIClientSessionManager);

				jLIST_TYPEDEF_map(jIE*, jClientSession_Asio_sp_t , m_listjClientSession_Asio);
				//nUtil::jCriticalSection m_listjClientSession_Asio_CS;

				jLIST_TYPEDEF_map(tstring, jIO_Service_sp_t , m_list_io_service);

			public:
				void erase(jIE* pS);

			};



			static void timer_handle(MOB_Timer_handler_t func,MOB_Timer* pTimer,const boost::system::error_code& error)
			{
				if (error == boost::asio::error::operation_aborted) 
				{
					ASIO_DEBUG_LOG(_T("Timer was canceled"));
					return;
				}
				bool is = func();
				if(is)
				{
					pTimer->async_wait(boost::bind(timer_handle,func, pTimer,boost::asio::placeholders::error));
				}
			}

			MOB_ITimer*	jClientSessionManager_Asio::Timer_Create(cstr szIOServiceName,int iTime,MOB_Timer_handler_t& func)
			{
				m_list_io_service_it it = m_list_io_service.find(szIOServiceName);
				jIO_Service_sp_t pIO;
				bool isFirst=false;
				if(it==m_list_io_service.end())
				{
					pIO = jIO_Service_sp_t(new jIO_Service(szIOServiceName));
					m_list_io_service[szIOServiceName]=pIO;
					isFirst=true;
				}
				else
				{
					pIO = it->second;
				}

				ASIO_DEBUG_LOG("%s",jFUNC);
				MOB_Timer* pTimer = new MOB_Timer(pIO->m_io_service, boost::posix_time::seconds(iTime));
				pTimer->async_wait(boost::bind(timer_handle,func,pTimer , boost::asio::placeholders::error));
				pIO->run_thread();
				return (MOB_ITimer*)pTimer;
			}

			void jClientSessionManager_Asio::Timer_Delete(MOB_ITimer*p)
			{

				ASIO_DEBUG_LOG("%s",jFUNC);
				jRETURN(p);
				MOB_Timer* pTimer= (MOB_Timer*)p;
				pTimer->cancel();
				SAFE_DELETE(pTimer);
			}



			void jClientSessionManager_Asio::Close(jIE* peSession)
			{
				jRETURN(peSession);
				m_listjClientSession_Asio_it it = m_listjClientSession_Asio.find(peSession);
				jvRETURN(it!=m_listjClientSession_Asio.end(), _T("%s not found"), peSession->GetTagName());
				it->second->Close();
				this->erase(peSession);
			}

			// peSession = <ORIGINAL b_ENABLE='0' TYPE='TCP' >127.0.0.1:2010</ORIGINAL>
			jIE* jClientSessionManager_Asio::Create(cstr szIOServiceName,jIPlugin_jIClientSession_Asio* pPlugIn,jIE* peSession)
			{
				if(!peSession->GetAttrVar(jS(ENABLE))->Get_bool()) return 0;

				vector<tstring> out;
				nString::jSplit(peSession->Get_cstr(), _T(":") , out);
				jASSERT0(out.size()==2);
				cstr szHost = out[0].c_str();
				cstr szPort = out[1].c_str();

				jvRETURN_ret( 0,!m_listjClientSession_Asio.count(peSession) , _T("szSessionName is duplicate!! : %s"), peSession->GetTagName() );

				m_list_io_service_it it = m_list_io_service.find(szIOServiceName);
				jIO_Service_sp_t pIO;
				if(it==m_list_io_service.end())
				{
					pIO = jIO_Service_sp_t(new jIO_Service(szIOServiceName));
					m_list_io_service[szIOServiceName]=pIO;
				}
				else
				{
					pIO = it->second;
				}

				tcp::resolver resolver(pIO->m_io_service);
				tcp::resolver::query query(jA(szHost), jA(szPort));
				tcp::resolver::iterator iterator = resolver.resolve(query);
				jClientSession_Asio_sp_t pS = jClientSession_Asio_sp_t(new jClientSession_Asio(pIO,iterator,pPlugIn,peSession));

				m_listjClientSession_Asio[peSession]=pS;
				pS->do_connect();
				pS->m_jIO_Service->run_thread();
				return peSession;
			}

			jIE* jClientSessionManager_Asio::Find(cstr szSessionName)
			{
				
				//jAUTO_LOCK_CS(m_listjClientSession_Asio_CS);
				m_listjClientSession_Asio_it it= m_listjClientSession_Asio.begin() ,ie=m_listjClientSession_Asio.end();
				for(;it!=ie;++it)
				{
					if(it->first->IsName(szSessionName))
						return it->first;
				}
				return 0;
			}

			bool jClientSessionManager_Asio::IsConnected(jIE* peSession)
			{
				if(!peSession) return false;
				return m_listjClientSession_Asio.count(peSession);
			}
			void jClientSessionManager_Asio::Send(jIE* peSession,char* sendData,asio_header_type_t iLen)
			{
				if(!peSession) return;
				//jAUTO_LOCK_CS(m_listjClientSession_Asio_CS);
				m_listjClientSession_Asio_it it= m_listjClientSession_Asio.find(peSession) ,ie=m_listjClientSession_Asio.end();
				jvRETURN(it!=ie,_T(" not found peSession=%s"),peSession->GetTagName()); 
				it->second->Send(sendData, iLen);
			}

			void jClientSessionManager_Asio::erase(jIE* peSession)
			{
				ASIO_DEBUG_LOG(jFUNC);
				//jAUTO_LOCK_CS(m_listjClientSession_Asio_CS);
				m_listjClientSession_Asio_it it =m_listjClientSession_Asio.find(peSession);
				if( it==m_listjClientSession_Asio.end() ) return;
				m_listjClientSession_Asio.erase(it);
				
				if(m_listjClientSession_Asio.size()) return;

// 				m_list_io_service_it itService;
// 				jFOR(m_list_io_service,itService)
// 				{
// 					itService->second->m_thread->join();
// 				}
// 				m_list_io_service.clear();
			}

			void jClientSessionManager_Asio::ReleaseAll()
			{
				//jAUTO_LOCK_CS(m_listjClientSession_Asio_CS);
				m_listjClientSession_Asio_it it;
				jFOR(m_listjClientSession_Asio,it)
				{
					it->second->Close();
				}
				jWARN(_T("s_ijClientSession_Asio= %d"),s_ijClientSession_Asio);
			}

			jClientSessionManager_Asio g_jClientSessionManager_Asio;
			jIClientSessionManager* Impl::jNet::Get_jIClientSessionManager(){	return &g_jClientSessionManager_Asio;}

			void jClientSession_Asio::do_close()	
			{		
				ASIO_DEBUG_LOG(jFUNC);
				g_jClientSessionManager_Asio.erase(m_pE);
				if(!m_pPlugIn) return;
				m_pPlugIn->OnDisconnect(m_pE);
				socket_.close();	
				m_pPlugIn=0;
			}

			void jNET_Plugin_callback_Start(jIPlugin_jIClientSession_Asio* m_pPlugIn)
			{
				m_pPlugIn->OnStartup();
				m_pPlugIn->Load_SQ();
				SquirrelObject* pSO = m_pPlugIn->GetSQTable();
				if(pSO)
				{
					try 
					{	
						SquirrelFunction<void> func(*pSO,jS(Start));
						if(!func.func.IsNull()) 
						{	
							func( m_pPlugIn); 
						}
					} 	
					jSQ_CATCH_ERROR();
				}
				GetjILog()->Log(jLogL,_T("Start : %s"),m_pPlugIn->m_pE->GetTagName());
			}
			void jNET_Plugin_callback_Stop(jIPlugin_jIClientSession_Asio* m_pPlugIn)
			{
				SquirrelObject* pSO = m_pPlugIn->GetSQTable();
				if(pSO)
				{
					try 
					{	
						SquirrelFunction<void> func(*pSO,jS(Stop));
						if(!func.func.IsNull()) 
						{	
							func( m_pPlugIn); 
						}
					} 	
					jSQ_CATCH_ERROR();
				}
				m_pPlugIn->OnStop();
				GetjILog()->Log(jLogL,_T("Stop : %s"),m_pPlugIn->m_pE->GetTagName());
			}

			//#--------------------------------------------------------------------------
			jIPlugin_jIClientSession_Asio* Create_Plugin_jClientSession_Asio(cstr szPlugIn,jIE* pePlugIn)
			//#--------------------------------------------------------------------------
			{
				jIPlugin_jIClientSession_Asio* pPlugIn = static_cast<jIPlugin_jIClientSession_Asio*>( jRTTI::New(szPlugIn 
														, _T("jNet") )  );
				pPlugIn->m_pE = pePlugIn;
				pPlugIn->m_pCSM = &g_jClientSessionManager_Asio;
				pePlugIn->SetUserData(jS(jIPlugin_jIClientSession_Asio),pPlugIn);

				jNET_Plugin_callback_Start(pPlugIn);
				//pPlugIn->OnStartup();
				return pPlugIn;
			}
			void Run_jClientSession_Asio(jIE* pePlugIn)
			{
				jIPlugin_jIClientSession_Asio* pPlugin= xGET_USER_DATA(jIPlugin_jIClientSession_Asio,pePlugIn);
				if(!pPlugin) throw _T("error pePlugIn->GetUserData(jS(jIPlugin_jIClientSession_Asio));");
				cstr szSERVICE_NAME = pePlugIn->GetAttr(jS(SERVICE_NAME));
				if(!szSERVICE_NAME)
					szSERVICE_NAME =jS(NULL);
				
				jIE* peSession = pePlugIn->begin();
				jrFOR(peSession)
				{
					if(!peSession->GetAttrVar(jS(ENABLE))->Get_bool()) continue;
					g_jClientSessionManager_Asio.Create(szSERVICE_NAME ,pPlugin,peSession);
				}
			}
			void Stop_jClientSession_Asio(jIE* pePlugIn)
			{
				jIPlugin_jIClientSession_Asio* pPlugin = xGET_USER_DATA(jIPlugin_jIClientSession_Asio,pePlugIn);
				jRETURN(pPlugin);
				//pPlugin->OnStop();
				jNET_Plugin_callback_Stop(pPlugin);

				jIE* peSession = pePlugIn->begin();
				jrFOR(peSession)
				{
					g_jClientSessionManager_Asio.Close(peSession);
				}
				jWARN(_T("s_ijClientSession_Asio= %d"),s_ijClientSession_Asio);
			}


		//}// namespace Impl


	}//namespace nNET

}//namespace nMech

