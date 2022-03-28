#pragma once
#include "Data.h"
#include "InputHandler.h"
#include "Calculator.h"
#include <iomanip>
#include <sstream>

class Menu
{
public:
	virtual void inputloop(UserData* user) = 0;
	virtual void printMenu() = 0;
	void putnch(char ch, int n, bool changeline = true);
	void putnch(wchar_t wch, int n, bool changeline = true);
	void formatting_output(list<CommodityData>* _list, bool onlyOnSale = false);
	void formatting_output(list<pair<CommodityData, int>>* _list);
	void formatting_output(list<UserData>* _list);
	void formatting_output(list<UserData>* _list, UserData* user);
	void formatting_output(list<OrderData>* _list);
	void formatting_output(list<OrderData>* _list, UserData* user);
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
	void show_commodity();
	void search_commodity();
	void remove_commodity();
	void show_orders();
	void show_users();
	void ban_user();
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
	void check_cart(UserData* user);
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
	float cal_balance(UserData* user);
};
