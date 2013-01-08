/* file : jPacketSocket_IOCP_eNET_SEND_FILE.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-07-01 14:34:00
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jPacketSocket_IOCP.h"


namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			const int iFILE_BUFFER_SIZE=MAX_SEND_DATA_SIZE;
			enum {e_iFSeekPos,e_pS,e_pCurr,  e_s_SendFileCookie , e_szPath,e_MAX};

			static bool send_eNET_SEND_FILE_CANCEL_REQ(jPacketSocket_IOCP* pS,send_file_cookie_t cookie)
			{
				nswb1024_t buf;
				nMech::nNET::nStream::jNetStreamWrite st(buf);
				nStream::Write(st,(uint8)eNET_SEND_FILE_CANCEL_REQ);
				nStream::Write(st,cookie);
				jPacket_Base pk;
				pk.buf = st.GetBuffer();
				pk.len = st.size();
				pk.num = eNET_SEND_FILE;
				jRETURN_ret(false,pS->WritePacket(&pk));
			}

			
			static bool send_eNET_SEND_FILE_DATA_NEXT_REQ(jPacketSocket_IOCP* pS,send_file_cookie_t cookie)
			{
				nswb1024_t buf;
				nMech::nNET::nStream::jNetStreamWrite st(buf);
				nStream::Write(st,(uint8)eNET_SEND_FILE_DATA_NEXT_REQ);
				nStream::Write(st,cookie);
				jPacket_Base pk;
				pk.buf = st.GetBuffer();
				pk.len = st.size();
				pk.num = eNET_SEND_FILE;
				jRETURN_ret(false,pS->WritePacket(&pk));
			}

			static bool send_eNET_SEND_FILE_BEGIN(jPacketSocket_IOCP* pS,send_file_cookie_t cookie,tcstr szPath,tcstr szRemoteJobThread,tcstr szRemotePath)
			{
				if(!szRemotePath) szRemotePath= _T("");
				nswb1024_t buf;
				nMech::nNET::nStream::jNetStreamWrite st(buf);
				nStream::Write(st,(uint8)eNET_SEND_FILE_BEGIN);
				nStream::Write(st,cookie);
				nStream::Write(st,szPath);
				nStream::Write(st,szRemoteJobThread);
				nStream::Write(st,szRemotePath);

				jPacket_Base pk;
				pk.buf = st.GetBuffer();
				pk.len = st.size();
				pk.num = eNET_SEND_FILE;
				jRETURN_ret(false,pS->WritePacket(&pk));
			}
			static bool send_eNET_SEND_FILE_CANCEL(jPacketSocket_IOCP* pS, send_file_cookie_t cookie)
			{
				nswb256_t buf;
				nMech::nNET::nStream::jNetStreamWrite st(buf);
				nStream::Write(st,(uint8)eNET_SEND_FILE_CANCEL);
				nStream::Write(st,cookie);

				jPacket_Base pk;
				pk.buf = st.GetBuffer();
				pk.len = st.size();
				pk.num = eNET_SEND_FILE;
				jRETURN_ret(FALSE,pS->WritePacket(&pk));
			}
			static bool send_eNET_SEND_FILE_DATA(jPacketSocket_IOCP* pS,send_file_cookie_t cookie,BYTE* pFileBuffer,int iSize)
			{
				jRETURN_ret(false,iSize<=iFILE_BUFFER_SIZE);
				bool isZiped=false;
				nswb16000_t buf;
				nMech::nNET::nStream::jNetStreamWrite st(buf);
				nStream::Write(st,(uint8)eNET_SEND_FILE_DATA);
				nStream::Write(st,cookie);
				nStream::Write(st,isZiped);
				nStream::Write(st,iSize);
				st.Write_Memory(pFileBuffer,iSize);

				jPacket_Base pk;
				pk.buf = st.GetBuffer();
				pk.len = st.size();
				pk.num = eNET_SEND_FILE;
#ifdef _DEBUG
				//jLOG(jFUNC1 _T("cookie=%d ,send size=%d "),cookie,iSize);
#endif
				jRETURN_ret(false,pS->WritePacket(&pk));
			}

			static bool send_eNET_SEND_FILE_END(jIPacketSocket_IOCP* pS,send_file_cookie_t cookie,int sendCount,jPacket_Base* pP)
			{
				nswb256_t buf;
				nMech::nNET::nStream::jNetStreamWrite st(buf);
				nStream::Write(st,(uint8)eNET_SEND_FILE_END);
				nStream::Write(st,cookie);
				nStream::Write(st,sendCount);
				nStream::Write(st,pP->GetNum());
				nStream::Write(st,pP->GetLen());
				st.Write_Memory(pP->buf,pP->GetLen());
				jPacket_Base pk;
				pk.buf = st.GetBuffer();
				pk.len = st.size();
				pk.num = eNET_SEND_FILE;
				jRETURN_ret(FALSE,pS->WritePacket(&pk));
			}
			static bool clear_pCurr(jPacketSocket_IOCP* pS, nNET::nUTIL::_jNetQueueData * pCurr,send_file_cookie_t cookie, nEVENT::jIMessage* pM)
			{
				nNET::nUTIL::_data_size_alloc_info * pDSAI = nNET::nUTIL::jCircularQueueBuffer::get_data_size_alloc_info(pCurr->m_iLength);
				jRETURN_ret(false,pDSAI);
				pDSAI->delete_func(pCurr);
				pM->GetArg(e_pCurr)->SetUserData(0);
				pM->Erase();
				jAUTO_LOCK_CS1(pS->m_jInfo_eNET_SEND_FILE_Send_CS);
				pS->m_jInfo_eNET_SEND_FILE_Send.erase(cookie);
				return true;
			}

			void JOB_SendFile(nEVENT::jIMessage* pM)
			{
				int					iFSeekPos= pM->GetArg(e_iFSeekPos)->Get_int();
				tcstr				szPath = pM->GetArg(e_szPath)->Get_cstr();				jAssert0(szPath);
				send_file_cookie_t	cookie = pM->GetArg(e_s_SendFileCookie )->Get_uint();	jAssert0(cookie!=0);
				jPacketSocket_IOCP* pS = (jPacketSocket_IOCP*)pM->GetArg(e_pS)->GetUserData();jAssert0(pS);
				nNET::nUTIL::_jNetQueueData *pCurr = (nNET::nUTIL::_jNetQueueData *)pM->GetArg(e_pCurr)->GetUserData(); jAssert0(pCurr);

				try
				{
					tname1024_t szFullPath;
					if(!jt_strchr(szPath,':'))
					{
						jt_sprintf(szFullPath,_T("%s%s"),g_ExeEnv.m_szStartDir, szPath);
						szPath = szFullPath;
					}
					nFileSystem::UFile fp(szPath,_T("rb"));
					if(!fp.fp)
					{
						throw _T("file open error");
					}
					fseek(fp,iFSeekPos ,SEEK_SET);
					BYTE pFileBuffer[iFILE_BUFFER_SIZE];
					size_t iSize = fread(pFileBuffer, sizeof(BYTE),iFILE_BUFFER_SIZE,fp);
					if(iSize<=0) 
					{
						jPacket_Base pk;
						pk.buf = pCurr->GetBuffer();
						pk.len = pCurr->m_iLength;
						pk.num = pCurr->dwProtocolNumber;

						jTHROW(send_eNET_SEND_FILE_END(pS, cookie,iFSeekPos+iSize,&pk));

						jCHECK( clear_pCurr(pS, pCurr, cookie, pM) );
						return;
					}
					jTHROW(send_eNET_SEND_FILE_DATA(pS, cookie,pFileBuffer,iSize) );
					iFSeekPos = ftell(fp);
					pM->GetArg(e_iFSeekPos)->Set_int(iFSeekPos);
					pM->DoSleep();
				}
				catch(tcstr szError)
				{
					jERROR(_T("%s,cookie=%d, %s"),szError,cookie,szPath);
					send_eNET_SEND_FILE_CANCEL(pS, cookie);
					jCHECK( clear_pCurr(pS, pCurr, cookie, pM) );
					return ;
				}
			}//void JOB_SendFile(nEVENT::jIMessage* pM)

			static send_file_cookie_t s_SendFileCookie=0;
			uint32 jPacketSocket_IOCP::SendFile(tcstr szPath,tcstr szRemoteJobThread,tcstr szRemotePath,jPacket_Base* pP)
			{
				static nEVENT::jIMsgManager* pMM = nEVENT::jIMsgManager::Get(jS(_jPacketSocket_IOCP_SendFile), true,true);
				jRETURN_ret(0,pMM);
				jRETURN_ret(0,GetFlag_IsConnected());
				jRETURN_ret(0,pP->buf);
				jRETURN_ret(0,GetType() <eTCP_SOCKET_END);

				++s_SendFileCookie;

				jAUTO_LOCK_CS1(m_jInfo_eNET_SEND_FILE_Send_CS);
				m_jInfo_eNET_SEND_FILE_Send_it it = m_jInfo_eNET_SEND_FILE_Send.find(s_SendFileCookie);
				jvIF_NOT(it==m_jInfo_eNET_SEND_FILE_Send.end() , _T("cookie = %d"),s_SendFileCookie )
				{
					it->second->Erase();
					m_jInfo_eNET_SEND_FILE_Send.erase(it);
				}

				jRETURN_ret(0, send_eNET_SEND_FILE_BEGIN(this, s_SendFileCookie,szPath,szRemoteJobThread,szRemotePath) );

				try
				{
					nNET::nUTIL::_data_size_alloc_info * pDSAI = nNET::nUTIL::jCircularQueueBuffer::get_data_size_alloc_info(pP->GetLen());
					jTHROW(pDSAI);
					nNET::nUTIL::_jNetQueueData *pCurr = pDSAI->new_func();
					jTHROW(pCurr);;
					pCurr->m_pObj		= 0;
					pCurr->m_iLength	= pP->GetLen();
					pCurr->dwProtocolNumber = pP->GetNum();
					memcpy(pCurr->GetBuffer() , pP->buf, pP->GetLen());

					nEVENT::jIMessage* pM = pMM->Regist_Loop(0,JOB_SendFile,e_MAX,true);
					pM->GetArg(e_iFSeekPos).T()=0;
					pM->GetArg(e_pS)->SetUserData(this);
					pM->GetArg(e_pCurr)->SetUserData(pCurr);
					pM->GetArg(e_s_SendFileCookie).T()= s_SendFileCookie;
					pM->GetArg(e_szPath).T()= szPath;

					m_jInfo_eNET_SEND_FILE_Send[s_SendFileCookie] = pM;
					pM->DoWakeUp();
				}
				catch (tcstr szError)
				{
					jERROR(_T("%s, cookie=%d, %s, %s"),szError,s_SendFileCookie,szPath,szRemotePath);
					send_eNET_SEND_FILE_CANCEL(this, s_SendFileCookie);
					return 0;
				}
				return s_SendFileCookie;

			}

			ESendFile jPacketSocket_IOCP::Recv_eNET_SEND_FILE(BYTE *pReadBuff,jPacketLen_t dwPacketLength,OUT jPacket_Base& pk)
			{
				ESendFile eType = ESendFile_MAX;
				nMech::nNET::nStream::jNetStreamRead st(pReadBuff,dwPacketLength);
				uint8 iType;
				send_file_cookie_t cookie=0;
				nStream::Read(st,iType);
				nStream::Read(st,cookie);

				try
				{
#ifdef _DEBUG
	//				jLOG(jFUNC1 _T("iType= %d , cookie=%d, dwPacketLength=%d"), iType,cookie,dwPacketLength);
#endif

					eType = (ESendFile)iType;
					switch(eType)
					{
					case eNET_SEND_FILE_BEGIN:
						{
							tfname_t szPath;
							tname32_t szRemoteJobThread;
							nStream::Read(st,szPath,255);
							nStream::Read(st,szRemoteJobThread,31);
							tfname_t szRemotePath;
							nStream::Read(st,szRemotePath,255);

							if(st.GetCurrPos()>dwPacketLength) throw _T("eNET_SEND_FILE_BEGIN st.GetCurrPos()>data_size");

							jAUTO_LOCK_CS1(m_jInfo_eNET_SEND_FILE_Recv_CS);
							m_jInfo_eNET_SEND_FILE_Recv_it it = m_jInfo_eNET_SEND_FILE_Recv.find(cookie), ie = m_jInfo_eNET_SEND_FILE_Recv.end();
							jInfo_eNET_SEND_FILE_Recv* pInfo=0;
							if(it!=ie)
							{
								jERROR_T("cookie=%d, Duplicate, %s,%s",cookie,szPath,szRemoteJobThread);
								it->second.deleteFile();
								pInfo = &it->second;
							}
							else
							{
								pInfo = &m_jInfo_eNET_SEND_FILE_Recv[cookie];
								it = m_jInfo_eNET_SEND_FILE_Recv.find(cookie);
							}
							tname32_t szIP;
							this->GetIP(szIP);
							if(!pInfo->createFile(cookie,szPath,szRemoteJobThread,szIP,szRemotePath) )
							{
								jERROR_T("cookie=%d, %s,%s,%s",cookie, szPath,szRemoteJobThread,szIP);
								pInfo->deleteFile();
								m_jInfo_eNET_SEND_FILE_Recv.erase(it);
								throw "createFile";
							}
							pInfo->m_iWriteCount=0;
							break;
						}
					case eNET_SEND_FILE_DATA:
						{
							BYTE pFileBuffer[iFILE_BUFFER_SIZE];
							bool isZiped;
							int iSize;
							nStream::Read(st,isZiped);
							nStream::Read(st,iSize);
							if(iSize > iFILE_BUFFER_SIZE )
							{
								jERROR(_T("cookie=%d,eNET_SEND_FILE_DATA,(%d) <= (%d)"),cookie,iSize, iFILE_BUFFER_SIZE);
								throw "eNET_SEND_FILE_DATA";
							}
							st.Read_Memory(pFileBuffer,iSize);
							if(st.GetCurrPos()>dwPacketLength) throw _T("eNET_SEND_FILE_DATA st.GetCurrPos()>data_size");

							jAUTO_LOCK_CS1(m_jInfo_eNET_SEND_FILE_Recv_CS);
							m_jInfo_eNET_SEND_FILE_Recv_it it = m_jInfo_eNET_SEND_FILE_Recv.find(cookie), ie = m_jInfo_eNET_SEND_FILE_Recv.end();
							if(it==ie)
							{
								jERROR(_T("cookie=%d, file not found"),cookie);
								throw "file not found";
							}
							it->second.saveFile(pFileBuffer,iSize);

							if(!send_eNET_SEND_FILE_DATA_NEXT_REQ(this,cookie))
							{
								throw "send_eNET_SEND_FILE_DATA_NEXT_REQ";
							}
#ifdef _DEBUG
//							jLOG(jFUNC1 _T("eNET_SEND_FILE_DATA iSize=%d"),iSize);
#endif

							break;
						}
					case eNET_SEND_FILE_DATA_NEXT_REQ:
						{
							jAUTO_LOCK_CS1(m_jInfo_eNET_SEND_FILE_Send_CS);
							m_jInfo_eNET_SEND_FILE_Send_it it = m_jInfo_eNET_SEND_FILE_Send.find(cookie);
							jvIF(it==m_jInfo_eNET_SEND_FILE_Send.end(),_T("eNET_SEND_FILE_DATA_NEXT_REQ"))
							{
								send_eNET_SEND_FILE_CANCEL(this, cookie);
								break;
							}
							nEVENT::jIMessage* pM = it->second;
							jvBREAK(pM,_T("eNET_SEND_FILE_DATA_NEXT_REQ"));
							pM->DoWakeUp();
							break;
						}
					case eNET_SEND_FILE_CANCEL_REQ: //SendFile 을 받는 원격지에서 파일 보내기 취소 가 날라 왔다.
						{
							jAUTO_LOCK_CS1(m_jInfo_eNET_SEND_FILE_Send_CS);
							m_jInfo_eNET_SEND_FILE_Send_it it = m_jInfo_eNET_SEND_FILE_Send.find(cookie);
							jvBREAK(it!=m_jInfo_eNET_SEND_FILE_Send.end(),_T("eNET_SEND_FILE_CANCEL_REQ"));
							nEVENT::jIMessage* pM = it->second;
							jvBREAK(pM,_T("eNET_SEND_FILE_CANCEL_REQ"));
							nNET::nUTIL::_jNetQueueData *pCurr = (nNET::nUTIL::_jNetQueueData *)pM->GetArg(e_pCurr)->GetUserData();
							jvBREAK(pCurr , _T("eNET_SEND_FILE_CANCEL_REQ"));
							jCHECK( clear_pCurr(this, pCurr, cookie, pM) );
							break;
						}
					case eNET_SEND_FILE_END:
						{
							jRETURN_ret(ESendFile_MAX,pk.buf);
							int sendCount;
							tstring sTempFile;
							nStream::Read(st,sendCount);
							{
								jAUTO_LOCK_CS1(m_jInfo_eNET_SEND_FILE_Recv_CS);
								m_jInfo_eNET_SEND_FILE_Recv_it it = m_jInfo_eNET_SEND_FILE_Recv.find(cookie), ie = m_jInfo_eNET_SEND_FILE_Recv.end();
								if(it==ie)
								{
									jERROR(_T("cookie=%d,eNET_SEND_FILE_END file not found"),cookie);
									throw "eNET_SEND_FILE_END";
								}
								if(sendCount!=it->second.m_iWriteCount)
								{
									jERROR(_T("cookie=%d, eNET_SEND_FILE_END, sendCount=%d,%d"),cookie ,sendCount, it->second.m_iWriteCount );
									throw "sendCount!=it->second.m_iWriteCount";
								}

								sTempFile = it->second.sTempFile;
								m_jInfo_eNET_SEND_FILE_Recv.erase(it);
							}
							int iOffset=0;

							// 파일명 기존 패킷에 저장.
							uint16 iLen = sTempFile.size();
							memcpy(pk.buf+iOffset,&iLen,sizeof(iLen));
							iOffset+=sizeof(iLen);

							memcpy(pk.buf+iOffset , sTempFile.c_str(), sizeof(TCHAR)*iLen );
							iOffset+=(sizeof(TCHAR)*iLen);

							// jPacketSocket_IOCP::SendFile(pk ...)로 보내는 원래의 패킷데이타 부분.
							nStream::Read(st,pk.num);
							nStream::Read(st,pk.len);
							jRETURN_ret(ESendFile_MAX, pk.len<2000);
							st.Read_Memory(pk.buf+iOffset,pk.len);
							iOffset+=pk.len;

							pk.len=iOffset;
							if(st.GetCurrPos()>dwPacketLength) 
								throw "eNET_SEND_FILE_END st.GetCurrPos()>data_size";
							break;
						}
					case eNET_SEND_FILE_CANCEL:
						{
							jAUTO_LOCK_CS1(m_jInfo_eNET_SEND_FILE_Recv_CS);
							m_jInfo_eNET_SEND_FILE_Recv_it it = m_jInfo_eNET_SEND_FILE_Recv.find(cookie);
							jvRETURN_ret(ESendFile_MAX, it!=m_jInfo_eNET_SEND_FILE_Recv.end() ,_T("cookie = %d"), cookie);
							it->second.deleteFile();
							m_jInfo_eNET_SEND_FILE_Recv.erase(it);
							break;
						}
					default:
						jERROR_T("type unkown : %d",iType);
						return ESendFile_MAX;
					}
				}
				catch(acstr szError)//acstr로 catch되면 SendFile하는 쪽에 send_eNET_SEND_FILE_CANCEL_REQ를 보내야 한다.
				{
					jERROR_T("%s send_eNET_SEND_FILE_CANCEL_REQ", jA(szError));
					send_eNET_SEND_FILE_CANCEL_REQ(this,cookie);
					return ESendFile_MAX;
				}
				catch(tcstr sz)
				{
					jERROR_T("%s (dwPacketLength=%u) " , sz,dwPacketLength); 
					return ESendFile_MAX;
				}
				return eType;
			}

			bool jPacketSocket_IOCP::jInfo_eNET_SEND_FILE_Recv::deleteFile()
			{
				if(!this->sTempFile.size()) return false;
				return DeleteFile(this->sTempFile.c_str());
			}

			#define BUFSIZE 512
			
			bool jPacketSocket_IOCP::jInfo_eNET_SEND_FILE_Recv::createFile(send_file_cookie_t cookie , tcstr szPath,tcstr szJobThread,tcstr szIP,tcstr szRemotePath)
			{
				DWORD dwBufSize=BUFSIZE;
				TCHAR lpPathBuffer[BUFSIZE];
				TCHAR szTempName[BUFSIZE];  

				if(!szRemotePath || !jt_strlen(szRemotePath) || !jt_strcmp(szRemotePath,jS(NULL)) )
				{
					DWORD dwRetVal = GetTempPath(dwBufSize,     // length of the buffer
						lpPathBuffer); // buffer for path 

					jvRETURN_ret(false, !(dwRetVal > dwBufSize || (dwRetVal == 0) ) , _T("GetTempPath failed with error %d.\n"), GetLastError());

					nFileSystem::jFileName fn(szPath);
					fname_t szFileName;
					fn.GetName(szFileName);
					jt_strcat(lpPathBuffer, szFileName);
				}
				else
				{
					if(!jt_strchr(szRemotePath,':'))
					{
						jt_sprintf( szTempName, _T("%s%s"), g_ExeEnv.m_szStartDir , szRemotePath);
					}
					else
					{
						jt_strcpy( szTempName, szRemotePath);
					}
					if(szTempName[jt_strlen(szTempName)-1]=='\\')
					{
						nFileSystem::jFileName fn(szPath);
						fname_t szFileName;
						fn.GetName(szFileName);
						jt_strcat(szTempName,szFileName);
					}
					nFileSystem::jFileName fn(szTempName);
					tname1024_t szPath;
					fn.GetPath(szPath);
					nFileSystem::jFolder::CreateDirForce(szPath);
				}

				// Create the new file to write the upper-case version to.
				HANDLE hTempFile = CreateFile((LPTSTR) szTempName, // file name 
					GENERIC_WRITE, // open r-w 
					0,                    // do not share 
					NULL,                 // default security 
					CREATE_ALWAYS,        // overwrite existing
					FILE_ATTRIBUTE_NORMAL,// normal file 
					NULL);                // no template 
				jvRETURN_ret(false, hTempFile != INVALID_HANDLE_VALUE ,_T("CreateFile failed with error %d") , GetLastError()) ;
				jvRETURN_ret(false , CloseHandle (hTempFile) , _T("CloseHandle failed with error %d."), GetLastError() );
				this->sTempFile = szTempName;
				return true;
			}

			bool jPacketSocket_IOCP::jInfo_eNET_SEND_FILE_Recv::saveFile(BYTE* buf,int iSize)
			{
				try
				{
					nFileSystem::UFile fp(sTempFile.c_str(), _T("ab+"));
					jvRETURN_ret(false, fp.fp, _T("CreateFile failed with error %d , %s"),GetLastError(),sTempFile.c_str()) ;
					fseek(fp, 0,SEEK_END);
					DWORD dwBytesWritten;
					jvRETURN_ret(false, fwrite(buf, iSize,1, fp) ,_T("WriteFile failed with error %d , %s") , GetLastError(),sTempFile.c_str()); 
					fp.fclose();
					m_iWriteCount+=iSize;
				}
				catch (tcstr szError)
				{
					return false;
				}
				return true;
			}



		}// nNet::Impl

	} //nNET
}//nMech


