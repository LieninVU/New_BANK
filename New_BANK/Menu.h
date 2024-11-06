#pragma once
#include <iostream>
#include <vector>
#include <conio.h>
#include "BILLS.h"
using namespace std;


class Menu {
	int key;
	short position = 0;
	unsigned int money;
	BILLS bills = BILLS();
	vector<string> cards;
	bool start = true;
	void credit();
	void bills_menu();
	void create_bill();
public:
	Menu();

};

