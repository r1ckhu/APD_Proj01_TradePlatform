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

	ws = L"UPDATE commodity SET ��ƷID = M002, ���� = EMAN, �۸� = 11, �ϼ�ʱ�� = 12-30,\
		 ����ID = U004, ���� = 20, ���� = һ����ƻ��, ��Ʒ״̬ = ���¼� WHERE �ϼ�ʱ�� = 10-30";
	sql_interpreter.interpret(ws);
	ws = L"UPDATE order SET ����ID = T009, ��ƷID = M007, ���׵��� = 11, ����ʱ�� = 12-30,\
		 ����ID = U004, ���� = 20, ���ID = U001 WHERE ����ID = U001";
	sql_interpreter.interpret(ws);
	ws = L"UPDATE user SET �û�ID = U004, �û��� = Max, ��ϵ��ʽ = 0000, ��ַ = ͬ�ô�ѧ,\
		 Ǯ����� = 99, ���� = qwerty WHERE ��ϵ��ʽ = 12345";
	sql_interpreter.interpret(ws);

	ws = L"SELECT * FROM commodity";
	list<CommodityData>* lc = (list<CommodityData>*)sql_interpreter.interpret(ws);
	for (list<CommodityData>::iterator it = lc->begin(); it != lc->end(); it++) {
		wcout << *it << endl;
	}
	cout << endl;
	ws = L"SELECT * FROM commodity WHERE �ϼ�ʱ�� = 12-30";
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
	ws = L"SELECT * FROM user WHERE ��ϵ��ʽ = 0";
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
	ws = L"SELECT * FROM order WHERE ����ID = U007";
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