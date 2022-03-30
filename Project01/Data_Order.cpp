#include "Data.h"
#include <iomanip>
using namespace std;
wostream& operator<<(wostream& output, const OrderData& od)
{
	// orderID, commodityID, unitPrice, number, date, sellerID, buyerID
	output << od.id << ' ' << od.commodity_id << ' ' << od.price << ' ' << od.quantity << ' '\
		<< od.seller_id << ' ' << od.buyer_id;
	return output;
}

wofstream& operator<<(wofstream& output, const OrderData& od)
{
	output << od.id << ',' << od.commodity_id << ',' << od.price << ',' << od.quantity << ',' \
		<< od.time << ',' << od.seller_id << ',' << od.buyer_id;
	return output;
}

void OrderData::format_output(int width)
{
	wcout << setw(width) << id << setw(width) << commodity_id
		<< setw(width) << price << setw(width) << quantity
		<< setw(width) << time << setw(width) << seller_id
		<< setw(width) << buyer_id << endl;
}

OrderData::OrderData()
{
	commodity_id = L"";
	time = L"";
	seller_id = L"";
	buyer_id = L"";
	price = 0.0;
	quantity = 0;
}

OrderData::OrderData(wstringstream& values)
{
	// orderID, commodityID, unitPrice, number, date, sellerID, buyerID
	values >> id >> commodity_id >> price >> quantity \
		>> time >> seller_id >> buyer_id;
}
