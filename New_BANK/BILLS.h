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
	string delete_type = "delete";
	char trash_char;
	string bills_way = "BILLS.txt";
	string credit_way = "CREDIT.txt";
	string history_way = "HISTORY.txt";
	string types_way = "TYPE.txt";
	string purchas_way = "PURCHAS.txt";
	fstream bills;
	string line = "";
	string text = "";
	char sim;
	vector<string> get_file(string way);
	void set_history_purchas(unsigned int id, int money, int type_id, int day, int month, int year);
	void set_history(string money, string bill, string type);
	void change(unsigned int id, int *money/*, int type_id, int day, int month, int year*/);//---- смотри сюжа ----
	int find(int quant, string line, string substr);
public:
	BILLS();
	bool is_work();
	bool is_empty(string way);
	vector<string> show();
	void remove(unsigned int del_id, unsigned int where_id); 
	void create(string name, unsigned int money);
	void credit(unsigned int id, int money);
	void change_purchas(unsigned int id, int money, int type_id, int day, int month, int year);
	int get_credit();
	vector<string> get_history();
	vector<string> get_history_purchas();
	vector<string> get_types();
	void make_type(string name);
	vector<string> get_purcha_type(string data_type, int day, int month, int year, string type_id);
	vector<string> get_purcha_top(string data_type, int day, int month, int year, string type_or_money);
};
