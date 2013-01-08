/* 
	filename:	juExeEnv.h
	coder	:	Cho Wook Rea (mech12@dreamwiz.com)(icq:74456993) 
	comp.	:	EmailPet 
	compiler:	vc++ 6.0
	date	:	2001-07-09���� 3:56:09
	title	:	
*/


// juExeEnv.h: interface for the juExeEnv class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JUEXEENV_H__AD04DFE3_8747_4F66_9755_30AF9B1777DF__INCLUDED_)
#define AFX_JUEXEENV_H__AD04DFE3_8747_4F66_9755_30AF9B1777DF__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
namespace nMech
{
	namespace nScript
	{
		struct jIINI_File;
	}

	typedef void *HMEMORYMODULE;
	struct jIMemoryDLL
	{
		virtual void ReadDB(tcstr szPath)=0; //db file load & init
		virtual void Close()=0; // ������ ����.
		virtual void WriteDB(tcstr szPath)=0; // db file write to GetDBName();
		virtual HMEMORYMODULE _LoadLibrary(acstr szDLL)=0;
		virtual FARPROC GetProcAddress(HMEMORYMODULE hDLL,acstr szFunc)=0;
	};

	//****************************************************************
	class JBASE_API juExeEnv  
		//****************************************************************
	{
	private:
		void __init();
	private:
#pragma warning(disable : 4251)
		jLIST_TYPEDEF_map(std::tstring,std::tstring,m_ArgList);
#pragma warning(default : 4251)
		jIMemoryDLL* m_jIMemoryDLL;
		nScript::jIINI_File* m_pINI_File;
	public:
		size_t GetArgCnt(){ return m_ArgList.size();}
		tcstr GetArg(tcstr sz);

		jIMemoryDLL* Get_DLL(){ return m_jIMemoryDLL;}
		nScript::jIINI_File* Get_INI(){ return m_pINI_File;}

#define jExeEnv_MEMBER(_N)\
	_N(path_t,m_szRunStartTime,_T(""),"")\
	\
	_N(path_t,m_szExeName,_T(""),"���ҽ� ��Ʈ ���� \ �� �ٴ´�")\
	_N(path_t,m_szStartDir,_T(""),"����������ġ ���� \ �� �ٴ´�")\
	_N(path_t,m_szModuleDir,_T(""),"�������� ��ġ ���� \ �� �ٴ´�")\
	_N(tfname_t,m_szVersion,_T(""),"��������")\
	_N(tfname_t,m_szAppNic,_T(""),"���������� ���� �г���-��ǻ�Ϳ��� ���μ��� �ĺ��ڷ� ���")\
	_N(tfname_t,m_szUserName,_T(""),"��ǻ�� ������")\
	_N(tfname_t,m_szComputerName,_T(""),"��ǻ�͸�")\
	_N(tfname_t,m_szIP,_T(""),"��ǥ ip")\
	_N(bool , m_isCreateUserSettingXML , false , "ó�� ����� ���� ���� ���� xml������ ����� ���θ���")\
	_N(bool , m_is_dont_save_file, false , "true�̸� app.xml ,ini, user.xml���� ���� ���� �ʴ´�")\

		jExeEnv_MEMBER(jDECL_VAR);

		tfname_t m_szDefaultLocale;
		jID* m_pDocLanguge;

		juExeEnv();
		cstr GetUserFilePath();
		cstr GetUserXmlFileName(fname_t buf);
	};

	extern  JBASE_API  juExeEnv  g_ExeEnv;


}
#endif // !defined(AFX_JUEXEENV_H__AD04DFE3_8747_4F66_9755_30AF9B1777DF__INCLUDED_)
