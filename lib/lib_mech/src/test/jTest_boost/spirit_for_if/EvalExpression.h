#ifndef _EVALEXPERSSION_H_
#define _EVALEXPRESSION_H_

#include <string>

class EvalExpression { 

public:
	int Eval(const char* expression);
	int Eval(std::string& expression) { return Eval(expression.c_str()); }

};

#endif