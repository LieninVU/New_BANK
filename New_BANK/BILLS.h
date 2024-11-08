#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#pragma once




class BILLS {
	string create_type = "create";
	string add_type = "add";
	string spend_type = "spend";
	string take_credit_type = "take_credit";
	string reduce_credit_type = "reduce_credit";
	char trash_char;
	string bills_way = "BILLS.txt";
	string credit_way = "CREDIT.txt";
	string history_way = "HISTORY.txt";
	fstream bills;
	string line = "";
	string text = "";
	char sim;
	void set_history(string money, string bill, string type);
public:
	BILLS();
	bool is_work();
	bool is_empty();
	vector<string> show();
	void change(unsigned int id, int money);
	void remove(int id); // осталось только это
	void create(string name, unsigned int money);
	void credit(unsigned int id, int money);
	int get_credit();
	vector<string> get_history();
};
