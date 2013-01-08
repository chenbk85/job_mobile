/* 
	coder	:	Cho Wook Rea (4MLMman@hitel.net)(icq:74456993) 
	compiler:	vc++ 6.0
	date	:	2001-07-05���� 7:28:50
	title	:	 xml -> jxml��ȯ�� Ŭ����.

	xml file load ��Ģ.
	: 
*/
// jxElement.cpp: implementation of the jxDocument class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jXmlUtil.h"
#include "jxElement.h"
#include "jxDocument.h"
#include "jXml.h"
#include "header\\jMemoryChunk.h"
#include "base/jXmlDictionary.h"
#include "base/jTestUnit.h"
#include "Interface/xml/jIElement_op.h"
//#include "base/XFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif


namespace nMech
{
	namespace nXML
	{

		uint jxElement::_GetObjSize(){ return 1024;}
		uint jxElement::_GetSlotCount(){ return 50;}

		jxElement::jxElement()
		{
			jxElement::Create();
		}
		void jxElement::Init(cstr szName)
		{ 
			SetTreeInfo(0,0,0,0,0,0); ChangeTagName(szName);
		}

		void jxElement::Create()
		{
			m_mapUserData=0;
			m_pTagName=0;
		}


		void jxElement::ChangeTagName(cstr sz)
		{
			m_iTagIndex = nString::Get_jIStringTable()->GetIndex(sz );
			m_pTagName = nString::Get_jIStringTable()->GetName(m_iTagIndex);
		}


		jIElement* jxElement::FindByContents(cstr szElement , jIVar*v)
		{		
			return FindByContents(nString::Get_jIStringTable()->GetIndex(szElement) , v); 
		}

		jIElement* jxElement::FindElementDepth(cstr szElement)	
		{		
			return FindElementDepth(nString::Get_jIStringTable()->GetIndex(szElement));	
		}

		jIElement* jxElement::FindA(cstr szElement)
		{
			jIE* pE = Find(szElement); 
			fname_t buf;
			jAssertArg(pE!=0 ,TEXT("Not Found Element [%s] from %s(%s)") 
				, szElement , this->m_pTagName , GetDoc()->GetURL(buf));
			return pE;
		}
		jIElement* jxElement::FindA(nMech::StringID szElement)
		{
			jIE* pE = Find(szElement); 
			fname_t buf;
			jAssertArg(pE!=0 ,TEXT("Not Found Element [%s] from %s(%s)") 
				, nString::Get_jIStringTable()->GetName(szElement), this->m_pTagName , GetDoc()->GetURL(buf));
			return pE;
		}

		jIElement* jxElement::FindA(cstr szElement, int iDepth)
		{
			jIE* pE = FindByDepth(iDepth, szElement);
			fname_t buf;
			jAssertArg(pE!=0 ,TEXT("Not Found Element [%s] from %s(%s)") 
				, szElement , this->m_pTagName , GetDoc()->GetURL(buf));
			return pE;

		}
		jIElement* jxElement::FindA(nMech::StringID szElement, int iDepth)
		{
			jIE* pE = FindByDepth(iDepth, szElement);
			fname_t buf;
			jAssertArg(pE!=0 ,TEXT("Not Found Element [%s] from %s(%s)") 
				, nString::Get_jIStringTable()->GetName(szElement), this->m_pTagName , GetDoc()->GetURL(buf));
			return pE;

		}

		cstr jxElement::Get_cstr() 
		{		
			if(m_Data.GetType() == jIVar::ETelement)
			{
				jRAISE(size()==0 && _T("if(m_Data.GetType() == jIVar::ETelement)"));
				m_Data.SetType(jxVar::EDcstr);
			}
			return m_Data.Get_cstr();
		}


		void jxElement::Set_cstr(cstr sz)
		{
			if(m_Data.GetType() == jIVar::ETelement)
			{
				jRAISE(size()==0);
				m_Data.m_eType = jIVar::EDcstr;
			}
			m_Data.Set_cstr(sz);
		}

		//****************************************************************
		// xml element������ �޸� ûũ�� ����.
		void jxElement::writeChunk(nUtil::jMemoryChunk& mc)
			//****************************************************************
		{	
			m_AttMap.writeChunk(mc);

			mc.writeChunk(const_cast<TCHAR*>(m_pTagName));
			m_Data.writeChunk(mc);

			if(m_Data.m_eType < jxVar::EDataType_MAX)	
			{		
				return;
			}
			else if(m_Data.IsNULL())
				return;

			uint16 iSize12 = iChild;
			mc.writeChunk(iSize12);
			jIE* it;
			rFOR(_pC,it)
			{
				it->writeChunk(mc);
			}
		}

		//****************************************************************
		// �޸� ûũ�� ���� xml element�� �����Ͽ� �����Ѵ�.
		void jxElement::readChunk(nUtil::jMemoryChunk& mc)
			/*{chowookrea@hotmail2004-07-26���� 9:22:50
			int main(int argc, TCHAR* argv[])
			{
			nFileSystem::jFileName fn;
			fn.Init("Z:\\TEST.XML");
			jxD* pD =g_pXml->Load(fn.buffer);
			jxD* pDclone = g_pXml->Clone(pD);
			jxE* peA = pD->Find(TEXT("AVATA_PICTURE_RECT"));
			jxVar* pV = &peA->Find(TEXT("ALL"))->GetVar();
			pV->pI[0]=1;
			pV->pI[1]=2;
			pV->pI[2]=3;
			pV->pI[3]=4;
			jMemoryChunk mc;
			mc.init(256);
			peA->writePacket(mc);
			jxE* peAclone = pDclone->Find(TEXT("AVATA_PICTURE_RECT"));
			peAclone->DebugPrint();
			mc.m_iCurrPos=0;
			peAclone->readPacket(mc);
			peAclone->DebugPrint();

			return 0;
			}
			}chowookrea@hotmail 2004-07-26���� 9:22:47*/
			//****************************************************************
		{
			m_AttMap.readChunk(mc);
			TCHAR* buf;
			mc.readChunk(&buf);
			assert(jt_strlen(buf));
			m_iTagIndex = nString::Get_jIStringTable()->GetIndex(buf);
			m_pTagName = nString::Get_jIStringTable()->GetName(m_iTagIndex);

			m_Data.readChunk(mc);
			if(m_Data.m_eType < jxVar::EDataType_MAX)	
			{		
				return;
			}
			else if(m_Data.IsNULL()) 
				return;

			uint16 len;
			mc.readChunk(len);

			EraseChild();
			jRAISE(!_pC);
			if(len==0) return;

			jxE* it = NewCB();
			it->readChunk(mc);
			for(size_t  i =1; i < len ; i++)	
			{
				it = it->NewR();
				it->readChunk(mc);
			}
			//#endif
		}

		//---------------------------------------------------------------
		void jxElement::writePacket(nUtil::jMemoryChunk& mc) // network packet��.
			//----------------------------------------------------------------
		{
			m_AttMap.writePacket(mc);
			m_Data.writePacket(mc);
			if(m_Data.m_eType < jxVar::EDataType_MAX)	
			{		
				return;
			}
			else if(m_Data.IsNULL() )
				return;
			jIE* it=begin();
			jrFOR(it)
			{
				it->writePacket(mc);
			}
		}

		//---------------------------------------------------------------
		void jxElement::readPacket(nUtil::jMemoryChunk& mc)
			//----------------------------------------------------------------
		{
			m_AttMap.readPacket(mc);
			m_Data.readPacket(mc);
			if(m_Data.m_eType < jxVar::EDataType_MAX)	
			{		
				return;
			}
			else if(m_Data.IsNULL()) 
				return;

			jIE* it = begin();
			jrFOR(it)	
			{
				it->readPacket(mc);
			}
		}

		//----------------------------------------------------------------
		jIE* jxElement::FindElementDepth(nMech::StringID idx)
			//----------------------------------------------------------------
		{
			if(m_iTagIndex == idx)
				return this;

			jIE* it,*pRet;
			rFOR(_pC, it)
			{
				pRet = ((jxE*)it)->FindElementDepth(idx);
				if(pRet) return pRet;
			}
			return 0;
		}

		//****************************************************************
		void jxElement::SaveXML(jXmlFile*fp)
			//****************************************************************
		{
			TCHAR bufX[2048];

			SaveIndent(fp);
			fname_t name;	
			m_Data.GetTagNameByType(GetTagName() , name);
			jxD* pD = (jxD*)GetDoc();
			jvector<std::tstring>* vecS = pD->m_jCommentManager.Find(this);
			if(m_Data.IsNULL() || (m_Data.m_eType == jxVar::ETelement && !iChild ))
			{
				if(fp->fp)
				{
					jt_fprintf(fp->fp, TEXT("<%s "), name);	
					m_AttMap.SaveXML(fp);
					jt_fprintf(fp->fp,TEXT("/>\n"));

					if(vecS)
					{
						for(uint iS=0 ; iS < vecS->size() ; ++iS)
						{
							SaveIndent(fp);
							jt_fprintf(fp->fp , TEXT("<!--%s-->\n"), (*vecS)[iS].c_str() );
						}
					}
				}
				else
				{
#ifdef UNICODE
					jt_sprintf(bufX, TEXT("<%s "), name);	
					//fp->xfp->Write(bufX,jt_strlen(bufX));
					fp->str +=bufX;

					m_AttMap.SaveXML(fp);
					
					//fp->xfp->Write(TEXT("/>\n"),jt_strlen(TEXT("/>\n")));
					fp->str +=L"/>\n";

					if(vecS)
					{
						for(uint iS=0 ; iS < vecS->size() ; ++iS)
						{
							SaveIndent(fp);
							jt_sprintf(bufX, TEXT("<!--%s-->\n"), (*vecS)[iS].c_str() );
							//fp->xfp->Write(bufX,jt_strlen(bufX));
							fp->str+=bufX;
						}
					}
#endif
				}

			}
			else
			{
				if(m_Data.m_eType< jxVar::EDataType_MAX)
				{
					if(fp->fp)
					{
						jt_fprintf(fp->fp, TEXT("<%s"), name);	
						m_AttMap.SaveXML(fp);
						jt_fprintf(fp->fp, TEXT("%s"), TEXT(">"));

						fname_t buf;
						cstr sz = m_Data.ToString(buf);
						jt_fprintf(fp->fp, TEXT("%s"),sz);
						//m_Data.SaveXML(fp);

						jt_fprintf(fp->fp, TEXT("</%s>"), name);
						if(vecS)
						{
							for(uint iS=0 ; iS < vecS->size() ; ++iS)
							{
								SaveIndent(fp);
								jt_fprintf(fp->fp , TEXT("<!--%s-->\n"), (*vecS)[iS].c_str() );
							}
						}
						else
							jt_fprintf(fp->fp,TEXT("\n"));
					}
					else
					{
#ifdef UNICODE
						jt_sprintf(bufX, TEXT("<%s"), name);	
						//fp->xfp->Write(bufX, jt_strlen(bufX));
						fp->str +=bufX;
						m_AttMap.SaveXML(fp);
						jt_sprintf(bufX, TEXT("%s"), TEXT(">"));
						//fp->xfp->Write(bufX, jt_strlen(bufX));
						fp->str +=bufX;

						fname_t buf;
						cstr sz = m_Data.ToString(buf);
						jt_sprintf(bufX, TEXT("%s"),sz);
						//fp->xfp->Write(bufX, jt_strlen(bufX));
						fp->str +=bufX;

						//m_Data.SaveXML(fp);

						jt_sprintf(bufX, TEXT("</%s>"), name);
						//fp->xfp->Write(bufX, jt_strlen(bufX));
						fp->str +=bufX;

						if(vecS)
						{
							for(uint iS=0 ; iS < vecS->size() ; ++iS)
							{
								SaveIndent(fp);
								jt_sprintf(bufX, TEXT("<!--%s-->\n"), (*vecS)[iS].c_str() );
								//fp->xfp->Write(bufX, jt_strlen(bufX));
								fp->str +=bufX;
							}
						}
						else
						{
							jt_sprintf(bufX,TEXT("\n"));
							//fp->xfp->Write(bufX, jt_strlen(bufX));
							fp->str +=bufX;

						}
#endif
					}

				}
				else
				{
					if(fp->fp)
					{
						jt_fprintf(fp->fp, TEXT("<%s"), name);	
						m_AttMap.SaveXML(fp);
						jt_fprintf(fp->fp, TEXT("%s"), TEXT(">\n"));
						if(vecS)
						{
							for(uint iS=0 ; iS < vecS->size() ; ++iS)
							{
								SaveIndent(fp);
								jt_fprintf(fp->fp , TEXT("<!--%s-->\n"), (*vecS)[iS].c_str() );
							}
						}
						jIE* it;
						rFOR(_pC , it)
						{
							((jxE*)it)->SaveXML(fp);
						}
						SaveIndent(fp);
						jt_fprintf(fp->fp, TEXT("</%s>\n"), name);
					}
					else
					{
#ifdef UNICODE
						jt_sprintf(bufX, TEXT("<%s"), name);	
						//fp->xfp->Write(bufX, jt_strlen(bufX));
						fp->str+=bufX;
						m_AttMap.SaveXML(fp);

						jt_sprintf(bufX, TEXT("%s"), TEXT(">\n"));
						//fp->xfp->Write(bufX, jt_strlen(bufX));
						fp->str+=bufX;


						if(vecS)
						{
							for(uint iS=0 ; iS < vecS->size() ; ++iS)
							{
								SaveIndent(fp);
								jt_sprintf(bufX, TEXT("<!--%s-->\n"), (*vecS)[iS].c_str() );
								//fp->xfp->Write(bufX, jt_strlen(bufX));
								fp->str+=bufX;

							}
						}
						jIE* it;
						rFOR(_pC , it)
						{
							((jxE*)it)->SaveXML(fp);
						}
						SaveIndent(fp);
						jt_sprintf(bufX, TEXT("</%s>\n"), name);
						//fp->xfp->Write(bufX, jt_strlen(bufX));
						fp->str+=bufX;

#endif
					}
				}
			}
		}
		//---------------------------------------------------------------
		// �Լ��� ����
		//----------------------------------------------------------------
		struct _jxEEqID
		{	
			nMech::StringID idE;
			_jxEEqID(nMech::StringID ide): idE(ide){}
			bool operator()(jxE* e)
			{	
				return e->m_iTagIndex == idE ;
			}
		};

		struct _jxEEqStr
		{	
			cstr idE;
			_jxEEqStr(cstr ide): idE(ide){}
			bool operator()(jxE* e)
			{	
				return !_tcscmp(e->m_pTagName ,idE );
			}
		};

		//----------------------------------------------------------------
		jIE* jxElement::Find(nMech::StringID idElement)
		{
			return _find_if(_jxEEqID(idElement) );
		}

		//---------------------------------------------------------------
		jIE* jxElement::Find(cstr szElement) // tag index�� ������� �ʰ� �˻�.
		{
			return _find_if(_jxEEqStr(szElement) );
		}

		jIE* jxElement::Find(cstr szElement,int iDepth)
		{
			return FindByDepth(iDepth, szElement);
		}
		jIE* jxElement::Find(nMech::StringID id,int iDepth)
		{
			return FindByDepth(iDepth, id);
		}


		//---------------------------------------------------------------
		jIElement* jxElement::FindFromParent(cstr szElement , jvector<jIE*> *out)
			//----------------------------------------------------------------
			// �θ���߿��� �ش� �̸��� ã�´�.
		{
			nMech::StringID idx = nString::Get_jIStringTable()->GetIndex(szElement);
			jIE* pE = FindFromParent(idx, out);
			return pE;
		}
		//---------------------------------------------------------------
		jIElement* jxElement::FindFromParent(nMech::StringID  iE,jvector<jIE*> *out)
			//----------------------------------------------------------------
		{
			jIE* it;
			for(it= this; it ; it = it->GetParent())
			{
				if(out)
					out->insert(out->begin(), it);
				if(iE == it->GetTagID() )
					return it;
			}
			if(out)
				out->clear();
			return 0;
		}


		// �ڽ��� ������ �θ���� Attribute�� �ش� �̸��� ã�´�.
		//---------------------------------------------------------------
		jIElement* jxElement::GetAttrFromParent(cstr szElement , jIVar** pvOut, jvector<jIE*> *out)
			//----------------------------------------------------------------
		{
			nMech::StringID idx = nString::Get_jIStringTable()->GetIndex(szElement);
			return GetAttrFromParent(idx,pvOut , out);
		}
		//---------------------------------------------------------------
		jIElement* jxElement::GetAttrFromParent(nMech::StringID iElement,jIVar** pvOut, jvector<jIE*> *out)
			//----------------------------------------------------------------
		{
			jIE* it= this;
			//pFOR(this , it)
			for( ; it ; it = it->GetParent() )
			{
				*pvOut = it->GetAttrVar(iElement);
				if(*pvOut) return it;
			}
			*pvOut=0;
			return 0;
		}


		struct _jxEEqID_byContents
		{	
			nMech::StringID idE;
			jxVar& v;
			_jxEEqID_byContents(nMech::StringID ide, jxVar& vv): idE(ide), v(vv){}
			bool operator()(jIE* e)
			{	
				return (e->GetTagID() == idE) && (v == *e->GetVar()->Base()) ;
			}
		};


		//---------------------------------------------------------------
		jIElement* jxElement::FindByContents(nMech::StringID idxElement, jIVar* var)
			//----------------------------------------------------------------
		{
			jIE* it,*pRet;
			rFOR( _pC,it )
			{
				if( idxElement ==jx(NULL) || it->GetTagID()== idxElement)
				{
					if(*var->Base() == *(it->GetVar()->Base()) )
						return it;
				}
			}
			rFOR( _pC,it )
			{
				pRet = it->FindByContents(idxElement, var);
				if(pRet) return pRet;
			}
			return 0;
		}

		//****************************************************************
		void jxElement::DebugPrint(bool pLogChckRetern)
			//****************************************************************
		{
			nLOG::jILog* pLog = nInterface::g_pjILog;
			//jxDocument_TRACE(TEXT(" \nchild cnt=%d\n"), m_aObj.size());
			jIE* it;
			DebugIndent(0,pLogChckRetern);
			int iDepth = GetDepth();
			if(m_Data.IsNULL())
			{
				GetjILog()->LogPlus(TEXT("<%s "), m_pTagName);
				m_AttMap.DebugPrint(pLog);
				//GetjILog()->LogPlus(TEXT(" DEPTH=\"%d\" order=%u"), iDepth, GetOrder());
				if(pLogChckRetern)
				{
					GetjILog()->LogPlus(TEXT(">\n"));
				}
				else
				{
					GetjILog()->LogPlus(TEXT(">"));
				}
			}
			else
			{
				GetjILog()->LogPlus(TEXT("<%s "), m_pTagName);
				m_AttMap.DebugPrint(pLog);
				//GetjILog()->LogPlus(TEXT(" DEPTH=\"%d\" order=%u"), iDepth, GetOrder());
				if(pLogChckRetern)
				{
					GetjILog()->LogPlus(TEXT(">\n"));
				}
				else
				{
					GetjILog()->LogPlus(TEXT(">"));
				}

				if( m_Data.m_eType < jxVar::EDataType_MAX )
				{ // m_aObj�ڽĳ�尡 ���� ����Ÿ�� �ִ�.

					if(pLogChckRetern)	DebugIndent(1,pLog);
					GetVar()->DebugPrint(pLog);
					if(pLogChckRetern)	GetjILog()->LogPlus(TEXT("\n"));
				}
				else
				{
					rFOR(_pC,it)
					{
						it->DebugPrint(pLogChckRetern);
					}

				}
				if(pLogChckRetern)
				{
					DebugIndent(0,pLog);
					GetjILog()->LogPlus(TEXT("</%s>\n"), m_pTagName);
				}
				else
				{
					GetjILog()->LogPlus(TEXT("</%s>"), m_pTagName);
				}
			}

			jxD* pD=0;
			try{
				//pD = dynamic_cast<jxD*>( GetRoot());
				pD = (jxD*)(GetRoot());
			}catch(...){}

			if(pD)
			{
				jvector<std::tstring>* vecS = pD->m_jCommentManager.Find(this);
				if(vecS)
				{
					for(uint iS=0 ; iS < vecS->size() ; ++iS)
					{
						if(pLogChckRetern)
							DebugIndent(0,pLog);
						GetjILog()->LogPlus(TEXT("<!--%s-->\n"), (*vecS)[iS].c_str() );
					}
				}
			}
		}

		void jxElement::DebugIndent(int cnt,bool isInsert_CR)
		{
			int i = 0; i-=cnt; 
			int iDepth = GetDepth();
			for( ; i < iDepth ; i++)
			{
				GetjILog()->LogPlus(TEXT("   "));
			}
		}



		//---------------------------------------------------------------
		// ������ �Ǹ������� �ڽ��� �߰�.
		jIElement* jxElement::InsertChild(cstr szTag, jIVar* v,int index)
			//----------------------------------------------------------------
		{
			jRAISE(m_Data.m_eType > jxVar::EDataType_MAX);
			m_Data.m_eType = jxVar::ETelement;
			jxE* it ;
			int iTot = (int)size();
			if(index==-1 || iTot<=index)	it = NewCE();
			else 
			{
				it = (jxE*)FindByOrder(index);
				it = it->NewL();
			}
			it->m_iTagIndex = nString::Get_jIStringTable()->GetIndex(szTag);
			it->m_pTagName = nString::Get_jIStringTable()->GetName(it->m_iTagIndex);
			if(v)		it->m_Data =*(v->Base());
			return it;
		}

		bool jxElement::InsertChild(jIE* peB1,jIE* peI)
		{
			jxE* peInsert = (jxE*)peI;
			jxE* peB = (jxE*)peB1;
			if(peB&& (this != peB->GetParent()) ) 
				return false;
			
			++iChild;
			if(!peB)
			{
				peInsert->_pR = _pC;
				if(_pC)_pC->_pL = peInsert;
				peInsert->_pL = 0;
				peInsert->_pP = this;
				_pC = peInsert;
				peInsert->ReMakeSiblingOrder(0);
				return true;
			}
			peInsert->_pL = peB;
			peInsert->_pR = peB->_pR;
			if(peB->_pR) 
				peB->_pR->_pL = peInsert;
			peB->_pR = peInsert;
			peInsert->_pP = this;
			peB->ReMakeSiblingOrder(peB->iOrder);
			return true;
		}


		//---------------------------------------------------------------
		void jxElement::DeleteAttr(cstr szAttrTag)
			//----------------------------------------------------------------
		{
			jxAttributeList::iterator it = m_AttMap.find(szAttrTag);
			if(it==m_AttMap.end() ) return;
			m_AttMap.erase(it);
		}

		//---------------------------------------------------------------
		cstr  jxElement::IsXmlFileNode()
			//----------------------------------------------------------------
		{
			bool is= false;
			if(GetType() != jxVar::EDcstr ) return false;
			if(_tcsstr(GetTagName() ,TEXT("FILE")) )		is= true;
			else if(_pP)
			{
				if(_tcsstr( _pP->GetTagName() , TEXT("FILE_LIST") ) )		is=true;
				if(_tcsstr( _pP->GetTagName() , (jS(FILES)) ) )		is=true;
				else
				{
					jIE* peP = _pP->GetParent();
					while(peP )
					{
						if(_tcsstr( peP->GetTagName() , jS(FILES)))
						{
							is = true;
							break;
						}
						peP = peP->GetParent();
					}
				}
			}

			if(is)
			{
				nFileSystem::jFileName fn(Get_cstr());
				if(_tcsstr(fn.ext , TEXT(".xml")))
					return TEXT(".xml");
			}
			return 0;
		}

		//---------------------------------------------------------------
		cstr jxElement::IsFileNode(cstr szExt=0)
			//----------------------------------------------------------------
		{
			bool is= false;
			if(GetType() != jxVar::EDcstr ) return false;

			if(_tcsstr(GetTagName() ,TEXT("FILE")) )		
				is= true;
			else if( _pP)
			{
				if(_tcsstr( _pP->GetTagName() , TEXT("FILE_LIST") ) )		
					is=true;
				else if(_tcsstr( _pP->GetTagName() , (jS(FILES)) ) )		
					is=true;
				else
				{
					jIE* peP = _pP->GetParent();
					while(peP)
					{
						if(_tcsstr( peP->GetTagName() , jS(FILES)))
						{
							is = true;
							break;
						}
						peP = peP->GetParent();
					}
				}
			}

			if(is)
			{
				static nFileSystem::jFileName fn;
				fn.Init(Get_cstr());
				if(szExt)
				{
					if(_tcsstr(fn.ext , szExt))
						return szExt;
				}
				return fn.ext;
			}
			return 0;
		}

		//---------------------------------------------------------------
		// �ش� ������Ʈ�� 1���� �ڽ��߿� �ش� ��Ʈ����Ʈ�� ������ �ڽ��� ���� 
		jIElement* jxElement::FindByFirstAttr(cstr szAttName, jIVar* v,int iChildLevel )
			//----------------------------------------------------------------
		{
			if(iChildLevel ==0) 
				return 0;

			jIE* it = begin();
			jIVar* pV;
			jrFOR( it)
			{
				pV = it->GetAttrVar(szAttName);
				if(!pV) 
					continue; 
				if(!v) 
					return it; // �Ӽ��� ������ �񱳾��ص� �Ǹ� ã����.
				if( *v->Base() == *pV->Base())	
					return it; // ������ ���ؾ��Ѵٸ� ���ؼ� ������ it����.
			}
			jIE* pE;
			it = begin();
			jrFOR( it)
			{
				pE = it->FindByFirstAttr( szAttName ,v ,iChildLevel-1 );
				if(pE) return pE;
			}
			return 0;
		}
		jIElement* jxElement::FindByFirstAttr(nMech::StringID szAttName, jIVar* v,int iChildLevel )
		{
			if(iChildLevel ==0) 
				return 0;

			jIE* it = begin();
			jIVar* pV;
			jrFOR( it)
			{
				pV = it->GetAttrVar(szAttName);
				if(!pV) 
					continue; 
				if(!v) 
					return it; // �Ӽ��� ������ �񱳾��ص� �Ǹ� ã����.
				if( *v->Base() == *pV->Base())	
					return it; // ������ ���ؾ��Ѵٸ� ���ؼ� ������ it����.
			}
			jIE* pE;
			it = begin();
			jrFOR( it)
			{
				pE = it->FindByFirstAttr( szAttName ,v ,iChildLevel-1 );
				if(pE) return pE;
			}
			return 0;
		}

		//---------------------------------------------------------------
		// iChildLevel�� 1�̸� �ٷ� ���� �ڽĿ� ���ؼ��� 
		jIElement* jxElement::FindByDepth(int iChildLevel , cstr szElement)
			//----------------------------------------------------------------
		{
			jIE* it = begin();
			if(iChildLevel <=0) 
				return 0;
			jrFOR( it)
			{
				if(!_tcscmp( it->GetTagName() , szElement ))
				{
					return it;
				}
			}
			jIE* pE;
			it = begin() ;
			jrFOR( it)
			{
				pE = it->FindByDepth(iChildLevel-1 , szElement);
				if(pE) return pE;
			}
			return 0;
		}

		//---------------------------------------------------------------
		// iChildLevel�� 1�̸� �ٷ� ���� �ڽĿ� ���ؼ��� 
		jIElement* jxElement::FindByDepth(int iChildLevel , StringID szElement)
			//----------------------------------------------------------------
		{
			jIE* it = begin();
			if(iChildLevel <=0) 
				return 0;
			jrFOR( it)
			{
				if(it->GetTagID()== szElement)
				{
					return it;
				}
			}
			jIE* pE;
			it = begin() ;
			jrFOR( it)
			{
				pE = it->FindByDepth(iChildLevel-1 , szElement);
				if(pE) return pE;
			}
			return 0;
		}

		//---------------------------------------------------------------
		void jxElement::CopyTo(jIElement*pe)
			//----------------------------------------------------------------
		{
			jxE * pE = (jxE*)pe;
			pE->m_AttMap.clear();
			pE->m_AttMap.insert(m_AttMap._begin() ,m_AttMap._end() );
			assert(m_AttMap.size() == pE->m_AttMap.size());

			pE->m_iTagIndex = m_iTagIndex;
			pE->m_pTagName = m_pTagName;
#ifdef _DEBUG
			assert( nString::Get_jIStringTable()->GetIndex(pE->m_pTagName) == pE->m_iTagIndex );
#endif
			assert(pE->m_pTagName);
			pE->m_Data = m_Data;

			CopyTo_Child(pE);
		}


		//---------------------------------------------------------------
		// pE�� �ڽĵ鸸 �����Ŵ
		void jxElement::CopyTo_Child(jIElement*pe)
			//----------------------------------------------------------------
		{
			jxE* pE = (jxE*)pe;
			if(m_Data.GetType() < jxVar::EDataType_MAX)		return;
			else if(m_Data.IsNULL()) 		return;

			pE->EraseChild();
			jRAISE(!pE->_pC);
			jIE* it = begin();
			int i=0;
			jrFOR(it)
			{
				++i;
				assert(it->GetTagName());
				assert(_tcslen(it->GetTagName()));
				jxE* itClone = pE->NewCE();
				((jxE*)it)->CopyTo(itClone);
			}
			assert(pE->size() ==size());
		}


		//---------------------------------------------------------------
		void jxElement::for_each(run_function_t *pFunc, void*v)
			//----------------------------------------------------------------
		{
			if(!pFunc(this,v)) return;
			jIE* it = begin();
			jrFOR( it)
			{
				it->for_each(pFunc,v);
			}
		}

#define _InitPersistElement_j622345(X)		\
	jIElement* jxElement::Persist( cstr name, X defaultValue) {	return Persist(nString::Get_jIStringTable()->GetIndex(name)  , defaultValue);	}\
	jIElement* jxElement::Persist( const StringID name, X defaultValue)\
		{\
		jIElement* pE = this->FindByDepth(1,name);\
		if(pE) return pE;\
		cstr sz = nString::Get_jIStringTable()->GetName(name);\
		pE = this->InsertChildElement(sz);\
		pE->GetVar()->InitValue(defaultValue);\
		return pE;\
		}\
		jIVar* jxElement::PersistAttr( cstr name, X defaultValue){	return PersistAttr(nString::Get_jIStringTable()->GetIndex(name), defaultValue);	}\
		jIVar* jxElement::PersistAttr( const  StringID name, X defaultValue)\
		{\
		jIVar* pV = this->GetAttrVar(name);\
		if(pV) return pV;\
		cstr sz = nString::Get_jIStringTable()->GetName(name);\
		pV = this->InsertAttr(sz);\
		pV->InitValue(defaultValue);\
		return pV;\
		}

		_for_each_setter_type_jvar(_InitPersistElement_j622345)
#undef _InitPersistElement_j622345

			//---------------------------------------------------------------
			jIElement* jxElement::Persist( cstr szName, jIVar::EElementType etype, cstr szDefaultValue_By_string)
		{	return Persist(nString::Get_jIStringTable()->GetIndex(szName) , etype , szDefaultValue_By_string); }
		jIElement* jxElement::Persist( StringID idName, jIVar::EElementType etype, cstr szDefaultValue_By_string)
		{
			cstr sz = nString::Get_jIStringTable()->GetName(idName);
			jIElement* pE = this->FindByDepth(1,sz);
			if(!pE)
			{
				pE = this->InsertChildElement(sz);
				if(szDefaultValue_By_string)
					pE->GetVar()->InitValue(szDefaultValue_By_string , etype);
				else
					pE->GetVar()->SetType( etype );
			}
			return pE;
		}
		//---------------------------------------------------------------
		jIVar* jxElement::PersistAttr(cstr szName, jIVar::EElementType etype,cstr szDefaultValue_By_string)
		{	return PersistAttr(nString::Get_jIStringTable()->GetIndex(szName) , etype , szDefaultValue_By_string); }
		jIVar* jxElement::PersistAttr(StringID idName, jIVar::EElementType etype,cstr szDefaultValue_By_string)
		{
			jIVar* pV = this->GetAttrVar(idName);
			if(!pV)
			{
				cstr sz = nString::Get_jIStringTable()->GetName(idName);
				pV = this->InsertAttr(sz);
				if(szDefaultValue_By_string)
					pV->InitValue(szDefaultValue_By_string , etype);
				else
					pV->SetType( etype );

			}
			return pV;
		}


		//---------------------------------------------------------------
		jID* jxElement::SXPathFromThis(jIE** ppE ,jIAttribute** ppA ) // �ش翤����Ʈ�� SXPATH����̴�.
			//----------------------------------------------------------------
		{
			assert(GetTagID()==jx(SXPATH) );
			*ppE=0; *ppA=0;
			jIVar* pV = this->PersistAttr( jx(DOC), jIVar::EDcstr ,g_XmlNULL);
			if(!_tcscmp( pV->Get_cstr() , g_XmlNULL ) ) return 0;

			nFileSystem::jFolder dm;
			dm.GotoStartDir();
			nFileSystem::UFileName fn(pV->Get_cstr() );
			if(!fn.IsFileExist()) 
			{
				fname_t szjXml;
				jt_sprintf(szjXml,_T("%s%s%s.jxml"),fn.drive,fn.dir,fn.fname);
				if(!nFileSystem::jFolder::Is_Exist(szjXml))
				{
					return 0;
				}
			}
			jID* pD = g_pXml->Load(fn.buffer);
			if(!pD) return 0;

			cstr szXPath = Get_cstr();
			if(!szXPath) 	return 0;

			if(!_tcscmp(szXPath, g_XmlNULL))
				Set_cstr(TEXT(""));

			*ppE= pD->GetSXPathNode(this->Get_cstr(), ppA );

			return pD;
		}

		// xpath ���� : @�� �Ӽ��̴�.  TEXT("attname@element.parent2.parent1.parent")  
		//								parent�� root�� ���Ծȵ�.
		// xml orb�� ��ŶElement�� ���.
		//----------------------------------------------------------
		jID* jxElement::XPathFromThis(jIE** ppE , jIAttribute** ppA )
		{
			assert(GetTagID() == jx(XPATH));
			*ppE=0; *ppA=0;

			jvector<std::tstring> outAtt, outE;

			jIVar* pV = this->PersistAttr( jx(DOC), jxVar::EDcstr ,g_XmlNULL);
			if(!_tcscmp( pV->Get_cstr() , g_XmlNULL ) ) return 0;

			nFileSystem::jFolder dm;
			dm.GotoStartDir();
			nFileSystem::UFileName fn(pV->Get_cstr() );
			if(!fn.IsFileExist()) return 0;
			jID* pD = g_pXml->Load(fn.buffer);
			if(!pD) return 0;

			cstr szXPath = Get_cstr();
			if(!szXPath) 	return 0;

			if(!_tcscmp(szXPath, g_XmlNULL))
				Set_cstr(TEXT(""));


			*ppE = pD->GetXPathNode(Get_cstr() , ppA);

			return pD;
		}

		//---------------------------------------------------------------
		void jxElement::SetXPathContents(jIE* pE, jIAttribute* pA)
			//
			//----------------------------------------------------------------
		{
			TCHAR buf[1024];
			jID* pD;
			if(GetTagID()==jx(XPATH))
			{
				pD = pE->XPathToString(buf, pA);
			}
			else if(GetTagID()==jx(SXPATH))
			{
				pD = pE->SXPathToString(buf, pA);
			}
			else assert(0);

			Set_cstr(buf);
			GetAttrVar(TEXT("DOC"))->Set_cstr(pD->GetURL(buf));
		}

		//----------------------------------------------------------
		// xpath ���� : @�� �Ӽ��̴�.  TEXT("attname@element.parent2.parent1.parent")  
		//								parent�� root�� ���Ծȵ�.
		// 
		//----------------------------------------------------------
		jID*  jxElement::XPathToString(TCHAR szOut[1024] , jIAttribute* pA  )
		{
			szOut[0]=0;
			if(pA)
			{
				_stprintf( szOut, TEXT("%s@") , pA->GetTagName() );
			}
			jIE* it;
			fname_t buf;
			for( it = this; !it->isRoot() ; it = it->GetParent() )
			{
				_stprintf(buf, TEXT("%d"), it->GetOrder());
				_tcscat(szOut , buf );
				_tcscat(szOut, TEXT("."));
			}

			if(szOut[_tcslen(szOut)-1]==TEXT('.'))
				szOut[_tcslen(szOut)-1]=0;
			assert(_tcslen(szOut) <1024);
			assert(it->isRoot());
			return (jxD*) it;
		}


		//----------------------------------------------------------
		// xpath ���� : @�� �Ӽ��̴�.  "attname@element.parent2.parent1.parent"  
		//								parent�� root�� ���Ծȵ�.
		// 
		//----------------------------------------------------------
		jID*  jxElement::SXPathToString(TCHAR szOut[1024] , jIAttribute* pA  )
		{
			szOut[0]=0;
			if(pA)
			{
				_stprintf( szOut, TEXT("%s@") , pA->GetTagName() );
			}
			jIE* it;
			for( it = this; !it->isRoot() ; it = it->GetParent() )
			{
				if(it == it->GetParent()->Find(it->GetTagID() ) )
				{
					_tcscat(szOut , it->GetTagName() );
					_tcscat(szOut, TEXT("."));
				}
				else
				{
					_tcscat(szOut , it->GetTagName() );
					_tcscat(szOut , _T(":") );
					fname_t szt;
					jt_sprintf(szt,_T("%d"),it->GetOrder() );
					_tcscat(szOut, szt);
					_tcscat(szOut, TEXT("."));
				}
			}
			if(szOut[_tcslen(szOut)-1]==TEXT('.'))
				szOut[_tcslen(szOut)-1]=0;
			assert(_tcslen(szOut) <1024);
			assert(it->isRoot());

			return (jxD*) it;
		}



		//---------------------------------------------------------------
		void jxElement::MovePosition(int iOrder)
			//----------------------------------------------------------------
		{
			if(isRoot()) return;
			if(iOrder == GetOrder()) return;

			jxE* pE;
			int tot = GetParent()->size();
			if(iOrder==-1 || iOrder >= tot )
			{
				if(!_pR) return; // �ڽ��� �Ǹ�����.
				jxE* peR = _pR; // ���������� ���� order�ű�.
				pE = (jxE*)GetParent()->FindByOrder(GetParent()->size()-1);
				if(_pR)	_pR->_pL = _pL; // ������ ������

				if(_pL) // ���� ������
					_pL->_pR = _pR;
				else 	 // �ڽ��� ū���̴�.
					_pP->_pC= _pR;

				_pL = pE; // pE�� ������ ����
				pE->_pR = this;
				_pR = 0;
				peR->ReMakeSiblingOrder(peR->GetOrder()-1 );
				return;
			}
			if(iOrder > GetOrder()) // �ڷ� �̵���
			{
				// iOrder�ڿ� ���δ�.
				pE = (jxE*)_pP->FindByOrder(iOrder);
				jxE* peR = _pR; // ���������� ���� order�� �Űܾ���.
				if(_pL)	_pL->_pR = _pR;
				else _pP->_pC = _pR;

				assert(_pR);// �ڷ� ���°��̱� ������ ������ �ִ�.
				_pR->_pL = _pL;

				if(pE->_pR)// ���ο� ���� ������ ������
					pE->_pR->_pL = this;

				_pR = pE->_pR;
				pE->_pR = this;
				_pL = pE;
				peR->ReMakeSiblingOrder(peR->GetOrder()-1);
				return;
			}
			// ������ �̵��� iOrder�տ� ���δ�.
			pE = (jxE*)_pP->FindByOrder(iOrder);
			if(_pR) // ������ ������ 
				_pR->_pL = _pL;

			assert(_pL);// ������ �̵��ϴ°��̹Ƿ� �׻� ���� �־����.
			_pL->_pR = _pR;

			if(pE->_pL) // �̵��Ұ��� ���� ������
				pE->_pL->_pR = this;
			else
				_pP->_pC = this;

			_pL = pE->_pL;
			_pR = pE;
			pE->_pL = this;
			ReMakeSiblingOrder(iOrder) ;
		}
		jIDocument* jxElement::GetDoc()
		{ 
#if 0
			try
			{
				return dynamic_cast<jID*>(GetRoot());
			}
			catch (...)
			{
				return 0;
			}
			return 0;
#endif
			return static_cast<jIDocument*> ( (jxDocument*)GetRoot() );	
		}


		//---------------------------------------------------------------
		jIElement* jxElement::FindByContents(cstr szElement, jIVar::EElementType eT , void* v)
		{	
			return jxElement::FindByContents(nString::Get_jIStringTable()->GetIndex(szElement) , eT , v );
		}
		// EDxmlstring�� �˻��Ҷ��� v�� cstr_t�� �ѱ��.
		jIElement* jxElement::FindByContents(nMech::StringID idxElement, jIVar::EElementType eT , void* v)
			//----------------------------------------------------------------
		{
			jIE* it,*pRet;
			rFOR( _pC,it )
			{
				if(idxElement==jx(NULL)|| it->GetTagID()== idxElement)
				{
					if(eT== it->GetType())
					{
						if(!v) return it;

						switch(eT)
						{
						case jIVar::EDStringID:
							{

								if(it->GetVar()->Get_StringID() == *((nMech::StringID*)v) )
									return it;
							}
						case jIVar::EDcstr:
							if(!jt_strcmp(it->Get_cstr() , (cstr)v))
								return it;
							break;
						case jIVar::EDbool:
							{
								if((*(int*)v)==it->GetVar()->Get_bool())
									return it;
							}
						case jIVar::EDint:
							{
								if((*(int*)v)==it->GetVar()->Get_int())
									return it;
							}
							break;
						case jIVar::EDhex:
						case jIVar::EDuint:
							{
								if((*(uint*)v)==it->GetVar()->uintValue())
									return it;
							}
							break;
						case jIVar::EDfloat:			
							if((*(float*)v)==it->GetVar()->floatValue())
								return it;
							break;
						default:
							jMB("ã���� ���� �ڷ�����", "FindByFirstAttr" );
							assert(0);
							break;

						}
					}
				}
			}
			rFOR( _pC,it )
			{
				pRet = it->FindByContents(idxElement, eT, v);
				if(pRet) return pRet;
			}
			return 0;
		}

		jIElement* jxElement::FindByFirstAttr(cstr szAttName, jIVar::EElementType eT , void* v,int iChildLevel)
		{	return jxElement::FindByFirstAttr( nString::Get_jIStringTable()->GetIndex(szAttName) , eT, v, iChildLevel);}
		//---------------------------------------------------------------
		jIElement* jxElement::FindByFirstAttr(nMech::StringID szAttName, jIVar::EElementType eT , void* v,int iChildLevel)
			//----------------------------------------------------------------
		{
			if(iChildLevel ==0) 
				return 0;

			jIE* it = begin();
			jIVar* pV;
			jrFOR( it)
			{
				pV = it->GetAttrVar(szAttName);
				if(!pV) 
					continue; 

				if(eT != pV->GetType() ) continue;;

				if(!v) return it; // �Ӽ��� ������ �񱳾��ص� �Ǹ� ã����.

				switch(eT)
				{
				case jIVar::EDStringID:
				case jIVar::EDcstr:
					if(!jt_strcmp(pV->Get_cstr() , (cstr)v))
						return it;
					break;
				case jIVar::EDbool:
					if((*(int*)v)==pV->Get_bool())
						return it;
				case jIVar::EDint:
					{
						if((*(int*)v)==pV->Get_int())
							return it;
					}
					break;
				case jIVar::EDhex:
				case jIVar::EDuint:
					{
						if((*(uint*)v)==pV->Get_uint())
							return it;
					}
					break;
				case jIVar::EDfloat:			
					if((*(float*)v)==pV->Get_float())
						return it;
					break;
				default:
					jMB("ã���� ���� �ڷ�����", "FindByFirstAttr" );
					assert(0);
					break;
				}
			}
			jIE* pE;
			it = begin();
			jrFOR( it)
			{
				pE = it->FindByFirstAttr( szAttName ,eT,v ,iChildLevel-1 );
				if(pE) return pE;
			}
			return 0;

		}

		void* jxElement::jGetData(cstr szDataName, void*)
		{
			return 0;
		}

		/* 
		FindByPath("-2") - �ڽ��� �������� �� �ܰ����� �θ�
		FindByPath("-3:ABC:3:DFG") �ڽ��� �������� ���ܰ����� �θ𿡼� <ABC>�׸��� ã��
		�ű⼭ ORDER�� 3��°�� �ڽ��� ã�� �״��� <DEF>�� ã�� ���ڽĵ��� ������
		FindByPath(""); �ڱ��ڽ��� ����
		*/
		jIElement* jxElement::FindByPath(cstr szPath)
		{
			if(!szPath || !jt_strlen(szPath)) return this;
			vector<std::tstring> out;
			nString::jSplit(szPath ,_T(" :"),out);
			jIE* pE = this;
			for(int i =0; i < out.size() ; ++i)
			{
				cstr sz = out[i].c_str();
				int iTot = jt_atoi(sz);
				if(!iTot)
				{
					pE = Find(sz);
				}
				else if( iTot > 0)
				{
					pE = FindByOrder(iTot);
				}
				else // ����
				{
					iTot = -iTot;
					for ( int iTot = -jt_atoi(sz);  iTot >0 ; --iTot)
					{
						pE = pE->GetParent();
						if(!pE) return 0;
					}
				}
				if(!pE) return 0;
			}
			return pE;
		}

		void jxElement::EraseAttr(nMech::StringID idAttr)
		{
			jxAttributeList::iterator it = m_AttMap.find(idAttr);
			if(it!=m_AttMap.end())m_AttMap.erase(it);
		}
		void jxElement::EraseAttr(cstr idAttr)
		{
			jxAttributeList::iterator it = m_AttMap.find(idAttr);
			if(it!=m_AttMap.end())m_AttMap.erase(it);
		}


		void jxElement::Lerp(jIE* pE1 , jIE* pE2, float fLerpRatio)
		{
			GetVar()->Lerp(pE1->GetVar(), pE2->GetVar(), fLerpRatio);
			jxAttributeList::iterator it = m_AttMap._begin(), ie = m_AttMap._end();
			jIA* pA1 = pE1->GetAttributeList()->begin()
				,*pA2 = pE2->GetAttributeList()->begin();

			for( ; it!=ie ; ++it)
			{
#ifdef _DEBUG
				jRAISE(it->GetTagID() == pA1->GetTagID());
				jRAISE(it->GetTagID() == pA2->GetTagID());
#endif
				it->GetVar()->Lerp( pA1->GetVar() , pA2->GetVar()  , fLerpRatio);
				pA1=  pA1->GetRight();
				pA2= pA2->GetRight();
			}
		}

		void jxElement::SetUserData(tcstr szTag,void* v)
		{
			if(!m_mapUserData)
				m_mapUserData = new m_mapUserData_t;
			(*m_mapUserData)[szTag] = v;
		}
		void* jxElement::GetUserData(tcstr szTag)
		{
			if(m_mapUserData)
			{
				m_mapUserData_it it = m_mapUserData->find(szTag);
				if(it!=m_mapUserData->end())
					return it->second;
			}
			return 0;
		}

		void jxElement::SaveIndent(jXmlFile* fp, int cnt)
		{
			int i = 0; i-=cnt;
			int tot = GetDepth(); 
			for( ; i < tot ; i++)
			{
				if(fp->fp)
				{
					jt_fprintf(fp->fp, TEXT("\t"));
				}
				else
				{
					fp->str+=L"\t";
					//fp->xfp->Write(TEXT("\t"), jt_strlen(TEXT("\t")));
				}
			}
		}

		static nUtil::jCriticalSection g_CS_ToString;
		wcstr jxElement::ToString()
		{
			static jXmlFile fp;
			g_CS_ToString.Lock();
			fp.str.clear();
			fp.fp = 0;
			fp.xfp = 0;
			jxElement::SaveXML(&fp);		

			return fp.str.c_str();
		}
		void jxElement::ToString_Free()
		{
			g_CS_ToString.UnLock();
		}
	}//namespace nXML
}
