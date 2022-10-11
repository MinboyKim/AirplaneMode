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

void log_in_prompt() {
    string input_id;
    while (true) {
        cout << "Id > ";
        vector<string> Id_input;
        while (cin >> input_id) {
        }
        if (input_id == "admin") {
            admin_prompt();
            break;
        } else {
        }
    }
}

void run() {
    integrity_check();
    log_in_prompt();
}

int main() {
    // run();
    return 0;
}