#include "StringOperator.h"

void StringOperator::comma2space(wstring& src)
{
	for (int i = 0; i < src.size(); i++)
		if (src[i] == ',')
			src[i] = ' ';
}
