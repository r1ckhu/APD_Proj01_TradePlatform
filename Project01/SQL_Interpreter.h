#pragma once
#include <string>
#include <list>
#include "Data.h"
using namespace std;
class CommodityData;
class OrderData;
class UserData;

class SQL_Interpreter
{
public:
	void* interpret(wstring& statement);
private:
	// TODO: new function will be added during development
	bool is_col_eql_val(wstringstream& ws_val, wstring& col, wstring& val, CommodityData& tar);
	bool is_col_eql_val(wstringstream& ws_val, wstring col, wstring val, OrderData& tar);
	bool is_col_eql_val(wstringstream& ws_val, wstring col, wstring val, UserData& tar);
	void update(wstringstream& values, CommodityData& dst);
	void update(wstringstream& values, OrderData& dst);
	void update(wstringstream& values, UserData& dst);
};