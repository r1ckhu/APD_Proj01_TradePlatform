#pragma once
#include <string>
#include <sstream>
using namespace std;
class StringOperator
{
public:
	static void comma2space(wstring& src);
	static bool checkvalidity(wstring& src);
	static wstring float2str(float n);
	static int str2int(wstring& src);
	static float str2float(wstring& src);
};

