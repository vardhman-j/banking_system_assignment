#include <bits/stdc++.h>
using namespace std;
#include "system.cpp"

int valid_date(int d, int m, int y){
    // 0 pe invalid date
    // -1 pe future date
    // 1 is alr
    
    if (d < 0 || m < 0 || d > 31 || m > 12) return 0;
    vector<string> cur_dmy = date_split(cur_date());
    vector<int> t0 = {4, 6, 9, 11};

    if (m == 2){
        if (d > 29) return 0;
        if (y%4 && d > 28) return 0;
    }
    int fl = 0;
    for(int x : t0){
        if (m == x){
            fl = 1;
            break;
        }
    }
    if (fl && d > 30) return 0;
    
    // checking if future date
    int cd = stoi(cur_dmy[0]), cm = stoi(cur_dmy[1]), cy = stoi(cur_dmy[2]);

    if (y > cy) return -1;
    if (y < cy) return 1;

    if (m > cm) return -1;
    if (m < cm) return 1;
        
    if (d > cd) return -1;
    return 1;
}

bool check_input(string name, string email, string ph_number, string  address, int age, string date){
    int ph_f = 1, em_f = 1, age_f = 1, name_f = 1, add_f = 1, date_f;
    age_f = (age >= 0);
    
    
    vector<string> dmy = date_split(date);
    
    int d = stoi(dmy[0]), m = stoi(dmy[1]), y = stoi(dmy[2]);
    date_f = valid_date(d, m, y);
    
    if (name.size() == 0) name_f = 0;
    if (address.size() == 0) add_f = 0;

    if (ph_number.size() != 10) ph_f = 0;
    for(char c : ph_number){
        if (c < '0' || c > '9'){
            ph_f = 0;
            break;
        }
    }

    int n = email.size();
    if (n < 7) em_f = 0;
    else{
        int end_f = 1, j;
        string end_sub = ".com";
        for(int i = n-4; i<n; i++){
            int j = i - (n-4);
            if (email[i] != end_sub[j]){
                end_f = 0;
                break;
            }
        }

        int at_f = 0;
        for(char c : email){
            if (c == '@'){
                at_f = 1;
                break;
            }
        }
        if (!at_f || !end_f) em_f = 0;
    }
    if (ph_f && em_f && age_f && name_f && add_f && date_f) return 1;
    if (!name_f) cout << "Enter non empty name.\n";
    if (!em_f) cout << "Invalid email.\n";
    if(!ph_f) cout << "Invalid Phone Number.\n";
    if (!add_f) cout << "Invalid non empty address.\n";
    if(!age_f) cout << "Invalid age.\n";
    if (date_f == -1) cout << "Enter a past date.\n";
    else if (date_f == 0) cout << "Enter a valid date.\n";
    return 0;
}

int main(){
    bank_system bank;
    map_init();
    int choice, acc_type;
    string user_id, date;
    cout << "\nWelcome!\nEnter your choice below:";
    do {
        cout << "\n1. New User\n2. Existing User\n3. View Bank Stats\n4. Exit\n\nEnter your choice below: "; cin >> choice; cout << '\n';
        if (choice == 1){
            bool ch;
            string name, email, phone, address; int age;
            do{
                cout << "Enter Personal details:\n";
                cout << "Enter Name: "; cin >> name;
                cout << "Enter Email: "; cin >> email;
                cout << "Enter Phone: "; cin >> phone;
                cout << "Enter Address: "; cin >> address;
                cout << "Enter Age: "; cin >> age;
                cout << "Enter Date (Day/Month/Year): "; cin >> date;

                ch = check_input(name, email, phone, address, age, date);
                if (!ch) cout << "\nEnter proper details. Exiting..";
            }
            while(!ch);

            User* new_user = bank.create_user(name, email, phone, address, age);
            user_id = new_user->user_id;
            cout << "\nNew User ID created, User_ID: " << user_id << "\n";

            cout << "\n1. Create Savings Account\n2. Create Current Account\n3. Create Loan Account\n4. Exit\n\nEnter choice: ";
            cin >> acc_type; cout << '\n';
            switch(acc_type){
                double amount;
                int accNum;
                char loan_type;
                case(1):
                    cout << "\nEnter Initial Deposit: "; cin >> amount; cout << '\n';
                    bank.create_savings_account(name, email, phone, address, age, amount, new_user, date);
                    break;
                case(2):
                    cout << "\nEnter Initial Deposit: "; cin >> amount; cout << '\n';
                    bank.create_current_account(name, email, phone, address, age, amount, new_user, date);
                    break;
                case(3):
                    cout << "Enter Loan Amount: "; cin >> amount;
                    int period; cout << "Enter Loan Period (in years): "; cin >> period;
                    cout << "Enter Loan Type (H, C, P, B): "; cin >> loan_type;
                    bank.create_loan_account(name, email, phone, address, age, amount, period, loan_type, new_user, date);
                    break;
                case(4):
                    cout << "User ID created, no account linked to it exists.\nNote User ID for future use.\n";
                    break;
                default:
                    cout << "Invalid Choice.";
                    break;
            }
            
        }

        else if (choice == 2){
            int ex_choice;
            string user_id;
            long long acc_number;
            cout << "1. Display User Details\n2. Display Account Details\n3. Display Account Statement\n4. Deposit (Savings, Current and Loan) \n5. Withdraw (Savings and Current)\n6. Existing user new A/C creation.\n7. Exit\nEnter your choice: "; cin >> ex_choice; cout << '\n';
            double amount;
            switch(ex_choice){
                
                case(1):
                    cout << "Enter User ID: "; cin >> user_id;
                    if (bank.id_to_user.find(user_id) == bank.id_to_user.end())
                        cout << "\nUser ID not found.";
                    else{
                        cout << "Personal details of User ID: " << user_id << "\n";
                        bank.id_to_user[user_id]->show_details();
                        cout << "Accounts linked to User ID " << user_id << ":\n";
                        cout << "A/C number       Type\n";
                        for(auto x : bank.user_accounts[user_id]){
                            cout << x.first << " " << x.second << '\n';
                        }
                    }
                    break;
                case(2):
                    cout << "Enter A/C Number: "; cin >> acc_number;
                    if (bank.savings_accounts_list.find(acc_number) != bank.savings_accounts_list.end()){
                        auto x = (bank.savings_accounts_list)[acc_number];
                        // account_base ptr = new account_base();
                        x->show_acc_det();
                    }
                    else if (bank.current_accounts_list.find(acc_number) != bank.current_accounts_list.end()){
                        auto x = (bank.current_accounts_list)[acc_number];
                        // account_base ptr = new account_base();
                        x->show_acc_det();
                    }
                    else if (bank.loan_accounts_list.find(acc_number) != bank.loan_accounts_list.end()){
                        auto x = (bank.loan_accounts_list)[acc_number];
                        // account_base ptr = new account_base();
                        x->show_acc_det();
                    }
                    else cout << "\nUser ID not found.";
                    break;
                
                case (3):
                    cout << "Enter A/C Number: "; cin >> acc_number;
                    cout << '\n';
                    if (bank.savings_accounts_list.find(acc_number) != bank.savings_accounts_list.end()){
                        auto x = (bank.savings_accounts_list)[acc_number];
                        // account_base ptr = new account_base();
                        x->print_transactions();
                    }
                    else if (bank.current_accounts_list.find(acc_number) != bank.current_accounts_list.end()){
                        auto x = (bank.current_accounts_list)[acc_number];
                        // account_base ptr = new account_base();
                        // x->deposit(amount, date);
                        x->print_transactions();
                    }
                    else if (bank.loan_accounts_list.find(acc_number) != bank.loan_accounts_list.end()){
                        auto x = (bank.loan_accounts_list)[acc_number];
                        // account_base ptr = new account_base();
                        // x->deposit(amount, date);
                        x->print_transactions();
                    }
                    else cout << "\nAccount number not found.\n"; 
                    break;
                case(4):
                    cout << "Enter A/C Number: "; cin >> acc_number;
                    cout << "Enter Amount to deposit: "; cin >> amount;
                    cout << "Enter Date: "; cin >> date;
                    if (bank.savings_accounts_list.find(acc_number) != bank.savings_accounts_list.end()){
                        auto x = (bank.savings_accounts_list)[acc_number];
                        x->deposit(amount, date);
                        x->show_acc_det();
                    }
                    else if (bank.current_accounts_list.find(acc_number) != bank.current_accounts_list.end()){
                        auto x = (bank.current_accounts_list)[acc_number];
                        x->deposit(amount, date);
                        x->show_acc_det();
                    }
                    else if (bank.loan_accounts_list.find(acc_number) != bank.loan_accounts_list.end()){
                        auto x = (bank.loan_accounts_list)[acc_number];
                        x->deposit(amount, date);
                        x->show_acc_det();
                    }
                    else cout << "\nAccount number not found.\n";

                    break;
                case(5):
                    cout << "Enter A/C Number: "; cin >> acc_number;
                    cout << "Enter Amount to withdraw: "; cin >> amount;
                    cout << "Enter Date: "; cin >> date;
                    int cur_bal;

                    if (bank.savings_accounts_list.find(acc_number) != bank.savings_accounts_list.end()){
                        auto x = (bank.savings_accounts_list)[acc_number];
                        cur_bal = x->balance;
                        x->withdraw(amount, date);
                        if (cur_bal != x->balance) cout << "Withdrew amount " << amount << " from A/C number " << acc_number << "\n";
                        x->show_acc_det();
                    }
                    else if (bank.current_accounts_list.find(acc_number) != bank.current_accounts_list.end()){
                        auto x = (bank.current_accounts_list)[acc_number];
                        cur_bal = x->balance;
                        x->withdraw(amount, date);
                        if (cur_bal != x->balance) cout << "Withdrew amount " << amount << " from A/C number " << acc_number << "\n";
                        x->show_acc_det();
                    }
                    else cout << "\nAccount number not found.\n";
                    break;
                case(6):
                    cout << "Enter User ID: "; cin >> user_id;
                    if (bank.id_to_user.find(user_id) == bank.id_to_user.end())
                        cout << "\nUser ID not found.";
                    else{
                    cout << "\n1. Create Savings Account\n2. Create Current Account\n3. Create Loan Account\n4. Exit\n\nEnter choice: ";
                    cin >> acc_type;
                    User* user = bank.id_to_user[user_id];
                    double amount;
                    int accNum;
                    char loan_type;
                    string n, e, p, a; int ag;
                    n = user->get_details(user)[0]; e = user->get_details(user)[1]; p = user->get_details(user)[2]; a = user->get_details(user)[3]; ag = user->age;
                    
                    if (acc_type == 1){
                        cout << "\nEnter Initial Deposit: "; cin >> amount;
                        cout << "Enter Date: "; cin >> date;
                        // if ()
                        bank.create_savings_account(n, e, p, a, ag, amount, user, date);
                    }
                    else if (acc_type == 2){
                        cout << "\nEnter Initial Deposit: "; cin >> amount; cout << '\n';
                        cout << "Enter Date: "; cin >> date;
                        bank.create_current_account(n, e, p, a, ag, amount, user, date);
                    }
                    else if (acc_type == 3){
                        cout << "Enter Loan Amount: "; cin >> amount;
                        cout << "Enter Date: "; cin >> date;
                        int period; cout << "Enter Loan Period (in years): "; cin >> period;
                        cout << "Enter Loan Type (H, C, P, B): "; cin >> loan_type;
                        bank.create_loan_account(n, e, p, a, ag, amount, period, loan_type, user, date);
                    }
                    else cout << "Invalid Choice, exiting.";
                }

                    break;
                case(7):
                    cout << "Exiting existing user menu..\n";
                    break;

                default:
                    cout << "Invalid Choice, exiting existing user menu..";
                    break;
            }

        }
        else if (choice == 3){
            cout << "\nTotal number of Users: " << bank.id_to_user.size() << '\n';
            int a = bank.savings_accounts_list.size(), b = bank.current_accounts_list.size(), c = bank.loan_accounts_list.size();
            cout << "Total number of Accounts: " << a + b + c << '\n';
            cout << "Savings accounts: " << a << '\n';
            cout << "Current accounts: " << b << '\n';
            cout << "Loan accounts: " << c << '\n';
        }
        else if (choice == 4){
            cout << "\nExiting..\n";
            break;
        }
        else{
            cout << "------------\n\n";
            cout << "Invalid choice\nRe-enter: ";
        }
        /*
        if (4 == 5){
            cout << "Enter A/C number: ";
            cin >> acc_number;
            cout << '\n';
            if (bank.savings_accounts_list.find(acc_number) != bank.savings_accounts_list.end()){
                auto x = (bank.savings_accounts_list)[acc_number];
                // account_base ptr = new account_base();
                x->print_transactions();
            }
            else if (bank.current_accounts_list.find(acc_number) != bank.current_accounts_list.end()){
                auto x = (bank.current_accounts_list)[acc_number];
                // account_base ptr = new account_base();
                x->deposit(amount, date);
                x->print_transactions();
            }
            else{
                auto x = (bank.loan_accounts_list)[acc_number];
                // account_base ptr = new account_base();
                x->deposit(amount, date);
                x->print_transactions();
            }
        }
        */
    
    } 
    while (choice != 4);
    cout << "Thank you, you are now logged out.";
    return 0;
}