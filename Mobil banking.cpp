/*
Author: Mulugeta M.

Description: Mimic a basic bank application that allows bankers to:
    1. Open new account
    2. Deposit funds
    3. Withdraw
    4. Transfer funds
    5. Count the number of customers the bank has
    6. The total amount of money deposited by all the customers
*/
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <string>

using namespace std;

// bank account ADT
struct BankAccount{
    int accountNumber;
    string name;
    string pas;
    double balance;
};

int getAccountNumber(){
   srand(time(NULL)); // Seed the random number generator with the current time
   return int(rand() % 100000); // Generate random number 1 - 100
}

// Bank account
BankAccount openAccount(){

    BankAccount acc;

    // Customer full name
    cout<<" Your fullname : ";
    cin>>acc.name;
    cout<<"Add new password :";
    cin>>acc.pas;
    cout<<"Confirm password :";
    cin>>acc.pas;
    //Auto generate account number
    acc.accountNumber = getAccountNumber();

    //Initial balance of 0
    acc.balance=0;

    // Show information about the newly created account
    cout<<" \nYou have successfully created a new account !!"<<endl;
    cout<<" ***Account information***"<<endl;
    cout<<" Account number: "<<acc.accountNumber<<endl;
    cout<<" Full name: "<<acc.name<<endl;

   return acc; // return the account to the caller
}

// Helper function: displays error message
void noRegisteredCustomer(){
     cout<<" You don't have register customer yet."<<endl;
     cout<<" Please register few"<<endl;
}

// Helper function: returns index of the account if found and -1 otherwise
int getCustomer(int account, BankAccount customers[], int count){
    BankAccount temp;
    for(int i=0; i < count; i++){
        if(customers[i].accountNumber == account){
            return i;
        }
    }
    return -1;
}

//Implements the deposit feature
void deposit(int account, double amount,BankAccount customers[], int count){
        int pos = getCustomer(account, customers, count);
          if(pos!=-1){
            //getCustomer(account).balance+=amount;
        customers[pos].balance+=amount;
        cout<<"\n You have successfully deposited ETB: "<< amount <<" and your new balance is ETB: "<<customers[pos].balance<<" \n Thank you for Banking with us !!"<<endl;
    }
   else
        cout<<"\n Wrong account number"<<endl;
}

//Implement the withdraw feature
void withdraw(int account, double amount, BankAccount customers[], int count){
    int pos = getCustomer(account, customers, count);
    if(pos!=-1){
        if(customers[pos].balance>= amount){
            customers[pos].balance-=amount;
            cout<<"\n Your account: "<< account << "is debited with ETB: "<< amount <<" and your current balance is ETB: "<<customers[pos].balance <<" \n Thank you for Banking with us !!"<<endl;
        }else{
            cout<<"\n Insufficient balance !"<<endl;
            cout<<" You can withdraw a maximum of: "<< customers[pos].balance<<endl;
        }
    }else
        cout<<"\n You entered wrong account number"<<endl;
}

// Implement the transfer feature
void transfer(int fromAccount, int toAccount, double amount, BankAccount customers[], int count){
    int fromPos = getCustomer(fromAccount, customers, count);
    int toPos = getCustomer(toAccount, customers, count);
    if(fromPos == -1)
        cout<<"\n The debit account: "<<fromAccount<<" not found."<<endl;
    if(toPos == -1)
        cout<<"\n The credit account: "<<toAccount<<" not found. Please try again !!"<<endl;
    else if(fromPos!=-1 && toPos!=-1){
        if(customers[fromPos].balance>= amount){
            customers[fromPos].balance-=amount;
            customers[toPos].balance+=amount;
            cout<<"\n Your account: "<< fromAccount << " is debited with ETB: "<< amount <<" and your current balance is ETB: "<<customers[fromPos].balance <<"\n Thank you for Banking with us !!"<<endl;
        }else{
            cout<<"\n Insufficient balance !"<<endl;
            cout<<" You can transfer a maximum of: "<< customers[fromPos].balance<<endl;
        }
    }
}

void balance(int account, BankAccount customers[], int count){

    int pos = getCustomer(account, customers, count);
    if(pos!=-1){
        cout<<"\n Your balance is ETB: "<<customers[pos].balance<<endl;
    }else
        cout<<"\n You entered wrong account number"<<endl;
}

double totalDeposit(BankAccount customers[], int count){
    double total=0;
    //find the sum of the money in the customers account
    for(int i=0; i<count; i++)
        total+= customers[i].balance;

    return total;
}

/*
Todo:
    1. Write it customers information into a file. You have to options here
        a. save each time new account is created or account is updated
        b. save at the time the app is exiting
    2. The app start by loading the customers data from a file
*/



int main(){

    const int SIZE=100; //Expected number of customers
    int count=0; // Number of registered customers
    BankAccount customers[SIZE]; //Data structure that holds all the customers

    int choice;
    int acc;
    double amount;
    cout<<"**********************************************"<<endl;
    cout<<"*  Welcome to ABC Bank Pseudo Bank APP    *"<<endl;
    cout<<"**********************************************"<<endl;
    do{
    cout<<"\n===========***Menu***======================="<<endl;
    cout<<" 1. Open new account"<<endl;
    cout<<" 2. Deposit"<<endl;
    cout<<" 3. Withdraw"<<endl;
    cout<<" 4. Balance"<<endl;
    cout<<" 5. Transfer "<<endl;
    cout<<" 6. Total money in the customers' account"<<endl;
    cout<<" 7. Exit "<<endl;

    cout<<"\nEnter your choice : ";
    cin>>choice;

    switch(choice){
        case 1:
            customers[count] = openAccount();
            count++;
            break;
        case 2:

            cout<<"Enter account number : ";
            cin>>acc;

            cout<<"Enter amount to deposit : ";
            cin>>amount;
            deposit(acc, amount, customers, count);
            break;

        case 3:
            cout<<"Enter account number : ";
            cin>>acc;

            cout<<"Enter amount to withdraw : ";
            cin>>amount;
            withdraw(acc, amount, customers, count);
            break;
         case 4:
            cout<<"Enter account number : ";
            cin>>acc;

            balance(acc, customers,count);
            break;
        case 5:
            cout<<"Enter from account number : ";
            cin>>acc;
            int acc2;
            cout<<"Enter to account number : ";
            cin>>acc2;
            cout<<"Enter amount to transfer : ";
            cin>>amount;
            transfer(acc, acc2, amount, customers, count);
            break;
        case 6:
             cout<<"\n\tThe total amount of money in the customers account : "<<totalDeposit(customers, count)<<endl<<endl;
            break;
         case 7:
             cout<<"\nThank you for using our app!!"<<endl;
             cout<<"App is exiting wait a moment..."<<endl<<endl;
            return 0;
            break;
        default:
            cout<<"\nWrong choice"<<endl;
            cout<<"Enter your choice again"<<endl;
            cin>>choice;
        }

    } while(choice != 7);

}