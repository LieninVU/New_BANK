#include "BILLS.h"






BILLS::BILLS() {}
	

bool BILLS::is_work() {
	bills.open(bills_way);
	if (!bills.is_open()) { bills.close(); return false; }
	else { bills.close(); return true; }
}



vector<string> BILLS::show() {
	bills.open(bills_way);
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
	bills << name << "=" << money;
	bills.close();
}
