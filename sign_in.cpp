#include "string_function.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool sign_in_prompt() {
    vector<string> user_input, new_user_data;
    while (true) {
        cout << "please input your name : ";
        user_input = split_space();
        if (user_input.size() == 1) {
            if (user_input[0] == "quit") {
                return false;
            }
            if (check_name(user_input[0])) {
                new_user_data.push_back(user_input[0]);
                break;
            }
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
            if (check_name(user_input[0])) {
                new_user_data.push_back(user_input[0]);
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
                new_user_data.push_back(user_input[0]);
                break;
            }
        }
        print_birth_warning();
    }

    if (make_new_user(new_user_data)) {
        return true;
    } else {
        return false;
    }
}

bool make_new_user(vector<string> new_user_data) { return false; }