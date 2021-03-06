#pragma once
#include "Menu.h"
#include "User.h"
using namespace std;
extern UserHandler userhandler;
extern SQL_Interpreter sql_interpreter;
void AdminMenu::printMenu()
{
	putnch('\n', 2);
	putnch('=', 63);
	wcout << L"1.View All Commodities 2.Search Commodities 3.Remove Commodity" << endl << endl;
	wcout << L"4.View All Orders 5.View All Users 6.Ban Users 7.Sign Out" << endl;
	putnch('=', 63);
}
void AdminMenu::inputloop(UserData* user)
{
	int input = 0;
	while (true) {
		printMenu();
		wprintf(L"Please choose an operation:");
		InputHandler::inputCommand(input, 1, 7);
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
			ban_user();
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
	sql_interpreter.log(command);
	list<CommodityData>* _list = (list<CommodityData>*)sql_interpreter.interpret(command);
	formatting_output(_list);
}

void AdminMenu::search_commodity()
{
	wstring name;
	wprintf(L"Please enter a commodity's name:");
	if (!InputHandler::inputString(name, 20, false, true)) { //name
		InputHandler::throwError();
		return;
	}
	wstring command(L"SELECT * FROM commodity WHERE commodityName CONTAINS ");
	command += name;
	list<pair<CommodityData, int>>* _list = (list<pair<CommodityData, int>>*)sql_interpreter.interpret(command);
	sql_interpreter.log(command);
	formatting_output(_list);
	delete _list;
}

void AdminMenu::remove_commodity()
{
	wstring id;
	wprintf(L"Please enter a commodity's id:");
	if (!InputHandler::inputString(id, 4, true, true)) {/*id*/
		InputHandler::throwError();
		return;
	}
	wstring command(L"SELECT * FROM commodity WHERE commodityID CONTAINS ");
	command += id;
	wprintf(L"This is the commodity you select:\n");
	list<CommodityData>* _list = (list<CommodityData>*)sql_interpreter.interpret(command);
	formatting_output(_list);
	if (_list->size() != 0)
	{
		sql_interpreter.log(command);
		wprintf(L"Please Confirm your choice (y/n):");
		wchar_t sign;
		InputHandler::inputConfirm(sign);
		if (sign == 'y') {
			command = L"UPDATE commodity SET state = removed WHERE commodityID = ";
			command += id;
			sql_interpreter.interpret(command);
			wprintf(L"Operation Successful!\n\n");
		}
		else {
			wprintf(L"Operation Terminated!\n\n");
		}
	}
	delete _list;
}

void AdminMenu::show_orders()
{
	wstring command(L"SELECT * FROM order");
	list<OrderData>* _list = (list<OrderData>*)sql_interpreter.interpret(command);
	sql_interpreter.interpret(command);
	formatting_output(_list);
}

void AdminMenu::show_users()
{
	wstring command(L"SELECT * FROM user");
	list<UserData>* _list = (list<UserData>*)sql_interpreter.interpret(command);
	sql_interpreter.interpret(command);
	formatting_output(_list);
}

void AdminMenu::ban_user()
{
	wstring id;
	wprintf(L"Please enter a user's id:");
	if (!InputHandler::inputString(id, 4, true, true)) {/*id*/
		InputHandler::throwError();
		return;
	}
	wstring command(L"SELECT * FROM user WHERE userID CONTAINS ");
	command += id;
	wprintf(L"This is the user you select:\n");
	list<UserData>* _list = (list<UserData>*)sql_interpreter.interpret(command);
	formatting_output(_list);
	if (_list->size() != 0)
	{
		sql_interpreter.interpret(command);
		wprintf(L"Please Confirm your choice (y/n):");
		wchar_t sign;
		InputHandler::inputConfirm(sign);
		if (sign == 'y') {
			command = L"UPDATE user SET userState = inactive WHERE userID = ";
			command += id;
			sql_interpreter.interpret(command);
			wprintf(L"Operation Successful!\n\n");
			command = L"UPDATE commodity SET state = removed WHERE sellerID = ";
			command += id;
			sql_interpreter.interpret(command);
		}
		else {
			wprintf(L"Operation Terminated!\n\n");
		}
	}
	delete _list;
}