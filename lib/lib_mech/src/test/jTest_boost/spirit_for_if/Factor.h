#ifndef _FACTOR_H_
#define _FACTOR_H_

#include <string>

enum FACTOR_TYPE {
	CONST_VOID,	// 不定

	CONST_INT,	// 定数整数
	CONST_STR,	// 定数文字列
	VAR_INT,	// 変数整数
	VAR_STR,	// 変数文字列
};


class Factor {
	FACTOR_TYPE		m_factor_type;

	std::string		m_name;	// 変数の場合の名前

	int				m_int_data;
	std::string		m_str_data;

public:
	Factor();					// デフォルトコンストラクタ
	Factor(FACTOR_TYPE type);	// コンストラクタ
	Factor(const Factor& rhs);	// コピーコンストラクタ

	void SetType(FACTOR_TYPE type) { m_factor_type = type; }
	FACTOR_TYPE GetType() { return m_factor_type; }
	void SetInt(int i) { m_int_data = i; }
	int GetInt() { return m_int_data; }

	void SetName(std::string& name) { m_name = name; }
	std::string& GetName() { return m_name; }

	void SetStr(std::string& str) { m_str_data = str; }
	std::string& GetStr() { return m_str_data; }

	
	void Assign(const Factor& rhs);	// 代入 （変数名はそのまま）

	// 演算子

	Factor& operator = (const Factor& rhs);	// メンバを全てコピー
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

	// 注意
	Factor operator && (const Factor& rhs);
	Factor operator || (const Factor& rhs);

};



#endif