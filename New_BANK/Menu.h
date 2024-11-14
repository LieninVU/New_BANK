#pragma once
#include <iostream>
#include <vector>
#include <conio.h>
#include "BILLS.h"
using namespace std;


class Menu {
	int key;
	string bills_way = "BILLS.txt";
	//short position = 0;
	//unsigned int money;
	char trash_char;
	BILLS bills = BILLS();
	vector<string> cards;
	bool start = true;
	void credit_menu();
	int bills_menu();
	void create_bill();
	void change_menu();
	void show_history();
	void remove_menu();
	int types_menu();
	void create_type();
	void report_menu();
	string data_type_menu();
	string money_or_types_menu();
	bool correct_data(unsigned int day, unsigned int month, unsigned int year);
public:
	Menu();

};

