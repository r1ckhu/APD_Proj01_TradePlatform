#pragma once
#include "Data.h"
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
		<< ud.balance <<' ' << ud.password;
	return output;
}

wostream& operator<<(wostream& output, const CommodityData& cd)
{
	output << cd.id << ' ' << cd.name << ' ' << cd.price << ' ' << cd.time_on_self << ' '\
		<< cd.seller_id << ' ' << cd.quantity <<' ' << cd.description <<' ' << cd.commodity_state;
	return output;
}

wostream& operator<<(wostream& output, const OrderData& od)
{
	output << od.id << ' ' << od.commodity_id << ' ' << od.price << ' ' << od.quantity << ' '\
		<< od.seller_id << ' ' << od.buyer_id;
	return output;
}
