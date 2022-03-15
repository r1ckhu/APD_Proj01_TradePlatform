#pragma once
#include <string>
#include <list>
#include "Data.h"
using namespace std;
class CommodityData;
class OrderData;
class UserData;
template<typename T>
class Table;

enum DATA_TYPES
{
	COMMODITY,
	USER,
	ORDER
};

class SQL_Interpreter
{
public:
	void* interpret(wstring& statement);
	void log(wstring& command);
	SQL_Interpreter();
private:
	wofstream in_commodity, in_user, in_order, in_command;
	template <typename T>
	T insert(wstringstream& values, Table<T>* table);
	template<typename T>
	void update(wstringstream& values, wstringstream& ws_val, wstring col, wstring val, Table<T>* table);
	template<typename T>
	void* select(wstringstream& ws_val, wstring col, wstring val, Table<T>* table);

	bool is_col_eql_val(wstringstream& ws_val, wstring& col, wstring& val, CommodityData& tar);
	bool is_col_eql_val(wstringstream& ws_val, wstring col, wstring val, OrderData& tar);
	bool is_col_eql_val(wstringstream& ws_val, wstring col, wstring val, UserData& tar);
	void update_row(wstringstream& values, CommodityData& dst);
	void update_row(wstringstream& values, OrderData& dst);
	void update_row(wstringstream& values, UserData& dst);

	void appendfile(CommodityData& cd);
	void appendfile(UserData& ud);
	void appendfile(OrderData& od);
	void writefile(DATA_TYPES dt);
};