#pragma once
#include <string>
using namespace std;
class StringOperator
{
public:
	static void comma2space(wstring &src);
	static bool checkvalidity(wstring& src);
	static string float2str(float n, int digits);
};

