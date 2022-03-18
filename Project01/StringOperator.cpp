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
