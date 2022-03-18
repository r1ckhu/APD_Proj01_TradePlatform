#pragma once
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

class InputHandler
{
public:
	//bool inputID(wstring& src);
	static bool inputInt(int& src);
	static bool inputFloat(float& src, int precison = 1);
	static bool inputNumber(wstring& src, int length);
	static bool inputString(wstring& src, int length, bool allowNumber, bool allowCaptial);
	static bool inputCommand(int& src, int lb, int rb);
	static bool inputConfirm(wchar_t& src);
	static void throwError();
};

