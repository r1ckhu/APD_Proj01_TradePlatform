#pragma once
#include "User.h"
#include <sstream>
using namespace std;
extern DataHandler datahandler;

UserData* UserHandler::adminlogin()
{
	wstring name, password;
	wprintf(L"Please enter admin username:");
	InputHandler::inputString(name, 20, true, true);
	wprintf(L"Please enter admin password:");
	InputHandler::inputString(password, 20, true, true);
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
	InputHandler::inputString(name, 20, true, true);
	wprintf(L"Please enter password:");
	InputHandler::inputString(password, 20, true, true);
	Table<UserData>* usertable = datahandler.get_user_table();
	UserData* ud = usertable->find_byName(name);
	if (ud != nullptr && ud->is_banned()) {
		wcout << "----You have been banned! Please contact Administrator for help.----" << endl;
		return nullptr;
	}
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
	if (!InputHandler::inputString(name, 10, false, true)) {
		InputHandler::throwError();
		return;
	}
	UserData* pud = datahandler.get_user_table()->find_byName(name);
	if (pud != nullptr) {
		wcout << "----Your user name have been used! Choose another one.----" << endl;
		return;
	}
	wprintf(L"Please enter your password: ");
	if (!InputHandler::inputString(password, 20, true, false)) {
		InputHandler::throwError();
		return;
	}
	wprintf(L"Please enter your phoneNumber: ");
	if (!InputHandler::inputNumber(phoneNumber, 20)) {
		InputHandler::throwError();
		return;
	}
	wprintf(L"Please enter your address: ");
	if (!InputHandler::inputString(address, 40, false, true)) {
		InputHandler::throwError();
		return;
	}
	id = datahandler.generate_user_id();
	wstringstream wss;
	wss << id << ' ' << name << ' ' << password << ' ' << phoneNumber << ' ' << address\
		<< ' ' << 0.0 << ' ' << "active";
	UserData ud(wss);
	datahandler.get_user_table()->_list.push_back(ud);
	wfstream out_user(fpath_user, ios::app);
	out_user << id << ',' << name << ',' << password << ',' << phoneNumber << ',' << address\
		<< ',' << 0.0 << ',' << "active" << endl;
	out_user.close();
	wcout << "----Register Successful!----" << endl;
}