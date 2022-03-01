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

class SQL_Interpreter
{
public:
	void* interpret(wstring& statement);
private:
	// TODO: new function will be added during development
	template <typename T>
	void insert(wstringstream& values, Table<T>* table);
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
};