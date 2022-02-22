#pragma once
#include "Data.h"
class Menu
{
public:
	virtual void inputloop() = 0;
};

class DefaultMenu : public Menu
{
public:
	void inputloop(UserData* user);
};

class AdminMenu : public Menu
{
public:
	void inputloop(UserData* user);
};

class UserMenu : public Menu
{
public:
	void inputloop(UserData* user);
};

class BuyerMenu : public Menu
{
public:
	void inputloop(UserData* user);
};

class SellerMenu : public Menu
{
public:
	void inputloop(UserData* user);
};

class InfoMenu : public Menu
{
public:
	void inputloop(UserData* user);
};
