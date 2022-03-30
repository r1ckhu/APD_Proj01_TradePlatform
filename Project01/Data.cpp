#pragma once
#pragma warning( disable : 4996)
#include "Data.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;
const string fpath_user = "data\\user.txt";
const string fpath_commodity = "data\\commodity.txt";
const string fpath_order = "data\\order.txt";
const string fpath_command = "data\\commands.txt";
const string fpath_balance = "data\\balance.txt";
const string fpath_cart = "data\\cart.txt";
const string fpath_message = "data\\message.txt";
const wstring user_attribute = L"userID,username,password,phoneNumber,address,balance,userState";
const wstring commodity_attribute = L"commodityID,commodityName,price,number,description,sellerID,addedDate,state";
const wstring order_attribute = L"orderID,commodityID,unitPrice,number,date,sellerID,buyerID";
extern locale zh_utf;


wstring& Data::get_id()
{
	return id;
}






