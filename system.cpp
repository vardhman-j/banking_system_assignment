#include <bits/stdc++.h>
using namespace std;
#include "accounts.cpp"

class bank_system{
    public:
    // user ID -> A/C Number -> Card Number for savings
        vector<User*> customers;
        map<long long, savings_account*> savings_accounts_list;
        map<long long, current_account*> current_accounts_list;
        map<long long, loan_account*> loan_accounts_list;
        map<string, vector<pair<long long, string>>> user_accounts;
        // user ID -> {A/C number and type}

        int customer_counter = 1;
        int account_counter = 1;
        
        
        // simple linear account_number_generator
        int generate_acc_number(){return account_counter++;}  
    
    // public:

        void create_savings_account(string name, string email, string phone_number, string address,
                                    int age, string user_id, double initial_deposit, string date)
        {
            if (initial_deposit < 10000) cout << "Can't open Savings account, minimum deposit must be Rs. 10000\n";
            else{
                string user_id = get_user_id(name);
                User* user = new User(name, email, phone_number, address, age, user_id);
                customers.push_back(user);
                int acc_number = generate_acc_number();

                savings_account* sav_account = new savings_account(acc_number, initial_deposit, user, date);
                savings_accounts_list[acc_number] = (sav_account);
                user_accounts[user_id].push_back({acc_number, "Savings"});

                cout << "\nNew savings account created:\n";
                cout << "User ID: " << user_id << '\n';
                cout << "A/C number: " << acc_number << '\n';

                sav_account->generate_atm_details();
            }
        }

        void create_current_account(string name, string email, string phone_number, string address,
                                    int age, string user_id, double initial_deposit, string date)
        {
            if (initial_deposit >= 100000 && age >= 18){
                string user_id = get_user_id(name);
                User* user = new User(name, email, phone_number, address, age, user_id);
                customers.push_back(user);

                int acc_number = generate_acc_number();

                current_account* cur_account = new current_account(acc_number, initial_deposit, user, date);
                current_accounts_list[acc_number] = (cur_account);
                user_accounts[user_id].push_back({acc_number, "Current"});
            }

            else cout << "Can't open Current account.\n";

        }

        void create_loan_account(string name, string email, string phone_number, string address,
                                    int age, string user_id, double loan_amt, int period, 
                                    char loan_type, string date){
            
            // Have an existing current or savings acc
            // age 25, time in years >= 2, total value <= 40% of deposits
            // amount >= 500000
            // long long user_id = get_user_id(name);
            bool has_acc = (user_accounts.find(user_id) != user_accounts.end());

            if (loan_amt < 500000 || age < 25 || period < 2 || !(has_acc)){
                cout << has_acc << '\n';
                cout <<  "Can't open Loan account.\n";
                return;
            }
            User* user = new User(name, email, phone_number, address, age, user_id);
            double bal = 0;
            for(auto x : (user_accounts[user_id])){
                double amt = 
                bal += amt;
            }

            if (loan_amt > 0.4 * bal){
                cout <<  "Can't open Loan account.\n";
                return;
            }
            
            customers.push_back(user);

            int acc_number = generate_acc_number();

            // loan_account(int acc_num, double amount, char loan_type, User* usr) 
            loan_account* loan_acc = new loan_account(acc_number, loan_amt, loan_type, user, date);
            loan_accounts_list[acc_number] = (loan_acc);    
            user_accounts[user_id].push_back({acc_number, "Loan"});                 
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