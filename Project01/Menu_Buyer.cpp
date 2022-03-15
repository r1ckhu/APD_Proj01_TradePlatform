#pragma once
#include "Menu.h"
#include "User.h"
using namespace std;
extern UserHandler userhandler;
extern SQL_Interpreter sql_interpreter;

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
			show_commodity(user);
			continue;
		}
		else if (input == 2) {
			//buy_commodity(user);
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
			//show_detail(user);
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
	// TODO: datahandler need get commodity funciton
}

void BuyerMenu::search_commodity(UserData* user)
{
	wstring name;
	wprintf(L"Please enter a commodity's name:");
	wcin >> name;
	wstring command(L"SELECT * FROM commodity WHERE commodityName CONTAINS ");
	command += name;
	list<CommodityData>* _list = (list<CommodityData>*)sql_interpreter.interpret(command);
	formatting_output(_list, true);
	sql_interpreter.interpret(command);
	delete _list;
}

void BuyerMenu::show_history(UserData* user)
{
	// Dismatched command 
	wstring command(L"SELECT * FROM order WHERE buyerID CONTAINS" + user->get_id());
	list<OrderData>* _list = (list<OrderData>*)sql_interpreter.interpret(command);
	formatting_output(_list);
	command = L"SELECT * FROM order";
	sql_interpreter.log(command);
	delete _list;
}

