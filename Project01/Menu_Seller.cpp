#include "Menu.h"
#include "User.h"
using namespace std;
extern UserHandler userhandler;
extern SQL_Interpreter sql_interpreter;

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