#pragma once
#include "SQL_Interpreter.h"
#include "Data.h"
#include <iostream>
#include <sstream>
using namespace std;
extern DataHandler datahandler;
const float DELTA = 0.00001;

void* SQL_Interpreter::interpret(wstring& statement) {
	// !! TODO: After reloading the operator >> in Data, template may be used to simplfy the code
	wstringstream wss;
	wss << statement;
	wstring word;
	wss >> word; // word is now command
	if (word == L"INSERT") {
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

		if (name == L"commodity") {
			Table<CommodityData>* table = datahandler.get_commodity_table();
			CommodityData newData;
			// TODO : it can be done by overloading the operator >>
			values >> newData.id >> newData.name >> newData.price >> \
				newData.time_on_shelf >> newData.seller_id >> newData.quantity \
				>> newData.description;
			while (wss >> word) {
				newData.description += ' ';
				newData.description.append(word);
			}
			newData.description.erase(--newData.description.end());
			newData.commodity_state = ON_SELL;
			table->_list.push_back(newData);
		}
		else if (name == L"order") {
			Table<OrderData>* table = datahandler.get_order_table();
			OrderData newData;
			values >> newData.id >> newData.commodity_id >> newData.price >> newData.quantity\
				>> newData.time >> newData.seller_id >> newData.buyer_id;
			table->_list.push_back(newData);
		}
		else if (name == L"user") {
			Table<UserData>* table = datahandler.get_user_table();
			UserData newData;
			values >> newData.id >> newData.name >> newData.contact >> \
				newData.address >> newData.balance >> newData.password;
			newData.user_type = AVE_USER;
			newData.banned = false;
			table->_list.push_back(newData);
		}
		return nullptr;
	}
	else if (word == L"UPDATE") {
		wss >> word;
		wstring name = word, col, val, eq;
		wstring space = L" ";
		wss >> word; // word is now set
		wstringstream values;
		wss >> col >> eq >> val;
		// ׼���ַ�����
		while (col != L"WHERE") {
			if (*(--val.end()) == ',')
				val.erase(--val.end());
			values << col << space << val << space;
			wss >> col >> eq >> val;
		}
		col = eq;
		wss >> val;
		wstringstream ws_val;
		ws_val << val;
		if (name == L"commodity") {
			Table<CommodityData>* table = datahandler.get_commodity_table();
			for (list<CommodityData>::iterator it = table->_list.begin(); \
				it != table->_list.end(); it++) {
				// ѭ������commodity���е���������
				values.clear();
				values.seekg(0);
				ws_val.clear();
				ws_val.seekg(0);
				// val ��ʱӦ��ĳһ��ֵ�������Ӧ��ֵ��wstring���������ֱ�ӱȽ�
				// ����ͽ�֮ǰ����� ws_val �е�ֵ����ת�����ٱȽ�
				if (is_col_eql_val(ws_val, col, val, *it)) {
					update(values, *it);
				}
			}
		}
		else if (name == L"order") {
			Table<OrderData>* table = datahandler.get_order_table();
			for (list<OrderData>::iterator it = table->_list.begin(); \
				it != table->_list.end(); it++) {
				values.clear();
				values.seekg(0);
				ws_val.clear();
				ws_val.seekg(0);
				if (is_col_eql_val(ws_val, col, val, *it)) {
					update(values, *it);
				}
			}
		}
		else if (name == L"user") {
			Table<UserData>* table = datahandler.get_user_table();
			for (list<UserData>::iterator it = table->_list.begin(); \
				it != table->_list.end(); it++) {
				values.clear();
				values.seekg(0);
				ws_val.clear();
				ws_val.seekg(0);
				if (is_col_eql_val(ws_val, col, val, *it)) {
					update(values, *it);
				}
			}
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
			if (name == L"commodity") {
				list<CommodityData>* dst = new list<CommodityData>;
				Table<CommodityData>* table = datahandler.get_commodity_table();
				for (list<CommodityData>::iterator it = table->_list.begin(); \
					it != table->_list.end(); it++) {
					ws_val.seekg(0);
					ws_val.clear();
					if (is_col_eql_val(ws_val, col, val, *it))
						dst->push_back(*it);
				}
				return dst;
			}
			else if (name == L"order") {
				list<OrderData>* dst = new list<OrderData>;
				Table<OrderData>* table = datahandler.get_order_table();
				for (list<OrderData>::iterator it = table->_list.begin(); \
					it != table->_list.end(); it++) {
					ws_val.seekg(0);
					ws_val.clear();
					if (is_col_eql_val(ws_val, col, val, *it))
						dst->push_back(*it);
				}
				return dst;
			}
			else if (name == L"user") {
				list<UserData>* dst = new list<UserData>;
				Table<UserData>* table = datahandler.get_user_table();
				for (list<UserData>::iterator it = table->_list.begin(); \
					it != table->_list.end(); it++) {
					ws_val.seekg(0);
					ws_val.clear();
					if (is_col_eql_val(ws_val, col, val, *it))
						dst->push_back(*it);
				}
				return dst;
			}
		}
		return nullptr;
	}
	else
		cout << "Invalid SQL statement!" << endl;
}


void SQL_Interpreter::update(wstringstream& values, CommodityData& dst)
{
	wstring col, val;
	while (values >> col >> val)
	{
		wstringstream ws_val;
		ws_val.str(L"");
		if (col == L"��ƷID")
			dst.id = val;
		else if (col == L"����")
			dst.name = val;
		else if (col == L"�۸�")
		{
			float p = 0.0;
			ws_val << val;
			ws_val >> p;
			dst.price = p;
		}
		else if (col == L"�ϼ�ʱ��")
			dst.time_on_shelf = val;
		else if (col == L"����ID")
			dst.seller_id = val;
		else if (col == L"����")
		{
			int q = 0;
			ws_val << val;
			ws_val >> q;
			dst.quantity = q;
		}
		else if (col == L"����")
			dst.description = val;
		else if (col == L"��Ʒ״̬")
		{
			if (val == L"������")
				dst.commodity_state = ON_SELL;
			else if (val == L"���¼�")
				dst.commodity_state = OFF_SHELF;
		}
	}
}
void SQL_Interpreter::update(wstringstream& values, OrderData& dst)
{
	wstring col, val;
	while (values >> col >> val)
	{
		wstringstream ws_val;
		ws_val.str(L"");
		if (col == L"����ID")
			dst.id = val;
		else if (col == L"��ƷID")
			dst.commodity_id = val;
		else if (col == L"���׵���")
		{
			float p = 0.0;
			ws_val << val;
			ws_val >> p;
			dst.price = p;
		}
		else if (col == L"����")
		{
			int q = 0;
			ws_val << val;
			ws_val >> q;
			dst.quantity = q;
		}
		else if (col == L"����ʱ��")
			dst.time = val;
		else if (col == L"����ID")
			dst.seller_id = val;
		else if (col == L"���ID")
			dst.buyer_id = val;
	}
}
void SQL_Interpreter::update(wstringstream& values, UserData& dst)
{
	wstring col, val;
	while (values >> col >> val)
	{
		wstringstream ws_val;
		ws_val.str(L"");
		if (col == L"�û�ID")
			dst.id = val;
		else if (col == L"�û���")
			dst.name = val;
		else if (col == L"Ǯ�����")
		{
			float b = 0.0;
			ws_val << val;
			ws_val >> b;
			dst.balance = b;
		}
		else if (col == L"��ϵ��ʽ")
		{
			int c = 0;
			ws_val << val;
			ws_val >> c;
			dst.contact = c;
		}
		else if (col == L"��ַ")
			dst.address = val;
		else if (col == L"����")
			dst.password = val;
		else if (col == L"�û�״̬")
		{
			if (val == L"����")
				dst.banned = false;
			else if (val == L"���")
				dst.banned = true;
		}
	}
}

bool SQL_Interpreter::is_col_eql_val(wstringstream& ws_val, wstring& col, wstring& val, CommodityData& tar)
{
	if (col == L"��ƷID" && tar.id == val)
		return true;
	else if (col == L"����" && tar.name == val)
		return true;
	else if (col == L"�۸�") {
		float p = 0.0;
		ws_val >> p;
		if (tar.price - p < DELTA)
			return true;
	}
	else if (col == L"�ϼ�ʱ��" && tar.time_on_shelf == val)
		return true;
	else if (col == L"����ID" && tar.seller_id == val)
		return true;
	else if (col == L"����") {
		int q = 0;
		ws_val >> q;
		if (tar.price == q)
			return true;
	}
	else if (col == L"����" && tar.description == val)
		return true;
	else if (col == L"��Ʒ״̬") {
		if (val == L"������" && tar.commodity_state == ON_SELL)
			return true;
		else if (val == L"���¼�" && tar.commodity_state == OFF_SHELF)
			return true;

	}
	return false;
}
bool SQL_Interpreter::is_col_eql_val(wstringstream& ws_val, wstring col, wstring val, OrderData& tar)
{
	if (col == L"����ID" && tar.id == val)
		return true;
	else if (col == L"��ƷID" && tar.commodity_id == val)
		return true;
	else if (col == L"���׵���") {
		float p = 0.0;
		ws_val >> p;
		if (p - tar.price < DELTA)
			return true;
	}
	else if (col == L"����") {
		int q = 0;
		ws_val >> q;
		if (q == tar.quantity)
			return true;
	}
	else if (col == L"����ʱ��" && tar.time == val)
		return true;
	else if (col == L"����ID" && tar.seller_id == val)
		return true;
	else if (col == L"���ID" && tar.buyer_id == val)
		return true;
}
bool SQL_Interpreter::is_col_eql_val(wstringstream& ws_val, wstring col, wstring val, UserData& tar)
{
	if (col == L"�û�ID" && tar.id == val)
		return true;
	else if (col == L"�û���" && tar.name == val)
		return true;
	else if (col == L"��ϵ��ʽ")
	{
		int c = 0;
		ws_val >> c;
		if (c == tar.contact)
			return true;
	}
	else if (col == L"����" && tar.password == val)
		return true;
	else if (col == L"��ַ" && tar.address == val)
		return true;
	else if (col == L"Ǯ�����")
	{
		float b = 0.0;
		ws_val >> b;
		if (abs(b - tar.balance) < DELTA)
			return true;
	}
	else if (col == L"�û�״̬")
	{
		if (val == L"����" && !tar.banned)
			return true;
		else if (val == L"���" && tar.banned)
			return true;
	}
}