#include "Menu.h"
#include "User.h"
using namespace std;
extern UserHandler userhandler;
extern SQL_Interpreter sql_interpreter;
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