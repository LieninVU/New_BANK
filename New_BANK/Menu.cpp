#include "Menu.h";
using namespace std;


Menu::Menu() {
	int position = 0;
	if (bills.is_empty(bills_way)) { cout << "You are't any BILL"; create_bill(); }
	while (start) {
		system("cls");
		cout << ">BILLS<";
		if (position == 0) { cout << "<="; }
		cout << endl;
		cout << ">CHANGE<";
		if (position == 1) { cout << "<="; }
		cout << endl;
		cout << ">HISTORY<";
		if (position == 2) { cout << "<="; }
		cout << endl;
		cout << ">CREDIT<";
		if (position == 3) { cout << "<="; }
		cout << endl;
		cout << ">REMOVE<";
		if (position == 4) { cout << "<="; }
		cout << endl;
		cout << ">REPORT<";
		if (position == 5) { cout << "<="; }
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
			if (position == 2) { show_history(); }
			if (position == 3) { credit_menu(); } 
			if (position == 4) { remove_menu(); }
			if (position == 5) { report_menu(); }
			break;
		}
		}
		if (position > 5) { position = 5; }
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
		if (position == 0) { cout << "<="; }
		cout << endl;
		cout << ">REDUSE<";
		if (position == 1) { cout << "<="; }
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
		if (position > size+1) { position = size+1; }
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
	unsigned short day = 0;
	unsigned short month = 0;
	unsigned short year = 0;
	system("cls");
	cout << "CHOOSE THE BILL";
	key = _getch();
	int id = bills_menu();
	if (id < 1) { return; }
	id--;
	system("cls");
	cout << "HOW MUCH MONAY DO YOU WANT TO ADD OR SPEND: ";
	int money;
	cin >> money;
	int type = types_menu();
	if (type == 0) return;
	type--;
	while (!correct_data(day, month, year)) {
		system("CLS");
		cout << "WRITE THE DAY: ";
		cin >> day;
		cout << "WRITE THE MONTH: ";
		cin >> month;
		cout << "WRITE THE YEAR: ";
		cin >> year;
	}
	bills.change_purchas(id, money,type, day, month, year);
}

void Menu::show_history() {
	while (true)
	{
		system("cls"); cout << "THE HISTORY" << endl;
		vector<string> arr = bills.get_history();
		for (string i : arr) {
			cout << i << endl;
		}
		key = _getch();
		if (key == 27) return;
	}
}


void Menu::remove_menu() {
	system("cls");
	cout << "SHOOCE WHAT BILL DO YOU WILL DELETE";
	key = _getch();
	unsigned int del = bills_menu();
	system("cls");
	cout << "SHOOCE WHERE DO YOU TRANSFER MONEY";
	key = _getch();
	unsigned int where = bills_menu();
	bills.remove(del, where);
}




int Menu::types_menu() {
	vector<string> types = bills.get_types();
	int size = types.size();
	int position = 0;
	bool exit = true;
	while (exit) {
		system("CLS");
		for (int i = 0; i <= size; i++) {
			if(i < size)cout << ">" << types[i] << "<";
			else cout << "\n" << "+CREATE NEW TYPE+"; 
			if (position == i) cout << "<=";
			cout << endl;
		}
		key = _getch();
		if (key == 224) { key = _getch(); }
		switch (key)
		{
		case 72: position--; break;
		case 80: position++; break;
		case 13: {
			if (position == size) { create_type(); types = bills.get_types(); size = types.size(); }
			else { types.clear(); return position + 1; }
			break;
		}
		case 27: exit = false; break;
		}
		if (position > size + 1) { position = size + 1; }
		if (position < 0) { position = 0; }
	}
	cards.clear();
	position = 0;
	return 0;
}




void Menu::create_type() {
	string name;
	system("CLS");
	cout << "WRITE THE NAME OF THE NEW TYPE: ";
	cin >> name;
	bills.make_type(name);
}


void Menu::report_menu() {
	unsigned short day = 1;
	unsigned short month = 1;
	unsigned int year = 0;
	string type_condition = "everything";
	string type_id;
	string type_data;
	vector<string> report;
	int position = 0;
	bool exit = true;
	while (exit) {
		system("CLS");
		cout << ">GET TYPE REPORT<";
		if (position == 0) { cout << "<="; }
		cout << endl;
		cout << ">GET TOP REPORT<";
		if (position == 1) { cout << "<="; }
		cout << endl;
		key = _getch();
		if (key == 224) { key = _getch(); }
		switch (key)
		{
		case 72: position--; break;
		case 80: position++; break;
		case 13: {
			if (position == 0) {
				type_id = to_string(types_menu());
				if (type_id == "0") {
					type_id = type_condition;
				}
				else type_id = to_string(stoi(type_id)-1);
				type_data = data_type_menu();
				while (!correct_data(day, month, year) && type_data != "any") {
					system("CLS");
					if (type_data == "day") {
						cout << "WRITE THE DAY: ";
						cin >> day;
					}
					if (type_data == "month" || type_data == "day") {
						cout << "WRITE THE MONTH: ";
						cin >> month;
					}
					if (type_data != "any") {
						cout << "WRITE THE YEAR: ";
						cin >> year;
					}
				}
				report = bills.get_purcha_type(type_data, day, month, year, type_id);
			}
			if (position == 1) {
				string money_or_types = money_or_types_menu();
				type_data = data_type_menu();
				while (!correct_data(day, month, year) && type_data != "any") {
					system("CLS");
					if (type_data == "day") {
						cout << "WRITE THE DAY: ";
						cin >> day;
					}
					if (type_data == "month" || type_data == "day") {
						cout << "WRITE THE MONTH: ";
						cin >> month;
					}
					if (type_data != "any") {
						cout << "WRITE THE YEAR: ";
						cin >> year;
					}
				}
				report = bills.get_purcha_top(type_data, day, month, year, money_or_types);
				
			}
			exit = false;
			break;

		}
		case 27: exit = false; break;
		}
		if (position > 1) { position = 1; }
		if (position < 0) { position = 0; }
	}
	system("CLS");
	for (string i : report) {
		cout << i << endl;
	}
	key = _getch();
	
}


string Menu::data_type_menu() {
	string day = "day";
	string month = "month";
	string year = "year";
	string any = "any";
	int position = 0;
	bool exit = true;
	while (exit) {
		system("CLS");
		cout << ">DAY<";
		if (position == 0) { cout << "<="; }
		cout << endl;
		cout << ">MONTH<";
		if (position == 1) { cout << "<="; }
		cout << endl;
		cout << ">YEAR<";
		if (position == 2) { cout << "<="; }
		cout << endl;
		cout << ">ANY<";
		if (position == 3) { cout << "<="; }
		cout << endl;
		key = _getch();
		if (key == 224) { key = _getch(); }
		switch (key)
		{
		case 72: position--; break;
		case 80: position++; break;
		case 13: {
			if (position == 0) return day;
			if (position == 1) return month;
			if (position == 2) return year;
			if (position == 3) return any;
			break;
		}
		case 27: exit = false; break;
		}
		if (position > 3) { position = 3; }
		if (position < 0) { position = 0; }
	}
}

string Menu::money_or_types_menu() {
	int position = 0;
	bool exit = true;
	while (exit) {
		system("CLS");
		cout << ">MONEY<";
		if (position == 0) { cout << "<="; }
		cout << endl;
		cout << ">TYPES<";
		if (position == 1) { cout << "<="; }
		cout << endl;
		key = _getch();
		if (key == 224) { key = _getch(); }
		switch (key)
		{
		case 72: position--; break;
		case 80: position++; break;
		case 13: {
			if (position == 0) return "money";
			if (position == 1) return "type";
			break;
		}
		case 27: exit = false; break;
		}
		if (position > 1) { position = 1; }
		if (position < 0) { position = 0; }
	}
}

bool Menu::correct_data(unsigned int day, unsigned int month, unsigned int year) {
	// Проверка диапазонов значений
	if (month < 1 || month > 12)
		return false;
	if (year == 0) return false;
	// Массив дней в месяцах обычного года
	static const unsigned char days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	// Рассматриваем февраль отдельно, чтобы учесть високосные годы
	if (month == 2) {
		if (((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
			return (day >= 1 && day <= 29);
		else
			return (day >= 1 && day <= 28);
	}

	// Для остальных месяцев используем массив
	return (day >= 1 && day <= days_in_month[month - 1]);
}