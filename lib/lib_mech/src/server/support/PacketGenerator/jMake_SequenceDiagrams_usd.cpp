/* file : jMake_SequenceDiagrams_usd.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2007-09-12 16:08:14
comp.: jgame.co.kr
title : 
desc : 



시킨스		프로토콜 해더 저장 폴더									*.usd파일이 있는 폴더
usd			Z:\source_ES\server\CE_Server\Protocal		Z:\source_ES\server\CE_Server\sequence


usd Z:\source_ES\server\CE_Server\Protocal Z:\doc_ce_team\sequence
*/

#include "stdafx.h"
#include "util/juFileEnum.h"
#include "header/uString_stl.h"
#include "jMake_SequenceDiagrams_usd.h"
#include "base/jxVar.h"
#include "functor/_jxCopyAttributeTo.h"
#include "interface/jIPak.h"

namespace nUSD_FILE
{
	tstring g_sTargetDir_usd ;
	tstring g_sTargetDir;
	jID* g_pDocProtocalDefine;
	jID* g_pDocProtocalPrototype;
	jLIST_TYPEDEF_map(std::tstring ,jID*, g_usdFiles);
	jLIST_TYPEDEF_map(std::tstring ,jID*, g_mapDomainXml_ByNamespace);
	jLIST_TYPEDEF_map(std::tstring ,jIE*, g_mapPacket_ByName);
	jLIST_TYPEDEF_map(std::tstring ,jNote_Protocal, g_mapNote_Protocal);
	jLIST_TYPEDEF_map(std::tstring ,jNote_Etc, g_mapNote_Etc);


	namespace fs = boost::filesystem;

	void _Load_uds_files(tcstr szPath,void*)
	{
		tstring strPath =szPath;
		nFileSystem::jFileName fn(strPath.c_str());
		
		if(jt_strcmp(fn.ext, _T(".usd") )) return;

		jFlagHelper useTiny(GetjIXml()->GetFlag(), nXML::eUSE_TINY_XML,true);
		nPAK::jIPak* asdf = nInterface::g_pjIPak;
		nInterface::g_pjIPak=0;
		jID* pD = GetjIXml()->Load(strPath.c_str());
		nInterface::g_pjIPak = asdf;

		useTiny.Reset();
		if(!pD) 
		{
			jWARN(_T("xml로딩 에러 : %s"), strPath.c_str());
			jMB(strPath.c_str(),_T("error"));
			return;
		}

		jIE* pE = pD->BaseI()->Find(_T("title"),1);
		if(!jt_strnicmp(pE->Get_cstr(), _T("Skip"), 4))
		{
			GetjIXml()->UnLoad(pD);
			return;
		}
		//cout << strPath<< endl;
		g_usdFiles[strPath.c_str()] = pD;
	}


	void trim_string(std::tstring& s)
	{
		s =nMech::nSTL::trim(s);
	}

	void puf_insert_Packet_to_DomainXmlProtocal(nXML::jE ePacket
		,cstr szNamespace,nXML::jE guardCond)
	{

		g_mapNote_Protocal_it it = g_mapNote_Protocal.find(ePacket->GetTagName());
		if(it==g_mapNote_Protocal.end()) 
		{
			//발견이 안되면 guardCond값으로 세팅
			vector<std::tstring> out, out1;
			nString::jSplit(guardCond->Get_cstr() , _T(","),out);
			if(!out.size()) return;

			for( size_t i =0; i < out.size(); ++i)
			{// SERVER_ID-serverid_t,result-int16
				out1.clear();
				tstring tok = nSTL::trim(out[i]);
				nString::jSplit(tok, _T("-"),out1);
				if(out1.size()!=2)
				{
					return;
				}
				if(i==0)
				{
					fname_t buf;
					guardCond->GetDoc()->GetURL(buf);
					tstring sBuf = buf;
					nSTL::replace(sBuf, g_sTargetDir_usd, _T("") );
					ePacket->PersistAttr(_T("USD"), sBuf.c_str());
				}

				nXML::jE eParam = ePacket->Persist(out1[0].c_str(), jIVar::ETelement);
				vector<std::tstring> out2_errorcheck;
				nString::jSplit(out1[1], _T("[]"),out2_errorcheck);
				out2_errorcheck.clear();
				nString::jSplit(out1[1], _T("[]"),out2_errorcheck);

				tstring sType = nSTL::trim(out2_errorcheck[0]);
				eParam.AttrP(_T("TYPE")).SetType(jIVar::EDcstr)->Set_cstr(sType.c_str());
				if(out2_errorcheck.size()==2)
				{
					int ilen = -1;
					if(out2_errorcheck[1][0]!='?')
						ilen = jt_atoi(out2_errorcheck[1].c_str());
					eParam.AttrP(_T("Length")).SetType(jIVar::EDint)->Set_int(ilen);
				}
			}
			return;
		}
		jNote_Protocal* v = &it->second;

		v->usdFile = nMech::nSTL::trim(v->usdFile);
		jFileName fn(v->usdFile.c_str());
		fname_t buf;
		fn.GetName(buf);
		tstring sBuf = buf;
		nSTL::replace(sBuf, g_sTargetDir_usd, _T("") );
		ePacket->PersistAttr(_T("USD"), sBuf.c_str());
		v->help = nMech::nSTL::trim(v->help);
		if(v->help.size())
		{
			ePacket->PersistAttr(_T("HELP"), v->help.c_str());
		}

		nXML::jE eNamespaceDef = g_pDocProtocalDefine->Find(_T("Namespace") )->Find(szNamespace);
		if(!eNamespaceDef.full())
		{
			jERROR_T("g_pDocProtocalDefine->Find(_T(Namespace) )->Find( %s );" , szNamespace);
		}

		for(size_t ii=0; ii< v->option.size() ; ++ii)
		{
			fname_t buf;
			vector<std::tstring> out;
			nMech::nString::jSplit(v->option[ii], _T("=\n"),out);
			if(out.size()!=2)
			{
				jERROR_T("out.size()!=2   =>    %s",v->option[ii].c_str());
			}
			jFOR_EACH(out, trim_string);
			jt_strncpy(buf, out[0].c_str() , ARRAY_SIZE(buf));
			jIVar::EElementType eType = jxVar::GetTypeByTagName(buf);
			ePacket.AttrP(buf).SetType(eType)->FromString(out[1].c_str());
		}


		for(size_t i =0; i < v->param.size(); ++i)
		{
			nXML::jE eParam = ePacket->Persist(v->param[i].name.c_str(), jIVar::ETelement);
			tstring sType = nSTL::trim(v->param[i].type);
			eParam.AttrP(_T("TYPE")).SetType(jIVar::EDcstr)->Set_cstr(sType.c_str());
			if(v->param[i].len)
				eParam.AttrP(_T("Length")).SetType(jIVar::EDint)->Set_int(v->param[i].len);

			v->param[i].help = nMech::nSTL::trim(v->param[i].help);
			if(v->param[i].help.size())
				eParam->PersistAttr(_T("HELP"), v->param[i].help.c_str());

		}
	}


	//--------------------------------------------------------------------------
	void puf_Parse_From_DomainObj(jID* pDocDomain, cstr szNamespace, jIE* peDomainObj_FromUSD)
	//--------------------------------------------------------------------------
	{
		//cout << "puf_Parse_From_DomainObj() UMLSDOBJ = " << szNamespace << "), _T("<< pDocDomain->GetURL(buf) << endl;

		pDocDomain->BaseI()->PersistAttr(_T("DebugPrint"),(int)2);

		jIE* pRoot_CurrUSDFile = peDomainObj_FromUSD->GetRoot();
		jIE* actBoxes = peDomainObj_FromUSD->Find(_T("actBoxes") );
		jIVar* pvDomainID = peDomainObj_FromUSD->Find(_T("objId") )->GetVar();
		jIE* actBox = actBoxes->begin();
		vector<std::tstring> out;
		jrFOR(actBox)
		{
			jIVar* actBoxID = actBox->GetAttrVar(_T("id")) ;
			jIE* peUMLSDACTBOX=pRoot_CurrUSDFile->FindByContents(_T("objId"), actBoxID)->GetParent();
			assert(peUMLSDACTBOX->Find(_T("type") )->IsContents(_T("UMLSDACTBOX")) );

			jIE* links = peUMLSDACTBOX->Find(_T("links") );
			jIE* link = links->begin();
			jrFOR(link)
			{
				//if(guardCond->GetType() == jIVar::ETelement)		continue;
				nXML::jE eUMLSDMESS = pRoot_CurrUSDFile->FindByContents(_T("objId"),link->GetAttrVar(_T("id")) )->GetParent() ;
				cstr message = eUMLSDMESS(_T("message") );
				if(!jt_strcmp(message,_T("UserInfo") ) )
				{
					int i =0;
					++i;
				}

				nXML::jE guardCond = eUMLSDMESS(_T("guardCond") );

				assert(eUMLSDMESS(_T("type")) ->IsContents(_T("UMLSDMESS")) );
				jIVar* objStart = eUMLSDMESS(_T("objStart") )->GetAttrVar(_T("id") );
				jIVar* objEnd = eUMLSDMESS( _T("objEnd") )->GetAttrVar(_T("id"));
				jIVar* pvThere_actBoxID=0,*pvHere_actBoxID=0;

				bool isCHANGE_DIR=false;
				if(objStart->IsContents(actBoxID->Get_cstr()))
				{
					pvThere_actBoxID = objEnd;
					pvHere_actBoxID= objStart;
				}
				else
				{
					isCHANGE_DIR=true;
					pvThere_actBoxID = objStart;
					pvHere_actBoxID= objEnd;
				}

				//cout << "actBoxID = " << actBoxID->Get_cstr() << endl;
				//cout << "objStart=" << objStart->Get_cstr() << endl;
				//cout << "objEnd=" << objEnd->Get_cstr() << endl;
				//cout << "pvThere_actBoxID=" << pvThere_actBoxID->Get_cstr() << endl;

				nXML::jE eHere_Domain = pRoot_CurrUSDFile->find_if(_jxFind_UMLSDOBJ_actBox_id(pvHere_actBoxID));
				nXML::jE eThere_Domain = pRoot_CurrUSDFile->find_if(_jxFind_UMLSDOBJ_actBox_id(pvThere_actBoxID));
				eHere_Domain = eHere_Domain(-2);
				eThere_Domain = eThere_Domain(-2);
				//cout << "eThere_Domain \n";
				//eThere_Domain->DebugPrint(nInterface::g_pjILog);
				assert(eHere_Domain( _T("type") )->IsContents(_T("UMLSDOBJ")) );
				assert(eThere_Domain( _T("type") )->IsContents(_T("UMLSDOBJ")) );
				jVar pvThereName = eThere_Domain( _T("objectName") );
				tstring There_TAG = eThere_Domain( jS(className));

				jVar pvHereName = eHere_Domain( _T("objectName") );
				tstring Here_TAG = eHere_Domain( jS(className));
				tstring sNEW_GROUP_TAG,sNEW_GROUP_NAME;
				if(!isCHANGE_DIR)
				{
					sNEW_GROUP_NAME = tstring(pvHereName->Get_cstr()) + _T("_") + pvThereName->Get_cstr();
					sNEW_GROUP_TAG= Here_TAG + _T("2") + There_TAG;
				}
				else 
				{
					sNEW_GROUP_NAME = tstring(pvThereName->Get_cstr()) + _T("_") + pvHereName->Get_cstr();
					sNEW_GROUP_TAG= There_TAG + _T("2") + Here_TAG;
				}
				sNEW_GROUP_TAG+=(tstring(_T(".")) + sNEW_GROUP_NAME);

				// 이쪽도메인과 저쪽도메인을 비교하여 어느쪽 도메인에 패킷을 추가할것인지 결정
				nXML::jE eDomain_in_ProtoDef = g_pDocProtocalDefine->BaseI()->Find(_T("Namespace"),1)->Find(szNamespace,1);
				assert(eDomain_in_ProtoDef.full());

				jID* pDocTargetDomain = pDocDomain;
				cstr szThereDomainName = eThere_Domain( _T("objectName") )->Get_cstr();
				g_mapDomainXml_ByNamespace_it it = g_mapDomainXml_ByNamespace.find( szThereDomainName );
				if(it==g_mapDomainXml_ByNamespace.end()) 
				{
					if(!g_pDocProtocalDefine->BaseI()->Find(szThereDomainName))// 등록이안된 도메인을 사용
					{
						cout << "WARNNING 등록안된 도메인 발견 : ";
						tcout << szThereDomainName << endl;
						continue;
					}
				}
				else // 어느쪽을 사용할지 결정
				{
					if( eDomain_in_ProtoDef(_T("Child"))(pvThereName->Get_cstr()).empty() )
					{
						// 현제 도메인에 저쪽도메인이 자식으로 등록되어 있지 않으므로 저쪽도메인의 프로토콜문서에 등록하자.
						pDocTargetDomain = it->second;
						nXML::jE eThereDomain_in_ProtoDef = g_pDocProtocalDefine->BaseI()->Find(_T("Namespace"),1)->Find(pvThereName->Get_cstr(),1);
						if(eThereDomain_in_ProtoDef(_T("Child"))(szNamespace).empty())
						{
							fname_t buf, bufDoc;
							jt_sprintf(buf, _T("%s의 차일드중 %s발견안됨 : protocal name = %s , usd=%s")
								,eThereDomain_in_ProtoDef->GetTagName()
								,szNamespace
								,message
								,peDomainObj_FromUSD->GetDoc()->GetURL(bufDoc)
								);
							jMB(buf, _T("에러 ProtocalPrototype.xml의 도메인에 Child가 발견안됨"));
							continue;
						}
					}
				}

				jIE* pePT = pDocTargetDomain->Find(_T("PROTOCAL_LIST"));
				//eUMLSDMESS->DebugPrint(nInterface::g_pjILog);
				if(pePT->Find(message))	continue;
				if(jt_strchr(message,'-')) continue;
				if(jt_strchr(message,' ')) continue;
				if(!jt_strlen(message)) continue;
				jIE* pePacket= pePT->Persist(message, jIVar::ETelement,0);
				if(pePacket->size()) continue;

				//GROUP_TAG처리
				nXML::jE ePacket = pePacket;
				jVar vGROUP_TAG = ePacket.AttrP(jS(GROUP_TAG));
				jLIST_TYPEDEF_vector(tstring,outGROUP_TAG);
				nString::jSplit(vGROUP_TAG->Get_cstr(),_T(";"),outGROUP_TAG);
				outGROUP_TAG_it itGROUP = jFIND(outGROUP_TAG,sNEW_GROUP_TAG);
				if(itGROUP==outGROUP_TAG.end())
				{
					tstring sNEW = sNEW_GROUP_TAG+ _T(";")  + vGROUP_TAG->Get_cstr();
					vGROUP_TAG->Set_cstr(sNEW.c_str());
				}

				g_mapPacket_ByName[message] = pePT;
				out.clear();
				//cout << szNamespace << " insert -> " << pePacket->GetTagName() << endl ;

				// param이 세팅이 되었다.
				
				puf_insert_Packet_to_DomainXmlProtocal(pePacket,szNamespace,guardCond);
			}
		}
	}

	//--------------------------------------------------------------------------
	void puf_parse_usd_file(g_usdFiles_vt vt)
		//--------------------------------------------------------------------------
	{
		jID* pDocUSD = vt.second;
		jIE* peElements = pDocUSD->BaseI()->Find(_T("elements"),1);
		jIE* itObj = peElements->begin();
		//cout << "puf_parse_usd_file() : " << vt.first << endl;
		jrFOR(itObj)
		{
			if(itObj->Find(_T("type"),1)->IsContents(_T("UMLSDOBJ")) )
			{
				cstr szNamespace = itObj->Find(_T("objectName"),1)->Get_cstr();
				//cout << "check : UMLSDOBJ : " << szNamespace << endl;

				g_mapDomainXml_ByNamespace_it it = g_mapDomainXml_ByNamespace.find(szNamespace);
				if(it==g_mapDomainXml_ByNamespace.end()) continue;
				jID* pDocDomain = it->second;
				puf_Parse_From_DomainObj(pDocDomain, szNamespace, itObj);

			}
		}

		// enum list등처리 ( UMLNOTE )
		g_mapNote_Etc_it it = g_mapNote_Etc.begin(),ie = g_mapNote_Etc.end();
		for(;it!=ie;++it)
		{
			if(it->second.type == jS(enum))
			{
				vector<tstring> outName;
				nString::jSplit(it->first,_T(":") , outName);
				if(outName.size()<2 || outName.size()>3)
				{
					fname_t szFile;
					jWARN(_T("UMLNOTE , NAME PARSE : %s : %s"), vt.second->GetURL(szFile), it->first.c_str());
					continue;
				}
				g_mapDomainXml_ByNamespace_it itXmlDoc = g_mapDomainXml_ByNamespace.find(outName[0]);
				if(itXmlDoc==g_mapDomainXml_ByNamespace.end()) 
				{
					fname_t szFile;
					jWARN(_T("UMLNOTE , NAME PARSE , Namespace not found: %s : %s"), vt.second->GetURL(szFile), it->first.c_str());
					continue;
				}
				nXML::jE eEnumList= itXmlDoc->second;
				eEnumList = eEnumList[jS(ENUM_TYPE_LIST)];
				nXML::jE eEnumNode = eEnumList[outName[outName.size()-1]], eEnumVal; // enum 이름
				eEnumNode.AttrP(jS(USD_FILE))  =it->second.doc;
				if(outName.size()==3)
				{
					eEnumNode.AttrP(jS(SCOPE))  =outName[1];
				}
				tstring& body = it->second.body;
				vector<tstring> out,outE;
				nString::jSplit(body, _T("\n\r"),out);
				for(int i =0; i < out.size(); ++i)
				{
					outE.clear();
					nSTL::trim(out[i]);
					nString::jSplit(out[i] , _T(",") , outE);
					nSTL::trim(outE[0]);
					
					tstring valName,val,help;
					valName = outE[0];

					if(outE.size()!=1)
					{
						help = outE[1];
					}
					outE.clear();
					nString::jSplit(valName, _T("= "),outE);
					valName = outE[0];
					if(outE.size()!=1)
					{
						val = outE[1];
					}
					eEnumVal = eEnumNode[valName];
					//if(help.size())
					eEnumVal.AttrP(jS(help)).T() = help;
					if(val.size())
						eEnumVal.AttrP(jS(val)).T() = (int) jt_atoi(val.c_str());
				}
			}
		}

	}
	void parse_etc_note(g_usdFiles_vt vt,TCHAR* szNote)
	{
		TCHAR* szTitle = szNote+1;
		TCHAR* ch = jt_strchr(szTitle,'>');
		*ch = 0;
		TCHAR* szBody = ch+1;

		ch = jt_strchr(szTitle, ' ');
		fname_t buf;
		vt.second->GetURL(buf);
		if(!ch) 
		{
			jWARN(_T("UMLNOTE parse error: %s : %s"),buf, szNote);
			return;
		}
		*ch = 0;
		TCHAR* szName = ch+1;
		jNote_Etc& en = g_mapNote_Etc[szName];
		en.type= szTitle;
		en.body = szBody;
		en.doc = buf;
		
		nSTL::replace(en.body, _T("&#x0A;"), _T(""));
	}

	//--------------------------------------------------------------------------
	void load_note_in_usdFile(g_usdFiles_vt vt)
		//--------------------------------------------------------------------------
	{
		fname_t buf;
		jID* pDocUSD = vt.second;
		jIE* peElements = pDocUSD->BaseI()->Find(_T("elements"),1);
		jIE* itObj = peElements->begin();
		vector<std::tstring> out, out2_errorcheck,out3;
		jrFOR(itObj)
		{
			out.clear();
			out2_errorcheck.clear();
			out3.clear();
			if(itObj->Find(_T("type"),1)->IsContents(_T("UMLNOTE")) )
			{
				//itObj->DebugPrint(nInterface::g_pjILog);
				TCHAR description[2048];
				jt_strncpy( description ,itObj->Find(_T("description") )->Get_cstr(), ARRAY_SIZE(description));
				if( description[0]=='<')
				{
					parse_etc_note(vt,description);
					continue;
				}

				if( description[0] != '[')  continue;
				TCHAR* pEnd = jt_strchr(description, ']');
				*pEnd = 0;
				tstring protocalName = description+1;
				g_mapNote_Protocal_value_t *val =&g_mapNote_Protocal[protocalName];
				nMech::nFileSystem::jFileName fn(pDocUSD->GetURL(buf));
				//val->usdFile = fn.GetName(buf);
				val->usdFile = pDocUSD->GetURL(buf);
				val->name = protocalName;
				tcout << _T("\tOK reg : ") << protocalName << _T(" : ") << val->usdFile <<endl;

				++pEnd;
				TCHAR* pHelp = pEnd;
				TCHAR* pParam = jt_strstr(pEnd, _T("{PARAM}") );
				if(!pParam) 
				{
					val->help = pHelp;
					continue;
				}
				else
				{
					pParam[0] =0;
					pParam += jt_strlen( _T("{PARAM}") );
					val->help = pHelp;
				}

				//--------------------------------------------------------------------------
				// {OPTION}처리
				//--------------------------------------------------------------------------
				pEnd = jt_strstr(pParam,_T("{OPTION}"));
				if(pEnd)
				{
					pEnd[0]=0;
					TCHAR* pOption = pEnd + jt_strlen(_T("{OPTION}"));
					nMech::nString::jSplit(pOption, _T("\n"),val->option);
					jFOR_EACH(val->option,trim_string);
				}

				//--------------------------------------------------------------------------
				// {PARAM}처리
				//--------------------------------------------------------------------------
				out.clear();
				nMech::nString::jSplit(pParam, _T("\n"),out);
				for(size_t i=0 ; i< out.size() ; ++i)
				{
					if(!out[i].size()) continue;
					out3.clear();
					out2_errorcheck.clear();
					assert(out.size()>i);
					nMech::nString::jSplit(out[i] , _T("-"), out2_errorcheck);
					out2_errorcheck.clear();
					nMech::nString::jSplit(out[i] , _T("-"), out2_errorcheck);
					jNote_Protocal::_jParam vParam;
					if(out2_errorcheck.size()<2)
					{
						jWARN(_T("note parse error : %s"), itObj->Find(_T("description") )->Get_cstr());
						continue;
					}
					assert(out2_errorcheck.size()>=1);
					vParam.name = out2_errorcheck[0];
					assert(out2_errorcheck.size()>=2);
					nMech::nString::jSplit(out2_errorcheck[1], _T("[]"), out3);

					if(out3.size()==1)
					{
						assert(out2_errorcheck.size()>=2);
						vParam.type = out2_errorcheck[1];
						vParam.len = 0;
					}
					else
					{
						assert(out3.size() >=1);
						vParam.type = out3[0];
						if(out3[1][0]=='?')
							vParam.len =-1;
						else
							vParam.len = jt_atoi(out3[1].c_str());
					}

					if(out2_errorcheck.size()>=3)
					{
						assert(out2_errorcheck.size()>=3);
						vParam.help = out2_errorcheck[2];
					}
					//cout << "param reg = " << out[i] << endl;
					val->param.push_back(vParam);
				}
			}
		}
	}

	//--------------------------------------------------------------------------
	struct _jxSetup_DomainFile_by_cfg
		//--------------------------------------------------------------------------
	{
		void operator() ( jIE* it )
		{
			cstr szFile = it->GetAttr(_T("FILE"));
			if(!szFile) return;
			nMech::nFileSystem::jFolder dm;

			tstring strXml = g_sTargetDir + _T("\\") + szFile;

			dm.Goto(g_sTargetDir.c_str());
			fname_t buf;
			g_pDocProtocalPrototype->GetURL(buf);
			CopyFile(buf , szFile,0);

			jID* pD = GetjIXml()->Load(strXml.c_str());
			pD->BaseI()->GetAttrVar(_T("HEADER") )->Set_cstr(it->GetTagName());

			nXML::jE eDocAtt = it->Find(_T("DOC_ATTRIBUTE"),1);
			assert(eDocAtt.full());
			eDocAtt->for_each_attr(_jxCopyAttributeTo(pD->BaseI()));

			jIE* peCode = it->Find(_T("CODE"));
			if(peCode && peCode->GetType()==jIVar::EDcstr)
			{
				jIVar* pv = pD->Find(_T("CODE") )->GetVar();
				if(pv) 
				{
					pv->SetType(jIVar::EDcstr);
					pv->Set_cstr(peCode->Get_cstr());
				}
			}
			//pD->DebugPrint(nInterface::g_pjILog);
			g_mapDomainXml_ByNamespace[it->GetTagName()] = pD;
			//cout << "g_mapDomainXml_ByNamespace[" << it->GetTagName() << "]= " << pD->GetURL(buf) << endl;

		}
	};

	void _jxSave_doc(g_mapDomainXml_ByNamespace_vt vt)
	{	
		//vt.second->DebugPrint(nInterface::g_pjILog);
		vt.second->Save();
	}
	void _jxRun_parse_jINet_OGS_Protocal(g_mapDomainXml_ByNamespace_vt vt)
	{
		jID* pD = vt.second;

		int argc = ARG_TEXT_EDITOR;
		TCHAR *argv[ARG_NET_MAX];
		fname_t buf;
		pD->GetURL(buf);
		argv[0] = g_ExeEnv.m_szExeName;
		argv[ARG_SOCKET] = _T("net");
		argv[ARG_HEADER_XML_FILE] = buf;
		argv[ARG_CREATE_TAG] = _T("PT");
		_tmain_Gen_Xml(argc,argv);

	}

}

using namespace nUSD_FILE;


//pg.exe usd Z:\source_ES\server\CE_Server\Protocal Z:\doc_ce_team\sequence
//--------------------------------------------------------------------------
void _tmain_Gen_usd(int argc, _TCHAR* argv[])
//--------------------------------------------------------------------------
{
	assert(argc>3);
	g_sTargetDir = argv[2];
	tstring sCFG = tstring(argv[3]) + _T("\\ProtocalDefine.xml");
	tstring sSaveHeaderDir = argv[2];
	g_sTargetDir_usd = argv[3];
	jt_strlwr(&g_sTargetDir_usd[0]);

	g_pDocProtocalDefine = GetjIXml()->Load(sCFG.c_str());
	if(!g_pDocProtocalDefine)
	{
		jMB(sCFG.c_str(),_T("해당 파일이 없습니다."));
		jASSERT0(g_pDocProtocalDefine);
	}
	sCFG = tstring(argv[3]) + _T("\\ProtocalPrototype.xml");
	g_pDocProtocalPrototype = GetjIXml()->Load(sCFG.c_str());
	assert(g_pDocProtocalPrototype );

	g_pDocProtocalDefine->BaseI()->for_each(_jxSetup_DomainFile_by_cfg());
	//juExeEnv::DoFileBackup

	nFileSystem::for_each_folder(g_sTargetDir_usd.c_str(), _Load_uds_files,0);
	// 데이타 준비완료.

	
	// parse1 : 노트 정보 로딩
	jFOR_EACH(g_usdFiles, load_note_in_usdFile);

	// parse2 : 프로토콜 생성시작
	jFOR_EACH(g_usdFiles, puf_parse_usd_file);

	// 결과 저장
	jFOR_EACH(g_mapDomainXml_ByNamespace,_jxSave_doc);

	// 프로토콜 해더파일 생성 
	jFOR_EACH(g_mapDomainXml_ByNamespace,_jxRun_parse_jINet_OGS_Protocal);

}
