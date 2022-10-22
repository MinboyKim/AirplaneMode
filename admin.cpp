#include "admin.h"
#include "integrity_check.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include "string_function.h"
#include <filesystem>

using namespace std;
namespace fls = std::filesystem;


void admin_prompt() {
	system("cls");
	printf("Admin> ");
	string s;
	cin.clear();
	getline(cin, s);
	cin.clear();
	vector<string> v(1000);
	v = split_space(s);
	admin_check(v);
	
}

void show_airplane() {
	//system("cls");
	cout << "항공편 목록" << endl;
	cout << "Admin> ";
	string s;
	cin.clear();
	getline(cin, s);
	vector<string> v;
	v= split_space(s);
	admin_check(v);
}

int choice() {
	int choice;
	scanf_s("%d", &choice);
	return choice;
}

void admin_check(vector<string> v) {
	if (v.size() > 2) {
		string cmd = v[0];
		if (cmd == "add" || cmd == "d" || cmd == "ad") check_add(v);
		else if (cmd == "cancel" || cmd == "cance" || cmd == "canc" || cmd == "can" || cmd == "ca" || cmd == "c") admin_cancel(v[1]);
		else if (cmd == "edit" || cmd == "edi" || cmd == "ed" || cmd == "e") admin_edit(v);
	}
	return;

}

void check_add(vector<string> v) {
	/*for (auto i : v) {
		cout << i << " ";
	}*/
	if (v.size() <= 5) {
		error(); return;
	}
	string planename = v[1];
	string departture_destination = v[2];
	string time = v[3];
	string price = v[4];
	string seats = v[5];

	for (int i = 0; i < 3; i++) {
		if (planename[i] >= 'A' && planename[i] <= 'Z') {}
		else if (planename[i] >= 'a' && planename[i] <= 'z')
			planename[i] -= 32;
		else { error(); return; }
	}
	for (int i = 3; i < 6; i++) {
		if (planename[i] < '0' && planename[i] > '9')
		{
			error(); return;
		}
	}
	for (int j = 0; j < 3; j++) {
		if (departture_destination[j] = admin_check_argv(departture_destination[j]) != '!') {
		}
		else { error(); return; }
	}
	if (departture_destination[3] == '/' || departture_destination[3] == ',' || departture_destination[3] == '-') {
	}
	else { error(); return; }
	for (int j = 4; j < 6; j++) {
		if (departture_destination[j] = admin_check_argv(departture_destination[j]) != '!') {
		}
		else { error(); return; }
	}
	if (time.length() == 21) {
		for (int i = 0; i < 10; i++) {
			if (check_integer(time[i]) != 0) { error(); return; }
		}
		if (time[10] != '-' && time[10] != ',' && time[10] != '~') { error(); return; }
		for (int i = 11; i < 21; i++) {
			if (check_integer(time[i]) != 0) { error(); return; }
		}
	}
	else if (time.length() == 23 && (time[10] == '-' || time[10] == ',' || time[10] == '~')) {
		for (int i = 0; i < 10; i++) {
			if (check_integer(time[i]) != 0) { error(); return; }
		}
		if (time[10] != '-' && time[10] != ',' && time[10] != '~') { error(); return; }
		for (int i = 11; i < 23; i++) {
			if (check_integer(time[i]) != 0) { error(); return; }
		}

	}
	else if (time.length() == 23 && (time[12] == '-' || time[12] == ',' || time[12] == '~')) {
		for (int i = 0; i < 10; i++) {
			if (check_integer(time[i]) != 0) { error(); return; }
		}
		if (time[12] != '-' && time[12] != ',' && time[12] != '~') { error(); return; }
		for (int i = 13; i < 23; i++) {
			if (check_integer(time[i]) != 0) { error(); return; }
		}

	}
	else if (time.length() == 25) {
		for (int i = 0; i < 12; i++) {
			if (check_integer(time[i]) != 0) {
				error(); return;
			}
		}
		if (time[12] != '-' && time[12] != ',' && time[12] != '~') {
			error(); return;
		}
		for (int i = 13; i < 25; i++) {
			if (check_integer(time[i]) != 0) {
				error(); return;
			}
		}

	}
	else {error(); return;
}

	string newprice="";
	for (char& c : price) {
		if (c == ',') {
		}
		else if (check_integer(c) == 0) {
			newprice += c;
		}
		else  {error(); return;
	}
	}
	v[4] = newprice;
	if (check_integer(seats[0]) == -1 || (seats[1] != ',' && seats[1] != '*' && seats[1] != '-') || check_integer(seats[2]) == -1) { error(); return; }
	admin_add(v);
	return;
}
void admin_add(vector<string> v){
	string line;
	string fname = "./data/airplane/"+v[1] + ".txt";
	
	fls::path p("./data");
	if (!fls::exists(p))
		fls::create_directory(p);

	fls::path p2("./data/airplane");
	if (!fls::exists(p2))
		fls::create_directory(p2);


	ofstream listfile("data\\airplane\\Aplist.txt", std::ios_base::out | std::ios_base::app);
	if (listfile.is_open()) {
		listfile << v[1]<<"^";
		listfile.close();
	}


	ofstream fs(fname, std::ios_base::out | std::ios_base::app);
	if (fs.is_open()) {
		for (vector<string>::iterator iter = v.begin()+1; iter != v.end(); iter++) {
			fs << *iter<<" ";
		}
		fs << endl;
		fs.close();
	}
	
	ifstream fs1(fname);
	if (fs1.is_open())
	{
		while (getline(fs1,line)) {
			cout << line << endl;
		}
		fs1.close();
	}

	/*fls::directory_iterator itr(fls::current_path() / "data"/"airplane");
	while (itr != fls::end(itr)) {
		const fls::directory_entry& entry = *itr;
		std::cout << entry.path() << std::endl;
		itr++;
	}
	show_airplane();*/
}


void admin_cancel(string s){
	string line;
	int offset;
	
	
	show_airplane();

}
void admin_edit(vector<string> v){

}

void error() {
	printf("syntax error \n");
	show_airplane();
}

int check_integer(char a) {
	if (a >= '0' && a <= '9') {
		return 0;
	}

	return -1;
}

char admin_check_argv(char c) {
	if (c>= 'A' && c<='Z') {}
	else if (c >= 'a' && c <= 'z')
		c -= 32;
	else {  return '!'; }

	return c;

}