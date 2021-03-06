#pragma once
#include <string>
using namespace std;

enum Precedence
{
	GREATER,
	EQUAL,
	LOWER
};

class Calculator
{
public:
	float calexp(wstring& exp);
	bool to_rpn(wstring& exp, wstring& dst);
private:
	bool is_operator(wchar_t ch);
	bool is_left_associative(wchar_t op);
	bool is_valid_expression(wstring& exp);
	void trim(wstring& exp);
	Precedence compare_precedence(wchar_t op1, wchar_t op2);
};

