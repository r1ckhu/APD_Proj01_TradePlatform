#pragma once
#include <iostream>
#include <string>
#include <list>
#include "SQL_Interpreter.h"
#include "Data.h"
using namespace std;
extern const string fpath_commodity;
extern const string fpath_order;
extern const string fpath_user;
extern const wstring user_attribute;
extern const wstring order_attribute;
extern const wstring commodity_attribute;

enum UserTypes
{
	ADMIN,
	AVE_USER
};

enum CommodityStates
{
	ON_SELL,
	OFF_SHELF
};

class Data
{
protected:
	wstring id;

public:
	wstring name;
	wstring& get_id();
	friend class SQL_Interpreter;
};

class UserData : public Data
{
private:
	wstring password;
	float balance;
	UserTypes user_type;
	bool banned;

public:
	UserData();
	UserData(wstringstream& values);
	wstring address;
	int contact;
	const wstring& get_password();
	const float& get_balance();
	const UserTypes& get_usertype();
	void set_password(const wstring& s);
	void set_balance(const float& b);
	void set_user_type(const UserTypes u_t);
	bool is_banned();
	friend class SQL_Interpreter;
	friend wostream& operator<<(wostream& output, const UserData& ud);
};

class CommodityData : public Data
{
private:
	int quantity;
	wstring seller_id;
	float price;
	CommodityStates commodity_state;

public:
	wstring description;
	wstring time_on_shelf;
	CommodityData();
	CommodityData(wstringstream& values);
	int& get_quantity();
	wstring& get_seller_id();
	float& get_price();
	CommodityStates& get_commodity_state();
	void set_quantity(const int& q);
	void set_price(const float& p);
	void set_seller_id(const int& s_id);
	void set_commodity_state(const CommodityStates& c);
	void initialize(wstringstream& values);
	friend class SQL_Interpreter;
	friend wostream& operator<<(wostream& output, const CommodityData& cd);
};

class OrderData :public Data
{
public:
	wstring commodity_id;
	wstring time;
	wstring seller_id;
	wstring buyer_id;
	float price;
	int quantity;
	OrderData();
	OrderData(wstringstream& values);
	friend class SQL_Interpreter;
	friend wostream& operator<<(wostream& output, const OrderData& od);
};


template<typename T>
class Table
{
private:
	int cnt = 0;
	list<T> _list;
public:
	friend class SQL_Interpreter;
	friend class UserHandler;
	friend class DataHandler;
	//write_to_file(); // TODO
};

class DataHandler
{
private:
	Table<CommodityData> commodityTable;
	Table<UserData> userTable;
	Table<OrderData> orderTable;

public:
	DataHandler(); // TODO
	Table<CommodityData>* get_commodity_table();
	Table<UserData>* get_user_table();
	Table<OrderData>* get_order_table();
};

