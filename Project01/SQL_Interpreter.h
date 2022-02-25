#pragma once
#include <string>
#include <list>
#include "Data.h"
using namespace std;
class CommodityData;
class OrderData;
class UserData;
class SQL_Interpreter
{
public:
	void interpret(wstring& statement);
private:
	void update_commodity(wstringstream& values, CommodityData& dst);
	void update_order(wstringstream& values, OrderData& dst);
	void update_user(wstringstream& values, UserData& dst);
};