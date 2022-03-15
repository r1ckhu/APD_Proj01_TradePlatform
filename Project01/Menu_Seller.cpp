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
	// TODO: Dismatched command
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
	wchar_t sign;
	wprintf(L"Please enter the commodity's id:");
	wcin >> id;
	wprintf(L"Please the attribute to be modified ( 1 for Price / 2 for Description):");
	wcin >> sign;
	if (sign == '1') {
		wprintf(L"Please enter new price:");
		wcin >> price;
		// Dismatched output
		putnch('*', 25);
		wcout << L"The commodity to be modified 's ID: " << id << endl;
		wcout << L"The new price: " << price << endl;;
		putnch('*', 25);
		wprintf(L"\nPlease confirm your choice (y/n):");
		wcin >> sign;
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
	else if (sign == '2') {
		wprintf(L"Please enter description:");
		wcin >> description;
		putnch('*', 25);
		wcout << L"The commodity to be modified 's ID: " << id << endl;
		wcout << L"The new description: " << description << endl;;
		putnch('*', 25);
		wprintf(L"\nPlease confirm your choice (y/n):");
		wcin >> sign;
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
	// TODO: need to confirm is seller's product
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
			sql_interpreter.log(command);
			wprintf(L"Operation Successful!\n\n");
		}
		else {
			wprintf(L"Operation Terminated!\n\n");
		}
	}
	delete _list;
}

void SellerMenu::show_history(UserData *user)
{
	// Dismatched command 
	wstring command(L"SELECT * FROM order WHERE sellerID CONTAINS" +user->get_id());
	list<OrderData>* _list = (list<OrderData>*)sql_interpreter.interpret(command);
	formatting_output(_list);
	command = L"SELECT * FROM order";
	sql_interpreter.log(command);
	delete _list;
}