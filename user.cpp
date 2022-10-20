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

using namespace std;
void help(vector<string> v) {

	if (v.size() == 1) {
		showguide();
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
			printf("            : ex> User> reservation KOR 222 A1")

		}
		else if (v[1] == "cancel" or v[1] == "can" or v[1] == "c") {
			printf("description : Instruction \"cancel or can or c \" cancel reservation with 1 argument about flight name. the name is necessary in flight information list \n");
			printf("            : ex> User> cancel KOR111")

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
			showguide();
			return;
		}
	}
}
void list() {

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
	printf("|     reservation,reserve,r |  flight and seat information                             description                       \n");
	printf("|                           |                               |                                                            \n");
	printf("|      cancel, can, c       |            flight             |                           quit flight                      \n");
	printf("|                           |                               |                                                            \n");
	printf("|      deposit, depo,d      |         deposit amount        |                        add user's amount                   \n");
	printf("|                           |                               |                                                            \n");
	printf("|    information, info, i   |             none              |                        print my information                \n");
	printf("-------------------------------------------------------------------------------------------------------------------------\n");

}
vector<string> input_oder() {

	vector<string> v;
	v = split_space();
	return v;

}

void user_prompt(string s){
	
	vector<string> v;
	while (1) {
		printf("User>")
		v = input_oder();
		if (v[0] == "help" or v[0] == "he" or v[0] == "h") {
			system("cls");
			help(v);
			continue;
		}
	}

}


int main() {
	show_guide();
}