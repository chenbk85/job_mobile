#ifndef _FACTOR_H_
#define _FACTOR_H_

#include <string>

enum FACTOR_TYPE {
	CONST_VOID,	// �s��

	CONST_INT,	// �萔����
	CONST_STR,	// �萔������
	VAR_INT,	// �ϐ�����
	VAR_STR,	// �ϐ�������
};


class Factor {
	FACTOR_TYPE		m_factor_type;

	std::string		m_name;	// �ϐ��̏ꍇ�̖��O

	int				m_int_data;
	std::string		m_str_data;

public:
	Factor();					// �f�t�H���g�R���X�g���N�^
	Factor(FACTOR_TYPE type);	// �R���X�g���N�^
	Factor(const Factor& rhs);	// �R�s�[�R���X�g���N�^

	void SetType(FACTOR_TYPE type) { m_factor_type = type; }
	FACTOR_TYPE GetType() { return m_factor_type; }
	void SetInt(int i) { m_int_data = i; }
	int GetInt() { return m_int_data; }

	void SetName(std::string& name) { m_name = name; }
	std::string& GetName() { return m_name; }

	void SetStr(std::string& str) { m_str_data = str; }
	std::string& GetStr() { return m_str_data; }

	
	void Assign(const Factor& rhs);	// ��� �i�ϐ����͂��̂܂܁j

	// ���Z�q

	Factor& operator = (const Factor& rhs);	// �����o��S�ăR�s�[
	Factor operator ! ();

	Factor operator + (const Factor& rhs);
	Factor operator - (const Factor& rhs);
	Factor operator * (const Factor& rhs);
	Factor operator / (const Factor& rhs);
	Factor operator % (const Factor& rhs);

	Factor operator < (const Factor& rhs);
	Factor operator > (const Factor& rhs);
	Factor operator <= (const Factor& rhs);
	Factor operator >= (const Factor& rhs);
	Factor operator == (const Factor& rhs);
	Factor operator != (const Factor& rhs);

	// ����
	Factor operator && (const Factor& rhs);
	Factor operator || (const Factor& rhs);

};



#endif