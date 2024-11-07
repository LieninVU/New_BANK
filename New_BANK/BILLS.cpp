#include "BILLS.h"






BILLS::BILLS() {}
	

bool BILLS::is_work() {
	bills.open(bills_way);
	if (!bills.is_open()) { bills.close(); return false; }
	else { bills.close(); return true; }
}

bool BILLS::is_empty() {
	bills.open(bills_way);
	bills.seekg(0, ios::end);
	bool empty = bills.tellg() == 0;
	bills.close();
	return empty;
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
	vector<string> lines;
	while (getline(bills, line)) {
		lines.push_back(line);
		line = "";
	}
	bills.close();

	ofstream file;
	file.open(bills_way);
	file.close();
	bills.open(bills_way);
	for (string i : lines) { bills << i << "\n"; }
	bills << name << " = " << money;
	bills.close();
}

void BILLS::change(unsigned int id, int money) {
	id--;
	bills.open(bills_way);
	vector<string> lines;
	while (getline(bills, line)) {
		lines.push_back(line);
		line = "";
	}
	bills.close();
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
}



void BILLS::credit(unsigned int id, int money) {
	string your_credit = "0";
	ofstream file;
	change(id, money);
	id--;
	bills.open(credit_way);
	if (bills.peek() != EOF) { getline(bills, your_credit); }
	bills.close();
	file.open(credit_way);
	file.close();
	bills.open(credit_way);
	if (money > 0) { bills << to_string(static_cast<int>(stoi(your_credit) + (money * 1.2))); }
	if(money < 0) { 
		if(stoi(your_credit) < money*-1){ cout << "YOU CAN'T HAVE LESS THAN ZERO"; return; }
		bills << (stoi(your_credit) + money); 
	}
	bills.close();
}

int BILLS::get_credit() {
	string line;
	bills.open(credit_way);
	if (bills.peek() == EOF) { return 0; }
	getline(bills, line);
	bills.close();
	return stoi(line);
}
