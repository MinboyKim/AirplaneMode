#include "admin.h"
#include "integrity_check.h"
#include "string_function.h"
#include "user.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void log_in_prompt();
void run();
void print_ID_warning();

void print_ID_warning() { cout << "Id gramatical error\n"; }

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
            } else {
            }
        }
    }
}

void run() {
    integrity_check();
    log_in_prompt();
}

int main() {
    run();
    return 0;
}