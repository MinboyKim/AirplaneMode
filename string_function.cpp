#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
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

bool check_name(string str) {}
bool check_sex(string str) {
    string data_set[6] = {"M", "MALE", "MAN", "F", "FEMALE", "WOMAN"};
    for (string data : data_set) {
        if (data == str) {
            return true;
        }
    }
    return false;
}

bool check_birth(string str) { return true; }

bool is_userID_in_data(string str) {
    char dir[256];
    getcwd(dir, 256);
    string server_dir(dir);
    server_dir += "/data/Userlist.txt";
    ifstream user_data;
    user_data.open(server_dir);
    if (user_data.is_open()) {
        while (!user_data.eof()) {
            char data[256];
            user_data.getline(data, 256);
            string dataStr(data);
            string ID_in_data = split_user_data(dataStr)[0];
            if (str == ID_in_data) {
                user_data.close();
                return true;
            }
        }
    } else {
        // if file open fail?
    }
    user_data.close();
    return false;
}

bool is_male(string str) {
    if (str[0] == 'm') {
        return true;
    }
    return false;
}

void print_ID_warning() { cout << "Id gramatical error\n"; }

void print_name_warning() { cout << "Name gramatical error\n"; }

void print_sex_warning() { cout << "Sex gramatical error\n"; }

void print_TEL_warning() { cout << "TEL gramatical error\n"; }

void print_birth_warning() { cout << "birth gramatical error\n"; }
