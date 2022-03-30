#include "Menu.h"
#include "User.h"
using namespace std;
extern UserHandler userhandler;
extern SQL_Interpreter sql_interpreter;

void UserMenu::printMenu()
{
	putnch('\n', 2);
	putnch('=', 70);
	wcout << L"1.I am a Buyer 2.I am a Seller 3.Manage Personal Info 4.Chat 5.Logout" << endl;
	putnch('=', 70);
}
void UserMenu::inputloop(UserData* user)
{
	int input = 0;
	while (true) {
		printMenu();
		wprintf(L"Please choose an operation:");
		InputHandler::inputCommand(input, 1, 5);
		if (input == 1) {
			BuyerMenu buyermenu;
			buyermenu.inputloop(user);
		}
		else if (input == 2) {
			SellerMenu sellermenu;
			sellermenu.inputloop(user);
		}
		else if (input == 3) {
			InfoMenu infomenu;
			infomenu.inputloop(user);
			continue;
		}
		else if (input == 4) {
			ChatMenu chatmenu;
			chatmenu.inputloop(user);
		}
		else if (input == 5) {
			return;
		}
	}
}