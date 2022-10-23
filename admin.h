#ifndef ADMIN_H
#define ADMIN_H

#include "integrity_check.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

void admin_prompt();

/*******************daehoon***************/
void admin_cancel(string s);
void admin_edit(vector<string> v);
void admin_show_airplane();
void admin_check(vector<string> v);
int admin_check_add(vector<string> v);
int admin_add(vector<string> v);
void error();
int check_integer(char a);
char admin_check_argv(char c);
void admin_quit();
int admin_flight_is_exist(vector<string> v);
/*******************daehoon***************/

/******************yeonggyo***************/
void admin_help(vector<string> v);
void admin_show_user(string s);
void admin_show_guide();
/******************yeonggyo***************/

#endif