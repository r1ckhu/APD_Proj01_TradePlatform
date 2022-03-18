#pragma once
#include "Menu.h"
#include "User.h"
#include "Data.h"
#include <sstream>
using namespace std;
extern UserHandler userhandler;
extern SQL_Interpreter sql_interpreter;
extern DataHandler datahandler;

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
		printMenu();
		wprintf(L"Please choose an operation:");
		InputHandler::inputCommand(input, 1, 6);
		if (input == 1) {
			show_commodity(user);
			continue;
		}
		else if (input == 2) {
			buy_commodity(user);
			continue;
		}
		else if (input == 3) {
			search_commodity(user);
			continue;
		}
		else if (input == 4) {
			show_history(user);
			continue;
		}
		else if (input == 5) {
			show_detail(user);
			continue;
		}
		else if (input == 6) {
			return;
		}
	}
}

void BuyerMenu::show_commodity(UserData* user)
{
	wstring command(L"SELECT * FROM commodity");
	list<CommodityData>* _list = (list<CommodityData>*)sql_interpreter.interpret(command);
	sql_interpreter.interpret(command);
	sql_interpreter.log(command);
	formatting_output(_list, true);
}

void BuyerMenu::buy_commodity(UserData* user)
{
	// TODO: offshelf commodity & no order
	wstring id;
	int quantity = 0;
	wprintf(L"Please enter the commodity's id:");
	if (!InputHandler::inputString(id, 4, true, true)) {/*id*/
		InputHandler::throwError();
		return;
	}
	wprintf(L"Please enter the quantity:");
	if (!InputHandler::inputInt(quantity)) {
		InputHandler::throwError();
		return;
	}
	Table<CommodityData>* table = datahandler.get_commodity_table();
	CommodityData* cd = table->find_byID(id);
	if (cd != nullptr)
	{
		if (user->get_balance() < cd->get_price() * quantity) {
			wprintf(L"-----Insufficient balance in your account! Operation Terminated.-----");
			return;
		}
		else if (cd->get_commodity_state() == OFF_SHELF) {
			wprintf(L"-----No commodity found! Operation Terminated.-----");
			return;
		}
		else if (quantity > cd->get_quantity())
		{
			wprintf(L"-----Insufficient quantity! Operation Terminated.-----");
			return;
		}
		wprintf(L"The commodity you choose:\n");
		putnch('*', 30);
		wprintf(L"The commodity ID is: ");
		wcout << cd->get_id() << endl;
		wprintf(L"The commodity name is: ");
		wcout << cd->name << endl;
		wprintf(L"The transaction time is:");
		wcout << datahandler.get_current_time() << endl;
		wprintf(L"The quantity you choose is:");
		wcout << quantity << endl;
		wprintf(L"Your balance after purchasing is: ");
		wcout << user->get_balance() - cd->get_price() * quantity << endl;
		putnch('*', 30);
		wprintf(L"Please confirm your choice (y/n): ");
		wchar_t sign;
		InputHandler::inputConfirm(sign);
		if (sign == 'y')
		{
			user->set_balance(user->get_balance() - cd->get_price() * quantity);
			wstringstream wss;
			wss << L"INSERT INTO order VALUES (" << datahandler.generate_order_id() << ',' \
				<< id << ',' << cd->get_price() << ','\
				<< cd->get_quantity() - quantity << ',' << datahandler.get_current_time() << ',' << cd->get_seller_id() \
				<< ',' << user->get_id() << ')';
			wstring command;
			command = wss.str();
			sql_interpreter.interpret(command);
			sql_interpreter.log(command);
			wss.str(L" ");
			wss.seekg(0);
			wss << L"UPDATE commodity SET number = " << cd->get_quantity() - quantity \
				<< " WHERE commodityID = " << id;
			command = wss.str();
			sql_interpreter.interpret(command);
			sql_interpreter.log(command);
			if (cd->get_quantity() == 0)
			{
				command = L"UPDATE commodity SET state = offShelf WHERE commodityID = ";
				command += id;
				sql_interpreter.interpret(command);
				sql_interpreter.log(command);
			}
			wprintf(L"-----Purchase successful!-----");
		}
	}
	else {
		wprintf(L"No commodity found! Operation Terminated.");
	}
}

void BuyerMenu::search_commodity(UserData* user)
{
	wstring name;
	wprintf(L"Please enter a commodity's name:");
	if (!InputHandler::inputString(name, 20, false, true)) { //name
		InputHandler::throwError();
		return;
	}
	wstring command(L"SELECT * FROM commodity WHERE commodityName CONTAINS ");
	command += name;
	list<CommodityData>* _list = (list<CommodityData>*)sql_interpreter.interpret(command);
	formatting_output(_list, true);
	sql_interpreter.interpret(command);
	delete _list;
}

void BuyerMenu::show_history(UserData* user)
{
	wstring command(L"SELECT * FROM order WHERE buyerID CONTAINS" + user->get_id());
	list<OrderData>* _list = (list<OrderData>*)sql_interpreter.interpret(command);
	formatting_output(_list);
	command = L"SELECT * FROM order";
	sql_interpreter.log(command);
	delete _list;
}

void BuyerMenu::show_detail(UserData* user)
{
	wstring id;
	wprintf(L"Please enter the commodityID:");
	if (!InputHandler::inputString(id, 4, true, true)) {/*id*/
		InputHandler::throwError();
		return;
	}
	CommodityData* cd = datahandler.get_commodity_table()->find_byID(id);
	putnch('*', 30);
	wcout << L"The commodity ID is: " << cd->get_id() << endl;
	wcout << L"The commodity name is: " << cd->name << endl;
	wcout << L"The commodity description is: " << cd->description << endl;
	wcout << L"On sell time is: " << cd->time_on_shelf << endl;
	wcout << L"The price is: " << cd->get_price() << endl;
	wcout << L"The seller ID is:" << cd->get_seller_id() << endl;
	putnch('*', 30);
}
