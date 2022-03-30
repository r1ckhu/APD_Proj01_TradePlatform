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
	putnch('=', 68);
	wcout << L"1.Release an Commodity 2.View my Commodities 3.Modify CommodityInfo" << endl << endl;
	wcout << L"4.Remove Commodity 5.View History Orders 6.Return to Main Menu" << endl;
	putnch('=', 68);
}
void SellerMenu::inputloop(UserData* user)
{
	int input = 0;
	while (true) {
		printMenu();
		wprintf(L"Please choose an operation:");
		InputHandler::inputCommand(input, 1, 6);
		if (input == 1) {
			put_commodity(user);
			continue;
		}
		else if (input == 2) {
			show_commodity(user);
			continue;
		}
		else if (input == 3) {
			modify_commodity(user);
			continue;
		}
		else if (input == 4) {
			remove_commodity(user);
			continue;
		}
		else if (input == 5) {
			show_history(user);
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
	if (!InputHandler::inputString(name, 20, false, true)) { //name
		InputHandler::throwError();
		return;
	}
	wprintf(L"Please enter unit price:");
	if (!InputHandler::inputFloat(price)) {
		InputHandler::throwError();
		return;
	}
	wprintf(L"Please enter quantity:");
	if (!InputHandler::inputInt(quantity)) {
		InputHandler::throwError();
		return;
	}
	wprintf(L"Please enter description:");
	if (!InputHandler::inputString(description, 200, false, true)) {
		InputHandler::throwError();
		return;
	}
	putnch('*', 25);
	wcout << L"Commodity name: " << name << endl;
	wcout << L"Commodity price: " << price << endl;;
	wcout << L"Commodity quantity: " << quantity << endl;
	wcout << L"Commodity description: " << description << endl;
	putnch('*', 25);
	wprintf(L"\nPlease confirm your choice (y/n):");
	wchar_t sign;
	InputHandler::inputConfirm(sign);
	if (sign == 'y') {
		wstringstream wss;
		wss << L"INSERT INTO commodity VALUES (" << datahandler.generate_commodity_id() \
			<< ',' << name << ',' << price << ',' << \
			quantity << ',' << description << ',' \
			<< user->get_id() << ',' << datahandler.get_current_time() << ',' << "onSale" << ')';
		command = wss.str();
		sql_interpreter.interpret(command);
		sql_interpreter.log(command);
		wprintf(L"Operation Successful!\n\n");
	}
	else {
		wprintf(L"Operation Terminated!\n\n");
	}
}

void SellerMenu::show_commodity(UserData* user)
{
	wstring command(L"SELECT * FROM commodity WHERE sellerID CONTAINS ");
	command += user->get_id();
	list<CommodityData>* _list = (list<CommodityData>*)sql_interpreter.interpret(command);
	formatting_output(_list);
	command = L"SELECT * FROM commodity";
	sql_interpreter.log(command);
	delete _list;
}

void SellerMenu::modify_commodity(UserData* user)
{
	wstring command;
	wstring id, description;
	float price = 0.0;
	int isign;
	wchar_t sign;
	wprintf(L"Please enter the commodity's id:");
	if (!InputHandler::inputString(id, 4, true, true)) {
		InputHandler::throwError();
		return;
	}
	CommodityData* cd = datahandler.get_commodity_table()->find_byID(id);
	if (cd == nullptr) {
		wprintf(L"No Commodity Found!\n");
		return;
	}
	if (cd->get_seller_id() != user->get_id()) {
		wprintf(L"----You can not modify other's commodity!----\n");
		return;
	}
	wprintf(L"Please the attribute to be modified ( 1 for Price / 2 for Description):");
	InputHandler::inputCommand(isign, 1, 2);
	if (isign == 1) {
		wprintf(L"Please enter new price:");
		if (!InputHandler::inputFloat(price)) {
			InputHandler::throwError();
			return;
		}
		putnch('*', 25);
		wcout << L"The commodity to be modified 's ID: " << id << endl;
		wcout << L"The new price: " << price << endl;;
		putnch('*', 25);
		wprintf(L"\nPlease confirm your choice (y/n):");
		InputHandler::inputConfirm(sign);
		if (sign == 'y') {
			wstringstream wss;
			wss << L"UPDATE commodity SET price = " << price << " WHERE commodityID = "
				<< id;
			command = wss.str();
			sql_interpreter.interpret(command);
			sql_interpreter.log(command);
			wprintf(L"Operation Successful!\n\n");
		}
		else {
			wprintf(L"Operation Terminated!\n\n");
		}
	}
	else if (isign == 2) {
		wprintf(L"Please enter description:");
		if (!InputHandler::inputString(description, 200, false, true)) {
			InputHandler::throwError();
			return;
		}
		putnch('*', 25);
		wcout << L"The commodity to be modified 's ID: " << id << endl;
		wcout << L"The new description: " << description << endl;;
		putnch('*', 25);
		wprintf(L"\nPlease confirm your choice (y/n):");
		InputHandler::inputConfirm(sign);
		if (sign == 'y') {
			wstringstream wss;
			wss << L"UPDATE commodity SET description = " << description << " WHERE commodityID = "
				<< id;
			command = wss.str();
			sql_interpreter.interpret(command);
			sql_interpreter.log(command);
			wprintf(L"Operation Successful!\n\n");
		}
		else {
			wprintf(L"Operation Terminated!\n\n");
		}
	}
	else {
		wprintf(L"Invaild Input! Operation Terminated.");
	}
}

void SellerMenu::remove_commodity(UserData* user)
{
	wstring id;
	wprintf(L"Please enter a commodity's id:");
	if (!InputHandler::inputString(id, 4, true, true)) {/*id*/
		InputHandler::throwError();
		return;
	}
	CommodityData* cd = datahandler.get_commodity_table()->find_byID(id);
	if (cd == nullptr) {
		wprintf(L"No Commodity Found!\n");
		return;
	}
	if (cd->get_seller_id() != user->get_id()) {
		wprintf(L"----You can not remove other's commodity!----\n");
		return;
	}
	wstring command(L"SELECT * FROM commodity WHERE commodityID CONTAINS ");
	command += id;
	wprintf(L"This is the commodity you select:\n");
	list<CommodityData>* _list = (list<CommodityData>*)sql_interpreter.interpret(command);
	formatting_output(_list);
	if (_list->size() != 0)
	{
		wprintf(L"Please Confirm your choice (y/n):");
		wchar_t sign;
		InputHandler::inputConfirm(sign);
		if (sign == 'y') {
			command = L"UPDATE commodity SET state = removed WHERE commodityID = ";
			command += id;
			sql_interpreter.interpret(command);
			sql_interpreter.log(command);
			wprintf(L"Operation Successful!\n\n");
		}
		else {
			wprintf(L"Operation Terminated!\n\n");
		}
	}
	delete _list;
}

void SellerMenu::show_history(UserData* user)
{
	wstring command(L"SELECT * FROM order WHERE sellerID CONTAINS" + user->get_id());
	list<OrderData>* _list = (list<OrderData>*)sql_interpreter.interpret(command);
	formatting_output(_list);
	command = L"SELECT * FROM order";
	sql_interpreter.log(command);
	delete _list;
}