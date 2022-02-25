#pragma once
#include "SQL_Interpreter.h"
#include "Data.h"
#include <iostream>
#include <sstream>
using namespace std;
extern DataHandler datahandler;
const float DELTA = 0.00001;

void SQL_Interpreter::interpret(wstring& statement)
{
	wstringstream wss;
	wss << statement;
	wstring word;
	wss >> word; // word is now command
	if (word == L"INSERT")
	{
		wss >> word >> word; // word is now name
		wstring name = word;
		// Remove ( and , in wss
		wss >> word >> word;
		word.erase(word.begin());
		for (int i = 0; i < word.size(); i++)
			if (word[i] == ',')
				word[i] = ' ';
		wstringstream values;
		values << word;

		if (name == L"commodity")
		{
			Table<CommodityData>* table = datahandler.get_commodity_table();
			CommodityData newData;
			// TODO : it can be done by overloading the operator >>
			values >> newData.id >> newData.name >> newData.price >> \
				newData.time_on_self >> newData.seller_id >> newData.quantity \
				>> newData.description;
			while (wss >> word)
			{
				newData.description += ' ';
				newData.description.append(word);
			}
			newData.description.erase(--newData.description.end());
			newData.commodity_state = ON_SELL;
			table->_list.push_back(newData);
		}
		else if (name == L"order")
		{
			Table<OrderData>* table = datahandler.get_order_table();
			OrderData newData;
			values >> newData.id >> newData.commodity_id >> newData.price >> newData.quantity\
				>> newData.time >> newData.seller_id >> newData.buyer_id;
			table->_list.push_back(newData);
		}
		else if (name == L"user")
		{
			Table<UserData>* table = datahandler.get_user_table();
			UserData newData;
			values >> newData.id >> newData.name >> newData.contact >> \
				newData.address >> newData.balance >> newData.password;
			newData.user_type = AVE_USER;
			newData.banned = false;
			table->_list.push_back(newData);
		}
	}
	else if (word == L"UPDATE")
	{
		wss >> word;
		wstring name = word, col, val, eq;
		wstring space = L" ";
		wss >> word; // word is now set
		wstringstream values;
		wss >> col >> eq >> val;
		// 准备字符串流
		while (col != L"WHERE")
		{
			if (*(--val.end()) == ',')
				val.erase(--val.end());
			values << col << space << val << space;
			wss >> col >> eq >> val;
		}
		col = eq;
		wss >> val;
		if (name == L"commodity")
		{
			Table<CommodityData>* table = datahandler.get_commodity_table();
			wstringstream ws_val;
			ws_val << val;
			for (list<CommodityData>::iterator it = table->_list.begin(); \
				it != table->_list.end(); it++) // 循环遍历commodity表中的所有数据
			{
				values.clear();
				values.seekg(0);
				ws_val.clear();
				ws_val.seekg(0);
				// val 此时应是某一个值，假如对应的值是wstring类型则可以直接比较
				// 否则就将之前储存进 ws_val 中的值类型转换后再比较
				if (col == L"商品ID" && (*it).id == val)
					update_commodity(values, *it);
				else if (col == L"名称" && (*it).name == val)
					update_commodity(values, *it);
				else if (col == L"价格")
				{
					float p = 0.0;
					ws_val >> p;
					if ((*it).price - p < DELTA)
						update_commodity(values, *it);
				}
				else if (col == L"上架时间" && (*it).time_on_self == val)
				{
					update_commodity(values, *it);
				}
				else if (col == L"卖家ID" && (*it).seller_id == val)
					update_commodity(values, *it);
				else if (col == L"数量")
				{
					int q = 0;
					ws_val >> q;
					if ((*it).price == q)
						update_commodity(values, *it);
				}
				else if (col == L"描述" && (*it).description == val)
					update_commodity(values, *it);
				else if (col == L"商品状态")
				{
					if (val == L"销售中" && (*it).commodity_state == ON_SELL)
						update_commodity(values, *it);
					else if (val == L"已下架" && (*it).commodity_state == OFF_SHELF)
						update_commodity(values, *it);
				}
			}
		}
		else if (name == L"order")
		{
			Table<OrderData>* table = datahandler.get_order_table();
			wstringstream ws_val;
			ws_val << val;
			for (list<OrderData>::iterator it = table->_list.begin(); \
				it != table->_list.end(); it++)
			{
				values.clear();
				values.seekg(0);
				ws_val.clear();
				ws_val.seekg(0);
				if (col == L"订单ID" && (*it).id == val)
					update_order(values, *it);
				else if (col == L"商品ID" && (*it).commodity_id == val)
					update_order(values, *it);
				else if (col == L"交易单价")
				{
					float p = 0.0;
					ws_val >> p;
					if (p - (*it).price < DELTA)
						update_order(values, *it);
				}
				else if (col == L"数量")
				{
					int q = 0;
					ws_val >> q;
					if (q == (*it).quantity)
						update_order(values, *it);
				}
				else if (col == L"交易时间" && (*it).time == val)
					update_order(values, *it);
				else if (col == L"卖家ID" && (*it).seller_id == val)
					update_order(values, *it);
				else if (col == L"买家ID" && (*it).buyer_id == val)
					update_order(values, *it);
			}
		}
		else if (name == L"user")
		{
			Table<UserData>* table = datahandler.get_user_table();
			wstringstream ws_val;
			ws_val << val;
			for (list<UserData>::iterator it = table->_list.begin(); \
				it != table->_list.end(); it++)
			{
				values.clear();
				values.seekg(0);
				ws_val.clear();
				ws_val.seekg(0);
				if (col == L"用户ID" && (*it).id == val)
					update_user(values, *it);
				else if (col == L"用户名" && (*it).name == val)
					update_user(values, *it);
				else if (col == L"联系方式")
				{
					int c = 0;
					ws_val >> c;
					if (c == (*it).contact)
						update_user(values, *it);
				}
				else if (col == L"密码" && (*it).password == val)
					update_user(values, *it);
				else if (col == L"地址" && (*it).address == val)
					update_user(values, *it);
				else if (col == L"钱包余额")
				{
					float b = 0.0;
					ws_val >> b;
					if (abs(b - (*it).balance) < DELTA)
						update_user(values, *it);
				}
				else if (col == L"用户状态")
				{
					if (val == L"正常" && !(*it).banned)
						update_user(values, *it);
					else if(val == L"封禁" && (*it).banned)
						update_user(values, *it);
				}
			}
		}
	}
	else if (word == L"SELECT")
	{
		wss >> word >> word >> word;
		//table = get_table(word);
		return;
	}
	else
	{
		cout << "Invalid SQL statement!" << endl;
	}
}


void SQL_Interpreter::update_commodity(wstringstream& values, CommodityData& dst)
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
			dst.time_on_self = val;
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
void SQL_Interpreter::update_order(wstringstream& values, OrderData& dst)
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
void SQL_Interpreter::update_user(wstringstream& values, UserData& dst)
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