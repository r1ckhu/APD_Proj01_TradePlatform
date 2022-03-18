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
