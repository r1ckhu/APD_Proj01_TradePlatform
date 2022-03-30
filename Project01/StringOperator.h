#pragma once
#include <string>
#include <sstream>
using namespace std;
const int Matched_letter = 0;
const int Unmatched_letter = -1;
const int Consecutive_match_bonus = 3;
const int Separator_bonus = 10;
const int Camel_case_bonus = 10;
const int Unmatched_leading_letter = -2;
const int Unmatched_leading_maxCnt = 3;
const int Full_matched = 20;

class StringOperator
{
public:
	static void comma2space(wstring& src);
	static wstring float2str(float n);
	static int str2int(wstring& src);
	static float str2float(wstring& src);
	static int fuzzy_match(wstring& pattern, wstring& str, int& score);
};

