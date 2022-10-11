#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> split_space() {
    string str;
    getline(cin, str);
    cout << str << endl;
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