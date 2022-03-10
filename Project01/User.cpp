#pragma once
#include "Data.h"
#include "User.h"
using namespace std;
extern DataHandler datahandler;

UserData* UserHandler::adminlogin()
{
	wstring name, password;
	wprintf(L"���������Աusername:");
	wcin >> name;
	wprintf(L"���������Աpassword:");
	wcin >> password;
	if (name != L"admin" || password != L"123456") {
		wprintf(L"---username��password���󣬷������˵�---\n\n");
		return nullptr;
	}
	else {
		UserData* user = new UserData;
		user->name = L"admin";
		user->set_user_type(ADMIN);
		user->set_password(L"123456");
		wprintf(L"---��½�ɹ�---\n\n");
		return user;
	}
}

UserData* UserHandler::userlogin()
{
	wstring name, password;
	wprintf(L"������username:");
	wcin >> name;
	wprintf(L"������password:");
	wcin >> password;
	Table<UserData>* usertable = datahandler.get_user_table();
	for (list<UserData>::iterator it = usertable->_list.begin(); it != usertable->_list.end(); it++)
	{
		if (it->name == name && it->get_password() == password)
		{
			wprintf(L"---��½�ɹ�---\n\n");
			return &(*it);
		}
	}
	wprintf(L"---username��password���󣬷������˵�---\n\n");
	return nullptr;
}