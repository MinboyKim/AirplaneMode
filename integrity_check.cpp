#include "integrity_check.h"
#include <iostream>
#include <io.h>
#include <fstream>
#include <vector>
#include <filesystem>
#include "string_function.h"
#include "user.h"
#include <stdio.h>


using namespace std;
namespace fs = std::filesystem;


void integrity_check() {
	cout << "Start integrity check" << endl;
	path_check();
	userList_check();
	available_check();
	rule_check();
}

void path_check()
{
	const char* path_data = ".\\data";
	int result_data = _access(path_data, 0);

	if (result_data != 0) {
		cout << "ERROR! Not found server path!" << endl;
		return;
	}
}


void userList_check() {
	const char* path_userList = ".\\data\\Userlist.txt";
	int result_userList = _access(path_userList, 0);

	if (result_userList != 0) {
		cout << "Alert! Necessary file missing." << endl;
		ofstream userList(".\\data\\Userlist.txt");
		if (result_userList == 0) {
			cout << "File create successfully" << endl;
		}
		else {
			cout << "ERROR! failed to make file." << endl;
			return;
		}
	}
}

void available_check()
{
	//Userlist is already checked so don't need to check it again
	//only check airplane
	string path_airplane = ".\\data\\airplane";
	vector<string> files = get_files_indirectory(path_airplane, "*"); //for all files in folder
	for(int i=2; i<files.size(); i++) { // file starts from '2'
		string fn = files[i];
		if (fn.substr(fn.find_last_of(".") + 1) != "txt") { 
			cout << "ERROR! Files that cannot be used in File I/O exist" << endl;
			return;
		}
	}
	
}

void rule_check()
{
	string userData;
	string airplaneData;
	string airplaneName;
	const char* path_airplane = ".\\data\\airplane";
	ifstream ifs1;
	ifs1.open(".\\data\\Userlist.txt");
	if (ifs1.is_open()) {
		while (!ifs1.eof()) {
			int i = 1;
			getline(ifs1, userData);
			if (user_integrity_check(userData)==0) {
				printf("ERROR! Incorrect data exist! ( file name : Userlist.txt , In row %d)\n", i);
			}
			i++;
		}
	}
	ifs1.close();
	
	
	if (!(_access(path_airplane, 0))) {
		fs::directory_iterator itr(fs::current_path() / "data" / "airplane");
		while (itr != fs::end(itr)) {
			const fs::directory_entry& entry = *itr;
			ifstream ifs2(entry.path());
			if (ifs2.is_open()) {
				getline(ifs2, airplaneName);
				while (!ifs2.eof()) {
					int i = 1;
					getline(ifs2, airplaneData);
					if (i == 1) {
						if (airplaneData == "") { //데이터 없음
							break;
						}
					}
					if (airplane_integrity_check(airplaneData) == 0) {
						printf("ERROR! Incorrect data exist! ( file name : %s , In row %d)\n", airplaneName, i);
					}
					i++;
				}
			}
			ifs2.close();
			itr++;
		}
		cout << "Integrity check completed!" << endl;
	}
	else {
		cout << "no airplane list exist" << endl;
		cout << "Integrity check completed!" << endl;
	}
}	



bool user_integrity_check(string str) {
	vector<string> integrity_data;
	if (str[0] != '^' || str.back() != '^') {
		return false;
	}
	integrity_data = split_user_data(str);
	if (integrity_data.size() != 6) {
		return false;
	}
	if (!check_ID(integrity_data[0])) {
		return false;
	}

	if (!integrity_check_name(integrity_data[1])) {
		return false;
	}

	if (integrity_data[2] != "1" && integrity_data[2] != "0") {
		return false;
	}

	if (!is_number(integrity_data[3]) || integrity_data[3].size() != 8) {
		return false;
	}
	else if (!check_TEL(integrity_data[3])) {
		return false;
	}

	if (!is_number(integrity_data[4]) || integrity_data[4].size() != 8) {
		return false;
	}
	else if (!check_birth(integrity_data[4])) {
		return false;
	}

	if (!is_number(integrity_data[5])) {
		return false;
	}
	return true;
}


bool airplane_integrity_check(string str) {
	vector<string> integrity_data;
	if (str[0] != '^' || str.back() != '^') {
		return false;
	}
	integrity_data = split_user_data(str); //airplane data split
	if (integrity_data.size() != 5) {
		return false;
	}
	else if (!(check_airplane_name(integrity_data[0]))) {
		return false;
	}
	else if (!(check_place(integrity_data[1]))) {
		return false;
	}
	else if (!(check_time(integrity_data[2]))) {
		return false;
	}
	else if (!(check_deposit(integrity_data[3]))) {
		return false;
	}
	else if (!(check_all_seat(integrity_data[4]))) {
		return false;
	}
	else if (!(check_seat(integrity_data[4], integrity_data[5]))) {
		return false;
	}
	return true;
}