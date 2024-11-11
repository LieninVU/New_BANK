#include "BILLS.h"






BILLS::BILLS() {}
	

bool BILLS::is_work() {
	bills.open(bills_way);
	if (!bills.is_open()) { bills.close(); return false; }
	else { bills.close(); return true; }
}

bool BILLS::is_empty() {
	bills.open(bills_way);
	if (bills.tellg() == EOF) {
		bills.close();
		return true;
	}
	else {
		bills.close();
		return false;
	}
}



vector<string> BILLS::show() {
	bills.open(bills_way);
	vector <string> cards;
	while (!bills.eof()) {
		getline(bills, line);
		cards.push_back(line);
		line = "";
	}
	bills.close();
	return cards;
}


void BILLS::create(string name, unsigned int money) {
	bills.open(bills_way);
	if (bills.is_open())
	{
		bills.seekg(0, ios::end);
		bills << "\n" << name << " = " << money;
	}
	else bills << name << " = " << money;
	bills.close();
	set_history(to_string(money), name, create_type);
}

void BILLS::change(unsigned int id, int money) {
	id--;
	vector<string> lines = show();
	ofstream file;
	file.open(bills_way);
	file.close();
	int position = lines[id].find(" = ") + 3;
	string old_digits = lines[id].substr(position);
	string new_digits = to_string(stoi(old_digits) + money);
	if (stoi(new_digits) < 0) { cout << "YOU CAN'T HAVE LESS THAN ZERO"; return; }
	lines[id].replace(position, lines[id].length()-1, new_digits);
	bills.open(bills_way);
	for (string i : lines) { bills << i; if (i != lines[lines.size() - 1]) { bills << "\n"; } }
	bills.close();
	if (money > 0)set_history(to_string(money), lines[id], add_type);
	if(money < 0)set_history(to_string(-money), lines[id], spend_type);
}



void BILLS::credit(unsigned int id, int money) {
	string your_credit = to_string(get_credit());
	ofstream file;
	change(id, money);
	id--;
	file.open(credit_way);
	file.close();
	bills.open(credit_way);
	if (money > 0) { bills << to_string(static_cast<int>(stoi(your_credit) + (money * 1.2))); }
	if(money < 0) { 
		if(stoi(your_credit) < money*-1){ cout << "YOU CAN'T HAVE LESS THAN ZERO"; return; }
		bills << (stoi(your_credit) + money); 
	}
	bills.close();
	if (money > 0) set_history(to_string(static_cast<int>(money * 1.2)), your_credit, take_credit_type);
	if(money < 0) set_history(to_string(-money), your_credit, reduce_credit_type);
}

int BILLS::get_credit() {
	string line;
	bills.open(credit_way);
	if (bills.peek() == EOF) { return 0; }
	getline(bills, line);
	bills.close();
	return stoi(line);
}


void BILLS::set_history(string money, string bill, string type) {
	bills.open(history_way);
	bills.seekp(0, ios::end);
	if (type == create_type) bills << "you create the bill: " << bill << " = " << money;
	else if (type == add_type) bills << "this bill: " << bill << " was grow to: " << money;
	else if (type == spend_type) bills << "this bill: " << bill << " was reduce to: " << money;
	else if (type == take_credit_type) bills << "your credit: " << bill << " was grow to: " << money;
	else if (type == reduce_credit_type) bills << "this credit: " << bill << " was reduce to: " << money;
	else if (type == delete_type) bills << "this bill was deleted: " << bill;
	bills << "\n";
	bills.close();


}

vector<string> BILLS::get_history() {
	bills.open(history_way);
	vector<string> history;
	while (getline(bills, line)) {
		history.push_back(line);
		line = "";
	}
	bills.close();
	return history;
}


void BILLS::remove(unsigned int del_id, unsigned int where_id) {
	if (del_id == 0 || where_id == 0 || where_id == del_id)return;
	del_id--;
	int money;
	vector<string> arr = show();
	int index = arr[del_id].find(" = ");
	money = stoi(arr[del_id].substr(index+3));
	change(where_id, money);
	set_history("", arr[del_id], delete_type);
	arr = show();
	arr.erase(arr.begin() + del_id);
	ofstream file;
	file.open(bills_way);
	file.close();
	bills.open(bills_way);
	for (int i = 0; i < arr.size(); i++) {
		bills << arr[i];
		if (i != arr.size()-1) bills << "\n";
	}
	bills.close();
}
