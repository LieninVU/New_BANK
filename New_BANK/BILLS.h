#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#pragma once




class BILLS {
	string bills_way = "BILLS.txt";
	fstream bills;
	string line = "";
	string text = "";
	vector <string> cards;
	char sim;
public:
	BILLS();
	bool is_work();
	vector<string> show();
	void change(unsigned int id, int money);
	void remove(int id);
	void create(string name, unsigned int money);
};
