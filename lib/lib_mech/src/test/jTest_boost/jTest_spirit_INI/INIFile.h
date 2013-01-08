//================================================================
//	ini のデータを保持するクラス
//================================================================
#ifndef _INIFILE_H_
#define _INIFILE_H_

#include <string>
#include <map>
#include <boost/any.hpp>


class INISection { 
	std::map<std::string, boost::any>	m_keys;

public:
	~INISection();

	void AddKey(const char* key, boost::any& data);
	boost::any* GetData(const char* key);
};




class INIFile { 
	std::map<std::string, INISection*>	m_sections;

public:
	~INIFile();

	void AddKey(const char* section, const char* key, boost::any& data);

	int GetInt(const char* section, const char* key);
	bool GetString(const char* section, const char* key, char* dest);
};


#endif