#pragma once
#include "Menu.h"
#include "User.h"
#include <sstream>
using namespace std;
extern UserHandler userhandler;
extern SQL_Interpreter sql_interpreter;
extern DataHandler datahandler;

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
			put_commodity(user);
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

void SellerMenu::put_commodity(UserData* user)
{
	wstring command;
	wstring name, description;
	float price;
	int quantity;
	wprintf(L"Please enter commodity name:");
	wcin >> name;
	wprintf(L"Please enter unit price:");
	wcin >> price;
	wprintf(L"Please enter quantity:");
	wcin >> quantity;
	wprintf(L"Please enter description:");
	wcin >> description;
	putnch('*', 25);
	wcout << L"Commodity name: " << name << endl;
	wcout << L"Commodity price: " << price << endl;;
	wcout << L"Commodity quantity: " << quantity << endl;
	wcout << L"Commodity description: " << description << endl;
	wprintf(L"\nPlease confirm your choice (y/n):");
	wchar_t sign;
	wcin >> sign;
	if (sign == 'y') {
		wstringstream wss;
		wss << L"INSERT INTO commodity VALUES (" << datahandler.generate_commodity_id() \
			<<',' << name << ',' << price << ',' << \
			quantity << ',' << description << ',' \
			<< user->get_id() << ',' << datahandler.get_current_time() << ',' <<"onSale"<<')';
		command = wss.str();
		sql_interpreter.interpret(command);
		wprintf(L"Operation Successful!\n\n");
	}
	else {
		wprintf(L"Operation Terminated!\n\n");
	}
}