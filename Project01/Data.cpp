#pragma once
#include "Data.h"
#include "StringOperator.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;
const string fpath_user = "data\\user.txt";
const string fpath_commodity = "data\\commodity.txt";
const string fpath_order = "data\\order.txt";
const wstring user_attribute = L"用户ID,用户名,密码,联系方式,地址,钱包余额,用户状态";
const wstring commodity_attribute = L"商品ID,名称,价格,数量,描述,卖家ID,上架时间,商品状态";
const wstring order_attribute = L"订单ID,商品ID,交易单价,数量,交易时间,卖家ID,买家ID";
extern locale zh_utf;
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
	// 用户ID,用户名,密码,联系方式,地址,钱包余额,用户状态
	wstring status;
	values >> id >> name >> password >> contact >> address >> balance >> status;
	user_type = AVE_USER;
	if (status == L"正常")
		banned = false;
	else
		banned = true;
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
	wstring status;
	// 商品ID,名称,价格,数量,描述,卖家ID,上架时间,商品状态
	values >> id >> name >> price >> quantity >> description\
		>> seller_id >> time_on_shelf >> status;
	//description.erase(--description.end());
	if (status == L"销售中")
		commodity_state = ON_SELL;
	else
		commodity_state = OFF_SHELF;

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

DataHandler::DataHandler()
{
	wifstream in_user(fpath_user, ios::in);
	wifstream in_commodity(fpath_commodity, ios::in);
	wifstream in_order(fpath_order, ios::in);
	in_user.imbue(locale("zh_CN.UTF-8"));
	in_commodity.imbue(locale("zh_CN.UTF-8"));
	in_order.imbue(locale("zh_CN.UTF-8"));

	if (!in_user) {
		wofstream out_user(fpath_user, ios::out);
		out_user.imbue(locale(zh_utf, new std::numpunct<wchar_t>));
		out_user << user_attribute << endl;
		out_user.close();
	}
	else {
		wstring ws_values;
		wstringstream wss_values;
		in_user >> ws_values;
		while (in_user >> ws_values)
		{
			wss_values.str(L"");
			wss_values.seekg(0);
			StringOperator::comma2space(ws_values);
			wss_values << ws_values;
			UserData userdata(wss_values);
			userTable._list.push_back(userdata);
			userTable.cnt++;
		}
		in_user.close();
	}

	if (!in_commodity) {
		wofstream out_commodity(fpath_commodity, ios::out);
		out_commodity.imbue(locale(zh_utf, new std::numpunct<wchar_t>));
		out_commodity << commodity_attribute << endl;
		out_commodity.close();
	}
	else {
		wstring ws_values;
		wstringstream wss_values;
		in_commodity >> ws_values;
		while (in_commodity >> ws_values)
		{
			wss_values.str(L"");
			wss_values.seekg(0);
			StringOperator::comma2space(ws_values);
			wss_values << ws_values;
			CommodityData commoditydata(wss_values);
			commodityTable._list.push_back(commoditydata);
			commodityTable.cnt++;
		}
		in_commodity.close();
	}

	if (!in_order) {
		wofstream out_order(fpath_order, ios::out);
		out_order.imbue(locale(zh_utf, new std::numpunct<wchar_t>));
		out_order << order_attribute << endl;
		out_order.close();
	}
	else {
		wstring ws_values;
		wstringstream wss_values;
		in_order >> ws_values;
		while (in_order >> ws_values)
		{
			wss_values.str(L"");
			wss_values.seekg(0);
			StringOperator::comma2space(ws_values);
			wss_values << ws_values;
			OrderData orderdata(wss_values);
			orderTable._list.push_back(orderdata);
			orderTable.cnt++;
		}
		in_order.close();
	}
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
	// 用户ID, 用户名, 密码, 联系方式, 地址, 钱包余额, 用户状态
	output << ud.id << ' ' << ud.name << ' ' << ud.password << ' ' << ud.contact << ' '\
		<< ud.address << ' ' << ud.balance << ' ' << ud.banned;
	return output;
}

wofstream& operator<<(wofstream& output, const UserData& ud)
{
	output << ud.id << ',' << ud.name << ',' << ud.password << ',' << ud.contact << ',' \
		<< ud.address << ',' << ud.balance << ',';
	if (ud.banned)
		output << L"正常";
	else
		output << L"封禁";
	return output;
}

void UserData::format_output(int width)
{
	wcout << setw(width) << id << setw(width) << name
		<< setw(width) << contact << setw(width) << address
		<< setw(width) << balance <<
		setw(width) << (banned ? L"封禁" : L"正常") << endl;
}

wostream& operator<<(wostream& output, const CommodityData& cd)
{
	// 商品ID, 名称, 价格, 数量, 描述, 卖家ID, 上架时间, 商品状态
	output << cd.id << ' ' << cd.name << ' ' << cd.price << ' ' << cd.quantity << ' '\
		<< cd.description << ' ' << cd.seller_id << ' ' << cd.time_on_shelf << ' ' << cd.commodity_state;
	return output;
}

wofstream& operator<<(wofstream& output, const CommodityData& cd)
{
	output << cd.id << ',' << cd.name << ',' << cd.price << ',' << cd.quantity << ',' << cd.description\
		<< ',' << cd.seller_id << ',' << cd.time_on_shelf << ',';
	if (cd.commodity_state == ON_SELL)
		output << L"销售中";
	else if (cd.commodity_state == OFF_SHELF)
		output << L"已下架";
	return output;
}

void CommodityData::format_output(int width)
{
	wcout << setw(width) << id << setw(width) << name
		<< setw(width) << price << setw(width) << quantity
		<< setw(width) << description << setw(width) << seller_id
		<< setw(width) << time_on_shelf << setw(width)
		<< setw(width) << (commodity_state == ON_SELL ? L"销售中" : L"已下架") << endl;
}

wostream& operator<<(wostream& output, const OrderData& od)
{
	// 订单ID, 商品ID, 交易单价, 数量, 交易时间, 卖家ID, 买家ID
	output << od.id << ' ' << od.commodity_id << ' ' << od.price << ' ' << od.quantity << ' '\
		<< od.seller_id << ' ' << od.buyer_id;
	return output;
}

wofstream& operator<<(wofstream& output, const OrderData& od)
{
	output << od.id << ',' << od.commodity_id << ',' << od.price << ',' << od.quantity << ',' \
		<< od.time << ',' << od.seller_id << ',' << od.buyer_id;
	return output;
}

void OrderData::format_output(int width)
{
	wcout << setw(width) << id << setw(width) << commodity_id
		<< setw(width) << price << setw(width) << quantity
		<< setw(width) << time << setw(width) << seller_id
		<< setw(width) << buyer_id << endl;
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
	// 订单ID, 商品ID, 交易单价, 数量, 交易时间, 卖家ID, 买家ID
	values >> id >> commodity_id >> price >> quantity \
		>> time >> seller_id >> buyer_id;
}
