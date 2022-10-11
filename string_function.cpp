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