#pragma once
#include "Calculator.h"
#include <sstream>
#include <string>
#include <stack>
#include <iostream>
using namespace std;
// TODO: Error handling
const wstring err_op = L"----ERROR: Illigal Operator!----";
const wstring err_divZero = L"----ERROR: Divide by Zero!----";
const wstring err_wroNumFor = L"----ERROR: Unaccepted Number Format!----";
const wstring err_mismatPar = L"----ERROR: Mismatched Parentheses!----";
const wstring err_unknown = L"----ERROR: Unknown Error!----";
const wstring err_unChar = L"----ERROR: Unaccepted Charactor!----";
const float DELTA = 0.00001;
bool Calculator::to_rpn(wstring& exp, wstring& dst)
{
	wstringstream input, output;
	stack<wchar_t> op_stack;
	wchar_t buffer = ' ';
	input << exp;
	while (input >> buffer)
	{
		float number = 0;
		char o1 = 0;
		if (buffer >= '0' && buffer <= '9') // buffer is an number
		{
			input.putback(buffer);
			input >> number;
			output << number << ' ';
		}
		else if (is_operator(buffer))
		{
			char o1 = buffer;
			char o2 = op_stack.empty() ? ' ' : op_stack.top();
			while (is_operator(o2) && (compare_precedence(o2, o1) == GREATER \
				|| (compare_precedence(o2, o1) == EQUAL && is_left_associative(o1)))) {
				output << o2 << ' ';
				op_stack.pop();
				o2 = op_stack.empty() ? ' ' : op_stack.top();
			}
			op_stack.push(o1);
		}
		else if (buffer == '(')
			op_stack.push(buffer);
		else if (buffer == ')') {
			if (op_stack.empty()) {
				wcout << err_mismatPar << endl;
				return false;
			}
			while (op_stack.top() != '(')
			{
				char o = op_stack.top();
				op_stack.pop();
				output << o << ' ';
				if (op_stack.empty()) {
					wcout << err_mismatPar << endl;
					return false;
				}
			}
			if (op_stack.top() == '(')
				op_stack.pop();
		}
	}
	while (!op_stack.empty()) {
		char o = op_stack.top();
		if (o == '(') {
			wcout << err_mismatPar << endl;
			return false;
		}
		op_stack.pop();
		output << o << ' ';
	}
	dst = output.str();
	return true;
}

float Calculator::calexp(wstring& exp)
{
	trim(exp);
	wcout << exp << endl;
	bool valid = is_valid_expression(exp);
	wstring rpn;
	bool matched_parentheses = to_rpn(exp, rpn);
	if (!(matched_parentheses && valid)) {
		return NAN;
	}
	wcout << rpn << endl;
	stack<float> num_stack;
	wstringstream ss(rpn);
	wchar_t buffer = ' ';
	while (ss >> buffer) {
		float num = 0;
		if (buffer >= '0' && buffer <= '9') {
			ss.putback(buffer);
			ss >> num;
			num_stack.push(num);
		}
		else if (buffer == '~') {
			float operand;
			if (!num_stack.empty()) {
				operand = num_stack.top();
				num_stack.pop();
			}
			else {
				wcout << err_unknown << endl;
				return NAN;
			}
			operand = -operand;
			num_stack.push(operand);
		}
		else {
			float operands[2];
			float result;
			for (int i = 1; i >= 0; i--) {
				if (!num_stack.empty()) {
					operands[i] = num_stack.top();
					num_stack.pop();
				}
				else {
					wcout << err_unknown << endl;
					return NAN;
				}
			}
			if (buffer == '*')
				result = operands[0] * operands[1];
			else if (buffer == '/') {
				if (operands[1] - 0.0 < DELTA) {
					wcout << err_divZero << endl;
					return NAN;
				}
				result = operands[0] / operands[1];
			}
			else if (buffer == '-')
				result = operands[0] - operands[1];
			else if (buffer == '+')
				result = operands[0] + operands[1];
			else {
				wcout << err_unknown << endl;
				return NAN;
			}
			num_stack.push(result);
		}
	}
	if (num_stack.size() != 1) {
		wcout << err_wroNumFor << endl;
		return NAN;
	}
	return num_stack.top();
}

void Calculator::trim(wstring& exp)
{
	for (int i = 0; i < exp.size(); i++) {
		if (is_operator(exp[i]) || exp[i] == '(' || exp[i] == ')') {
			wchar_t left, right;
			int opPos = i;
			int lb = (opPos == 0) ? opPos : opPos - 1;
			while (exp[lb] == ' ' && lb > 0)
				lb--;
			left = exp[lb];
			if (lb != opPos)
				exp.erase(exp.begin() + lb + 1, exp.begin() + i);
			int leftCutLen = opPos - lb - 1;
			opPos -= leftCutLen;
			i -= leftCutLen;
			int rb = (opPos == exp.size() - 1) ? opPos : opPos + 1;
			while (exp[rb] == ' ' && rb < exp.size())
				rb++;
			right = exp[rb];
			if (rb != opPos)
				exp.erase(exp.begin() + 1 + opPos, exp.begin() + rb);
		}
	}

	for (int i = 0; i < exp.size() - 1; i++) {
		if (exp[i] == '(' && exp[i + 1] == '-')
			exp[i + 1] = '~';
		if (is_operator(exp[i]) && exp[i + 1] == '-')
			exp[i + 1] = '~';
	}
	if (exp[0] == '-')
		exp[0] = '~';
	return;
}


bool Calculator::is_operator(wchar_t ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '~';
}

bool Calculator::is_left_associative(wchar_t op)
{
	if (op == '+' || op == '-' || op == '*' || op == '/')
		return true;
	else
		return false;
}

bool Calculator::is_valid_expression(wstring& exp)
{
	for (int i = 0; i < exp.size(); i++) {
		if (is_operator(exp[i])) {
			if ((i == 0 && exp[i] != '~') || (i == exp.size() - 1)) {
				wcout << err_op << endl;
				return false;
			}
			else if (i == 0 && exp[i] == '~')
				continue;
			if (is_operator(exp[i - 1]) || is_operator(exp[i + 1])) {
				// TODO: This may be legal
				wcout << err_op << endl;
				return false;
			}
		}
		else if (exp[i] == '.') {
			if (i == 0 || i == exp.size() - 1) {
				wcout << err_wroNumFor << endl;
				return false;
			}
			else if (exp[i - 1] < '0' || exp[i - 1]>'9') {
				wcout << err_wroNumFor << endl;
				return false;
			}
			else if (exp[i + 1] < '0' || exp[i + 1]>'9') {
				wcout << err_wroNumFor << endl;
				return false;
			}
		}
		else if ('0' <= exp[i] && exp[i] <= '9') {
			if ((i != 0 && exp[i - 1] == ' ') || (i != exp.size() - 1 && exp[i + 1] == ' ')) {
				wcout << err_wroNumFor << endl;
				return false;
			}
		}
		else if (!is_operator(exp[i]) && !('0' <= exp[i] && exp[i] <= '9') \
			&& !(exp[i] == '(' || exp[i] == ')')) {
			wcout << err_unChar << endl;
			return false;
		}
	}
	return true;
}

Precedence Calculator::compare_precedence(wchar_t op1, wchar_t op2)
{
	int p1 = 0, p2 = 0;
	if (op1 == '~')
		p1 = 3;
	else if (op1 == '*' || op1 == '/')
		p1 = 2;
	else if (op1 == '+' || op1 == '-')
		p1 = 1;
	if (op2 == '~')
		p2 = 3;
	else if (op2 == '*' || op2 == '/')
		p2 = 2;
	else if (op1 == '+' || op2 == '-')
		p2 = 1;
	if (p1 < p2)
		return LOWER;
	else if (p1 == p2)
		return EQUAL;
	else
		return GREATER;
}