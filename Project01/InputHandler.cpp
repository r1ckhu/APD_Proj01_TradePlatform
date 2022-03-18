#include "InputHandler.h"
#include "StringOperator.h"
bool InputHandler::inputInt(int& src)
{
	wstring buffer;
	wcin >> buffer;
	for (wchar_t ch : buffer)
		if (ch > '9' || ch < '0')
		{
			wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return false;
		}
	src = StringOperator::str2int(buffer);
	wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return true;
}

bool InputHandler::inputFloat(float& src, int precison)
{
	// TODO: precison not support
	wstring buffer;
	wcin >> buffer;
	for (wchar_t ch : buffer)
		if ((ch > '9' || ch < '0') && ch != '.')
		{
			wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return false;
		}
	int afterpoint = 0;
	wstring::iterator it = buffer.begin();
	for (; it != buffer.end(); it++) {
		if (afterpoint == 2)
			break;
		if (afterpoint == 1)
			afterpoint++;
		if (*it == '.')
			afterpoint = 1;
	}
	if (afterpoint == 2)
		buffer.erase(it, buffer.end());
	src = StringOperator::str2float(buffer);
	if (src - (float)9999999 > 0)
		wcout << "----WARNING: THE NUMBER MAY BE TOO LARGE TO BE ACCURATE!----" << endl;
	wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return true;
}

bool InputHandler::inputNumber(wstring& src, int length)
{
	wcin >> src;
	for (wchar_t ch : src) {
		if (ch < '1' || ch >'9') {
			wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return false;
		}
	}
	if (src.size() > length)
		wcout << "----WARNING: INPUT EXCEED MAXIMUM LENGTH! EXCEEDED PART WILL BE CUT!----" << endl;
	src.resize(length);
	wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return true;
}

bool InputHandler::inputString(wstring& src, int length, bool allowNumber, bool allowCaptial)
{
	wcin >> src;
	for (wchar_t ch : src) {
		if (allowNumber && '1' <= ch && ch <= '9')
			continue;
		if (allowCaptial && 'A' <= ch && ch <= 'Z')
			continue;
		if (ch < 'a' || ch >'z') {
			wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return false;
		}
	}
	if (src.size() > length)
		wcout << "----WARNING: INPUT EXCEED MAXIMUM LENGTH! EXCEEDED PART WILL BE CUT!----" << endl;
	src.resize(length);
	wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return true;
}

bool InputHandler::inputCommand(int& src, int lb, int rb)
{
	wcin >> src;
	if (!wcin) {
		wcin.clear();
		wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return false;
	}
	if (src<lb || src>rb) {
		wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return false;
	}
	return true;
}

bool InputHandler::inputConfirm(wchar_t& src)
{
	wcin >> src;
	if (!wcin) {
		wcin.clear();
		wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return false;
	}
	if (src != 'y' && src != 'n') {
		wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return false;
	}
	return true;
}

void InputHandler::throwError()
{
	wcout << "----Illegial Input!---" << endl;
}
