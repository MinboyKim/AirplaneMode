#include<stdio.h>
#include<vector>
#include<windows.h>
#include<fstream>
#include<io.h>
#include<conio.h>
#include "string_function.h"
#include "user.h"
#include "integrity_check.h"
#include <iostream>
#include <string>
#include <sstream>
#include<typeinfo>
#include <regex>
#include <filesystem>
#include <direct.h>


using namespace std;

namespace fls = std::filesystem;

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
void user_show_guide() {
	cout << ("---------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	cout << ("|                    command set                            |           argument            |                          description                       \n");
	cout << ("|                                                           |                               |                                                            \n");
	cout << ("|                    help, he,h                             |         none or 1 command     |                 print all commands or detail of            \n");
	cout << ("|                                                           |                               |                                                            \n");
	cout << ("|                    quit, qu,q                             |             none              |                          quit program                      \n");
	cout << ("|                                                           |                               |                                                            \n");
	cout << ("|                    list, li, l                            |    Not exist or 1 flight      |       print flight imformation list or seat information    \n");
	cout << ("|                                                           |                               |                                                            \n");
	cout << ("|     reservation,reserve,resrv, reser, rese, res, re, r    |  flight and seat information  |                          description                       \n");
	cout << ("|                                                           |                               |                                                            \n");
	cout << ("|      cancel, cance, canc, can, ca, c                      |            flight             |                           quit flight                      \n");
	cout << ("|                                                           |                               |                                                            \n");
	cout << ("|      deposit, depo,depos, depo, dep, de, d                |         deposit amount        |                        add user's amount                   \n");
	cout << ("|                                                           |                               |                                                            \n");
	cout << ("|    information, inform, infor, info, inf, in, i           |             none              |                        print my information                \n");
	cout << ("---------------------------------------------------------------------------------------------------------------------------------------------------------\n");

}

vector<string> user_input() {

	vector<string> v;
	v = split_space();
	return v;

}

void user_help(vector<string> v, string userID) {

	if (v.size() == 1) {
		system("cls");
		user_show_guide();
		user_prompt(userID);
		return;
	}

	else if (v.size() == 2) {// 명령어와 인자를 입력한 경우
		if (v.at(1) == "help" || v.at(1) == "hel" || v.at(1) == "he" || v.at(1) == "h") {
			system("cls");
			cout << "description : Instruction \" help or hel or he \" shows you information about user's instruction.\n" << endl;
			cout << "              if you use it with 1 argument that composed of 1 instruction like \" quit \" you can read about more detail information \n" << endl;
			cout << "              if you use it with no argument, you can see basic information about all instructions\n" << endl;
		}
		else if (v.at(1) == "quit" || v.at(1) == "qu" || v.at(1) == "q" || v.at(1) == "qui") {
			system("cls");
			cout << "description : Instruction \"quit or qu or q \" quits program \n" << endl;
		}
		else if (v.at(1) == "list" || v.at(1) == "lis" || v.at(1) == "li" || v.at(1) == "l") {
			system("cls");
			cout << "description : Instruction \"list or li or l \" prints flight list \n" << endl;
			cout << "              if you use it with 1 flight you can see about seat information. \n" << endl;
			cout << "              if you use it with no argument, you can see all flight information in list \n" << endl;
		}
		else if (v.at(1) == "reservation" || v.at(1) == "reserve" || v.at(1) == "reserv" || v.at(1) == "reser" || v.at(1) == "rese" || v.at(1) == "res" || v.at(1) == "re" || v.at(1) == "r") {
			system("cls");
			cout << "description : Instruction \"reservation or reserve or r \" reserve seat. you can use this instuctrion with 2 arguments flight name and seat postion. \n" << endl;
			cout << "            : ex> User> reservation KOR 222 A1" << endl;

		}
		else if (v.at(1) == "cancel" || v.at(1) == "cance" || v.at(1) == "canc" || v.at(1) == "can" || v.at(1) == "ca" || v.at(1) == "c") {
			system("cls");
			cout << "description : Instruction \"cancel or can or c \" cancel reservation with 1 argument about flight name. the name is necessary in flight information list \n" << endl;
			cout << "            : ex> User> cancel KOR111" << endl;

		}
		else if (v.at(1) == "deposit" || v.at(1) == "deposi" || v.at(1) == "depos" || v.at(1) == "dep" || v.at(1) == "de" || v.at(1) == "d") {
			system("cls");
			cout << "description : Instruction \" deposit or depo or d \" deposit user's money. You can use this instruction with 1 argument about amount. \n" << endl;
			cout << "            : ex> User> deposit 1120" << endl;

		}
		else if (v.at(1) == "information" || v.at(1) == "inform" || v.at(1) == "infor" || v.at(1) == "info" || v.at(1) == "inf" || v.at(1) == "in" || v.at(1) == "i") {
			system("cls");
			cout << "description : Instruction \" information or info or i \" prints user's information with no argument.\n" << endl;
			cout << "            : ex> User> informaiton\n" << endl;
			cout << "            : cj2200 ChoiJungyu M 01050362323 1990622\n" << endl;
		}
		else {
			system("cls");
			user_show_guide();
			cout << "Syntex Error" << endl;
			user_prompt(userID);
			return;
		}
	}
	user_prompt(userID);
}

void user_quit()
{
}
void user_list(vector<string> v,string userID) {
	
			// 인자가 없는 경우.
			vector<string> flight; //항공편명 리스트벡터
			vector<string> f_info;
			vector<string> f_info_temp;
			string path;

			char dir[256];
			_getcwd(dir, 256);
			string server_dir(dir);
			server_dir += "\\data\\airplane\\";
			path = server_dir;
			string temp = path;

			if (v.size() == 1) { // 인자가 없는 경우.

				flight = get_files_indirectory(server_dir, "*.*");
				
				if (flight.size() == 0) {
					cout << "No flights list" << endl;
					user_prompt(userID);
					return;
				}

				for (int i = 2; i < flight.size(); i++) {//파일 하나씩 읽어오기
					path = temp;
					path = path + flight.at(i);//읽어드릴 텍스트파일 경로

					ifstream readFile;
					readFile.open(path);
					while (!readFile.eof()) {
						string str;
						getline(readFile, str);
						f_info_temp = split_user_data(str);
						f_info.insert(f_info.end(), f_info_temp.begin(), f_info_temp.end());

					}
					readFile.close();


					for (int k = 0; k < 5; k++) { //항공편명, 출발도착지,츨발도착지, 좌석, 가격
						if (k == 1) {
							for (int j = 0; j < 3; j++) {
								cout << f_info.at(k)[j];
							}
							cout << " / ";
							for (int j = 3; j < 6; j++) {
								cout << f_info.at(k)[j];
							}
							cout << " ";
							continue;
						}
						if (k == 2) {
							for (int j = 0; j < 11; j++) {
								cout << f_info.at(k)[j];
							}
							cout << " ~ ";
							for (int j = 11; j < 24; j++) {
								cout << f_info.at(k)[j];
							}

							cout << " ";
							continue;
						}

						if (k == 3) {
							cout << f_info.at(k)[0] << "," << f_info.at(k)[2]<<" ";
							continue;
						}
						cout << f_info.at(k); //5번-이름 6번-좌석정보 7번-이름 8번-좌석정보 f_info --> flight 마다 저장된 데이터 리스트.
						cout << " ";
					}
					cout << endl;
					f_info.clear();
					f_info_temp.clear();
				}
			}
		
	



	else if (v.size() == 2) {//인자가 2개일때.

		string check_string;
		check_string = v.at(1);
		if (check_string.size() != 6) { //입력된 인자가 6글자 이상이므로 리턴
			system("cls");
			cout << "Syntex Error" << endl;
			user_prompt(userID);
			return;
		}
		for (int i = 0; i < 3; i++) {
			if (check_string[i] < 'A' || check_string[i]>'Z') { //대문자로 이루어진 경우가 아닌 경우 리턴
				user_prompt(userID);
				return;
			}
			if (check_string[i + 3] < '0' || check_string[i + 3]>'9') { // 숫자로 이루어진 경우가 아닌 경우 리턴
				user_prompt(userID);
				return;
			}
		}

		flight = get_files_indirectory(server_dir, "*.*");

		int index = -1;

		for (int a = 2; a < flight.size(); a++) {
			if ((v.at(1) + ".txt") == flight.at(a)) {
				index = a;
			}
		}
		if (index == -1) {

			cout << "no flight name" << endl;
			user_prompt(userID);
			return;
		}
		else
		{
			ifstream readFile;
			path = path + flight.at(index);
			readFile.open(path);
			while (!readFile.eof()) {
				string str;
				getline(readFile, str);
				f_info_temp = split_user_data(str);
				f_info.insert(f_info.end(), f_info_temp.begin(), f_info_temp.end());
			}
			readFile.close();
			if (f_info.size() < 6) {//예약된 좌석이 없는 경우 모두 0으로 출력.
				
				int co = 0;
				int ru = 0;
				co = f_info.at(3)[0] - 48; //행
				ru = f_info.at(3)[2] - 48; //렬

				for (int h = 0; h < co*ru; h++) {
					cout << '0 ';
					if (h % 4 == 1) {
						cout << endl;
					}
				}
			}
			else {
				int c = -1;
				int r = -1;
				int Seat_array[100][100] = { 0 };

				for (int h = 6; h < f_info.size(); h++) {
					if (h % 2 == 0) {

						c = f_info.at(h)[0] - 65;
						r = f_info.at(h)[1] - 48;

						if (c < 0) {
							cout << "error" << endl;
							user_prompt(userID);
							return;
						}

						Seat_array[c][r] = 1;
						c = -1;
						r = -1;
					}
				}
				int co = 0;
				int ru = 0;
				co = f_info.at(3)[0] - 48; //행
				ru = f_info.at(3)[2] - 48; //렬


				for (int g = 0; g < co; g++) {
					for (int l = 0; l < ru; l++) {
						cout << Seat_array[g][l] << " ";
					}
					cout << endl;
				}

			}
		}
	}
	user_prompt(userID);
}




void user_reservation(vector<string> v,string userID) //v[0] 명령어 - flight name v[1] - seat_information v[2]
{

	char dir[256];
	_getcwd(dir, 256);
	string server_dir(dir);
	server_dir += "\\data\\airplane\\";

	if (v.size() != 3) { //인자 개수 맞게 입력 안하면 
		cout << "Syntax Error" << endl;
		user_prompt(userID);
		return;
	}

	string check_string;
	//항공편 리스트 문법
	check_string = v.at(1);
	if (check_string.size() != 6) { //입력된 인자가 6글자 이상이므로 리턴
		cout << "Syntax Error" << endl;
		user_prompt(userID);
		return;
	}
	for (int i = 0; i < 3; i++) {
		if (check_string[i] < 'A' || check_string[i]>'Z') { //대문자로 이루어진 경우가 아닌 경우 리턴
			cout << "Syntax Error" << endl;
			user_prompt(userID);
			return;
		}
		if (check_string[i + 3] < '0' or check_string[i + 3]>'9') { // 숫자로 이루어진 경우가 아닌 경우 리턴
			cout << "Syntax Error" << endl;
			user_prompt(userID);
			return;
		}
	}
	//항공편 리스트 자리 문법
	string check_seat = v.at(2);
	if (check_seat.size() != 2) {
		cout << "Syntax Error" << endl; //입력된 글자가 2글자가 아니므로 리턴
		user_prompt(userID);
		return;
	}
	if (check_seat[0]<'A' || check_seat[0] > 'Z') {
		cout << "Syntax Error" << endl; //좌석 첫번째가 영어가 아니므로 리턴
		user_prompt(userID);
		return;
	}
	if (check_seat[1]<'0' || check_seat[1] > '9') {
		cout << "Syntax Error" << endl; //좌석 입력 두번째가 숫자가 아니므로 리턴.
		user_prompt(userID);
		return;
	}

	int indexf = -1;
	vector<string> flight_vector;
	string path;
	path = "C:\\flights\\";
	path =server_dir;
	flight_vector = get_files_indirectory(server_dir, "*.*"); // flight_vector 에 폴더에있는 파일 이름 명저장 ex KOR111.txt

	for (int i = 2; i < flight_vector.size(); i++) {
		if ((v.at(1)+".txt") == flight_vector.at(i)) {
			indexf = i;
			break;
		}
	}
	if (indexf == -1) {
		system("cls");
		cout << "No flight sorry man" << endl;
		user_prompt(userID);
		return;
	}

	ifstream readFile;
	vector<string> f_info;
	vector<string> f_info_temp;
	path = path + flight_vector.at(indexf);
	readFile.open(path);
	while (!readFile.eof()) {

		string str;
		getline(readFile, str);
		f_info_temp = split_user_data(str);
		f_info.insert(f_info.end(), f_info_temp.begin(), f_info_temp.end()); // 5번부터 유저 정보 좌석정보는 3번.

	}
	readFile.close();

	char seat_number_1 = f_info.at(3)[0]; //좌석 개수 몇곱하기 몇의 앞자리만 따와서
	char seat_number_2 = f_info.at(3)[2]; //좌석 개수 몇곱하기 몇의 뒷자리만 따와서

	
	if (seat_number_1-48 < v.at(2)[0] - 65 || seat_number_2 - 48 < v.at(2)[1] - 48) {
		cout << "No flight seat" << endl;
		user_prompt(userID);
		return;
	}
	else { 

		for (int j = 6; j<f_info.size(); j++) {
			
			if (v.at(2) == f_info.at(j)) {
				cout << "alreay reserved seat sorry man" << endl;
				user_prompt(userID);
				return;
			}

		}
		ofstream writeFile;
		writeFile.open(path,ios::app);

		if (writeFile.is_open()) {

			writeFile << "^"+userID + "^" + v.at(2) + "^" << endl;
			cout << "reservation completed!" << endl;
		}
		writeFile.close();
		user_prompt(userID);
		return;
	}

	user_prompt(userID);
	

}
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

void user_prompt(string userID) {
	printf("User> ");
	string s;
	cin.clear();
	getline(cin, s);
	vector<string> v(1000);
	v = split_space(s);
	user_check(v, userID);
}

void user_cancel(string flightName, string userID)
{
	char dir[256];
	_getcwd(dir, 256);
	string server_dir(dir);
	server_dir += "\\data\\" + flightName;
	fls::path p(server_dir);
	if (fls::exists(p)) {
		FILE* p_file = NULL;
		vector<string> txtAll;
		char buffer[128];
		if (0 == fopen_s(&p_file, server_dir.c_str(), "rt")) {
			while (fgets(buffer, 128, p_file) != NULL) {
				txtAll.push_back(buffer);
			}
			fclose(p_file);
		}

		int index = 0;
		string tempString;
		for (auto i : txtAll) {
			index++;
			if (i.find(userID) != string::npos) {
				break;
			}
		}
		txtAll[index] = "";
		ofstream ofile;
		ofile.open(server_dir);
		for (auto i : txtAll) {
			ofile << i;
		}
		ofile.close();
		cout << "Delete success" << endl;
		return;
	}
	else {
		cout << "There is no flight " << '"' << flightName << '"' << endl;
		return;
	}
}

void user_deposit(string iMoney, string userID)
{
	int money = stoi(iMoney);
	char dir[256];
	_getcwd(dir, 256);
	string server_dir(dir);
	server_dir += "\\data\\Userlist.txt";
	
	FILE* p_file = NULL;
	vector<string> txtAll;
	char buffer[128];
	if (0 == fopen_s(&p_file, server_dir.c_str(), "rt")) {
		while (fgets(buffer, 128, p_file) != NULL) {
			txtAll.push_back(buffer);
		}
		fclose(p_file);
	}
	
	int index = 0;
	string tempString;
	for (auto i : txtAll) {
		index++;
		if (i.find(userID) != string::npos) {
			istringstream ss(i);
			string stringBuffer;
			vector<string> tempVector;
			while (getline(ss, stringBuffer, '^')) {
				tempVector.push_back(stringBuffer);
			}
			tempVector[6] = to_string(money + stoi(tempVector[6]));
			for (auto iter : tempVector) {
				if (iter != "")tempString.append("^" + iter);
			}
			break;
		}
	}
	txtAll[index - 1] = tempString;
	
	ofstream ofile;
	ofile.open(server_dir);
	for (auto i : txtAll) {
		ofile << i;
	}
	ofile.close();
	cout << "deposition complete" << endl;
}

void user_information(string userID)
{
	char dir[256];
	_getcwd(dir, 256);
	string server_dir(dir);
	server_dir += "\\data\\Userlist.txt";

	FILE* p_file = NULL;
	vector<string> txtAll;
	char buffer[128];
	if (0 == fopen_s(&p_file, server_dir.c_str(), "rt")) {
		while (fgets(buffer, 128, p_file) != NULL) {
			txtAll.push_back(buffer);
		}
		fclose(p_file);
	}

	int index = 0;
	vector<string> tempVector;
	for (auto i : txtAll) {
		index++;
		if (i.find(userID) != string::npos) {
			istringstream ss(i);
			string stringBuffer;
			while (getline(ss, stringBuffer, '^')) {
				tempVector.push_back(stringBuffer);
			}
			break;
		}
	}
	tempVector[7] = "";
	for (auto i : tempVector) {
		if(i != "")cout << i << " ";
	}
	cout << endl;
}


void user_check(vector<string> v, string userID) {
		string cmd = v[0];
		if (cmd == "cancel" || cmd == "cance" || cmd == "canc" || cmd == "can" || cmd == "ca" || cmd == "c") user_cancel_check(v, userID);
		else if (cmd == "deposit" || cmd == "deposi" || cmd == "depos" || cmd == "depo" || cmd == "dep" || cmd == "de" || cmd == "d") user_deposit_check(v, userID);
		else if (cmd == "information" || cmd == "inform" || cmd == "infor" || cmd == "info" || cmd == "inf" || cmd == "in" || cmd == "i") user_information_check(v, userID);
		else if (cmd == "help" || cmd == "hel" || cmd == "he" || cmd == "h") user_help_check(v, userID);
		else if (cmd == "reservation" || cmd == "reserve" || cmd == "reserv" || cmd == "reser" || cmd == "rese" || cmd == "res" || cmd == "re" || cmd == "r")user_reservation_check(v, userID);
		else if (cmd == "list" || cmd == "lis" || cmd == "li" || cmd == "l") user_list_check(v, userID);
		else if (cmd == "quit" || cmd == "qu" || cmd == "qui" || cmd == "q") exit(0);
		else return;
}

void user_cancel_check(vector<string> v, string userID)
{
	if (v.size() != 2) {
		user_error();
		user_prompt(userID);
		return;
	}
	else {
		regex re("[A-Z]{3}[0-9]{3}");
		if (regex_match(v[1], re)) {
			user_cancel(v[1], userID);
			user_prompt(userID);
			return;
		}
		else {
			user_error();
			user_prompt(userID);
			return;
		}
	}
}

void user_deposit_check(vector<string> v, string userID)
{
	if (v.size() != 2 ) {
		user_error();
		user_prompt(userID);
		return;
	}
	else {
		regex re("\\d*");
		if (regex_match(v[1], re)) {
			user_deposit(v[1], userID);
			user_prompt(userID);
			return;
		}
		else {
			user_error();
			user_prompt(userID);
			return;
		}
	}
}

void user_information_check(vector<string> v, string userID)
{
	if (v.size() != 1) {
		user_error();
		user_prompt(userID);
		return;
	}
	else {
		user_information(userID);
		user_prompt(userID);
		return;
	}
}

void user_error()
{
	cout << "Syntax ERROR" << endl;
	return;
}
void user_help_check(vector<string> v,string user_ID) {

	if (v.size() == 0) {
		user_error();
		user_prompt(user_ID);

	}
	else user_help(v, user_ID);
}


void user_reservation_check(vector<string> v, string user_ID) {

	if (v.size() == 0) {
		user_error();
		user_prompt(user_ID);
	}
	else user_reservation(v, user_ID);

}

void user_list_check(vector<string> v, string user_ID) {
	if (v.size() == 0) {
		user_error();
		user_prompt(user_ID);
	}
	else user_list(v, user_ID);
}
