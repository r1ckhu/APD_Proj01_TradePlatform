#pragma once
#include "Data.h"
#include "SQL_Interpreter.h"
DataHandler datahandler;
SQL_Interpreter sql_interpreter;
int main()
{
	wstring ws = L"INSERT INTO commodity VALUES (M001,NAME,10.5,10-30,U002,10,A Test Commodity)";
	sql_interpreter.interpret(ws);
	ws = L"INSERT INTO order VALUES (T002,M001,10,20,10-20,U001,U003)";
	sql_interpreter.interpret(ws);
	ws = L"INSERT INTO user VALUES (U010,RICK,1234,NANJINGUNIVERSITY,0,12345)";
	sql_interpreter.interpret(ws);
	return 0;
}