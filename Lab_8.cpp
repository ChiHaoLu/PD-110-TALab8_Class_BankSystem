/*------------------------------------- Reference -------------------------------------*/
//  PD-110 TALab_8_Class
//  Author: b08303113 ChiHaoLu
// 	Discussion with: 
//  2021/11/28 19:49
/*-------------------------------------------------------------------------------------*/

#include <iostream>
#include <cmath>
#include <cctype>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#define MaxAccountNAME_LEN 20
#define MinAccountFIRST_DEPOSIT 1000
#define MaxAccountNUMBER 99999999
#define MinAccountNUMBER 10000000
#define AccountPasswordLen 8
using namespace std;

/*------------------------------------- Construct the Data Structure. --------------------*/
class Account{ 
private:
	char* _Name; // UserName
	int _Balance; // Account Balance
	int _Number; // Account Number
	int _Password; // Account Password
	bool _OperateNormally; // Whether the account is Operating Normally or not
public:
	Account(); // Constructors: Initialize something
	void ReviseAccount(char* Name, int Balance, int Password); // Revise the data when create the account
	void deposit(int);
	void withdraw(int);
	void PrintAccout();
	bool Status(); // return _OperateNormally
	bool Verify(int, int); // verify the account number, password and Operating Normally or not
	void DestroyAccout(); // change _OperateNormally to fasle
	~Account(); // Destructors: do something when the object is destroyed
};

Account::Account(){
	_Name = "UNCreated";
	_Balance = -1;
	_Number = -1;
	_Password = -1;
	_OperateNormally = false;
}

void Account::ReviseAccount(char* Name, int Balance, int Password){
	_Name = new char[MaxAccountNAME_LEN + 1];
	for(int i = 0; i <= strlen(Name); i++){
		_Name[i] = Name[i];
	}
	_Balance = Balance;
	// Produce the number by Random Seed in C++, We need the 8-digit Integer Number.
	_Number = rand() % (MaxAccountNUMBER - MinAccountNUMBER + 1) + MinAccountNUMBER;
	_Password = Password;
	_OperateNormally = true;
}

void Account::deposit(int Money){
	_Balance += Money;
}

void Account::withdraw(int Money){
	if(_Balance - Money >= 0){
		_Balance -= Money;
	}
	else{
		cout << "Sorry, You don't have enough money to withdraw!\n";
	}
}

bool Account::Status(){
	return _OperateNormally;
}

bool Account::Verify(int AccountNumber, int AccountPassword){
	cout << _OperateNormally << endl;
	if(AccountNumber == _Number && AccountPassword == _Password && _OperateNormally){
		return true;
	}
	return false;
}

void Account::PrintAccout(){
	cout << "---------------Account---------------\n";
	cout << "Name: " << _Name << endl;
	cout << "Account Number: " << _Number << endl;
	cout << "Account Balance: $" << _Balance << endl;
	cout << "-------------------------------------\n\n";
}

void Account::DestroyAccout(){
	_OperateNormally = false; 
}

Account::~Account(){
	delete [] _Name;
}

/*------------------------------------- Prepare the useful function!!! ------------------*/

void CreateAccount(Account &NewAccount){
	
	char *Creator_Name = new char[MaxAccountNAME_LEN + 1];
	int Creator_Balance = 0;
	int Creator_Password = 0;
	cout << endl;
	
	cout << "Please Key-In your \"Account Name\"(max len is " << MaxAccountNAME_LEN << "): ";
	cin >> Creator_Name;
	if(strlen(Creator_Name) > MaxAccountNAME_LEN){
		cout << "Create Failed!!! The len of Your Account Name is more than " << MaxAccountNAME_LEN << ".\n";
		return;
	}
	
	cout << "Please Key-In your \"First deposit\"(minimal requirement is $" << MinAccountFIRST_DEPOSIT << "): $";
	cin >>  Creator_Balance;
	if(Creator_Balance < MinAccountFIRST_DEPOSIT){
		cout << "Create Failed!!! Your First Deposit is less than $" << MinAccountFIRST_DEPOSIT << ".\n";
		return;
	}

	cout << "Please Key-In your \"Account Password\"(your password len must be  " << 8 <<"): ";
	cin >> Creator_Password;
	if(Creator_Password > 99999999 || Creator_Password < 10000000){
		cout << "Create Failed!!! The len of Your Password is not " << 8 << ".\n";
		return;
	}
	
	cout << "Create Successfully!!! Welcome Our New Member!!!\n";
	NewAccount.ReviseAccount(Creator_Name, Creator_Balance, Creator_Password);
	NewAccount.PrintAccout();
}

int LogInAccount(Account *AccountList, int AccountNumbers, Account &LoginAccount){
	int LoginNumber = 0;
	int LoginPassword = 0;
	cout << "Please Log in Your Account:\n";
	cout << "Account Number:";
	cin >> LoginNumber;
	cout << "Account Password:";
	cin >> LoginPassword;
	
	for(int i = 0; i < AccountNumbers; i++){
		if(AccountList[i].Verify(LoginNumber, LoginPassword)){
			LoginAccount = AccountList[i];
			return LoginNumber;
		}
	}
	return -1;
}

/*---------------------------------------------------------------------------------------*/

int main(){
	
	// Module Import and Something...
	srand(time(NULL)); // Fix the random seed by time.
	
	// Initialization and Data Preprocessing.

	int MaxAccountNum;
	cout << "How many member in your Bank?\n";
	cin >> MaxAccountNum;
	cout << "-------------------------------------------------------------\n";
	Account *AccountList = new Account[MaxAccountNum];
	
	for(int i = 0; i < MaxAccountNum; i++){
		CreateAccount(AccountList[i]);
	}
	
	// Login.
	int operation = -1;
	int LoginReturn = -1;
	Account LoginAccount;
	 
	while(LoginReturn == -1){
		LoginReturn = LogInAccount(AccountList, MaxAccountNum, LoginAccount);
		if(LoginReturn == -1){
			cout << "Login Failed!\n";
		}
		else{
			cout << "Login Successfully!\n";
			LoginAccount.PrintAccout();
		}
	}
	
	// Operation.
	while(true){
		cout << "Which operation do you want to do? (Please key-in the Number)\n";
		cout << "【1】Withdraw\t 【2】Deposit\t 【3】Destroy Account\t 【4】Switch Account\n";
		cin >> operation;
		if(operation == 4){
			cout << "Goodbye!\n";
			cout << "-------------------------------------------------------------\n";
		} 
		else if(operation == 1){
			int m = 0;
			cout << "How much do you wnat to Withdraw?\n";
			cin >> m;
			LoginAccount.withdraw(m);
		}
		else if(operation == 2){
			int m = 0;
			cout << "How much do you wnat to Deposit?\n";
			cin >> m;
			LoginAccount.deposit(m);
		}
		else if(operation == 3){
			cout << "Are you sure to Destroy your Account?\n (Yes -> 1 / No -> 0)";
			int flag = 0;
			cin >> flag;
			if(flag){
				LoginAccount.DestroyAccout();
			}
			else{
				operation = 0;
			}
		}
		
		if(operation == 3 || operation == 4){
			// Because the Account is destroyed or switched, let the user login again
			LoginReturn = -1;
			while(LoginReturn == -1){
				LoginReturn = LogInAccount(AccountList, MaxAccountNum, LoginAccount);
				if(LoginReturn == -1){
					cout << "Login Failed!\n";
				}
				else{
					cout << "Login Successfully!\n";
					LoginAccount.PrintAccout();
				}
			}
		}
		else{
			LoginAccount.PrintAccout();
		}
	}
	
	return 0;
}

