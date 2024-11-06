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
