/* file : jIXmlUtil.h
Coder : by icandoit ( mech12@nate.com)
Date : 2006-12-14 17:15:57
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jIXmlUtil_header__
#define __jIXmlUtil_header__
#pragma once

namespace nMech
{
	namespace nXML
	{
#define jINTERFACE_jIXmlUtil(X) public:	\
	/* jIVar*의 컨텐츠로 부터 Doc로딩또는 찾아서 리턴.이때 jID*는 jIVar::GetUserData()에 저장됨 */\
	virtual jID*Var2Doc(jIVar* v) ##X \
	virtual void AdjustFileNameByDoc(tfname_t &szName , jIE* it)##X \
	virtual bool GetMacroString(cstr szIn , jIE* peMacro, TCHAR* szOut)##X \
	virtual int GetParentPath(jIE* pe , jvector<StringID>& out)##X \
	virtual int GetParentPath(jIE* pe , jvector<std::tstring>& out)##X \
	virtual void SetXPath(jIE* pePacket , jIE* pE, jIA* pA) ##X \
	virtual jID* GetXPath(jIE* pePacket, jIE**pE, jIA**pA) ##X \
	virtual bool LoadFromRegistry(jIE*,tcstr szRegPath,tcstr szRegName) ##X\
	virtual void SaveToRegistry(jIE* ,tcstr szRegPath,tcstr szRegName) ##X\
	\
	/* iParentDepth==-1 이면 peOverride로부터 루트를 제외한 부모로 부터 찾는다. 1이면 바로 윗부모만 찾고 0이면 peOverride에대해서만 찾는다*/\
	virtual jIVar* GetOverrideAttr(jIE* pE ,cstr szAttr,jIVar::EElementType eType , cstr szDefault,jIE* peOverride,int iParentDepth=-1) ##X\

		jINTERFACE_END(jIXmlUtil);

	}//nXML


}


#endif // __jIXmlUtil_header__
