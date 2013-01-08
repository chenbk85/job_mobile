/* file : jString.h
Coder : by icandoit ( mech12@nate.com)
Date : 2006-10-26 19:08:56
comp.: pantavision.co.kr
title : 
desc :  jXml���� ����� ��Ʈ��Ŭ���� . �������۰� yVector�޸�Ǯ���� Ȱ��.


*/

#ifndef __jString_headerASDF23KSDFIOEJFK__
#define __jString_headerASDF23KSDFIOEJFK__
#pragma once

#include "header/yVector.h"
#include <iostream>

using std::ostream;
using std::istream;


class JBASE_API jString : public ySimpleNode<jString>
{
	int m_iLen;
	char* m_str;
public:
	jDECLEAR_SIMPLE_MEMORY(jString);
	/* *_* by icandoit : 2006-10-26 19:09:28

	jString(const char* s=NULL);
	jString(const jString& s);
	~jString();
	jString& operator=(const jString& s);
	jString& operator+=(const jString& s);
	bool operator==(const jString& s);
	jString operator+(const jString& s);
	*/ //*_* by icandoit : 2006-10-26 19:09:33
	void Create()	{		Init();	}
	void Destroy()
	{
		m_iLen = 0;
		SAFE_DELETE_ARRAY(m_str);
	}
	void CopyFrom(const jString& s)
	{
		delete []m_str;                    // �޸��� ������ ���� ����?
		m_iLen=s.m_iLen;
		m_str=new char[m_iLen];
		strcpy(m_str, s.m_str);
	}

	void Init(cstr s = NULL)
	{
		m_iLen=(s!=NULL ? strlen(s)+1 : 1);
		m_str=new char[m_iLen];

		if(s!=NULL)
			strcpy(m_str, s);
	}

	char* c_str(){ return m_str;}
	int size(){ return m_iLen-1;}
	void resize(int i)
	{
		char* temp = new char[i];
		memset(temp , 0 , i);
		strcpy(temp,m_str);
		m_iLen=i;
		delete [] m_str;
		m_str = temp;
	}

	jString::jString(const char* s=NULL)	{		Init(s);	}
	jString::jString(const jString& s)
	{
		m_iLen=s.m_iLen;
		m_str=new char[m_iLen];
		strcpy(m_str, s.m_str);
	}

	jString::~jString()
	{
		m_iLen = 0;
		SAFE_DELETE_ARRAY(m_str);
	}
/* *_* by icandoit : 2006-10-26 20:03:30

	jString& jString::operator=(const jString& s)
	{
		delete []m_str;                    // �޸��� ������ ���� ����?
		m_iLen=s.m_iLen;
		m_str=new char[m_iLen];
		strcpy(m_str, s.m_str);
		return *this;                    // �������� ���� ������ ����ϱ� ����
	}

	jString jString::operator+(const jString& s)
	{
		char* tStr=new char[m_iLen+s.m_iLen-1];
		strcpy(tStr, m_str);      // ���ڿ� ����
		strcat(tStr, s.m_str);        // ���ڿ� �߰�
		jString temp(tStr);
		delete []tStr;
		return temp;
	}
	*/ //*_* by icandoit : 2006-10-26 20:03:33

	jString& jString::operator+=(const jString& s)
	{
		m_iLen=m_iLen+s.m_iLen-1;
		char* tStr=new char[m_iLen];
		strcpy(tStr, m_str);      // ���ڿ� ����
		delete []m_str;

		strcat(tStr, s.m_str);    //���ڿ� �߰�
		m_str=tStr;
		return *this;
	}

	bool jString::operator==(const jString& s)
	{
		return strcmp(m_str, s.m_str)? false:true;
	}


	friend ostream& operator<<(ostream& os, const jString& s);
	friend istream& operator>>(istream& is, jString& s);
};




#endif // __jString_headerASDF23KSDFIOEJFK__
