#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <limits>
#include <string>

using namespace std;

const int MAX_ACCOUNTS = 100;
const int MAX_HISTORY = 50;
const int MAX_MASTER = 1000;

struct Transaction
{
    string accNo;
    string type;
    double amount;
    string timestamp;
};

struct Account
{
    string name;
    string accNo;
    double balance;
    Transaction history[MAX_HISTORY];
    int historyCount;
};

class Bank
{
private:
    Account accounts[MAX_ACCOUNTS];
    int accountCount;

    Transaction master[MAX_MASTER];
    int masterCount;

    string getTime()
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        char buffer[30];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
        return buffer;
    }

    int findAccountIndex(string accNo)
    {
        for (int i = 0; i < accountCount; i++)
        {
            if (accounts[i].accNo == accNo)
            {
                return i;
            }
        }
        return -1;
    }

    Account *findAccount(string accNo)
    {
        int index = findAccountIndex(accNo);
        if (index != -1)
        {
            return &accounts[index];
        }
        return nullptr;
    }

    void loadAccountsFromFile()
    {
        ifstream file("accounts.txt");
        if (!file)
            return;

        string line;
        while (getline(file, line))
        {
            if (accountCount >= MAX_ACCOUNTS)
            {
                cout << "Warning: Max accounts reached. Some accounts may not be loaded.\n";
                break;
            }

            stringstream ss(line);
            Account acc;
            acc.historyCount = 0;

            getline(ss, acc.accNo, ',');
            getline(ss, acc.name, ',');
            string balanceStr;
            getline(ss, balanceStr, ',');

            if (balanceStr.empty())
                continue;
            acc.balance = stod(balanceStr);

            accounts[accountCount] = acc;
            accountCount++;
        }
        file.close();
    }

    void saveAccountsToFile()
    {
        ofstream file("accounts.txt", ios::out);
        for (int i = 0; i < accountCount; i++)
        {
            file << accounts[i].accNo << ","
                 << accounts[i].name << ","
                 << accounts[i].balance << "\n";
        }
        file.close();
    }

    void loadTransactionsOnStartup()
    {
        ifstream file("Master_Transactions.txt");
        if (!file)
            return;

        string line;
        while (getline(file, line))
        {
            if (masterCount >= MAX_MASTER)
            {
                cout << "Warning: Master log full. Some transactions may not be loaded.\n";
                break;
            }

            stringstream ss(line);
            Transaction t;

            getline(ss, t.accNo, ',');
            getline(ss, t.type, ',');
            string amountStr;
            getline(ss, amountStr, ',');
            if (amountStr.empty())
                continue;
            t.amount = stod(amountStr);
            getline(ss, t.timestamp, ',');

            master[masterCount] = t;
            masterCount++;

            Account *acc = findAccount(t.accNo);
            if (acc != nullptr)
            {
                if (acc->historyCount < MAX_HISTORY)
                {
                    acc->history[acc->historyCount] = t;
                    acc->historyCount++;
                }
            }
        }
        file.close();
    }

    void saveTransactionToFile(const Transaction &t)
    {
        ofstream file("Master_Transactions.txt", ios::app);
        if (!file)
        {
            cout << "Error writing to master log file." << endl;
            return;
        }
        file << t.accNo << ","
             << t.type << ","
             << t.amount << ","
             << t.timestamp << "\n";
        file.close();
    }

    void addTransactionToHistory(Account *acc, const Transaction &t)
    {
        if (acc->historyCount < MAX_HISTORY)
        {
            acc->history[acc->historyCount] = t;
            acc->historyCount++;
        }
        else
        {
            cout << "Note: Account history is full. This transaction won't be saved in history.\n";
        }
    }

    void addTransactionToMaster(const Transaction &t)
    {
        if (masterCount < MAX_MASTER)
        {
            master[masterCount] = t;
            masterCount++;
        }
        else
        {
            cout << "Note: Master transaction log is full. This transaction won't be saved.\n";
        }
    }

public:
    Bank()
    {
        accountCount = 0;
        masterCount = 0;
    }

    void loadDataOnStartup()
    {
        cout << "Loading accounts...\n";
        loadAccountsFromFile();
        cout << "Loading transaction history...\n";
        loadTransactionsOnStartup();
        cout << "Data loaded.\n";
    }

    void finalSave()
    {
        saveAccountsToFile();
    }

    void createAccount()
    {
        if (accountCount >= MAX_ACCOUNTS)
        {
            cout << "Cannot create new account: Bank capacity is full.\n";
            return;
        }

        Account acc;
        cout << "Enter Account No: ";
        cin >> acc.accNo;
        if (findAccount(acc.accNo) != nullptr)
        {
            cout << "Account already exists.\n";
            return;
        }
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, acc.name);
        cout << "Enter Initial Balance: ";
        cin >> acc.balance;

        acc.historyCount = 0;
        accounts[accountCount] = acc;
        accountCount++;

        saveAccountsToFile();

        cout << "Account created successfully.\n";
    }

    void deposit()
    {
        string accNo;
        double amt;
        cout << "Enter Account No: ";
        cin >> accNo;

        Account *acc = findAccount(accNo);
        if (acc == nullptr)
        {
            cout << "Account not found.\n";
            return;
        }

        cout << "Enter Amount to Deposit: ";
        cin >> amt;
        if (amt <= 0)
        {
            cout << "Deposit amount must be positive.\n";
            return;
        }
        acc->balance += amt;

        Transaction t = {accNo, "DEPOSIT", amt, getTime()};
        addTransactionToHistory(acc, t);
        addTransactionToMaster(t);

        saveTransactionToFile(t);
        saveAccountsToFile();

        cout << "Deposit successful.\n";
    }

    void withdraw()
    {
        string accNo;
        double amt;
        cout << "Enter Account No: ";
        cin >> accNo;

        Account *acc = findAccount(accNo);
        if (acc == nullptr)
        {
            cout << "Account not found.\n";
            return;
        }

        cout << "Enter Amount to Withdraw: ";
        cin >> amt;
        if (amt <= 0)
        {
            cout << "Withdrawal amount must be positive.\n";
            return;
        }
        if (amt > acc->balance)
        {
            cout << "Insufficient balance.\n";
            return;
        }
        acc->balance -= amt;

        Transaction t = {accNo, "WITHDRAW", amt, getTime()};
        addTransactionToHistory(acc, t);
        addTransactionToMaster(t);

        saveTransactionToFile(t);
        saveAccountsToFile();

        cout << "Withdrawal successful.\n";
    }

    void transferFunds()
    {
        string fromAcc, toAcc;
        double amt;
        cout << "Enter *your* Account No: ";
        cin >> fromAcc;
        cout << "Enter Account No to transfer *to*: ";
        cin >> toAcc;

        Account *accFrom = findAccount(fromAcc);
        Account *accTo = findAccount(toAcc);

        if (accFrom == nullptr)
        {
            cout << "Your account was not found.\n";
            return;
        }
        if (accTo == nullptr)
        {
            cout << "The recipient account was not found.\n";
            return;
        }
        if (fromAcc == toAcc)
        {
            cout << "Cannot transfer to the same account.\n";
            return;
        }

        cout << "Enter amount to transfer: ";
        cin >> amt;

        if (amt <= 0)
        {
            cout << "Transfer amount must be positive.\n";
            return;
        }
        if (amt > accFrom->balance)
        {
            cout << "Insufficient balance for transfer.\n";
            return;
        }

        accFrom->balance -= amt;
        accTo->balance += amt;

        string time = getTime();
        Transaction tOut = {fromAcc, "TRANSFER_OUT", amt, time};
        Transaction tIn = {toAcc, "TRANSFER_IN", amt, time};

        addTransactionToHistory(accFrom, tOut);
        addTransactionToMaster(tOut);
        saveTransactionToFile(tOut);

        addTransactionToHistory(accTo, tIn);
        addTransactionToMaster(tIn);
        saveTransactionToFile(tIn);

        saveAccountsToFile();

        cout << "Transfer successful.\n";
    }

    void deleteAccount()
    {
        string accNo;
        cout << "Enter Account No to delete: ";
        cin >> accNo;

        int index = findAccountIndex(accNo);
        if (index == -1)
        {
            cout << "Account not found.\n";
            return;
        }

        Account *acc = &accounts[index];

        if (acc->balance > 0)
        {
            cout << "Cannot delete account. Balance is not zero ("
                 << acc->balance << ").\n";
            cout << "Please withdraw all funds first.\n";
            return;
        }

        char confirm;
        cout << "Delete " << acc->name << " (" << accNo << ")? (y/n): ";
        cin >> confirm;

        if (confirm == 'y' || confirm == 'Y')
        {
            for (int i = index; i < accountCount - 1; i++)
            {
                accounts[i] = accounts[i + 1];
            }
            accountCount--;

            saveAccountsToFile();
            cout << "Account deleted successfully.\n";
        }
        else
        {
            cout << "Deletion cancelled.\n";
        }
    }

    void checkBalance()
    {
        string accNo;
        cout << "Enter Account No: ";
        cin >> accNo;
        Account *acc = findAccount(accNo);
        if (acc == nullptr)
        {
            cout << "Account not found.\n";
            return;
        }
        cout << "Account Holder: " << acc->name << "\n";
        cout << "Balance: " << fixed << setprecision(2) << acc->balance << "\n";
    }

    void showAccountHistory()
    {
        string accNo;
        cout << "Enter Account No: ";
        cin >> accNo;
        Account *acc = findAccount(accNo);
        if (acc == nullptr)
        {
            cout << "Account not found.\n";
            return;
        }
        cout << "\nTransaction History for " << acc->name << " (" << accNo << ")\n";
        cout << "--------------------------------------------------------\n";
        cout << left << setw(15) << "Type" << setw(12) << "Amount" << "Timestamp\n";
        cout << "--------------------------------------------------------\n";

        if (acc->historyCount == 0)
        {
            cout << "No transactions found.\n";
        }

        for (int i = 0; i < acc->historyCount; i++)
        {
            Transaction &t = acc->history[i];
            cout << left << setw(15) << t.type
                 << setw(12) << fixed << setprecision(2) << t.amount
                 << t.timestamp << "\n";
        }
    }

    void showMasterTransactions()
    {
        cout << "\n=== Master Transaction Log ===\n";
        cout << "-----------------------------------------------------------------------------\n";
        cout << left
             << setw(12) << "Account No"
             << setw(20) << "Name"
             << setw(15) << "Type"
             << setw(12) << "Amount"
             << "Timestamp" << "\n";
        cout << "-----------------------------------------------------------------------------\n";

        ifstream file("Master_Transactions.txt");
        if (!file)
        {
            cout << "No transaction log file found.\n";
            return;
        }

        string line;
        while (getline(file, line))
        {
            if (line.empty())
            {
                continue;
            }

            stringstream ss(line);
            string accNo, type, amountStr, timestamp;
            getline(ss, accNo, ',');
            getline(ss, type, ',');
            getline(ss, amountStr, ',');
            getline(ss, timestamp, ',');

            string name = "N/A";
            Account *acc = findAccount(accNo);
            if (acc != nullptr)
            {
                name = acc->name;
            }

            if (amountStr.empty())
            {
                continue;
            }

            cout << left
                 << setw(12) << accNo
                 << setw(20) << name
                 << setw(15) << type
                 << setw(12) << fixed << setprecision(2) << stod(amountStr)
                 << timestamp << "\n";
        }
        file.close();
    }
};

int getChoice()
{
    int choice;
    cout << "\nEnter choice: ";
    cin >> choice;

    while (cin.fail())
    {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> choice;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

int main()
{
    Bank b;
    b.loadDataOnStartup();

    int choice;
    while (true)
    {
        cout << "\n--- Banking System ---\n";
        cout << "1. Create Account\n2. Deposit\n3. Withdraw\n4. Check Balance\n";
        cout << "5. Account History\n6. Master Transactions\n7. Transfer Funds\n";
        cout << "8. Delete Account\n9. Exit\n";

        choice = getChoice();

        switch (choice)
        {
        case 1:
            b.createAccount();
            break;
        case 2:
            b.deposit();
            break;
        case 3:
            b.withdraw();
            break;
        case 4:
            b.checkBalance();
            break;
        case 5:
            b.showAccountHistory();
            break;
        case 6:
            b.showMasterTransactions();
            break;
        case 7:
            b.transferFunds();
            break;
        case 8:
            b.deleteAccount();
            break;
        case 9:
            cout << "Shutting down and saving...\n";
            b.finalSave();
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}