#include "stdafx.h"
#include "iostream"
using namespace std;
#include "string"
#include "fstream"
#include "conio.h"

void Menu();
void BackToMenu(int);

class CreateAccount {
public:
	void Create() {
		cout << "Please enter a ID: ";
		cin >> ID;
		cout << "Please enter a password: ";
		cin >> Password;
		cout << "Please enter a amount: ";
		cin >> Amount;
		Amount /= 10;
		cout << Amount << " Tomans was added" << endl;
		cout << "-----------------------------" << endl;
	}
protected:
	int ID, Password;
	double Amount;
};

class AccountInformation : public CreateAccount {
public:
	void Accounts() {
		cout << "ID: " << ID << endl << "Password: " << Password << endl << "Your account balance is " << Amount << endl;
		cout << "-----------------------------" << endl;
	}
	void Deposit(double Amount) {
		this->Amount += Amount;
	}
	void Withdrawal(double Amount) {
		this->Amount -= Amount;
	}
	double ReturnAmount() {
		return Amount;
	}
	int ReturnID() {
		return ID;
	}
	void CreateFunc() {
		CreateAccount CreateAccountObject;
		ofstream Account("Accounts.txt", ios::app);
		CreateAccountObject.Create();
		Account.write((char *)&CreateAccountObject, sizeof(CreateAccountObject));
	}
	void AccountFunc() {
		AccountInformation AccountInformationObject;
		ifstream Account("Accounts.txt");
		while (Account.read((char *)&AccountInformationObject, sizeof(AccountInformationObject))) {
			AccountInformationObject.Accounts();
		}
		if (!Account.is_open()) {
			cout << "There is no account" << endl;
			cout << "-----------------------------" << endl;
		}
	}
	void DepositAndWithdrawal(int ID, int Option) {
		AccountInformation AccountInformationObject;
		bool Flag = false;
		fstream Account("Accounts.txt", ios::in | ios::out);
		if (!Account.is_open()) {
			cout << "There is no account" << endl;
			cout << "-----------------------------" << endl;
		} else {
			while (!Account.eof() && Flag == false) {
				Account.read((char *)&AccountInformationObject, sizeof(AccountInformationObject));
				if (AccountInformationObject.ReturnID() == ID) {
					AccountInformationObject.Accounts();
					if (Option == 1) {
						cout << "Please enter a amount: ";
						cin >> Amount;
						if (Amount >= 1) {
							Amount /= 10;
							cout << Amount << " Tomans was added" << endl;
							AccountInformationObject.Deposit(Amount);
						} else {
							cout << "Amount are not enough" << endl;
						}
					} else if (Option == 2) {
						cout << "Please enter a amount: ";
						cin >> Amount;
						if (AccountInformationObject.ReturnAmount() >= Amount / 10 && Amount >= 1) {
							Amount /= 10;
							cout << Amount << " Tomans was reduced" << endl;
							AccountInformationObject.Withdrawal(Amount);
						} else {
							cout << "Amount are not enough" << endl;
						}
					}
					cout << "-----------------------------" << endl;
					int Edit = (int)sizeof(AccountInformationObject) * -1;
					Account.seekp(Edit, ios::cur);
					Account.write((char *)&AccountInformationObject, sizeof(AccountInformationObject));
					Flag = true;
				}
			}
			if (Flag == false) {
				cout << "This account does not exist" << endl;
				cout << "-----------------------------" << endl;
			}
		}
	}
	void AssetsFunc(int ID) {
		AccountInformation AccountInformationObject;
		bool Flag = false;
		ifstream Account("Accounts.txt");
		while (Account.read((char *)&AccountInformationObject, sizeof(AccountInformationObject))) {
			if (AccountInformationObject.ReturnID() == ID) {
				AccountInformationObject.Accounts();
				Flag = true;
			}
		}
		if (Flag == false) {
			cout << "This account does not exist" << endl;
			cout << "-----------------------------" << endl;
		}
	}
};

int main() {
	AccountInformation AccountInformationObject;
	system("color A");
	while (true) {
		int ID, Option;
		Menu();
		cin >> Option;
		if (Option == 1) {
			system("CLS");
			AccountInformationObject.CreateFunc();
			BackToMenu(Option);
		} else if (Option == 2) {
			system("CLS");
			AccountInformationObject.AccountFunc();
			BackToMenu(Option);
		} else if (Option == 3) {
			system("CLS");
			cout << "Please enter a ID: ";
			cin >> ID;
			AccountInformationObject.DepositAndWithdrawal(ID, 1);
			BackToMenu(Option);
		} else if (Option == 4) {
			system("CLS");
			cout << "Please enter a ID: ";
			cin >> ID;
			AccountInformationObject.AssetsFunc(ID);
			BackToMenu(Option);
		} else if (Option == 5) {
			system("CLS");
			cout << "Please enter a ID: ";
			cin >> ID;
			AccountInformationObject.DepositAndWithdrawal(ID, 2);
			BackToMenu(Option);
		} else if (Option == 0) {
			system("CLS");
			char Exit;
			cout << "Are you sure you want to leave (Y/N): ";
			cin >> Exit;
			if (Exit == 'y' || Exit == 'Y') {
				cout << "Thank you for using this application.";
				break;
			}
			system("CLS");
		} else {
			cout << "Please select the correct option" << endl;
			cout << "-----------------------------" << endl;
		}
	}
	_getch();
}

void Menu() {
	cout << "1. Create a new account" << endl;
	cout << "2. Accounts" << endl;
	cout << "3. Deposit" << endl;
	cout << "4. Asset" << endl;
	cout << "5. Withdrawal" << endl;
	cout << "0. Exit" << endl;
	cout << "Please select an option: ";
}

void BackToMenu(int Option) {
	cout << "1. Back to menu" << endl;
	cout << "Please select an option: ";
	cin >> Option;
	cout << "-----------------------------" << endl;
	while (Option != 1) {
		cout << "1. Back to menu" << endl;
		cout << "Please select the correct option: ";
		cin >> Option;
		cout << "-----------------------------" << endl;
	}
	system("CLS");
}
