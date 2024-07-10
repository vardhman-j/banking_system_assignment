#include <bits/stdc++.h>
using namespace std;
#include "system.cpp"

int main(){
    bank_system bank;
    map_init();
    int choice;
    do {
        cout << "1. Create Savings Account\n2. Create Current Account\n3. Create Loan Account\n4. Display Passbook\n5. Existing User Menu\n6. Exit.\nEnter your choice: ";
        cin >> choice;

        string name, email, phone, address;
        int age;
        double amount;
        int accNum, custId;
        char loan_type;
        string user_id;
        string date;

        switch (choice) {
            case 1:
                cout << "Enter Name: "; cin >> name;
                cout << "Enter Email: "; cin >> email;
                cout << "Enter Phone: "; cin >> phone;
                cout << "Enter Address: "; cin >> address;
                cout << "Enter Age: "; cin >> age;
                cout << "Enter Initial Deposit: "; cin >> amount;
                cout << "Enter Date (Day/Month/Year): "; cin >> date;

                user_id = get_user_id(name);
                
                if (bank.user_accounts.find(user_id) != bank.user_accounts.end()){
                    int suf = 0;
                    string s = (user_id) + "_" + to_string(suf);
                    while(bank.user_accounts.find(s) != bank.user_accounts.end()){
                        suf++;
                        s = user_id + "_" + to_string(suf);
                    }
                    user_id = s;
                }
                bank.create_savings_account(name, email, phone, address, age, user_id, amount, date);
                break;

            case 2:
                cout << "Enter Name: "; cin >> name;
                cout << "Enter Email: "; cin >> email;
                cout << "Enter Phone: "; cin >> phone;
                cout << "Enter Address: "; cin >> address;
                cout << "Enter Age: "; cin >> age;
                cout << "Enter Initial Deposit: "; cin >> amount;
                cout << "Enter Date (Day/Month/Year): "; cin >> date;

                bank.create_current_account(name, email, phone, address, age, get_user_id(name), amount, date);
                break;

            case 3:
                cout << "Enter Name: "; cin >> name;
                cout << "Enter Email: "; cin >> email;
                cout << "Enter Phone: "; cin >> phone;
                cout << "Enter Address: "; cin >> address;
                cout << "Enter Age: "; cin >> age;
                cout << "Enter Loan Amount: "; cin >> amount;
                int period; cout << "Enter Loan Period (in years): "; cin >> period;
                cout << "Enter Loan Type (H, C, P, B): "; cin >> loan_type;
                cout << "Enter Date (Day/Month/Year): "; cin >> date;

                bank.create_loan_account(name, email, phone, address, age, get_user_id(name), amount, period, loan_type, date);
                break;

            case 4:
                cout << "Enter Account Number: "; cin >> accNum;
                bank.printPassbook(accNum);
                break;
            
            case 5:
                cout << "Existing User Menu.\n";
                int x;
                cout << "1. Display Account Details\n2. Deposit (Savings, Current and Loan) \n3. Withdraw (Savings and Current)\n4. Display User Accounts\n5. Account statement.\n6. Exit\nEnter your choice: ";
                cin >> x;
                long long acc_number;
                double amount;
                
                // based on account number input.
                if (x == 1){
                    cout << "Enter Account number: ";
                    cin >> acc_number;
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
                    else{
                        auto x = (bank.loan_accounts_list)[acc_number];
                        // account_base ptr = new account_base();
                        x->show_acc_det();
                    }
                }

                else if (x == 2){
                    cout << "Enter Account number: ";
                    cin >> acc_number;
                    cout << "Enter Amount to deposit: ";
                    cin >> amount;
                    cout << "Enter Date: ";
                    cin >> date;
                    
                    cout << "Deposited amount " << amount << " in A/C number " << acc_number << "\nUpdated ";
                    if (bank.savings_accounts_list.find(acc_number) != bank.savings_accounts_list.end()){
                        auto x = (bank.savings_accounts_list)[acc_number];
                        // account_base ptr = new account_base();
                        x->deposit(amount, date);
                        x->show_acc_det();
                    }
                    else if (bank.current_accounts_list.find(acc_number) != bank.current_accounts_list.end()){
                        auto x = (bank.current_accounts_list)[acc_number];
                        // account_base ptr = new account_base();
                        x->deposit(amount, date);
                        x->show_acc_det();
                    }
                    else{
                        auto x = (bank.loan_accounts_list)[acc_number];
                        // account_base ptr = new account_base();
                        x->deposit(amount, date);
                        x->show_acc_det();
                    }
                    ///////////////////

                }
                else if (x == 3){
                    cout << "Enter Account number: ";
                    cin >> acc_number;
                    cout << "Enter Amount to deposit: ";
                    cin >> amount;
                    cout << "Enter Date: ";
                    cin >> date;

                    cout << "Withdrew amount " << amount << " from A/C number " << acc_number << "\nUpdated ";
                    if (bank.savings_accounts_list.find(acc_number) != bank.savings_accounts_list.end()){
                        auto x = (bank.savings_accounts_list)[acc_number];
                        // account_base ptr = new account_base();
                        x->withdraw(amount, date);
                        x->show_acc_det();
                    }
                    else{
                        auto x = (bank.current_accounts_list)[acc_number];
                        // account_base ptr = new account_base();
                        x->withdraw(amount, date);
                        x->show_acc_det();
                    }
                }
                else if (x == 4){
                    cout << "Enter User ID: ";
                    cin >> user_id;
                    cout << "Accounts linked to User ID " << user_id << ":\n";
                    cout << "A/C number       Type\n";
                    for(auto x : bank.user_accounts[user_id]){
                        cout << x.first << " " << x.second << '\n';
                    }
                    // bank.printPassbook(user_id);
                }
                else if (x == 5){
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
                else if (x == 6){
                    cout << "Going back to main menu.\n";
                }
                else{
                    cout << "Invalid choice!" << endl;
                }
                break;

            case 6:
                cout << "Exiting\n.";
                break;

            default:
                cout << "Invalid choice!. Exiting existing user menu.\n";
                break;

        }

    } while (choice != 6);

    return 0;
}