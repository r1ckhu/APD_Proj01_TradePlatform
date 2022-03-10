#pragma once
#include "Data.h"
#include "User.h"
using namespace std;
extern DataHandler datahandler;

UserData* UserHandler::adminlogin()
{
	wstring name, password;
	wprintf(L"请输入管理员username:");
	wcin >> name;
	wprintf(L"请输入管理员password:");
	wcin >> password;
	if (name != L"admin" || password != L"123456") {
		wprintf(L"---username或password错误，返回主菜单---\n\n");
		return nullptr;
	}
	else {
		UserData* user = new UserData;
		user->name = L"admin";
		user->set_user_type(ADMIN);
		user->set_password(L"123456");
		wprintf(L"---登陆成功---\n\n");
		return user;
	}
}

UserData* UserHandler::userlogin()
{
	wstring name, password;
	wprintf(L"请输入username:");
	wcin >> name;
	wprintf(L"请输入password:");
	wcin >> password;
	Table<UserData>* usertable = datahandler.get_user_table();
	for (list<UserData>::iterator it = usertable->_list.begin(); it != usertable->_list.end(); it++)
	{
		if (it->name == name && it->get_password() == password)
		{
			wprintf(L"---登陆成功---\n\n");
			return &(*it);
		}
	}
	wprintf(L"---username或password错误，返回主菜单---\n\n");
	return nullptr;
}