#include "integrity_check.h"

#include <io.h>
#include <stdio.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "string_function.h"
#include "user.h"

using namespace std;
namespace fs = std::filesystem;

vector<string> user_ID_set;
vector<string> user_TEL_set;
vector<string> reservaton_user_ID;

void integrity_check() {
    user_ID_set.clear();
    user_TEL_set.clear();
    reservaton_user_ID.clear();
    cout << "Start integrity check\n" << endl;
    path_check();
    userList_check();
    available_check();
    rule_check();
    cout << "Integrity check completed!\n" << endl;
}

void path_check() {
    const char *path_data = ".";
    int result_data = _access(path_data, 0);
    if (result_data != 0) {
        cout << "ERROR! Not found server path!\n" << endl;
        exit(0);
    }
    return;
}

void userList_check() {
    const char *path_userList = ".\\data\\Userlist.txt";
    fs::path p("./data");
    if (!fs::exists(p))
        fs::create_directory(p);
    if (_access(path_userList, 0) == -1) {
        cout << "Alert! Necessary file missing.\n" << endl;
        ofstream userList(".\\data\\Userlist.txt");
        if (_access(path_userList, 0) != -1) {
            cout << "File create successfully\n" << endl;
        } else {
            cout << "ERROR! failed to make file.\n" << endl;
            exit(0);
        }
        userList.close();
    }
    return;
}

void available_check() {
    const char *path_userList = ".\\data\\Userlist.txt";
    if (_access(path_userList, 4) == -1) {
        cout << "ERROR! Files that cannot be used in File I/O exist\n";
        exit(0);
    }
    if (_access(path_userList, 2) == -1) {
        cout << "ERROR! Files that cannot be used in File I/O exist\n";
        exit(0);
    }

    string dir = "./data/airplane";
    vector<string> paths;
    if (_access(dir.c_str(), 0) != -1) {
        for (auto &p : std::filesystem::directory_iterator(dir)) {
            paths.push_back(p.path().string());
        }
        for (int i = 0; i < paths.size(); i++) {
            if (_access(paths[i].c_str(), 4) == -1) {
                cout << "ERROR! Files that cannot be used in File I/O exist\n";
                exit(0);
            }
            if (_access(paths[i].c_str(), 2) == -1) {
                cout << "ERROR! Files that cannot be used in File I/O exist\n";
                exit(0);
            }
        }
    }

    return;
}

void rule_check() {
    string userData;
    string airplaneData;
    string airplaneName;
    const char *path_airplane = "./data/airplane";
    ifstream ifs1;
    ifs1.open(".\\data\\Userlist.txt");
    if (ifs1.is_open()) {
        int i = 1;
        while (!ifs1.eof()) {
            getline(ifs1, userData);
            if (i == 1) {
                if (userData == "") {
                    break;
                } else if (user_integrity_check(userData) == 0) {
                    printf("ERROR! Incorrect data exist! ( file name : Userlist.txt , In row %d)\n", i);
                    exit(0);
                }
            } else if (user_integrity_check(userData) == 0) {
                printf("ERROR! Incorrect data exist! ( file name : Userlist.txt , In row %d)\n", i);
                exit(0);
            }
            i++;
        }
        ifs1.close();
    }

    if (!(_access(path_airplane, 0))) {
        string dir = "./data/airplane";
        vector<string> paths;
        if (_access(dir.c_str(), 0) != -1) {
            for (auto &p : std::filesystem::directory_iterator(dir)) {
                paths.push_back(p.path().string());
            }
        }
        for (int l = 0; l < paths.size(); l++) {
            string temp_str = split_backslash(paths[l]).back();
            reservaton_user_ID.clear();
            if (temp_str.size() != 10) {
                cout << "ERROR! Incorrect file Name! ( file name : " << temp_str << "\n";
                exit(0);
            } else if (temp_str.substr(6, 4) != ".txt") {
                cout << "ERROR! Incorrect file Name! ( file name : " << temp_str << "\n";
                exit(0);
            }
            airplaneName = temp_str.substr(0, 6);

            ifstream ifs2(paths[l]);
            if (ifs2.is_open()) {
                getline(ifs2, airplaneData);
                if (airplaneData == "") { //데이터 없음
                    cout << "ERROR! Incorrect data exist! ( file name : " << airplaneName << ", In row 1)\n";
                    exit(0);
                }

                if (airplane_integrity_check(airplaneData) == false) {
                    cout << "ERROR! Incorrect data exist! ( file name : " << airplaneName << ", In row 1)\n";
                    exit(0);
                }

                if (split_user_data(airplaneData)[0] != airplaneName) {
                    cout << "ERROR! Incorrect data exist! ( file name : " << airplaneName << ", In row 1)\n";
                    exit(0);
                }

                string seat_data = split_user_data(airplaneData)[4];
                int i = 2;
                while (!ifs2.eof()) {
                    getline(ifs2, airplaneData);
                    if (!reservation_integrity_check(airplaneData, seat_data)) {
                        cout << "ERROR! Incorrect data exist! ( file name : " << airplaneName << ", In row " << i << ")\n";
                    }
                    i++;
                }
            }
            ifs2.close();
        }
    }
}

bool user_integrity_check(string str) {
    vector<string> integrity_data;
    if (str[0] != '^' || str.back() != '^') {
        return false;
    }
    integrity_data = split_user_data(str);
    if (integrity_data.size() != 6) {
        return false;
    }

    if (!check_ID(integrity_data[0])) {
        return false;
    }

    if (!integrity_check_name(integrity_data[1])) {
        return false;
    }

    if (integrity_data[2] != "1" && integrity_data[2] != "0") {
        return false;
    }

    if (!is_number(integrity_data[3]) || integrity_data[3].size() != 8) {
        return false;
    } else if (!check_TEL(integrity_data[3])) {
        return false;
    }

    if (!is_number(integrity_data[4]) || integrity_data[4].size() != 8) {
        return false;
    } else if (!check_birth(integrity_data[4])) {
        return false;
    }

    if (!is_number(integrity_data[5])) {
        return false;
    }
    for (int i = 0; i < user_ID_set.size(); i++) {
        if (user_ID_set[i] == integrity_data[0]) {
            return false;
        }
    }
    user_ID_set.push_back(integrity_data[0]);

    for (int i = 0; i < user_TEL_set.size(); i++) {
        if (user_TEL_set[i] == integrity_data[3]) {
            return false;
        }
    }
    user_TEL_set.push_back(integrity_data[3]);

    return true;
}

bool airplane_integrity_check(string str) {
    vector<string> integrity_data;
    if (str[0] != '^' || str.back() != '^') {
        return false;
    }
    integrity_data = split_user_data(str); // airplane data split
    if (integrity_data.size() != 5) {
        return false;
    } else if (!(check_airplane_name(integrity_data[0]))) {
        return false;
    } else if (!(check_place(integrity_data[1]))) {
        return false;
    } else if (!(check_time(integrity_data[2]))) {
        return false;
    } else if (!(check_deposit(integrity_data[3]))) {
        return false;
    } else if (!(check_all_seat(integrity_data[4]))) {
        return false;
    }
    return true;
}

bool reservation_integrity_check(string str, string seat_data) {
    vector<string> integrity_data;
    if (str[0] != '^' || str.back() != '^') {
        return false;
    }

    integrity_data = split_user_data(str);
    if (integrity_data.size() != 2) {
        return false;
    }

    if (!check_ID(integrity_data[0])) {
        return false;
    }

    if (integrity_data[1].size() != 2) {
        return false;
    }
    string seat = integrity_data[1];
    if (seat[0] < 'A' || seat[0] > 'I') {
        return false;
    }
    if (seat[1] < '1' || seat[1] > '9') {
        return false;
    }

    if (seat[0] - seat_data[0] > 16) {
        return false;
    }

    if (seat[1] - seat_data[2] > 0) {
        return false;
    }

    bool flag = false;
    for (int i = 0; i < user_ID_set.size(); i++) {
        if (user_ID_set[i] == integrity_data[0]) {
            return true;
            break;
        }
    }

    if (flag)
        return false;

    for (int i = 0; i < reservaton_user_ID.size(); i++) {
        if (reservaton_user_ID[i] == integrity_data[0]) {
            return false;
        }
    }

    reservaton_user_ID.push_back(integrity_data[0]);

    return true;
}