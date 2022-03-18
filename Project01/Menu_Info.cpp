#include "Menu.h"
#include "User.h"
#include "Calculator.h"
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;
extern UserHandler userhandler;
extern SQL_Interpreter sql_interpreter;
extern DataHandler datahandler;
extern Calculator calculator;
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
		printMenu();
		wprintf(L"Please choose an operation:");
		InputHandler::inputCommand(input, 1, 4);
		if (input == 1) {
			show_info(user);
			continue;
		}
		else if (input == 2) {
			modify_info(user);
			continue;
		}
		else if (input == 3) {
			recharge(user);
			continue;
		}
		else if (input == 4) {
			return;
		}
	}
}

void InfoMenu::show_info(UserData* user)
{
	putnch('*', 30);
	wprintf(L"Your User ID is: ");
	wcout << user->get_id() << endl;
	wprintf(L"Your name is: ");
	wcout << user->name << endl;
	wprintf(L"Your contact is: %d\n", user->contact);
	wprintf(L"Your address is: ");
	wcout << user->address << endl;
	wprintf(L"Your balance is: ");
	wcout << cal_balance(user) << endl;
	putnch('*', 30);
}

void InfoMenu::modify_info(UserData* user)
{
	wstring command;
	wstring name, contact, address;
	int isign;
	wchar_t sign;
	wprintf(L"Please the attribute to be modified ( 1 for Name / 2 for Contact / 3 for Address):");
	if (!InputHandler::inputCommand(isign, 1, 3)) {
		InputHandler::throwError();
		return;
	}
	if (isign == 1) {
		wprintf(L"Please enter new name:");
		if (!InputHandler::inputString(name, 10, false, true)) { //name
			InputHandler::throwError();
			return;
		}
		putnch('*', 25);
		wcout << L"Your name wiil be: " << name << endl;
		putnch('*', 25);
		wprintf(L"\nPlease confirm your choice (y/n):");
		InputHandler::inputConfirm(sign);
		UserData* possible_user = datahandler.get_user_table()->find_byName(name);
		if (sign == 'y' && possible_user == nullptr) {
			wstringstream wss;
			wss << L"UPDATE user SET username = " << name << " WHERE userID = "
				<< user->get_id();
			command = wss.str();
			sql_interpreter.interpret(command);
			sql_interpreter.log(command);
			wprintf(L"Operation Successful!\n\n");
		}
		else if (possible_user != nullptr) {
			wprintf(L"This name has been used by others! Choose a new one.\n\n");
		}
		else {
			wprintf(L"Operation Terminated!\n\n");
		}
	}
	else if (isign == 2)
	{
		wprintf(L"Please enter new phone number:");
		// Stop here
		putnch('*', 25);
		wcout << L"Your phone number wiil be: " << contact << endl;
		putnch('*', 25);
		wprintf(L"\nPlease confirm your choice (y/n):");
		wcin >> sign;
		if (sign == 'y') {
			wstringstream wss;
			wss << L"UPDATE user SET phoneNumber = " << contact << " WHERE userID = "
				<< user->get_id();
			command = wss.str();
			sql_interpreter.interpret(command);
			sql_interpreter.log(command);
			wprintf(L"Operation Successful!\n\n");
		}
		else {
			wprintf(L"Operation Terminated!\n\n");
		}
	}
	else if (isign == 3)
	{
		wprintf(L"Please enter new address:");
		wcin >> address;
		putnch('*', 25);
		wcout << L"Your address wiil be: " << address << endl;
		putnch('*', 25);
		wprintf(L"\nPlease confirm your choice (y/n):");
		wcin >> sign;
		if (sign == 'y') {
			wstringstream wss;
			wss << L"UPDATE user SET address = " << address << " WHERE userID = "
				<< user->get_id();
			command = wss.str();
			sql_interpreter.interpret(command);
			sql_interpreter.log(command);
			wprintf(L"Operation Successful!\n\n");
		}
		else {
			wprintf(L"Operation Terminated!\n\n");
		}
	}
}

void InfoMenu::recharge(UserData* user)
{
	float money = 0.0;
	wprintf(L"Please enter the amount you want to recharge: ");
	wcin >> money;
	user->set_balance(user->get_balance() + money);
	wofstream out_balance(fpath_balance, ios::app);
	out_balance << user->get_id() << ' ' << money << endl;
	wprintf(L"Successful! Now you have: %.f", user->get_balance());
	wstringstream wss;
	wss << L"UPDATE user SET balance = " << user->get_balance() << L" WHERE userID = " << user->get_id();
	wstring command;
	command = wss.str();
	sql_interpreter.interpret(command);
	out_balance.close();
}

float InfoMenu::cal_balance(UserData* user)
{
	map<int, vector<float>> map_exp;
	Table<OrderData>* tod = datahandler.get_order_table();
	for (list<OrderData>::iterator it = tod->_list.begin(); it != tod->_list.end(); it++) {
		if ((*it).seller_id == user->get_id() || (*it).buyer_id == user->get_id()) {
			float val = ((*it).seller_id == user->get_id()) ? (*it).price : -(*it).price;
			int mul = (*it).quantity;
			map<int, vector<float>>::iterator itt = map_exp.find(mul);
			if (itt != map_exp.end()) {
				itt->second.push_back(val);
			}
			else {
				vector<float> v;
				v.push_back(val);
				map_exp.insert(pair<int, vector<float>>(mul, v));
			}
		}

	}
	wifstream in_balance(fpath_balance, ios::in);
	wstring id;
	float val = 0.0;
	while (in_balance >> id >> val) {
		if (id == user->get_id()) {
			map<int, vector<float>>::iterator itt = map_exp.find(1);
			if (itt != map_exp.end()) {
				itt->second.push_back(val);
			}
			else {
				vector<float> v;
				v.push_back(val);
				map_exp.insert(pair<int, vector<float>>(1, v));
			}
		}
	}
	wstring exp;
	wstringstream wss;
	map<int, vector<float>>::iterator itt;
	for (itt = map_exp.begin(); itt != map_exp.end(); itt++) {
		wss << (*itt).first << '*' << '(';
		for (vector<float>::iterator vit = (*itt).second.begin(); vit != (*itt).second.end(); vit++) {
			if (vit == (*itt).second.begin())
				wss << (*vit);
			else {
				if (*vit >= 0)
					wss << '+' << (*vit);
				else
					wss << (*vit);
			}
		}
		wss << ')' << '+';
	}
	wss << '0';
	exp = wss.str();
	float ans = calculator.calexp(exp);
	return ans;
}