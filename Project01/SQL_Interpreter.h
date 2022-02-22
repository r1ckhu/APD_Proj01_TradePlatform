#pragma once
#include <string>
#include <list>
#include "Data.h"
using namespace std;

class SQL_Interpreter
{
public:
	void interpret(wstring& statement);
};