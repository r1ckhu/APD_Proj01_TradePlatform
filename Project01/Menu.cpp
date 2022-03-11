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

void Menu::formatting_output(list<CommodityData>* _list)
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
			// TODO: user register
			continue;
		}
		else if (input == 3) {
			user = userhandler.userlogin();
			UserMenu usermenu;
			usermenu.inputloop(user);
		}
		else if (input == 4) {
			exit(0);
		}
	}
};


void AdminMenu::printMenu()
{
	putnch('\n', 2);
	putnch('=', 100);
	wcout << L"1.View All Commodities 2.Search Commodities 3.Remove Commodity 4.View All Orders 5.View All Users 6.Ban Users 7.Logout" << endl;
	putnch('=', 100);
}
void AdminMenu::inputloop(UserData* user)
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
			show_commodity();
			continue;
		}
		else if (input == 2) {
			search_commodity();
			continue;
		}
		else if (input == 3) {
			remove_commodity();
			continue;
		}
		else if (input == 4) {
			show_orders();
			continue;
		}
		else if (input == 5) {
			show_users();
			continue;
		}
		else if (input == 6) {
			continue;
		}
		else if (input == 7) {
			return;
		}
	}
}

void AdminMenu::show_commodity()
{
	wstring command(L"SELECT * FROM commodity");
	list<CommodityData>* _list = (list<CommodityData>*)sql_interpreter.interpret(command);
	formatting_output(_list);
}

void AdminMenu::search_commodity()
{
	wstring name;
	wprintf(L"Please enter a commodity's name:");
	wcin >> name;
	wstring command(L"SELECT * FROM commodity WHERE commodityName CONTAINS ");
	command += name;
	list<CommodityData>* _list = (list<CommodityData>*)sql_interpreter.interpret(command);
	formatting_output(_list);
}

void AdminMenu::remove_commodity()
{
	wstring id;
	wprintf(L"Please enter a commodity's id:");
	wcin >> id;
	wstring command(L"SELECT * FROM commodity WHERE commodityID CONTAINS ");
	command += id;
	wprintf(L"This is the commodity you select:\n");
	list<CommodityData>* _list = (list<CommodityData>*)sql_interpreter.interpret(command);
	formatting_output(_list);
	if (_list->size() != 0)
	{
		wprintf(L"Please Confirm your choice (y/n):");
		wchar_t sign;
		wcin >> sign;
		if (sign == 'y') {
			command = L"UPDATE commodity SET state = offShelf WHERE commodityID = ";
			command += id;
			sql_interpreter.interpret(command);
			wprintf(L"Operation Successful!\n\n");
		}
		else {
			wprintf(L"Operation Terminated!\n\n");
		}
	}
}

void AdminMenu::show_orders()
{
	wstring command(L"SELECT * FROM order");
	list<OrderData>* _list = (list<OrderData>*)sql_interpreter.interpret(command);
	formatting_output(_list);
}

void AdminMenu::show_users()
{
	wstring command(L"SELECT * FROM user");
	list<UserData>* _list = (list<UserData>*)sql_interpreter.interpret(command);
	formatting_output(_list);
}


void UserMenu::printMenu()
{
	putnch('\n', 2);
	putnch('=', 49);
	wcout << L"1.I am a Buyer 2.I am a Seller 3.Manage Personal Info 4.Logout" << endl;
	putnch('=', 49);
}
void UserMenu::inputloop(UserData* user)
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
			BuyerMenu buyermenu;
			buyermenu.inputloop(user);
		}
		else if (input == 2) {
			SellerMenu sellermenu;
			sellermenu.inputloop(user);
		}
		else if (input == 3) {
			InfoMenu infomenu;
			infomenu.inputloop(user);
			continue;
		}
		else if (input == 4) {
			return;
		}
	}
}

void SellerMenu::printMenu()
{
	putnch('\n', 2);
	putnch('=', 85);
	wcout << L"1.Release an Commodity 2.View my Commodities 3.Modify Commodity Info 4.Remove Commodity 5.View History Orders 6.Return to Main Menu" << endl;
	putnch('=', 85);
}
void SellerMenu::inputloop(UserData* user)
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
			//put_commodity(user);
			continue;
		}
		else if (input == 2) {
			//show_commodity(user);
			continue;
		}
		else if (input == 3) {
			//modify_commodity(user);
			continue;
		}
		else if (input == 4) {
			//remove_commodity(user);
			continue;
		}
		else if (input == 5) {
			//show_history(user);
			continue;
		}
		else if (input == 6) {
			return;
		}
	}
}

void BuyerMenu::printMenu()
{
	putnch('\n', 2);
	putnch('=', 89);
	wcout << L"1.View All Commodities 2.Purchase Commodities 3.Search Commodities 4.View History Orders 5.View Detailed Commidity Info 6.Return to Main Menu" << endl;
	putnch('=', 89);
}
void BuyerMenu::inputloop(UserData* user)
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
			//show_commodity(user);
			continue;
		}
		else if (input == 2) {
			//buy_commodity(user);
			continue;
		}
		else if (input == 3) {
			//search_commodity(user);
			continue;
		}
		else if (input == 4) {
			//show_history(user);
			continue;
		}
		else if (input == 5) {
			//show_detail(user);
			continue;
		}
		else if (input == 6) {
			return;
		}
	}
}

void InfoMenu::printMenu()
{
	putnch('\n', 2);
	putnch('=', 45);
	wcout << L"1.View My Info 2.Modify My Info 3.Recharge 4.Return to Main Menu" << endl;
	putnch('=', 45);
}
void InfoMenu::inputloop(UserData* user)
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
			//show_info(user);
			continue;
		}
		else if (input == 2) {
			//modify_info(user);
			continue;
		}
		else if (input == 3) {
			//recharge(user);
			continue;
		}
		else if (input == 4) {
			return;
		}
	}
}