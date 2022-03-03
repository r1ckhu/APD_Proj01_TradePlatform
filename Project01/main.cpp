#pragma once
#include "Data.h"
#include "SQL_Interpreter.h"
#include "Calculator.h"
#include "Menu.h"
DataHandler datahandler;
SQL_Interpreter sql_interpreter;
Calculator calculator;
int main()
{
	wcout.imbue(locale("zh_CN.UTF-8"));
	setlocale(LC_ALL, "zh_CN.UTF-8");
	/*wstring ws = L"INSERT INTO commodity VALUES (M001,NAME,10.5,10-31,U002,10,A_Test_Commodity)";
	sql_interpreter.interpret(ws);
	ws = L"INSERT INTO commodity VALUES (M010,NAMEEE,10.5,10-30,U001,10,ATestCommodity)";
	sql_interpreter.interpret(ws);

	ws = L"INSERT INTO order VALUES (T002,M001,10,20,10-20,U001,U003)";
	sql_interpreter.interpret(ws);
	ws = L"INSERT INTO order VALUES (T010,M005,12,90,11-20,U002,U003)";
	sql_interpreter.interpret(ws);

	ws = L"INSERT INTO user VALUES (U010,RICK,12345,NANJINGUNIVERSITY,0,12345)";
	sql_interpreter.interpret(ws);
	ws = L"INSERT INTO user VALUES (U012,Bono,12345,JIAOTONGUNIVERSITY,100,password)";
	sql_interpreter.interpret(ws);

	ws = L"UPDATE commodity SET 商品ID = M002, 名称 = EMAN, 价格 = 11, 上架时间 = 12-30,\
		 卖家ID = U004, 数量 = 20, 描述 = 一个红苹果, 商品状态 = 已下架 WHERE 上架时间 = 10-30";
	sql_interpreter.interpret(ws);
	ws = L"UPDATE order SET 订单ID = T009, 商品ID = M007, 交易单价 = 11, 交易时间 = 12-30,\
		 卖家ID = U004, 数量 = 20, 买家ID = U001 WHERE 卖家ID = U001";
	sql_interpreter.interpret(ws);
	ws = L"UPDATE user SET 用户ID = U004, 用户名 = Max, 联系方式 = 0000, 地址 = 同济大学,\
		 钱包余额 = 99, 密码 = qwerty WHERE 联系方式 = 12345";
	sql_interpreter.interpret(ws);

	ws = L"SELECT * FROM commodity";
	list<CommodityData>* lc = (list<CommodityData>*)sql_interpreter.interpret(ws);
	for (list<CommodityData>::iterator it = lc->begin(); it != lc->end(); it++) {
		wcout << *it << endl;
	}
	cout << endl;
	ws = L"SELECT * FROM commodity WHERE 上架时间 = 12-30";
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
	ws = L"SELECT * FROM user WHERE 联系方式 = 0";
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
	ws = L"SELECT * FROM order WHERE 卖家ID = U007";
	lo = (list<OrderData>*)sql_interpreter.interpret(ws);
	for (list<OrderData>::iterator it = lo->begin(); it != lo->end(); it++) {
		wcout << *it << endl;
	}
	cout << endl << endl;*/

	string exp = "3 + 4 * 2 / ( 1 - 5 )";
	float ans = calculator.calexp(exp);
	cout << ans << endl<<endl;

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
	usermenu.inputloop(ud);
	return 0;
}