#include <bits/stdc++.h>
using namespace std;

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
    public:
        int age;
        string user_id;
        string name;

        
        // Constructor
        User(string n, string e, string ph_no, string add, int a, string uid){ // Constructor
            name = n; email = e; phone_number = ph_no;
            address = add; age = a; user_id = uid;
            
        }

        vector<string> get_details(User* u){
            return {u->name, u->email, u->phone_number, u->address};
        }
        void show_details(){
            cout << "Personal details:\n";
            cout << "Name: " << name;
            cout << "\nEmail: " << email;
            cout << "\nPhone Number: " << phone_number;
            cout << "\nUser ID: " << user_id;
            cout << "\nAge: " << age << '\n';
        }
        
};