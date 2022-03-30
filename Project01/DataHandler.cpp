#pragma warning( disable : 4996)
#include "Data.h"
using namespace std;

DataHandler::DataHandler()
{
	wifstream in_user(fpath_user, ios::in);
	wifstream in_commodity(fpath_commodity, ios::in);
	wifstream in_order(fpath_order, ios::in);
	wifstream in_cart(fpath_cart, ios::in);
	in_user.imbue(locale("zh_CN.UTF-8"));
	in_commodity.imbue(locale("zh_CN.UTF-8"));
	in_order.imbue(locale("zh_CN.UTF-8"));

	if (!in_user) {
		wofstream out_user(fpath_user, ios::out);
		// out_user.imbue(locale(zh_utf, new std::numpunct<wchar_t>));
		out_user << user_attribute << endl;
		out_user.close();
	}
	else {
		wstring ws_values;
		wstringstream wss_values;
		in_user >> ws_values;
		while (in_user >> ws_values)
		{
			wss_values.str(L"");
			wss_values.seekg(0);
			StringOperator::comma2space(ws_values);
			wss_values << ws_values;
			UserData userdata(wss_values);
			userTable._list.push_back(userdata);
			userTable.cnt++;
		}
		in_user.close();
	}

	if (!in_commodity) {
		wofstream out_commodity(fpath_commodity, ios::out);
		// out_commodity.imbue(locale(zh_utf, new std::numpunct<wchar_t>));
		out_commodity << commodity_attribute << endl;
		out_commodity.close();
	}
	else {
		wstring ws_values;
		wstringstream wss_values;
		in_commodity >> ws_values;
		while (in_commodity >> ws_values)
		{
			wss_values.str(L"");
			wss_values.seekg(0);
			StringOperator::comma2space(ws_values);
			wss_values << ws_values;
			CommodityData commoditydata(wss_values);
			commodityTable._list.push_back(commoditydata);
			commodityTable.cnt++;
		}
		in_commodity.close();
	}

	if (!in_order) {
		wofstream out_order(fpath_order, ios::out);
		// out_order.imbue(locale(zh_utf, new std::numpunct<wchar_t>));
		out_order << order_attribute << endl;
		out_order.close();
	}
	else {
		wstring ws_values;
		wstringstream wss_values;
		in_order >> ws_values;
		while (in_order >> ws_values)
		{
			wss_values.str(L"");
			wss_values.seekg(0);
			StringOperator::comma2space(ws_values);
			wss_values << ws_values;
			OrderData orderdata(wss_values);
			orderTable._list.push_back(orderdata);
			orderTable.cnt++;
		}
		in_order.close();
	}

	if (!in_cart) {
		wofstream out_cart(fpath_cart, ios::out);
		// out_cart.imbue(locale(zh_utf, new std::numpunct<wchar_t>));
		out_cart.close();
	}
	else {
		OrderData od;
		//output << od.buyer_id << od.commodity_id << od.quantity << od.price << od.seller_id;
		while (in_cart >> od.buyer_id >> od.commodity_id >> od.quantity >> od.price >> od.seller_id) {
			if (userTable.find_byID(od.buyer_id) != nullptr)
				userTable.find_byID(od.buyer_id)->cart.push_back(od);
		}
	}
}

Table<CommodityData>* DataHandler::get_commodity_table()
{
	return &commodityTable;
}

Table<UserData>* DataHandler::get_user_table()
{
	return &userTable;
}

Table<OrderData>* DataHandler::get_order_table()
{
	return &orderTable;
}

wstring DataHandler::generate_commodity_id()
{
	wstringstream wss;
	commodityTable.cnt++;
	if (commodityTable.cnt < 10)
		wss << "M00" << commodityTable.cnt;
	else if (commodityTable.cnt < 100)
		wss << "M0" << commodityTable.cnt;
	else
		wss << "M" << commodityTable.cnt;
	wstring id;
	wss >> id;
	return id;
}

wstring DataHandler::generate_user_id()
{
	wstringstream wss;
	userTable.cnt++;
	if (userTable.cnt < 10)
		wss << "U00" << userTable.cnt;
	else if (userTable.cnt < 100)
		wss << "U0" << userTable.cnt;
	else
		wss << "U" << userTable.cnt;
	wstring id;
	wss >> id;
	return id;
}

wstring DataHandler::generate_order_id()
{
	wstringstream wss;
	orderTable.cnt++;
	if (orderTable.cnt < 10)
		wss << "T00" << orderTable.cnt;
	else if (orderTable.cnt < 100)
		wss << "T0" << orderTable.cnt;
	else
		wss << "T" << orderTable.cnt;
	wstring id;
	wss >> id;
	return id;
}

wstring DataHandler::get_current_time(bool concise)
{
	time_t now = time(0);
	tm* gmtm = gmtime(&now);
	gmtm->tm_mon += 1;
	wstringstream wss;
	wstring time;
	wss << (gmtm->tm_year + 1900) << '-';
	if (gmtm->tm_mon < 10)
		wss << '0' << gmtm->tm_mon << '-';
	else
		wss << gmtm->tm_mon << '-';

	if (gmtm->tm_mday < 10)
		wss << '0' << gmtm->tm_mday;
	else
		wss << gmtm->tm_mday;
	if (!concise)
	{
		wss << ' ';
		if (gmtm->tm_hour < 10)
			wss << '0' << gmtm->tm_hour << ':';
		else
			wss << gmtm->tm_hour << ':';

		if (gmtm->tm_min < 10)
			wss << '0' << gmtm->tm_min << ':';
		else
			wss << gmtm->tm_min << ':';

		if (gmtm->tm_sec < 10)
			wss << '0' << gmtm->tm_sec;
		else
			wss << gmtm->tm_sec;
	}
	time = wss.str();
	return time;
}

void DataHandler::add_cart(OrderData& od)
{
	wofstream output(fpath_cart, ios::app);
	output << od.buyer_id << ' ' << od.commodity_id << ' ' << od.quantity << ' ' << od.price << ' ' << od.seller_id << endl;
	output.close();
}

void DataHandler::update_cart()
{
	wofstream output(fpath_cart, ios::out);
	list<UserData>& _list = userTable._list;
	for (list<UserData>::iterator it = _list.begin(); it != _list.end(); it++) {
		for (vector<OrderData>::iterator itt = (*it).cart.begin(); itt != (*it).cart.end(); itt++) {
			output << (*itt).buyer_id << ' ' << (*itt).commodity_id << ' ' << (*itt).quantity << ' ' << (*itt).price << ' ' << (*itt).seller_id << endl;
		}
	}
}