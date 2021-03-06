#pragma once
#include "Menu.h"
#include "User.h"

extern UserHandler userhandler;
extern SQL_Interpreter sql_interpreter;
extern Calculator calculator;
using namespace std;
const int WIDTH = 15;

void Menu::putnch(char ch, int n, bool changeline)
{
	for (int i = 1; i <= n; i++)
		printf("%c", ch);
	if (changeline)
		printf("\n");
}

void Menu::putnch(wchar_t ch, int n, bool changeline)
{
	for (int i = 1; i <= n; i++)
		wprintf(L"%lc", ch);
	if (changeline)
		wprintf(L"\n");
}

void Menu::formatting_output(list<CommodityData>* _list, bool onlyOnSale)
{
	if (_list->size() == 0) {
		wprintf(L"No Commodity Found!\n");
		return;
	}
	putnch('*', 110);
	wcout << setw(WIDTH) << L"commodityID" << setw(WIDTH) << L"commodityName" << setw(WIDTH) << L"price" << setw(WIDTH) << L"number" <<
		setw(WIDTH) << L"description" << setw(WIDTH) << L"sellerID" << setw(WIDTH) << L"addedDate" << setw(WIDTH) << L"state" << endl;
	for (list<CommodityData>::iterator it = _list->begin(); it != _list->end(); it++)
	{
		//TODO: if all the commodity in the list is removed, then will output empty list
		if (onlyOnSale && (*it).commodity_state == ON_SELL)
			(*it).format_output(15);
		else if (!onlyOnSale)
			(*it).format_output(15);
	}
	putnch('*', 110);
}

void Menu::formatting_output(list<pair<CommodityData, int>>* _list)
{
	if (_list->size() == 0) {
		wprintf(L"No Commodity Found!\n");
		return;
	}
	putnch('*', 110);
	wcout << setw(WIDTH) << L"commodityID" << setw(WIDTH) << L"commodityName" << setw(WIDTH) << L"price" << setw(WIDTH) << L"number" <<
		setw(WIDTH) << L"description" << setw(WIDTH) << L"sellerID" << setw(WIDTH) << L"addedDate" << setw(WIDTH) << L"state" << endl;
	for (list<pair<CommodityData, int>>::iterator it = _list->begin(); it != _list->end(); it++)
		if ((*it).first.get_commodity_state() == ON_SELL)
			(*it).first.format_output(15);
	putnch('*', 110);
}

void Menu::formatting_output(list<OrderData>* _list)
{
	if (_list->size() == 0) {
		wprintf(L"No Order Found!\n");
		return;
	}
	putnch('*', 100);
	wcout << setw(WIDTH) << L"orderID" << setw(WIDTH) << L"commodityID" << setw(WIDTH) << L"unitPrice" << setw(WIDTH) << L"number" <<
		setw(WIDTH) << L"date" << setw(WIDTH) << L"sellerID" << setw(WIDTH) << L"buyerID" << endl;
	for (list<OrderData>::iterator it = _list->begin(); it != _list->end(); it++)
		(*it).format_output(15);
	putnch('*', 100);
}

void Menu::formatting_output(list<UserData>* _list)
{
	if (_list->size() == 0) {
		wprintf(L"No User Found!\n");
		return;
	}
	putnch('*', 100);
	wcout << setw(WIDTH) << L"userID" << setw(WIDTH) << L"username" << setw(WIDTH) << L"password" << setw(WIDTH) << L"phoneNumber" <<
		setw(WIDTH) << L"address" << setw(WIDTH) << L"balance" << setw(WIDTH) << L"userState" << endl;
	for (list<UserData>::iterator it = _list->begin(); it != _list->end(); it++)
		(*it).format_output(15);
	putnch('*', 100);
}

void Menu::formatting_output(list<MessageData>* _list, UserData* user)
{
	if (_list->size() == 0) {
		wprintf(L"No Message Found!\n");
		return;
	}
	wcout << L"This is the message you have received: " << endl;
	putnch('*', 100);
	wcout << setw(WIDTH) << L"messageID" << setw(WIDTH) << L"content" << setw(WIDTH)
		<< L"senderID" << setw(WIDTH) << L"receiverID" <<L"readState" << endl;
	for (list<MessageData>::iterator it = _list->begin(); it != _list->end(); it++)
		if ((*it).get_receiverID() == user->id) {
			(*it).readMsg();
			(*it).format_output(15);
		}
	putnch('*', 100);
	wcout << endl;
	wcout << L"This is the message you have sent: " << endl;
	putnch('*', 100);
	wcout << setw(WIDTH) << L"messageID" << setw(WIDTH) << L"content" << setw(WIDTH)
		<< L"senderID" << setw(WIDTH) << L"receiverID" << L"readState" << endl;
	for (list<MessageData>::iterator it = _list->begin(); it != _list->end(); it++)
		if ((*it).get_senderID() == user->id)
			(*it).format_output(15);
	putnch('*', 100);
}

void DefaultMenu::printMenu()
{
	putnch('\n', 2);
	putnch('=', 63);
	wcout << L"1.Admin Login 2.User Register 3.User Login 4.Exit 5.Calculator" << endl;
	putnch('=', 63);
}

void DefaultMenu::inputloop(UserData* user)
{
	int input = 0;
	while (true) {
		printMenu();
		wprintf(L"Please choose an operation:");
		InputHandler::inputCommand(input, 1, 5);
		if (input == 1) {
			user = userhandler.adminlogin();
			if (user != nullptr) {
				AdminMenu adminmenu;
				adminmenu.inputloop(user);
			}
			delete user; // admin is a temporary Userdata
		}
		else if (input == 2) {
			userhandler.userRegister();
		}
		else if (input == 3) {
			user = userhandler.userlogin();
			if (user != nullptr) {
				UserMenu usermenu;
				usermenu.inputloop(user);
			}
		}
		else if (input == 4) {
			//_CrtDumpMemoryLeaks();
			exit(0);
		}
		else if (input == 5) {
			wstring ws;
			wcin.get();
			wprintf(L"Please enter an arithmetic expression:");
			getline(wcin, ws);
			while (ws != L"exit") {
				float ans = calculator.calexp(ws);
				wcout << ans << endl << endl;
				wprintf(L"Please enter an arithmetic expression:");
				getline(wcin, ws);
			}
		}
	}
};

