#include "admin.h"
#include "integrity_check.h"
#include <iostream>
//#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include "string_function.h"
#include <filesystem>
#include <sstream>

using namespace std;
namespace fls = std::filesystem;




void admin_prompt() {
	//system("cls");
	printf("Admin> ");
	string s;
	cin.clear();
	getline(cin, s);
	cin.clear();
	vector<string> v(1000);
	v = split_space(s);
	admin_check(v);

}

void admin_show_airplane(vector<string> v) {
	if (v.size() >= 3) {
		h_list();
		admin_prompt();
		return;
	}

	if (v.size() == 2) {
		string s = v[1];

		if (s.size() != 6) {
			error();
			return;
		}
		else {
			for (int i = 0; i < 3; i++) {
				if (!(s[i] >= 'A' && s[i] <= 'Z')) {
					error();
					return;
				}
				if (!(s[i + 3] >= '0' && s[i + 3] <= '9')) {
					error();
					return;
				}
			}
		}

		string dir = "./data/airplane";
		vector<string> paths;
		if (_access(dir.c_str(), 0) != -1) {
			for (auto& p : std::filesystem::directory_iterator(dir)) {
				paths.push_back(p.path().string());
			}
		}
		int is_find = -1;
		for (int l = 0; l < paths.size(); l++) {
			string temp_str = split_backslash(paths[l]).back().substr(0, 6);
			if (temp_str == s) {
				is_find = l;
				break;
			}
		}
		if (is_find == -1) {
			cout << "There is no flight " << s << endl;
		}
		else {
			string airplaneData;
			string data_in;
			ifstream ifs2(paths[is_find]);
			if (ifs2.is_open()) {
				getline(ifs2, airplaneData);
				vector<string> print_data = split_user_data(airplaneData);
				cout << print_data[0] << ' ';
				cout << print_data[1].substr(0, 3) << '/' << print_data[1].substr(3, 3) << ' ';
				cout << print_data[2].substr(0, 12) << '~' << print_data[2].substr(12, 12) << ' ';
				cout << print_data[3] << ' ';
				cout << print_data[4][0] << ',' << print_data[4][2];
				while (!ifs2.eof()) {
					cout << " res" << endl;
					getline(ifs2, airplaneData);
					string res_user = split_user_data(airplaneData)[0];
					ifstream user_ifs("./data/Userlist.txt");
					while (!user_ifs.eof()) {
						getline(user_ifs, data_in);
						if (res_user == split_user_data(data_in)[0]) {
							for (int i = 0; i < 5; i++) {
								cout << split_user_data(data_in)[i] << ' ';
							}
							cout << split_user_data(data_in)[1] << endl;
							break;
						}
					}
					user_ifs.close();
				}
				ifs2.close();
			}
		}
	}
	else if (v.size() == 1) {
		string dir = "./data/airplane";
		vector<string> paths;
		if (_access(dir.c_str(), 0) != -1) {
			for (auto& p : std::filesystem::directory_iterator(dir)) {
				paths.push_back(p.path().string());
			}
		}
		string airplaneData;
		for (int i = 0; i < paths.size(); i++) {
			ifstream ifs2(paths[i]);
			if (ifs2.is_open()) {
				getline(ifs2, airplaneData);
				vector<string> print_data = split_user_data(airplaneData);
				cout << print_data[0] << ' ';
				cout << print_data[1].substr(0, 3) << '/' << print_data[1].substr(3, 3) << ' ';
				cout << print_data[2].substr(0, 12) << '~' << print_data[2].substr(12, 12) << ' ';
				cout << print_data[3] << ' ';
				cout << print_data[4][0] << ',' << print_data[4][2];
				while (!ifs2.eof()) {
					cout << " res";
					break;
				}
				cout << endl;
				ifs2.close();
			}
		}
	}
	admin_prompt();
	return;
}

int choice() {
	int choice;
	scanf_s("%d", &choice);
	return choice;
}

void admin_check(vector<string> v) {
	if (v.size() == 0) {
		admin_show_guide();
		admin_prompt();
		return;
	}
	string cmd = v[0];
	if (cmd == "add" || cmd == "a" || cmd == "ad") {
		if (v.size() == 6) {
			if (admin_flight_is_exist(v) == 1) {
				if ((admin_check_add(v).size() == 6)) {
					v = admin_check_add(v);
					admin_add(v);
				}
			}
		}
		else {
			h_add();
		}

	}
	else if (v.size() == 2 && (cmd == "cancel" || cmd == "cance" || cmd == "canc" || cmd == "can" || cmd == "ca" || cmd == "c")) admin_cancel(v[1]);
	else if (cmd == "edit" || cmd == "edi" || cmd == "ed" || cmd == "e") admin_edit(v);
	else if (cmd == "list" || cmd == "lis" || cmd == "li" || cmd == "l") admin_show_airplane(v);
	else if (cmd == "quit" || cmd == "qui" || cmd == "qu" || cmd == "q") admin_quit();
	else if (cmd == "help" || cmd == "hel" || cmd == "he" || cmd == "h") admin_help(v);
	else if (cmd == "user" || cmd == "use" || cmd == "us" || cmd == "u") {
		if (v.size() != 2)
			error();
		else
			admin_show_user(v[1]);
	}
	else if (cmd == "test" || cmd == "tes" || cmd == "te" || cmd == "t") {
		if (v.size() == 1)
			integrity_check();
		else error();
	}
	else error();

	admin_prompt();
	return;
}

vector<string> admin_check_add(vector<string> v) {
	/*for (auto i : v) {
		cout << i << " ";
	}*/
	vector<string> errorvertor;
	if (v.size() < 6 || v.size() > 6) {
		error(); h_add(); return errorvertor;
	}
	string planename = v[1];
	string departture_destination = v[2];
	string time = v[3];
	string price = v[4];
	string seats = v[5];


	for (int i = 0; i < 3; i++) {
		if (admin_check_argv(planename[i]) != '!') {}
		else {
			error();
			h_add();
			return errorvertor;
		}
		planename[i] = admin_check_argv(planename[i]);
	}
	v[1] = planename;

	for (int i = 3; i < 6; i++) {
		if (planename[i] < '0' && planename[i] > '9')
		{
			error();
			h_add();
			return errorvertor;
		}
	}
	for (int j = 0; j < 3; j++) {
		if (admin_check_argv(departture_destination[j]) != '!') {
			departture_destination[j] = admin_check_argv(departture_destination[j]);
		}
		else {
			error();
			h_add();
			return errorvertor;
		}
	}
	if (departture_destination[3] == '/' || departture_destination[3] == ',' || departture_destination[3] == '-') {
	}
	else {
		error();
		h_add();
		return errorvertor;
	}
	for (int j = 4; j < 7; j++) {
		if (admin_check_argv(departture_destination[j]) != '!') {
			departture_destination[j - 1] = admin_check_argv(departture_destination[j]);
		}
		else {
			error();
			h_add();
			return errorvertor;
		}
		if (j == 6) {
			departture_destination[j] = NULL;
		}
	}
	departture_destination.resize(6);
	/*string d = "abcdef";
	for (int i = 0; i < 6; i++) {
		d[i] = departture_destination[i];
	}
	*/
	v[2] = departture_destination;
	
	
	/**********time****************/
	string newTime;
	newTime.clear();
	string division_char = "-,~";
	if (v[3].size() == 25) {
		if (division_char.find(v[3][12]) == string::npos) {    // Delimiter?
			h_add();
			return errorvertor;
		}
		else if (v[3].substr(0, 2) != "20" || v[3].substr(13, 2) != "20") { //2000 up?
			h_add();
			return errorvertor;
		}
		else {
			for (auto i : v[3]) {
				if (division_char.find(i) == string::npos) {           //except Delimiter
					newTime += i;
				}
			}
		}
	}
	else if (v[3].size() == 21) {
		if (division_char.find(v[3][10]) == string::npos) {    // Delimiter?
			h_add();
			return errorvertor;
		}
		else {
			for (auto i : v[3]) {
				if (division_char.find(i) == string::npos) {           //except Delimiter
					newTime += i;
				}
			}
			newTime.insert(0, "20");
			newTime.insert(12, "20");
		}
	}
	else {
		h_add();
		return errorvertor;
	}
	
	/************time condition*************/
		int day_for_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int depTime = stoi(newTime.substr(4, 8));
		int arrTime = stoi(newTime.substr(16,8));
		int depYear = stoi(newTime.substr(0,4));
		int arrYear = stoi(newTime.substr(12, 4));
		int depMonth = stoi(newTime.substr(4, 2));
		int arrMonth = stoi(newTime.substr(16, 2));
		if (depYear < 2022 ||depYear > arrYear) {
			h_add();
			return errorvertor;
		}
		else if (depTime < 10030000 ||depTime >= arrTime) {
			h_add();
			return errorvertor;
		}
		else if (depMonth > 12 || depMonth == 00 || arrMonth > 12 || arrMonth == 00) {
			h_add();
			return errorvertor;
		}
		else if (stoi(newTime.substr(6, 2)) > day_for_month[depMonth - 1] || stoi(newTime.substr(18, 2)) > day_for_month[arrMonth - 1]) {
			h_add();
			return errorvertor;
		}
		v[3] = newTime;
	


	string newprice = "";
	for (char& c : price) {
		if (c == ',') {
		}
		else if (check_integer(c) == 0) {
			newprice += c;
		}
		else {
			error(); return errorvertor;
		}
	}
	v[4] = newprice;
	if (check_integer(seats[0]) == -1 || (seats[1] != ',' && seats[1] != '*' && seats[1] != '-') || check_integer(seats[2]) == -1) {
		error(); return errorvertor;
	}
	seats[1] = '*';
	v[5] = seats;
	return v;

}

int admin_add(vector<string> v) {
	string line;
	string fname = "./data/airplane/" + v[1] + ".txt";

	fls::path p("./data");
	if (!fls::exists(p))
		fls::create_directory(p);

	fls::path p2("./data/airplane");
	if (!fls::exists(p2))
		fls::create_directory(p2);


	ofstream fs(fname, std::ios_base::out | std::ios_base::app);
	if (fs.is_open()) {
		fs << "^";
		for (vector<string>::iterator iter = v.begin() + 1; iter != v.end(); iter++) {
			fs << *iter << "^";
		}
		fs.close();
	}
	cout << "Add success\n";
	return 1;
}


void admin_cancel(string s) {
	string planename = s;

	if (s.size() != 6) {
		error(); return;
	}

	for (int i = 0; i < 3; i++) {
		if (planename[i] = admin_check_argv(planename[i]) != '!') {}
		else {
			error();
			return;
		}
	}

	for (int i = 3; i < 6; i++) {
		if (planename[i] < '0' && planename[i] > '9')
		{
			error();
			return;
		}
	}

	fls::path paths("./data/airplane/" + s + ".txt");
	if (!fls::exists(paths)) {
		cout << "There is no flight "" << s << """ << endl;
		return;
	}
	int r = remove(paths);
	cout << "Seat cancellation complete\n";
	admin_prompt();
}

void admin_edit(vector<string> v) {
	if (v.size() != 6) {
		error();
		h_edit();
		admin_prompt();
	}
	string s = v[1];

	if (s.size() != 6) {
		error();
		return;
	}
	else {
		for (int i = 0; i < 3; i++) {
			if (admin_check_argv(s[i]) != '!') {
				s[i] = admin_check_argv(s[i]);
			}
			if (!(s[i + 3] >= '0' && s[i + 3] <= '9')) {
				error();
				return;
			}
		}
	}
	v[1] = s;
	string dir = "./data/airplane";
	vector<string> paths;
	if (_access(dir.c_str(), 0) != -1) {
		for (auto& p : std::filesystem::directory_iterator(dir)) {
			paths.push_back(p.path().string());
		}
	}
	int is_find = -1;
	for (int l = 0; l < paths.size(); l++) {
		string temp_str = split_backslash(paths[l]).back().substr(0, 6);
		if (temp_str == s) {
			is_find = l;
			break;
		}
	}
	if (is_find == -1) {
		std::cout << "There is no flight \"" << v[1] << "\"" << endl;
	}
	else {
		for (int i = 0; i < 3; i++) {
			if (!(v[2][i] >= 'A' && v[2][i] <= 'Z')) {
				error();
				return;
			}
			if (!(v[2][i + 4] >= 'A' && v[2][i + 4] <= 'Z')) {
				error();
				return;
			}
		}
		if (v[2][3] != '/' && v[2][3] != ',' && v[2][3] != '-') {
			error();
			return;
		}
		string mod_str = v[3];
		if (mod_str[12] != '~' && mod_str[12] != ',' && mod_str[12] != '-') {
			error();
			return;
		}
		mod_str = mod_str.substr(0, 12) + mod_str.substr(13, 12);
		if (!(check_time(mod_str))) {
			error();
			return;
		}

		string newprice = "";
		for (char& c : v[4]) {
			if (c == ',') {
			}
			else if (check_integer(c) == 0) {
				newprice += c;
			}
			else { error(); return; }
		}
		v[4] = newprice;
		if (v[5][0] < '0' || v[5][0] > '9') {
			error();
			return;
		}
		if (v[5][1] != '*' && v[5][1] != '-' && v[5][1] != ',') {
			error();
			return;
		}
		if (v[5][2] < '0' || v[5][2] > '9') {
			error();
			return;
		}

		string plane_path = "./data/airplane/" + s + ".txt"; \
			const char* path = plane_path.c_str();
		int r = remove(path);

		string line;
		string fname = "./data/airplane/" + v[1] + ".txt";

		fls::path p("./data");
		if (!fls::exists(p))
			fls::create_directory(p);

		fls::path p2("./data/airplane");
		if (!fls::exists(p2))
			fls::create_directory(p2);
		ofstream fs(fname, std::ios_base::out | std::ios_base::app);
		if (fs.is_open()) {
			fs << "^";
			fs << v[1] << '^' << v[2].substr(0, 3) + v[2].substr(4, 3) << '^' << mod_str << '^' << v[4] << '^' << v[5][0] << '*' << v[5][2] << '^';
			fs.close();
		}
		cout << "Update success\n";
	}
	admin_prompt();
}

void error() {
	printf("syntax error \n");
}

int check_integer(char a) {
	if (a >= '0' && a <= '9') {
		return 0;
	}

	return -1;
}

char admin_check_argv(char c) {
	if (c >= 'A' && c <= 'Z') {}
	else if (c >= 'a' && c <= 'z') {
		c -= 32;
	}
	else { return '!'; }
	return c;

}

int admin_flight_is_exist(vector<string> v) {
	fls::path p("./data");
	if (!fls::exists(p))
		fls::create_directory(p);

	fls::path p2("./data/airplane");
	if (!fls::exists(p2))
		fls::create_directory(p2);
	fls::directory_iterator itr(fls::current_path() / "data" / "airplane");

	while (itr != fls::end(itr)) {
		const fls::directory_entry& entry = *itr;
		std::filesystem::path paths = "./data/airplane/" + v[1] + ".txt";
		if (exists(paths)) {
			cout << "Duplicate Insertion ERROR\n";
			return 0;
		}
		itr++;
	}
	return 1;
}

void admin_quit() {
	cout << "Good bye";
	exit(0);
}

void admin_show_user(string s)
{
	if (s.size() != 6) {
		error();
		return;
	}
	else {
		for (int i = 0; i < 3; i++) {
			if (!(s[i] >= 'A' && s[i] <= 'Z')) {
				error();
				return;
			}
			if (!(s[i + 3] >= '0' && s[i + 3] <= '9')) {
				error();
				return;
			}
		}
	}
	string dir = "./data/airplane";
	vector<string> paths;
	if (_access(dir.c_str(), 0) != -1) {
		for (auto& p : std::filesystem::directory_iterator(dir)) {
			paths.push_back(p.path().string());
		}
	}
	int is_find = -1;
	for (int l = 0; l < paths.size(); l++) {
		string temp_str = split_backslash(paths[l]).back().substr(0, 6);
		if (temp_str == s) {
			is_find = l;
			break;
		}
	}
	if (is_find == -1) {
		cout << "There is no flight " << s << endl;
	}
	else {
		string airplaneData;
		string data_in;
		ifstream ifs2(paths[is_find]);
		if (ifs2.is_open()) {
			getline(ifs2, airplaneData);
			while (!ifs2.eof()) {
				getline(ifs2, airplaneData);
				string res_user = split_user_data(airplaneData)[0];
				ifstream user_ifs("./data/Userlist.txt");
				while (!user_ifs.eof()) {
					getline(user_ifs, data_in);
					if (res_user == split_user_data(data_in)[0]) {
						vector<string> userInfo = split_user_data(data_in);
						if (userInfo[2] == "1") {
							userInfo[2] = "M";
						}
						else if (userInfo[2] == "0") {
							userInfo[2] = "W";
						}
						userInfo[3] = "010" + userInfo[3];
						for (int i = 0; i < 5; i++) {					
							cout << userInfo[i] << ' ';
						}
						cout << endl;
						break;
					}
				}
				user_ifs.close();
			}
			ifs2.close();
		}
	}
	admin_prompt();
	return;
}

void admin_show_guide()
{
	cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
	cout << ("|         command set       |                argument                  |                          description                       \n");
	cout << ("|                           |                                          |                                                            \n");
	cout << ("|         help, he,h        |           none or 1 command              |            print all commands or detail of argument        \n");
	cout << ("|                           |                                          |                                                            \n");
	cout << ("|         quit, qu,q        |                  none                    |                          quit program                      \n");
	cout << ("|                           |                                          |                                                            \n");
	cout << ("|         test, te, t       |                  none                    |                        integrity check                     \n");
	cout << ("|                           |                                          |                                                            \n");
	cout << ("|         list, li, l       |           none or flight name            |                print flight imformation list or            \n");
	cout << ("|                           |                                          |                   specific flight information              \n");
	cout << ("|                           |                                          |                                                            \n");
	cout << ("|                           |          flight name, departure,         |                                                            \n");
	cout << ("|         add, ad, a        |       destination, departure time,       |                            add flght                       \n");
	cout << ("|                           |  arrival time, price, number of seats    |                                                            \n");
	cout << ("|                           |                                          |                                                            \n");
	cout << ("|      cancel, canc, c      |               flight name                |                          delete flight                     \n");
	cout << ("|                           |                                          |                                                            \n");
	cout << ("|                           |          flight name, departure,         |                                                            \n");
	cout << ("|        edit, ed, e        |       destination, departure time,       |                        add user's amount                   \n");
	cout << ("|                           |  arrival time, price, number of seats    |                                                            \n");
	cout << ("|                           |                                          |                                                            \n");
	cout << ("|                           |                                          |                                                            \n");
	cout << ("|        user, usr, u       |               flight name                |                  print user list of the flight             \n");
	cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
}

void h_help()
{
	system("cls");
	cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
	cout << ("|         help, he,h        |           none or 1 command              |            print all commands or detail of argument        \n");
	cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
}

void h_quit()
{
	system("cls");
	cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
	cout << ("|         quit, qu,q        |                  none                    |                          quit program                      \n");
	cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
}

void h_test()
{
	cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
	cout << ("|         test, te, t       |                  none                    |                        integrity check                     \n");
	cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
}

void h_list()
{
	cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
	cout << ("|         list, li, l       |           none or flight name            |                print flight imformation list or            \n");
	cout << ("|                           |                                          |                   specific flight information              \n");
	cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
}

void h_add()
{
	cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
	cout << ("|                           |          flight name, departure,         |                                                            \n");
	cout << ("|         add, ad, a        |       destination, departure time,       |                            add flght                       \n");
	cout << ("|                           |  arrival time, price, number of seats    |                                                            \n");
	cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
}

void h_cancel()
{
	system("cls");
	cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
	cout << ("|      cancel, canc, c      |               flight name                |                          delete flight                     \n");
	cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
}

void h_edit()
{
	cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
	cout << ("|                           |          flight name, departure,         |                                                            \n");
	cout << ("|        edit, ed, e        |       destination, departure time,       |                        add user's amount                   \n");
	cout << ("|                           |  arrival time, price, number of seats    |                                                            \n");
	cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
}

void h_user()
{
	system("cls");
	cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
	cout << ("|        user, usr, u       |               flight name                |                  print user list of the flight             \n");
	cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
}

int admin_check_edit(vector<string> v)
{
	if (v.size() < 6) {
		error(); h_edit(); return 0;
	}
	string planename = v[1];
	string departture_destination = v[2];
	string time = v[3];
	string price = v[4];
	string seats = v[5];


	for (int i = 0; i < 3; i++) {
		if (planename[i] = admin_check_argv(planename[i] != '!')) {}
		else {
			error();
			h_edit();
			return 0;
		}

	}

	for (int i = 3; i < 6; i++) {
		if (planename[i] < '0' && planename[i] > '9')
		{
			error();
			h_edit();
			return 0;
		}
	}

	v[1] = planename;

	for (int j = 0; j < 3; j++) {
		if (admin_check_argv(departture_destination[j]) != '!') {
			departture_destination[j] = admin_check_argv(departture_destination[j]);
		}
		else {
			error();
			h_edit();
			return 0;
		}
	}
	if (departture_destination[3] == '/' || departture_destination[3] == ',' || departture_destination[3] == '-') {
	}
	else {
		error();
		h_edit();
		return 0;
	}
	for (int j = 4; j < 7; j++) {
		if (admin_check_argv(departture_destination[j]) != '!') {
			departture_destination[j - 1] = admin_check_argv(departture_destination[j]);
		}
		else {
			error();
			h_edit();
			return 0;
		}
	}
	v[2] = departture_destination;
	if (time.length() == 21) {
		for (int i = 0; i < 10; i++) {
			if (check_integer(time[i]) != 0) {
				error();
				h_edit();
				return 0;
			}
		}
		if (time[10] != '-' && time[10] != ',' && time[10] != '~') {
			error();
			h_edit();
			return 0;
		}
		for (int i = 11; i < 21; i++) {
			if (check_integer(time[i]) != 0) {
				error(); h_edit(); return 0;
			}
		}
	}
	else if (time.length() == 23 && (time[10] == '-' || time[10] == ',' || time[10] == '~')) {
		for (int i = 0; i < 10; i++) {
			if (check_integer(time[i]) != 0) { error(); h_edit(); return 0; }
		}
		if (time[10] != '-' && time[10] != ',' && time[10] != '~') { error(); h_edit(); return 0; }
		for (int i = 11; i < 23; i++) {
			if (check_integer(time[i]) != 0) { error(); h_edit(); return 0; }
		}

	}
	else if (time.length() == 23 && (time[12] == '-' || time[12] == ',' || time[12] == '~')) {
		for (int i = 0; i < 10; i++) {
			if (check_integer(time[i]) != 0) { error(); h_edit(); return 0; }
		}
		if (time[12] != '-' && time[12] != ',' && time[12] != '~') { error(); h_edit(); return 0; }
		for (int i = 13; i < 23; i++) {
			if (check_integer(time[i]) != 0) { error(); h_edit(); return 0; }
		}

	}
	else if (time.length() == 25) {
		for (int i = 0; i < 12; i++) {
			if (check_integer(time[i]) != 0) {
				error(); h_edit(); return 0;
			}
		}
		if (time[12] != '-' && time[12] != ',' && time[12] != '~') {
			error(); h_edit(); return 0;
		}
		for (int i = 13; i < 25; i++) {
			if (check_integer(time[i]) != 0) {
				error(); h_edit(); return 0;
			}
		}

	}
	else {
		error(); return 0;
	}
}

void admin_help(vector<string> v)
{
	if (v.size() == 1) {			 // help¸¸ ÀÔ·Â
		system("cls");
		admin_show_guide();
		return;
	}

	else if (v.size() == 2) {		// help¿Í ÀÎÀÚ ÀÔ·Â
		string h_command = v[1];
		if (h_command == "help" or h_command == "hel" or h_command == "he" or h_command == "h") {
			h_help();
		}
		else if (h_command == "quit" or h_command == "qu" or h_command == "q") {
			h_quit();
		}
		else if (h_command == "test" or h_command == "te" or h_command == "t") {
			system("cls");
			h_test();
		}
		else if (h_command == "list" or h_command == "li" or h_command == "l") {
			system("cls");
			h_list();

		}
		else if (h_command == "add" or h_command == "ad" or h_command == "a") {
			system("cls");
			h_add();
		}
		else if (h_command == "cancel" or h_command == "canc" or h_command == "c") {
			h_cancel();

		}
		else if (h_command == "edit" or h_command == "ed" or h_command == "e") {
			system("cls");
			h_edit();
		}
		else if (h_command == "user" or h_command == "usr" or h_command == "u") {
			h_user();
		}
		else {
			system("cls");
			cout << "There is no command \"" << h_command << "\"\n.";
			admin_show_guide();
			return;
		}
	}
	else {
		system("cls");
		cout << "There are 2 or more arguments.\n";
		admin_show_guide();
		return;
	}
}
