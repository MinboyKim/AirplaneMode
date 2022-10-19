#include "admin.h"
#include "integrity_check.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include "string_function.h"

using namespace std;


void admin_prompt() {
	system("cls");
	printf("Admin> ");
	if (choice() == 1) {
		show_airplane();
		check();
		//admin_add();
	}
	else {
		
	}
}

int choice() {
	int choice;
	scanf_s("%d", &choice);
	return 1;
}

void check() {
	string s;
	getline(cin, s);
	vector<string> v = split_space(s);
	if (v.front() == "add") admin_add(v);
	else if (v.front() == "cancel") admin_cancel(v[1]);
	return;

}

void admin_add(vector<string> v){
	string line;
	string fname = v[1] + ".txt";

	ofstream listfile("Aplist.txt", std::ios_base::out | std::ios_base::app);
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
	//fs.open("APlist.txt");

	if (fs1.is_open())
	{
		while (getline(fs1,line)) {
			cout << line << endl;
		}
		fs1.close();
	}
	show_airplane();
}

void show_airplane() {
	//system("cls");
	cout << "항공편 목록"<<endl;
	cout << "Admin> ";
	if (choice() == 1) {
		check();
	}
}

void admin_cancel(string s){
	string line;
	int offset;
	
	std::vector<std::string>?get_files_inDirectory(const?std::string & _path, const?std::string & _filter) {
		std::string?searching? = _path? + _filter;?????std::vector<std::string>?return_;?????_finddata_t?fd;????long?handle? = _findfirst(searching.c_str(), &fd);?
	show_airplane();

}
void admin_edit(){

}