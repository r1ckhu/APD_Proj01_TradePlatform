#include "Data.h"
using namespace std;
CommodityData::CommodityData()
{
	quantity = 0;
	seller_id = L"";
	price = 0.0;
	commodity_state = ON_SELL;
	description = L"";
	time_on_shelf = L"";
}

CommodityData::CommodityData(wstringstream& values)
{
	// description can not have space!!
	wstring status;
	// commodityID,commodityName,price,number,description,sellerID,addedDate,state
	values >> id >> name >> price >> quantity >> description\
		>> seller_id >> time_on_shelf >> status;
	//description.erase(--description.end());
	if (status == L"onSale")
		commodity_state = ON_SELL;
	else
		commodity_state = OFF_SHELF;

}

int& CommodityData::get_quantity()
{
	return quantity;
}
wstring& CommodityData::get_seller_id()
{
	return seller_id;
}
float& CommodityData::get_price()
{
	return price;
}
CommodityStates& CommodityData::get_commodity_state()
{
	return commodity_state;
}
void CommodityData::set_quantity(const int& q)
{
	quantity = q;
}
void CommodityData::set_price(const float& p)
{
	price = p;
}
void CommodityData::set_seller_id(const int& s_id)
{
	seller_id = s_id;
}
void CommodityData::set_commodity_state(const CommodityStates& c)
{
	commodity_state = c;
}

wostream& operator<<(wostream& output, const CommodityData& cd)
{
	// commodityID, commodityName, price, number, description, sellerID, addedDate, state
	output << cd.id << ' ' << cd.name << ' ' << cd.price << ' ' << cd.quantity << ' '\
		<< cd.description << ' ' << cd.seller_id << ' ' << cd.time_on_shelf << ' ' << cd.commodity_state;
	return output;
}

wofstream& operator<<(wofstream& output, const CommodityData& cd)
{
	output << cd.id << ',' << cd.name << ',' << cd.price << ',' << cd.quantity << ',' << cd.description\
		<< ',' << cd.seller_id << ',' << cd.time_on_shelf << ',';
	if (cd.commodity_state == ON_SELL)
		output << L"onSale";
	else if (cd.commodity_state == OFF_SHELF)
		output << L"offShelf";
	return output;
}

void CommodityData::format_output(int width)
{
	wcout << setw(width) << id << setw(width) << name
		<< setw(width) << price << setw(width) << quantity
		<< setw(width) << description << setw(width) << seller_id
		<< setw(width) << time_on_shelf << setw(width)
		<< setw(width) << (commodity_state == ON_SELL ? L"onSale" : L"offShelf") << endl;
}