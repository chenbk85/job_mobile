/* file : nBASE_BALL.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-04-25 15:20:18
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "nBASE_BALL.h"
#include "common/jxVar.h"
#include "excel/code/table_const_excel_enum.h"

#define jFUNC_LOG() jLOG("<<< %s:%d(%s) >>> ",__FUNCTION__,__LINE__,__FILE__);


namespace nMech
{
	namespace nXML
	{
		jTE* find(jTD& doc, tcstr szPath)
		{
			vector<tstring> o;
			nString::jSplit(szPath,".",o);
			jRETURN_ret(0,o.size());

			jTE* peFind = doc.FirstChildElement(o[0].c_str());
			jvRETURN_ret(0,peFind,"xml element not found : %s , idx = %d, %s",szPath, 0,o[0].c_str());
			for(int i=1; i< o.size() ; ++i)
			{
				peFind = peFind->FirstChildElement(o[i].c_str());
				jvRETURN_ret(0,peFind,"xml element not found : %s , idx = %d, %s",szPath, i,o[i].c_str());
			}
			return peFind;
		}

// 		jTE* find(jTE* pE, tcstr szPath)
// 		{
// 			jRETURN_ret(0,pE);
// 			jRETURN_ret(0,szPath);
// 			vector<tstring> o;
// 			nString::jSplit(szPath,".",o);
// 			jRETURN_ret(0,o.size());
// 			jLOG("%s : szPath= %s", jFUNC, szPath);
// 			jTE* peFind = pE->FirstChildElement(o[0].c_str());
// 			jRETURN_ret(0,peFind);
// 			for(int i=1; i< o.size() ; ++i)
// 			{
// 				peFind = peFind->FirstChildElement(o[i].c_str());
// 				jvRETURN_ret(0,peFind,"xml element not found : %s , idx = %d, %s",szPath, i,o[i].c_str());
// 			}
// 			return peFind;
// 		}

#		define jTE_for(pE) for(;pE;pE = pE->NextSiblingElement())
		void for_each(jTE* peParent, for_each_ft& func)
		{
			jRETURN(peParent);
			TiXmlElement* pE = peParent->FirstChildElement();
			jTE_for(pE)
			{
				func(pE);
			}
		}
		jTE* find_if(jTE* peParent, find_if_ft& func)
		{
			jRETURN_ret(false,peParent);
			TiXmlElement* pE = peParent->FirstChildElement();
			jTE_for(pE)
			{
				if(func(pE))
					return pE;
			}
			return 0;
		}

		void print_element(jTE* pE)
		{
			jLOG("%s =%s", pE->Value(),pE->GetText());
		}
	}


	jLIST_TYPEDEF_map(tstring , jxVar , g_map_jIVar) ;

#	define for_each_type_of_map_jIVar(X)\
	X(int)\
	X(float)\
	X(bool)\


#	define def_init_jIVar_func(TYPE)\
	void init_jIVar(tcstr szName, TYPE val)\
	{\
		fname_t name;\
		jt_strcpy(name, szName);\
		jxVar::GetTypeByTagName(name);\
		jxVar& v = g_map_jIVar[szName];\
		v.SetType(jIVar::ED##TYPE);\
		v.Set_##TYPE(val);\
	}\

	void init_jIVar(tcstr szName, tcstr val)
	{
		fname_t name;
		jt_strcpy(name, szName);
		jIVar::EElementType eType = jxVar::GetTypeByTagName(name);
		jxVar& v = g_map_jIVar[szName];
		v.SetType(eType);
		v.FromString(val);
	}


	for_each_type_of_map_jIVar(def_init_jIVar_func);
	

	jExcel_ConstVar::jExcel_ConstVar()
	{
#		define init_jIVar213(VAR, VAL, HELP) init_jIVar(#VAR,VAL);
		for_each_table_const_excel_enum(init_jIVar213);
	}

	void jExcel_ConstVar::print(tcstr szName)
	{
		jIVar* _pV = get(szName);
		jxVar* pV= (jxVar*)_pV;
		jvRETURN(pV, "%s not found", szName);
		fname_t buf;
		jLOG("%s = %s(%s)",szName, pV->ToString(buf),pV->GetTypeString());
	}

	void jExcel_ConstVar::print_all()
	{
#		define print_jIVar213(VAR, VAL, HELP) print(#VAR);
		for_each_table_const_excel_enum(print_jIVar213);

	}
	void jExcel_ConstVar::for_each(for_each_fn_t& func)
	{
		g_map_jIVar_it it = g_map_jIVar.begin(), ie = g_map_jIVar.end();
		for(;it!=ie;++it)
		{
			for_each_it_t arg = std::make_pair(it->first,&it->second);
			func(arg);
		}
	}

	jIVar* jExcel_ConstVar::get(cstr szName)
	{
		g_map_jIVar_it it = g_map_jIVar.find(szName);
		if(it==g_map_jIVar.end()) return 0;
		return &it->second;
	}

	//#--------------------------------------------------------------------------
	void update_from_xml(jTE* pE)
	//#--------------------------------------------------------------------------
	{
		fname_t name;
		jRETURN(pE);
		jt_strcpy(name , pE->Value());
		jIVar::EElementType eType = jxVar::GetTypeByTagName(name);
		tcstr szValue = pE->Value();
		jRETURN(szValue);
		g_map_jIVar_it it = g_map_jIVar.find(szValue);
		if(it!=g_map_jIVar.end())
		{
			tcstr szText = pE->GetText();
			jvRETURN(szText,"%s's value is not exist",name);
			it->second.FromString(szText);
			return;
		}
		szValue = pE->Value();
		jRETURN(szValue)
		jxVar v = g_map_jIVar[szValue];
		v.SetType(eType);
		cstr szText2 = pE->GetText();
		jRETURN(szText2);
		v.FromString(szText2);
	}
	
	TiXmlDocument g_DocECV;
	
	//#--------------------------------------------------------------------------
	void jExcel_ConstVar::load_xml(cstr szXml)
	//#--------------------------------------------------------------------------
	{
		if(!nOS::is_exist_file(CONSOLEVAR_XML_FILE))
		{

		}

		jRETURN(g_DocECV.LoadFile(CONSOLEVAR_XML_FILE) );
		jTE* pE= nXML::find(g_DocECV ,"baseball.ConsoleVar");
		
		bool isNeedSave=false;
		g_map_jIVar_it it = g_map_jIVar.begin(), ie = g_map_jIVar.end();
		for(;it!=ie;++it)
		{
			fname_t szNameBuf;
			it->second.GetTagNameByType(it->first.c_str(),szNameBuf);

			jTE* peFind = pE->FirstChildElement(it->first.c_str());
			if(peFind) continue;
			TiXmlElement* msg = new TiXmlElement(it->first.c_str()); 
			fname_t buf;
			msg->LinkEndChild( new TiXmlText( it->second.ToString(buf) )); 
			pE->LinkEndChild( msg );  
			isNeedSave=true;
		}
		if(isNeedSave)
		{
			g_DocECV.SaveFile(CONSOLEVAR_XML_FILE);
		}

		{
			nXML::for_each_ft func = update_from_xml;
			nXML::for_each(pE,func);
		}

#		define init_table_const6654(var,val,help) nGLOBAL::var=this->get(#var);
		for_each_table_const_excel_enum(init_table_const6654);

	}


	void jExcel_ConstVar::save_to_xml(tcstr szXml)
	{
		jTE* pE= nXML::find(g_DocECV ,"baseball.ConsoleVar");

		g_map_jIVar_it it = g_map_jIVar.begin(), ie = g_map_jIVar.end();
		for(;it!=ie;++it)
		{
			jTE* peFind = pE->FirstChildElement(it->first.c_str());
			jCONTINUE(peFind);
			fname_t szValue;
			it->second.ToString(szValue);
			TiXmlNode* peT = peFind->LastChild();
			jvCONTINUE(peT,"name = %s",it->first.c_str());
			TiXmlText* peText = peT->ToText();
			jvCONTINUE(peText,"name= %s",it->first.c_str());
			peText->SetValue(szValue);
		}
		g_DocECV.SaveFile(szXml);
	}

}//namespace nMech

namespace nGLOBAL
{
	TiXmlDocument g_DocApp;
	nMech::jExcel_ConstVar g_ECV;

#	define define_table_const6654(var,val,help) nMech::jIVar* var=0;
	for_each_table_const_excel_enum(define_table_const6654);

}//namespace nGLOBAL


namespace nBASE_BALL
{
#define jLAMDA_find_grade(X,Z) Z(level_t ,level)
	jLAMDA_find_if(find_grade,jTE*)
	{
		cstr szLevel = it->Attribute("i_MINMAX_PLAYER_LEVEL");
		jRETURN_ret(false,szLevel);
		level_t iMax = atoi(szLevel);
		return (iMax >= level);
	}
	jLAMDA_end();


	nEXCEL::EItemGradeType get_bonus_item_grade(level_t level)
	{
		static jTE* peRandomGiftPercent =  nXML::find(nGLOBAL::g_DocApp,"baseball.play_data.GAME_RESULT.RandomGiftPercent");
		jRETURN_ret(eIGT_E,peRandomGiftPercent);	

		nXML::find_if_ft func = find_grade(level);
		jTE* pE = nXML::find_if(peRandomGiftPercent, func);
		jRETURN_ret(eIGT_E,pE);

		EItemGradeType eGrade = nExcelUtil::FromString(pE->Value(), eBEGIN_EItemGradeType);
		jRETURN_ret(eIGT_E, nExcelUtil::IsValid(eGrade));
		return eGrade;
	}

	level_t get_player_level(exp_t exp)
	{
		Sys_PlayerLevel* p=0;
		for(int i=0; i< jCSV(Sys_PlayerLevel).size(); ++i)
		{
			p = jCSV(Sys_PlayerLevel).at(i);
			if(p->Get_max_exp() >= exp)
			{
				break;
			}
		}
		if(!p) return 1;
		return p->Get_level();
	}

#define jLAMDA_get_random_item_info(X,Z) X(vector<int>&,vecPercent) Z(vector<int>&,vecCount)
	jLAMDA_for_each(get_random_item_info,jTE*)
	{
		cstr sz = it->Attribute("i_COUNT");
		jRETURN(sz);
		vecCount.push_back(atoi(sz));
		cstr szPer = it->GetText();
		jRETURN(szPer);
		vecPercent.push_back(atoi(szPer));
	}
	jLAMDA_end();

	int get_bonus_item_count( cstr category )
	{
		jTE* peItemInfo = nXML::find(nG::g_DocApp, category);
		jRETURN_ret(-1,peItemInfo);
		vector<int> vecCount;
		vector<int> vecPercent;
		nXML::for_each_ft func= get_random_item_info(vecPercent,vecCount);
		nXML::for_each(peItemInfo , func);
		jvRETURN_ret(-1,vecPercent.size(), "%s",category);
		jvRETURN_ret(-1,vecPercent.size()==vecCount.size() , "%s",category);
		int selected = nMOB::random_by_percent_list(vecPercent);
		jvRETURN_ret(-1,selected<vecCount.size(), "%s",category);
		return vecCount[selected];
	}

	void calc_bonus_item_count(IN bool isWin, OUT int& iIC_STUFF , OUT int& iIC_CONSUME)
	{
		fname_t szXPath;
		sprintf(szXPath,"baseball.play_data.GAME_RESULT.PVP.%s.RewardItemCount.IC_STUFF", isWin?"WIN":"LOSE");
		iIC_STUFF = get_bonus_item_count(szXPath);
		sprintf(szXPath,"baseball.play_data.GAME_RESULT.PVP.%s.RewardItemCount.IC_CONSUME", isWin?"WIN":"LOSE");
		iIC_CONSUME = get_bonus_item_count(szXPath);
	}

}//namespace nBASE_BALL
