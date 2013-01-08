
#pragma warning(disable : 4761)
#include <iostream>
#include <stack>
#include <vector>
#include <list>
#include <cstdio>
#include <boost/spirit/core.hpp>
using namespace std;
using namespace boost::spirit;

namespace
{

vector<char> r_name;
void BeginName(char c)
{
	r_name.clear();
	r_name.push_back(c);
}
void MidName(char c)
{
	r_name.push_back(c);
}
void EndName(const char* const, const char* const)
{
	r_name.push_back('\0');
}
vector<char> r_string;
void BeginString(const char* const, const char* const)
{
	r_string.clear();
}
void AckString(char c)
{
	r_string.push_back(c);
}
void EndString(const char* const, const char* const)
{
	if(!r_string.empty())
	{
		r_string.pop_back();	
		r_string.push_back('\0');
	}
}
vector<char> r_description;
void BeginDescription(const char* const, const char* const)
{
	r_description.clear();
}
void AckDescription(char c)
{
	r_description.push_back(c);
}
void EndDescription(const char* const a, const char* const b)
{
	if(!r_description.empty())
	{
		r_description.pop_back();	
		r_description.push_back('\0');
	}
}


struct AttributeBuf { 
	string	m_key;
	string	m_data;
	AttributeBuf(const char* key, const char* data)
	{ m_key = key; m_data = data; } 
};
class NodeBuf { 
public:
	string				m_nodename;
	list<AttributeBuf>	m_attribute;
	void Clear();
	void SetNodeName(const char* name);
	void AddAttribute(const char* key, const char* data);
};
void NodeBuf::Clear()
{
	m_nodename = "";
	m_attribute.clear();
}
void NodeBuf::SetNodeName(const char* name)
{
	m_nodename = name;
}
void NodeBuf::AddAttribute(const char* key, const char* data)
{
	m_attribute.push_back(AttributeBuf(key, data));
}
NodeBuf	g_nodebuf;
void ClearBuf(const char* const, const char* const)
{
	g_nodebuf.Clear();
}
void SetNodeName(const char* const, const char* const)
{
	g_nodebuf.SetNodeName(&r_name[0]);
}
void AddAttribute(const char* const, const char* const)
{
	g_nodebuf.AddAttribute(&r_name[0], &r_string[0]);
}
void PushNode(const char* nodename);
void PopNode(const char* nodename);
void Attribute(const char* key, const char* data);
void PushBuf(const char* const, const char* const)
{
	PushNode(g_nodebuf.m_nodename.c_str());
	for(list<AttributeBuf>::iterator it = g_nodebuf.m_attribute.begin(); it != g_nodebuf.m_attribute.end(); ++it)
	{
		Attribute(it->m_key.c_str(), it->m_data.c_str());
	}
}
void PopBuf(const char* const, const char* const)
{
	PopNode(g_nodebuf.m_nodename.c_str());
}


int g_indent = 0;
void Indent()
{
	for(int i = 0; i < g_indent; i++)
		printf("    ");
}
void PushNode(const char* nodename)
{
	
	Indent();
	++g_indent;
	printf("PushNode    : <%s>\n", nodename);
}
void PopNode(const char* nodename)
{
	
	--g_indent;
	Indent();
	printf("PopNode     : </%s>\n", nodename);
}
void Attribute(const char* key, const char* data)
{
	
	Indent();
	printf("Attribute   : %s=\"%s\"\n", key, data);
}
void Description(const char* const, const char* const)
{
	
	Indent();
	printf("Description : \"%s\"\n", &r_description[0]);
}



struct xml_parser : public grammar<xml_parser> {
	template<typename S> struct definition {
		rule<S> s, name_r, string_r, desc_r;
		rule<S> attribute, description;
		rule<S> stag, etag, emptyelem, content, comment, element;
		rule<S> xml;
		definition(const xml_parser& self)
		{
			s			= +space_p;

			string_r	= '\"' >> eps_p[&BeginString] 
						>> *(anychar_p[&AckString] - '\"') 
						>> '\"' >> eps_p[&EndString];

			name_r		= (alpha_p[&BeginName] | ch_p('_')[&BeginName]) 
						>> *( (alnum_p[&MidName] | ch_p('_')[&MidName]) ) 
						>> eps_p[&EndName];

			desc_r		= eps_p[&BeginDescription] 
						>> +(anychar_p[&AckDescription] - '<') 
						>> eps_p[&EndDescription];

			attribute	= name_r >> '=' >> string_r 
						>> eps_p[&AddAttribute];

			description = desc_r[&Description];

			stag		= '<' >> eps_p[&ClearBuf] 
						>> name_r[&SetNodeName] >> *(s >> attribute) 
						>> '>' >> eps_p[&PushBuf];

			etag		= "</" >> eps_p[&ClearBuf] 
						>> name_r[&SetNodeName] 
						>> '>' >> eps_p[&PopBuf];

			emptyelem	= '<' >> eps_p[&ClearBuf] 
						>> name_r[&SetNodeName] >> *(s >> attribute) 
						>> "/>" >> eps_p[&PushBuf] >> eps_p[&PopBuf];

			comment		= "<!--" >> *(anychar_p - "-->") >> "-->";

			content		= element | description;

			element		= comment | emptyelem | (stag >> *content >> etag);

			xml			= *space_p >> *element >> *space_p;

		}
		
		const rule<S>& start() const { return xml; }	
	};
};
}

#include <boost/filesystem/operations.hpp>

int main_spirit_XML()
{
	boost::filesystem::path foo(boost::filesystem::initial_path() / "../jTest/test.xml" );
	string str1 = foo.normalize().native_directory_string();

    string str;
	FILE* fp = fopen(str1.c_str(), "r");
	if(!fp) return -1;
	char str2[2048];
	while(NULL != fgets(str2, 2048, fp))
	{
		str += str2;
	}
	fclose(fp);

	{
		xml_parser xmlp;
		parse_info<> r = parse(str.c_str(), xmlp);
		if(r.full)	
			cout << "ok" << endl;
		else	
			cout << "error" << endl;
	}
	return 0;
}
