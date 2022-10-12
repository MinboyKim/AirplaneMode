#include "string_function.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool sign_in_prompt(string user_ID) {
    vector<string> user_input, new_user_data;
    while (true) {
        cout << "please input your name : ";
        string user_name_input = getline_trim();
        if (user_name_input == "quit") {
            return false;
        }
        if (check_name(user_name_input)) {
            new_user_data.push_back(make_name_data(user_name_input));
            break;
        }
        print_name_warning();
    }

    while (true) {
        cout << "please input your sex : ";
        user_input = split_space();
        if (user_input.size() == 1) {
            if (user_input[0] == "quit") {
                return false;
            }
            if (check_sex(user_input[0])) {
                if (is_male(user_input[0])) {
                    new_user_data.push_back("1");
                } else {
                    new_user_data.push_back("0");
                }
                break;
            }
        }
        print_sex_warning();
    }

    while (true) {
        cout << "please input your phonenumber : ";
        user_input = split_space();
        if (user_input.size() == 1) {
            if (user_input[0] == "quit") {
                return false;
            }
            if (check_TEL(user_input[0])) {
                new_user_data.push_back(make_TEL_data(user_input[0]));
                break;
            }
        }
        print_TEL_warning();
    }

    while (true) {
        cout << "please input your date of birth : ";
        user_input = split_space();
        if (user_input.size() == 1) {
            if (user_input[0] == "quit") {
                return false;
            }
            if (check_birth(user_input[0])) {
                new_user_data.push_back(make_birth_data(user_input[0]));
                break;
            }
        }
        print_birth_warning();
    }

    if (make_new_user(new_user_data, user_ID)) {
        return true;
    } else {
        return false;
    }
}

bool make_new_user(vector<string> new_user_data, string user_ID) {
    string will_write = "^" + user_ID + "^";
    for (int i = 0; i < 4; i++) {
        will_write += new_user_data[i] + "^";
    }
    will_write += "0^";

    char dir[256];
    getcwd(dir, 256);
    string server_dir(dir);
    server_dir += "/data/Userlist.txt";
    ofstream user_data;
    user_data.open(server_dir, ios::app);
    if (user_data.is_open()) {
        user_data << will_write << endl;
        user_data.close();
        return true;
    } else {
        return false;
    }
}