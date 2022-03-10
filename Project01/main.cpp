#pragma once
#include "Data.h"
#include "SQL_Interpreter.h"
#include "Calculator.h"
#include "Menu.h"
#include "User.h"
#include <locale>
#include <iomanip>
DataHandler datahandler;
UserHandler userhandler;
SQL_Interpreter sql_interpreter;
Calculator calculator;
locale zh_utf("zh_CN.UTF-8");
int main()
{
	wcout << setiosflags(ios::left);
	wcout.imbue(locale(zh_utf, new std::numpunct<wchar_t>));
	wcin.imbue(locale("zh_CN.UTF-8"));
	setlocale(LC_ALL, "zh_CN.UTF-8");
	
	// orderID, commodityID, unitPrice, number, date, sellerID, buyerID
	// commodityID, commodityName, price, number, description, sellerID, addedDate, state
	// userID, username, password, phoneNumber, address, balance, userState
	/*wstring ws = L"INSERT INTO commodity VALUES (M001,NAME,10.5,10,A_Test_Commodity,U002,10-31,onSale)";
	sql_interpreter.interpret(ws);
	ws = L"INSERT INTO commodity VALUES (M011,NAMEEE,12.5,10,AGreenApple,U004,10-30,offShelf)";
	sql_interpreter.interpret(ws);

	ws = L"INSERT INTO order VALUES (T002,M001,10.1,20,10-20,U001,U003)";
	sql_interpreter.interpret(ws);
	ws = L"INSERT INTO order VALUES (T010,M005,12.2,90,11-20,U002,U003)";
	sql_interpreter.interpret(ws);

	ws = L"INSERT INTO user VALUES (U010,RICK,12345,1234555,NANJINGUNIVERSITY,0,active)";
	sql_interpreter.interpret(ws);
	ws = L"INSERT INTO user VALUES (U012,Bono,password,12345,JIAOTONGUNIVERSITY,100,已inactive)";
	sql_interpreter.interpret(ws);

	ws = L"UPDATE commodity SET commodityID = M002, commodityName = EMAN, price = 11, addedDate = 12-30,\
		 sellerID = U004, number = 20, description = 一个红苹果, state = offShelf WHERE addedDate = 10-30";
	sql_interpreter.interpret(ws);
	ws = L"UPDATE order SET orderID = T009, commodityID = M007, unitPrice = 11, date = 12-30,\
		 sellerID = U004, number = 20, buyerID = U001 WHERE sellerID = U001";
	sql_interpreter.interpret(ws);
	ws = L"UPDATE user SET userID = U004, username = Max, phoneNumber = 0000, address = 同济大学,\
		 balance = 99, password = qwerty WHERE phoneNumber = 12345";
	sql_interpreter.interpret(ws);*/
	wstring ws;
	ws = L"SELECT * FROM commodity";
	list<CommodityData>* lc = (list<CommodityData>*)sql_interpreter.interpret(ws);
	for (list<CommodityData>::iterator it = lc->begin(); it != lc->end(); it++) {
		wcout << *it << endl;
	}
	cout << endl;
	ws = L"SELECT * FROM commodity WHERE addedDate CONTAINS 12-30";
	lc = (list<CommodityData>*)sql_interpreter.interpret(ws);
	for (list<CommodityData>::iterator it = lc->begin(); it != lc->end(); it++) {
		wcout << *it << endl;
	}
	cout << endl << endl;


	ws = L"SELECT * FROM user";
	list<UserData>* lu = (list<UserData>*)sql_interpreter.interpret(ws);
	for (list<UserData>::iterator it = lu->begin(); it != lu->end(); it++) {
		wcout << *it << endl;
	}
	cout << endl;
	ws = L"SELECT * FROM user WHERE phoneNumber CONTAINS 0";
	lu = (list<UserData>*)sql_interpreter.interpret(ws);
	for (list<UserData>::iterator it = lu->begin(); it != lu->end(); it++) {
		wcout << *it << endl;
	}
	cout << endl << endl;


	ws = L"SELECT * FROM order";
	list<OrderData>* lo = (list<OrderData>*)sql_interpreter.interpret(ws);
	for (list<OrderData>::iterator it = lo->begin(); it != lo->end(); it++) {
		wcout << *it << endl;
	}
	cout << endl;
	ws = L"SELECT * FROM order WHERE sellerID CONTAINS U007";
	lo = (list<OrderData>*)sql_interpreter.interpret(ws);
	for (list<OrderData>::iterator it = lo->begin(); it != lo->end(); it++) {
		wcout << *it << endl;
	}
	cout << endl << endl;

	string exp = "3 + 4 * 2 / ( 1 - 5 )";
	float ans = calculator.calexp(exp);
	cout << ans << endl << endl;

	exp = "-2";
	ans = calculator.calexp(exp);
	cout << ans << endl << endl;

	exp = "(-2)*4";
	ans = calculator.calexp(exp);
	cout << ans << endl << endl;

	exp = "2*-4";
	ans = calculator.calexp(exp);
	cout << ans << endl << endl;

	exp = "4*(-2)";
	ans = calculator.calexp(exp);
	cout << ans << endl << endl;

	exp = "((4 * 3 + 2) / (6.4 - 2.4) - 10) * (6.4 - 7.2) + (-2) * 4";
	ans = calculator.calexp(exp);
	cout << ans << endl << endl;

	exp = "(2 + 4 * 3.5) * 6";
	ans = calculator.calexp(exp);
	cout << ans << endl << endl;

	UserData* ud = nullptr;
	DefaultMenu defaultmenu;
	UserMenu usermenu;
	//usermenu.inputloop(ud);
	defaultmenu.inputloop(ud);
	
	return 0;
}