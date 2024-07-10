#include <bits/stdc++.h>
using namespace std;
#include "customer.cpp"

class account_base{
    // protected:
    public:
        int acc_number;
        double balance;
        string account_type;
        vector<vector<string>> transactions;
        // transactions store withdrawal/deposit, amount, date and acc_type
        User* user;

        // virtual void interest(int months) = 0;
        // virtual void display() = 0;

        account_base(string acc_type, int acc_num, double bal, User* usr){
            acc_number = acc_num;
            account_type = acc_type;
            balance = bal;
            user = usr;
        }

        void show_acc_det(){
            cout << "Account details: \n";
            cout << "A/C number: " << acc_number;
            cout << "\nBalance: " << balance << '\n';
        }

        int get_acc_number(){ return acc_number;}
        int get_balance(){ return balance;}
        
        // virtual void deposit(int amount, string date) = 0;
        // virtual void withdraw(int amount, string date) = 0;

        void addTransaction(vector<string> transaction){
            transactions.push_back(transaction);
        }
        
        void print_transactions(){  // Printing Statement
            cout << "Transaction history for A/C number " << acc_number << ":\n";
            for (auto x : transactions){
                if (x[0] == "+") cout << "Deposited ";
                else cout << "Withdrew ";
                cout << x[1] << " on " << x[2];

                if (x[2] == "+") cout << "in ";
                else cout << "from ";

                cout << x[3];
            }
        }

        int get_months(string date1, string date2){
            vector<string> date_1 = date_split(date1);
            vector<string> date_2 = date_split(date2);

            string m1 = date_1[1], m2 = date_2[1], y1 = date_1[2],  y2 = date_2[2];
            vector<string> dates = {m1, m2, y1, y2};
            vector<int> num_d(4, 0);
            for(int x : num_d) cout << x << " ";
            int ans = 0;
            if (num_d[3] == num_d[2]) ans = num_d[1] - num_d[0];
            else{
                ans = (num_d[1] - num_d[0]) + (num_d[3] - num_d[2])*12;
            }
            // cout << ans << " ";
            return ans;                    
        }

        // User* get_user() const { return user;}
};

class savings_account : public account_base{
    private:
        
        const double interest_rate = 0.06;
        const double min_balance = 10000;
        double NRV = 100000;
        double daily_withdrawal_value = 0;
        int monthly_withdrawal_cnt = 0;
        map<long long, string> savings_atm;
        map<string, int> unique_atm_numbers;
        // 2 mappings exist because, savings_atm is acc number to atm_card_number
        // atm_numbers is just to check uniqueness.

    protected:

        string atm_card_number = "";
        int atm_card_cvv = 0;
        string atm_card_expiry = "";

        vector<string> prev_date = {"00", "00", "0000"};


    public:

        savings_account(int acc_num, double bal, User* usr, string date) : account_base("Savings", acc_num, bal, usr){
            unique_atm_numbers[""] = 0;
            transactions.push_back({"+", to_string(bal), date, "Savings"});
        }
        
        void interest(int months){
            balance += balance * (months * interest_rate / 12);
        }
        
        
        void deposit(int amount, string date){
            if (transactions.size()){
                int diff = get_months(transactions.back()[1], date);
                interest(diff);
            }
            balance += amount;
            transactions.push_back({"+", to_string(amount), date, "Savings"});
        }


        void withdraw(int amount, string date){
            if (transactions.size()){
                int diff = get_months(transactions.back()[1], date);
                interest(diff);
            }

            if (amount >= 20000 || amount >= balance){
                cout << "Transaction rejected, check withdrawal amount and balance.";
            }
            else{
                vector<string> current_date = date_split(date); //get date, month, year

                if (current_date[1] == prev_date[1] && current_date[2] == prev_date[2]){  // same month
                    if (current_date[0] == prev_date[0]){ // same day
                        if (daily_withdrawal_value == 50000) cout << "Transaction rejected, daily withdrawal amount limit reached.";
                        else if (amount + daily_withdrawal_value >= 50000){
                            double difference = 50000 - daily_withdrawal_value;
                            balance -= difference;
                            cout << "Withdrew only the difference.";
                            daily_withdrawal_value = 50000;
                            monthly_withdrawal_cnt++;
                            transactions.push_back({"-", to_string(difference), date, "Savings"});
                        }
                        else {    //can withdraw, no limitation on daily limit.
                            balance -= amount;
                            daily_withdrawal_value += amount;
                            monthly_withdrawal_cnt++;
                            transactions.push_back({"-", to_string(amount), date, "Savings"});
                        }
                    }

                    else{
                        daily_withdrawal_value = 0;
                        if (monthly_withdrawal_cnt == 5){
                            cout << "Penalty of Rs.500, Monthly transaction limit reached.";
                            balance -= 500;
                        }
                        else monthly_withdrawal_cnt++;

                        balance -= amount;
                        transactions.push_back({"-", to_string(amount), date, "Savings"});
                    }
                }
                else{
                    monthly_withdrawal_cnt = 0;
                    balance -= amount;
                    transactions.push_back({"-", to_string(amount), date, "Savings"});
                }

                prev_date = current_date;
            }
        }

        void generate_atm_details(){      // generateds and prints the ATM details.
            string x = "";

            while(unique_atm_numbers.find(x) != unique_atm_numbers.end()){
                x = "";
                for(int i = 0; i<16; i++){
                    int rnd = (rand()%10);
                    x += ('0' + rnd);
                }
            }
            atm_card_number = x;

            for(int i = 0; i<3; i++){
                int rnd = (rand() % 10) + 1;
                atm_card_cvv += ('0' + rnd);
            }

            string m; string y;
            m = to_string(1 + ((rand()%12)));
            y = to_string(2030 + rand()%5);

            if (m.size() == 1) m = ("0" + m);
            
            atm_card_expiry = m + '/' + y;

            cout << "\nATM Card details:\n" << "Card number: " << atm_card_number << '\n';
            cout << "Card CVV: " << atm_card_cvv << "\nCard Expiry: " << atm_card_expiry << '\n';
            savings_atm[acc_number] = atm_card_number;
        }

};

class current_account : public account_base {
    private:
        const int min_balance = 100000;
        const int min_age = 18;
        double NRV = 500000;
        int monthly_transaction_cnt = 0;
        vector<string> prev_date = {"00", "00", "0000"};
    
    public:
        current_account(int acc_num, double bal, User* usr, string date) : account_base("Current", acc_num, bal, usr){
            transactions.push_back({"+", to_string(bal), date, "Current"});
        }

        void display()  {
            cout << "Current account number: " << acc_number;
            cout << "\nCurrent Account Balance: " << balance << '\n';
        }
        // void interest(int months) override{}
        
        void deposit(int amount, string date) {
            balance += (amount);
            balance -= min(500.0, 0.005*amount);
            string month = date_split(date)[1];
            if (transactions.size()){
                if (date_split((transactions.back()[2]))[1] == month){
                    monthly_transaction_cnt++;
                }
                else{
                    string prev_month = date_split((transactions.back()[2]))[1];
                    if (monthly_transaction_cnt >= 3){
                        monthly_transaction_cnt = 1;
                    }
                    else balance -= 500;
                }
            }
            
            else monthly_transaction_cnt = 1;
            transactions.push_back({"+", to_string(amount), date, "Current"});
        }
            

        void withdraw(int amount, string date) {
            if (amount >= balance) cout << "Transaction rejected, check withdrawal amount and balance.";

            else{
                balance -= (amount);
                balance -= min(500.0, 0.005*amount);
                transactions.push_back({"-", to_string(amount), date, "Current"});
            }
        }
};

class loan_account : public account_base {

    private:
        double interest_rate;
        double base_loan_amount, rem_loan_amt;

    public:
        // account_base(string acc_type, int acc_num, double bal, User* usr)
        loan_account(int acc_num, double amount, char loan_type, User* usr, string date) 
            : account_base("Loan", acc_num, amount, usr){
                
                if (loan_type == 'H')
                    interest_rate = 0.07;
                else if (loan_type == 'C')
                    interest_rate = 0.08;
                else if (loan_type == 'P')
                    interest_rate = 0.12;
                else interest_rate = 0.15;
                
                transactions.push_back({"-", to_string(amount), date, "Loan"});
                base_loan_amount = amount;
                rem_loan_amt = base_loan_amount;
        }


        
        /*
        ADD FUNCTIONALITY OF ENSURING LOAN ACCOUNT OPENS IFF
        SAVINGS OR CURRENT ACCOUNT EXISTS
        */

        void interest(int months) {
            rem_loan_amt += rem_loan_amt * pow((1 + interest_rate/2), 2); // compounded half yearly
        }

        void display() {
            cout << "Loan Account Number: " << acc_number;
            cout << "\nLoan Amount: " << rem_loan_amt;
            cout << "\nInterest Rate: " << interest_rate << "%\n";
            cout << "User ID: " << get_user_id(user->name) << endl;
        }

        void deposit(int installment, string date) {
            if (transactions.size()){
                int diff = get_months(transactions.back()[1], date);
                interest(diff/6);
            }
            if (installment > (0.1 * base_loan_amount)){
                cout << "Installment must be atmost 10% of Base loan amount.\n";
                return;
            } 
            rem_loan_amt -= installment;
            transactions.push_back({"+", to_string(installment), date, "Loan"});

            if (installment >= rem_loan_amt){
                rem_loan_amt = 0;
                cout << "Loan has been repaid.\n";
            }

        }
        
        // void withdraw(int amount, string date) override{}
};