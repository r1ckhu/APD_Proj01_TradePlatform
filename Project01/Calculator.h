#pragma once
#include <string>
using namespace std;
struct Operator
{
	char op;
	int precedence;
	bool is_left_associative;
};

enum Precedence
{
	GREATER,
	EQUAL,
	LOWER
};

class Calculator
{
public:
	float calexp(string& exp);
	string& to_rpn(string& exp, string& dst);
private:
	bool is_operator(char ch);
	bool is_left_associative(char op);
	void trim(string& exp);
	Precedence compare_precedence(char op1, char op2);
};

