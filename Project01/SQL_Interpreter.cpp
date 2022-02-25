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
		// ׼���ַ�����
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
				it != table->_list.end(); it++) // ѭ������commodity���е���������
			{
				values.clear();
				values.seekg(0);
				ws_val.clear();
				ws_val.seekg(0);
				// val ��ʱӦ��ĳһ��ֵ�������Ӧ��ֵ��wstring���������ֱ�ӱȽ�
				// ����ͽ�֮ǰ����� ws_val �е�ֵ����ת�����ٱȽ�
				if (col == L"��ƷID" && (*it).id == val)
					update_commodity(values, *it);
				else if (col == L"����" && (*it).name == val)
					update_commodity(values, *it);
				else if (col == L"�۸�")
				{
					float p = 0.0;
					ws_val >> p;
					if ((*it).price - p < DELTA)
						update_commodity(values, *it);
				}
				else if (col == L"�ϼ�ʱ��" && (*it).time_on_self == val)
				{
					update_commodity(values, *it);
				}
				else if (col == L"����ID" && (*it).seller_id == val)
					update_commodity(values, *it);
				else if (col == L"����")
				{
					int q = 0;
					ws_val >> q;
					if ((*it).price == q)
						update_commodity(values, *it);
				}
				else if (col == L"����" && (*it).description == val)
					update_commodity(values, *it);
				else if (col == L"��Ʒ״̬")
				{
					if (val == L"������" && (*it).commodity_state == ON_SELL)
						update_commodity(values, *it);
					else if (val == L"���¼�" && (*it).commodity_state == OFF_SHELF)
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
				if (col == L"����ID" && (*it).id == val)
					update_order(values, *it);
				else if (col == L"��ƷID" && (*it).commodity_id == val)
					update_order(values, *it);
				else if (col == L"���׵���")
				{
					float p = 0.0;
					ws_val >> p;
					if (p - (*it).price < DELTA)
						update_order(values, *it);
				}
				else if (col == L"����")
				{
					int q = 0;
					ws_val >> q;
					if (q == (*it).quantity)
						update_order(values, *it);
				}
				else if (col == L"����ʱ��" && (*it).time == val)
					update_order(values, *it);
				else if (col == L"����ID" && (*it).seller_id == val)
					update_order(values, *it);
				else if (col == L"���ID" && (*it).buyer_id == val)
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
				if (col == L"�û�ID" && (*it).id == val)
					update_user(values, *it);
				else if (col == L"�û���" && (*it).name == val)
					update_user(values, *it);
				else if (col == L"��ϵ��ʽ")
				{
					int c = 0;
					ws_val >> c;
					if (c == (*it).contact)
						update_user(values, *it);
				}
				else if (col == L"����" && (*it).password == val)
					update_user(values, *it);
				else if (col == L"��ַ" && (*it).address == val)
					update_user(values, *it);
				else if (col == L"Ǯ�����")
				{
					float b = 0.0;
					ws_val >> b;
					if (abs(b - (*it).balance) < DELTA)
						update_user(values, *it);
				}
				else if (col == L"�û�״̬")
				{
					if (val == L"����" && !(*it).banned)
						update_user(values, *it);
					else if(val == L"���" && (*it).banned)
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
			dst.time_on_self = val;
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
void SQL_Interpreter::update_order(wstringstream& values, OrderData& dst)
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
void SQL_Interpreter::update_user(wstringstream& values, UserData& dst)
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