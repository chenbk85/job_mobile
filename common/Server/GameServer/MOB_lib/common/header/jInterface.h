/* file : jInterface.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-07-24 16:54:55
comp.: jgame.co.kr
title : 
desc : 

*/

#ifndef __jInterface_headashweuihdsafkjer__
#define __jInterface_headashweuihdsafkjer__
#pragma once


namespace nMech
{
/* 
기본적인 사용법.

	struct test_interface
	{
#define jINTERFACE_test_interface(X)\
	virtual void asdf(int a) ##X \
	virtual float asdf1(int aa) ##X \

		jINTERFACE_ABSTRACT(test_interface);

	};

	class test_class : public test_interface
	{
	public:
		jINTERFACE_HEADER(test_interface);
	};

	void test_class::asdf(int a){}
	float test_class::asdf1(int ){ return 0;}

	test_class aaa;
*/

#ifndef jINTERFACE_ABSTRACT
#define jINTERFACE_ABSTRACT(class_name)				jINTERFACE_##class_name(=0;)
	// 상속받는 클래스의 내부에 사용
#define jINTERFACE_HEADER(class_name)					jINTERFACE_##class_name(;)
#endif



	// 인터페이스 선언부의 마지막에 사용.
#ifndef jINTERFACE_END
#define jINTERFACE_END( class_name)						struct class_name { jINTERFACE_ABSTRACT(class_name);	};
#endif

	// 상속받는 인터페이스 선언부의 마지막에 사용.
#ifndef jINTERFACE_END_BASE1
#define jINTERFACE_END_BASE1(interface_name, parent_class) struct interface_name : public parent_class \
	{ \
		jINTERFACE_ABSTRACT(interface_name);\
		typedef interface_name interface_t;\
		typedef parent_class parent_t;\
	};
#endif

	namespace nInterface
	{

		#define jINTERFACE_jIInterface(x) public:	\
			virtual tcstr GetName()  x \
			virtual void Release()  x \

		jINTERFACE_END(jIInterface);

		template<typename T>	struct AutoPtr
		{
		private:
			T* m_p;
		public:
			bool empty(){ return !m_p;}
			bool full(){ return !empty();}
			AutoPtr(T* p):m_p(p){}
			~AutoPtr()	{		if(full()){m_p->Release();	m_p=0 ;}	}
			T* operator->() const	{	return m_p;	}
			operator T*() const		{	return m_p;	}

		};
	}

}


#define jCREATE_INTERFACE(name) static_cast<name*>(nMech::g_jBase.CreateInterface(_T(#name)) );
#define jCREATE_INTERFACE_AUTO(var, name) nMech::nInterface::AutoPtr<name> var = jCREATE_INTERFACE(name);

//
#ifndef jCTOR_INTERFACE
#define jCTOR_INTERFACE(_Interface , _implement)\
	tcstr _implement::GetName(){ return _T(#_Interface);}\
	extern nMech::nInterface::jIInterface *_Get_##_implement();\
	jONCE_RUN(_implement##_once_run){nMech::jBase::Regist_InterfaceFactory(_T(#_Interface) , _Get_##_implement);}\
	nMech::nInterface::jIInterface *_Get_##_implement()
#endif

#ifndef jDTOR_INTERFACE
#define jDTOR_INTERFACE(_Interface , _implement)	void _implement::Release()
#endif


/*
사용 예.

		jCREATE_INTERFACE_AUTO(pReg, nMech::nUtil::jIRegistry);
		pReg->Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Perflib"));
		pReg->GetValue(_T("Last Counter"), &gLastIndex);
		pReg->Close();


< 인터페이스 해더의 정의>

		#define jINTERFACE_jISMTPClient(x) public:	\
		virtual BOOL		Connect( cstr ipAddress, cstr userName = 0,cstr password = 0, int portNo = SMTP_DEFAULT_PORT ) ##x \
		virtual BOOL		Disconnect() ##x \

		jINTERFACE_END_BASE1(jISMTPClient, nInterface::jIInterface);


< 인터페이스를 상속받는 법 >

		class SMTPClient : public jISMTPClient
		{
		public:
			jINTERFACE_HEADER(jIInterface);
			jINTERFACE_HEADER(jISMTPClient);



< 인터페이스 생성 예>

		jISMTPClient* pMail = jCREATE_INTERFACE(nMech::nUtil::nDebug::jISMTPClient);
		ret = pMail->Connect( "uniana2.uniana.com" );
		ret = pMail->MailFrom( "crash@uniana.com" );
		ret = pMail->MailTo( "icandoit@uniana.com" );
		ret = pMail->MailContents( "Crasher", "DontSendMe@sonicant.co.kr", "제목", "메일내용" );
		ret = pMail->MailAttachFile( "..\\log.txt" );
		ret = pMail->MailSubmit();
		pMail->Disconnect();
		SAFE_RELEASE(pMail);

*/

#endif // __jInterface_headashweuihdsafkjer__
