/* file : nBASE_BALL.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-04-25 15:19:06
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __nBASE_BALL_header__
#define __nBASE_BALL_header__
#pragma once

#include "common/header/jHeader.h"
#include "common/header/jBoost.h"
#include <tinyxml/tinyxml.h>
#include "interface/jIVar.h"
#include "excel/code/table_const_excel_enum.h"
#include "excel/db_type.h"
#include "excel/excel_all.h"

// #include "excel/code/excel_baseball_table_db.ph.h"

typedef TiXmlElement jTE;
typedef TiXmlDocument jTD;


#define CONSOLEVAR_XML_FILE "../etc/xml/baseball_ConsoleVar.xml"
#define CONSOLEVAR_XML_FILE_DEFAULT "../etc/xml/baseball_ConsoleVar_default.xml"
namespace nMech
{
	namespace nXML
	{
		namespace nFunctor
		{
#			define jLAMDA_get_child(X,Z) Z(vector<jTE*>&,vec)
			jLAMDA_for_each(get_child,jTE*)
			{
				vec.push_back(it);
			}jLAMDA_end();
		}

		/// @brief :doc에 대해 szPath로 찾은후 해당 노드 리턴.
		/// @param szPath예 "NODE1.NODE2.NODE3"
		//jTE* find(jTE* pE, tcstr szPath);
		jTE* find(jTD& doc, tcstr szPath);
		//inline jTE* find(jTD& doc, tcstr szPath){return find(doc.RootElement(), szPath);}

		/// @brief pE의 자식들에 대해 func수행.
		typedef boost::function<void(jTE*)> for_each_ft;
		void for_each(jTE* peParent,  for_each_ft& func);

		typedef boost::function<bool(jTE*)> find_if_ft;
		jTE* find_if(jTE* peParent, find_if_ft& func);

	}
	namespace nX=nXML;

	struct jExcel_ConstVar
	{
		jExcel_ConstVar();
		void	print_all();
		void	print(tcstr szName);
		jIVar*	get(cstr szName);
		void	load_xml();

		typedef std::pair<tstring,jIVar*> for_each_it_t;
		typedef boost::function<void (for_each_it_t)> for_each_fn_t;
		void	for_each(for_each_fn_t&);
		void	save_to_xml(tcstr);
	};

	struct jIVar;
}//namespace nMech


namespace nGLOBAL
{
	extern TiXmlDocument g_DocApp;
	extern nMech::jExcel_ConstVar g_ECV;

#	define declare_table_const6654(var,val,help) extern nMech::jIVar* var;
	for_each_table_const_excel_enum(declare_table_const6654);

}//namespace nGLOBAL

namespace nG = nGLOBAL;


namespace nBASE_BALL
{
	level_t get_player_level(exp_t exp);
	elo_point_t calc_elo_K(elo_point_t curr_Ra);
	
}//namespace nBASE_BALL


#endif // __nBASE_BALL_header__
