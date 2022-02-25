#pragma once
#include "Data.h"
#include "SQL_Interpreter.h"
DataHandler datahandler;
SQL_Interpreter sql_interpreter;
int main()
{
	wcout.imbue(locale("chs"));
	wstring ws = L"INSERT INTO commodity VALUES (M001,NAME,10.5,10-30,U002,10,A Test Commodity)";
	sql_interpreter.interpret(ws);
	ws = L"INSERT INTO commodity VALUES (M010,NAMEEE,10.5,10-30,U001,10,ATestCommodity)";
	sql_interpreter.interpret(ws);

	ws = L"INSERT INTO order VALUES (T002,M001,10,20,10-20,U001,U003)";
	sql_interpreter.interpret(ws);
	ws = L"INSERT INTO order VALUES (T010,M005,12,90,11-20,U001,U003)";
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
	return 0;
}