#include <bits/stdc++.h>
using namespace std;
#include "accounts.cpp"

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

class bank_system{
    public:
    // user ID -> A/C Number -> Card Number for savings
        vector<User*> customers; // can be used to determine number of users
        map<long long, savings_account*> savings_accounts_list;
        map<long long, current_account*> current_accounts_list;
        map<long long, loan_account*> loan_accounts_list;
        // map<long long, account_base*> accounts_list;
        map<string, vector<pair<long long, string>>> user_accounts; 
        map<string, User*> id_to_user;
        // user ID -> {A/C number and type}

        int customer_counter = 1;
        int account_counter = 1;
        
        
        // simple linear account_number_generator
        int generate_acc_number(){return account_counter++;}  
    
    // public:

        User* create_user(string name, string email, string phone_number, 
                        string address, int age){
            string user_id = get_user_id(name);
            if (id_to_user.find(user_id) != id_to_user.end()){
                int suf = 0;
                string s = (user_id) + "_" + to_string(suf);
                while(id_to_user.find(s) != id_to_user.end()){
                    suf++;
                    s = user_id + "_" + to_string(suf);
                }
                user_id = s;
            }

            User* user = new User(name, email, phone_number, address, age, user_id);
            customers.push_back(user);
            id_to_user[user_id] = user;
            return user;
        }

        void create_savings_account(int age, double initial_deposit, User* user, string date)
        {
            if (initial_deposit < 10000) cout << "Can't open Savings account, minimum deposit must be Rs. 10000\n";
            else{
                // string user_id = get_user_id(name);
                // User* user = new User(name, email, phone_number, address, age, user_id);
                // customers.push_back(user);
                int acc_number = generate_acc_number();
                string user_id = user->user_id;
                savings_account* sav_account = new savings_account(acc_number, initial_deposit, user, date);
                savings_accounts_list[acc_number] = (sav_account);
                user_accounts[user_id].push_back({acc_number, "Savings"});

                cout << "\nNew savings account created:\n";
                cout << "User ID: " << user_id << '\n';
                cout << "A/C number: " << acc_number << '\n';
                // sav_account->transactions.push_back({initial_deposit, date})
                // for(auto x : sav_account->transactions){
                //     cout << x.first << " " << x.second << '\n';
                // }
                sav_account->generate_atm_details();
            }
        }

        void create_current_account(int age, double initial_deposit, User* user, string date)
        {
            if (initial_deposit >= 100000 && age >= 18){

                int acc_number = generate_acc_number();
                string user_id = user->user_id;
                current_account* cur_account = new current_account(acc_number, initial_deposit, user, date);
                current_accounts_list[acc_number] = (cur_account);
                user_accounts[user_id].push_back({acc_number, "Current"});

                cout << "\nNew current account created:\n";
                cout << "User ID: " << user_id << '\n';
                cout << "A/C number: " << acc_number << '\n';
            }

            else cout << "Can't open Current account.\n";

        }

        void create_loan_account(int age, double loan_amt, int period, char loan_type, User* user, string date){
            
            // Have an existing current or savings acc
            // age 25, time in years >= 2, total value <= 40% of deposits
            // amount >= 500000
            string user_id = user->user_id;
            bool has_acc = (user_accounts.find(user_id) != user_accounts.end());
            if (loan_amt < 500000 || age < 25 || period < 2 || !(has_acc)){
            // if (age < 25 || period < 2 || !(has_acc)){
                // cout << has_acc << '\n';
                if (loan_amt < 500000) cout << "Loan amt must be >= 500000.\n";
                if (age < 25) cout << "Age must be >= 25.\n";
                if (period < 2) cout << "Loan period must be >= 2 years.\n";
                if (!has_acc) cout << "Open a savings or current account before taking a loan.\n";
                cout <<  "Can't start Loan account.\n";
                return;
            }
            double bal = 0;
            for(auto x : (user_accounts[user_id])){
                double amt = 0;
                long long ac_num = x.first;
            
                if (x.second == "Savings"){
                    auto ac = (savings_accounts_list[ac_num]);
                    string date1 = ac->transactions.back().second;
                    int diff = ac->get_months(date1, date);
                    ac->interest(diff);
                    amt += ac->balance;
                }
                else if (x.second == "Current"){
                    auto ac = (current_accounts_list[ac_num]);
                    amt += ac->balance;
                }

                bal += amt;
            }

            if (loan_amt > 0.4 * bal){
                cout <<  "Can't open Loan account.\n";
                return;
            }

            int acc_number = generate_acc_number();
            
            // loan_account(int acc_num, double amount, char loan_type, User* usr) 
            loan_account* loan_acc = new loan_account(acc_number, loan_amt, loan_type, user, date);
            loan_accounts_list[acc_number] = (loan_acc);    
            user_accounts[user_id].push_back({acc_number, "Loan"});  
            cout << "Created loan account with:\n Principal Amount: " << loan_amt << "\nPeriod: " << period << '\n';               
    }


        void printPassbook(long long acc_num){
            if (savings_accounts_list.find(acc_num) != savings_accounts_list.end())
                    ((savings_accounts_list[acc_num])->print_transactions());
            else if (current_accounts_list.find(acc_num) != current_accounts_list.end())
                    ((current_accounts_list[acc_num])->print_transactions());
            else if (loan_accounts_list.find(acc_num) != loan_accounts_list.end())
                    ((loan_accounts_list[acc_num])->print_transactions());
            else cout << "Account not found!" << endl;
        }
};