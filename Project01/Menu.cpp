#pragma once
#include "Menu.h"
#include "User.h"
extern UserHandler userhandler;
using namespace std;

void Menu::putnch(char ch, int n, bool changeline)
{
	for (int i = 1; i <= n; i++)
		printf("%c", ch);
	if (changeline)
		printf("\n");
}

void Menu::putnch(wchar_t ch, int n, bool changeline)
{
	for (int i = 1; i <= n; i++)
		wprintf(L"%lc", ch);
	if (changeline)
		wprintf(L"\n");
}

void DefaultMenu::printMenu()
{
	putnch('=', 47);
	wcout << L"1.����Ա��¼ 2.�û�ע�� 3.�û���¼ 4.�˳�����" << endl;
	putnch('=', 47);
}

void DefaultMenu::inputloop(UserData* user)
{
	int input = 0;
	while (true) {
		printMenu();
		wprintf(L"���������:");
		cin >> input;
		if (input == 1) {
			UserData* user = userhandler.adminlogin();
			if (user != nullptr) {
				AdminMenu adminmenu;
				adminmenu.inputloop(user);
			}
		}
		else if (input == 2) {
			// TODO: user register
			continue;
		}
		else if (input == 3) {
			userhandler.userlogin();
			continue;
		}
		else if (input == 4) {
			exit(0);
		}
	}
};


void AdminMenu::printMenu()
{
	putnch('=', 100);
	wcout << L"1.�鿴�����û� 2.������Ʒ 3.�¼���Ʒ 4.�鿴���ж��� 5.�鿴�����û� 6.����û� 7.ע��" << endl;
	putnch('=', 100);
}
void AdminMenu::inputloop(UserData *user)
{
	int input = 0;
	while (true) {
		printMenu();
		wprintf(L"���������:");
		cin >> input;
		if (input == 1) {
			continue;
		}
		else if (input == 2) {
			continue;
		}
		else if (input == 3) {
			continue;
		}
		else if (input == 4) {
			continue;
		}
		else if (input == 5) {
			continue;
		}
		else if (input == 6) {
			continue;
		}
		else if (input == 7) {
			return;
		}
	}
}

void UserMenu::printMenu()
{
	putnch('=', 49);
	wcout << L"1.������� 2.�������� 3.������Ϣ���� 4.ע����¼" << endl;
	putnch('=', 49);
}
void UserMenu::inputloop(UserData* user)
{
	int input = 0;
	while (true) {
		printMenu();
		wprintf(L"���������:");
		cin >> input;
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
			return;
		}
	}
}

void SellerMenu::printMenu()
{
	putnch('=', 85);
	wcout << L"1.������Ʒ 2.�鿴������Ʒ 3.�޸���Ʒ��Ϣ 4.�¼���Ʒ 5.�鿴��ʷ���� 6.�����û�������" << endl;
	putnch('=', 85);
}
void SellerMenu::inputloop(UserData* user)
{
	int input = 0;
	while (true) {
		printMenu();
		wprintf(L"���������:");
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

void BuyerMenu::printMenu()
{
	putnch('=', 89);
	wcout << L"1.�鿴��Ʒ�б� 2.������Ʒ 3.������Ʒ 4.�鿴��ʷ���� 5.�鿴��Ʒ��ϸ��Ϣ 6.�����û�������" << endl;
	putnch('=', 89);
}
void BuyerMenu::inputloop(UserData* user)
{
	int input = 0;
	while (true) {
		printMenu();
		wprintf(L"���������:");
		cin >> input;
		if (input == 1) {
			//show_commodity(user);
			continue;
		}
		else if (input == 2) {
			//buy_commodity(user);
			continue;
		}
		else if (input == 3) {
			//search_commodity(user);
			continue;
		}
		else if (input == 4) {
			//show_history(user);
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

void InfoMenu::printMenu()
{
	putnch('=', 45);
	wcout << L"1.�鿴��Ϣ 2.�޸���Ϣ 3.��ֵ 4.�����û�������" << endl;
	putnch('=', 45);
}
void InfoMenu::inputloop(UserData* user)
{
	int input = 0;
	while (true) {
		printMenu();
		wprintf(L"���������:");
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