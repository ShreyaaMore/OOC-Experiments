#include <iostream>
#include <string>

using namespace std;

class SavingAccount
{
private:
    string accountHolderName;
    int accountNumber;
    double balance;
    double interestRate;

public:
    SavingAccount(string name, int accNumber, double initialBalance, double rate)
    {
        accountHolderName = name;
        accountNumber = accNumber;
        balance = initialBalance;
        interestRate = rate;
    }

    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            cout << "Deposited: Rs." << amount << endl;
        }
    }

    void withdraw(double amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            cout << "Withdrawn: Rs." << amount << endl;
        }
        else
        {
            cout << "Insufficient balance or invalid amount!" << endl;
        }
    }

    void applyInterest()
    {
        double interest = balance * interestRate / 100;
        balance += interest;
        cout << "Interest Applied: Rs." << interest << endl;
    }

    void display() const
    {
        cout << "\n[Savings Account Statement]" << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: Rs." << balance << endl;
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }
};

class CheckingAccount
{
private:
    string accountHolderName;
    int accountNumber;
    double balance;
    double transactionFee;

public:
    CheckingAccount(string name, int accNumber, double initialBalance, double fee)
    {
        accountHolderName = name;
        accountNumber = accNumber;
        balance = initialBalance;
        transactionFee = fee;
    }

    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            cout << endl << "Deposited: Rs." << amount << endl;
        }
    }

    void withdraw(double amount)
    {
        double total = amount + transactionFee;
        if (amount <= 0)
        {
            cout << "Invalid withdrawal amount!" << endl;
        }
        else if (total <= balance)
        {
            balance -= total;
            cout << endl << "Withdrawn: Rs." << amount << " (Rs." << transactionFee << " fee applied)" << endl;
        }
        else
        {
            cout << "Insufficient balance for withdrawal + fee! (Need Rs." << total << ")" << endl;
        }
    }

    void display() const
    {
        cout << "\n[Checking Account Statement]" << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: Rs." << balance << endl;
        cout << "Transaction Fee: Rs." << transactionFee << endl;
    }
};

int main()
{
    SavingAccount savings("Alice", 1001, 5000.0, 3.0);
    CheckingAccount checking("Bob", 1002, 3000.0, 20.0);

    cout << "--- Starting Savings Account Operations ---" << endl;
    savings.display();
    savings.deposit(1000);
    savings.withdraw(2000);
    savings.applyInterest();
    savings.display();

    cout << endl;

    cout << "--- Starting Checking Account Operations ---" << endl;
    checking.display();
    checking.deposit(1500.0);
    checking.withdraw(1000.0);
    checking.withdraw(4000.0);
    checking.display();

    return 0;
}