#include "INIFile.h"

using namespace std;
using namespace boost;

///////////////////////////////////////////////////////////////////////////

INISection::~INISection()
{
}

void INISection::AddKey(const char* key, any& data)
{
	m_keys.insert(make_pair(static_cast<string>(key), data));
}

any* INISection::GetData(const char* key)
{
	map<string, any>::iterator it = m_keys.find(key);

	if(it != m_keys.end())
		return &(it->second);
	else
		return NULL;
}

///////////////////////////////////////////////////////////////////////////


INIFile::~INIFile()
{
}

void INIFile::AddKey(const char* section, const char* key, boost::any& data)
{
	map<string, INISection*>::iterator it = m_sections.find(section);
	if(it != m_sections.end())
	{
		it->second->AddKey(key, data);
	}
	else
	{
		INISection* psec = new INISection;
		psec->AddKey(key, data);
		m_sections.insert(make_pair(static_cast<string>(section), psec));
	}
}

int INIFile::GetInt(const char* section, const char* key)
{
	map<string, INISection*>::iterator it = m_sections.find(section);
	if(it != m_sections.end())
	{
		any* pany = it->second->GetData(key);

		if(pany)
		{
			return any_cast<int>(*pany);
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

bool INIFile::GetString(const char* section, const char* key, char* dest)
{
	map<string, INISection*>::iterator it = m_sections.find(section);
	if(it != m_sections.end())
	{
		any* pany = it->second->GetData(key);

		if(pany)
		{
			strcpy(dest, any_cast<string>(*pany).c_str());

			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

