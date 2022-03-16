#pragma once
#pragma warning( disable : 4996)
#include "Data.h"
#include "StringOperator.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;
const string fpath_user = "data\\user.txt";
const string fpath_commodity = "data\\commodity.txt";
const string fpath_order = "data\\order.txt";
const string fpath_command = "data\\commands.txt";
const string fpath_balance = "data\\balance.txt";
const wstring user_attribute = L"userID,username,password,phoneNumber,address,balance,userState";
const wstring commodity_attribute = L"commodityID,commodityName,price,number,description,sellerID,addedDate,state";
const wstring order_attribute = L"orderID,commodityID,unitPrice,number,date,sellerID,buyerID";
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
	// userID,username,password,phoneNumber,address,balance,userState
	wstring status;
	values >> id >> name >> password >> contact >> address >> balance >> status;
	user_type = AVE_USER;
	if (status == L"active")
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
	// commodityID,commodityName,price,number,description,sellerID,addedDate,state
	values >> id >> name >> price >> quantity >> description\
		>> seller_id >> time_on_shelf >> status;
	//description.erase(--description.end());
	if (status == L"onSale")
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

wstring DataHandler::generate_commodity_id()
{
	wstringstream wss;
	commodityTable.cnt++;
	if (commodityTable.cnt < 10)
		wss << "M00" << commodityTable.cnt;
	else if (commodityTable.cnt < 100)
		wss << "M0" << commodityTable.cnt;
	else
		wss << "M" << commodityTable.cnt;
	wstring id;
	wss >> id;
	return id;
}

wstring DataHandler::generate_user_id()
{
	wstringstream wss;
	userTable.cnt++;
	if (userTable.cnt < 10)
		wss << "U00" << userTable.cnt;
	else if (userTable.cnt < 100)
		wss << "U0" << userTable.cnt;
	else
		wss << "U" << userTable.cnt;
	wstring id;
	wss >> id;
	return id;
}

wstring DataHandler::generate_order_id()
{
	wstringstream wss;
	orderTable.cnt++;
	if (orderTable.cnt < 10)
		wss << "T00" << orderTable.cnt;
	else if (orderTable.cnt < 100)
		wss << "T0" << orderTable.cnt;
	else
		wss << "T" << orderTable.cnt;
	wstring id;
	wss >> id;
	return id;
}

wstring DataHandler::get_current_time(bool concise)
{
	time_t now = time(0);
	tm* gmtm = gmtime(&now);
	gmtm->tm_mon += 1;
	wstringstream wss;
	wstring time;
	wss << (gmtm->tm_year + 1900) << '-';
	if (gmtm->tm_mon < 10)
		wss << '0' << gmtm->tm_mon << '-';
	else
		wss << gmtm->tm_mon << '-';

	if (gmtm->tm_mday < 10)
		wss << '0' << gmtm->tm_mday;
	else
		wss << gmtm->tm_mday;
	if (!concise)
	{
		wss << ' ';
		if (gmtm->tm_hour < 10)
			wss << '0' << gmtm->tm_hour << ':';
		else
			wss << gmtm->tm_hour << ':';

		if (gmtm->tm_min < 10)
			wss << '0' << gmtm->tm_min << ':';
		else
			wss << gmtm->tm_min << ':';

		if (gmtm->tm_sec < 10)
			wss << '0' << gmtm->tm_sec;
		else
			wss << gmtm->tm_sec;
	}
	time = wss.str();
	return time;
}

wostream& operator<<(wostream& output, const UserData& ud)
{
	// userID, username, password, phoneNumber, address, balance, userState
	output << ud.id << ' ' << ud.name << ' ' << ud.password << ' ' << ud.contact << ' '\
		<< ud.address << ' ' << ud.balance << ' ' << ud.banned;
	return output;
}

wofstream& operator<<(wofstream& output, const UserData& ud)
{
	output << ud.id << ',' << ud.name << ',' << ud.password << ',' << ud.contact << ',' \
		<< ud.address << ',' << ud.balance << ',';
	if (!ud.banned)
		output << L"active";
	else
		output << L"inactive";
	return output;
}

void UserData::format_output(int width)
{
	wcout << setw(width) << id << setw(width) << name << setw(width) << password
		<< setw(width) << contact << setw(width) << address
		<< setw(width) << balance <<
		setw(width) << (banned ? L"inactive" : L"active") << endl;
}

wostream& operator<<(wostream& output, const CommodityData& cd)
{
	// commodityID, commodityName, price, number, description, sellerID, addedDate, state
	output << cd.id << ' ' << cd.name << ' ' << cd.price << ' ' << cd.quantity << ' '\
		<< cd.description << ' ' << cd.seller_id << ' ' << cd.time_on_shelf << ' ' << cd.commodity_state;
	return output;
}

wofstream& operator<<(wofstream& output, const CommodityData& cd)
{
	output << cd.id << ',' << cd.name << ',' << cd.price << ',' << cd.quantity << ',' << cd.description\
		<< ',' << cd.seller_id << ',' << cd.time_on_shelf << ',';
	if (cd.commodity_state == ON_SELL)
		output << L"onSale";
	else if (cd.commodity_state == OFF_SHELF)
		output << L"offShelf";
	return output;
}

void CommodityData::format_output(int width)
{
	wcout << setw(width) << id << setw(width) << name
		<< setw(width) << price << setw(width) << quantity
		<< setw(width) << description << setw(width) << seller_id
		<< setw(width) << time_on_shelf << setw(width)
		<< setw(width) << (commodity_state == ON_SELL ? L"onSale" : L"offShelf") << endl;
}

wostream& operator<<(wostream& output, const OrderData& od)
{
	// orderID, commodityID, unitPrice, number, date, sellerID, buyerID
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
	// orderID, commodityID, unitPrice, number, date, sellerID, buyerID
	values >> id >> commodity_id >> price >> quantity \
		>> time >> seller_id >> buyer_id;
}

