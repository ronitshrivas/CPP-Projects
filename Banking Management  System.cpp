
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Account
{
public:
    int accountNumber;
    string name;
    float balance;

    Account() : accountNumber(0), name(""), balance(0.0) {}

    Account(int accNo, string accName, float accBalance) : accountNumber(accNo), name(accName), balance(accBalance) {}

    void display() const
    {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Balance: $" << balance << endl;
    }

    void deposit(float amount)
    {
        balance += amount;
    }

    void withdraw(float amount)
    {
        if (amount > balance)
        {
            cout << "Insufficient funds!" << endl;
        }
        else
        {
            balance -= amount;
        }
    }
};

void saveAccount(const Account &acc)
{
    ofstream outFile("accounts.dat", ios::binary | ios::app);
    if (!outFile)
    {
        cerr << "Error opening file!" << endl;
        return;
    }
    outFile.write(reinterpret_cast<const char *>(&acc), sizeof(Account));
    outFile.close();
}

vector<Account> loadAccounts()
{
    vector<Account> accounts;
    ifstream inFile("accounts.dat", ios::binary);
    if (!inFile)
    {
        cerr << "Error opening file!" << endl;
        return accounts;
    }
    Account acc;
    while (inFile.read(reinterpret_cast<char *>(&acc), sizeof(Account)))
    {
        accounts.push_back(acc);
    }
    inFile.close();
    return accounts;
}

void createAccount()
{
    int accNo;
    string name;
    float balance;

    cout << "Enter account number: ";
    cin >> accNo;
    cin.ignore(); // To ignore newline left in the buffer
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter initial balance: ";
    cin >> balance;

    Account acc(accNo, name, balance);
    saveAccount(acc);

    cout << "Account created successfully!" << endl;
}

void depositMoney()
{
    vector<Account> accounts = loadAccounts();
    int accNo;
    float amount;

    cout << "Enter account number: ";
    cin >> accNo;
    cout << "Enter amount to deposit: ";
    cin >> amount;

    for (auto &acc : accounts)
    {
        if (acc.accountNumber == accNo)
        {
            acc.deposit(amount);
            break;
        }
    }

    ofstream outFile("accounts.dat", ios::binary | ios::trunc);
    if (!outFile)
    {
        cerr << "Error opening file!" << endl;
        return;
    }
    for (const auto &acc : accounts)
    {
        outFile.write(reinterpret_cast<const char *>(&acc), sizeof(Account));
    }
    outFile.close();

    cout << "Amount deposited successfully!" << endl;
}

void withdrawMoney()
{
    vector<Account> accounts = loadAccounts();
    int accNo;
    float amount;

    cout << "Enter account number: ";
    cin >> accNo;
    cout << "Enter amount to withdraw: ";
    cin >> amount;

    for (auto &acc : accounts)
    {
        if (acc.accountNumber == accNo)
        {
            acc.withdraw(amount);
            break;
        }
    }

    ofstream outFile("accounts.dat", ios::binary | ios::trunc);
    if (!outFile)
    {
        cerr << "Error opening file!" << endl;
        return;
    }
    for (const auto &acc : accounts)
    {
        outFile.write(reinterpret_cast<const char *>(&acc), sizeof(Account));
    }
    outFile.close();

    cout << "Amount withdrawn successfully!" << endl;
}

void checkBalance()
{
    vector<Account> accounts = loadAccounts();
    int accNo;

    cout << "Enter account number: ";
    cin >> accNo;

    for (const auto &acc : accounts)
    {
        if (acc.accountNumber == accNo)
        {
            acc.display();
            return;
        }
    }

    cout << "Account not found!" << endl;
}

void listAccounts()
{
    vector<Account> accounts = loadAccounts();
    for (const auto &acc : accounts)
    {
        acc.display();
        cout << "---------------------------" << endl;
    }
}

int main()
{
    int choice;

    while (true)
    {
        cout << "\nBanking Management System\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. List All Accounts\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
            depositMoney();
            break;
        case 3:
            withdrawMoney();
            break;
        case 4:
            checkBalance();
            break;
        case 5:
            listAccounts();
            break;
        case 6:
            return 0;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
