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
	wcout << L"1.管理员登录 2.用户注册 3.用户登录 4.退出程序" << endl;
	putnch('=', 47);
}

void DefaultMenu::inputloop(UserData* user)
{
	int input = 0;
	while (true) {
		printMenu();
		wprintf(L"请输入操作:");
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
	wcout << L"1.查看所有用户 2.搜索商品 3.下架商品 4.查看所有订单 5.查看所有用户 6.封禁用户 7.注销" << endl;
	putnch('=', 100);
}
void AdminMenu::inputloop(UserData *user)
{
	int input = 0;
	while (true) {
		printMenu();
		wprintf(L"请输入操作:");
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
	wcout << L"1.我是买家 2.我是卖家 3.个人信息管理 4.注销登录" << endl;
	putnch('=', 49);
}
void UserMenu::inputloop(UserData* user)
{
	int input = 0;
	while (true) {
		printMenu();
		wprintf(L"请输入操作:");
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
	wcout << L"1.发布商品 2.查看发布商品 3.修改商品信息 4.下架商品 5.查看历史订单 6.返回用户主界面" << endl;
	putnch('=', 85);
}
void SellerMenu::inputloop(UserData* user)
{
	int input = 0;
	while (true) {
		printMenu();
		wprintf(L"请输入操作:");
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
	wcout << L"1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.返回用户主界面" << endl;
	putnch('=', 89);
}
void BuyerMenu::inputloop(UserData* user)
{
	int input = 0;
	while (true) {
		printMenu();
		wprintf(L"请输入操作:");
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
	wcout << L"1.查看信息 2.修改信息 3.充值 4.返回用户主界面" << endl;
	putnch('=', 45);
}
void InfoMenu::inputloop(UserData* user)
{
	int input = 0;
	while (true) {
		printMenu();
		wprintf(L"请输入操作:");
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