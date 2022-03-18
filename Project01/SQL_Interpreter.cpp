#pragma once
#include "SQL_Interpreter.h"
#include "StringOperator.h"
#include "Data.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <locale>
#include <ctime>
using namespace std;
extern DataHandler datahandler;
extern locale zh_utf;
const float DELTA = 0.00001;

void* SQL_Interpreter::interpret(wstring& statement) {
	wstringstream wss;
	wss << statement;
	wstring word;
	wss >> word; // word is now command
	if (word == L"INSERT") {
		// TODO: need retesting
		wss >> word >> word; // word is now name
		wstring name = word;
		wss >> word >> word; // Remove ( and , in wss
		word.erase(word.begin());
		word.erase(--word.end());
		StringOperator::comma2space(word);
		wstringstream values;
		values << word;
		if (name == L"commodity") {
			// TODO: can be changed to reference
			Table<CommodityData>* table = datahandler.get_commodity_table();
			CommodityData cd = insert<CommodityData>(values, table);
			appendfile(cd);
		}
		else if (name == L"order") {
			Table<OrderData>* table = datahandler.get_order_table();
			OrderData od = insert<OrderData>(values, table);
			appendfile(od);
		}
		else if (name == L"user") {
			Table<UserData>* table = datahandler.get_user_table();
			UserData ud = insert<UserData>(values, table);
			appendfile(ud);
		}
		return nullptr;
	}
	else if (word == L"UPDATE") {
		wss >> word;
		wstring name = word, col, val, eq;
		wstring space = L" ";
		wss >> word; // word is now set
		wstringstream values, ws_val;
		wss >> col >> eq >> val;
		while (col != L"WHERE") { // 准备字符串流
			if (*(--val.end()) == ',')
				val.erase(--val.end());
			values << col << space << val << space;
			wss >> col >> eq >> val;
		}
		col = eq; wss >> val;
		ws_val << val;
		if (name == L"commodity") {
			Table<CommodityData>* table = datahandler.get_commodity_table();
			update<CommodityData>(values, ws_val, col, val, table);
			writefile(COMMODITY);
		}
		else if (name == L"order") {
			Table<OrderData>* table = datahandler.get_order_table();
			update<OrderData>(values, ws_val, col, val, table);
			writefile(ORDER);
		}
		else if (name == L"user") {
			Table<UserData>* table = datahandler.get_user_table();
			update<UserData>(values, ws_val, col, val, table);
			writefile(USER);
		}
		return nullptr;
	}
	else if (word == L"SELECT") {
		wss >> word >> word >> word; // word is now name
		wstring name = word;
		if (wss >> word) { // word is now where if possible
			wstring col, val;
			wstringstream ws_val;
			wss >> col >> word >> val;
			ws_val << val;
			void* dst = nullptr;
			if (name == L"commodity") {
				Table<CommodityData>* table = datahandler.get_commodity_table();
				dst = select<CommodityData>(ws_val, col, val, table);
			}
			else if (name == L"order") {
				Table<OrderData>* table = datahandler.get_order_table();
				dst = select<OrderData>(ws_val, col, val, table);
			}
			else if (name == L"user") {
				Table<UserData>* table = datahandler.get_user_table();
				dst = select<UserData>(ws_val, col, val, table);
			}
			return dst;
		}
		else {
			if (name == L"commodity") {
				Table<CommodityData>* table = datahandler.get_commodity_table();
				return &(table->_list);
			}
			else if (name == L"order") {
				Table<OrderData>* table = datahandler.get_order_table();
				return &(table->_list);
			}
			else if (name == L"user") {
				Table<UserData>* table = datahandler.get_user_table();
				return &(table->_list);
			}
		}
		return nullptr;
	}
	else
		cout << "Invalid SQL statement!" << endl;
	return nullptr;
}

SQL_Interpreter::SQL_Interpreter()
{
	in_command.open(fpath_command, ios::app);
}

template<typename T>
T SQL_Interpreter::insert(wstringstream& values, Table<T>* table)
{
	T newdata(values);
	table->_list.push_back(newdata);
	return newdata;
}

template<typename T>
void SQL_Interpreter::update(wstringstream& values, wstringstream& ws_val, wstring col, wstring val, Table<T>* table)
{
	typename list<T>::iterator it;
	for (it = table->_list.begin(); it != table->_list.end(); it++) {
		// 循环遍历表中的所有数据
		values.clear(); values.seekg(0);
		ws_val.clear(); ws_val.seekg(0);
		// val 此时应是某一个值，假如对应的值是wstring类型则可以直接比较
		// 否则就将之前储存进 ws_val 中的值类型转换后再比较
		if (is_col_eql_val(ws_val, col, val, *it)) {
			update_row(values, *it);
		}
	}
}
template<typename T>
void* SQL_Interpreter::select(wstringstream& ws_val, wstring col, wstring val, Table<T>* table)
{
	list<T>* dst = new list<T>;
	typename list<T>::iterator it;
	for (it = table->_list.begin(); it != table->_list.end(); it++) {
		ws_val.seekg(0); ws_val.clear();
		if (is_col_eql_val(ws_val, col, val, *it))
			dst->push_back(*it);
	}
	return dst;
}

void SQL_Interpreter::update_row(wstringstream& values, CommodityData& dst)
{
	wstring col, val;
	while (values >> col >> val)
	{
		wstringstream ws_val;
		ws_val.str(L"");
		if (col == L"commodityID")
			dst.id = val;
		else if (col == L"commodityName")
			dst.name = val;
		else if (col == L"price")
		{
			float p = 0.0;
			ws_val << val;
			ws_val >> p;
			dst.price = p;
		}
		else if (col == L"addedDate")
			dst.time_on_shelf = val;
		else if (col == L"sellerID")
			dst.seller_id = val;
		else if (col == L"number")
		{
			int q = 0;
			ws_val << val;
			ws_val >> q;
			dst.quantity = q;
		}
		else if (col == L"description")
			dst.description = val;
		else if (col == L"state")
		{
			if (val == L"onSale")
				dst.commodity_state = ON_SELL;
			else if (val == L"offShelf")
				dst.commodity_state = OFF_SHELF;
		}
	}
}
void SQL_Interpreter::update_row(wstringstream& values, OrderData& dst)
{
	wstring col, val;
	while (values >> col >> val)
	{
		wstringstream ws_val;
		ws_val.str(L"");
		if (col == L"orderID")
			dst.id = val;
		else if (col == L"commodityID")
			dst.commodity_id = val;
		else if (col == L"unitPrice")
		{
			float p = 0.0;
			ws_val << val;
			ws_val >> p;
			dst.price = p;
		}
		else if (col == L"number")
		{
			int q = 0;
			ws_val << val;
			ws_val >> q;
			dst.quantity = q;
		}
		else if (col == L"date")
			dst.time = val;
		else if (col == L"sellerID")
			dst.seller_id = val;
		else if (col == L"buyerID")
			dst.buyer_id = val;
	}
}
void SQL_Interpreter::update_row(wstringstream& values, UserData& dst)
{
	wstring col, val;
	while (values >> col >> val)
	{
		wstringstream ws_val;
		ws_val.str(L"");
		if (col == L"userID")
			dst.id = val;
		else if (col == L"username")
			dst.name = val;
		else if (col == L"balance")
		{
			float b = 0.0;
			ws_val << val;
			ws_val >> b;
			dst.balance = b;
		}
		else if (col == L"phoneNumber")
			dst.contact = val;
		else if (col == L"address")
			dst.address = val;
		else if (col == L"password")
			dst.password = val;
		else if (col == L"userState")
		{
			if (val == L"active")
				dst.banned = false;
			else if (val == L"inactive")
				dst.banned = true;
		}
	}
}

bool SQL_Interpreter::is_col_eql_val(wstringstream& ws_val, wstring& col, wstring& val, CommodityData& tar)
{
	if (col == L"commodityID" && val.find(tar.id) != wstring::npos)
		return true;
	else if (col == L"commodityName" && val.find(tar.name) != wstring::npos)
		return true;
	else if (col == L"price") {
		float p = 0.0;
		ws_val >> p;
		if (tar.price - p < DELTA)
			return true;
	}
	else if (col == L"addedDate" && tar.time_on_shelf == val)
		return true;
	else if (col == L"sellerID" && tar.seller_id == val)
		return true;
	else if (col == L"number") {
		int q = 0;
		ws_val >> q;
		if (tar.price == q)
			return true;
	}
	else if (col == L"description" && tar.description == val)
		return true;
	else if (col == L"state") {
		if (val == L"onSale" && tar.commodity_state == ON_SELL)
			return true;
		else if (val == L"offShelf" && tar.commodity_state == OFF_SHELF)
			return true;
	}
	return false;
}
bool SQL_Interpreter::is_col_eql_val(wstringstream& ws_val, wstring col, wstring val, OrderData& tar)
{
	if (col == L"orderID" && tar.id == val)
		return true;
	else if (col == L"commodityID" && tar.commodity_id == val)
		return true;
	else if (col == L"unitPrice") {
		float p = 0.0;
		ws_val >> p;
		if (p - tar.price < DELTA)
			return true;
	}
	else if (col == L"number") {
		int q = 0;
		ws_val >> q;
		if (q == tar.quantity)
			return true;
	}
	else if (col == L"date" && tar.time == val)
		return true;
	else if (col == L"sellerID" && tar.seller_id == val)
		return true;
	else if (col == L"buyerID" && tar.buyer_id == val)
		return true;
	return false;
}
bool SQL_Interpreter::is_col_eql_val(wstringstream& ws_val, wstring col, wstring val, UserData& tar)
{
	if (col == L"userID" && val.find(tar.id) != wstring::npos)
		return true;
	else if (col == L"username" && val.find(tar.name) != wstring::npos)
		return true;
	else if (col == L"phoneNumber" && tar.contact == val)
		return true;
	else if (col == L"password" && tar.password == val)
		return true;
	else if (col == L"address" && tar.address == val)
		return true;
	else if (col == L"balance")
	{
		float b = 0.0;
		ws_val >> b;
		if (abs(b - tar.balance) < DELTA)
			return true;
	}
	else if (col == L"userState")
	{
		if (val == L"active" && !tar.banned)
			return true;
		else if (val == L"inactive" && tar.banned)
			return true;
	}
	return false;
}

void SQL_Interpreter::appendfile(CommodityData& cd)
{
	// commodityID, commodityName, price, number, description, sellerID, addedDate, state
	wofstream output(fpath_commodity, ios::app);
	output.imbue(locale(zh_utf, new std::numpunct<wchar_t>));
	output << cd.id << ',' << cd.name << ',' << cd.price << ',' << cd.quantity << ',' << cd.description\
		<< ',' << cd.seller_id << ',' << cd.time_on_shelf << ',';
	if (cd.commodity_state == ON_SELL)
		output << L"onSale" << endl;
	else if (cd.commodity_state == OFF_SHELF)
		output << L"offShelf" << endl;
	output.close();
}
void SQL_Interpreter::appendfile(UserData& ud)
{
	// userID, username, password, phoneNumber, address, balance, userState
	wofstream output(fpath_user, ios::app);
	output.imbue(locale(zh_utf, new std::numpunct<wchar_t>));
	output << ud.id << ',' << ud.name << ',' << ud.password << ',' << ud.contact << ',' \
		<< ud.address << ',' << ud.balance << ',';
	if (ud.banned)
		output << L"active" << endl;
	else
		output << L"inactive" << endl;
	output.close();
}
void SQL_Interpreter::appendfile(OrderData& od)
{
	// orderID, commodityID, unitPrice, number, date, sellerID, buyerID
	wofstream output(fpath_order, ios::app);
	output.imbue(locale(zh_utf, new std::numpunct<wchar_t>));
	output << od.id << ',' << od.commodity_id << ',' << od.price << ',' << od.quantity << ',' \
		<< od.time << ',' << od.seller_id << ',' << od.buyer_id << endl;
	output.close();
}
void SQL_Interpreter::writefile(DATA_TYPES dt)
{
	if (dt == COMMODITY) {
		Table<CommodityData>* table = datahandler.get_commodity_table();
		wofstream output(fpath_commodity, ios::out);
		output.imbue(locale(zh_utf, new std::numpunct<wchar_t>));
		output << commodity_attribute << endl;
		for (list<CommodityData>::iterator it = table->_list.begin(); \
			it != table->_list.end(); it++) {
			/*output << (*it).id << ',' << (*it).name << ',' << (*it).price << ',' << (*it).quantity << ',' << (*it).description\
				<< ',' << (*it).seller_id << ',' << (*it).time_on_shelf << ',';
			if ((*it).commodity_state == ON_SELL)
				output << L"onSale" << endl;
			else if ((*it).commodity_state == OFF_SHELF)
				output << L"offShelf" << endl;*/
			output << (*it) << endl;
		}
		output.close();
		return;
	}
	else if (dt == USER) {
		Table<UserData>* table = datahandler.get_user_table();
		wofstream output(fpath_user, ios::out);
		output.imbue(locale(zh_utf, new std::numpunct<wchar_t>));
		output << user_attribute << endl;
		for (list<UserData>::iterator it = table->_list.begin(); \
			it != table->_list.end(); it++) {
			/*output << (*it).id << ',' << (*it).name << ',' << (*it).password << ',' << (*it).contact << ',' \
				<< (*it).address << ',' << (*it).balance << ',';
			if ((*it).banned)
				output << L"active" << endl;
			else
				output << L"inactive" << endl;*/
			output << (*it) << endl;
		}
		output.close();
		return;
	}
	else if (dt == ORDER) {
		Table<OrderData>* table = datahandler.get_order_table();
		wofstream output(fpath_order, ios::out);
		output.imbue(locale(zh_utf, new std::numpunct<wchar_t>));
		output << order_attribute << endl;
		for (list<OrderData>::iterator it = table->_list.begin(); \
			it != table->_list.end(); it++) {
			/*output << (*it).id << ',' << (*it).commodity_id << ',' << (*it).price << ',' << (*it).quantity << ',' \
				<< (*it).time << ',' << (*it).seller_id << ',' << (*it).buyer_id << endl;*/
			output << (*it) << endl;
		}
		output.close();
		return;
	}
}

void SQL_Interpreter::log(wstring& command)
{
	in_command << datahandler.get_current_time(false) << L": " << command << endl;
}