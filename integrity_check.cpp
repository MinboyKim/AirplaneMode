//#include "integrity_check.h"
//#include <iostream>
//#include <io.h>
//#include <fstream>
//#include <vector>
//#include <Windows.h>
//
//using namespace std;
//namespace fs = std::filesystem;
//
//void integrity_check() {
//	cout << "Start integrity check" << endl;
//}
//
//void path_check()
//{
//	const char* path_data = ".\\data";
//	int result_data = access(path_data, 0);
//
//	if (result_data == 0) {
//		cout << ".\\data exist" << endl;
//	}
//
//	else {
//		cout << ".\\data not exist" << endl;
//		cout << "make .\\data" << endl;
//		ofstream data(".\\data");
//		if (path_data == 0) {
//			cout << "Success!" << endl;
//		}
//		else {
//			cout << "Fail" << endl;
//			return;
//		}
//	}
//}
//
//
//void userList_check() {
//	const char* path_userList = ".\\data\\Userlist.txt";
//	int result_userList = access(path_userList, 0);
//
//	if (path_userList == 0) {
//		cout << ".data\\Userlist.txt exist " << endl;
//	}
//
//	else {
//		cout << ".data\\UserlIst.txt not exist" << endl;
//		cout << "make .data\\Userlist.txt" << endl;
//		ofstream userList(".\\data\\Userlist.txt");
//		if (path_userList == 0) {
//			cout << "Success!" << endl;
//		}
//		else {
//			cout << "Fail" << endl;
//			return;
//		}
//	}
//}
//
//void available_check()
//{
//	Userlist is already checked so don't need to check it again
//	cout << "Start available check" << endl;
//	string path_airplane = ".\\data\\airplane";
//	vector<string> files = get_files_indirectory(path_airplane, "*");
//	for(int i=2; i<sizeof(files); i++){
//		string fn = files[i];
//		if (fn.substr(fn.find_last_of(".") + 1) != "txt") {
//			cout << "ERROR: can't open file except .txt" << endl;
//			return;
//		}
//	}
//	cout << "available check is successful" << endl;
//	
//}
//
//void rule_check()
//{
//	ifstream ifs;
//	ifs.open(".\\data\\Userlist.txt");
//	if (ifs.fail()) {
//		cerr << "Error!" << endl;
//		return;
//	}
//
//}
//
//vector<string> get_files_indirectory(const string& _path, const string& _filter) {
//	string searching = _path + _filter;
//	vector<string> return_;
//	_finddata_t fd;
//	intptr_t handle = _findfirst(searching.c_str(), &fd);
//	if (handle == -1) return return_;
//	int result = 0;
//	do {
//		return_.push_back(fd.name);
//		result = _findnext(handle, &fd);
//	} while (result != -1);
//	_findclose(handle);
//	return return_;
//
//}
//
