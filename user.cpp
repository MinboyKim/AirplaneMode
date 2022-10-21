/*
구현할 명령어 목록
help
quit
list
reservation
cancel
deposit
information
*/
#include "user.h"
#include <windows.h>
#include <vector>
#include<iostream>
#include "string_function.h"
#include<fstream>
#include<io.h>
#include<conio.h>
#include<stdio.h>
qweqweqweqwewqeqwqweqweqwe
qweqweqwewqeqwe
wqeqwe
using namespace std;
void help(vector<string> v) {

	if (v.size() == 1) {
		show_guide();
		return;
	}

	else if (v.size() == 2) {// 명령어와 인자를 입력한 경우
		if (v[1] == "help" or v[1] == "hel" or v[1] == "he" or v[1] == "h") {
			printf("description : Instruction \" help or hel or he \" shows you information about user's instruction.\n");
			printf("              if you use it with 1 argument that composed of 1 instruction like \" quit \" you can read about more detail information \n");
			printf("              if you use it with no argument, you can see basic information about all instructions\n");
		}
		else if (v[1] == "quit" or v[1] == "qu" or v[1] == "q") {
			printf("description : Instruction \"quit or qu or q \" quits program \n");
		}
		else if (v[1] == "list" or v[1] == "li" or v[1] == "l") {
			printf("description : Instruction \"list or li or l \" prints flight list \n");
			printf("              if you use it with 1 flight you can see about seat information. \n");
			printf("              if you use it with no argument, you can see all flight information in list \n");
		}
		else if (v[1] == "reservation" or v[1] == "reserve" or v[1] == "r") {
			printf("description : Instruction \"reservation or reserve or r \" reserve seat. you can use this instuctrion with 2 arguments flight name and seat postion. \n");
			printf("            : ex> User> reservation KOR 222 A1");

		}
		else if (v[1] == "cancel" or v[1] == "can" or v[1] == "c") {
			printf("description : Instruction \"cancel or can or c \" cancel reservation with 1 argument about flight name. the name is necessary in flight information list \n");
			printf("            : ex> User> cancel KOR111");

		}
		else if (v[1] == "deposit" or v[1] == "depo" or v[1] == "d") {
			printf("description : Instruction \" deposit or depo or d \" deposit user's money. You can use this instruction with 1 argument about amount. \n");
			printf("            : ex> User> deposit 1120");

		}
		else if (v[1] == "information" or v[1] == "info" or v[1] == "i") {
			printf("description : Instruction \" information or info or i \" prints user's information with no argument.\n");
			printf("            : ex> User> informaiton\n");
			printf("            : cj2200 ChoiJungyu M 01050362323 1990622\n");
		}
		else {
			show_guide();
			return;
		}
	}
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
			printf("NO flights \n");
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
					printf("%s", flight[0]);//항공편명
				}
				if (h == 1) {//항공편 출발지 도착지
					for (int j = 0; j < 3; j++) {
						printf("%c", flight[1][j]);
					}
					printf(" /");
					for (int j = 3; j < 6; j++) {
						printf("%c", flight[1][j]);
					}
					printf("  ");
				}
				else if (h == 2) { //출발 시간 도착 시간

					for (int j = 0; j < 12; j++) {
						printf("%c", v[2][j]);
					}
					printf(" ~");
					for (int j = 12; j < 24; j++) {
						printf("%c", v[2][j]);
					}
					printf(" ");
				}

				else if (h == 3) {
					printf("%s", flight[3]);//금액
				}
				else if (i == 4) {


				}
			}
		}
	}

	else if (v.size() == 2) {//인자가 있는 경우. 좌석을 출력.
		
		//if v[1] 이 입력 형식에 맞으면.

		string check_string;
		check_string = v[1];

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

		readFile.open("." + v[1]+"txt");
		if (readFile.is_open()) {
			
			while (!readFile.eof()) {
				getline(readFile, str);
				flight = split_user_data(str);

				int fvs = flight.size();

			}
		}

	}
}
void reservation() {

}
void cancel() {

}
void deposit() {

}
void information() {

}
void show_guide() {
	printf("-------------------------------------------------------------------------------------------------------------------------\n");
	printf("|         command set       |           argument            |                          description                       \n");
	printf("|                           |                               |                                                            \n");
	printf("|         help, he,h        |         none or 1 command     |                 print all commands or detail of            \n");
	printf("|                           |                               |                                                            \n");
	printf("|         quit, qu,q        |             none              |                          quit program                      \n");
	printf("|                           |                               |                                                            \n");
	printf("|         list, li, l       |    Not exist or 1 flight      |       print flight imformation list or seat information    \n");
	printf("|                           |                               |                                                            \n");
	printf("|     reservation,reserve,r |  flight and seat information  |                          description                       \n");
	printf("|                           |                               |                                                            \n");
	printf("|      cancel, can, c       |            flight             |                           quit flight                      \n");
	printf("|                           |                               |                                                            \n");
	printf("|      deposit, depo,d      |         deposit amount        |                        add user's amount                   \n");
	printf("|                           |                               |                                                            \n");
	printf("|    information, info, i   |             none              |                        print my information                \n");
	printf("-------------------------------------------------------------------------------------------------------------------------\n");

}
vector<string> user_input() {

	vector<string> v;
	v = split_space();
	return v;

}

void user_prompt(string s){
	
	int quit_num = 0;
	vector<string> v;
	while (1) {
		printf("User>");
		v = user_input();
		if (v[0] == "help" or v[0] == "he" or v[0] == "h") {
			help(v);
			continue;
		}
		if (v[0] == "quit" or v[0] == "qu" or v[0] == "q") {
			system("cls");
			break;
		}
		if (v[0] == "list" or v[0] == "li" or v[0] == "l") {
			list(v);
			continue;
		}
		if (v[0] == "reservation" or v[0] == "reserve" or v[0] == "r") {
			system("cls");
			reservation(v);
			continue;
		}
	}

}


int main() {
	printf("@#@323");
}