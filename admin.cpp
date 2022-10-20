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
	string s;
	cin.ignore();
	getline(cin, s);
	vector<string> v(1000);
	v = split_space(s);
	check(v);
	
}

void show_airplane() {
	//system("cls");
	cout << "항공편 목록" << endl;
	cout << "Admin> ";
	string s;
	cin.ignore();
	getline(cin, s);
	vector<string> v(1000);
	v= split_space(s);
	check(v);
}

int choice() {
	int choice;
	scanf_s("%d", &choice);
	return choice;
}

void check(vector<string> v) {
	if (v.size() > 6) {
		string cmd = v[0];
		if (cmd == "add" || cmd == "d" || cmd == "ad") check_add(v);
		else if (cmd == "cancel" || cmd == "cance" || cmd == "canc" || cmd == "can" || cmd == "ca" || cmd == "c") admin_cancel(v[1]);
		else if (cmd == "edit" || cmd == "edi" || cmd == "ed" || cmd == "e") admin_edit(v);
	}
	return;

}

void check_add(vector<string> v) {
	string planename = v[1];
	string departture_destination = v[2];
	string time = v[3];
	string price = v[4];
	string seats = v[5]; 

	for (int i = 0; i < 3; i++) {
		if (planename[i] >= 'A' && planename[i] <= 'Z')
			if (planename[i] >= 'a' && planename[i] <= 'z')
				planename[i] -= 32;
			else { error(); return; }
		else { error(); return; }
	}
	for (int i = 3; i < 6; i++) {
		if (planename[i] < '0' && planename[i] > '9') 
			 { error(); return; }
	}
	for (int j = 0; j < 3; j++) {
		if (departture_destination[j] >= 'A' && departture_destination[j] <= 'z') {
		}
		else{ error(); return; }
	}
	if (departture_destination[3] == '/' && departture_destination[3] == ',' && departture_destination[3] == '-') {
	}
	else{ error(); return; }
	for (int j = 3; j < 6; j++) {
		if (departture_destination[j] >= 'A' && departture_destination[j] <= 'z') {
		}
		else { error(); return; }
	}
	if(time.length()==21) {
		for (int i = 0; i < 2; i++) {
			time[0]==
		}
	}
	else if (time.length() == 23) {


	}
	else if (time.length() == 25) {

	}
	else
	
	admin_add(v);
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

