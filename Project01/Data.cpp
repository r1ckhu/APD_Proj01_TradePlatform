#pragma once
#include <Data.h>
int &Data::get_id()
{
    return id;
}

// UserData
const string &UserData::get_password()
{
    return password;
}

const float &UserData::get_balance()
{
    return balance;
}
void UserData::set_password(const string &s)
{
    password = s;
}
void UserData::set_balance(const float &b)
{
    balance = b;
}
bool UserData::is_banned()
{
    return banned;
}

// Commodity Data
int &CommodityData::get_quantity()
{
    return quantity;
}
int &CommodityData::get_seller_id()
{
    return seller_id;
}
float &CommodityData::get_price()
{
    return price;
}
CommodityStates &CommodityData::get_commodity_state()
{
    return commodity_state;
}
void CommodityData::set_quantity(const int &q)
{
    quantity = q;
}
void CommodityData::set_price(const float &p)
{
    price = p;
}
void CommodityData::set_commodity_state(const CommodityStates &c)
{
    commodity_state = c;
}