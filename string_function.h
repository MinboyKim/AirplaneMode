#ifndef STRING_FUNCTION_H
#define STRING_FUNCTION_H

#include <algorithm>
#include <direct.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> split_space();
vector<string> split_space(string str);
vector<string> split_user_data(string str);
vector<string> split_backslash(string str);
string getline_trim();

bool check_ID(string str);
bool check_name(string str);
bool check_sex(string str);
bool check_TEL(string str);
bool check_birth(string str);

bool integrity_check_name(string str);
bool is_userID_in_data(string str);
bool is_TEL_in_data(string str);
bool is_male(string str);
bool is_number(string str);

bool check_airplane_name(string str);
bool check_place(string str);
bool check_time(string str);
bool check_deposit(string str);
bool check_all_seat(string str);
bool check_seat(string str1, string str2);

string make_name_data(string str);
string make_sex_data(string str);
string make_TEL_data(string str);
string make_birth_data(string str);

void print_ID_warning();
void print_name_warning();
void print_sex_warning();
void print_TEL_warning();
void print_birth_warning();

#endif