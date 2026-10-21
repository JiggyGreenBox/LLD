/*
Problem Statement: Bank Account System

Design and implement a clean, object-oriented Bank Account System 
in-memory. The system should manage account details, handle secure 
deposits and withdrawals with proper validation, and maintain a log 
of recent transactions.



Functional Requirements

1. Account Initialization:
 - Each account must have a unique Account Number, an Owner Name, and 
   an initial Balance (which cannot be negative).


2. Deposit Operation:
 - Allow depositing money into the account (`deposit(amount)`).
 - The deposit amount must be strictly greater than 0; otherwise, reject it.


3. Withdrawal Operation:
 - Allow withdrawing money from the account (`withdraw(amount)`).
 - The withdrawal amount must be greater than 0 and cannot exceed the 
   current balance (no overdraft protection needed for this basic 
   version). Reject invalid or insufficient-fund withdrawals.


4. Transaction Logging:
 - Keep a history of transactions (e.g., records of deposits and 
   successful/failed withdrawals with amounts).
 - Provide a method to view the current balance and transaction history.
*/

/*
Account
    - account_num
    - name
    - balance
    - vector<Transactions>

    + withdraw
    + deposit
    + printTXs

Transactions
    - tx_id
    - type
    - balance_before
    - amount
    - balance_after
*/
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

enum class TXType{
    CREDIT,
    DEBIT
};

class Transactions{
    private:
        int tx_id;
        double balance_before;
        double amount;
        double balance_after;
        TXType type;

    public:
        Transactions(   
            int tx_id,
            double balance_before,
            double amount,
            double balance_after,
            TXType type):

            tx_id(tx_id),
            balance_before(balance_before) ,
            amount(amount) ,
            balance_after(balance_after) ,
            type(type) {}

        void print() {            
            string stype = (type == TXType::CREDIT) ? "CREDIT" : "DEBIT";

            cout << "type:"<< stype << " "
                 << "tx_id:"<< tx_id << " "
                 << "beforebal:"<< balance_before << " "
                 << "amount:"<< amount << " "
                 << "afterbal:"<< balance_after << endl;
        }
};

class Account {
    private:
        string account_num;
        string name;
        double balance;
        vector<Transactions> transactions;

    public:
    Account(
        string account_num,
        string name,
        double balance) : account_num(account_num), name(name), balance(balance) {
            // how do i add validation in a constructor?
            if(balance < 0)
                throw invalid_argument("balance cannot be negative");
        }

    bool deposit(double amount) {
        if(amount <= 0)
            return false;
        
        
        Transactions t(transactions.size(), balance, amount, balance + amount, TXType::CREDIT);
        transactions.push_back(t);

        balance += amount;

        return true;
    }

    bool withdraw(double amount) {
        if(amount <= 0)
            return false;

        if(balance < amount)
            return false;

        
        Transactions t(transactions.size(), balance, -amount, balance - amount, TXType::DEBIT);
        transactions.push_back(t);

        balance -= amount;

        return true;
    }

    void displayTXs() {
        for(Transactions &tx : transactions)
            tx.print();
    }

    double getBalance() const {
        return balance;
    }
};



int main() {

    Account acc1("ACC1", "Sourabh", 1000);
    // Account acc1("ACC1", "Sourabh", -1000);??

    acc1.deposit(100);
    acc1.withdraw(100000);
    acc1.withdraw(100);
    acc1.withdraw(900);
    acc1.displayTXs();
    
    cout << acc1.getBalance() << endl;

    return 0;
}