/* file : jIConsoleVar.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-01-29 17:59:46
comp.: www.actoz.com
title : 
desc : 

FILE:z:\server\src\core\jCommon\Interface\jIConsoleVar.txt

*/

#ifndef _jICONSOLE_VA232eioweuroiwdk2378R_H_
#define _jICONSOLE_VA232eioweuroiwdk2378R_H_


namespace nMech
{
	namespace nCONSOLE
	{

		//--------------------------------------------------------------------------
		//�ֹܼٿ��� �����ϴ� �ڷ���
#define for_each_jIConsoleVar_type(_ENUM)\
	_ENUM(int)\
	_ENUM(float)\
	_ENUM(tcstr)

		//--------------------------------------------------------------------------
#define for_each_EConsoleVarType(X)\
	\
	X(eDONT_SAVE2FILE , jBIT_0)\
	/* �ܼ�XML�� �ֺܼ��� ������ ������� �ʴ´�.\
		INI���Ϸ� ���� �ε��� �ֺܼ������� ���÷��׸� ����Ͽ� �ܼ�XML���Ͽ� ������� �ʴ´�. */\
		\
		X(eCPP_ONLY_DEFINE, jBIT_1)\
		/*�� �ֺܼ����� CPP��⿡���� ���ǵǸ� �ʱⰪ�� ���õ�. \
		�ܼ�XML���� ���� �����ص� �ε��� �������� �ȵ�.\
		�ܼ�XML���� ���� ���� ����ϱ� ���� ����Ǵ°���.*/\
		\
		X(eFROM_DEFINED_INI,jBIT_2)\
		/* ini���Ϸ� ���� ������ ����. �⺻������ read only����Ÿ�̴�.\
		������ ���� ini�� ���� �� ������ ������ ���������� �������� ���ڷ� ���� �����*/\
		X(eRUNTIME_READ_ONLY,jBIT_2)\
		/* ��Ÿ�ӿ����� �����Ұ�. INI, XML���� �ε��� �ȴ�.*/\


		enum EConsoleVarType
		{
#define jGEN_ENUM12(VAR,INIT) VAR = INIT,
			for_each_EConsoleVarType(jGEN_ENUM12)
		};


		//ó�� �ε��� �ܼ� xml ���Ͽ��� �ֺܼ������� �ε����� �ʾƾ� �ϴ��� üũ.
		inline bool is_does_not_load_console_xml(int iFlag)
		{
			return ((iFlag & eFROM_DEFINED_INI) || (iFlag & eCPP_ONLY_DEFINE) || (iFlag & eDONT_SAVE2FILE) );
		}

		// �ֺܼ��������� ���Ϸ� �����Ҷ� �ش� ������ �������� �ʴ��� üũ
		inline bool is_save_to_console_xml(int iFlag)
		{
			return (iFlag & eDONT_SAVE2FILE);
		}


#define jINTERFACE_jIConsoleVar(X) public:	\
	virtual void Init(jID* pDocApp) ##X /* jMech_Init()���� ȣ��� */ \
	virtual void Release() ##X \
	/* Console������ ����ִ� xml������ �Ѱ���(jConsoleVar.xml) */\
	virtual jID *GetDoc() ##X \
	\
	/* szCategory=0�̸� �����ϸ� <DEFAULT>ī�װ��� ������, \
		nFlags�� EConsoleVarType �� ���� �ü� �ִ�*/\
		virtual jIVar *CreateVar(tcstr szCategory,tcstr sName,tcstr sValue	,int nFlags, tcstr help = _T("") )##X \
		/*virtual jIVar *CreateVar(tcstr szCategory,tcstr sName,bool iValue		,int nFlags, tcstr help = _T(""))##X */\
		virtual jIVar *CreateVar(tcstr szCategory,tcstr sName,int iValue		,int nFlags, tcstr help = _T(""))##X \
		virtual jIVar *CreateVar(tcstr szCategory,tcstr sName,float fValue	,int nFlags, tcstr help = _T(""))##X \
		\
		/* noCase == true�̸� ��ҹ��� ���о��ϰ� ã�´�. */\
		virtual jIVar* GetVar( tcstr szCategory,tcstr name,bool noCase=false)##X \
		\
		/*! Execute a string in the console*/	\
		virtual bool ParseCmd(tcstr szCmd) ##X \
		virtual tcstr AutoComplete( tcstr  substr ) ##X \
		virtual tcstr	AutoCompletePrev( tcstr  substr ) ##X \
		virtual tcstr ProcessCompletion( tcstr szInputBuffer ) ##X \
		virtual void ResetAutoCompletion()##X \
		virtual int GetFlag(jIE* var)##X \
		virtual void SetFlag(jIE* var, int iFlag)##X \
		\
		/* ���ϸ��� �������������� xml\user\[app_nic_name]_[username].xml�� ����ȴ�.\
		���� szFile�� ���� Ȯ���ڴ� xml �Ǵ� jxml�� �ڵ����� �ٴ´�.\
		[exe][USE_JXML]�� ���� true�̸� jxml�� �����
		*/\
		virtual void SaveToFile(cstr szFile=0) ##X \

		jINTERFACE_END(jIConsoleVar);
		jSINGTON_INTERFACE_HEADER(JBASE_API , jIConsoleVar);

	}//namespace nCONSOLE
}

#define jGV(category, name) nMech::nCONSOLE::Get_jIConsoleVar()->GetVar(_T(#category),_T(#name))
#define jCV(category, name, value, flag, help) \
	nMech::nCONSOLE::Get_jIConsoleVar()->CreateVar(_T(#category),_T(#name),value,flag,_T(help))
#define jCV1(category, name, value, flag, help) \
	nMech::nCONSOLE::Get_jIConsoleVar()->CreateVar(category,_T(#name),value,flag,_T(help))

#define jCV_DECLARE(cate,var, val, flag,help)	extern jIVar* pv_##var;
#define jCV_DEFINE(cate,var, val, flag,help)	jIVar* pv_##var  = jCV(cate,var, val,flag,help);

#endif //_jICONSOLE_VA232eioweuroiwdk2378R_H_
