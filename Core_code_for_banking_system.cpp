#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>
using namespace std;

class BankAccount {
private:
    string accountHolderName;
    string accountNumber;
    double balance;
    static const double INTEREST_RATE;

public:
    BankAccount(string holderName, string accNumber) {
        accountHolderName = holderName;
        accountNumber = accNumber;
        balance = 0.0;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: " << amount << " into account " << accountNumber << endl;
        } else {
            cout << "Invalid amount for deposit." << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: " << amount << " from account " << accountNumber << endl;
        } else {
            cout << "Insufficient balance or invalid amount." << endl;
        }
    }

    void createFDR(double amount, int months) {
        if (amount > 0) {
            double interest = amount * INTEREST_RATE * months / 12;
            double totalAmount = amount + interest;
            cout << "FDR Created for " << months << " months with amount: " << totalAmount << endl;
        } else {
            cout << "Invalid amount for FDR." << endl;
        }
    }

    void createDPS(double amount, int months) {
        if (amount > 0) {
            double interest = amount * INTEREST_RATE * months / 12;
            double totalAmount = amount + interest;
            cout << "DPS Created for " << months << " months with amount: " << totalAmount << endl;
        } else {
            cout << "Invalid amount for DPS." << endl;
        }
    }

    void displayAccountInfo() {
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: " << balance << endl;
    }

    string getAccountNumber() {
        return accountNumber;
    }

    double getBalance() {
        return balance;
    }
};

const double BankAccount::INTEREST_RATE = 0.02;

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
    vector<BankAccount> bankAccounts;
    for (int i = 1; i <= 10; i++) {
        string accountHolderName = "User " + to_string(i);
        string accountNumber = "ACC" + to_string(1000 + i);
        bankAccounts.push_back(BankAccount(accountHolderName, accountNumber));
    }

    int choose = 1;
    while (true) {
        system("CLS");

        SetColor(11);
        cout << "Banking System - Use 'w' to move up, 'x' to move down, 's' to select an option\n";
        SetColor(10);
        cout << "Use 'w' or 'x' to navigate and 's' to select.\n\n";

        SetColor(7);
        cout << (choose == 1 ? "> Deposit" : "  Deposit") << endl;
        SetColor(9);
        cout << (choose == 2 ? "> Withdraw" : "  Withdraw") << endl;
        SetColor(11);
        cout << (choose == 3 ? "> Create FDR" : "  Create FDR") << endl;
        SetColor(13);
        cout << (choose == 4 ? "> Create DPS" : "  Create DPS") << endl;
        SetColor(14);
        cout << (choose == 5 ? "> Display Account Info" : "  Display Account Info") << endl;
        SetColor(12);
        cout << (choose == 6 ? "> Exit" : "  Exit") << endl;

        char ch = _getch();

        if ((ch == 'w' || ch == 'W' || ch == 72) && (choose > 1)) {
            choose--;
        } else if ((ch == 'x' || ch == 'X' || ch == 80) && (choose < 6)) {
            choose++;
        } else if (ch == 's' || ch == 'S' || ch == '\r') {
            if (choose ==6) {
                cout << "Exiting the banking system. Goodbye!" << endl;
                return 0;
            }
            system("CLS");
            SetColor(10);
            string accountNumber;
            cout << "\nEnter Account Number: ";
            cin >> accountNumber;

            BankAccount* account = nullptr;
            for (auto &acc : bankAccounts) {
                if (acc.getAccountNumber() == accountNumber) {
                    account = &acc;
                    break;
                }
            }

            if (account == nullptr) {
                system("CLS");
                SetColor(12);
                cout << "\nNo user or account found with Account Number: " << accountNumber << endl;
                SetColor(10);
                cout << "Press any key to continue...";
                _getch();
                continue;
            }

            switch (choose) {
                case 1: {
                    double depositAmount;
                    cout << "Enter amount to deposit: ";
                    cin >> depositAmount;
                    account->deposit(depositAmount);
                    break;
                }
                case 2: {
                    double withdrawAmount;
                    cout << "Enter amount to withdraw: ";
                    cin >> withdrawAmount;
                    account->withdraw(withdrawAmount);
                    break;
                }
                case 3: {
                    double fdrAmount;
                    int fdrMonths;
                    cout << "Enter amount for FDR: ";
                    cin >> fdrAmount;
                    cout << "Enter number of months: ";
                    cin >> fdrMonths;
                    account->createFDR(fdrAmount, fdrMonths);
                    break;
                }
                case 4: {
                    double dpsAmount;
                    int dpsMonths;
                    cout << "Enter amount for DPS: ";
                    cin >> dpsAmount;
                    cout << "Enter number of months: ";
                    cin >> dpsMonths;
                    account->createDPS(dpsAmount, dpsMonths);
                    break;
                }
                case 5: {
                    account->displayAccountInfo();
                    break;
                }
                default:
                    cout << "Invalid option! Please try again." << endl;
            }

            cout << "\nPress any key to continue...";
            _getch();
        }
    }

    return 0;
}
