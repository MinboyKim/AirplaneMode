#ifndef USER_H
#define USER_H
//#define _HAS_STD_BYTE 0
#include "string_function.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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

using namespace std;

void user_show_guide();
void user_help(vector<string> v, string userID);
void user_quit();
void user_list(vector<string> v, string userID);
void user_reservation(vector<string> v, string userID);
void user_prompt(string userID);
void user_cancel(string flightName, string userID);
void user_deposit(string iMoney, string userID);
void user_information(string userID);
void user_check(vector<string> v, string userID);
void user_cancel_check(vector<string> v, string userID);
void user_deposit_check(vector<string> v, string userID);
void user_information_check(vector<string> v, string userID);
void user_list_check(vector<string> v, string user_ID);
void user_help_check(vector<string> v, string user_ID);
void user_reservation_check(vector<string> v, string user_ID);
void user_error();
void user_quit_check(vector<string> v, string userID);
vector<string> get_files_indirectory(const string& _path, const string& _filter);
#endif
