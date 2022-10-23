#ifndef INTEGRITY_CHECK_H
#define INTEGRITY_CHECK_H

#include <io.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "string_function.h"

void integrity_check();
void path_check();
void userList_check();
void available_check();
void rule_check();
bool user_integrity_check(string str);
bool airplane_integrity_check(string str);
bool reservation_integrity_check(string str, string seat_data);

#endif