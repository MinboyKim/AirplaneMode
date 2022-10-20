#include "integrity_check.h"
#include "log_in.h"
#include <iostream>
#include <string>
#include <vector>
#include "user.h"

using namespace std;

void run();

void run() {
    integrity_check();
    log_in_prompt();
}

int main() {
    run();
    return 0;
}
