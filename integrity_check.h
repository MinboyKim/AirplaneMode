#include <iostream>
#include <io.h>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <filesystem>
#include "string_function.h"

void integrity_check();
void path_check();
void userList_check();
void available_check();
void rule_check();
vector<string> get_files_indirectory(const string& _path, const string& _filter);
bool user_integrity_check(string str);
bool airplane_integrity_check(string str);
