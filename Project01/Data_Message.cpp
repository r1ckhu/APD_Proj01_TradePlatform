#include "Data.h"
#include <iomanip>
using namespace std;
MessageData::MessageData()
{
	id = L"";
	msg = L"";
	senderID = L"";
	receiverID = L"";
	read = false;
}

MessageData::MessageData(wstring& _id, wstring& _msg, wstring& _senderID, wstring& _receiverID)
{
	id = _id;
	msg = _msg;
	senderID = _senderID;
	receiverID = _receiverID;
	read = false;
}

void MessageData::format_output(int width)
{
	wcout << setw(width) << id << setw(width) << msg
		<< setw(width) << senderID << setw(width) << receiverID;
	if (read)
		wcout << setw(width) << L"hasRead";
	else
		wcout << setw(width) << L"notRead";
	wcout << endl;
}

wstring MessageData::get_senderID()
{
	return senderID;
}

wstring MessageData::get_receiverID()
{
	return receiverID;
}

wstring MessageData::get_msg()
{
	return msg;
}

bool MessageData::hasRead()
{
	return read;
}

void MessageData::readMsg()
{
	read = true;
}

wofstream& operator<<(wofstream& output, const MessageData& msgd)
{
	output << msgd.id << endl << msgd.msg << endl \
		<< msgd.senderID << ' ' << msgd.receiverID << ' ' << msgd.read;
	return output;
}