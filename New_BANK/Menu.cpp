#include "Menu.h";
using namespace std;



Menu::Menu() {
	if (!bills.is_work()) { cout << "txt bills file isn't open"; start = false; }
	if (bills.is_empty()) { cout << "You are't any BILL"; create_bill(); }
	while (start) {
		system("cls");
		cout << ">BILLS<";
		if (position == 0) { cout << "<"; }
		cout << endl;
		cout << ">BUY<";
		if (position == 1) { cout << "<"; }
		cout << endl;
		cout << ">ADD<";
		if (position == 2) { cout << "<"; }
		cout << endl;
		cout << ">HISTORY<";
		if (position == 3) { cout << "<"; }
		cout << endl;
		cout << ">CREDIT<";
		if (position == 4) { cout << "<"; }
		cout << endl;
		key = _getch();
		if (key == 224) { key = _getch(); }
		switch (key)
		{
		case 72: position--; break;
		case 80: position++; break;
		case 13: {
			if (position == 0) { bills_menu(); }
			if (position == 1) { system("cls"); cout << "WHRITE DOWN HOW COST IS IT" << endl; cin >> money; }
			if (position == 2) { system("cls"); cout << "WHRITE DOWN HOW MANY YOU WANT TO ADD" << endl; cin >> money; }
			if (position == 3) { system("cls"); cout << "THE HISTORY OF YOUR PURCHAS" << endl; cin >> money; }
			if (position == 4) { credit(); } 
			break;
		}
		}
		if (position > 4) { position = 4; }
		if (position < 0) { position = 0; }

	}
}


void Menu:: credit() {
	position = 0;
	bool exit = true;
	while (exit) {
		system("cls");
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
		case 13: position; break;
		case 27: exit = false; break;
		}
		if (position > 1) { position = 1; }
		if (position < 0) { position = 0; }
	}
}


void Menu::bills_menu() {
	position = 0;
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
			if (position == size) { create_bill(); }
			break;
		}
		case 27: exit = false; break;
		}
		if (position > size) { position = size; }
		if (position < 0) { position = 0; }
	}
	cards.clear();
	position = 0;
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