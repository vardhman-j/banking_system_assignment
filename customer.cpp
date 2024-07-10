#include <bits/stdc++.h>
using namespace std;

vector<int> map1(26, 0);

void map_init(){
    map1['a' - 97] = 1; 
    for(int i = 1; i<26; i++){
        map1[i] = 2*map1[i-1] + i;
    }
}

string get_user_id(string name){
    long long sum = 0;

    for(char c : name){
        sum += map1[((tolower(c))) - 'a'];
    }
    return to_string(sum);
}

string cur_date(){
    time_t cur_time = time(0);
    tm* ltm = localtime(&cur_time);
    string date = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
    return date;
}

vector<string> date_split(string date){
    string day = "", month = "" , year = "";
    int n = 0;
    for(int i = 0;i<date.size(); i++){
        char c = date[i];
        if (c != '/'){
            if (n == 0) day += c;
            else if (n == 1) month += c;
            else year += c;
        }
        else n++;
    }
    return {day, month, year};
}


class User{
    protected:
        string email, address, phone_number;
        int age;
    public:
        string user_id;
        string name;
        // Constructor
        User(string n, string e, string ph_no, string add, int a, string uid){ // Constructor
            name = n; email = e; phone_number = ph_no;
            address = add; age = a; user_id = uid;
        }

        void show_details(){
            cout << "Personal details:" << '\n';
            cout << "Name: " << name;
            cout << "\nPhone Number: " << phone_number;
            cout << "\nUser ID: " << user_id;
            cout << "\nAge: " << age;
        }
        
};