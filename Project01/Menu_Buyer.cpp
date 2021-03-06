#pragma once
#include "Menu.h"
#include "User.h"
#include "Data.h"

using namespace std;
extern UserHandler userhandler;
extern SQL_Interpreter sql_interpreter;
extern DataHandler datahandler;

void BuyerMenu::printMenu()
{
	putnch('\n', 2);
	putnch('=', 68);
	wcout << L"1.View All Commodities 2.Purchase Commodities 3.Search Commodities" << endl << endl;
	wcout << L"4.View History Orders 5.View Detailed Commidity Info 6.Show my cart" << endl << endl;
	wcout << L"7.Return to Main Menu" << endl;
	putnch('=', 68);
}
void BuyerMenu::inputloop(UserData* user)
{
	int input = 0;
	while (true) {
		printMenu();
		wprintf(L"Please choose an operation:");
		InputHandler::inputCommand(input, 1, 7);
		if (input == 1) {
			show_commodity(user);
			continue;
		}
		else if (input == 2) {
			buy_commodity(user);
			continue;
		}
		else if (input == 3) {
			search_commodity(user);
			continue;
		}
		else if (input == 4) {
			show_history(user);
			continue;
		}
		else if (input == 5) {
			show_detail(user);
			continue;
		}
		else if (input == 6) {
			check_cart(user);
			continue;
		}
		else if (input == 7) {
			return;
		}
	}
}

void BuyerMenu::show_commodity(UserData* user)
{
	wstring command(L"SELECT * FROM commodity");
	list<CommodityData>* _list = (list<CommodityData>*)sql_interpreter.interpret(command);
	sql_interpreter.interpret(command);
	sql_interpreter.log(command);
	if (_list->size() == 0) {
		wprintf(L"No Commodity Found!\n");
		return;
	}
	putnch('*', 100);
	int WIDTH = 15;
	wcout << setw(WIDTH) << L"commodityID" << setw(WIDTH) << L"commodityName" << setw(WIDTH) << L"price" << setw(WIDTH) << L"number" <<
		setw(WIDTH) << L"sellerID" << setw(WIDTH) << L"addedDate" << setw(WIDTH) << L"state" << endl;
	for (list<CommodityData>::iterator it = _list->begin(); it != _list->end(); it++)
	{
		if ((*it).get_commodity_state() == ON_SELL) {
			wcout << setw(WIDTH) << (*it).get_id() << setw(WIDTH) << (*it).name
				<< setw(WIDTH) << (*it).get_price() << setw(WIDTH) << (*it).get_quantity()
				<< setw(WIDTH) << (*it).get_seller_id()
				<< setw(WIDTH) << (*it).time_on_shelf << setw(WIDTH)
				<< setw(WIDTH) << ((*it).get_commodity_state() == ON_SELL ? L"onSale" : L"offShelf") << endl;
		}

	}
	putnch('*', 100);
}

void BuyerMenu::buy_commodity(UserData* user)
{
	wstring id;
	int quantity = 0;
	int isign = 0;
	wprintf(L"Please enter the commodity's id:");
	if (!InputHandler::inputString(id, 4, true, true)) {/*id*/
		InputHandler::throwError();
		return;
	}
	wprintf(L"Please enter the quantity:");
	if (!InputHandler::inputInt(quantity)) {
		InputHandler::throwError();
		return;
	}
	wprintf(L"Do you want to buy now or add to your cart? (1 for buy now, 2 for add to cart):");
	if (!InputHandler::inputCommand(isign, 1, 2)) {
		InputHandler::throwError();
		wprintf(L"----Operation Terminated.----");
		return;
	}
	Table<CommodityData>* table = datahandler.get_commodity_table();
	CommodityData* cd = table->find_byID(id);
	if (cd != nullptr)
	{
		if (isign == 1 && user->get_balance() < cd->get_price() * quantity) {
			wprintf(L"-----Insufficient balance in your account! Operation Terminated.-----");
			return;
		}
		else if (cd->get_commodity_state() == OFF_SHELF) {
			wprintf(L"-----No commodity found! Operation Terminated.-----");
			return;
		}
		else if (quantity > cd->get_quantity() || cd->get_quantity() == 0)
		{
			wprintf(L"-----Insufficient quantity! Operation Terminated.-----");
			return;
		}
		else if (quantity <= 0) {
			wprintf(L"----Operation Terminated.----");
			return;
		}
		wprintf(L"The commodity you choose:\n");
		putnch('*', 30);
		wprintf(L"The commodity ID is: ");
		wcout << cd->get_id() << endl;
		wprintf(L"The commodity name is: ");
		wcout << cd->name << endl;
		wprintf(L"The quantity you choose is:");
		wcout << quantity << endl;
		if (isign == 1) {
			wprintf(L"The transaction time is:");
			wcout << datahandler.get_current_time() << endl;
			wprintf(L"Your balance after purchasing is: ");
			wcout << user->get_balance() - cd->get_price() * quantity << endl;
		}
		putnch('*', 30);
		wprintf(L"Please confirm your choice (y/n): ");
		wchar_t sign;
		InputHandler::inputConfirm(sign);
		if (sign == 'y')
		{
			if (isign == 1) { // Purchase now
				wstringstream wss;
				wstring command;
				user->set_balance(user->get_balance() - cd->get_price() * quantity);
				wss << L"UPDATE user SET balance = " << user->get_balance()\
					<< L" WHERE userID = " << user->get_id();
				command = wss.str();
				sql_interpreter.interpret(command);

				wss.str(L" ");
				wss.seekg(0);
				wss << L"INSERT INTO order VALUES (" << datahandler.generate_order_id() << ',' \
					<< id << ',' << cd->get_price() << ','\
					<< quantity << ',' << datahandler.get_current_time() << ',' << cd->get_seller_id() \
					<< ',' << user->get_id() << ')';
				command = wss.str();
				sql_interpreter.interpret(command);
				sql_interpreter.log(command);

				wss.str(L" ");
				wss.seekg(0);
				wss << L"UPDATE commodity SET number = " << cd->get_quantity() - quantity \
					<< " WHERE commodityID = " << id;
				command = wss.str();
				sql_interpreter.interpret(command);
				sql_interpreter.log(command);

				if (cd->get_quantity() == 0)
				{
					command = L"UPDATE commodity SET state = removed WHERE commodityID = ";
					command += id;
					sql_interpreter.interpret(command);
					sql_interpreter.log(command);
				}
				wprintf(L"-----Purchase successful!-----");
			}
			else if (isign == 2) { // add to the cart
				wstringstream wss;
				OrderData od;
				od.buyer_id = user->get_id();
				od.commodity_id = cd->get_id();
				od.quantity = quantity;
				od.price = cd->get_price();
				od.seller_id = cd->get_seller_id();
				user->cart.push_back(od);
				datahandler.add_cart(od);
				wprintf(L"-----Successful!-----");
			}
		}
	}
	else {
		wprintf(L"No commodity found! Operation Terminated.");
	}
}

void BuyerMenu::search_commodity(UserData* user)
{
	wstring name;
	wprintf(L"Please enter a commodity's name:");
	if (!InputHandler::inputString(name, 20, false, true)) { //name
		InputHandler::throwError();
		return;
	}
	wstring command(L"SELECT * FROM commodity WHERE commodityName CONTAINS ");
	command += name;
	list<pair<CommodityData, int>>* _list = (list<pair<CommodityData, int>>*)sql_interpreter.interpret(command);
	char csign = ' ';
	putnch('*', 40);
	wprintf(L"---Please select the sorting order.---\n");
	// TODO: can add more
	wprintf(L"   (Default) enter for by relevance \n");
	wprintf(L"   1 for by price (low->high)\n");
	wprintf(L"   2 for by price (high->low)\n");
	putnch('*', 40);
	wprintf(L"Please enter the sorting order: ");
	csign = getchar();
	//wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	wcout << endl;
	if (csign == '1') {
		_list->sort([](pair<CommodityData, int>& p1, pair<CommodityData, int>& p2) {
			return p1.first.get_price() < p2.first.get_price();
			});
	}
	else if (csign == '2') {
		_list->sort([](pair<CommodityData, int>& p1, pair<CommodityData, int>& p2) {
			return p1.first.get_price() > p2.first.get_price();
			});
	}
	formatting_output(_list);
	sql_interpreter.interpret(command);
	if (csign != '\n')
		wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	delete _list;
}

void BuyerMenu::show_history(UserData* user)
{
	wstring command(L"SELECT * FROM order WHERE buyerID CONTAINS " + user->get_id());
	list<OrderData>* _list = (list<OrderData>*)sql_interpreter.interpret(command);
	formatting_output(_list);
	command = L"SELECT * FROM order";
	sql_interpreter.log(command);
	delete _list;
}

void BuyerMenu::show_detail(UserData* user)
{
	wstring id;
	wprintf(L"Please enter the commodityID:");
	if (!InputHandler::inputString(id, 4, true, true)) {/*id*/
		InputHandler::throwError();
		return;
	}
	CommodityData* cd = datahandler.get_commodity_table()->find_byID(id);
	putnch('*', 30);
	wcout << L"The commodity ID is: " << cd->get_id() << endl;
	wcout << L"The commodity name is: " << cd->name << endl;
	wcout << L"The commodity description is: " << cd->description << endl;
	wcout << L"On sell time is: " << cd->time_on_shelf << endl;
	wcout << L"The price is: " << cd->get_price() << endl;
	wcout << L"The seller ID is:" << cd->get_seller_id() << endl;
	putnch('*', 30);
}

void BuyerMenu::show_cart(UserData* user)
{
	int WIDTH = 15;
	putnch('*', 70);
	wcout << setw(WIDTH) << L"SerialNumber" << setw(WIDTH) << L"commodityID" << setw(WIDTH) << L"unitPrice" << setw(WIDTH) << L"number" \
		<< setw(WIDTH) << L"sellerID" << endl;
	for (int i = 0; i < user->cart.size(); i++) {
		wcout << setw(WIDTH) << i + 1 << setw(WIDTH) << user->cart[i].commodity_id
			<< setw(WIDTH) << user->cart[i].price << setw(WIDTH) << user->cart[i].quantity
			<< setw(WIDTH) << user->cart[i].seller_id << endl;
	}
	putnch('*', 70);
}

void BuyerMenu::modify_cart(UserData* user)
{
	wstring command;
	int serialNumber = 0, quantity = 0;
	wchar_t sign;
	wprintf(L"Please enter the commodity's serial number in the cart:");
	if (!InputHandler::inputInt(serialNumber)) {
		InputHandler::throwError();
		return;
	}
	if (serialNumber > user->cart.size() || serialNumber <= 0) {
		InputHandler::throwError();
		return;
	}
	OrderData& od = user->cart[serialNumber - 1];
	wprintf(L"Please enter the new quantity you want to buy (0 to remove the item):");
	if (!InputHandler::inputInt(quantity)) {
		InputHandler::throwError();
		return;
	}
	if (quantity == 0) {
		putnch('*', 25);
		wcout << L"The order to be removed 's SerialNumber: " << serialNumber << endl;
		wcout << L"The commodity's name: " << datahandler.get_commodity_table()->find_byID(od.commodity_id)->name << endl;
		putnch('*', 25);
		wprintf(L"\nPlease confirm your choice (y/n):");
		InputHandler::inputConfirm(sign);
		if (sign == 'y') {
			user->cart.erase(user->cart.begin() + serialNumber - 1);
			wprintf(L"Operation Successful!\n\n");
		}
		else {
			wprintf(L"Operation Terminated!\n\n");
		}
	}
	else {
		putnch('*', 25);
		wcout << L"The order to be modified 's SerialNumber: " << serialNumber << endl;
		wcout << L"The commodity's name: " << datahandler.get_commodity_table()->find_byID(od.commodity_id)->name << endl;
		wcout << L"The new quantity: " << quantity << endl;;
		putnch('*', 25);
		wprintf(L"\nPlease confirm your choice (y/n):");
		InputHandler::inputConfirm(sign);
		if (sign == 'y') {
			od.quantity = quantity;
			wprintf(L"Operation Successful!\n\n");
		}
		else {
			wprintf(L"Operation Terminated!\n\n");
		}
	}
	datahandler.update_cart();
}

void BuyerMenu::checkout_cart(UserData* user)
{
	wchar_t ch = ' ';
	wprintf(L"This is your current cart.\n");
	show_cart(user);
	wprintf(L"Please confirm (y/n): ");
	InputHandler::inputConfirm(ch);
	if (ch == 'y') {
		for (int i = 0; i < user->cart.size(); i++) {
			OrderData& od = user->cart[i];
			CommodityData* cd = datahandler.get_commodity_table()->find_byID(od.commodity_id);
			if (cd == nullptr) {
				wcout << L"Unexpected Error" << endl;
				continue;
			}
			wcout << "For SerialNumber:" << i + 1 << "| commodityName: " << cd->name;
			putnch('.', 6, false);
			if (od.quantity > cd->get_quantity()) {
				user->cart.erase(user->cart.begin() + i); i--;
				wcout << "Failure: Insufficient stock.\n" << endl;
				continue;
			}
			else if (cd->get_commodity_state() == OFF_SHELF) {
				user->cart.erase(user->cart.begin() + i); i--;
				wcout << "Failure: Unavailable commodity.\n" << endl;
				continue;
			}
			else if (cd->get_price() * od.quantity > user->get_balance()) {
				wcout << "Failure: Insufficient balance.\n" << endl;
				continue;
			}
			wstringstream wss;
			wstring command;
			user->set_balance(user->get_balance() - cd->get_price() * od.quantity);
			wss << L"UPDATE user SET balance = " << user->get_balance()\
				<< L" WHERE userID = " << user->get_id();
			command = wss.str();
			sql_interpreter.interpret(command);

			wss.str(L" ");
			wss.seekg(0);
			wss << L"INSERT INTO order VALUES (" << datahandler.generate_order_id() << ',' \
				<< cd->get_id() << ',' << cd->get_price() << ','\
				<< od.quantity << ',' << datahandler.get_current_time() << ',' << cd->get_seller_id() \
				<< ',' << user->get_id() << ')';
			command = wss.str();
			sql_interpreter.interpret(command);
			sql_interpreter.log(command);

			wss.str(L" ");
			wss.seekg(0);
			wss << L"UPDATE commodity SET number = " << cd->get_quantity() - od.quantity \
				<< " WHERE commodityID = " << cd->get_id();
			command = wss.str();
			sql_interpreter.interpret(command);
			sql_interpreter.log(command);

			if (cd->get_quantity() == 0)
			{
				command = L"UPDATE commodity SET state = removed WHERE commodityID = ";
				command += cd->get_id();
				sql_interpreter.interpret(command);
				sql_interpreter.log(command);
			}
			user->cart.erase(user->cart.begin() + i); i--;
			wprintf(L"Successful!\n");
		}
		//user->cart.clear();
		datahandler.update_cart();
	}
	else {
		wprintf(L"Operation Terminated!\n\n");
		return;
	}
}

void BuyerMenu::check_cart(UserData* user)
{
	int input = 0;
	while (true) {
		putnch('\n', 2);
		putnch('-', 51);
		putnch('*', 12, false);
		wprintf(L"  The Shopping Cart subMenu  ");
		putnch('*', 12);
		wcout << endl;
		wprintf(L"1.Show 2.Modify 3.Checkout 4.Return to BuyerMenu\n");
		putnch('-', 51);
		wprintf(L"Please choose an operation:");
		InputHandler::inputCommand(input, 1, 4);
		if (input == 1) {
			show_cart(user);
			continue;
		}
		else if (input == 2) {
			modify_cart(user);
			continue;
		}
		else if (input == 3) {
			checkout_cart(user);
		}
		else if (input == 4) {
			return;
		}
	}
}

