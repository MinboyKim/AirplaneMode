#include "sign_in.h"
#include "string_function.h"

using namespace std;
namespace fls = std::filesystem;

bool make_new_user(vector<string> new_user_data, string user_ID) {
    string will_write = "^" + user_ID + "^";
    for (int i = 0; i < 4; i++) {
        will_write += new_user_data[i] + "^";
    }
    will_write += "0^0^";

    char dir[256];
    _getcwd(dir, 256);
    string server_dir(dir);
    fls::path p("./data");
    if (!fls::exists(p))
        fls::create_directory(p);
    server_dir += "./data/Userlist.txt";

    bool enter = false;
    ifstream user_data_r;
    user_data_r.open(server_dir);
    if (user_data_r.is_open()) {
        string first_line;
        getline(user_data_r, first_line);
        if (first_line != "") {
            enter = true;
        } else {
            enter = false;
        }
        user_data_r.close();
    }

    ofstream user_data;
    user_data.open(server_dir, ios::app);
    if (user_data.is_open()) {
        if (enter) {
            user_data << endl;
        }
        user_data << will_write;
        user_data.close();
        return true;
    } else {
        return false;
    }
}

bool sign_in_prompt(string user_ID) {
    bool (*check_func[])(string) = {check_name, check_sex, check_TEL, check_birth};
    bool (*make_func[])(string) = {make_name_data, make_sex_data, make_TEL_data, make_birth_data};
    void (*print_func[])() = {print_name_warning, print_sex_warning, print_TEL_warning, print_birth_warning};
    vector<string> user_input, new_user_data;
    string print_data[4] = {"please input your name : ", "please input your sex : ", "please input your phonenumber : ", "please input your date of birth : "};

    for (int i = 0; i < 4; i++) {
        while (true) {
            cout << print_data[i];

            if (i == 0) {
                user_input.clear();
                string user_name_input = getline_trim();
                user_input.push_back(user_name_input);
            } else {
                user_input = split_space();
            }

            if (user_input.size() == 1) {
                if (user_input[0] == "quit") {
                    return false;
                }
                if (check_func[i](user_input[0])) {
                    new_user_data.push_back(make_func[i](user_input[0]));
                    break;
                }
            }
            print_func[i]();
        }
    }

    if (make_new_user(new_user_data, user_ID)) {
        return true;
    } else {
        return false;
    }
}