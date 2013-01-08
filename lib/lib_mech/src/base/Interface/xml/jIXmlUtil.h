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
	/* jIVar*�� �������� ���� Doc�ε��Ǵ� ã�Ƽ� ����.�̶� jID*�� jIVar::GetUserData()�� ����� */\
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
	/* iParentDepth==-1 �̸� peOverride�κ��� ��Ʈ�� ������ �θ�� ���� ã�´�. 1�̸� �ٷ� ���θ� ã�� 0�̸� peOverride�����ؼ��� ã�´�*/\
	virtual jIVar* GetOverrideAttr(jIE* pE ,cstr szAttr,jIVar::EElementType eType , cstr szDefault,jIE* peOverride,int iParentDepth=-1) ##X\

		jINTERFACE_END(jIXmlUtil);

	}//nXML


}


#endif // __jIXmlUtil_header__
