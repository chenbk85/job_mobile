#include "Executable.h"
#include "comment_parser.h"
#include <boost/spirit/core.hpp>

#include "EvalExpression.h"

using namespace std;
using namespace boost::spirit;

//=============================================================================

EvalExpression g_ee;

void Sentence::Exec()
{
	// debug
	cout << m_sentence << endl;

	g_ee.Eval(m_sentence);
}

void IfSentence::Exec()
{
	// debug
	cout << m_condition << endl;

	if(g_ee.Eval(m_condition))
	{
		Executable nested_exe(m_body);
		nested_exe.Exec();
	}
}

void ForSentence::Exec()
{
	for(cout << m_init << endl, g_ee.Eval(m_init);
		cout << m_condition << endl, g_ee.Eval(m_condition);
		cout << m_step << endl, g_ee.Eval(m_step) )
	{
		Executable nested_exe(m_body);
		nested_exe.Exec();
	}
}

//=============================================================================


//-------------------------------------------------------------

std::vector<SentenceBase*>* g_psentence_array = NULL;

//-------------------------------------------------------------
//	sentence
//-------------------------------------------------------------

vector<char>	g_sentence;

void BeginSentence(const char* const, const char* const)
{
	g_sentence.clear();
}

void AckSentence(const char c)
{
	g_sentence.push_back(c);
}

void EndSentence(const char* const, const char* const)
{
	if(!g_sentence.empty())
		g_sentence.pop_back();

	g_sentence.push_back('\0');

	g_psentence_array->push_back(new Sentence(&g_sentence[0]));
}

//-------------------------------------------------------------------
//	if
//-------------------------------------------------------------

vector<char>	g_if_condition;

void BeginIfCondition(const char* const, const char* const)
{
	g_if_condition.clear();
}

void AckIfCondition(const char c)
{
	g_if_condition.push_back(c);
}

void EndIfCondition(const char* const, const char* const)
{
	if(!g_if_condition.empty())
		g_if_condition.pop_back();

	g_if_condition.push_back('\0');
}

//-------------------------------------------------------------------

vector<char>	g_if_body;

void BeginIfBody(const char* const, const char* const)
{
	g_if_body.clear();
}

void AckIfBody(const char c)
{
	g_if_body.push_back(c);
}

void EndIfBody(const char* const, const char* const)
{
	if(!g_if_body.empty())
		g_if_body.pop_back();

	g_if_body.push_back('\0');

	g_psentence_array->push_back(new IfSentence(&g_if_condition[0], &g_if_body[0]));
}

//-------------------------------------------------------------
//	for
//-------------------------------------------------------------

vector<char>	g_for_init;

void BeginForInit(const char* const, const char* const)
{
	g_for_init.clear();
}

void AckForInit(const char c)
{
	g_for_init.push_back(c);
}

void EndForInit(const char* const, const char* const)
{
	if(!g_for_init.empty())
		g_for_init.pop_back();

	g_for_init.push_back('\0');
}

//-------------------------------------------------------------

vector<char>	g_for_condition;

void BeginForCondition(const char* const, const char* const)
{
	g_for_condition.clear();
}

void AckForCondition(const char c)
{
	g_for_condition.push_back(c);
}

void EndForCondition(const char* const, const char* const)
{
	if(!g_for_condition.empty())
		g_for_condition.pop_back();

	g_for_condition.push_back('\0');
}

//-------------------------------------------------------------

vector<char>	g_for_step;

void BeginForStep(const char* const, const char* const)
{
	g_for_step.clear();
}

void AckForStep(const char c)
{
	g_for_step.push_back(c);
}

void EndForStep(const char* const, const char* const)
{
	if(!g_for_step.empty())
		g_for_step.pop_back();

	g_for_step.push_back('\0');
}

//-------------------------------------------------------------

vector<char>	g_for_body;

void BeginForBody(const char* const, const char* const)
{
	g_for_body.clear();
}

void AckForBody(const char c)
{
	g_for_body.push_back(c);
}

void EndForBody(const char* const, const char* const)
{
	if(!g_for_body.empty())
		g_for_body.pop_back();

	g_for_body.push_back('\0');

	g_psentence_array->push_back(new ForSentence(&g_for_init[0], &g_for_condition[0], g_for_step.begin(), &g_for_body[0]) );
}

//-------------------------------------------------------------



struct sentence_parser : public boost::spirit::grammar<sentence_parser> {

	template<typename S> struct definition {

		boost::spirit::rule<S> sentence;

		boost::spirit::rule<S> if_condition_string, if_condition_brace;
		boost::spirit::rule<S> if_body_string, if_body_brace;
		boost::spirit::rule<S> if_condition, if_body;

		boost::spirit::rule<S> if_sentence;

		boost::spirit::rule<S> for_body_brace;
		boost::spirit::rule<S> for_init, for_condition, for_step, for_body;

		boost::spirit::rule<S> for_sentence;

		boost::spirit::rule<S> source;

		definition(const sentence_parser& self)
		{
			// if
			if_condition_string = ch_p('\"')[&AckIfCondition] >> *(anychar_p[&AckIfCondition] - '\"') >> '\"';
			if_condition_brace	= ch_p('(')[&AckIfCondition] >> *(anychar_p[&AckIfCondition] - ')') >> ')';

			if_condition	=	eps_p[&BeginIfCondition] >> 
								*( (if_condition_string) | (if_condition_brace) | (anychar_p[&AckIfCondition] - ')') ) >> 
								eps_p[&EndIfCondition];

			if_body_string	= ch_p('\"')[&AckIfBody] >> *(anychar_p[&AckIfBody] - '\"') >> '\"';
			if_body_brace	= ch_p('{')[&AckIfBody] >> *(anychar_p[&AckIfBody] - '}') >> '}';

			if_body			=	eps_p[&BeginIfBody] >> 
								(
									('{' >> *( (if_body_string) | (if_body_brace) | (anychar_p[&AckIfBody] - '}') ) >> '}') | 
									(*( (if_body_string) | (anychar_p[&AckIfBody] - ';') ) >> ch_p(';')[&AckIfBody])
								) >>
								eps_p[&EndIfBody];

			if_sentence	=	"if" >> *space_p >> 
							'(' >> *space_p >> if_condition >> *space_p >> ')' >> *space_p >>
							if_body >> *space_p;

			// for
			for_init		=	eps_p[&BeginForInit] >> *(anychar_p[&AckForInit] - ';') >> eps_p[&EndForInit];
			for_condition	=	eps_p[&BeginForCondition] >> *(anychar_p[&AckForCondition] - ';') >> eps_p[&EndForCondition];
			for_step		=	eps_p[&BeginForStep] >> *(anychar_p[&AckForStep] - ')') >> eps_p[&EndForStep];

			for_body_brace	=	ch_p('{')[&AckForBody] >> *(anychar_p[&AckForBody] - '}') >> '}';

			for_body		=	eps_p[&BeginForBody] >> 
								(
									('{' >> *( (for_body_brace) | (anychar_p[&AckForBody] - '}') ) >> '}') | 
									(*(anychar_p[&AckForBody] - ';') >> ch_p(';')[&AckForBody])
								) >>
								eps_p[&EndForBody];

			for_sentence	=	"for" >> *space_p >>
								'(' >>
									*space_p >> for_init >> *space_p >> ';' >>
									*space_p >> for_condition >> *space_p >> ';' >>
									*space_p >> for_step >> *space_p >> 
								')' >> *space_p >> for_body;


			// sentence
			sentence	= eps_p[&BeginSentence] >> *(anychar_p[&AckSentence] - ';') >> ';' >> eps_p[&EndSentence];

			source	=	*(*space_p >> (for_sentence | if_sentence | sentence) >> *space_p);
		}

		const boost::spirit::rule<S>& start() const { return source; }
	};
};

//========================================================================

Executable::Executable(string& source)
{
	Split(source, m_sentence_array);
}

Executable::~Executable()
{
	for(vector<SentenceBase*>::iterator it = m_sentence_array.begin(); it != m_sentence_array.end(); ++it)
	{
		delete *it;
	}
	m_sentence_array.clear();
}

bool Executable::Split(std::string& source, std::vector<SentenceBase*>& sentence_array)
{
	g_psentence_array = &sentence_array;

	comment_parser comment;
	sentence_parser sentence;

	parse_info<> r = parse(source.c_str(), sentence, comment);

	g_psentence_array = NULL;

	if(r.full)	// ì¸óÕÇ≥ÇÍÇΩï∂éöóÒÇ™ëSÇƒâêÕÇ≥ÇÍÇƒÇ¢ÇΩÇÁOK
		return true;
	else
		return false;
}

void Executable::Exec()
{
	for(vector<SentenceBase*>::iterator it = m_sentence_array.begin(); it != m_sentence_array.end(); ++it)
	{
		(*it)->Exec();
	}
}

void Executable::PrintState()
{
	for(vector<SentenceBase*>::iterator it = m_sentence_array.begin(); it != m_sentence_array.end(); ++it)
	{
		(*it)->PrintState();
	}
}

