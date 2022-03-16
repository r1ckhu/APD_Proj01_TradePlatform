#include "Menu.h"
#include "User.h"
#include <sstream>
using namespace std;
extern UserHandler userhandler;
extern SQL_Interpreter sql_interpreter;
extern DataHandler datahandler;
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
			show_info(user);
			continue;
		}
		else if (input == 2) {
			modify_info(user);
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
	wcout << user->get_balance() << endl;
	putnch('*', 30);
}

void InfoMenu::modify_info(UserData* user)
{
	wstring command;
	wstring name, contact, address;
	wchar_t sign;
	wprintf(L"Please the attribute to be modified ( 1 for Name / 2 for Contact / 3 for Address):");
	wcin >> sign;
	if (sign == '1') {
		wprintf(L"Please enter new name:");
		wcin >> name;
		putnch('*', 25);
		wcout << L"Your name wiil be: " << name << endl;
		putnch('*', 25);
		wprintf(L"\nPlease confirm your choice (y/n):");
		wcin >> sign;
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
	else if (sign == '2')
	{
		wprintf(L"Please enter new phone number:");
		wcin >> contact;
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
	else if (sign == '3')
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
			wss << L"UPDATE user SET address = " << address<< " WHERE userID = "
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