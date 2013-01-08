/* file : jScriptLua_Util.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-02-04 00:29:54
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jScriptLua_Util_header__
#define __jScriptLua_Util_header__
#pragma once

namespace nMech
{
	namespace nLUA
	{
		namespace jLuaUtil
		{
			jVec3 Get_jVec3(IFunctionHandler *pH, int nArg, CScriptObjectVector& oVec)
			{
				if(!pH->GetParam(nArg,*oVec))	throw "Get_jVec3(oVec) arg error";
				return oVec.Get();
			}
			jVec3 Get_jVec3(IFunctionHandler *pH, int nArg)
			{
				CScriptObjectVector oVec(nInterface::g_pIScriptSystem,true);
				if(!pH->GetParam(nArg ,*oVec)) throw "Get_jVec3() arg error";
				return oVec.Get();
			}
			//--------------------------------------------------------------------------
			jIE* Get_jIE(IFunctionHandler *pH,int iArg)
				//--------------------------------------------------------------------------
			{
				int nCookie;
				jIE* pE;
				pH->GetParamUDVal(iArg ,(INT_PTR &)pE,nCookie);		//AMD Port
				if(!pE) throw "인자에러";
				if(nCookie== jx(USER_DATA_jID))
				{
					pE = ((jID*)pE)->BaseI();
				}
				else if(nCookie==jx(USER_DATA_jIE))
				{
				}
				else
				{
					static fname_t buf;
					sprintf( buf, "%d 번째인자가 jID , jIE 가 아님", iArg);
					throw buf;
				}
				return pE;
			}
		};

#define JLUA_CATCH( func ) \
	catch (cstr szError)\
		{\
		nInterface::g_pIScriptSystem->RaiseError(  #func  " : %s" ,szError);\
		return pH->EndFunction();\
		}\
		catch (std::string szError)\
		{\
		nInterface::g_pIScriptSystem->RaiseError(  #func  " : %s" ,szError.c_str() );\
		return pH->EndFunction();\
		}\
		catch(bool)\
		{\
		}\
		catch(...)\
		{\
		nInterface::g_pIScriptSystem->RaiseError(  #func);\
		}\
		return pH->EndFunction();

	}//nLUA_Sink
}//nMech



#endif // __jScriptLua_Util_header__
