#include "stdafx.h"
#include "base/SafeDateTime.h"
#include "interface/db/jIDB.h"


namespace nMech
{
	namespace nDB
	{

		class SafeDB_test : public nUtil::jCriticalSection
		{
		public:
			//////////////////////////////////////////////////////////////////////////
			void SafeDB_test::Initialize(tcstr szDB, tcstr usrName, tcstr pwd)
			{
				m_pDB->SetError(&m_pErrHandler);
				m_pDB->SetInfo(szDB, usrName, pwd);
				try
				{
					m_pDB->Open();
				}
				catch (tstring &str)
				{
					jERROR(_T("%s 디비연결안됨"), str.c_str() );
				}
				catch (tcstr sz)
				{
					jERROR(_T("%s 디비연결안됨"), sz);
				}
			}

			virtual SafeDB_test::~SafeDB_test()
			{
				Finalize();
			}

			void SafeDB_test::Finalize()
			{	
				m_pDB->Close();
			}
			bool SafeDB_test::Ping() //약 1초에 한번씩 핑을때림.
			{
				if( !m_pDB->Ping() )
				{
					m_pDB->Close();
					try
					{
						m_pDB->Open();
						return true;
					}
					catch (...)
					{
					}
				}
				return false;
			}

			tcstr GetSvrName() { return m_pDB->GetSvrName(); }

		public:
			jIDB		*m_pDB;
			IOdbcErrorHandler	m_pErrHandler;

			//--------------------------------------------------------------------------
			// 테스트 코드
			//--------------------------------------------------------------------------

			bool  LoadCharServerInfo(TCHAR* myIP,int & m_Ver)
			{
				struct LoadChar : public jISqlJob
				{
					TCHAR* myIP;
					int &m_Ver;

					LoadChar(TCHAR* ip,int & ver) :myIP(ip) ,m_Ver(ver) {}

					void Bind(jISqlParameter* pSP) 
					{
						pSP->Bind(SP_IN, myIP);
					}

					void Fetch(jISqlRecord* pR)
					{
						if (pR->Next())
						{
							pR->GetData(m_Ver);
						}
					}
				};

				m_pDB->RunSQL(_T("{call Fuc_CharServerInfo(?)}"), &LoadChar(myIP,m_Ver));
				return true;
			}

			bool SetInvenPeriod(DWORD dwCharIndex, BYTE byPosition, DWORD dwItemIndex, WORD wItemCount, int CanUseTime, SysTime& outCanUseTime)
			{
#define jLAMDA_setInvenPeriod(X,Z) \
	X(DWORD,dwCharIndex) \
	X(BYTE,byPosition) \
	X(DWORD,dwItemIndex) \
	X(WORD,wItemCount) \
	X(int,CanUseTime) \
	Z(SysTime&,outCanUseTime)

				jLAMDA_begin2(setInvenPeriod,jISqlJob);
				void Bind(jISqlParameter* pSP) 
				{
					ZeroMemory(&outCanUseTime, sizeof(outCanUseTime));
					pSP->Bind(SP_IN, dwCharIndex);
					pSP->Bind(SP_IN, byPosition);
					pSP->Bind(SP_IN, dwItemIndex);
					pSP->Bind(SP_IN, wItemCount);
					pSP->Bind(SP_IN, CanUseTime);
				}
				void Fetch(jISqlRecord* pR)
				{
					if (pR->Next())
					{
						pR->GetData(outCanUseTime);
						return ;
					}
				}
				jLAMDA_end();

				m_pDB->RunSQL(_T("{call usp_Inven_SavePeriod(?,?,?,?,?)}")
					, &setInvenPeriod( dwCharIndex,  byPosition,  dwItemIndex,  wItemCount,  CanUseTime,  outCanUseTime));

				return false;
			}


			bool SetInvenAll(DWORD dwCharIndex, tcstr invenInfo)
			{
#define jLAMDA_setInvenAll(X,Z) \
	X(DWORD,dwCharIndex) \
	Z(tcstr,invenInfo)

				jLAMDA_begin2(setInvenAll,jISqlJob);
				void Bind(jISqlParameter* pSP) 
				{
					pSP->Bind(SP_IN, dwCharIndex);
					pSP->Bind(SP_IN, invenInfo);
				}
				jLAMDA_end();

				m_pDB->RunSQL(_T("{call usp_Inven_SaveAll2(?,?)}") , &setInvenAll(dwCharIndex,invenInfo));

				return false;
			}

		};//class SafeDB_test 


#if 0 //asdf


		bool SafeDB_test::GetStoreAll(DWORD dwMembIndex, DWORD dwCharIndex, StoreInfo* info, SafeDB_test* pLogDB)
		{
			jOdbcParameter sp;

			if (! m_pDB->Prepare("{call usp_Store_LoadAll(?)}", &sp)) 
				return false;

			sp.Bind(1, SP_IN, dwMembIndex);

			OdbcRecord rec;
			if (!sp.Execute(&rec)) 
				return false;

			int iItemID, iItemCount;
			int iDateCmp = 0, iPosition;
			ITEMSN lItemSN = 0;
			SysTime endUseTime;

			while (rec.Next()) 
			{// 창고: 일반 tb_MembStoreNormal
				rec.Data(1, iItemID);
				rec.Data(2, iItemCount);
				rec.Data(3, iDateCmp);
				rec.Data(4, endUseTime);
				rec.Data(5, iPosition);
				rec.Data(6, lItemSN);

				bool init = false;
				Sys_Item *iip = Get_Sys_Item( GetLow( iItemID ) );
				if (iip)
				{
					if (iip->can_use_time > 0 && iDateCmp < 0)
					{
						init = true;
						pLogDB->AddLogItem( dwMembIndex, dwCharIndex, 0, iItemID, iItemCount, 0, iItemCount, lItemSN, LOG_ITEM_STORE_EXPIRED );
					}

					if (iip->overlap == 0 && iItemCount > 1)
					{
						WRITELOG( "[Item Error] StoreNormal(2) - Char: %u, ID: %d, Count: %d, ItemSN: %I64d", dwCharIndex, iItemID, iItemCount, lItemSN );
						iItemCount = 1;
					}

					if( iip->overlap > 0 && iip->overlap < iItemCount )
					{
						WRITELOG( "[Item Error] StoreNormal(3) - Char: %u, ID: %d, Count: %d, ItemSN: %I64d", dwCharIndex, iItemID, iItemCount, lItemSN );
						iItemID = 0;
						iItemCount = 0;
						ZeroMemory( &endUseTime, sizeof( SysTime ) );
						lItemSN = 0;
					}
				}
				else
				{
					init = true;
					WRITELOG( "[Item Error] StoreNormal(1) - Char: %u, ID: %d, Count: %d, ItemSN: %I64d", dwCharIndex, iItemID, iItemCount, lItemSN );
				}

				if (init)
				{
					info->set_store_data( STORE_NORMAL, iPosition, 0, 0, 0, 0, 0 );
				}
				else
				{
					info->set_store_data( STORE_NORMAL, iPosition, iItemID, iItemCount, ToSafeTime(endUseTime), lItemSN, iDateCmp );
					info->m_Item[STORE_NORMAL][iPosition].m_isChanged = false;
				}
			}//while (rec.Next()) // 창고: 일반 tb_MembStoreNormal

			if (!rec.More())
			{
				WRITELOG( "[Error] GetStoreAll / tb_MembStoreWeapon 실패");
				return false;
			}

			while (rec.Next())
			{//-- 창고: 무기  tb_MembStoreWeapon
				rec.Data(1, iItemID);
				rec.Data(2, iItemCount);
				rec.Data(3, iDateCmp);
				rec.Data(4, endUseTime);
				rec.Data(5, iPosition);
				rec.Data(6, lItemSN);

				bool init = false;
				Sys_Item *iip = Get_Sys_Item( GetLow( iItemID ) );
				if (iip)						
				{
					if (iip->can_use_time > 0 && iDateCmp < 0)
					{
						init = true;
						pLogDB->AddLogItem( dwMembIndex, dwCharIndex, 0, iItemID, iItemCount, 0, iItemCount, lItemSN, LOG_ITEM_STORE_EXPIRED );
					}

					if (iip->overlap == 0 && iItemCount > 1)
					{
						WRITELOG( "[Item Error] StoreWeapon(2) - Char: %u, ID: %d, Count: %d, ItemSN: %I64d", dwCharIndex, iItemID, iItemCount, lItemSN );
						iItemCount = 1;
					}

					if( iip->overlap > 0 && iip->overlap < iItemCount )
					{
						WRITELOG( "[Item Error] StoreWeapon(3) - Char: %u, ID: %d, Count: %d, ItemSN: %I64d", dwCharIndex, iItemID, iItemCount, lItemSN );
						iItemID = 0;
						iItemCount = 0;
						ZeroMemory( &endUseTime, sizeof( SysTime ) );
						lItemSN = 0;
					}
				}
				else
				{
					init = true;
					WRITELOG( "[Item Error] StoreWeapon(1) - Char: %u, ID: %d, Count: %d, ItemSN: %I64d", dwCharIndex, iItemID, iItemCount, lItemSN );
				}

				if (init)
				{
					info->set_store_data( STORE_WEAPON, iPosition, 0, 0, 0, 0, 0 );
				}
				else
				{
					info->set_store_data( STORE_WEAPON, iPosition, iItemID, iItemCount, ToSafeTime(endUseTime), lItemSN, iDateCmp );
					info->m_Item[STORE_WEAPON][iPosition].m_isChanged = false;
				}
			}//-- 창고: 무기  tb_MembStoreWeapon

			if (!rec.More())
			{
				WRITELOG( "[Error] GetStoreAll / tb_MembStoreCard 실패");
				return false;
			}

			while (rec.Next())
			{//-- 창고: 카드 ,tb_MembStoreCard
				rec.Data(1, iItemID);
				rec.Data(2, iItemCount);
				rec.Data(3, iDateCmp);
				rec.Data(4, endUseTime);
				rec.Data(5, iPosition);
				rec.Data(6, lItemSN);

				bool init = false;
				Sys_Item *iip = Get_Sys_Item( GetLow( iItemID ) );
				if (iip)						
				{
					if (iip->can_use_time > 0 && iDateCmp < 0)
					{
						init = true;
						pLogDB->AddLogItem( dwMembIndex, dwCharIndex, 0, iItemID, iItemCount, 0, iItemCount, lItemSN, LOG_ITEM_STORE_EXPIRED );
					}

					if (iip->overlap == 0 && iItemCount > 1)
					{
						WRITELOG( "[Item Error] StoreCard(2) - Char: %u, ID: %d, Count: %d, ItemSN: %I64d", dwCharIndex, iItemID, iItemCount, lItemSN );
						iItemCount = 1;
					}

					if( iip->overlap > 0 && iip->overlap < iItemCount )
					{
						WRITELOG( "[Item Error] StoreCard(3) - Char: %u, ID: %d, Count: %d, ItemSN: %I64d", dwCharIndex, iItemID, iItemCount, lItemSN );
						iItemID = 0;
						iItemCount = 0;
						ZeroMemory( &endUseTime, sizeof( SysTime ) );
						lItemSN = 0;
					}
				}
				else
				{
					init = true;
					WRITELOG( "[Item Error] StoreCard(1) - Char: %u, ID: %d, Count: %d, ItemSN: %I64d", dwCharIndex, iItemID, iItemCount, lItemSN );
				}

				if (init)
				{
					info->set_store_data( STORE_CARD, iPosition, 0, 0, 0, 0, 0 );
				}
				else
				{
					info->set_store_data( STORE_CARD, iPosition, iItemID, iItemCount, ToSafeTime(endUseTime), lItemSN, iDateCmp );
					info->m_Item[STORE_CARD][iPosition].m_isChanged = false;
				}
			}////-- 창고: 카드 ,tb_MembStoreCard

			if (!rec.More())
			{
				WRITELOG( "[Error] GetStoreAll / tb_MembStoreCash 실패" );
				return false;
			}

			while (rec.Next())
			{//-- 창고: 캐쉬  tb_MembStoreCash
				rec.Data(1, iItemID);
				rec.Data(2, iItemCount);
				rec.Data(3, iDateCmp);
				rec.Data(4, endUseTime);
				rec.Data(5, iPosition);
				rec.Data(6, lItemSN);

				bool init = false;
				Sys_Item *iip = Get_Sys_Item( GetLow( iItemID ) );
				if (iip)						
				{
					if (iip->overlap == 0 && iItemCount > 1)
					{
						WRITELOG( "[Item Error] StoreCash(2) - Char: %u, ID: %d, Count: %d, ItemSN: %I64d", dwCharIndex, iItemID, iItemCount, lItemSN );
						iItemCount = 1;
					}

					if( iip->overlap > 0 && iip->overlap < iItemCount )
					{
						WRITELOG( "[Item Error] StoreCash(3) - Char: %u, ID: %d, Count: %d, ItemSN: %I64d", dwCharIndex, iItemID, iItemCount, lItemSN );
						iItemID = 0;
						iItemCount = 0;
						ZeroMemory( &endUseTime, sizeof( SysTime ) );
						lItemSN = 0;
					}
				}
				else
				{
					init = true;
					WRITELOG( "[Item Error] StoreCash(1) - Char: %u, ID: %d, Count: %d, ItemSN: %I64d", dwCharIndex, iItemID, iItemCount, lItemSN );
				}

				if (init)
				{
					info->set_store_data( STORE_CASH, iPosition, 0, 0, 0, 0, 0 );
				}
				else
				{
					info->set_store_data( STORE_CASH, iPosition, iItemID, iItemCount, ToSafeTime(endUseTime), lItemSN, iDateCmp );
					info->m_Item[STORE_CASH][iPosition].m_isChanged = false;
				}
			}//while (rec.Next()) //if (rec.More()) //-- 창고: 캐쉬  tb_MembStoreCash

			info->m_isLoaded = true;
			return true;
		}

		bool SafeDB_test::CheckDualTime(DWORD dwCharIndex, INT64& diffTime)
		{
			jOdbcParameter sp;
			OdbcRecord rec;

			if (m_pDB->Prepare("{call usp_Dual_CheckTime(?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwCharIndex);

				if (sp.Execute(&rec))
				{
					if (rec.Next())
					{
						rec.Data(1, diffTime);
						if( diffTime < 0 )
							diffTime = 0;

						return true;
					}
				}
			}
			return false;
		}

		bool SafeDB_test::SetDualTime(DWORD dwCharIndex)
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_Dual_Refresh(?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwCharIndex);

				return sp.Execute();
			}
			return false;
		}

		bool SafeDB_test::AccountRank(DWORD dwMissionID, RankInfo& rank)
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_Rank_AccountEach(?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwMissionID);

				OdbcRecord rec;

				if (sp.Execute(&rec))
				{
					int count = 0;
					SysTime date;

					while (rec.Next())
					{
						RankUser& ru = rank.m_Rank[count++];

						rec.Data(1, ru.m_dwCharIndex);
						rec.Data(2, ru.m_wszName, 24);
						rec.Data(3, ru.m_wszGuildName, 24);
						rec.Data(4, ru.m_byLevel);
						rec.Data(5, ru.m_dwScore);
						rec.Data(6, ru.m_dwRank);
						rec.Data(7, date);

						ru.m_lDate = ToSafeTime(date);

						if (count >= 10)
							break;
					}
					rank.m_byRankCount = count;
					return true;
				}
			}
			return false;
		}


		bool SafeDB_test::GetRankUser(DWORD dwMissionID, LPCWSTR wszCharName, RankUser& user)
		{
			jOdbcParameter sp;

			user.Clear();

			if (m_pDB->Prepare("{call usp_Rank_Search(?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwMissionID);
				sp.Bind(2, SP_IN, wszCharName);

				OdbcRecord rec;

				if (sp.Execute(&rec))
				{
					user.Clear();

					if (rec.Next())
					{
						rec.Data(1, user.m_dwCharIndex);
						rec.Data(2, user.m_wszName, 24);
						rec.Data(3, user.m_wszGuildName, 24);
						rec.Data(4, user.m_byLevel);
						rec.Data(5, user.m_dwScore);
						rec.Data(6, user.m_dwRank);
					}
					return true;
				}
			}
			return false;
		}

		bool SafeDB_test::AddMail(DWORD dwSendMembIndex, DWORD dwSendCharIndex, LPCWSTR wszSendName, LPCWSTR wszRecvName, BYTE byMailType, LPCWSTR wszSubject, LPCWSTR wszBody,
			DWORD dwItemID, WORD wItemCount, ITEMSN lItemSN, int iMesso, WORD wLetter, DWORD dwSysCharIndex,
			DWORD& dwRecvMembIndex, DWORD& dwRecvCharIndex, DWORD& dwNewRecvMail, INT64 &nMailSN, BYTE& byResult)
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_Mail_Send(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwSendMembIndex);
				sp.Bind(2, SP_IN, dwSendCharIndex);
				sp.Bind(3, SP_IN, wszSendName);
				sp.Bind(4, SP_IN, wszRecvName);
				sp.Bind(5, SP_IN, byMailType);
				sp.Bind(6, SP_IN, wszSubject);
				sp.Bind(7, SP_IN, wszBody);
				sp.Bind(8, SP_IN, dwItemID);
				sp.Bind(9, SP_IN, wItemCount);
				sp.Bind(10, SP_IN, iMesso);
				sp.Bind(11, SP_IN, wLetter);
				sp.Bind(12, SP_OUT, dwRecvMembIndex);
				sp.Bind(13, SP_OUT, dwRecvCharIndex);
				sp.Bind(14, SP_OUT, dwNewRecvMail);
				sp.Bind(15, SP_OUT, byResult);
				sp.Bind(16, SP_OUT, nMailSN);
				sp.Bind(17, SP_IN, lItemSN);
				sp.Bind(18, SP_IN, dwSysCharIndex);

				return sp.Execute();
			}
			return false;
		}

		bool SafeDB_test::DelMail(DWORD dwCharIndex, INT64 nMailSN, BYTE byMailBox)
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_Mail_Del(?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwCharIndex);
				sp.Bind(2, SP_IN, nMailSN);
				sp.Bind(3, SP_IN, byMailBox);

				return sp.Execute();
			}
			return false;
		}

		bool SafeDB_test::GetMail(DWORD dwCharIndex, INT64 nMailSN, BYTE byMailBox, DWORD& dwMailCount, MailItem& mail)
		{
			jOdbcParameter sp;

			mail.m_nMailSN = 0;

			if (m_pDB->Prepare("{call usp_Mail_GetBody(?,?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwCharIndex);
				sp.Bind(2, SP_IN, nMailSN);
				sp.Bind(3, SP_IN, byMailBox);
				sp.Bind(4, SP_OUT, dwMailCount);

				OdbcRecord rec;
				if (sp.Execute(&rec))
				{
					if (rec.Next())
					{
						SysTime date;

						rec.Data(1, mail.m_nMailSN);
						rec.Data(2, mail.m_wszSendName, MAX_CHAR_NAMEW);
						rec.Data(3, mail.m_wszRecvName, MAX_CHAR_NAMEW);
						rec.Data(4, mail.m_byMailType);
						rec.Data(5, mail.m_dwItemID);
						rec.Data(6, mail.m_wItemCount);
						rec.Data(7, mail.m_iMesso);
						rec.Data(8, date);
						mail.m_SendDate = ToSafeTime(date);

						rec.Data(9, date);
						mail.m_RecvDate = ToSafeTime(date);

						rec.Data(10, date);
						mail.m_GetDate = ToSafeTime(date);

						rec.Data(11, mail.m_wszSubject, MAX_MAIL_SUBJECT);
						rec.Data(12, mail.m_wszBody, MAX_MAIL_BODY);
						rec.Data(13, mail.m_wLetter);
						rec.Data(14, mail.m_lItemSN);

						if (mail.m_GetDate != 0)
						{
							mail.m_dwItemID = 0;
							mail.m_iMesso  = 0;
							mail.m_wItemCount = 0;
							mail.m_lItemSN = 0;
						}
					}

					rec.More();

					return true;
				}
			}
			return false;
		}

		bool SafeDB_test::GetMailList(DWORD dwCharIndex, BYTE byMailBox, BYTE byPage, DWORD& dwMaxPage, MailBox& box)
		{
			jOdbcParameter sp;

			box.m_byMailCount = 0;
			box.m_byBoxType   = 0;

			if (m_pDB->Prepare("{call usp_Mail_List(?,?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwCharIndex);
				sp.Bind(2, SP_IN, byMailBox);
				sp.Bind(3, SP_IN, byPage);
				sp.Bind(4, SP_OUT, dwMaxPage);

				OdbcRecord rec;
				if (sp.Execute(&rec))
				{
					int count = 0;
					SysTime date;

					while (rec.Next())
					{
						MailBase& base = box.m_Mail[count];
						rec.Data(1, base.m_nMailSN);
						rec.Data(2, base.m_wszSendName, MAX_CHAR_NAMEW);
						rec.Data(3, base.m_wszRecvName, MAX_CHAR_NAMEW);
						rec.Data(4, base.m_byMailType);
						rec.Data(5, base.m_dwItemID);
						rec.Data(6, base.m_iMesso);
						rec.Data(7, date);
						base.m_SendDate = ToSafeTime(date);

						rec.Data(8, date);
						base.m_RecvDate = ToSafeTime(date);

						rec.Data(9, date);
						base.m_GetDate = ToSafeTime(date);

						rec.Data(10, base.m_wszSubject, MAX_MAIL_SUBJECT);

						if (base.m_GetDate != 0)
						{
							base.m_dwItemID = 0;
							base.m_iMesso  = 0;
						}

						if (++count >= MAX_MAIL_PER_PAGE)
							break;
					}
					box.m_byMailCount = count;
					box.m_byBoxType   = byMailBox;

					rec.More();
					return true;
				}
			}
			return false;
		}

		bool SafeDB_test::ParseGuid(ITEMSN lItemSN, BYTE& byCreateType, BYTE& byChannelNo, WORD& wUniqueID, SysTime& date)
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_ItemGuid_Parse(?,?,?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, lItemSN);
				sp.Bind(2, SP_OUT, byCreateType);
				sp.Bind(3, SP_OUT, byChannelNo);
				sp.Bind(4, SP_OUT, wUniqueID);
				sp.Bind(5, SP_OUT, date);

				if (sp.Execute())
				{
					return true;
				}
			}
			return false;
		}

		//////////////////////////////////////////////////////////////////////////
		// Log DB
		bool SafeDB_test::AddLogTrade(DWORD dwCharIndex1, DWORD dwCharIndex2, int iMesso, DWORD key[], WORD count[], ITEMSN sn[], int item_count)
		{
#ifdef DF_DB_LOG_THREAD
			WCHAR *wszLog = WORKMANAGER->GetLog( L"{call usp_Log_Trade2(%u,%u,%u,%u,%I64d,%u,%u,%I64d,%u,%u,%I64d,%u,%u,%I64d,%u,%u,%I64d,%u,%u,%I64d,%u,%u,%I64d,%u,%u,%I64d,%d)}",
				dwCharIndex1, dwCharIndex2, key[0], count[0], sn[0], key[1], count[1], sn[1], key[2], count[2], sn[2], key[3], count[3], sn[3], 
				key[4], count[4], sn[4], key[5], count[5], sn[5], key[6], count[6], sn[6], key[7], count[7], sn[7], iMesso );

			WORKMANAGER->PutLog( m_iThreadID, wszLog );
			return true;
#else
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_Log_Trade2(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwCharIndex1);
				sp.Bind(2, SP_IN, dwCharIndex2);

				int idx = 3;
				for (int i=0; i < item_count; i++)
				{
					sp.Bind(idx++, SP_IN, key[i]);
					sp.Bind(idx++, SP_IN, count[i]);
					sp.Bind(idx++, SP_IN, sn[i]);
				}
				sp.Bind(idx, SP_IN, iMesso);

				return sp.Execute();
			}
			return false;
#endif
		}

		bool SafeDB_test::AddLogContents(DWORD dwMembIndex, DWORD dwCharIndex, DWORD dwTrigger, BYTE byResult, DWORD dwData)
		{
#ifdef DF_DB_LOG_THREAD
			WCHAR *wszLog = WORKMANAGER->GetLog( L"{call usp_Log_Contents(%u,%u,%u,%d,%u)}", dwMembIndex, dwCharIndex, dwTrigger, byResult, dwData ); 
			WORKMANAGER->PutLog( m_iThreadID, wszLog );
			return true;
#else
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_Log_Contents(?,?,?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwMembIndex);
				sp.Bind(2, SP_IN, dwCharIndex);
				sp.Bind(3, SP_IN, dwTrigger);
				sp.Bind(4, SP_IN, byResult);
				sp.Bind(5, SP_IN, dwData);

				return sp.Execute();
			}
			return false;
#endif
		}

		bool SafeDB_test::AddLogItem(DWORD dwMembIndex, DWORD dwCharIndex, DWORD dwDestCharIndex, DWORD dwItemIndex, short sCount, int iMesso, int iMoveCount, ITEMSN lItemSN, BYTE byLogType)
		{
#ifdef DF_DB_LOG_THREAD
			WCHAR *wszLog = WORKMANAGER->GetLog( L"{call usp_Log_Item(%u,%u,%u,%u,%d,%d,%d,%d,%I64d)}", 
				dwMembIndex, dwCharIndex, dwDestCharIndex, dwItemIndex, sCount, iMesso, iMoveCount, byLogType, lItemSN ); 
			WORKMANAGER->PutLog( m_iThreadID, wszLog );

			return true;
#else
			jOdbcParameter sp;

			if( dwItemIndex == 0xffffffff )
				return false;

			if (m_pDB->Prepare("{call usp_Log_Item(?,?,?,?,?,?,?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwMembIndex);
				sp.Bind(2, SP_IN, dwCharIndex);
				sp.Bind(3, SP_IN, dwDestCharIndex);
				sp.Bind(4, SP_IN, dwItemIndex);
				sp.Bind(5, SP_IN, sCount);
				sp.Bind(6, SP_IN, iMesso);
				sp.Bind(7, SP_IN, iMoveCount);
				sp.Bind(8, SP_IN, byLogType);
				sp.Bind(9, SP_IN, lItemSN);

				return sp.Execute();
			}
			return false;
#endif
		}

		bool SafeDB_test::AddCashLogItem( DWORD dwMembIndex, DWORD dwCharIndex, DWORD dwItemIndex, wchar* wszItemName, DWORD dwPrice, ITEMSN lItemSN )
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_CashItemBuyLogSave(?,?,?,?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwMembIndex);
				sp.Bind(2, SP_IN, dwCharIndex);
				sp.Bind(3, SP_IN, dwItemIndex);
				sp.Bind(4, SP_IN, wszItemName);
				sp.Bind(5, SP_IN, dwPrice);
				sp.Bind(6, SP_IN, lItemSN);

				return sp.Execute();
			}
			return false;
		}

		//#ifdef DF_HANBIT
		bool SafeDB_test::AddGiftMailLog( DWORD dwMembIndex, DWORD dwCharIndex, DWORD dwDestCharIndex, DWORD dwItemIndex, DWORD dwPrice, WCHAR* wszRecvName, WCHAR* wszItemName )
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_Mail_GiftLogSave(?,?,?,?,?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwMembIndex);
				sp.Bind(2, SP_IN, dwCharIndex);
				sp.Bind(3, SP_IN, dwDestCharIndex);
				sp.Bind(4, SP_IN, wszRecvName);
				sp.Bind(5, SP_IN, dwItemIndex);
				sp.Bind(6, SP_IN, wszItemName);
				sp.Bind(7, SP_IN, dwPrice);

				return sp.Execute();
			}
			return false;
		}

		bool SafeDB_test::CashItemUseLog( DWORD dwCharIndex, BYTE byPage, BYTE bySlot, DWORD dwItemIndex, Sys_Item *iip, WORD wCount, BYTE byKind )
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_CashItemUseLog(?,?,?,?,?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwCharIndex);
				sp.Bind(2, SP_IN, byPage);
				sp.Bind(3, SP_IN, bySlot);
				sp.Bind(4, SP_IN, dwItemIndex);
				sp.Bind(5, SP_IN, iip->name);
				sp.Bind(6, SP_IN, wCount);
				sp.Bind(7, SP_IN, byKind);

				return sp.Execute();
			}
			return false;
		}
		//#endif

#ifdef DF_LOGINLOG_ADD
		bool SafeDB_test::AddLogLogin(BYTE byLogType, BYTE byGroup, BYTE byChannel, DWORD dwMembIndex, DWORD dwCharIndex, int iExp, int iMesso, LPCSTR szIP, INT64& nLogID)
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_Log_CharLogin(?,?,?,?,?,?,?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, byLogType);
				sp.Bind(2, SP_IN, byGroup);
				sp.Bind(3, SP_IN, dwMembIndex);
				sp.Bind(4, SP_IN, dwCharIndex);
				sp.Bind(5, SP_IN, iExp);
				sp.Bind(6, SP_IN, iMesso);
				sp.Bind(7, SP_IN, szIP);
				sp.Bind(8, SP_OUT, nLogID);
				sp.Bind(9, SP_IN, byChannel);

				return sp.Execute();
			}
			return false;
		}
#else
		bool SafeDB_test::AddLogLogin(BYTE byLogType, BYTE byGroup, BYTE byChannel, DWORD dwCharIndex, int iExp, int iMesso, LPCSTR szIP, INT64& nLogID)
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_Log_CharLogin(?,?,?,?,?,?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, byLogType);
				sp.Bind(2, SP_IN, byGroup);
				sp.Bind(3, SP_IN, dwCharIndex);
				sp.Bind(4, SP_IN, iExp);
				sp.Bind(5, SP_IN, iMesso);
				sp.Bind(6, SP_IN, szIP);
				sp.Bind(7, SP_OUT, nLogID);
				sp.Bind(8, SP_IN, byChannel);

				return sp.Execute();
			}
			return false;
		}
#endif

		bool SafeDB_test::SetLogLogout(INT64 nLogID, int iExp, int iMesso)
		{
#ifdef DF_DB_LOG_THREAD
			WCHAR *wszLog = WORKMANAGER->GetLog( L"{call usp_Log_CharLogout(%I64d,%d,%d)}", nLogID, iExp, iMesso ); 
			WORKMANAGER->PutLog( m_iThreadID, wszLog );
			return true;
#else
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_Log_CharLogout(?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, nLogID);
				sp.Bind(2, SP_IN, iExp);
				sp.Bind(3, SP_IN, iMesso);		// [이상] 마이너스 값이 들어갈 수 없는데 마이너스 값이 들어가 있음...

				return sp.Execute();
			}
			return false;
#endif
		}

		bool SafeDB_test::AddLogQuest(BYTE byLogType, DWORD dwMembIndex, DWORD dwCharIndex, BYTE byLevel, int nQuestID)
		{
#ifdef DF_DB_LOG_THREAD
			WCHAR *wszLog = WORKMANAGER->GetLog( L"{call usp_Log_Quest(%u,%u,%d,%d,%d)}", 
				dwMembIndex, dwCharIndex, byLevel, nQuestID, byLogType );
			WORKMANAGER->PutLog( m_iThreadID, wszLog );
			return true;
#else
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_Log_Quest(?,?,?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwMembIndex);
				sp.Bind(2, SP_IN, dwCharIndex);
				sp.Bind(3, SP_IN, byLevel);
				sp.Bind(4, SP_IN, nQuestID);
				sp.Bind(5, SP_IN, byLogType);

				return sp.Execute();
			}
			return false;
#endif
		}

		bool SafeDB_test::AddLogCharShop(BYTE byLogType, DWORD dwMembIndex, DWORD dwCharIndex, DWORD dwDestMembIndex, DWORD dwDestCharIndex,
			BYTE byMap, DWORD dwItemIndex, WORD wItemCount, int iPrice, ITEMSN lItemSN )
		{
#ifdef DF_DB_LOG_THREAD
			WCHAR *wszLog = WORKMANAGER->GetLog( L"{call usp_Log_CharShop(%u,%u,%u,%u,%d,%d,%u,%u,%d,%I64d)}", 
				dwDestMembIndex, dwDestCharIndex, dwMembIndex, dwCharIndex, byLogType, byMap, dwItemIndex, wItemCount, iPrice, lItemSN ); 
			WORKMANAGER->PutLog( m_iThreadID, wszLog );
			return true;
#else
			jOdbcParameter sp;

			if( m_pDB->Prepare( "{call usp_Log_CharShop(?,?,?,?,?,?,?,?,?,?)}", &sp ) )
			{
				sp.Bind( 1, SP_IN, dwDestMembIndex );
				sp.Bind( 2, SP_IN, dwDestCharIndex );
				sp.Bind( 3, SP_IN, dwMembIndex );
				sp.Bind( 4, SP_IN, dwCharIndex );
				sp.Bind( 5, SP_IN, byLogType );
				sp.Bind( 6, SP_IN, byMap );
				sp.Bind( 7, SP_IN, dwItemIndex );
				sp.Bind( 8, SP_IN, wItemCount );
				sp.Bind( 9, SP_IN, iPrice );
				sp.Bind(10, SP_IN, lItemSN );

				return sp.Execute();
			}
			return false;
#endif
		}

		bool SafeDB_test::AddLogJob(BYTE byLogType, DWORD dwMembIndex, DWORD dwCharIndex, BYTE byJob)
		{
#ifdef DF_DB_LOG_THREAD
			WCHAR *wszLog = WORKMANAGER->GetLog( L"{call usp_Log_CharJob(%u,%u,%d,%d)}", dwMembIndex, dwCharIndex, byLogType, byJob );
			WORKMANAGER->PutLog( m_iThreadID, wszLog );
			return true;
#else
			jOdbcParameter sp;

			if( m_pDB->Prepare( "{call usp_Log_CharJob(?,?,?,?)}", &sp ) )
			{
				sp.Bind( 1, SP_IN, dwMembIndex );
				sp.Bind( 2, SP_IN, dwCharIndex );
				sp.Bind( 3, SP_IN, byLogType );
				sp.Bind( 4, SP_IN, byJob );

				return sp.Execute();
			}
			return false;
#endif
		}

		bool SafeDB_test::AddLogCardBook(DWORD dwMembIndex, DWORD dwCharIndex, BYTE byBookPage, BYTE byBookSlot, DWORD dwItemID, int iPagePoint, int iCardPoint, int iBookPoint)
		{
#ifdef DF_DB_LOG_THREAD
			WCHAR *wszLog = WORKMANAGER->GetLog( L"{call usp_Log_CardBook(%u,%u,%d,%d,%u,%d,%d,%d)}", 
				dwMembIndex, dwCharIndex, byBookPage, byBookSlot, dwItemID, iPagePoint, iCardPoint, iBookPoint );	
			WORKMANAGER->PutLog( m_iThreadID, wszLog );
			return true;
#else
			jOdbcParameter sp;

			if( m_pDB->Prepare( "{call usp_Log_CardBook(?,?,?,?,?,?,?,?)}", &sp ) )
			{
				sp.Bind( 1, SP_IN, dwMembIndex );
				sp.Bind( 2, SP_IN, dwCharIndex );
				sp.Bind( 3, SP_IN, byBookPage );
				sp.Bind( 4, SP_IN, byBookSlot );
				sp.Bind( 5, SP_IN, dwItemID );
				sp.Bind( 6, SP_IN, iPagePoint );
				sp.Bind( 7, SP_IN, iCardPoint );
				sp.Bind( 8, SP_IN, iBookPoint );

				return sp.Execute();
			}
			return false;
#endif
		}

		bool SafeDB_test::AddLogWorldDrop(DWORD dwMembIndex, DWORD dwCharIndex, DWORD dwItemID, ITEMSN lItemSN, BYTE byChannel)
		{
#ifdef DF_DB_LOG_THREAD
			WCHAR *wszLog = WORKMANAGER->GetLog( L"{call usp_Log_WorldDrop(%u,%u,%u,%I64d,%d)}", 
				dwMembIndex, dwCharIndex, dwItemID, lItemSN, byChannel );
			WORKMANAGER->PutLog( m_iThreadID, wszLog );
			return true;
#else
			jOdbcParameter sp;

			if( m_pDB->Prepare( "{call usp_Log_WorldDrop(?,?,?,?,?)}", &sp) )
			{
				sp.Bind( 1, SP_IN, dwMembIndex );
				sp.Bind( 2, SP_IN, dwCharIndex );
				sp.Bind( 3, SP_IN, dwItemID );
				sp.Bind( 4, SP_IN, lItemSN );
				sp.Bind( 5, SP_IN, byChannel );

				return sp.Execute();
			}
			return false;
#endif
		}

		//#ifdef DF_HANBIT
		bool SafeDB_test::ChangeGiftMailAtt( INT64 lGiftMailSN, DWORD dwCharIndex, DWORD &dwRecvMembIndex, DWORD &dwRecvCharIndex, DWORD &dwNewRecvMail )
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_Mail_ChangeGiftAtt(?,?,?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwCharIndex);
				sp.Bind(2, SP_IN, lGiftMailSN);
				sp.Bind(3, SP_OUT, dwRecvMembIndex);
				sp.Bind(4, SP_OUT, dwRecvCharIndex);
				sp.Bind(5, SP_OUT, dwNewRecvMail);

				return sp.Execute();
			}
			return false;
		}
		//#endif


#ifdef DF_BUGSIG
		void SafeDB_test::AddBugSig( DWORD dwMembIndex, DWORD dwCharIndex, BYTE byType, BYTE byChannelNo, WORD wMapID, char *szIP, int iMesso, BYTE byLevel, int iExp, WCHAR *wszName, char *szID, BYTE byPCRoom )
		{
#ifdef DF_DB_LOG_THREAD
			WCHAR *wszLog = WORKMANAGER->GetLog( L"{call usp_WriteBug2(%u,%u,%d,%d,%d,'%s',%d,%d,%d,'%s','%s',%d)}", 
				dwMembIndex, dwCharIndex, byType, byChannelNo, wMapID, szIP, iMesso, byLevel, iExp, wszName, szID, byPCRoom );
			WORKMANAGER->PutLog( m_iThreadID, wszLog );
			return;
#else
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_WriteBug2(?,?,?,?,?,?,?,?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwMembIndex);
				sp.Bind(2, SP_IN, dwCharIndex);
				sp.Bind(3, SP_IN, byType);
				sp.Bind(4, SP_IN, byChannelNo);
				sp.Bind(5, SP_IN, wMapID);
				sp.Bind(6, SP_IN, szIP);
				sp.Bind(7, SP_IN, iMesso);
				sp.Bind(8, SP_IN, byLevel);
				sp.Bind(9, SP_IN, iExp);
				sp.Bind(10, SP_IN, wszName);
				sp.Bind(11, SP_IN, szID);
				sp.Bind(12, SP_IN, byPCRoom);	

				return sp.Execute();
			}
			return false;
#endif
		}
#endif

		bool SafeDB_test::AddLogMesso( CharInfo *pCharInfo, BYTE byGroup, BYTE byLogType, int iMesso )
		{
#ifdef DF_DB_LOG_THREAD
			WCHAR *wszLog = WORKMANAGER->GetLog( L"{call usp_Log_Messo(%u,%d,%d,%d,%d,%d,%u,%u,%d,%d)}", 
				pCharInfo->m_BaseInfo.m_dwCharIndex, pCharInfo->m_BaseInfo.m_byLevel, byLogType, pCharInfo->m_BaseInfo.m_iMesso, iMesso,
				pCharInfo->m_Book.m_nBookPt, pCharInfo->m_BaseInfo.m_dwAdvPoint, pCharInfo->m_StatInfo.m_wRemainPoint, pCharInfo->m_BaseInfo.m_byGrade,
				pCharInfo->m_BaseInfo.m_iExp );
			WORKMANAGER->PutLog( m_iThreadID, wszLog );
			return true;
#else
			jOdbcParameter sp;

			if( m_pDB->Prepare("{call usp_Log_Messo(?,?,?,?,?,?,?,?,?,?)}", &sp ) )
			{
				sp.Bind( 1, SP_IN, pCharInfo->m_BaseInfo.m_dwCharIndex );
				sp.Bind( 2, SP_IN, pCharInfo->m_BaseInfo.m_byLevel );
				sp.Bind( 3, SP_IN, byLogType );
				sp.Bind( 4, SP_IN, pCharInfo->m_BaseInfo.m_iMesso );		// [이상] 마이너스 값이 들어갈 수 없는데 마이너스 값이 들어가 있음...
				sp.Bind( 5, SP_IN, iMesso );
				sp.Bind( 6, SP_IN, pCharInfo->m_Book.m_nBookPt );			// 카드북포인트
				sp.Bind( 7, SP_IN, pCharInfo->m_BaseInfo.m_dwAdvPoint );	// 모험포인트
				sp.Bind( 8, SP_IN, pCharInfo->m_StatInfo.m_wRemainPoint );	// 잔여포인트
				sp.Bind( 9, SP_IN, pCharInfo->m_BaseInfo.m_byGrade );		// 계급
				sp.Bind( 10, SP_IN, pCharInfo->m_BaseInfo.m_iExp );

				return sp.Execute();
			}

			return false;
#endif
		}

#ifdef DF_PCROOM
		int SafeDB_test::SendPCMail( DWORD dwCharIndex, DWORD dwHour )
		{
			jOdbcParameter sp;
			BYTE byPCSend = 0;

			if (m_pDB->Prepare("{call usp_PcMailSend(?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwCharIndex);
				sp.Bind(2, SP_IN, dwHour);
				sp.Bind(3, SP_OUT, byPCSend);

				OdbcRecord rec;
				if (sp.Execute(&rec))
				{
					while (rec.Next())
					{

						rec.Data(1, byPCSend );
					}

					rec.More();

					if( byPCSend == 1 )
					{
						return 2;
					}


					return 0;
				}
			}
			return 1;
		}

		bool SafeDB_test::SendPCLogout( DWORD dwMembIndex, DWORD dwPlayTime )
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_PCLogout(?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwMembIndex);
				sp.Bind(2, SP_IN, dwPlayTime);

				return sp.Execute();
			}

			return false;
		}
#endif



		/*
		bool SafeDB_test::GuildInfoLog( CharInfo *pCharInfo, BYTE byType )
		{
		jOdbcParameter sp;

		if (m_pDB->Prepare("{call usp_GuildInfoLog(?,?)}", &sp))
		{
		sp.Bind(1, SP_IN, pCharInfo->m_dw);
		sp.Bind(2, SP_IN, dwPlayTime);

		return sp.Execute();
		}

		return false;
		}
		*/


		BYTE GetItemType(BYTE kind0, BYTE kind1, BYTE kind2)
		{
			if(kind0 == 0 && kind1 == 5 && kind2 == 0) return ONEHAND_PHYSICS;			//한손 물리	
			if(kind0 == 0 && kind1 == 5 && kind2 == 6) return SHIELD;						//방패
			if(kind0 == 0 && kind1 == 5 && (kind2 == 2 || kind2 == 4)) return TWOHAND_PHYSICS;			//양손 물리	
			if(kind0 == 0 && kind1 == 5 && kind2 == 7) return SSANGSU;					//쌍수
			if(kind0 == 0 && kind1 == 5 && kind2 == 8) return FIGHT;						//격투	
			if(kind0 == 0 && kind1 == 5 && (kind2 == 9 || kind2 == 10 || kind2 == 11)) return LONG_DISTANCE_PHYSICS;		//원거리 물리
			if(kind0 == 0 && kind1 == 5 && kind2 == 1) return ONEHAND_MAGIC;				//한손 마법	
			if(kind0 == 0 && kind1 == 5 && kind2 == 3) return TWOHAND_MAGIC;				//양손 마법
			if(kind0 == 0 && kind1 == 5 && kind2 == 5) return SUJUNGGU;					//수정구		

			if(kind0 == 0 && kind1 == 1) return HELMET;						//투구	
			if(kind0 == 0 && kind1 == 2) return ARMOR;						//갑옷
			if(kind0 == 0 && kind1 == 3) return GLOVE;						//장갑
			if(kind0 == 0 && kind1 == 4) return BOOTS;						//신발

			if(kind0 == 0 && kind1 == 6) return RING;						//링
			if(kind0 == 0 && kind1 == 7) return NECKLACE;					//목걸이
			if(kind0 == 0 && kind1 == 8) return EARRING;					//귀걸이

			if(kind0 == 0 && kind1 == 0) return UNIFORM_OUTER;				//복장	
			if(kind0 == 0 && kind1 == 11) return HEADBAND_OUTER;			//머리띠
			if(kind0 == 0 && kind1 == 17) return HEAD_OUTER;				//머리
			if(kind0 == 0 && kind1 == 16) return SHOULDR_OUTER;				//어깨
			if(kind0 == 0 && kind1 == 14) return ARM_OUTER;					//팔
			if(kind0 == 0 && kind1 == 19) return BODY_OUTER;				//몸통
			if(kind0 == 0 && kind1 == 12) return BACK_OUTER;				//등
			if(kind0 == 0 && kind1 == 13) return WAIST_OUTER;				//허리
			if(kind0 == 0 && kind1 == 18) return LEG_OUTER;					//다리
			if(kind0 == 0 && kind1 == 15) return ANKLE_OUTER;				//발목

			if(kind0 == 3 && kind1 == 1) return MERCENARY_CARD;				//용병카드
			if(kind0 == 3 && kind1 == 0) return SKILL_CARD;					//스킬카드
			if(kind0 == 3 && kind1 == 2) return MATERIAL_CARD;				//스킬카드

			if(kind0 == 1 && kind1 == 2) return BOOSTERS;					//부스터
			if(kind0 == 1 && kind1 == 3) return CONTACT_AGENT;				//촉매제
			if(kind0 == 1 && kind1 == 4) return INCHENT;					//인첸트
			if(kind0 == 1 && kind1 == 1) return MATERIALS;					//재료
			if(kind0 == 1 && kind1 == 7) return QUEST;						//퀘스트
			if(kind0 == 4 && kind1 == 1) return EQUIPRECIPE;				//장비레시피
			if(kind0 == 4 && kind1 == 2) return CARDRECIPE;					//카드레시피
			if(kind0 == 4 && kind1 == 3) return NORMALRECIPE;				//카드레시피
			if(kind0 == 1 && kind1 == 8) return PACKAGE_ITEM;				//패키지아이템

			if(kind0 == 1 && kind1 == 9) return CASH_CHARGE;				//캐쉬충전(금돼지)

			return 0;
		}


#ifdef DF_CHARSHOP_SEARCH
		bool SafeDB_test::RegistCharShopSearch( CharShopInfo *pShopInfo, WORD wMapID, WCHAR* wszShopHost )
		{
			BYTE byItemType = 0;
			Sys_Item *iip = NULL;

			jOdbcParameter sp;
			if (m_pDB->Prepare("{call usp_CharShopSearchClear(?)}", &sp))
			{
				sp.Bind(1, SP_IN, pShopInfo->m_dwCharIndex);

				sp.Execute();
			}

			for(BYTE i = 0; i < pShopInfo->m_bySlotCount; ++i)
			{
				if(pShopInfo->m_sData[i].m_dwItemIndex)
				{
					iip = Get_Sys_Item( GetLow( pShopInfo->m_sData[i].m_dwItemIndex ) );
					if(!iip) return false;
					byItemType = GetItemType(iip->kind0, iip->kind1, iip->kind2);

					jOdbcParameter sp;

					if (m_pDB->Prepare("{call usp_CharShopSearchRegist(?,?,?,?,?,?,?,?,?,?,?,?)}", &sp))
					{
						sp.Bind(1, SP_IN, pShopInfo->m_dwCharIndex);
						sp.Bind(2, SP_IN, wszShopHost);
						sp.Bind(3, SP_IN, pShopInfo->m_sData[i].m_dwItemIndex);				
						sp.Bind(4, SP_IN, iip->name);
						sp.Bind(5, SP_IN, pShopInfo->m_sData[i].m_iPrice);
						sp.Bind(6, SP_IN, iip->use_level);
						sp.Bind(7, SP_IN, iip->job_cate_only);
						sp.Bind(8, SP_IN, pShopInfo->m_wszShopName);
						sp.Bind(9, SP_IN, pShopInfo->m_byChannel);
						sp.Bind(10, SP_IN, wMapID);
						sp.Bind(11, SP_IN, byItemType);
						sp.Bind(12, SP_IN, i);

						sp.Execute();
					}
				}
			}

			return true;
		}

		bool SafeDB_test::UnRegistCharShopSearch( DWORD dwCharIndex )
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_CharShopSearchClear(?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwCharIndex);

				return sp.Execute();
			}
			return false;
		}

		bool SafeDB_test::CharShopSearchDeleteOne( DWORD dwCharIndex, BYTE bySlot )
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_CharShopSearchDeleteOne(?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwCharIndex);
				sp.Bind(2, SP_IN, bySlot);

				return sp.Execute();
			}
			return false;
		}

		bool SafeDB_test::CharShopSearch(BYTE byItemType, WORD wItemNameLen, WCHAR *wszItemName, BYTE byMinLevel, BYTE byMaxLevel, BYTE byJob, BYTE bySort, BYTE bySortType, BYTE byPage, Packet *pSendPacket)
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_CharShopSearch(?,?,?,?,?,?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, byItemType);
				sp.Bind(2, SP_IN, wszItemName);
				sp.Bind(3, SP_IN, byMinLevel);
				sp.Bind(4, SP_IN, byMaxLevel);
				sp.Bind(5, SP_IN, byJob);
				sp.Bind(6, SP_IN, bySort);
				sp.Bind(7, SP_IN, bySortType);
				sp.Bind(8, SP_IN, byPage);

				OdbcRecord rec;

				if( sp.Execute(&rec) )
				{
					if (rec.Next())
					{
						BYTE byTotalPage = 0, byCount = 0;
						rec.Data(1, byTotalPage);

						*pSendPacket << byTotalPage;

						if(byTotalPage == 0 )
						{
							return true;
						}

						rec.Data(2, byPage);
						rec.Data(3, byCount);

						*pSendPacket << byPage << byCount;

						if(rec.More())
						{					
							DWORD dwItemID = 0;
							int iPrice = 0;
							WCHAR wszShopName[32] = { 0, };
							BYTE byChannel = 0;
							WORD wMap = 0;
							WCHAR wszShopHost[24] = { 0, };

							while(rec.Next())
							{
								rec.Data(1, dwItemID);
								rec.Data(2, iPrice);
								rec.Data(3, wszShopName, 32);
								rec.Data(4, byChannel);
								rec.Data(5, wMap);
								rec.Data(6, wszShopHost, 24);

								*pSendPacket << dwItemID << iPrice;
								pSendPacket->addWString(wszShopName, (DWORD)wcslen(wszShopName));
								*pSendPacket << byChannel << wMap;
								pSendPacket->addWString(wszShopHost, (DWORD)wcslen(wszShopHost));

								ZeroMemory(wszShopName, sizeof(wszShopName));
								ZeroMemory(wszShopHost, sizeof(wszShopHost));
							}

							return true;
						}
					}
				}
			}
			return false;
		}
#endif


#ifdef DF_PARTY_MATCHING
		bool SafeDB_test::RegistPartyMatching( short nMapMode, DWORD dwMemberIndex, WCHAR *wszCharName, BYTE byChannel, BYTE byMode, BYTE byDifficult, BYTE byCharLevel, BYTE byJob )
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_RegistPartyMatching(?,?,?,?,?,?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, nMapMode);
				sp.Bind(2, SP_IN, dwMemberIndex);
				sp.Bind(3, SP_IN, wszCharName);
				sp.Bind(4, SP_IN, byChannel);
				sp.Bind(5, SP_IN, byMode);
				sp.Bind(6, SP_IN, byDifficult);
				sp.Bind(7, SP_IN, byCharLevel);
				sp.Bind(8, SP_IN, byJob);

				OdbcRecord rec;

				if( sp.Execute(&rec) )
				{
					if (rec.Next())
					{
						BYTE byResult = 0;
						rec.Data(1, byResult);

						return byResult == 0;
					}
				}
			}

			return false;
		}

		bool SafeDB_test::UnRegistPartyMatching( short nMapMode, DWORD dwMemberIndex )
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_UnRegistPartyMatching(?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, nMapMode);
				sp.Bind(2, SP_IN, dwMemberIndex);

				OdbcRecord rec;

				if( sp.Execute(&rec) )
				{
					if (rec.Next())
					{
						BYTE byResult = 0;
						rec.Data(1, byResult);

						return byResult == 0;
					}
				}
			}

			return false;
		}

		bool SafeDB_test::SearchPartyMatching( short nMapMode, WCHAR *wszCharName, BYTE byPage, Packet *pSendPacket )
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_SearchPartyMatching(?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, nMapMode);
				sp.Bind(2, SP_IN, wszCharName);
				sp.Bind(3, SP_IN, byPage);

				OdbcRecord rec;

				if( sp.Execute(&rec) )
				{
					if (rec.Next())
					{
						BYTE byTotalPage = 0, byCount = 0;
						rec.Data(1, byTotalPage);

						*pSendPacket << byTotalPage;

						if(byTotalPage == 0 )
						{
							return true;
						}

						rec.Data(2, byPage);
						rec.Data(3, byCount);

						*pSendPacket << byPage << byCount;

						if(rec.More())
						{
							short nMapModeID = 0;
							DWORD dwMemberIndex = 0;
							WCHAR wszCharName[32] = { 0, };
							BYTE byChannel = 0;
							BYTE byMode = 0;
							BYTE byDifficult = 0;
							BYTE byCharLevel = 0;
							BYTE byJob = 0;

							while(rec.Next())
							{
								rec.Data(1, nMapModeID);
								rec.Data(2, dwMemberIndex);
								rec.Data(3, wszCharName, 32);
								rec.Data(4, byChannel);
								rec.Data(5, byMode);
								rec.Data(6, byDifficult);
								rec.Data(7, byCharLevel);
								rec.Data(8, byJob);

								*pSendPacket << nMapModeID << dwMemberIndex;
								pSendPacket->addWString(wszCharName, (DWORD)wcslen(wszCharName));
								*pSendPacket << byChannel << byMode;
								*pSendPacket << byDifficult << byCharLevel << byJob;

								ZeroMemory(wszCharName, sizeof(wszCharName));
							}

							return true;
						}
					}
				}
			}

			return false;
		}
#endif

#ifdef DF_SECRET_STORE
		bool SafeDB_test::SetSecretStore( DWORD dwMemberIndex, WCHAR *wszSecret )
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_Store_SetSecret(?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwMemberIndex);
				sp.Bind(2, SP_IN, wszSecret);

				return sp.Execute();
			}

			return false;
		}

		bool SafeDB_test::SetSecretStorePenalty( DWORD dwMemberIndex, BYTE byFailCount, DWORD dwPenalty )
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_Store_SetPenalty(?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwMemberIndex);
				sp.Bind(2, SP_IN, byFailCount);
				sp.Bind(3, SP_IN, dwPenalty);

				return sp.Execute();
			}

			return false;
		}

		bool SafeDB_test::ResetSecretStore( WCHAR *wszCharName, DWORD& dwDestMembIndex, BYTE& byResult )
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_Store_ResetSecret(?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, wszCharName);
				sp.Bind(2, SP_OUT, dwDestMembIndex);
				sp.Bind(3, SP_OUT, byResult);

				return sp.Execute();
			}
			return false;
		}
#endif

		bool SafeDB_test::GetAuction( LPCWSTR wszItemName, BYTE bySort, BYTE bySortType, INT nPage, INT& nTotalPage, AuctionItemList& itemList )
		{
			jOdbcParameter sp;

			itemList.Clear();

			if (m_pDB->Prepare("{call usp_Auction_ListBuy(?,?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, wszItemName);
				sp.Bind(2, SP_IN, bySort);
				sp.Bind(3, SP_IN, bySortType);
				sp.Bind(4, SP_IN, nPage);

				OdbcRecord rec;
				if (sp.Execute(&rec))
				{
					BYTE byCount = 0;

					if (rec.Next())
					{
						rec.Data(1, nTotalPage);
						rec.Data(2, nPage);
					}

					if (rec.More())
					{
						while (rec.Next())
						{
							if( byCount >= MAX_AUCTION_PAGE_ITEM )
								break;

							rec.Data(1, itemList.m_Item[byCount].m_AuctionID);
							rec.Data(2, itemList.m_Item[byCount].m_dwItemIndex);
							rec.Data(3, itemList.m_Item[byCount].m_Price);
							rec.Data(4, itemList.m_Item[byCount].m_wszCharName, MAX_CHAR_NAMEW );

							itemList.m_Item[byCount].m_wItemCount = 1;
							byCount++;
						}

						itemList.m_byCount = byCount;
					}
					return true;
				}
			}
			return false;
		}


		bool SafeDB_test::GetMyAuction(DWORD dwCharIndex, BYTE bySort, BYTE bySortType, INT nPage, INT& nTotalPage, AuctionItemList& itemList )
		{
			jOdbcParameter sp;

			itemList.Clear();

			if (m_pDB->Prepare("{call usp_Auction_ListSell(?,?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwCharIndex);
				sp.Bind(2, SP_IN, bySort);
				sp.Bind(3, SP_IN, bySortType);
				sp.Bind(4, SP_IN, nPage);

				OdbcRecord rec;
				if (sp.Execute(&rec))
				{
					BYTE byCount = 0;

					if (rec.Next())
					{
						rec.Data(1, nTotalPage);
						rec.Data(2, nPage);
					}

					if (rec.More())
					{
						while (rec.Next())
						{
							if( byCount >= MAX_AUCTION_PAGE_ITEM )
								break;

							rec.Data(1, itemList.m_Item[byCount].m_AuctionID);
							rec.Data(2, itemList.m_Item[byCount].m_dwItemIndex);
							rec.Data(3, itemList.m_Item[byCount].m_Price);
							rec.Data(4, itemList.m_Item[byCount].m_wszCharName, MAX_CHAR_NAMEW );

							itemList.m_Item[byCount].m_wItemCount = 1;
							byCount++;
						}

						itemList.m_byCount = byCount;
					}
					return true;
				}
			}
			return false;
		}

		bool SafeDB_test::AddAuction(DWORD dwCharIndex, LPCWSTR wszCharName, LPCWSTR wszItemName, INT nItemID, WORD wItemCount, ITEMSN lItemSN, INT nPrice, BYTE byLevel, BYTE byJob, BYTE byItemType, BYTE byMoneyType)
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_Auction_Add(?,?,?,?,?,?,?,?,?,?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, dwCharIndex);
				sp.Bind(2, SP_IN, wszCharName);
				sp.Bind(3, SP_IN, wszItemName);
				sp.Bind(4, SP_IN, nItemID);
				sp.Bind(5, SP_IN, wItemCount);
				sp.Bind(6, SP_IN, lItemSN);
				sp.Bind(7, SP_IN, nPrice);
				sp.Bind(8, SP_IN, byLevel);
				sp.Bind(9, SP_IN, byJob);
				sp.Bind(10, SP_IN, byItemType);
				sp.Bind(11, SP_IN, byMoneyType);

				return sp.Execute();
			}
			return false;
		}

		bool SafeDB_test::BuyAuction( INT64 lAuctionID, DWORD& dwOwnerCharIndex, DWORD& dwItemID, WORD& wItemCount, ITEMSN& lItemSN, int& iPrice, WCHAR* wszName )
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_Auction_Buy(?)}", &sp))
			{
				sp.Bind(1, SP_IN, lAuctionID);

				OdbcRecord rec;
				if( sp.Execute(&rec) )
				{
					if( rec.Next() )
					{
						rec.Data(1, dwOwnerCharIndex);
						rec.Data(2, dwItemID);
						rec.Data(3, wItemCount);
						rec.Data(4, lItemSN);
						rec.Data(5, iPrice);
						rec.Data(6, wszName, MAX_CHAR_NAMEW);

						return true;
					}
				}
			}
			return false;
		}

		bool SafeDB_test::DelAuction(INT64 lAuctionID, BYTE& byResult)
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_Auction_Del(?,?)}", &sp))
			{
				sp.Bind(1, SP_IN, lAuctionID);
				sp.Bind(2, SP_OUT, byResult);

				return sp.Execute();
			}
			return false;
		}

		bool SafeDB_test::ClearAuctions()
		{
			jOdbcParameter sp;

			if (m_pDB->Prepare("{call usp_Auction_Clear()}", &sp))
			{
				return sp.Execute();
			}
			return false;
		}


#endif// #if 0


	}//namespace nDB


}//nMech