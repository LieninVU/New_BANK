#include "Menu.h";
using namespace std;


Menu::Menu() {
	int position = 0;
	if (!bills.is_work()) { cout << "txt bills file isn't open"; start = false; }
	if (bills.is_empty()) { cout << "You are't any BILL"; create_bill(); }
	while (start) {
		system("cls");
		cout << ">BILLS<";
		if (position == 0) { cout << "<"; }
		cout << endl;
		cout << ">CHANGE<";
		if (position == 1) { cout << "<"; }
		cout << endl;
		cout << ">HISTORY<";
		if (position == 2) { cout << "<"; }
		cout << endl;
		cout << ">CREDIT<";
		if (position == 3) { cout << "<"; }
		cout << endl;
		key = _getch();
		if (key == 224) { key = _getch(); }
		switch (key)
		{
		case 72: position--; break;
		case 80: position++; break;
		case 13: {
			if (position == 0) { bills_menu(); }
			if (position == 1) { change_menu(); }
			if (position == 2) { system("cls"); cout << "THE HISTORY OF YOUR PURCHAS" << endl; cin >> trash_char; }
			if (position == 3) { credit_menu(); } 
			break;
		}
		}
		if (position > 3) { position = 3; }
		if (position < 0) { position = 0; }

	}
}


void Menu:: credit_menu() {
	int position = 0;
	bool exit = true;
	unsigned int money = 0;
	unsigned int id = 0;
	while (exit) {
		system("cls");
		cout << "YOUR CREDIT: " << bills.get_credit() << endl;
		cout << ">GET<";
		if (position == 0) { cout << "<"; }
		cout << endl;
		cout << ">REDUSE<";
		if (position == 1) { cout << "<"; }
		cout << endl;
		key = _getch();
		if (key == 224) { key = _getch(); }
		switch (key)
		{
		case 72: position--; break;
		case 80: position++; break;
		case 13: {
			if (position == 0) {
				cout << "CREDIT PERCENT == 20%\nWRITE IT DOWN HOW MUSH MONEY DO YOU WANT TO TAKE: ";
				cin >> money;
				cout << "CHOOSE THE BILL WHICH GET A CREDIT";
				cin >> trash_char;
				id = bills_menu();
				bills.credit(id, money);
			}
			if (position == 1) {
				cout << "CHOOsE FROM WHICH BILL YOU TAKE A MONAY FOR REDUCE A CREDIT";
				cin >> trash_char;
				id = bills_menu();
				cout << "WRITE IT DOWN HOW MUCH MOHEY YOU WANT TO TAKE: ";
				cin >> money;
				bills.credit(id, money*-1);
			}
			break;
		}
		case 27: exit = false; break;
		}
		if (position > 1) { position = 1; }
		if (position < 0) { position = 0; }
	}
}


int Menu::bills_menu() {
	int position = 0;
	bool exit = true;
	cards = bills.show();
	int size = cards.size();
	while (exit) {
		system("cls");
		for (int i = 0; i <= size; i++) {
			if(i < size)cout << i << ". " << cards[i];
			if (i == size) { cout << "\n" << "+CREATE NEW BILL+";  }
			if (position == i) { cout << "< " << position; }
			cout << endl;
		}
		key = _getch();
		if (key == 224) { key = _getch(); }
		switch (key)
		{
		case 72: position--; break;
		case 80: position++; break;
		case 13: {
			if (position == size) { create_bill(); cards = bills.show(); size = cards.size(); }
			else { cards.clear(); return position+1; }
			break;
		}
		case 27: exit = false; break;
		}
		if (position > size) { position = size; }
		if (position < 0) { position = 0; }
	}
	cards.clear();
	position = 0;
	return 0;
}

void Menu::create_bill() {
	string name;
	unsigned int money;
	cout << "Write it down your bill's name:";
	cin >> name;
	cout << "Write it down how much money your bill has:";
	cin >> money;
	bills.create(name, money);

}


void Menu::change_menu() {
	system("cls");
	cout << "CHOOSE THE BILL";
	cin >> new char;
	int id = bills_menu();
	if (id < 1) { return; }
	system("cls");
	cout << "HOW MUCH MONAY DO YOU WANT TO ADD OR SPEND";
	int money;
	cin >> money;
	bills.change(id, money);
}