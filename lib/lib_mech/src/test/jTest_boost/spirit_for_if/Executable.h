#ifndef _EXECUTABLE_H_
#define _EXECUTABLE_H_

#include <string>
#include <vector>
#include <iostream>

//=============================================================================

class SentenceBase {
public:
	virtual ~SentenceBase() {}

	virtual void Exec() {}
	virtual void PrintState() { std::cout << "Unknown" << std::endl; }
};

//---------------------------------------------
//---------------------------------------------

class Sentence : public SentenceBase { 
	std::string	m_sentence;
public:
	Sentence(const char* sentence) : m_sentence(sentence) {}

	std::string& GetSentence() { return m_sentence; }

	void Exec();
	void PrintState() { std::cout << "Sentence : " << m_sentence << std::endl; }
};

//---------------------------------------------

class IfSentence : public SentenceBase { 
	std::string m_condition;
	std::string m_body;
public:
	IfSentence(const char* condition, const char* body) : m_condition(condition), m_body(body) {}

	void Exec();
	void PrintState() { std::cout << "IfSentence : condition = " << m_condition << " : body = " << m_body << std::endl; }
};

//---------------------------------------------

class ForSentence : public SentenceBase { 
	std::string m_init;
	std::string m_condition;
	std::string m_step;
	std::string m_body;
public:
	ForSentence(const char* init, const char* condition, const char* step, const char* body) 
		: m_init(init), m_condition(condition), m_step(step), m_body(body) {}

	void Exec();
	void PrintState() { std::cout << "ForSentence : init = " << m_init << " : condition = " << m_condition << " : step = " << m_step << " : body = " << m_body << std::endl; }
};

//============================================================================

class Executable { 
	std::vector<SentenceBase*>		m_sentence_array;

	bool Split(std::string& source, std::vector<SentenceBase*>& sentence_array);
public:
	Executable(std::string& source);
	~Executable();

	void Exec();
	void PrintState();
};

//============================================================================

#endif