#include "string_function.h"
#include <algorithm>
#include <direct.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> split_space() {
    string str;
    getline(cin, str);
    istringstream ss(str);
    string strBuffer;
    vector<string> v;

    v.clear();
    while (getline(ss, strBuffer, ' ')) {
        if (strBuffer != "") {
            v.push_back(strBuffer);
        }
    }

    return v;
}

vector<string> split_space(string str) {
    istringstream ss(str);
    string strBuffer;
    vector<string> v;

    v.clear();
    while (getline(ss, strBuffer, ' ')) {
        if (strBuffer != "") {
            v.push_back(strBuffer);
        }
    }

    return v;
}

vector<string> split_user_data(string str) {
    istringstream ss(str);
    string strBuffer;
    vector<string> v;

    v.clear();
    while (getline(ss, strBuffer, '^')) {
        if (strBuffer != "") {
            v.push_back(strBuffer);
        }
    }

    return v;
}

vector<string> split_backslash(string str) {
    istringstream ss(str);
    string strBuffer;
    vector<string> v;

    v.clear();
    while (getline(ss, strBuffer, '\\')) {
        if (strBuffer != "") {
            v.push_back(strBuffer);
        }
    }

    return v;
}

string getline_trim() {
    string str;
    const char *t = " \t\n\r\f\v";
    getline(cin, str);
    str.erase(0, str.find_first_not_of(t));
    str.erase(str.find_last_not_of(t) + 1);
    return str;
}

bool check_ID(string str) {
    if (str.size() < 4 || str.size() > 16) {
        return false;
    }
    for (int i = 0; i < str.size(); i++) {
        if (!((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z'))) {
            return false;
        }
    }
    return true;
}

bool check_name(string str) {
    int space_check = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == ' ') {
            space_check += 1;
            if (space_check == 2)
                return false;
        }
    }
    istringstream ss(str);
    string strBuffer;
    vector<string> v;

    v.clear();
    while (getline(ss, strBuffer, ' ')) {
        v.push_back(strBuffer);
    }
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            char tmp = v[i][j];
            if (!((tmp >= 'a' && tmp <= 'z') || (tmp >= 'A' && tmp <= 'Z'))) {
                return false;
            }
        }
    }
    return true;
}
bool check_sex(string str) {
    string data_set[6] = {"M", "MALE", "MAN", "F", "FEMALE", "WOMAN"};
    for (string data : data_set) {
        if (data == str) {
            return true;
        }
    }
    return false;
}

bool check_TEL(string str) {
    if (str.size() == 9) {
        if (str[4] != '-') {
            return false;
        }
        for (int i = 0; i < 9; i++) {
            if (i != 4) {
                if (str[i] > '9' || str[i] < '0') {
                    return false;
                }
            }
        }
    } else if (str.size() == 8) {
        for (int i = 0; i < 8; i++) {
            if (str[i] > '9' || str[i] < '0') {
                return false;
            }
        }
    } else if (str.size() == 11) {
        if (str.substr(0, 3) != "010") {
            return false;
        }
        for (int i = 3; i < 11; i++) {
            if (str[i] > '9' || str[i] < '0') {
                return false;
            }
        }
    } else if (str.size() == 13) {
        if (str.substr(0, 3) != "010") {
            return false;
        }
        if (str[3] != '-' || str[8] != '-') {
            return false;
        }
        for (int i = 4; i < 13; i++) {
            if (i != 8) {
                if (str[i] > '9' || str[i] < '0') {
                    return false;
                }
            }
        }
    } else {
        return false;
    }
    return true;
}

bool check_birth(string str) {
    string mod_str = "";
    string division_char = "/.-";

    if (str.size() == 6) {
        mod_str = str;
    } else if (str.size() == 8) {
        if (division_char.find(str[2]) != string::npos && division_char.find(str[5]) != string::npos) {
            mod_str = str.substr(0, 2) + str.substr(3, 2) + str.substr(6, 2);
        } else {
            mod_str = str;
        }
    } else if (str.size() == 10) {
        if (division_char.find(str[4]) != string::npos && division_char.find(str[7]) != string::npos) {
            mod_str = str.substr(0, 4) + str.substr(5, 2) + str.substr(8, 2);
        } else {
            return false;
        }
    } else {
        return false;
    }
    for (int i = 0; i < mod_str.size(); i++) {
        if (mod_str[i] < '0' || mod_str[i] > '9') {
            return false;
        }
    }
    int yyyy, mm, dd;
    if (mod_str.size() == 6) {
        yyyy = stoi(mod_str.substr(0, 2));
        if (yyyy < 22) {
            yyyy += 2000;
        } else {
            yyyy += 1900;
        }
        mm = stoi(mod_str.substr(2, 2));
        dd = stoi(mod_str.substr(4, 2));
    } else {
        yyyy = stoi(mod_str.substr(0, 4));
        mm = stoi(mod_str.substr(4, 2));
        dd = stoi(mod_str.substr(6, 2));
    }
    int day_for_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (yyyy % 4 == 0) {
        if (yyyy % 100 == 0 && yyyy % 400 != 0) {
        } else {
            day_for_month[1] = 29;
        }
    }
    if (mm < 1 || mm > 12) {
        return false;
    }
    if (dd < 1 || dd > day_for_month[mm - 1]) {
        return false;
    }

    if (yyyy > 2022) {
        return false;
    }
    if (yyyy == 2022 && (mm > 11 || (mm == 10 && dd > 3))) {
        return false;
    }

    return true;
}

bool integrity_check_name(string str) {
    bool space = false;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == ' ') {
            if (space) {
                return false;
            } else {
                space = true;
            }
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
        } else {
            return false;
        }
    }
    return true;
}

bool is_userID_in_data(string str) {
    char dir[256];
    _getcwd(dir, 256);
    string server_dir(dir);
    server_dir += "\\data\\Userlist.txt";
    ifstream user_data;
    user_data.open(server_dir);
    if (user_data.is_open()) {
        while (!user_data.eof()) {
            char data[256];
            user_data.getline(data, 256);
            string dataStr(data);
            vector<string> v = split_user_data(dataStr);
            if (v.size() > 0) {
                string ID_in_data = split_user_data(dataStr)[0];
                if (str == ID_in_data) {
                    user_data.close();
                    return true;
                }
            }
        }
    } else {
        // if file open fail?
    }
    user_data.close();
    return false;
}

bool is_male(string str) {
    if (str[0] == 'M') {
        return true;
    }
    return false;
}

bool is_number(string str) {
    for (int i = 0; i < str.size(); i++) {
        if (isdigit(str[i]) == 0) {
            return false;
        }
    }
    return true;
}

bool check_airplane_name(string str) {
    if (str.size() != 6) {
        return false;
    }

    for (int i = 0; i < 3; i++) {
        if (!(str[i] >= 'A' && str[i] <= 'Z')) {
            return false;
        }
    }
    for (int i = 3; i < 6; i++) {
        if (!(str[i] >= '1' && str[i] <= '9')) {
            return false;
        }
    }
    return true;
}

bool check_place(string str) {
    if (str.size() != 6) {
        return false;
    }
    for (int i = 0; i < 6; i++) {
        if (!(str[i] >= 'A' && str[i] <= 'Z')) {
            return false;
        }
    }
    return true;
}

bool check_time(string str) {
    if (str.size() != 24) {
        return false;
    }
    for (int i = 0; i < 24; i++) {
        if (!(str[i] >= '0' && str[i] <= '9')) {
            return false; // check if they're all number
        }
    }
    // check if it's before 2022/1003/0000
    if (stoi(str.substr(0, 4)) < 2022) {
        return false;
    } else if (stoi(str.substr(0, 4)) == 2022 && stoi(str.substr(4, 2)) < 10) {
        return false;
    } else if (stoi(str.substr(0, 4)) == 2022 && stoi(str.substr(4, 2)) == 10 && stoi(str.substr(6, 2)) < 3) {
        return false;
    }

    // check if arrival time faster than departure time
    if (stoi(str.substr(12, 4)) < stoi(str.substr(0, 4))) {
        return false;
    } else if (stoi(str.substr(12, 4)) == stoi(str.substr(0, 4)) && stoi(str.substr(16, 4)) < stoi(str.substr(4, 4))) {
        return false;
    } else if (stoi(str.substr(12, 4)) == stoi(str.substr(0, 4)) && stoi(str.substr(16, 4)) == stoi(str.substr(4, 4)) &&
               stoi(str.substr(20, 2)) < stoi(str.substr(8, 2))) {
        return false;
    } else if (stoi(str.substr(12, 4)) == stoi(str.substr(0, 4)) && stoi(str.substr(16, 4)) == stoi(str.substr(4, 4)) &&
               stoi(str.substr(20, 2)) == stoi(str.substr(8, 2)) && stoi(str.substr(22, 2)) < stoi(str.substr(10, 2))) {
        return false;
    }
    return true;
}

bool check_deposit(string str) {
    for (int i = 0; i < str.size(); i++) {
        if (!(str[i] >= '0' && str[i] <= '9')) {
            return false; // check if they're all number
        }
    }
    if (str[0] == '0') {
        return false;
    }
    return true;
}

bool check_all_seat(string str) {
    if (!((str[0] >= '0' && str[0] <= '9') && (str[2] >= '0' && str[2] <= '9'))) {
        return false;
    }
    return true;
}

bool check_seat(string str1, string str2) // str1-->all seat , str2 --> current seat
{
    if (!((str2[0] >= 'A' && str2[0] <= 'Z') && (str2[2] >= '0' && str2[2] <= '9'))) {
        return false;
    }
    if (int(str2[0]) - 64 > int(str1[0])) {
        return false;
    } else if (int(str2[0]) - 64 == int(str1[0]) && int(str2[1]) > int(str1[2])) {
        return false;
    }
    return true;
}

string make_name_data(string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

string make_TEL_data(string str) {
    string data_str;
    if (str.size() == 8) {
        data_str = str;
    } else if (str.size() == 9) {
        data_str = str.substr(0, 4) + str.substr(5, 4);
    } else if (str.size() == 11) {
        data_str = str.substr(3, 8);
    } else if (str.size() == 13) {
        data_str = str.substr(4, 4) + str.substr(9, 4);
    }
    return data_str;
}

string make_birth_data(string str) {
    string mod_str = "";
    string division_char = "/.-";

    if (str.size() == 6) {
        mod_str = str;
    } else if (str.size() == 8) {
        if (division_char.find(str[2]) != string::npos && division_char.find(str[5]) != string::npos) {
            mod_str = str.substr(0, 2) + str.substr(3, 2) + str.substr(6, 2);
        } else {
            mod_str = str;
        }
    } else if (str.size() == 10) {
        if (division_char.find(str[4]) != string::npos && division_char.find(str[7]) != string::npos) {
            mod_str = str.substr(0, 4) + str.substr(5, 2) + str.substr(8, 2);
        } else {
        }
    }

    if (mod_str.size() == 6) {
        if (stoi(mod_str.substr(0, 2)) < 22) {
            mod_str = "20" + mod_str;
        } else {
            mod_str = "19" + mod_str;
        }
    }

    return mod_str;
}

void print_ID_warning() { cout << "Id gramatical error\n"; }

void print_name_warning() { cout << "Name gramatical error\n"; }

void print_sex_warning() { cout << "Sex gramatical error\n"; }

void print_TEL_warning() { cout << "TEL gramatical error\n"; }

void print_birth_warning() { cout << "birth gramatical error\n"; }