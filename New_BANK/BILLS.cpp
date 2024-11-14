#include "BILLS.h"






BILLS::BILLS() {}
	

bool BILLS::is_work() {
	bills.open(bills_way);
	if (!bills.is_open()) { bills.close(); return false; }
	else { bills.close(); return true; }
}

bool BILLS::is_empty(string way) {
	bills.open(way);
	if (bills.peek() == EOF) {
		bills.close();
		return true;
	}
	else {
		bills.close();
		return false;
	}
}

vector<string> BILLS::get_file(string way) {
	bills.open(way);
	vector<string> arr;
	while (getline(bills, line)) {
		arr.push_back(line);
		line = "";
	}
	bills.close();
	return arr;
}

vector<string> BILLS::get_types() {
	return get_file(types_way);
}


vector<string> BILLS::show() {
	return get_file(bills_way);
}

vector<string> BILLS::get_history() {
	return get_file(history_way);
}

vector<string> BILLS::get_history_purchas() {
	return get_file(purchas_way);
}


void BILLS::create(string name, unsigned int money) {
	if (is_empty(bills_way))
	{
		bills.open(bills_way);
		bills << name << " = " << money;
		bills.close();
	}
	else {
		bills.open(bills_way);
		bills.seekg(0, ios::end);
		bills << "\n" << name << " = " << money;
		bills.close();
	}
	set_history(to_string(money), name, create_type);
}

void BILLS::change(unsigned int id, int *money /*int type_id, int day, int month, int year*/) {
	//id--;
	vector<string> lines = show();
	ofstream file;
	file.open(bills_way);
	file.close();
	int position = lines[id].find(" = ") + 3;
	string old_digits = lines[id].substr(position);
	if ((stoi(old_digits) + *money) < 0) *money = -stoi(old_digits);
	string new_digits = to_string(stoi(old_digits) + *money);
	//if (stoi(new_digits) < 0) { cout << "YOU CAN'T HAVE LESS THAN ZERO"; return; }
	lines[id].replace(position, lines[id].length()-1, new_digits);
	bills.open(bills_way);
	for (string i : lines) { bills << i; if (i != lines[lines.size() - 1]) { bills << "\n"; } }
	bills.close();
	if (*money > 0)set_history(to_string(*money), lines[id], add_type);
	if(*money < 0)set_history(to_string(-*money), lines[id], spend_type);
}



void BILLS::credit(unsigned int id, int money) {
	string your_credit = to_string(get_credit());
	ofstream file;
	change(id, &money);
	//id--;
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
	if (is_empty(credit_way)) { return 0; }
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



void BILLS::remove(unsigned int del_id, unsigned int where_id) {
	if (del_id == 0 || where_id == 0 || where_id == del_id)return;
	del_id--;
	int money;
	vector<string> arr = show();
	int index = arr[del_id].find(" = ");
	money = stoi(arr[del_id].substr(index+3));
	change(where_id, &money);
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






void BILLS::make_type(string name){
	if (is_empty(types_way)) {
		bills.open(types_way);
		bills << name;
	}
	else {
		vector<string> types = get_types();
		bills.open(types_way);
		bool same = true;
		for (string i : types) {
			if (i == name) same = false;
		}
		bills.seekp(0, ios::end);
		if(same) bills << "\n" << name;
	}
	bills.close();
}


void BILLS::change_purchas(unsigned int id, int money, int type_id, int day, int month, int year) {
	change(id, &money);
	if(money < 0) set_history_purchas(id, money, type_id, day, month, year);
}


void BILLS::set_history_purchas(unsigned int id, int money, int type_id, int day, int month, int year) {
	vector<string>receipt = show();
	vector<string>types = get_types();
	if (is_empty(purchas_way)) {
		bills.open(purchas_way);
		bills << "FROM THE BILL: " << receipt[id] << " YOU BOUNGTH ON " << -money << " IN THIS SECTION " << types[type_id] << " AT THIS DATE " << day << ":" << month << ":" << year;
		bills.close();
		return;
	}
	bills.open(purchas_way);
	bills.seekp(0, ios::end);
	bills << "\n" << "FROM THE BILL: " << receipt[id] << " YOU BOUNGTH ON " << -money << " IN THIS SECTION " << types[type_id] << " AT THIS DATE " << day << ":" << month << ":" << year;
	bills.close();
}


vector<string> BILLS::get_purcha_type(string data_type, int day, int month, int year, string type_id) {
	vector <string> purcha = get_history_purchas();
	vector <string> types = get_types();
	vector <string> report = purcha;
	int position = 0;
	int position_end = 0;
	string line;
	if (data_type != "any") {
		report.clear();
		for (int i = 0; i < purcha.size(); i++) {
			position = find(3, purcha[i], ":");
			line = purcha[i].substr(position+1 );
			if (line == to_string(year)) report.push_back(purcha[i]);
		}
		if (data_type != "year") {
			purcha.clear();
			for (int i = 0; i < report.size(); i++) {
				position = find(2, report[i], ":");
				position_end = find(3, report[i], ":");
				line = report[i].substr(position + 1, position_end - position-1);
				if (line == to_string(month)) purcha.push_back(report[i]);
			}
			report = purcha;
		}
		if (data_type == "day") {
			purcha.clear();
			for (int i = 0; i < report.size(); i++) {
				position = report[i].find(" AT THIS DATE ");
				position += 13;
				position_end = find(2, report[i], ":");
				line = report[i].substr(position + 1, position_end - position - 1);
				if (line == to_string(day)) purcha.push_back(report[i]);
			}
			report = purcha;
		}
	}
	if (type_id != "everything") {
		int id = stoi(type_id);
		purcha.clear();
		for (int i = 0; i < report.size(); i++) {
			position = report[i].find(" IN THIS SECTION ");
			position += 16;
			position_end = report[i].find(" AT THIS DATE ");
			line = report[i].substr(position + 1, position_end - position - 1);
			if (line == types[id]) purcha.push_back(report[i]);
		}
		report = purcha;
	}
	else report = purcha;
	return report;

}


int BILLS::find(int quant, string line, string substr) {
	int count = 0;
	size_t position = 0;

	while (count < quant && position < line.length()) {
		position = line.find(substr, position);

		if (position == std::string::npos) {
			return -1; // Подстрока не найдена
		}

		++count;
		position += substr.length(); // Перейти к следующему возможному совпадению
	}

	return (count == quant) ? position - substr.length() : -1;

}

vector<string> BILLS::get_purcha_top(string data_type, int day, int month, int year, string type_or_money) {
	vector<string> b_filter = get_purcha_type(data_type, day, month, year, "everything");
	vector<string> p_filter;
	vector<int> money;
	int position = 0;
	int position_end = 0;
	string line;
	if (type_or_money == "money") {
		for (int i = 0; i < b_filter.size(); i++) {
			position = b_filter[i].find(" YOU BOUNGTH ON ");
			position += 15;
			position_end = b_filter[i].find(" IN THIS SECTION ");
			line = b_filter[i].substr(position + 1, position_end - position - 1);
			money.push_back(stoi(line));
		}
		p_filter = b_filter;
		for (int i = 0; i < money.size() - 1; i++) {
			for (int j = 0; j < money.size() - i - 1; j++) {
				if (money[j] < money[j + 1]) {
					swap(money[j], money[j + 1]);
					swap(p_filter[j], p_filter[j + 1]);
				}
			}
		}
	}
	if (type_or_money == "type") {
		vector<string> types = get_types();
		int coins = 0;
		int dollar;
		string line;
		for (int i = 0; i < types.size(); i++) {
			for (int j = 0; j < b_filter.size(); i++) {
				position = b_filter[j].find(" IN THIS SECTION ");
				position += 17;
				position_end = b_filter[j].find(" AT THIS DATE ");
				line = b_filter[j].substr(position, position_end - position);
				if (types[i] == line) {
					position = b_filter[j].find(" YOU BOUNGTH ON ");
					position += 16;
					position_end = b_filter[j].find(" IN THIS SECTION ");
					line = b_filter[j].substr(position, position_end - position);
					coins += stoi(line);
				}
			}
			p_filter[i] = types[i] + " AMOUNT= " + to_string(coins);
		}
		for (int i = 0; i < p_filter.size()-1; i++) {
			for (int j = 0; j < p_filter.size() - i - 1; j++) {
				position = p_filter[j].find(" AMOUNT = ");
				position_end = p_filter[j + 1].find(" AMOUNT = ");
				position += 10;
				coins = stoi(p_filter[j].substr(position));
				dollar = stoi(p_filter[j + 1].substr(position_end));
				if (coins < dollar) { swap(p_filter[j], p_filter[j + 1]); }
			}
		}
	}
	/*if (type_or_money == "type") {
		vector<string> types = get_types();
		int dollar = 0;
		string otherline;
		for (int i = 0; i < types.size(); i++) {
			for (int j = 0; j < b_filter.size(); j++) {
				position = b_filter[j].find(" IN THIS SECTION ");
				position += 16;
				position_end = b_filter[j].find(" AT THIS DATE ");
				line = b_filter[j].substr(position + 1, position_end - position - 1);
				dollar = 0;
				if (line == types[i]) {
					position = b_filter[j].find(" YOU BOUNGTH ON ");
					position += 15;
					position_end = b_filter[j].find(" IN THIS SECTION ");
					otherline = b_filter[i].substr(position + 1, position_end - position - 1);
					dollar+=(stoi(line));
					line = types[i] + " SUM OF " + to_string(dollar);
					p_filter.push_back(line);
				}
			}
		}
	}*/
	return p_filter;
}