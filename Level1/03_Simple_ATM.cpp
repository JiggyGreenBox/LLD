/*
Problem 03: Simple ATM
SDE1 · Beginner

Problem statement

Design and implement a simplified ATM system in C++ that allows a 
user to check their account balance, deposit money, and withdraw 
money.
The system should maintain an account's balance and record 
transactions. 
Invalid operations must be rejected without incorrectly 
changing the balance.

Requirements
1. Account: Each account has a unique account ID, account holder's 
name, and current balance.
2. Check balance: Return the current account balance.
3. Deposit: Deposit a positive amount into an account.
4. Withdraw: Withdraw a positive amount if sufficient funds are 
available.
5. Transaction history: Record successful deposits and withdrawals, 
including the amount and resulting balance.
6. ATM: Provide operations through which a user interacts with an 
account.
7. Validation: Reject zero or negative amounts, withdrawals exceeding 
the balance, and operations on nonexistent accounts.
8. Multiple accounts: The ATM can manage multiple accounts, each with 
an independent balance.
9. Consistency: A failed transaction must not modify the account 
balance or be recorded as a successful transaction.

*/


/*
Account
    ID
    name
    balance
    transactions

    showTransactions()
    deposit()
    withdraw()

Transaction
    status success
    type credit debit
    amount
    balance before
    balance after

ATM
    accounts <ID, account>

    addAccount(account)

    showTransactions(account_id)

*/

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include <optional>
using namespace std;

enum class TransactionType {
    CREDIT,
    DEBIT
};

class Transaction {
    private:
        string tx_id;
        int amount;
        TransactionType type;
        int balance_before;
        int balance_after;
        bool success;
    public:
        Transaction(
            string tx_id,
            int amount,
            TransactionType type,
            int balance_before,
            int balance_after,
            bool success        
        ) : 
            tx_id(tx_id),
            amount(amount),
            type(type),
            balance_before(balance_before),
            balance_after(balance_after),
            success(success) {}

        void print() const {
            string txtype = (type == TransactionType::CREDIT)? "CREDIT" : "DEBIT";
            cout << " tx_id: "<< tx_id
                 << " amount: "<< amount
                 << " type: "<< txtype
                 << " balance_before: "<< balance_before
                 << " balance_after: "<< balance_after 
                 << " success: "<< success << endl;
        }

};

class Account {
    private:
        string account_id;
        string name;
        vector<Transaction> transactions;
        int balance;

    public:
        Account(
            string id,
            string name,
            int balance = 0
        ) : account_id(id), name(name), balance(balance) {
            if(balance < 0)
                throw invalid_argument("balance cannot be negative");
        }

        void printTransactions() const {
            for(auto &tx : transactions) {
                tx.print();
            }
        }

        string id() const {
            return account_id;
        }

        bool deposit(string acc_id, int amount) {
            if(amount <= 0)
                return false;


            string tx_id = acc_id + ":" + to_string(transactions.size());
            Transaction t(
                tx_id,
                amount,
                TransactionType::CREDIT,
                balance,
                balance + amount,
                true);
            
            balance += amount;

            transactions.push_back(t);
            return true;
        }
        bool withdraw(string acc_id, int amount) {

            if(amount > balance)
                return false;

            string tx_id = acc_id + ":" + to_string(transactions.size());
            Transaction t(
                tx_id,
                amount,
                TransactionType::DEBIT,
                balance,
                balance - amount,
                true);

            balance -= amount;
            
            transactions.push_back(t);
            return true;
        }

        int getBalance() const {
            return balance;
        }
};

class ATM {
    private:
        unordered_map<string, Account> accounts;
    public:

        bool addAccount(Account acc) {
            string acc_id = acc.id();

            auto it = accounts.find(acc_id);

            if(it != accounts.end()) 
                return false;

            accounts.emplace(acc_id, acc);
            return true;
        }

        optional<int> showBalance(string acc_id) {
            auto it = accounts.find(acc_id);
            if(it == accounts.end())
                return nullopt; // missing account

            return it->second.getBalance();
        }

        bool showTransactions(string acc_id) {
            auto it = accounts.find(acc_id);
            if(it == accounts.end())
                return false; // missing account

            it->second.printTransactions();
            return true;
        }

        bool deposit(string acc_id, int amount) {
            auto it = accounts.find(acc_id);
            if(it == accounts.end())
                return false; // missing account

            return it->second.deposit(acc_id, amount);
        }

        bool withdraw(string acc_id, int amount) {
            auto it = accounts.find(acc_id);
            if(it == accounts.end())
                return false; // missing account

            return it->second.withdraw(acc_id, amount);
        }
};

int main() {

    ATM atm;

    Account acc1("ACC1","sourabh", 1000);
    atm.addAccount(acc1);
    Account acc2("ACC2","jiggy", 2000);
    atm.addAccount(acc2);

    atm.deposit("ACC1", 100);
    atm.withdraw("ACC1", 900);
    auto bal = atm.showBalance("ACC1");
    if(bal.has_value())
        cout << bal.value() << endl;


    auto b1 =  atm.showBalance("ACC1");
    if(b1.has_value())
        cout << b1.value() << endl;

    atm.showTransactions("ACC1");

    auto b2 =  atm.showBalance("ACC2");
    if(b2.has_value())
        cout << b2.value() << endl;

    atm.withdraw("ACC2", 2000);
    atm.showTransactions("ACC2");

    b2 =  atm.showBalance("ACC2");
    if(b2.has_value())
        cout << b2.value() << endl;

    return 0;
}