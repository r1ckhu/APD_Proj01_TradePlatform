#include "Data.h"
using namespace std;
MessageHandler::MessageHandler()
{
	wifstream in_msg(fpath_message, ios::in);
	MessageData msgd;
	if (!in_msg) {
		wofstream out_msg(fpath_message, ios::out);
		// out_user.imbue(locale(zh_utf, new std::numpunct<wchar_t>));
		out_msg.close();
	}
	while (in_msg >> msgd.id)
	{
		if (!msgd.id.empty())
		{
			getline(in_msg, msgd.msg);
			getline(in_msg, msgd.msg);
			in_msg >> msgd.senderID >> msgd.receiverID >> msgd.read;
			Msglist.push_back(msgd);
		}
	}
	in_msg.close();
}

void MessageHandler::sendMsg(wstring& msg, wstring& senderID, wstring& receieverID)
{
	wstring id = generate_new_id();
	MessageData msgd(id, msg, senderID, receieverID);
	Msglist.push_back(msgd);
	logMessage(msgd);
}

void MessageHandler::retractMsg(UserData* user, wstring& msgID)
{
	for (list<MessageData>::iterator it = Msglist.begin();
		it != Msglist.end(); it++)
	{
		if ((*it).id == msgID)
		{
			if ((*it).senderID == user->get_id())
			{
				if (!(*it).read) {
					Msglist.erase(it);
					wprintf(L"----Retract Message Successful!----\n");
					updateMessage();
					return;
				}
				else {
					wprintf(L"----Failure: The message has been read!----\n");
					updateMessage();
					return;
				}
			}
			else {
				wprintf(L"----Failure: This is not your message!----\n");
				updateMessage();
				return;
			}
		}
	}
	wprintf(L"----Failure: No Message Found!----\n");
	return;
}

list<MessageData>* MessageHandler::get_message_list()
{
	return  &Msglist;
}

void MessageHandler::logMessage(MessageData& msgd)
{
	wofstream output(fpath_message, ios::app);
	output << msgd << endl;
}

void MessageHandler::updateMessage()
{
	wofstream output(fpath_message, ios::out);
	for (list<MessageData>::iterator it = Msglist.begin();
		it != Msglist.end(); it++)
	{
		output << (*it) << endl;
	}
}

wstring MessageHandler::generate_new_id()
{
	wstringstream wss;
	int cnt = Msglist.size() + 1;
	if (cnt < 10)
		wss << "X00" << cnt;
	else if (cnt < 100)
		wss << "X0" << cnt;
	else
		wss << "X" << cnt;
	wstring id;
	wss >> id;
	return id;
}
