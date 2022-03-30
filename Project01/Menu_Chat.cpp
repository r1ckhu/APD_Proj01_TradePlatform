#include "Menu.h"
#include "User.h"
#include "Data.h"
using namespace std;
extern MessageHandler messagehandler;
void ChatMenu::printMenu()
{
	putnch('\n', 2);
	putnch('=', 100);
	wcout << L"1.Show Message 2.Send Message 3.RetractMessage 4.Return to Main Menu" << endl;
	putnch('=', 100);
}

void ChatMenu::inputloop(UserData* user)
{
	int input = 0;
	while (true) {
		printMenu();
		wprintf(L"Please choose an operation:");
		InputHandler::inputCommand(input, 1, 4);
		if (input == 1) {
			show_message(user);
			continue;
		}
		else if (input == 2) {
			sendMessage(user);
			continue;
		}
		else if (input == 3) {
			retractMessage(user);
			continue;
		}
		else if (input == 4) {
			return;
		}
	}
}

void ChatMenu::show_message(UserData* user)
{
	list<MessageData>* _list = messagehandler.get_message_list();
	formatting_output(_list, user);
}

void ChatMenu::sendMessage(UserData* user)
{
	wstring msg, senderID, receiverID;
	wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	wcout << L"Please enter your content: ";
	getline(wcin, msg);
	wcout << L"Please enter the receiverID: ";
	if (!InputHandler::inputString(receiverID, 4, true, true)){
		InputHandler::throwError();
		return;
	}
	wcout << L"Please confirm (y/n): ";
	wchar_t sign;
	InputHandler::inputConfirm(sign);
	if (sign == 'y')
	{
		messagehandler.sendMsg(msg, user->get_id(), receiverID);
		wcout << "----Successful!----" << endl;
	}
	else
	{
		wcout << "----Operation Terminated!----" << endl;
	}
}

void ChatMenu::retractMessage(UserData* user)
{
	wstring id;
	wcout << "Please enter the messageID: ";
	if (!InputHandler::inputString(id, 4, true, true)){
		InputHandler::throwError();
		return;
	}
	messagehandler.retractMsg(user, id);
	return;
}
