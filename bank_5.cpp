#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;
class Bank {
public:
    virtual void intro() = 0;
    virtual string getBankName() = 0;
    virtual ~Bank() {}
};

class SBI : public Bank {
public:
    void intro() override {
        cout << "Welcome to State Bank of India (SBI)" << endl;
    }

    string getBankName() override {
        return "SBI";
    }
};

class AxisBank : public Bank {
public:
    void intro() override {
        cout << "Welcome to Axis Bank" << endl;
    }

    string getBankName() override {
        return "Axis Bank";
    }
};

class ICICIBank : public Bank {
public:
    void intro() override {
        cout << "Welcome to ICICI Bank" << endl;
    }

    string getBankName() override {
        return "ICICI Bank";
    }
};

class HDFC : public Bank {
public:
    void intro() override {
        cout << "Welcome to HDFC Bank" << endl;
    }

    string getBankName() override {
        return "HDFC Bank";
    }
};

class PNB : public Bank {
public:
    void intro() override {
        cout << "Welcome to Punjab National Bank (PNB)" << endl;
    }

    string getBankName() override {
        return "PNB";
    }
};

class CanaraBank : public Bank {
public:
    void intro() override {
        cout << "Welcome to Canara Bank" << endl;
    }

    string getBankName() override {
        return "Canara Bank";
    }
};

class account {
    int acno;
    char name[50];
    char type;
    string password;
    int deposit;
    Bank* bank;

public:
    void create_account(Bank* bank);
    void show_account();
    void modify();
    void dep(int);
    void draw(int);
    void report();
    int retacno();
    int retdeposit();
    char rettype();
    bool check_password(string);
    void change_name(char[]);
    void change_password(string&);
};

vector<account> sbiAccounts;
vector<account> axisBankAccounts;
vector<account> iciciAccounts;
vector<account> hdfcAccounts;
vector<account> pnbAccounts;
vector<account> canaraAccounts;

bool account::check_password(string pass) {
    return password == pass;
}

void account::create_account(Bank* bank) {
    cout << "\nEnter The account No. : ";
    cin >> acno;
    cout << "\n\nEnter The Name of The account Holder : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nEnter Type of The account (C/S) : ";
    cin >> type;
    type = toupper(type);
    cout << "\nEnter The Initial amount (>=500 for Saving and >=1000 for current): ";
    cin >> deposit;
    cout << "\nEnter The Account Password: ";
    cin >> password;
    this->bank = bank;
    cout << "\nAccount Created in " << bank->getBankName() << "..";
    cin.get();
}

void account::show_account() {
    string pass;
    cout << "\nEnter Account Password: ";
    cin >> pass;
    if (check_password(pass)) {
        bank->intro();
        cout << "\nAccount No. : " << acno;
        cout << "\nAccount Holder Name : " << name;
        cout << "\nType of Account : " << type;
        cout << "\nBalance amount : " << deposit;
    } else {
        cout << "\nInvalid password. Access denied.";
    }
    cin.get();
}

void account::modify() {
    string pass;
    cout << "\nEnter Account Password: ";
    cin >> pass;
    if (check_password(pass)) {
        cout << "\nAccount No. : " << acno;
        cout << "\nModify Account Holder Name (or press Enter to keep the same): ";
        cin.ignore();
        cin.getline(name, 50);

        cout << "\nSet a new password (or press Enter to keep the same): ";
        string new_password;
        cin >> new_password;
        if (!new_password.empty()) {
            password = new_password;
        }
        cout << "\nRecord Updated";
    } else {
        cout << "\nInvalid password. Access denied.";
    }
    cin.get();
}

void account::change_name(char new_name[]) {
    strcpy(name, new_name);
}

void account::change_password(string& new_password) {
    password = new_password;
}

void account::dep(int x) {
    deposit += x;
}

void account::draw(int x) {
    deposit -= x;
}

void account::report() {
    cout << acno << "\t\t" << name << "\t\t" << type << "\t\t" << deposit << endl;
}

int account::retacno() {
    return acno;
}

int account::retdeposit() {
    return deposit;
}

char account::rettype() {
    return type;
}

void write_account(Bank* bank, vector<account>& accounts) {
    account ac;
    ac.create_account(bank);
    accounts.push_back(ac);
    cout << "\nAccount Created..";
    cin.get();
}

void display_sp(int n, Bank* bank, vector<account>& accounts) {
    bool found = false;
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].retacno() == n) {
            accounts[i].show_account();
            found = true;
        }
    }
    if (!found)
        cout << "\nAccount number does not exist";
    cin.get();
}

void modify_account(int n, Bank* bank, vector<account>& accounts) {
    bool found = false;
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].retacno() == n) {
            accounts[i].show_account();
            cout << "\nEnter The New Details of account" << endl;
            accounts[i].modify();
            cout << "\nRecord Updated";
            found = true;
        }
    }
    if (!found)
        cout << "\nRecord Not Found ";
    cin.get();
}

void delete_account(int n, vector<account>& accounts) {
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].retacno() == n) {
            accounts.erase(accounts.begin() + i);
            cout << "\nRecord Deleted ..";
            return;
        }
    }
    cout << "\nRecord Not Found ";
    cin.get();
}

void display_all(vector<account>& accounts) {
    cout << "\nACCOUNT HOLDER LIST\n";
    cout << "====================================================\n";
    cout << "A/c no.     NAME                Type  Balance\n";
    cout << "====================================================\n";
    for (int i = 0; i < accounts.size(); i++) {
        accounts[i].report();
    }
    cin.get();
}

void deposit_withdraw(int n, int option, vector<account>& accounts) {
    int amt;
    bool found = false;
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].retacno() == n) {
            cout << "Enter Account Password: ";
            string pass;
            cin >> pass;
            if (accounts[i].check_password(pass)) {
                accounts[i].show_account();
                if (option == 1) {
                    cout << "TO DEPOSIT AMOUNT" << endl;
                    cout << "Enter The amount to be deposited: ";
                    cin >> amt;
                    accounts[i].dep(amt);
                    cout << "Amount Deposited!";
                }
                if (option == 2) {
                    cout << "TO WITHDRAW AMOUNT" << endl;
                    cout << "Enter The amount to be withdrawn: ";
                    cin >> amt;
                    if (amt <= accounts[i].retdeposit()) {
                        accounts[i].draw(amt);
                        cout << "Amount Withdrawn!";
                    } else {
                        cout << "Insufficient balance!";
                    }
                }
                found = true;
            } else {
                cout << "Invalid password. Access denied.";
            }
        }
    }
    if (!found) {
        cout << "Account Not Found";
    }
    cin.get();
}

vector<account>& getAccountsForBank(Bank* selectedBank) {
    if (selectedBank->getBankName() == "SBI") {
        return sbiAccounts;
    } else if (selectedBank->getBankName() == "Axis Bank") {
        return axisBankAccounts;
    } else if (selectedBank->getBankName() == "ICICI Bank") {
        return iciciAccounts;
    } else if (selectedBank->getBankName() == "HDFC Bank") {
        return hdfcAccounts;
    } else if (selectedBank->getBankName() == "PNB") {
        return pnbAccounts;
    } else if (selectedBank->getBankName() == "Canara Bank") {
        return canaraAccounts;
    } else {
        cerr << "Bank not found!";
        exit(1);
    }
}
void intro() {
    cout << "\n\n\n\t\t  ---------------- BANK MANAGEMENT SYSTEM ----------------";
    cout << "\n\n\nTEAM MEMBERS : \t\t\t\t\t\t\t\t  SUBMITTED TO : MS. SHIKHA";
    cout << "\n\nDHRUV KANDPAL (22124031) ";
    cout << "\nDIVYANSH SAXENA (22124032) ";
    cout << "\nEKASPREET SINGH ATWAL (22124033) ";
    cout << "\nGARVIT GROVER (22124035) ";
    cout << "\nGOVIND DUBEY (22124038)\n ";
    cout << "\nBRANCH : INFORMATION TECHNOLOGY ";
    cout << "\n\n\n----------- COLLEGE : Dr. B.R. AMBEDKAR NATIONAL INSTITUTE OF TECHNOLOGY , JALANDHAR -------------";
    cin.get();
}

int main() {
    char ch;
    int num;
    intro();

    do {
        system("cls");
        cout << "\nSelect your bank:" << endl;
        vector<Bank*> banks = {new SBI, new AxisBank, new ICICIBank, new HDFC, new PNB, new CanaraBank};
        int i = 0;
        for (; i < banks.size(); i++) {
            cout << i + 1 << ". " << banks[i]->getBankName() << endl;
        }
        cout << i + 1 << ". Exit" << endl;
        int bankChoice;
        cin >> bankChoice;
        cout << "\n\n";
        if (bankChoice == i + 1) {
            ch = '8';
        } else if (bankChoice >= 1 && bankChoice <= banks.size()) {
            Bank* selectedBank = banks[bankChoice - 1];
            selectedBank->intro();

            cout << "\nMAIN MENU" << endl;
            cout << "1. NEW ACCOUNT" << endl;
            cout << "2. DEPOSIT AMOUNT" << endl;
            cout << "3. WITHDRAW AMOUNT" << endl;
            cout << "4. BALANCE ENQUIRY" << endl;
            cout << "5. ALL ACCOUNT HOLDER LIST" << endl;
            cout << "6. CLOSE AN ACCOUNT" << endl;
            cout << "7. MODIFY AN ACCOUNT" << endl;
            cout << "8. EXIT" << endl;
            cout << "Select Your Option (1-8): ";
            cin >> ch;
            
            switch (ch) {
                case '1':
                    write_account(selectedBank, getAccountsForBank(selectedBank));
                    break;
                case '2':
                    cout << "Enter The account No. : ";
                    cin >> num;
                    deposit_withdraw(num, 1, getAccountsForBank(selectedBank));
                    break;
                case '3':
                    cout << "Enter The account No. : ";
                    cin >> num;
                    deposit_withdraw(num, 2, getAccountsForBank(selectedBank));
                    break;
                case '4':
                    cout << "Enter The account No. : ";
                    cin >> num;
                    display_sp(num, selectedBank, getAccountsForBank(selectedBank));
                    break;
                case '5':
                    display_all(getAccountsForBank(selectedBank));
                    break;
                case '6':
                    cout << "Enter The account No. : ";
                    cin >> num;
                    delete_account(num, getAccountsForBank(selectedBank));
                    break;
                case '7':
                    cout << "Enter The account No. : ";
                    cin >> num;
                    modify_account(num, selectedBank, getAccountsForBank(selectedBank));
                    break;
                case '8':
                    cout << "Thanks for using bank management system" << endl;
                    break;
                default:
                    cout << "Invalid option. Please try again." << endl;
            }
        } else {
            cout << "Invalid bank choice. Exiting..." << endl;
        }
        // Cleanup
        for (Bank* bank : banks) {
            delete bank;
        }
        if(ch!=8){
            cout<<"\n Press Enter to continue";
            cin.get();
        }
    } while (ch != '8');
    return 0;
}
