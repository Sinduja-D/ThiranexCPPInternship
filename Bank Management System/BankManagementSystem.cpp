#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Account {
public:
    int accountNo;
    string name;
    string phone;
    double balance;

    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accountNo;
        cin.ignore();

        cout << "Enter Customer Name: ";
        getline(cin, name);

        cout << "Enter Phone Number: ";
        getline(cin, phone);

        cout << "Enter Initial Deposit: ";
        cin >> balance;
    }

    void displayAccount() const {
        cout << left
             << setw(12) << accountNo
             << setw(25) << name
             << setw(15) << phone
             << setw(12) << fixed << setprecision(2) << balance
             << endl;
    }
};

const string FILE_NAME = "accounts.txt";

// Load all accounts
vector<Account> loadAccounts() {
    vector<Account> accounts;
    ifstream file(FILE_NAME);

    string line;

    while (getline(file, line)) {
        Account acc;

        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);

        acc.accountNo = stoi(line.substr(0, p1));
        acc.name = line.substr(p1 + 1, p2 - p1 - 1);
        acc.phone = line.substr(p2 + 1, p3 - p2 - 1);
        acc.balance = stod(line.substr(p3 + 1));

        accounts.push_back(acc);
    }

    file.close();
    return accounts;
}

// Save all accounts
void saveAccounts(const vector<Account>& accounts) {
    ofstream file(FILE_NAME);

    for (const auto& acc : accounts) {
        file << acc.accountNo << "|"
             << acc.name << "|"
             << acc.phone << "|"
             << acc.balance << endl;
    }

    file.close();
}

// Create account
void createAccount() {
    Account acc;
    acc.createAccount();

    ofstream file(FILE_NAME, ios::app);

    file << acc.accountNo << "|"
         << acc.name << "|"
         << acc.phone << "|"
         << acc.balance << endl;

    file.close();

    cout << "\nAccount Created Successfully!\n";
}

// Display all accounts
void displayAccounts() {
    vector<Account> accounts = loadAccounts();

    if (accounts.empty()) {
        cout << "\nNo accounts found.\n";
        return;
    }

    cout << "\n==============================================================\n";
    cout << left
         << setw(12) << "Acc No"
         << setw(25) << "Name"
         << setw(15) << "Phone"
         << setw(12) << "Balance" << endl;
    cout << "==============================================================\n";

    for (const auto& acc : accounts) {
        acc.displayAccount();
    }
}

// Search account
void searchAccount() {
    int accNo;
    cout << "\nEnter Account Number: ";
    cin >> accNo;

    vector<Account> accounts = loadAccounts();

    for (const auto& acc : accounts) {
        if (acc.accountNo == accNo) {
            cout << "\nAccount Found:\n\n";

            cout << "Account Number : " << acc.accountNo << endl;
            cout << "Name           : " << acc.name << endl;
            cout << "Phone          : " << acc.phone << endl;
            cout << "Balance        : " << acc.balance << endl;

            return;
        }
    }

    cout << "\nAccount not found.\n";
}

// Deposit
void depositMoney() {
    int accNo;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    vector<Account> accounts = loadAccounts();

    for (auto& acc : accounts) {
        if (acc.accountNo == accNo) {
            cout << "Enter Amount to Deposit: ";
            cin >> amount;

            acc.balance += amount;

            saveAccounts(accounts);

            cout << "\nDeposit Successful!\n";
            cout << "Current Balance: " << acc.balance << endl;
            return;
        }
    }

    cout << "\nAccount not found.\n";
}

// Withdraw
void withdrawMoney() {
    int accNo;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    vector<Account> accounts = loadAccounts();

    for (auto& acc : accounts) {
        if (acc.accountNo == accNo) {

            cout << "Enter Amount to Withdraw: ";
            cin >> amount;

            if (amount > acc.balance) {
                cout << "\nInsufficient Balance!\n";
                return;
            }

            acc.balance -= amount;

            saveAccounts(accounts);

            cout << "\nWithdrawal Successful!\n";
            cout << "Remaining Balance: " << acc.balance << endl;
            return;
        }
    }

    cout << "\nAccount not found.\n";
}

// Check balance
void checkBalance() {
    int accNo;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    vector<Account> accounts = loadAccounts();

    for (const auto& acc : accounts) {
        if (acc.accountNo == accNo) {
            cout << "\nCurrent Balance: " << acc.balance << endl;
            return;
        }
    }

    cout << "\nAccount not found.\n";
}

// Delete account
void deleteAccount() {
    int accNo;

    cout << "\nEnter Account Number to Delete: ";
    cin >> accNo;

    vector<Account> accounts = loadAccounts();
    vector<Account> updatedAccounts;

    bool found = false;

    for (const auto& acc : accounts) {
        if (acc.accountNo == accNo) {
            found = true;
        } else {
            updatedAccounts.push_back(acc);
        }
    }

    if (!found) {
        cout << "\nAccount not found.\n";
        return;
    }

    saveAccounts(updatedAccounts);

    cout << "\nAccount Deleted Successfully!\n";
}

// Main Menu
int main() {
    int choice;

    do {
        cout << "\n\n========== BANK MANAGEMENT SYSTEM ==========\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Display All Accounts\n";
        cout << "6. Search Account\n";
        cout << "7. Delete Account\n";
        cout << "8. Exit\n";
        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
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
            displayAccounts();
            break;

        case 6:
            searchAccount();
            break;

        case 7:
            deleteAccount();
            break;

        case 8:
            cout << "\nThank You For Using Bank Management System!\n";
            break;

        default:
            cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 8);

    return 0;
}