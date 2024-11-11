#pragma once
#include <iostream>
#include <vector>
#include <conio.h>
#include "BILLS.h"
using namespace std;


class Menu {
	int key;
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
public:
	Menu();

};

