#include "admin.h"
#include "sign_in.h"
#include "string_function.h"
#include "user.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void log_in_prompt() {
    string input_id;
    while (true) {
        cout << "Id > ";
        vector<string> ID_input;
        ID_input = split_space();
        if (ID_input.size() != 1) {
            print_ID_warning();
            continue;
        } else if (!check_ID(ID_input[0])) {
            print_ID_warning();
            continue;
        } else {
            if (ID_input[0] == "admin") {
                admin_prompt();
                break;
            } else if (is_userID_in_data(ID_input[0])) {
                user_prompt(ID_input[0]);
                break;
            } else {
                if (sign_in_prompt()) {
                    user_prompt(ID_input[0]);
                    break;
                }
            }
        }
    }
}