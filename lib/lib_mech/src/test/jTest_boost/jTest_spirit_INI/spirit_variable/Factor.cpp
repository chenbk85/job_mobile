#include "Factor.h"
#include <stdio.h>

// デフォルトコンストラクタ
Factor::Factor() 
#ifdef _DEBUG
	: m_factor_type(CONST_VOID), m_name("NoName"), m_int_data(0xdddddddd), m_str_data("NoStr")
#else
	: m_factor_type(CONST_VOID)
#endif
{
}


// コンストラクタ
Factor::Factor(FACTOR_TYPE type) 
#ifdef _DEBUG
	: m_factor_type(type), m_name("NoName"), m_int_data(0xdddddddd), m_str_data("NoStr")
#else
	: m_factor_type(type)
#endif
{
}

// コピーコンストラクタ
Factor::Factor(const Factor& rhs) 
	: m_factor_type(rhs.m_factor_type), m_name(rhs.m_name), m_int_data(rhs.m_int_data), m_str_data(rhs.m_str_data) 
{
}


// 代入
void Factor::Assign(const Factor& rhs)
{
	if(this == &rhs) return;

	switch(rhs.m_factor_type)
	{
	case CONST_INT:
	case VAR_INT:
		m_factor_type = VAR_INT;
		m_int_data = rhs.m_int_data;
		break;
	case CONST_STR:
	case VAR_STR:
		m_factor_type = VAR_STR;
		m_str_data = rhs.m_str_data;
		break;
	default:
		printf("Factor::Assign error\n");
	}
}

// 演算子

Factor& Factor::operator = (const Factor& rhs)
{
	if(this == &rhs) return *this;

	m_factor_type = rhs.m_factor_type;
	m_name = rhs.m_name;
	m_int_data = rhs.m_int_data;
	m_str_data = rhs.m_str_data;
		
	return *this;
}

Factor Factor::operator ! ()
{
	Factor f(CONST_INT);
	f.SetInt(!m_int_data);
	return f;
}

Factor Factor::operator + (const Factor& rhs)
{
	Factor f;
	if(CONST_INT == m_factor_type || VAR_INT == m_factor_type)
	{
		f.SetType(CONST_INT);
		f.SetInt(m_int_data + rhs.m_int_data);
	}
	else
	{
		f.SetType(VAR_INT);
		f.SetStr(m_str_data + rhs.m_str_data);
	}
	return f;
}

Factor Factor::operator - (const Factor& rhs)
{
	Factor f(CONST_INT);
	f.SetInt(m_int_data - rhs.m_int_data);
	return f;
}

Factor Factor::operator * (const Factor& rhs)
{
	Factor f(CONST_INT);
	f.SetInt(m_int_data * rhs.m_int_data);
	return f;
}

Factor Factor::operator / (const Factor& rhs)
{
	Factor f(CONST_INT);
	f.SetInt(m_int_data / rhs.m_int_data);
	return f;
}

Factor Factor::operator % (const Factor& rhs)
{
	Factor f(CONST_INT);
	f.SetInt(m_int_data % rhs.m_int_data);
	return f;
}


Factor Factor::operator < (const Factor& rhs)
{
	Factor f(CONST_INT);
	f.SetInt(m_int_data < rhs.m_int_data);
	return f;
}

Factor Factor::operator > (const Factor& rhs)
{
	Factor f(CONST_INT);
	f.SetInt(m_int_data > rhs.m_int_data);
	return f;
}

Factor Factor::operator <= (const Factor& rhs)
{
	Factor f(CONST_INT);
	f.SetInt(m_int_data <= rhs.m_int_data);
	return f;
}

Factor Factor::operator >= (const Factor& rhs)
{
	Factor f(CONST_INT);
	f.SetInt(m_int_data >= rhs.m_int_data);
	return f;
}

Factor Factor::operator == (const Factor& rhs)
{
	Factor f;
	if(CONST_INT == m_factor_type || VAR_INT == m_factor_type)
	{
		f.SetType(CONST_INT);
		f.SetInt(m_int_data == rhs.m_int_data);
	}
	else
	{
		f.SetType(VAR_INT);
		f.SetInt(m_str_data == rhs.m_str_data);
	}
	return f;
}

Factor Factor::operator != (const Factor& rhs)
{
	Factor f;
	if(CONST_INT == m_factor_type || VAR_INT == m_factor_type)
	{
		f.SetType(CONST_INT);
		f.SetInt(m_int_data != rhs.m_int_data);
	}
	else
	{
		f.SetType(VAR_INT);
		f.SetInt(m_str_data != rhs.m_str_data);
	}
	return f;
}


Factor Factor::operator && (const Factor& rhs)
{
	Factor f(CONST_INT);
	f.SetInt(m_int_data && rhs.m_int_data);
	return f;
}

Factor Factor::operator || (const Factor& rhs)
{
	Factor f(CONST_INT);
	f.SetInt(m_int_data || rhs.m_int_data);
	return f;
}


