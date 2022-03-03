#pragma once
#include "Calculator.h"
#include <sstream>
#include <string>
#include <stack>
#include <iostream>
using namespace std;
// TODO: Error handling
string& Calculator::to_rpn(string& exp, string& dst)
{
	stringstream input, output;
	stack<char> op_stack;
	char buffer = ' ';
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
				cout << "Mismatched parentheses!" << endl;
				return dst;
			}
			while (op_stack.top() != '(')
			{
				char o = op_stack.top();
				op_stack.pop();
				output << o << ' ';
				if (op_stack.empty()) {
					cout << "Mismatched parentheses!" << endl;
					return dst;
				}
			}
			if (op_stack.top() == '(')
				op_stack.pop();
		}
	}
	while (!op_stack.empty()) {
		char o = op_stack.top();
		if (o == '(') {
			cout << "Mismatched parentheses!" << endl;
			return dst;
		}
		op_stack.pop();
		output << o << ' ';
	}
	dst = output.str();
	return dst;
}

float Calculator::calexp(string& exp)
{
	trim(exp);
	string rpn;
	rpn = to_rpn(exp, rpn);
	cout << rpn << endl;
	stack<float> num_stack;
	stringstream ss(rpn);
	char buffer = ' ';
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
				cout << "Invaild expression!" << endl;
				return -1;
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
					cout << "Invaild expression!" << endl;
					return -1;
				}
			}
			if (buffer == '*')
				result = operands[0] * operands[1];
			else if (buffer == '/')
				result = operands[0] / operands[1];
			else if (buffer == '-')
				result = operands[0] - operands[1];
			else if (buffer == '+')
				result = operands[0] + operands[1];
			else {
				cout << "Invaild expression!" << endl;
				return -1;
			}
			num_stack.push(result);
		}
	}
	return num_stack.top();
}

void Calculator::trim(string& exp)
{
	for (int i = 0; i < exp.size(); i++){
		if (exp[i] == ' '){
			exp.erase(i,1);
			i--;
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
	cout << exp << endl;
	return;
}


bool Calculator::is_operator(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '~';
}

bool Calculator::is_left_associative(char op)
{
	if (op == '+' || op == '-' || op == '*' || op == '/')
		return true;
	else
		return false;
}

Precedence Calculator::compare_precedence(char op1, char op2)
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