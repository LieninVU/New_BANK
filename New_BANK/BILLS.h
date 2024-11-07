#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#pragma once




class BILLS {
	char trash_char;
	string bills_way = "BILLS.txt";
	string credit_way = "CREDIT.txt";
	fstream bills;
	string line = "";
	string text = "";
	char sim;
public:
	BILLS();
	bool is_work();
	bool is_empty();
	vector<string> show();
	void change(unsigned int id, int money);
	void remove(int id);
	void create(string name, unsigned int money);
	void credit(unsigned int id, int money);
	int get_credit();

};
