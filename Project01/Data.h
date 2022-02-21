#pragma once
#include <iostream>
#include <string>
#include <list>
#include <memory>
using namespace std;
using d_ptr = unique_ptr<Data>;
enum UserTypes
{
    ADMIN,
    AVE_USER
};

enum CommodityStates
{
    ON_SELL,
    OFF_SHELF
};

class Data
{
protected:
    int id;

public:
    wstring name;
    int &get_id();
};

class UserData : public Data
{
private:
    string password;
    float balance;
    UserTypes user_type;
    bool banned;

public:
    wstring address;
    int contact;
    const string &get_password();
    const float &get_balance();
    const UserTypes &get_usertype();
    void set_password(const string &s);
    void set_balance(const float &b);
    bool is_banned();
};

class CommodityData : public Data
{
private:
    int quantity;
    int seller_id;
    float price;
    CommodityStates commodity_state;

public:
    wstring description;
    string time_on_self;
    int &get_quantity();
    int &get_seller_id();
    float &get_price();
    CommodityStates &get_commodity_state();
    void set_quantity(const int &q);
    void set_price(const float &p);
    void set_commodity_state(const CommodityStates &c);
};

class Table
{
private:
    int cnt = 0;
    list<d_ptr> _list;
public:
    void *insert_into(Data *d);
    void *update(Data *d, wstring &coloum, wstring &value);
    list<d_ptr> *select();
    list<d_ptr> *select(wstring &coloum, wstring &value);
};

class DataHandler
{
private:
    Table commodityTable;
    Table userTable;
    Table orderTable;

public:
    Table *get_commodity_table();
    Table *get_user_table();
    Table *get_order_table();
};