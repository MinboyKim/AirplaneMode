#include<stdio.h>
#include<vector>
#include<windows.h>
#include<fstream>
#include<io.h>
#include<conio.h>
#include<stdio.h>
#include "string_function.h"

using namespace std;

void show_guide() {
	cout << ("-------------------------------------------------------------------------------------------------------------------------\n");
	cout << ("|         command set       |           argument            |                          description                       \n");
	cout << ("|                           |                               |                                                            \n");
	cout << ("|         help, he,h        |         none or 1 command     |                 print all commands or detail of            \n");
	cout << ("|                           |                               |                                                            \n");
	cout << ("|         quit, qu,q        |             none              |                          quit program                      \n");
	cout << ("|                           |                               |                                                            \n");
	cout << ("|         list, li, l       |    Not exist or 1 flight      |       print flight imformation list or seat information    \n");
	cout << ("|                           |                               |                                                            \n");
	cout << ("|     reservation,reserve,r |  flight and seat information  |                          description                       \n");
	cout << ("|                           |                               |                                                            \n");
	cout << ("|      cancel, can, c       |            flight             |                           quit flight                      \n");
	cout << ("|                           |                               |                                                            \n");
	cout << ("|      deposit, depo,d      |         deposit amount        |                        add user's amount                   \n");
	cout << ("|                           |                               |                                                            \n");
	cout << ("|    information, info, i   |             none              |                        print my information                \n");
	cout << ("-------------------------------------------------------------------------------------------------------------------------\n");

}

vector<string> user_input() {

	vector<string> v;
	v = split_space();
	return v;

}

void help(vector<string> v) {

	if (v.size() == 1) {
		system("cls");
		show_guide();
		return;
	}

	else if (v.size() == 2) {// 명령어와 인자를 입력한 경우
		if (v.at(1) == "help" or v.at(1) == "hel" or v.at(1) == "he" or v.at(1) == "h") {
			system("cls");
			cout << "description : Instruction \" help or hel or he \" shows you information about user's instruction.\n" << endl;
			cout << "              if you use it with 1 argument that composed of 1 instruction like \" quit \" you can read about more detail information \n" << endl;
			cout << "              if you use it with no argument, you can see basic information about all instructions\n" << endl;
		}
		else if (v.at(1) == "quit" or v.at(1) == "qu" or v.at(1) == "q") {
			system("cls");
			cout << "description : Instruction \"quit or qu or q \" quits program \n" << endl;
		}
		else if (v.at(1) == "list" or v.at(1) == "li" or v.at(1) == "l") {
			system("cls");
			cout << "description : Instruction \"list or li or l \" prints flight list \n" << endl;
			cout << "              if you use it with 1 flight you can see about seat information. \n" << endl;
			cout << "              if you use it with no argument, you can see all flight information in list \n" << endl;
		}
		else if (v.at(1) == "reservation" or v.at(1) == "reserve" or v.at(1) == "r") {
			system("cls");
			cout << "description : Instruction \"reservation or reserve or r \" reserve seat. you can use this instuctrion with 2 arguments flight name and seat postion. \n" << endl;
			cout << "            : ex> User> reservation KOR 222 A1" << endl;

		}
		else if (v.at(1) == "cancel" or v.at(1) == "can" or v.at(1) == "c") {
			system("cls");
			cout << "description : Instruction \"cancel or can or c \" cancel reservation with 1 argument about flight name. the name is necessary in flight information list \n" << endl;
			cout << "            : ex> User> cancel KOR111" << endl;

		}
		else if (v.at(1) == "deposit" or v.at(1) == "depo" or v.at(1) == "d") {
			system("cls");
			cout << "description : Instruction \" deposit or depo or d \" deposit user's money. You can use this instruction with 1 argument about amount. \n" << endl;
			cout << "            : ex> User> deposit 1120" << endl;

		}
		else if (v.at(1) == "information" or v.at(1) == "info" or v.at(1) == "i") {
			system("cls");
			cout << "description : Instruction \" information or info or i \" prints user's information with no argument.\n" << endl;
			cout << "            : ex> User> informaiton\n" << endl;
			cout << "            : cj2200 ChoiJungyu M 01050362323 1990622\n" << endl;
		}
		else {
			system("cls");
			show_guide();
			return;
		}
	}
}

void user_prompt(string s) {

	int quit_num = 0;
	vector<string> v;

	while (1) {
		cout << "User>";

		v = user_input();

		if (v.at(0) == "help" or v.at(0) == "he" or v.at(0) == "h") {
			help(v);
			continue;
		}
		if (v.at(0) == "quit" or v.at(0) == "qu" or v.at(0) == "q") {
			system("cls");
			break;
		}
		if (v.at(0) == "list" or v.at(0) == "li" or v.at(0) == "l") {
			continue;
		}
		if (v.at(0) == "reservation" or v.at(0) == "reserve" or v.at(0) == "r") {
			system("cls");
			continue;
		}
	}

}

vector<string> get_files_indirectory(const string& _path, const string& _filter) {

	string searching = _path + _filter;

	vector<string> return_;

	_finddata_t fd;

	intptr_t handle = _findfirst(searching.c_str(), &fd);
	if (handle == -1) return return_;

	int result = 0;
	do {
		return_.push_back(fd.name);
		result = _findnext(handle, &fd);
	} while (result != -1);

	_findclose(handle);
	return return_;

}


void list(vector<string> v) {
	//리스트 출력
	vector<string> fname;
	vector<string> flight;//항공편 정보를 담는 벡터
	string str;

	int k = 0;
	ifstream readFile;
	_finddata_t fd;
	long handle;
	int result = 1;
	handle = _findfirst(".", &fd);  //현재 폴더 내 모든 파일을 찾는다.
	if (v.size() == 1) {//인자가 없는 경우
		if (handle == -1)
		{
			cout << ("NO flights \n");
			return;
		}

		while (result != -1)
		{
			fname.push_back(fd.name);
			result = _findnext(handle, &fd);
			k++;
		}
		_findclose(handle);

		for (int i = 0; i < k + 1; i++) {

			readFile.open("." + fname[i]);
			if (readFile.is_open()) {
				while (!readFile.eof()) {
					getline(readFile, str);
					flight = split_user_data(str); // 항공편명^ 출발지 도착지 ^출발시각 도착시각 ^좌석 사이즈 ^ 금액 ^ 유저아이디^ 좌석........//7번 벡터부터 유저정보.
				}

			}
			readFile.close();

			for (int h = 0; h < 5; h++) {
				if (h == 0) {
					cout << flight[0];//항공편명
				}
				if (h == 1) {//항공편 출발지 도착지
					for (int j = 0; j < 3; j++) {
						cout << flight[1][j];
					}
					cout << (" /");
					for (int j = 3; j < 6; j++) {
						cout << flight[1][j];
					}
					cout << ("  ");
				}
				else if (h == 2) { //출발 시간 도착 시간

					for (int j = 0; j < 12; j++) {
						cout << v[2][j];
					}
					cout << (" ~");
					for (int j = 12; j < 24; j++) {
						cout << v[2][j];
					}
					cout << (" ");
				}

				else if (h == 3) {
					cout << flight[3];//금액
				}
				else if (i == 4) {


				}
			}
		}
	}

	else if (v.size() == 2) {//인자가 있는 경우. 좌석을 출력.

		//if v.at(1) 이 입력 형식에 맞으면.

		string check_string;
		check_string = v.at(1);

		if (check_string.size() > 6) { //입력된 인자가 6글자 이상이므로 리턴
			return;
		}
		for (int i = 0; i < 3; i++) {
			if (check_string[i] < 'A' or check_string[i]>'Z') { //대문자로 이루어진 경우가 아닌 경우 리턴
				return;

			}
			if (check_string[i + 3] < '0' or check_string[i + 3]>'9') { // 숫자로 이루어진 경우가 아닌 경우 리턴
				return;
			}
		}

		readFile.open("." + v.at(1) + "txt");
		if (readFile.is_open()) {

			while (!readFile.eof()) {
				getline(readFile, str);
				flight = split_user_data(str);

				int fvs = flight.size();

			}
		}

	}
}


int main(void) {

	user_prompt("wewewe");

}