#pragma once
#include "Menu.h"
#include "User.h"
#include <iomanip>
extern UserHandler userhandler;
extern SQL_Interpreter sql_interpreter;
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
	putnch('*', 100);
	wcout << setw(WIDTH) << L"commodityID" << setw(WIDTH) << L"commodityName" << setw(WIDTH) << L"price" << setw(WIDTH) << L"number" <<
		setw(WIDTH) << L"description" << setw(WIDTH) << L"sellerID" << setw(WIDTH) << L"addedDate" << setw(WIDTH) << L"state" << endl;
	for (list<CommodityData>::iterator it = _list->begin(); it != _list->end(); it++)
	{
		if (onlyOnSale && (*it).commodity_state == ON_SELL)
			(*it).format_output(15);
		else if (!onlyOnSale)
			(*it).format_output(15);
	}
	putnch('*', 100);
}

void Menu::formatting_output(list<CommodityData>* _list, UserData* user)
{
	if (_list->size() == 0) {
		wprintf(L"No Commodity Found!\n");
		return;
	}
	putnch('*', 100);
	wcout << setw(WIDTH) << L"commodityID" << setw(WIDTH) << L"commodityName" << setw(WIDTH) << L"price" << setw(WIDTH) << L"number" <<
		setw(WIDTH) << L"description" << setw(WIDTH) << L"sellerID" << setw(WIDTH) << L"addedDate" << setw(WIDTH) << L"state" << endl;
	for (list<CommodityData>::iterator it = _list->begin(); it != _list->end(); it++)
		(*it).format_output(15);
	putnch('*', 100);
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

void DefaultMenu::printMenu()
{
	putnch('\n', 2);
	putnch('=', 47);
	wcout << L"1.Admin Login 2.User Register 3.User Login 4.Exit" << endl;
	putnch('=', 47);
}

void DefaultMenu::inputloop(UserData* user)
{
	int input = 0;
	while (true) {
		if (!cin) { //illegal input handling
			cin.clear();
			string cache;
			cin >> cache;
		}
		printMenu();
		wprintf(L"Please choose an operation:");
		cin >> input;
		if (input == 1) {
			UserData* user = userhandler.adminlogin();
			if (user != nullptr) {
				AdminMenu adminmenu;
				adminmenu.inputloop(user);
			}
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
			exit(0);
		}
	}
};

