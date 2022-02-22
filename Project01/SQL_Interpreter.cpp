#pragma once
#include "SQL_Interpreter.h"
#include "Data.h"
#include <iostream>
#include <sstream>
using namespace std;
extern DataHandler datahandler;

void SQL_Interpreter::interpret(wstring& statement)
{
	wstringstream wss;
	wss << statement;
	wstring word;
	wss >> word; // word is now command
	if (word == L"INSERT")
	{
		wcout << word << endl;
		wss >> word >> word; // word is now name
		wstring name = word;
		// Remove ( and , in wss
		wss >> word >> word;
		word.erase(word.begin());
		for (int i = 0; i < word.size(); i++)
			if (word[i] == ',')
				word[i] = ' ';
		wcout << word;
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
		wstring coloum;
		wchar_t eq = '=';
		if (word == L"commodity")
		{
			Table<CommodityData>* table = datahandler.get_commodity_table();
			CommodityData newData;
			return;
		}
		else if (word == L"order")
		{
			return;
		}
		else if (word == L"user")
		{
			return;
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
