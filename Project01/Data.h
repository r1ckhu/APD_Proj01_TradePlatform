#pragma once
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>
#include <iomanip>
#include "SQL_Interpreter.h"
#include "StringOperator.h"
using namespace std;
extern const string fpath_commodity;
extern const string fpath_order;
extern const string fpath_user;
extern const string fpath_command;
extern const string fpath_balance;
extern const string fpath_message;
extern const string fpath_cart;
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
	void format_output(int width);
	friend class SQL_Interpreter;
	friend class Menu;
	friend wostream& operator<<(wostream& output, const CommodityData& cd);
	friend wofstream& operator<<(wofstream& output, const CommodityData& cd);
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
	void format_output(int width);
	friend class SQL_Interpreter;
	friend class Menu;
	friend wostream& operator<<(wostream& output, const OrderData& od);
	friend wofstream& operator<<(wofstream& output, const OrderData& od);
};

class UserData : public Data
{
private:
	wstring password;
	float balance;
	UserTypes user_type;
	bool banned;

public:
	vector<OrderData> cart;
	UserData();
	UserData(wstringstream& values);
	wstring address;
	wstring contact;
	const wstring& get_password();
	const float& get_balance();
	const UserTypes& get_usertype();
	void set_password(const wstring& s);
	void set_balance(const float& b);
	void set_user_type(const UserTypes u_t);
	bool is_banned();
	void format_output(int width);
	friend class SQL_Interpreter;
	friend class Menu;
	friend wostream& operator<<(wostream& output, const UserData& ud);
	friend wofstream& operator<<(wofstream& output, const UserData& ud);
};

class MessageData :public Data
{
private:
	wstring msg;
	wstring senderID, receiverID;
	bool read;
public:
	MessageData();
	MessageData(wstring& _id, wstring& _msg, wstring& _senderID, wstring& _receiverID);
	void format_output(int width);
	wstring get_senderID();
	wstring get_receiverID();
	wstring get_msg();
	bool hasRead();
	void readMsg();
	friend class MessageHandler;
	friend class DataHandler;
	// friend wostream& operator<<(wostream& output, const MessageData& msgd);
	friend wofstream& operator<<(wofstream& output, const MessageData& msgd);
};

template<typename T>
class Table
{
private:
	list<T> _list;
public:
	T* find_byID(wstring& tar)
	{
		typename list<T>::iterator it;
		for (it = _list.begin(); it != _list.end(); it++)
		{
			if ((*it).get_id() == tar)
				return &*it;
		}
		return nullptr;
	}
	T* find_byName(wstring& tar)
	{
		typename list<T>::iterator it;
		for (it = _list.begin(); it != _list.end(); it++)
		{
			if ((*it).name.find(tar) != wstring::npos)
				return &*it;
		}
		return nullptr;
	}
	friend class SQL_Interpreter;
	friend class MessageHandler;
	friend class UserHandler;
	friend class DataHandler;
	friend class InfoMenu;
	friend class ChatMenu;
	//write_to_file(); // TODO
};

class DataHandler
{
private:
	Table<CommodityData> commodityTable;
	Table<UserData> userTable;
	Table<OrderData> orderTable;

public:
	DataHandler(); //TODO: Set fstream static
	Table<CommodityData>* get_commodity_table();
	Table<UserData>* get_user_table();
	Table<OrderData>* get_order_table();
	wstring generate_commodity_id();
	wstring generate_user_id();
	wstring generate_order_id();
	wstring get_current_time(bool concise = true);
	void add_cart(OrderData& od);
	void update_cart();
};


class MessageHandler
{
public:
	MessageHandler();
	void sendMsg(wstring& msg, wstring& senderID, wstring& receieverID);
	void retractMsg(UserData* user, wstring& msgID);
	list<MessageData>* get_message_list();
private:
	list<MessageData> Msglist;
	void logMessage(MessageData& msgd);
	void updateMessage();
	wstring generate_new_id();
};

