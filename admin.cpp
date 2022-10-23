#include "admin.h"
#include "integrity_check.h"
#include <iostream>
#include <windows.h>
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

void admin_show_airplane() {
	cout << "------------AirPlane LIst---------\n";
	string line;
	fls::directory_iterator itr(fls::current_path() /"data"/"airplane");
	while (itr != fls::end(itr)) {
		const fls::directory_entry& entry = *itr;
		ifstream fs3(entry.path());
		if (fs3.is_open())
		{
			while (getline(fs3, line)) {
				cout << line << endl;
			}
			fs3.close();
		}
		itr++;
	}
	admin_prompt();
}

int choice() {
	int choice;
	scanf_s("%d", &choice);
	return choice;
}

void admin_check(vector<string> v) {
	
		string cmd = v[0];
		if (cmd == "add" || cmd == "ad" || cmd == "a") admin_check_add(v);
		else if (cmd == "cancel" || cmd == "cance" || cmd == "canc" || cmd == "can" || cmd == "ca" || cmd == "c") admin_cancel(v[1]);
		else if (cmd == "edit" || cmd == "edi" || cmd == "ed" || cmd == "e") admin_edit(v);
		else if (cmd == "list" || cmd == "lis" || cmd == "li" || cmd == "l") admin_show_airplane();
		else if (cmd == "quit" || cmd == "qui" || cmd == "qu" || cmd == "q") admin_quit();
		else if (cmd == "help" || cmd == "hel" || cmd == "he" || cmd == "h") admin_help(v);
		else if (cmd == "user" || cmd == "use" || cmd == "us" || cmd == "u") admin_show_user(v[1]);
		else error();

		admin_prompt();
	return;

}

int admin_check_add(vector<string> v) {
	/*for (auto i : v) {
		cout << i << " ";
	}*/
	if (v.size() <= 5) {
		error(); return 0;
	}
	string planename = v[1];
	string departture_destination = v[2];
	string time = v[3];
	string price = v[4];
	string seats = v[5];

	for (int i = 0; i < 3; i++) {
		planename[i]=admin_check_argv(planename[i]);
	}
	v[1] = planename;
	
	for (int i = 3; i < 6; i++) {
		if (planename[i] < '0' && planename[i] > '9')
		{
			error(); return 0;
		}
	}
	for (int j = 0; j < 3; j++) {
		if (departture_destination[j] = admin_check_argv(departture_destination[j]) != '!') {
		}
		else { error(); return 0;
		}
	}
	if (departture_destination[3] == '/' || departture_destination[3] == ',' || departture_destination[3] == '-') {
	}
	else { error(); return 0;
	}
	for (int j = 4; j < 6; j++) {
		if (departture_destination[j] = admin_check_argv(departture_destination[j]) != '!') {
		}
		else { error(); return 0;
		}
	}
	v[2] = departture_destination;
	if (time.length() == 21) {
		for (int i = 0; i < 10; i++) {
			if (check_integer(time[i]) != 0) { error(); return 0;
			}
		}
		if (time[10] != '-' && time[10] != ',' && time[10] != '~') { error(); return 0;
		}
		for (int i = 11; i < 21; i++) {
			if (check_integer(time[i]) != 0) { error(); return 0;
			}
		}
	}
	else if (time.length() == 23 && (time[10] == '-' || time[10] == ',' || time[10] == '~')) {
		for (int i = 0; i < 10; i++) {
			if (check_integer(time[i]) != 0) { error(); return 0; }
		}
		if (time[10] != '-' && time[10] != ',' && time[10] != '~') { error(); return 0; }
		for (int i = 11; i < 23; i++) {
			if (check_integer(time[i]) != 0) { error(); return 0; }
		}

	}
	else if (time.length() == 23 && (time[12] == '-' || time[12] == ',' || time[12] == '~')) {
		for (int i = 0; i < 10; i++) {
			if (check_integer(time[i]) != 0) { error(); return 0; }
		}
		if (time[12] != '-' && time[12] != ',' && time[12] != '~') { error(); return 0; }
		for (int i = 13; i < 23; i++) {
			if (check_integer(time[i]) != 0) { error(); return 0; }
		}

	}
	else if (time.length() == 25) {
		for (int i = 0; i < 12; i++) {
			if (check_integer(time[i]) != 0) {
				error(); return 0;
			}
		}
		if (time[12] != '-' && time[12] != ',' && time[12] != '~') {
			error(); return 0;
		}
		for (int i = 13; i < 25; i++) {
			if (check_integer(time[i]) != 0) {
				error(); return 0;
			}
		}

	}
	else {error(); return 0;
}

	string newprice="";
	for (char& c : price) {
		if (c == ',') {
		}
		else if (check_integer(c) == 0) {
			newprice += c;
		}
		else  {error(); return 0;}
	}
	v[4] = newprice;
	if (check_integer(seats[0]) == -1 || (seats[1] != ',' && seats[1] != '*' && seats[1] != '-') || check_integer(seats[2]) == -1) { error(); return 0; }
	return admin_add(v);
	
}

int admin_add(vector<string> v){
	string line;
	string fname = "./data/airplane/"+v[1] + ".txt";
	
	fls::path p("./data");
	if (!fls::exists(p))
		fls::create_directory(p);

	fls::path p2("./data/airplane");
	if (!fls::exists(p2))
		fls::create_directory(p2);


	ofstream fs(fname, std::ios_base::out | std::ios_base::app);
	if (fs.is_open()) {
		for (vector<string>::iterator iter = v.begin()+1; iter != v.end(); iter++) {
			fs << *iter<<" ";
		}
		fs << endl;
		fs.close();
	}
	

	
	return 1;
}


void admin_cancel(string s){
	string line;
	string plane_path ="./data/airplane/"+s+".txt";\
	const char* path = plane_path.c_str();
	int r=remove(path);
	admin_prompt();
}

void admin_edit(vector<string> v){
	string line;
	//system("cls");
	fls::directory_iterator itr(fls::current_path() / "data" / "airplane");
	while (itr != fls::end(itr)) {
		const fls::directory_entry& entry = *itr;
		std::filesystem::path paths = "./data/airplane/" + v[1] + ".txt";
		if (exists(paths)) {
			if (admin_check_add(v) == 1) {
				remove(paths);
				admin_check_add(v);
			}
			admin_prompt();
		}
		else { 
			cout<< "There is no flight \""<< v[1] <<"\""<< endl;
			admin_prompt();
		}

		
			
		itr++;
	}
}

void error() {
	printf("syntax error \n");
	admin_prompt();
}

int check_integer(char a) {
	if (a >= '0' && a <= '9') {
		return 0;
	}

	return -1;
}

char admin_check_argv(char c) {
	if (c>= 'A' && c<='Z') {}
	else if (c >= 'a' && c <= 'z') {
		c -= 32;
	}
	else {  return '!'; }

	return c;

}

void admin_quit() {
	exit(0);
}

void admin_show_user(string s)
{
	
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

void admin_help(vector<string> v)
{
	if (v.size() == 1) {			 // help만 입력
		system("cls");
		admin_show_guide();
		return;
	}

	else if (v.size() == 2) {		// help와 인자 입력
		string h_command = v[1];
		if (h_command == "help" or h_command == "hel" or h_command == "he" or h_command == "h") {
			system("cls");
			cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
			cout << ("|         help, he,h        |           none or 1 command              |            print all commands or detail of argument        \n");
			cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
		}
		else if (h_command == "quit" or h_command == "qu" or h_command == "q") {
			system("cls");
			cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
			cout << ("|         quit, qu,q        |                  none                    |                          quit program                      \n");
			cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
		}
		else if (h_command == "test" or h_command == "te" or h_command == "t") {
			system("cls");
			cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
			cout << ("|         test, te, t       |                  none                    |                        integrity check                     \n");
			cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
		}
		else if (h_command == "list" or h_command == "li" or h_command == "l") {
			system("cls");
			cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
			cout << ("|         list, li, l       |           none or flight name            |                print flight imformation list or            \n");
			cout << ("|                           |                                          |                   specific flight information              \n");
			cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");

		}
		else if (h_command == "add" or h_command == "ad" or h_command == "a") {
			system("cls");
			cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
			cout << ("|                           |          flight name, departure,         |                                                            \n");
			cout << ("|         add, ad, a        |       destination, departure time,       |                            add flght                       \n");
			cout << ("|                           |  arrival time, price, number of seats    |                                                            \n");
			cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");

		}
		else if (h_command == "cancel" or h_command == "canc" or h_command == "c") {
			system("cls");
			cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
			cout << ("|      cancel, canc, c      |               flight name                |                          delete flight                     \n");
			cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");

		}
		else if (h_command == "edit" or h_command == "ed" or h_command == "e") {
			system("cls");
			cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
			cout << ("|                           |          flight name, departure,         |                                                            \n");
			cout << ("|        edit, ed, e        |       destination, departure time,       |                        add user's amount                   \n");
			cout << ("|                           |  arrival time, price, number of seats    |                                                            \n");
			cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
		}
		else if (h_command == "user" or h_command == "usr" or h_command == "u") {
			system("cls");
			cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
			cout << ("|        user, usr, u       |               flight name                |                  print user list of the flight             \n");
			cout << ("------------------------------------------------------------------------------------------------------------------------------------\n");
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

