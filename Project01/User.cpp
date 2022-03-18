#pragma once
#include "Data.h"
#include "User.h"
#include <sstream>
using namespace std;
extern DataHandler datahandler;

UserData* UserHandler::adminlogin()
{
	wstring name, password;
	wprintf(L"Please enter admin username:");
	wcin >> name;
	wprintf(L"Please enter admin password:");
	wcin >> password;
	if (name != L"admin" || password != L"123456") {
		wprintf(L"---username or password wrong£¬return to the main menu now---\n\n");
		return nullptr;
	}
	else {
		UserData* user = new UserData;
		user->name = L"admin";
		user->set_user_type(ADMIN);
		user->set_password(L"123456");
		wprintf(L"---Login Successful---\n\n");
		return user;
	}
}

UserData* UserHandler::userlogin()
{
	wstring name, password;
	wprintf(L"Please enter username:");
	wcin >> name;
	wprintf(L"Please enter password:");
	wcin >> password;
	Table<UserData>* usertable = datahandler.get_user_table();
	for (list<UserData>::iterator it = usertable->_list.begin(); it != usertable->_list.end(); it++)
	{
		if (it->name == name && it->get_password() == password)
		{
			wprintf(L"---Login Successful---\n\n");
			return &(*it);
		}
	}
	wprintf(L"---username or password wrong£¬return to the main menu now---\n\n");
	return nullptr;
}

void UserHandler::userRegister()
{
	wstring id, name, phoneNumber, password, address;
	wprintf(L"Please enter your userName: ");
	wcin >> name;
	wprintf(L"Please enter your password: ");
	wcin >> password;
	wprintf(L"Please enter your phoneNumber: ");
	wcin >> phoneNumber;
	wprintf(L"Please enter your address: ");
	wcin >> address;
	id = datahandler.generate_user_id();
	wstringstream wss;
	wss << id << ' ' << name << ' ' << password << ' ' << phoneNumber << ' ' << address\
		<< ' ' << 0.0 <<  ' ' << "active";
	UserData ud(wss);
	datahandler.get_user_table()->_list.push_back(ud);
	wfstream out_user(fpath_user,ios::app);
	out_user<< id << ',' << name << ',' << password << ',' << phoneNumber << ',' << address\
		<< ',' << 0.0 << ',' << "active";
	out_user.close();
}