#pragma once
#include "SQL_Interpreter.h"
#include "Data.h"
#include <iostream>
#include <sstream>
using namespace std;
extern DataHandler datahandler;
const float DELTA = 0.00001;

void* SQL_Interpreter::interpret(wstring& statement) {
	wstringstream wss;
	wss << statement;
	wstring word;
	wss >> word; // word is now command
	if (word == L"INSERT") {
		wss >> word >> word; // word is now name
		wstring name = word;
		wss >> word >> word; // Remove ( and , in wss
		word.erase(word.begin());
		word.erase(--word.end());
		for (int i = 0; i < word.size(); i++)
			if (word[i] == ',')
				word[i] = ' ';
		wstringstream values;
		values << word;
		if (name == L"commodity") {
			Table<CommodityData>* table = datahandler.get_commodity_table();
			insert<CommodityData>(values, table);
		}
		else if (name == L"order") {
			Table<OrderData>* table = datahandler.get_order_table();
			insert<OrderData>(values, table);
		}
		else if (name == L"user") {
			Table<UserData>* table = datahandler.get_user_table();
			insert<UserData>(values, table);
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
		}
		else if (name == L"order") {
			Table<OrderData>* table = datahandler.get_order_table();
			update<OrderData>(values, ws_val, col, val, table);
		}
		else if (name == L"user") {
			Table<UserData>* table = datahandler.get_user_table();
			update<UserData>(values, ws_val, col, val, table);
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
}

template<typename T>
void SQL_Interpreter::insert(wstringstream& values, Table<T>* table)
{
	T newdata(values);
	table->_list.push_back(newdata);
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
		if (col == L"商品ID")
			dst.id = val;
		else if (col == L"名称")
			dst.name = val;
		else if (col == L"价格")
		{
			float p = 0.0;
			ws_val << val;
			ws_val >> p;
			dst.price = p;
		}
		else if (col == L"上架时间")
			dst.time_on_shelf = val;
		else if (col == L"卖家ID")
			dst.seller_id = val;
		else if (col == L"数量")
		{
			int q = 0;
			ws_val << val;
			ws_val >> q;
			dst.quantity = q;
		}
		else if (col == L"描述")
			dst.description = val;
		else if (col == L"商品状态")
		{
			if (val == L"销售中")
				dst.commodity_state = ON_SELL;
			else if (val == L"已下架")
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
		if (col == L"订单ID")
			dst.id = val;
		else if (col == L"商品ID")
			dst.commodity_id = val;
		else if (col == L"交易单价")
		{
			float p = 0.0;
			ws_val << val;
			ws_val >> p;
			dst.price = p;
		}
		else if (col == L"数量")
		{
			int q = 0;
			ws_val << val;
			ws_val >> q;
			dst.quantity = q;
		}
		else if (col == L"交易时间")
			dst.time = val;
		else if (col == L"卖家ID")
			dst.seller_id = val;
		else if (col == L"买家ID")
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
		if (col == L"用户ID")
			dst.id = val;
		else if (col == L"用户名")
			dst.name = val;
		else if (col == L"钱包余额")
		{
			float b = 0.0;
			ws_val << val;
			ws_val >> b;
			dst.balance = b;
		}
		else if (col == L"联系方式")
		{
			int c = 0;
			ws_val << val;
			ws_val >> c;
			dst.contact = c;
		}
		else if (col == L"地址")
			dst.address = val;
		else if (col == L"密码")
			dst.password = val;
		else if (col == L"用户状态")
		{
			if (val == L"正常")
				dst.banned = false;
			else if (val == L"封禁")
				dst.banned = true;
		}
	}
}

bool SQL_Interpreter::is_col_eql_val(wstringstream& ws_val, wstring& col, wstring& val, CommodityData& tar)
{
	if (col == L"商品ID" && tar.id == val)
		return true;
	else if (col == L"名称" && tar.name == val)
		return true;
	else if (col == L"价格") {
		float p = 0.0;
		ws_val >> p;
		if (tar.price - p < DELTA)
			return true;
	}
	else if (col == L"上架时间" && tar.time_on_shelf == val)
		return true;
	else if (col == L"卖家ID" && tar.seller_id == val)
		return true;
	else if (col == L"数量") {
		int q = 0;
		ws_val >> q;
		if (tar.price == q)
			return true;
	}
	else if (col == L"描述" && tar.description == val)
		return true;
	else if (col == L"商品状态") {
		if (val == L"销售中" && tar.commodity_state == ON_SELL)
			return true;
		else if (val == L"已下架" && tar.commodity_state == OFF_SHELF)
			return true;
	}
	return false;
}
bool SQL_Interpreter::is_col_eql_val(wstringstream& ws_val, wstring col, wstring val, OrderData& tar)
{
	if (col == L"订单ID" && tar.id == val)
		return true;
	else if (col == L"商品ID" && tar.commodity_id == val)
		return true;
	else if (col == L"交易单价") {
		float p = 0.0;
		ws_val >> p;
		if (p - tar.price < DELTA)
			return true;
	}
	else if (col == L"数量") {
		int q = 0;
		ws_val >> q;
		if (q == tar.quantity)
			return true;
	}
	else if (col == L"交易时间" && tar.time == val)
		return true;
	else if (col == L"卖家ID" && tar.seller_id == val)
		return true;
	else if (col == L"买家ID" && tar.buyer_id == val)
		return true;
	return false;
}
bool SQL_Interpreter::is_col_eql_val(wstringstream& ws_val, wstring col, wstring val, UserData& tar)
{
	if (col == L"用户ID" && tar.id == val)
		return true;
	else if (col == L"用户名" && tar.name == val)
		return true;
	else if (col == L"联系方式")
	{
		int c = 0;
		ws_val >> c;
		if (c == tar.contact)
			return true;
	}
	else if (col == L"密码" && tar.password == val)
		return true;
	else if (col == L"地址" && tar.address == val)
		return true;
	else if (col == L"钱包余额")
	{
		float b = 0.0;
		ws_val >> b;
		if (abs(b - tar.balance) < DELTA)
			return true;
	}
	else if (col == L"用户状态")
	{
		if (val == L"正常" && !tar.banned)
			return true;
		else if (val == L"封禁" && tar.banned)
			return true;
	}
	return false;
}