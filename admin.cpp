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
		if (cmd == "add" || cmd == "d" || cmd == "ad") admin_check_add(v);
		else if (cmd == "cancel" || cmd == "cance" || cmd == "canc" || cmd == "can" || cmd == "ca" || cmd == "c") admin_cancel(v[1]);
		else if (cmd == "edit" || cmd == "edi" || cmd == "ed" || cmd == "e") admin_edit(v);
		else if (cmd == "list" || cmd == "li" || cmd == "l") admin_show_airplane();
		else if (cmd == "quit" || cmd == "qu" || cmd == "q") admin_quit();
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
	return;
}