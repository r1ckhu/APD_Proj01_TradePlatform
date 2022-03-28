#pragma once
#include "StringOperator.h"
#include <sstream>
void StringOperator::comma2space(wstring& src)
{
	for (int i = 0; i < src.size(); i++)
		if (src[i] == ',')
			src[i] = ' ';
}

wstring StringOperator::float2str(float n)
{
	wstringstream wss;
	wss << n;
	wstring ws;
	wss >> ws;
	return ws;
}

int StringOperator::str2int(wstring& src)
{
	wstringstream wss;
	wss << src;
	int dst = 0;
	wss >> dst;
	return dst;
}

float StringOperator::str2float(wstring& src)
{
	float dst = 0.0f;
	wstringstream wss;
	wss << src;
	wss >> dst;
	return dst;
}

int StringOperator::fuzzy_match(wstring& pattern, wstring& str, int& score)
{

	int i = 0, j = 0;
	bool combo = false;
	bool leadingMatched = true;
	int comboCnt = 0;
	int _score = 0;
	while (i < pattern.size() && j < str.size()) {
		if (tolower(pattern[i]) == tolower(str[j])) {
			if (pattern[i] == str[i] && pattern[i] > 'A' && pattern[i] < 'Z') {
				_score += Camel_case_bonus;
			}
			if (combo) {
				_score += Consecutive_match_bonus;
				if (pattern[i] == ' ') {
					_score += Separator_bonus;
				}
			}
			else if (!combo)
				combo = true;
			i++; j++;
		}
		else {
			if (j < Unmatched_leading_maxCnt)
				_score += Unmatched_leading_letter;
			else
				_score += Unmatched_letter;
			combo = false;
			j++;
		}
	}
	if (i == pattern.size())
		_score += Full_matched;
	score = _score;
	return _score;
}


