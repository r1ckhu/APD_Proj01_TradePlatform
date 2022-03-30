#include "Data.h"
#include <iomanip>
using namespace std;
const wstring& UserData::get_password()
{
	return password;
}

const float& UserData::get_balance()
{
	return balance;
}
const UserTypes& UserData::get_usertype()
{
	return user_type;
}
void UserData::set_password(const wstring& s)
{
	password = s;
}
void UserData::set_balance(const float& b)
{
	balance = b;
}
void UserData::set_user_type(const UserTypes u_t)
{
	user_type = u_t;
}
bool UserData::is_banned()
{
	return banned;
}

UserData::UserData()
{
	id = L"";
	name = L"";
	contact = L"";
	address = L"";
	balance = 0.0;
	password = L"";
	user_type = AVE_USER;
	banned = false;
}

UserData::UserData(wstringstream& values)
{
	// userID,username,password,phoneNumber,address,balance,userState
	wstring status;
	values >> id >> name >> password >> contact >> address >> balance >> status;
	user_type = AVE_USER;
	if (status == L"active")
		banned = false;
	else
		banned = true;
}



wostream& operator<<(wostream& output, const UserData& ud)
{
	// userID, username, password, phoneNumber, address, balance, userState
	output << ud.id << ' ' << ud.name << ' ' << ud.password << ' ' << ud.contact << ' '\
		<< ud.address << ' ' << ud.balance << ' ' << ud.banned;
	return output;
}

wofstream& operator<<(wofstream& output, const UserData& ud)
{
	output << ud.id << ',' << ud.name << ',' << ud.password << ',' << ud.contact << ',' \
		<< ud.address << ',' << ud.balance << ',';
	if (!ud.banned)
		output << L"active";
	else
		output << L"inactive";
	return output;
}

void UserData::format_output(int width)
{
	wcout << setw(width) << id << setw(width) << name << setw(width) << password
		<< setw(width) << contact << setw(width) << address
		<< setw(width) << balance <<
		setw(width) << (banned ? L"inactive" : L"active") << endl;
}