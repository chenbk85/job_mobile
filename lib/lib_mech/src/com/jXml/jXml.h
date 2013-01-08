/* file : jXml.h
Coder : by icandoit (mech12@nate.com)
Date : 2005-06-08 00:08:28
title : 
desc : 

� �̰� ������ϸ� ã�ƿ� ȣ���ߴ�.
"���� �ϴ� �ϸ��� ����� �Ǵ� ���� ������ �� ���� �����Դϱ�?"
"�װ��� �ʰ� ������ ��Ǯ�� �ʾұ� �����̴϶�."
"���� �ƹ��͵� ���� �� ���� �����͸��Դϴ�."
"�׷��� �ʴ��϶�. ����� ������ ������ �� �� �ִ� �ϰ� ������ �������Գ� �ִ� ���̴�. 

ù°�� ȭ�Ƚ� �� �󱼿� ȭ���� ��� �ε巴�� ���ٿ� �󱼷� ���� ���ϴ°��̿�. 
��°�� ��÷μ� ���� �󸶵��� ��Ǯ�� ������ ����� ��, Ī���� ��, ������ ��, �ݷ��� ��, �纸�� ��, �ε巯�� ������ ���ϴ� ���̴�. 
��°�� �ɽ÷μ� ������ ���� ���� ������ ������ �ִ°��̰� 
��°�� �Ƚ� �� ȣ�Ǹ� ���� ������ ����� ���� ��ó�� ������ ��Ǫ�� ���̴�. 
�ټ�°�� �Ž�, �� ������ ���ϴ� �����μ� ���� ���� ��� �شٰų� ���� ���� ���̿�. 
����°�� �½÷� ���� ��ҿ� �°� �ڸ��� ���־� �纸�ϴ°��̰� 
�ϰ�°�� ���÷� ���� ���� �ʰ� ����� ������ ��Ʒ� �˾Ƽ� ���� �ִ� ���̴�. 

�װ� �� �ϰ������� ���Ͽ� ������ ������ �ʿ��� ����� ���� ���̴϶�.

*/

#ifndef __jXml_header__
#define __jXml_header__
#pragma once


#ifdef JXML_EXPORTS
#define JXML_API __declspec(dllexport)
#else
#define JXML_API __declspec(dllimport)
#endif

#include "interface/xml/jIXml.h"
#include "header\\m_Manager.h"
#include "jxDocument.h"
#include "interface/xml/jIXmlCallBackManager.h"
#include <boost/any.hpp>
namespace nMech
{
	namespace nXML
	{
		class jXmlCallBackManager : public jIXmlCallBackManager
		{
		private:
			jLIST_TYPEDEF_map(std::tstring, jXml_Callback_ft, m_jXml_Callback);
		public:
			virtual void SetCallback(cstr, jXml_Callback_ft);
			virtual void RunCallBack(cstr sz , boost::any a);
		};


		//----------------------------------------------------------------
		class  jXml : public jIXml
			//----------------------------------------------------------------
		{
			jINTERFACE_HEADER(jIXml);

			jIXml_Param m_Param;
		public:
			jLIST_TYPEDEF_map(std::tstring, jxD, m_DocList);

			int m_iFlag;
			jFLAG_ENUM(eUSE_TINY_XML);


			jXml() : m_iFlag(0)
			{
			}

			~jXml();

			jxD* Insert(tcstr key); // �ش��̸����� ������Ʈ�� ����ϰ� �ּҸ� ����.

			void SetAutoLoad(bool is);
			bool GetAutoLoad();
			void jTestUnit_xmllid();
			void Release();
		};

		extern jXml* g_pXml;

	}
}

#endif // __jXml_header__
