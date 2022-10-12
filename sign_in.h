#include "string_function.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool sign_in_prompt(string user_ID);
bool make_new_user(vector<string> new_user_data, string user_ID);