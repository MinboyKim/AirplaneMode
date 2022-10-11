#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

using namespace std;

vector<string> split_space();
vector<string> split_space(string str);
vector<string> split_user_data(string str);
bool check_ID(string str);
bool check_name(string str);
bool check_sex(string str);
bool check_birth(string str);
bool is_userID_in_data(string str);
bool is_male(string str);
void print_ID_warning();
void print_name_warning();
void print_sex_warning();
void print_TEL_warning();
void print_birth_warning();