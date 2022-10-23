#ifndef INTEGRITY_CHECK_H
#define INTEGRITY_CHECK_H

#include "string_function.h"
#include <filesystem>
#include <fstream>
#include <io.h>
#include <iostream>
#include <vector>

void integrity_check();
void path_check();
void userList_check();
void available_check();
void rule_check();
bool user_integrity_check(string str);
bool airplane_integrity_check(string str);

#endif