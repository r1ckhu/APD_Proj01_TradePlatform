#pragma once
#include "Data.h"
class Menu
{
public:
	virtual void inputloop(UserData* user) = 0;
	virtual void printMenu() = 0;
	void putnch(char ch, int n, bool changeline = true);
	void putnch(wchar_t wch, int n, bool changeline = true);
};

class DefaultMenu : public Menu
{
public:
	void inputloop(UserData* user);
	void printMenu();
};

class AdminMenu : public Menu
{
public:
	void printMenu();
	void inputloop(UserData* user);
};

class UserMenu : public Menu
{
public:
	void printMenu();
	void inputloop(UserData* user);
};

class BuyerMenu : public Menu
{
public:
	void printMenu();
	void inputloop(UserData* user);
	void show_commodity(UserData* user);
	void buy_commodity(UserData* user);
	void search_commodity(UserData* user);
	void show_history(UserData* user);
	void show_detail(UserData* user);
};

class SellerMenu : public Menu
{
public:
	void inputloop(UserData* user);
	void printMenu();
	void put_commodity(UserData* user);
	void show_commodity(UserData* user);
	void modify_commodity(UserData* user);
	void remove_commodity(UserData* user);
	void show_history(UserData* user);
};

class InfoMenu : public Menu
{
public:
	void inputloop(UserData* user);
	void printMenu();
	void show_info(UserData* user);
	void modify_info(UserData* user);
	void recharge(UserData* user);
};
