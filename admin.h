
#include "integrity_check.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>

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
/*******************daehoon***************/

