#pragma once
#include "Data.h"
#include <string>
#include <sstream>
using namespace std;
wstring& Data::get_id()
{
	return id;
}

// UserData
const wstring& UserData::get_password()
{
	return password;
}

const float& UserData::get_balance()
{
	return balance;
}
const UserTypes& UserData::get_usertype()
{
	return user_type;
}
void UserData::set_password(const wstring& s)
{
	password = s;
}
void UserData::set_balance(const float& b)
{
	balance = b;
}
void UserData::set_user_type(const UserTypes u_t)
{
	user_type = u_t;
}
bool UserData::is_banned()
{
	return banned;
}

UserData::UserData()
{
	id = L"";
	name = L"";
	contact = 0;
	address = L"";
	balance = 0.0;
	password = L"";
	user_type = AVE_USER;
	banned = false;
}

UserData::UserData(wstringstream& values)
{
	values >> id >> name >> contact >> address >> balance >> password;
	user_type = AVE_USER;
	banned = false;
}

CommodityData::CommodityData()
{
	quantity = 0;
	seller_id = L"";
	price = 0.0;
	commodity_state = ON_SELL;
	description = L"";
	time_on_shelf = L"";
}

CommodityData::CommodityData(wstringstream& values)
{
	// description can not have space!!
	values >> id >> name >> price >> \
	time_on_shelf >> seller_id >> quantity >> description;
	description.erase(--description.end());
	commodity_state = ON_SELL;
}

// Commodity Data
int& CommodityData::get_quantity()
{
	return quantity;
}
wstring& CommodityData::get_seller_id()
{
	return seller_id;
}
float& CommodityData::get_price()
{
	return price;
}
CommodityStates& CommodityData::get_commodity_state()
{
	return commodity_state;
}
void CommodityData::set_quantity(const int& q)
{
	quantity = q;
}
void CommodityData::set_price(const float& p)
{
	price = p;
}
void CommodityData::set_seller_id(const int& s_id)
{
	seller_id = s_id;
}
void CommodityData::set_commodity_state(const CommodityStates& c)
{
	commodity_state = c;
}

Table<CommodityData>* DataHandler::get_commodity_table()
{
	return &commodityTable;
}

Table<UserData>* DataHandler::get_user_table()
{
	return &userTable;
}

Table<OrderData>* DataHandler::get_order_table()
{
	return &orderTable;
}

wostream& operator<<(wostream& output, const UserData& ud)
{
	output << ud.id << ' ' << ud.name << ' ' << ud.contact << ' ' << ud.address << ' '\
		<< ud.balance << ' ' << ud.password;
	return output;
}

wostream& operator<<(wostream& output, const CommodityData& cd)
{
	output << cd.id << ' ' << cd.name << ' ' << cd.price << ' ' << cd.time_on_shelf << ' '\
		<< cd.seller_id << ' ' << cd.quantity << ' ' << cd.description << ' ' << cd.commodity_state;
	return output;
}

wstringstream& operator>>(wstringstream& input, CommodityData& cd)
{
	input >> cd.id >> cd.name >> cd.price >> \
		cd.time_on_shelf >> cd.seller_id >> cd.quantity \
		>> cd.description;
}

wostream& operator<<(wostream& output, const OrderData& od)
{
	output << od.id << ' ' << od.commodity_id << ' ' << od.price << ' ' << od.quantity << ' '\
		<< od.seller_id << ' ' << od.buyer_id;
	return output;
}

OrderData::OrderData()
{
	commodity_id = L"";
	time = L"";
	seller_id = L"";
	buyer_id = L"";
	price = 0.0;
	quantity = 0;
}

OrderData::OrderData(wstringstream& values)
{
	values >> id >>commodity_id >> price >> quantity \
		>> time >> seller_id >> buyer_id;
}
