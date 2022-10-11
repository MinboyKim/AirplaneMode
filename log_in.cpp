#include "admin.h"
#include "sign_in.h"
#include "string_function.h"
#include "user.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void log_in_prompt() {
    while (true) {
        cout << "Id > ";
        vector<string> ID_input;
        ID_input = split_space();
        if (ID_input.size() == 0) {
            continue;
        } else if (ID_input.size() >= 2) {
            print_ID_warning();
            continue;
        }
        if (ID_input.size() == 1) {
            if (ID_input[0] == "admin") {
                admin_prompt();
                break;
            } else if (check_ID(ID_input[0])) {
                if (is_userID_in_data(ID_input[0])) {
                    user_prompt(ID_input[0]);
                    break;
                } else if (sign_in_prompt(ID_input[0])) {
                    user_prompt(ID_input[0]);
                    break;
                }
            }
        }
    }
}
