#pragma once
#include <iostream>
#include <vector>
#include <conio.h>
#include "BILLS.h"
using namespace std;


class Menu {
	int key;
	short position;
	unsigned int money;
	BILLS bills = BILLS();
	vector<string> cards;
	bool start = true;
	void credit();
	void bills_menu();
public:
	Menu();

};

