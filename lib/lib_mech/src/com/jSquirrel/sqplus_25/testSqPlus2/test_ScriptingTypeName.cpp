/* file : test_ScriptingTypeName.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-20 18:50:13
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"


// === BEGIN from a forum post by jkleinecke. 8/23/06 jcs ===

namespace Scripting 
{
	//--------------------------------------------------------------------------
	class ScriptEntity 
	//--------------------------------------------------------------------------
	{
	public:
		ScriptEntity() 
		{
			Bind();
		}
		static void Bind() 
		{
			SqPlus::SQClassDef<ScriptEntity>(_T("ScriptEntity")).
				var(&ScriptEntity::m_strName,_T("name"));
		} // Bind
		
		SqPlus::ScriptStringVar64 m_strName;
	};
}//namespace Scripting 

DECLARE_INSTANCE_TYPE_NAME(Scripting::ScriptEntity,ScriptEntity)

//--------------------------------------------------------------------------
void testScriptingTypeName(void) 
//--------------------------------------------------------------------------
{
	Scripting::ScriptEntity entity ;
	try 
	{
		SqPlus::BindVariable(&entity,_T("instance"));
		SquirrelObject sqObj = SquirrelVM::CompileBuffer(_T("\
											instance.name = \"Testing an instance variable bind: member assignment.\";\
											print(instance.name); \
											print(instance.name.len())"
		));
		SquirrelVM::RunScript(sqObj);
		scprintf(_T("\n len = %d"), scstrlen(entity.m_strName));


		/* Ãâ·Â

		Testing an instance variable bind: member assignment.
		53

		len = 53
		*/
	
	} // try
	catch (SquirrelError e) 
	{
		scprintf(_T("testScriptingTypeName: %s\n"),e.desc);
	} // catch
}

// === END from a forum post by jkleinecke. 8/23/06 jcs ===

