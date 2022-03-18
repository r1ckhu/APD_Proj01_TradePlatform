#pragma once
#include "Data.h"
#include "SQL_Interpreter.h"
#include "Calculator.h"
#include "Menu.h"
#include "User.h"
#include "InputHandler.h"
#include <locale>
#include <iomanip>
DataHandler datahandler;
UserHandler userhandler;
SQL_Interpreter sql_interpreter;
Calculator calculator;
locale zh_utf("zh_CN.UTF-8");
int main()
{
	wcout << setiosflags(ios::left);
	wcout.precision(1);
	wcout.setf(ios::fixed, ios::floatfield);
	//cout.setf(ios::showpoint);
	cout.precision(1);
	//wcout.imbue(locale(zh_utf, new std::numpunct<wchar_t>));
	//wcin.imbue(locale("zh_CN.UTF-8"));
	//setlocale(LC_ALL, "zh_CN.UTF-8");
	UserData* ud = nullptr;
	DefaultMenu defaultmenu;
	UserMenu usermenu;
	defaultmenu.inputloop(ud);

	return 0;
}