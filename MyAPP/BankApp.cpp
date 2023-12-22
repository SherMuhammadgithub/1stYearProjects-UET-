#include <iostream>  // comma separation to user name , cards type and account type has to be done
#include <windows.h> // separation of File
#include <string>
#include <iomanip>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <typeinfo>
#include <limits>
using namespace std;
HANDLE consoleHandle;
void gotoxy(int, int);

// validation Checks
int validationCheck(string, int, int);
bool commaCheck(string);
string validationForString(string, string, int, int);
int strToInt(string);

// loading headers
void userPannelLoader();
void startingLoader();

// headers of my APP
void header();
void boxContainer();
void adminHeader();
void notificationsHeader();

// Main Menus
string MainMenuForUser(string[], string[], string[], int &);
string MainMenuForAdmin();
string MainMenu();

// User Credentials Check
bool signUp(string[], string[], string[], string[], int &);
void accountCreationCheck(string[], string[], int[], int[], int &);
bool signIn(string[], string[], int &, int &);
bool accountCreation(string[], string[], int[], int[], int &);

// All functions for User
void userInformation(string[], string[], string[], string[], int &);
void accountInformation(string[], string[], int[], int &);
int seeOPtions();
void depositeMoney(string[], int[], int &, int[], int &);
void withdrawMoney(string[], int[], int &, int[], int &);
void changePassword(string[], int &);
void interestEarned(string[], int[], int &, float[]);
void zakatDeduction(string[], int[], int &, string[]);
void transferFunds(string[], int[], int &, int[], int &);
void applyForLoan(string[], int[], int &, int[], string[]);
void notifiactions(string[]);

// all funcitons for Admin
void searchUser(string userName[], string userPassword[], string DOB[], string addressOfUser[], string accountType[], string cardsOption[], int intialDeposite[], int monthlySalary[], int &userCount);
void viewAllAcounts(string[], int &);
void deleteAccount(string[], string[], string[], string[], int[], int[], int &, int &, int[]);
void vipCustomers(string[], int[], int &);
void checkForLoans(string[], int[], int[], int[], int &);
void summaryReports(int[], int &);
void changePasswordForAdmin(string[]);
void userDetails(string[], string[], string[], string[], int);
void userAccountDetails(string[], string[], int[], int[], int);
void updateInterestRates(float[]);
void transactionHistory(int[], int[], int[], int &);
int showAllNotes(string[]);
void updateNotifications(string[], float[]);

// File Handling
void saveData(string userName[], string userPassword[], string DOB[], string addressOfUser[], string accountType[], string cardsOption[], int intialDeposite[], int monthlySalary[], int loanApplied[], int depositeHistory[], int withrawalHistory[], int fundsHistory[], float interestRate[], int userCount);
void loadData(string userName[], string userPassword[], string DOB[], string addressOfUser[], string accountType[], string cardsOption[], int intialDeposite[], int monthlySalary[], int loanApplied[], int depositeHistory[], int withrawalHistory[], int fundsHistory[], float interestRate[], int &userCount);
string readField(string line, int field);
void saveBankNotes(string notes[]);
void loadBankNotes(string notes[]);

/// *** format password (on login screens)
string passwordFormat();
main()
{
    // Arrays
    string userName[100], userPassword[100], DOB[100], addressOfUser[100], accountType[100], cardsOption[100], notes[100];
    int intialDeposite[100], monthlySalary[100], loanApplied[100], depositeHistory[100], withrawalHistory[100], fundsHistory[100] = {0};
    for (int i = 0; i < 100; i++)
    {
        accountType[i] = "N/A";
        cardsOption[i] = "N/A";
    }
    float interestRate[1];

    // counter Vars
    int userCount = 0, particularUserCount, couterToTransaction = 0;
    // for suspecious activity (after 3 tries)
    int counts = 0;
    // loading all data

    loadData(userName, userPassword, DOB, addressOfUser, accountType, cardsOption, intialDeposite, monthlySalary, loanApplied, depositeHistory, withrawalHistory, fundsHistory, interestRate, userCount);
    loadBankNotes(notes);
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    startingLoader();
    Sleep(3000);
start:
    while (true)
    {

        system("cls");
        header();
        string option = MainMenu();

        if (option == "1")
        {
            system("cls");
            bool flag = signIn(userName, userPassword, particularUserCount, userCount); // 1 signIn()
            if (flag)
            {
                gotoxy(76, 32);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "Successfully logged In!" << endl;
                // cout << particularUserCount; for checking!
                Sleep(500);
                if (particularUserCount == 0) // 0 is for admin
                {
                    system("cls");
                    // sign in as admin
                    while (true)
                    {
                        system("cls");
                        string option = MainMenuForAdmin();
                        if (option == "6")
                        {
                            system("cls");
                            viewAllAcounts(userName, userCount);
                        }
                        else if (option == "1")
                        {
                            system("cls");
                            searchUser(userName, userPassword, DOB, addressOfUser, accountType, cardsOption, intialDeposite, monthlySalary, userCount);
                        }
                        else if (option == "2")
                        {
                            updateNotifications(notes, interestRate);
                        }
                        else if (option == "11")
                        {
                            system("cls");
                            goto start;
                        }
                        else if (option == "4")
                        {
                            system("cls");
                            updateInterestRates(interestRate);
                        }
                        else if (option == "5")
                        {
                            system("cls");
                            deleteAccount(userName, userPassword, accountType, cardsOption, intialDeposite, monthlySalary, userCount, particularUserCount, loanApplied);
                        }
                        else if (option == "8")
                        {
                            system("cls");
                            vipCustomers(userName, intialDeposite, userCount);
                        }
                        else if (option == "9")
                        {
                            system("cls");
                            checkForLoans(userName, monthlySalary, intialDeposite, loanApplied, userCount);
                        }
                        else if (option == "3")
                        {
                            system("cls");
                            summaryReports(intialDeposite, userCount);
                        }
                        else if (option == "7")
                        {
                            system("cls");
                            transactionHistory(depositeHistory, withrawalHistory, fundsHistory, couterToTransaction);
                        }

                        else if (option == "10")
                        {
                            system("cls");
                            changePasswordForAdmin(userPassword);
                        }
                        else
                        {
                            gotoxy(74, 39);
                            cout << "Enter a valid option!";
                        }
                        char ch;
                        gotoxy(74, 41);
                        cout << "Press any key to continue: ";
                        ch = getch();
                    }
                }
                else
                {
                    gotoxy(76, 32);
                    system("cls");
                    userPannelLoader();
                    Sleep(3000);
                    system("cls");
                    // sign in as user
                    while (true)
                    {
                        system("cls");
                        string option = MainMenuForUser(notes, accountType, userName, particularUserCount);

                        if (option == "11")
                        {
                            system("cls");
                            goto start;
                        }
                        else if (option == "4")
                        {
                            system("cls");
                            userInformation(userName, DOB, userPassword, addressOfUser, particularUserCount);
                        }
                        else if (option == "1")
                        {
                            system("cls");
                            accountCreationCheck(accountType, cardsOption, monthlySalary, intialDeposite, particularUserCount);
                        }
                        else if (option == "5")
                        {
                            system("cls");
                            accountInformation(accountType, cardsOption, intialDeposite, particularUserCount);
                        }
                        else if (option == "2")
                        {
                            system("cls");
                            depositeMoney(accountType, intialDeposite, particularUserCount, depositeHistory, couterToTransaction);
                        }
                        else if (option == "3")
                        {
                            system("cls");
                            withdrawMoney(accountType, intialDeposite, particularUserCount, withrawalHistory, couterToTransaction);
                        }
                        else if (option == "7")
                        {
                            system("cls");
                            changePassword(userPassword, particularUserCount);
                        }
                        else if (option == "9")
                        {
                            system("cls");
                            interestEarned(accountType, intialDeposite, particularUserCount, interestRate);
                        }
                        else if (option == "10")
                        {
                            system("cls");
                            zakatDeduction(accountType, intialDeposite, particularUserCount, userName);
                        }
                        else if (option == "8")
                        {
                            system("cls");
                            transferFunds(accountType, intialDeposite, particularUserCount, fundsHistory, couterToTransaction);
                        }
                        else if (option == "6")
                        {
                            system("cls");
                            applyForLoan(accountType, loanApplied, particularUserCount, monthlySalary, userName);
                        }
                        else
                        {
                            gotoxy(74, 38);
                            cout << "Enter a valid option!";
                        }
                        char ch;
                        gotoxy(74, 41);
                        cout << "Press any key to continue: ";
                        ch = getch();
                    }
                }
            }
            else
            {
                gotoxy(76, 32);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "Invalid credentials........." << endl;
                counts++; // tarcking suspecoius avtivity
                if (counts == 3)
                {
                    gotoxy(76, 34);
                    cout << "Suspecious activity detected!";
                    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
                    for (int i = 19; i >= 0; i--)
                    {
                        gotoxy(74, 36);
                        cout << "\r" << setw(80) << i << " seconds remaining  " << flush;
                        Sleep(1000);
                    }
                    counts = 0;
                }
                else
                {
                    Sleep(1500);
                    system("cls");
                }
            }
        }
        else if (option == "2")
        {
            system("cls");
            bool result = signUp(userName, userPassword, DOB, addressOfUser, userCount);
            if (result)
            {
                gotoxy(76, 38);
                cout << "A user already exit" << endl;
                Sleep(300);
                system("cls");
            }
            else
            {
                gotoxy(76, 38);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "You have been successfully Registered!" << endl;
                Sleep(1000);
                system("cls");
                userCount++; // incraesing index for next entery if the user is not alraedy there
            }
        }
        else if (option == "3")
        {
            system("cls");
            saveData(userName, userPassword, DOB, addressOfUser, accountType, cardsOption, intialDeposite, monthlySalary, loanApplied, depositeHistory, withrawalHistory, fundsHistory, interestRate, userCount);
            saveBankNotes(notes);
            // saveAdminData(userName, intialDeposite, userCount);
            exit(0);
        }
        else
        {
            gotoxy(74, 32);
            Sleep(600);
            cout << "Enter a valid option!";
        }
    }
}
void notifications(string notes[])
{
    notificationsHeader();
    int y = 14;
    for (int i = 0; i <= 3; i++)
    {
        gotoxy(144, y);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "=>" << notes[i] << endl;
        y += 2;
    }
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
string MainMenu()
{
    header();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    gotoxy(78, 10);
    cout << "+-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+";
    gotoxy(78, 11);
    cout << "|H| |o| |m| |e|   |P| |a| |g| |e|";
    gotoxy(78, 12);
    cout << "+-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+";
    boxContainer();
    gotoxy(74, 26);
    cout << "1.Login" << endl;
    gotoxy(74, 28);
    cout << "2.Regitration" << endl;
    gotoxy(74, 30);
    cout << "3.exit" << endl;
    string option;
    gotoxy(74, 34);
    cout << "Enter option: ";
    cin >> option;
    return option;
}
bool signUp(string userName[], string userPass[], string dateOfBirth[], string addressOfUsers[], int &userCount)
{
    system("cls");
    header();
    gotoxy(72, 10);
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
    cout << "+-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+";
    gotoxy(72, 11);
    cout << "|R| |e| |g| |i| |s| |t| |r| |a| |t| |i| |o| |n|";
    gotoxy(72, 12);
    cout << "+-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+";
    boxContainer();
    string pass;
    string user;
    cin.ignore();
    gotoxy(76, 26);
    userName[userCount] = validationForString(userName[userCount], "Full Name: ", 76, 26);
    dateOfBirth[userCount] = validationForString(dateOfBirth[userCount], "Date of Birth: ", 76, 28);
    addressOfUsers[userCount] = validationForString(addressOfUsers[userCount], "Address: ", 76, 30);
    userPass[userCount] = validationForString(userPass[userCount], "Password: ", 76, 32);
    user = userName[userCount];
    pass = userPass[userCount];
    bool flag;
    if (userCount > 0)
    {
        for (int i = 0; i < userCount; i++)
        {
            if (userName[i] == user)
            {
                flag = true;
                break;
            }
            else
            {
                flag = false;
            }
        }
        return flag;
    }
    else
    {
        flag = false;
        return flag;
    }
}
bool signIn(string userName[], string userPass[], int &particularUserCount, int &userCount)
{
    header();
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
    gotoxy(76, 10);
    cout << "+-+ +-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+";
    gotoxy(76, 11);
    cout << "|L| |o| |g| |i| |n|   |P| |a| |g| |e|";
    gotoxy(76, 12);
    cout << "+-+ +-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+" << endl;
    boxContainer();
    string UserN, password;
    bool flag;
    cin.ignore();
    gotoxy(76, 26);
    cout << "User Name: ";
    getline(cin, UserN);
    gotoxy(76, 28);
    cout << "User Password: ";
    password = passwordFormat();
    for (particularUserCount = 0; particularUserCount <= userCount; particularUserCount++)
    {
        if (userName[particularUserCount] == UserN && userPass[particularUserCount] == password)
        {
            flag = true;
            break;
        }
        else
        {
            flag = false;
        }
    }
    return flag;
}
// USER DASHBOARD OPTIONS
string MainMenuForUser(string notes[], string accountType[], string userName[], int &particularUserCount)
{
    header();
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
    gotoxy(69, 10);
    cout << "+-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+";
    gotoxy(69, 11);
    cout << "|U| |s| |e| |r|   |D| |a| |s| |h| |b| |o| |a| |r| |d|";
    gotoxy(69, 12);
    cout << "+-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+";
    boxContainer();
    gotoxy(76, 26);
    cout << "1.Create an Account " << endl;
    gotoxy(76, 27);
    cout << "2.Deposite Money " << endl;
    gotoxy(76, 28);
    cout << "3.Withdraw Money " << endl;
    gotoxy(76, 29);
    cout << "4.User Information " << endl;
    gotoxy(76, 30);
    cout << "5.User Account Information " << endl;
    gotoxy(76, 31);
    cout << "6.Apply for a Loan " << endl;
    gotoxy(76, 32);
    cout << "7.Change Password " << endl;
    gotoxy(76, 33);
    cout << "8.Transfer Funds " << endl;
    gotoxy(76, 34);
    cout << "9.View Interest Earned " << endl;
    gotoxy(76, 35);
    cout << "10.Zakat " << endl;
    gotoxy(76, 36);
    cout << "11.Logout " << endl;
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
    if (accountType[particularUserCount] == "savings" || accountType[particularUserCount] == "current")
    {
        gotoxy(28, 32);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "Welcome " << userName[particularUserCount] << "!" << endl;
    }
    else
    {
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        gotoxy(20, 32);
        cout << "Welcome " << userName[particularUserCount] << "!" << endl;
        gotoxy(20, 34);
        cout << "Open an Account for Further Interactions!" << endl;
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    }
    gotoxy(94, 26);
    notifications(notes);
    string option;
    gotoxy(77, 38);
    cout << "Enter your Choice: ";
    cin >> option;
    return option;
}
// user F4
void userInformation(string userName[], string DOB[], string userPassword[], string addressOfUser[], int &particularUserCount)
{
    // header();
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
    gotoxy(65, 10);
    cout << "+-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+";
    gotoxy(65, 11);
    cout << "|U| |s| |e| |r|   |I| |n| |f| |o| |r| |m| |a| |t| |i| |o| |n|";
    gotoxy(65, 12);
    cout << "+-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+";
    boxContainer();
    gotoxy(74, 26);
    cout << "Name:   " << setw(30) << userName[particularUserCount] << endl;
    gotoxy(74, 28);
    cout << "DOB:    " << setw(30) << DOB[particularUserCount] << endl;
    gotoxy(74, 30);
    cout << "PIN:    " << setw(30) << userPassword[particularUserCount] << endl;
    gotoxy(74, 32);
    cout << "Address:" << setw(30) << addressOfUser[particularUserCount] << endl
         << endl;
}
// user F1
bool accountCreation(string accountType[], string cardsOption[], int monthlySalary[], int intialDeposite[], int &particularUserCount)
{
start:
    header();
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
    gotoxy(65, 10);
    cout << "+-+ +-+ +-+ +-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+";
    gotoxy(65, 11);
    cout << "|A| |c| |c| |o| |u| |n| |t|   |C| |r| |e| |a| |t| |i| |o| |n|";
    gotoxy(65, 12);
    cout << "+-+ +-+ +-+ +-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+";
    boxContainer();
    bool flag = true;
    if (monthlySalary[particularUserCount] && intialDeposite[particularUserCount])
    {
        flag = false;
    }

    else
    {
        string account, card;
        gotoxy(73, 26);
        cout << "Account Type(s for savings or c for current): ";
        cin >> account;
        if (account == "s")
        {
            accountType[particularUserCount] = "savings";
        }
        else if (account == "c")
        {
            accountType[particularUserCount] = "current";
        }
        else
        {
            gotoxy(73, 38);
            cout << "Enter a valid option!" << endl;
            Sleep(1000);
            system("cls");
            goto start;
        }
        gotoxy(73, 28);
        cout << "Cards Options(d for Debit or c for Credit): ";
        cin >> card;
        if (card == "d")
        {
            cardsOption[particularUserCount] = "Debit";
        }
        else if (card == "c")
        {
            cardsOption[particularUserCount] = "Credit";
        }
        else
        {

            gotoxy(73, 38);
            cout << "Enter a valid option!" << endl;

            Sleep(1000);
            system("cls");
            goto start;
        }
        monthlySalary[particularUserCount] = validationCheck("Monthly Salary: $", 73, 30);
        intialDeposite[particularUserCount] = validationCheck("Intial Deposite: $", 73, 32);
    }
    return flag;
}
// check for F1
void accountCreationCheck(string accountType[], string cardsOption[], int monthlySalary[], int intialDeposite[], int &particularUserCount)
{
    bool flag = accountCreation(accountType, cardsOption, monthlySalary, intialDeposite, particularUserCount);
    if (flag)
    {
        gotoxy(73, 35);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "Welcome! " << endl;
        gotoxy(73, 36);
        cout << "Your account created successfully!" << endl
             << endl;
    }
    else
    {
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
        gotoxy(73, 26);
        cout << "Your account already exists" << endl
             << endl;
    }
}
// user F5
void accountInformation(string accountType[], string cardsOption[], int intialDeposite[], int &particularUserCount)
{
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
    gotoxy(63, 10);
    cout << "+-+ +-+ +-+ +-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+";
    gotoxy(63, 11);
    cout << "|A| |c| |c| |o| |u| |n| |t|   |I| |n| |f| |o| |r| |m| |a| |t| |i| |o| |n|";
    gotoxy(63, 12);
    cout << "+-+ +-+ +-+ +-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+";
    boxContainer();
    if (accountType[particularUserCount] == "savings" || accountType[particularUserCount] == "current")
    {
        gotoxy(74, 26);
        cout << "Account Type:  " << setw(25) << accountType[particularUserCount] << endl;
        gotoxy(74, 28);
        cout << "Card Type:     " << setw(25) << cardsOption[particularUserCount] << endl;
        gotoxy(74, 30);
        cout << "Your Balance:  " << setw(25) << intialDeposite[particularUserCount] << endl
             << endl;
    }
    else
    {
        gotoxy(74, 26);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "You Don't have any account.Make One!" << endl
             << endl;
    }
}

// options for withdraw and deposit Money (ATM approach)
int seeOPtions()
{
    gotoxy(74, 26);
    cout << "a.500 " << setw(20) << "b.1000" << endl;
    gotoxy(74, 28);
    cout << "c.1500" << setw(20) << "d.2000" << endl;
    gotoxy(74, 30);
    cout << "o.Other Amount" << endl;
    gotoxy(74, 33);
    char option;
    cout << "Enter your option: ";
    cin >> option;
    return option;
}
// user F2
void depositeMoney(string accountType[], int intialDeposite[], int &particularUserCount, int depositeHistory[], int &counterToTransaction)
{
    header();
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
    gotoxy(71, 10);
    cout << "+-+ +-+ +-+ +-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+ +-+";
    gotoxy(71, 11);
    cout << "|D| |e| |p| |o| |s| |i| |t|   |M| |o| |n| |e| |y|";
    gotoxy(71, 12);
    cout << "+-+ +-+ +-+ +-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+ +-+";
    boxContainer();
    if (accountType[particularUserCount] == "savings" || accountType[particularUserCount] == "current")
    {

        char option = seeOPtions();

        if (option == 'a')
        {
            intialDeposite[particularUserCount] += 500;
            gotoxy(74, 36);
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << "$500 has been successfully deposited!" << endl;
            depositeHistory[counterToTransaction] = 500;
            counterToTransaction++;
        }
        else if (option == 'b')
        {
            intialDeposite[particularUserCount] += 1000;

            gotoxy(74, 36);
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << "$1000 has been successfully deposited!" << endl;
            depositeHistory[counterToTransaction] = 1000;
            counterToTransaction++;
        }
        else if (option == 'c')
        {
            intialDeposite[particularUserCount] += 1500;

            gotoxy(74, 36);
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << "$1500 has been successfully deposited!" << endl;
            depositeHistory[counterToTransaction] = 1500;
            counterToTransaction++;
        }
        else if (option == 'd')
        {
            intialDeposite[particularUserCount] += 2000;

            gotoxy(74, 36);
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << "$2000 has been successfully deposited!" << endl;
            depositeHistory[counterToTransaction] = 2000;
            counterToTransaction++;
        }
        else if (option == 'o')
        {
            int otherAmount = validationCheck("Enter amount to deposite: $", 74, 35);
            // gotoxy(74, 35);
            // cout << "Enter amount to deposite: $";
            if (otherAmount >= 0 && (otherAmount < 2147483647)) // added so that user can't deposit negative amount of money
            {
                intialDeposite[particularUserCount] += otherAmount;
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                gotoxy(74, 36);
                cout << "$" << otherAmount << " has been successfully deposited!" << endl;
                depositeHistory[counterToTransaction] = otherAmount;
                counterToTransaction++;
            }
            else
            {
                gotoxy(74, 36);
                cout << "The transaction was declined...";
            }
        }
        else
        {
            gotoxy(74, 36);
            cout << "Invalid Choice";
        }
    }
    else
    {
        cout << "You Don't have any account.Make One!" << endl
             << endl;
    }
}
// user f3
void withdrawMoney(string accountType[], int intialDeposite[], int &particularUserCount, int withdrawalHistory[], int &counterToTransaction)
{
    header();
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
    gotoxy(70, 10);
    cout << "+-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+ +-+";
    gotoxy(70, 11);
    cout << "|W| |i| |t| |h| |d| |r| |a| |w|   |M| |o| |n| |e| |y|";
    gotoxy(70, 12);
    cout << "+-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+ +-+";
    boxContainer();
    if (accountType[particularUserCount] == "savings" || accountType[particularUserCount] == "current")
    {
        char option = seeOPtions();
        string recpiet;
        gotoxy(74, 35);
        cout << "Do you want Recipit (Deduct $1) [Yes/No]: ";
        cin >> recpiet;
        bool deduct = false;
        if (recpiet == "yes" || recpiet == "Yes")
        {
            deduct = true;
        }
        if (option == 'a')
        {
            if (intialDeposite[particularUserCount] >= 500)
            {
                if (deduct && intialDeposite[particularUserCount] > 500)
                {
                    intialDeposite[particularUserCount] -= 1;
                }
                intialDeposite[particularUserCount] -= 500;
                gotoxy(74, 37);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "$500 has been successfully withdrawn" << endl
                     << endl;
                withdrawalHistory[counterToTransaction] = 500;
                counterToTransaction++;
            }
            else
            {
                gotoxy(74, 37);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "You Don't have enough money!" << endl
                     << endl;
            }
        }
        else if (option == 'b')
        {
            if (intialDeposite[particularUserCount] >= 1000)
            {
                if (deduct && intialDeposite[particularUserCount] > 1000)
                {
                    intialDeposite[particularUserCount] -= 1;
                }
                intialDeposite[particularUserCount] -= 1000;
                gotoxy(74, 37);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "$1000 has been successfully withdrawn" << endl
                     << endl;
                withdrawalHistory[counterToTransaction] = 1000;
                counterToTransaction++;
            }
            else
            {
                gotoxy(74, 37);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "You Don't have enough money!" << endl
                     << endl;
            }
        }
        else if (option == 'c')
        {
            if (intialDeposite[particularUserCount] >= 1500)
            {
                if (deduct && intialDeposite[particularUserCount] > 1500)
                {
                    intialDeposite[particularUserCount] -= 1;
                }
                intialDeposite[particularUserCount] -= 1500;
                gotoxy(74, 37);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "$1500 has been successfully withdrawn" << endl
                     << endl;
                withdrawalHistory[counterToTransaction] = 1500;
                counterToTransaction++;
            }
            else
            {
                gotoxy(74, 37);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "You Don't have enough money!" << endl
                     << endl;
            }
        }
        else if (option == 'd')
        {
            if (intialDeposite[particularUserCount] >= 2000)
            {
                if (deduct && intialDeposite[particularUserCount] > 2000)
                {
                    intialDeposite[particularUserCount] -= 1;
                }
                intialDeposite[particularUserCount] -= 2000;
                gotoxy(74, 37);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "$2000 has been successfully withdrawn" << endl
                     << endl;
                withdrawalHistory[counterToTransaction] = 2000;
                counterToTransaction++;
            }
            else
            {
                gotoxy(74, 37);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "You Don't have enough money!" << endl
                     << endl;
            }
        }
        else if (option == 'o')
        {
            int otherAmount = validationCheck("Enter the amount to withdraw: $", 74, 37);
            if (intialDeposite[particularUserCount] >= otherAmount && otherAmount >= 0)
            {
                if (deduct && intialDeposite[particularUserCount] > otherAmount)
                {
                    intialDeposite[particularUserCount] -= 1;
                }
                intialDeposite[particularUserCount] -= otherAmount;
                gotoxy(74, 39);
                cout << "! " << endl;
                gotoxy(74, 40);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "$" << otherAmount << " has been successfully withdrawn" << endl;
                withdrawalHistory[counterToTransaction] = otherAmount;
                counterToTransaction++;
            }
            else
            {
                gotoxy(74, 40);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY | FOREGROUND_BLUE);
                cout << "Trasaction not completed..." << endl;
            }
        }
        else
        {
            gotoxy(74, 36);
            cout << "Invalid Option";
        }
    }
    else
    {
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "You Don't have any Account.Make One!" << endl
             << endl;
    }
}
// USER F5
void changePassword(string userPassword[], int &particularUserCount)
{
    header();
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
    gotoxy(77, 10);
    cout << "+-+ +-+ +-+ +-+ +-+ +-+   +-+ +-+ +-+";
    gotoxy(77, 11);
    cout << "|R| |E| |S| |T| |E| |T|   |P| |I| |N|";
    gotoxy(77, 12);
    cout << "+-+ +-+ +-+ +-+ +-+ +-+   +-+ +-+ +-+";
    boxContainer();
    gotoxy(74, 26);
    cout << "Prevoius PIN: " << userPassword[particularUserCount];
    cin.ignore();
    string newPass;
    newPass = validationForString(newPass, "Enter New PIN: ", 74, 28);
    string confirmPass;
    confirmPass = validationForString(confirmPass, "Confirm new PIN: ", 74, 30);
    if (newPass == confirmPass)
    {
        gotoxy(74, 33);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "The PIN successfully changed! ";
        userPassword[particularUserCount] = newPass;
    }
    else
    {
        gotoxy(74, 33);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "Confirm PIN and new PIN must match!" << endl;
        Sleep(1500);
        system("cls");
        changePassword(userPassword, particularUserCount);
    }
}
// USER F9
void interestEarned(string accountType[], int intialDeposite[], int &particularUserCount, float interestRate[])
{
    header();
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
    gotoxy(78, 10);
    cout << "+-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+";
    gotoxy(78, 11);
    cout << "|I| |N| |T| |E| |R| |E| |S| |T|";
    gotoxy(78, 12);
    cout << "+-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+";
    boxContainer();

    if (accountType[particularUserCount] == "savings" || accountType[particularUserCount] == "current")
    {

        gotoxy(74, 26);
        cout << "Interest Rate: " << interestRate[0] << "%";
        gotoxy(74, 28);
        cout << "Principal Amount: $" << intialDeposite[particularUserCount];
        float accruedInterest = (interestRate[0] * intialDeposite[particularUserCount]) / 100;
        gotoxy(74, 30);
        cout << "Accrued Interest: $" << accruedInterest;
        float totalBalanceThen = accruedInterest + intialDeposite[particularUserCount];
        gotoxy(74, 32);
        cout << "Total Balance will be: $" << totalBalanceThen;
    }
    else
    {
        gotoxy(74, 26);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "You Don't have any Account.Make One!" << endl
             << endl;
    }
}
// USER F10
void zakatDeduction(string accountType[], int intialDeposite[], int &particularUserCount, string userName[])
{
    header();
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
    gotoxy(83, 10);
    cout << "+-+ +-+ +-+ +-+ +-+";
    gotoxy(83, 11);
    cout << "|Z| |A| |K| |A| |T|";
    gotoxy(83, 12);
    cout << "+-+ +-+ +-+ +-+ +-+";
    boxContainer();
    if (accountType[particularUserCount] == "savings" || accountType[particularUserCount] == "current")
    {
        if (intialDeposite[particularUserCount] >= 50000)
        {
            float rate = 2.5;
            gotoxy(74, 26);
            cout << "Zakat Rate: " << rate << "%";
            gotoxy(74, 28);
            cout << "Principal Amount: $" << intialDeposite[particularUserCount];
            float zakakDeduction = (rate * intialDeposite[particularUserCount]) / 100;
            gotoxy(74, 30);
            cout << "Zakat Applied: $" << zakakDeduction;
            float totalBalanceThen = intialDeposite[particularUserCount] - zakakDeduction;
            gotoxy(74, 32);
            cout << "Remaining Balance will be: $" << totalBalanceThen;
        }
        else
        {
            gotoxy(74, 26);
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << "Zakat will not be applicable on you!";
            gotoxy(74, 28);
            cout << userName[particularUserCount] << " your Balaance is " << intialDeposite[particularUserCount];
            gotoxy(74, 30);
            cout << "Zakat will be applied on $50,000";
            gotoxy(74, 31);
            cout << " or more amount!";
        }
    }
    else
    {
        gotoxy(74, 26);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "You Don't have any Account.Make One!" << endl
             << endl;
    }
}
// USER F8
void transferFunds(string accountType[], int intialDeposite[], int &particularUserCount, int fundsHistory[], int &counterToTransaction)
{
start:
    header();
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
    gotoxy(68, 10);
    cout << "+-+ +-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+";
    gotoxy(68, 11);
    cout << "|F| |U| |N| |D| |S|   |T| |R| |A| |N| |S| |F| |E| |R|";
    gotoxy(68, 12);
    cout << "+-+ +-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+";
    boxContainer();
    if (accountType[particularUserCount] == "savings" || accountType[particularUserCount] == "current")
    {
        gotoxy(74, 26);
        cout << "Select trust You want to trasfer funds: ";
        gotoxy(74, 29);
        cout << "a.EDHI TRUST    " << setw(25) << "b.JDC TRUST";
        gotoxy(74, 31);
        cout << "c.AGA KHAN TRUST" << setw(25) << "d.DAR-UL-SKUN TRUST";
        gotoxy(74, 33);
        cout << "e.WAR TRUST     " << setw(25) << "f.AKHUWAT TRUST";
        string option;
        gotoxy(74, 36);
        cout << "Enter your choice: ";
        cin >> option;
        int amountToTransfer = validationCheck("Enter Amount to transfer: $", 74, 37);
        if (option == "a")
        {
            if (intialDeposite[particularUserCount] > amountToTransfer)
            {
                gotoxy(74, 39);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "$" << amountToTransfer << " has trasferred to EDHI TRUST!";
                intialDeposite[particularUserCount] -= amountToTransfer;
                fundsHistory[counterToTransaction] = amountToTransfer;
                counterToTransaction++;
            }
            else
            {
                gotoxy(74, 39);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "You Don't have enough money!";
            }
        }
        else if (option == "b")
        {
            if (intialDeposite[particularUserCount] > amountToTransfer)
            {
                gotoxy(74, 39);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "$" << amountToTransfer << " has trasferred to JDC TRUST!";
                intialDeposite[particularUserCount] -= amountToTransfer;
                fundsHistory[counterToTransaction] = amountToTransfer;
                counterToTransaction++;
            }
            else
            {
                gotoxy(74, 39);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "You Don't have enough money!";
            }
        }
        else if (option == "c")
        {
            if (intialDeposite[particularUserCount] > amountToTransfer)
            {
                gotoxy(74, 39);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "$" << amountToTransfer << " has trasferred to AGA KHAN TRUST!";
                intialDeposite[particularUserCount] -= amountToTransfer;
                fundsHistory[counterToTransaction] = amountToTransfer;
                counterToTransaction++;
            }
            else
            {
                gotoxy(74, 39);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "You Don't have enough money!";
            }
        }

        else if (option == "d")
        {
            if (intialDeposite[particularUserCount] > amountToTransfer)
            {
                gotoxy(74, 39);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "$" << amountToTransfer << " has trasferred to DARUL-SKUN TRUST!";
                intialDeposite[particularUserCount] -= amountToTransfer;
                fundsHistory[counterToTransaction] = amountToTransfer;
                counterToTransaction++;
            }
            else
            {
                gotoxy(74, 39);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "You Don't have enough money!";
            }
        }
        else if (option == "e")
        {
            if (intialDeposite[particularUserCount] > amountToTransfer)
            {
                gotoxy(74, 39);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "$" << amountToTransfer << " has trasferred to WAR TRUST!";
                intialDeposite[particularUserCount] -= amountToTransfer;
                fundsHistory[counterToTransaction] = amountToTransfer;
                counterToTransaction++;
            }
            else
            {
                gotoxy(74, 39);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "You Don't have enough money!";
            }
        }
        else if (option == "f")
        {
            if (intialDeposite[particularUserCount] > amountToTransfer)
            {
                gotoxy(74, 39);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "$" << amountToTransfer << " has trasferred to AKHUWAT TRUST!";
                intialDeposite[particularUserCount] -= amountToTransfer;
                fundsHistory[counterToTransaction] = amountToTransfer;
                counterToTransaction++;
            }
            else
            {
                gotoxy(74, 39);
                SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "You Don't have enough money!";
            }
        }
        else
        {
            gotoxy(74, 38);
            cout << "Plz Choose a Valid option!";
        }
    }
    else
    {
        gotoxy(74, 26);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "You Don't have any Account.Make One!" << endl
             << endl;
    }
}
// USER F8
void applyForLoan(string accountType[], int loanApplied[], int &particularUserCount, int monthlySalary[], string userName[])
{
start:
    header();
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN);
    gotoxy(72, 10);
    cout << "+-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+ +-+ +-+ +-+";
    gotoxy(72, 11);
    cout << "|L| |O| |A| |N|   |A| |P| |P| |L| |I| |E| |D|";
    gotoxy(72, 12);
    cout << "+-+ +-+ +-+ +-+   +-+ +-+ +-+ +-+ +-+ +-+ +-+";
    boxContainer();
    if (accountType[particularUserCount] == "savings" || accountType[particularUserCount] == "current")
    {
        if (loanApplied[particularUserCount] > 0)
        {
            gotoxy(74, 26);
            cout << "You have already applied for loan!";
        }
        else
        {
            gotoxy(74, 28);
            cout << userName[particularUserCount] << " monthly income is: $" << monthlySalary[particularUserCount];
            int loanHasApply = validationCheck("Enter the amount of Loan: $", 74, 30);
            loanApplied[particularUserCount] = loanHasApply;
            int familyMembers = validationCheck("Family memebers: ", 74, 32);
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            gotoxy(74, 34);
            cout << "Request for Loan has been sent!";
            gotoxy(74, 35);
            cout << "Wait for Administration to verify!";
        }
    }
    else
    {
        gotoxy(74, 26);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "You Don't have any Account.Make One!" << endl
             << endl;
    }
}
// ADMIN ALL OPTIONS
string MainMenuForAdmin()
{
    header();
    adminHeader();
    boxContainer();
    gotoxy(74, 26);
    cout << "1.Search User " << endl;
    gotoxy(74, 27);
    cout << "2.Upate Notifications " << endl;
    gotoxy(74, 28);
    cout << "3.Summary Reports " << endl;
    gotoxy(74, 29);
    cout << "4.Update Interest Rates " << endl;
    gotoxy(74, 30);
    cout << "5.Delete an Account " << endl;
    gotoxy(74, 31);
    cout << "6.View All Accounts" << endl;
    gotoxy(74, 32);
    cout << "7.View Transaction History" << endl;
    gotoxy(74, 33);
    cout << "8.VIP Customers" << endl;
    gotoxy(74, 34);
    cout << "9.Check For Loans" << endl;
    gotoxy(74, 35);
    cout << "10.Change Password" << endl;
    gotoxy(74, 36);
    cout << "11.logout" << endl;
    string option;
    gotoxy(74, 39);
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
    cout << "Enter your Choice: ";
    cin >> option;
    return option;
}

// ADMIN F8
void viewAllAcounts(string userName[], int &userCount)
{
    header();
    adminHeader();
    boxContainer();
    int y = 28;
    if (userCount > 1)
    {
        gotoxy(74, 26);
        cout << "All Users: ";
        for (int i = 1; i < userCount; i++)
        {
            gotoxy(74, y);
            cout << "User." << i << setw(30) << userName[i] << endl;
            y++;
        }
    }
    else
    {
        gotoxy(74, 26);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "No User found!";
    }
}
// F5 for admin
void deleteAccount(string userName[], string userPassword[], string accountType[], string cardsOption[], int intialDeposite[], int monthlySalary[], int &userCount, int &particularUserCount, int loanApplied[])
{
    header();
    adminHeader();
    boxContainer();
    int y = 28;
    if (userCount > 1)
    {
        gotoxy(74, 26);
        cout << "All Users: ";
        for (int i = 1; i < userCount; i++)
        {
            gotoxy(74, y);
            cout << i << ".User Name: " << setw(30) << userName[i];
            y++;
        }
        gotoxy(74, y + 2);
        string valueToDelete;
        cout << "Enter the userName to delete!: ";
        cin.ignore();
        getline(cin, valueToDelete);
        int i, j;
        bool flag;
        for (i = 1; i < userCount; ++i)
        {
            if (userName[i] == valueToDelete)
            {
                // Shift elements to the left to fill the gap
                for (particularUserCount = i; particularUserCount <= userCount - 1; ++particularUserCount)
                {
                    userName[particularUserCount] = userName[particularUserCount + 1];
                    userPassword[particularUserCount] = userPassword[particularUserCount + 1];
                    accountType[particularUserCount] = accountType[particularUserCount + 1];
                    intialDeposite[particularUserCount] = intialDeposite[particularUserCount + 1];
                    cardsOption[particularUserCount] = cardsOption[particularUserCount + 1];
                    loanApplied[particularUserCount] = loanApplied[particularUserCount + 1];
                }

                // Decrease the size of the array
                --userCount;
                flag = true;
                break;
            }
            else
            {
                flag = false;
            }
        }
        if (flag)
        {
            gotoxy(74, y + 4);
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << "User Deleted Successfully!";
        }
        else
        {
            gotoxy(74, y + 4);
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout << "User not Found!";
        }
    }
    else
    {
        gotoxy(74, 26);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "No User found!";
    }
}
// F8 for admin
void vipCustomers(string userName[], int intialDeposite[], int &userCount)
{
    header();
    adminHeader();
    boxContainer();
    bool flag = false;
    int y = 26;
    int j = 1;
    for (int i = 1; i <= userCount; i++)
    {
        if (intialDeposite[i] >= 50000)
        {
            flag = true;
            gotoxy(74, y);
            cout << j << ". " << userName[i] << " is a VIP user with Balance $" << intialDeposite[i];
            j++;
            y++;
        }
    }
    if (!flag)
    {
        gotoxy(74, 26);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "No User is VIP!";
    }
}

// ADMIN F9
void checkForLoans(string userName[], int monthlySalary[], int intialDeposite[], int loanApplied[], int &userCount)
{
    header();
    adminHeader();
    boxContainer();
    int y = 26;
    bool hasApplied = false;
    for (int i = 1; i <= userCount; i++)
    {
        if (loanApplied[i] > 0)
        {
            hasApplied = true;
            break;
        }
    }
    if (hasApplied)
    {
        for (int i = 1; i <= userCount; i++)
        {
            if (loanApplied[i] > 0)
            {
                gotoxy(74, y);
                cout << userName[i] << " has applied for $" << loanApplied[i];
                gotoxy(74, y + 1);
                cout << "His/Her monthly income is $" << monthlySalary[i];

                y += 2;
            }
        }
        int z = y + 2;
        string userToGiveLoan;
        gotoxy(74, z);
        cout << "Enter the User Name to give Loan: ";
        cin.ignore();
        getline(cin, userToGiveLoan);
        bool flag = false;
        for (int i = 1; i <= userCount; i++)
        {
            if (userToGiveLoan == userName[i] && loanApplied[i] > 0)
            {
                intialDeposite[i] += loanApplied[i];
                loanApplied[i] = 0;
                flag = true;
            }
        }
        if (!flag)
        {
            gotoxy(74, 39);
            cout << "Enter the correct user name!";
        }
        else
        {
            gotoxy(74, 39);
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << "Loan delivered successfully!";
        }
    }
    else
    {
        gotoxy(74, 26);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "No Loans applied!";
    }
}
// ADMIN F3
void summaryReports(int intialDeposite[], int &userCount)
{
    header();
    adminHeader();
    boxContainer();
    int allBalance = 0;
    for (int i = 1; i <= userCount; i++)
    {
        allBalance += intialDeposite[i];
    }
    gotoxy(74, 26);
    cout << "Total Registered Users: " << userCount - 1 << endl;
    gotoxy(74, 28);
    cout << "Total Balance in the Bank: "
         << "$" << allBalance << endl;
}
// ADMIN F10
void changePasswordForAdmin(string userPassword[])
{
    header();
    adminHeader();
    boxContainer();
    string pass;
    cin.ignore();
    gotoxy(74, 26);
    cout << "Enter your password: ";
    getline(cin, pass);
    if (pass == userPassword[0])
    {
        string newPassword;
        newPassword = validationForString(newPassword, "Enter New PIN: ", 74, 28);
        string confirmPassword;
        confirmPassword = validationForString(confirmPassword, "Confirm new PIN: ", 74, 30);
        if (newPassword == confirmPassword)
        {
            gotoxy(74, 32);
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << "Your Password Changed successfully" << endl;
            userPassword[0] = newPassword;
        }
        else
        {
            gotoxy(74, 32);
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout << "New Password and confirmed Password must match!" << endl;
            Sleep(1500);
            system("cls");
            changePasswordForAdmin(userPassword); // redirecting again
        }
    }
    else
    {
        gotoxy(74, 26);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "You have enetred Wrong Password!" << endl;
    }
}
// ADMIN F1
void searchUser(string userName[], string userPassword[], string DOB[], string addressOfUser[], string accountType[], string cardsOption[], int intialDeposite[], int monthlySalary[], int &userCount)
{
    header();
    adminHeader();
    boxContainer();
    string nameToSearch;
    gotoxy(74, 26);
    cout << "Enter the user name to Search: ";
    cin.ignore();
    getline(cin, nameToSearch);
    bool flag = false;
    int counter = 0;
    for (int i = 1; i <= userCount; i++)
    {
        if (userName[i] == nameToSearch)
        {
            flag = true;
            counter = i;
            break;
        }
    }
    if (flag)
    {
        gotoxy(74, 28);
        cout << "1.View User's Details " << endl;
        gotoxy(74, 30);
        cout << "2.View Uesr's Account Details" << endl;
        int choice;
        gotoxy(74, 33);
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1)
        {
            userDetails(userName, userPassword, DOB, addressOfUser, counter);
        }
        else if (choice == 2)
        {
            userAccountDetails(accountType, cardsOption, intialDeposite, monthlySalary, counter);
        }
    }
    else
    {
        gotoxy(74, 28);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "No User Found!" << endl;
    }
}
void userDetails(string userName[], string userPassword[], string DOB[], string addressOfUser[], int counter)
{
    gotoxy(74, 35);
    cout << "Name:   " << setw(30) << userName[counter] << endl;
    gotoxy(74, 36);
    cout << "DOB:    " << setw(30) << DOB[counter] << endl;
    gotoxy(74, 37);
    cout << "PIN:    " << setw(30) << userPassword[counter] << endl;
    gotoxy(74, 38);
    cout << "Address:" << setw(30) << addressOfUser[counter] << endl
         << endl;
}
void userAccountDetails(string accountType[], string cardsOption[], int intialDeposite[], int monthlySalary[], int counter)
{
    if (accountType[counter] == "savings" || accountType[counter] == "current")
    {
        gotoxy(74, 35);
        cout << "Account Type:" << setw(30) << accountType[counter] << endl;
        gotoxy(74, 36);
        cout << "Card Type:   " << setw(30) << cardsOption[counter] << endl;
        gotoxy(74, 36);
        cout << "Your Balance:" << setw(30) << intialDeposite[counter] << endl
             << endl;
    }
    else
    {
        gotoxy(74, 35);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "User has'nt yet opened Account!" << endl;
    }
}
// ADMIN F4
void updateInterestRates(float interestRate[])
{
    header();
    adminHeader();
    boxContainer();
    float prevRate;
    gotoxy(74, 26);
    cout << "Previous Interest Rate: " << interestRate[0] << "%" << endl;
    prevRate = interestRate[0];
    int newRate = validationCheck("Enter the new Rate: ", 74, 28);
    interestRate[0] = newRate;
    gotoxy(74, 30);
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "Interest Rate changed from " << prevRate << "% to " << newRate << "%" << endl;
}
// ADMIN F5
void transactionHistory(int depositeHistory[], int withrawalHistory[], int fundsHistory[], int &couterToTransaction)
{
    header();
    adminHeader();
    boxContainer();
    int y = 26;
    if (couterToTransaction > 0)
    {
        for (int i = 0; i < 100; i++)
        {
            if (withrawalHistory[i] > 0)
            {
                gotoxy(76, y);
                cout << "$" << withrawalHistory[i] << "  withdrwaed!";
                y++;
            }

            if (depositeHistory[i] > 0)
            {
                gotoxy(76, y);
                cout << "$" << depositeHistory[i] << " deposited!";
                y++;
            }

            if (fundsHistory[i] > 0)
            {
                gotoxy(76, y);
                cout << fundsHistory[i] << " Funds Trasferred!";
                y++;
            }
        }
    }
    else
    {
        gotoxy(74, 26);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "You don't have any Transaction History!";
    }
}
// ADMIN F8
int showAllNotes(string notes[])
{
    header();
    adminHeader();
    boxContainer();
    gotoxy(74, 26);
    cout << "All Notifications" << endl;
    int i = 0;
    int y = 28;
    while (notes[i] != "\0")
    {
        gotoxy(74, y);
        cout << i + 1 << "." << notes[i] << endl;
        i++;
        y++;
    }
    int option = validationCheck("Update Notifications(1-4): ", 74, y + 2);
    return option;
}
void updateNotifications(string notes[], float interestRate[])
{
    string newNote;
    int option = showAllNotes(notes);
    if (option == 1)
    {
        cin.ignore();
        notes[0] = validationForString(newNote, "Enter new Note: ", 74, 38);
        gotoxy(74, 39);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "Note changes successfully!";
    }
    else if (option == 2)
    {
        newNote = "Interst Accured is " + to_string(interestRate[0]) + "%";
        notes[1] = newNote;
        gotoxy(74, 38);
        cout << newNote;
        gotoxy(74, 39);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "Note changes successfully!";
    }
    else if (option == 3)
    {
        cin.ignore();
        notes[2] = validationForString(newNote, "Enter new Note: ", 74, 38);
        gotoxy(74, 39);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "Note changes successfully!";
    }
    else if (option == 4)
    {
        cin.ignore();
        notes[3] = validationForString(newNote, "Enter new Note: ", 74, 38);
        gotoxy(74, 39);
        SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "Note changes successfully!";
    }
    else
    {
        gotoxy(74, 36);
        cout << "Enter a valid Option";
    }
}
/// defination of anonymous pass
string passwordFormat()
{
    char singleLetter;
    string completeWord;
    while (true)
    {
        singleLetter = getch();
        if (singleLetter == '\r')
            break;
        cout << "*";
        completeWord += singleLetter;
    }
    return completeWord;
}

string readField(string line, int field)
{
    int count = 0;
    string result = "";
    for (int i = 0; line[i] != '\0'; i++)
    {
        if (line[i] != ',')
        {
            result += line[i];
        }
        else
        {
            count++;
            if (count == field)
            {
                return result;
            }
            result = "";
        }
    }
}

void saveData(string userName[], string userPassword[], string DOB[], string addressOfUser[], string accountType[], string cardsOption[], int intialDeposite[], int monthlySalary[], int loanApplied[], int depositeHistory[], int withrawalHistory[], int fundsHistory[], float interestRate[], int userCount)
{
    ofstream file;
    file.open("datas.txt");
    for (int i = 0; i < userCount; i++)
    {
        file << userName[i] << "," << userPassword[i] << "," << DOB[i] << "," << addressOfUser[i] << "," << accountType[i] << "," << cardsOption[i] << "," << intialDeposite[i] << "," << monthlySalary[i] << "," << loanApplied[i] << "," << interestRate[i];
        if (i != userCount - 1)
        {
            file << endl;
        }
    }
    file.close();
}

void loadData(string userName[], string userPassword[], string DOB[], string addressOfUser[], string accountType[], string cardsOption[], int intialDeposite[], int monthlySalary[], int loanApplied[], int depositeHistory[], int withrawalHistory[], int fundsHistory[], float interestRate[], int &userCount)
{
    string line;
    ifstream file;
    file.open("datas.txt");
    int i = 0;
    while (!file.eof())
    {
        getline(file, line);
        userName[i] = readField(line, 1);
        userPassword[i] = readField(line, 2);
        DOB[i] = readField(line, 3);
        addressOfUser[i] = readField(line, 4);
        accountType[i] = readField(line, 5);
        cardsOption[i] = readField(line, 6);
        intialDeposite[i] = strToInt(readField(line, 7));
        monthlySalary[i] = strToInt(readField(line, 8));
        loanApplied[i] = strToInt(readField(line, 9));
        interestRate[i] = strToInt(readField(line, 13));
        i++;
    }
    userCount = i;
}

int strToInt(string s)
{

    int result = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        result = result * 10 + (s[i] - '0');
    }
    return result;
}
int validationCheck(string n, int x, int y)
{
start:
    int taken = 0;
    string option;
    gotoxy(x, y);
    cout << n;
    cin.clear();
    cin >> option;
    try
    {
        taken = stoi(option);
        return taken;
    }
    catch (invalid_argument)
    {
        gotoxy(74, 39);
        cout << "Invalid Argument" << endl;
        Sleep(2000); // Wait for 2 seconds
        gotoxy(74, 39);
        cout << string(18, ' '); // Overwrite the error message with spaces to hide it
        goto start;
    }
    catch (out_of_range)
    {
        gotoxy(74, 39);
        cout << "Out of Range" << endl;
        Sleep(2000); // Wait for 2 seconds
        gotoxy(74, 39);
        cout << string(12, ' '); // Overwrite the error message with spaces to hide it
        goto start;
    }
}
bool commaCheck(string option)
{
    for (int i = 0; option[i] != '\0'; i++)
    {
        if (option[i] == ',')
        {
            return false;
            break;
        }
    }
    return true;
}
string validationForString(string option, string input, int x, int y)
{
start:
    gotoxy(x, y);
    cout << input;
    getline(cin, option);
    if (commaCheck(option))
    {
        return option;
    }
    else
    {
        gotoxy(74, 39);
        cout << "Comma is not allowed!" << endl;
        Sleep(2000);
        gotoxy(74, 39);
        cout << string(22, ' ');
        goto start;
    }
}

// saving bank notification
void saveBankNotes(string notes[])
{
    ofstream file;
    file.open("notifications.txt");
    for (int i = 0; i < 4; i++)
    {
        file << notes[i];
        if (i != 3)
        {
            file << endl;
        }
    }
    file.close();
}
// loading Bank notification
void loadBankNotes(string notes[])
{
    string line;
    ifstream file;
    file.open("notifications.txt");
    int i = 0;
    while (!file.eof())
    {
        getline(file, line);
        notes[i] = line;
        i++;
    }
    file.close();
}

// ############################### Headers ################################
void header()
{
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_RED);
    gotoxy(72, 2);
    cout << " ____    _    _   _ _  __     _    ____  ____  " << endl;
    gotoxy(72, 3);
    cout << "| __ )  / \\  | \\ | | |/ /    / \\  |  _ \\|  _ \\ " << endl;
    gotoxy(72, 4);
    cout << "|  _ \\ / _ \\ |  \\| | ' /    / _ \\ | |_) | |_) |" << endl;
    gotoxy(72, 5);
    cout << "| |_) / ___ \\| |\\  | . \\   / ___ \\|  __/|  __/ " << endl;
    gotoxy(72, 6);
    cout << "|____/_/   \\_\\_| \\_|_|\\_\\ /_/   \\_\\_|   |_|    " << endl;
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void startingLoader()
{
    system("cls"); // to remove previous content
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_BLUE | FOREGROUND_RED);
    gotoxy(44, 22);
    cout << "   ______      __    __           ____       _     __          _______                        _       __";
    gotoxy(44, 23);
    cout << "  / ____/___  / /___/ /__  ____  / __ \\_____(_)___/ /__       / ____(_)___  ____ _____  _____(_)___ _/ /";
    gotoxy(44, 24);
    cout << " / / __/ __ \\/ / __  / _ \\/ __ \\/ /_/ / ___/ / __  / _ \\     / /_  / / __ \\/ __ `/ __ \\/ ___/ / __ `/ / ";
    gotoxy(44, 25);
    cout << "/ /_/ / /_/ / / /_/ /  __/ / / / ____/ /  / / /_/ /  __/    / __/ / / / / / /_/ / / / / /__/ / /_/ / /  ";
    gotoxy(44, 26);
    cout << "\\____/\\____/_/\\__,_/\\___/_/ /_/_/   /_/  /_/\\__,_/\\___/    /_/   /_/_/ /_/\\__,_/_/ /_/\\___/_/\\__,_/_/   ";
}
void userPannelLoader()
{
    gotoxy(75, 25);
    cout << "    _____  __                    ________                   ______";
    gotoxy(75, 26);
    cout << "__  / / /___________________ ___  __ \\_____ _______________  /    ";
    gotoxy(75, 27);
    cout << "_  / / /__  ___/  _ \\_  ___/ __  /_/ /  __ `/_  __ \\  _ \\_  /     ";
    gotoxy(75, 28);
    cout << "/ /_/ / _(__  )/  __/  /     _  ____// /_/ /_  / / /  __/  /      ";
    gotoxy(75, 29);
    cout << "\\____/  /____/ \\___//_/      /_/     \\__,_/ /_/ /_/\\___//_/       ";
}
void adminHeader()
{
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    gotoxy(63, 10);
    cout << "          _____           ________                   ______                ";
    gotoxy(63, 11);
    cout << "___    |_____  /______ ______(_)______    ___  __ \\_____ _______________  /";
    gotoxy(63, 12);
    cout << "__  /| |  __  /__  __ `__ \\_  /__  __ \\   __  /_/ /  __ `/_  __ \\  _ \\_  / ";
    gotoxy(63, 13);
    cout << "_  ___ / /_/ / _  / / / / /  / _  / / /   _  ____// /_/ /_  / / /  __/  /  ";
    gotoxy(63, 14);
    cout << "/_/  |_\\__,_/  /_/ /_/ /_//_/  /_/ /_/    /_/     \\__,_/ /_/ /_/\\___//_/   ";
}
void notificationsHeader()
{
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    gotoxy(152, 8);
    cout << "ALL NOTIFICATIONS!";
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_RED);
    gotoxy(140, 10);
    cout << "+-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+";
    gotoxy(140, 11);
    cout << "|-| |-| |-| |-| |-| |-| |-| |-| |-| |-| |-|";
    gotoxy(140, 12);
    cout << "+-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+";
    gotoxy(140, 13);
    cout << "+-+                                     +-+";
    gotoxy(140, 14);
    cout << "|||                                     |||";
    gotoxy(140, 15);
    cout << "+-+                                     +-+";
    gotoxy(140, 16);
    cout << "+-+                                     +-+";
    gotoxy(140, 17);
    cout << "|||                                     |||";
    gotoxy(140, 18);
    cout << "+-+                                     +-+";
    gotoxy(140, 19);
    cout << "+-+                                     +-+";
    gotoxy(140, 20);
    cout << "|||                                     |||";
    gotoxy(140, 21);
    cout << "+-+                                     +-+";
    gotoxy(140, 22);
    cout << "+-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+";
    gotoxy(140, 23);
    cout << "|-| |-| |-| |-| |-| |-| |-| |-| |-| |-| |-|";
    gotoxy(140, 24);
    cout << "+-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+ +-+";
}
void boxContainer()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_RED);
    gotoxy(70, 19);
    cout << " ***** ***** ***** ***** ***** ***** ***** ***** *****";
    gotoxy(70, 20);
    cout << "///// ///// ///// ///// ///// ///// ///// ///// ///// ";
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    gotoxy(70, 21);
    cout << "                                                      ";
    gotoxy(70, 22);
    cout << "                                                      ";
    gotoxy(70, 23);
    cout << "                                                      ";
    gotoxy(70, 24);
    cout << " *                                                 *  ";
    gotoxy(70, 25);
    cout << "/*                                                /*  ";
    gotoxy(70, 26);
    cout << "/*                                                /*  ";
    gotoxy(70, 27);
    cout << "/                                                 /   ";
    gotoxy(70, 28);
    cout << " *                                                 *  ";
    gotoxy(70, 29);
    cout << "/*                                                /*  ";
    gotoxy(70, 30);
    cout << "/*                                                /*  ";
    gotoxy(70, 31);
    cout << "/                                                 /   ";
    gotoxy(70, 32);
    cout << " *                                                 *  ";
    gotoxy(70, 33);
    cout << "/*                                                /*  ";
    gotoxy(70, 34);
    cout << "/*                                                /*  ";
    gotoxy(70, 35);
    cout << "/                                                 /   ";
    gotoxy(70, 36);
    cout << " *                                                 *  ";
    gotoxy(70, 37);
    cout << "/*                                                /*  ";
    gotoxy(70, 38);
    cout << "/*                                                /*  ";
    gotoxy(70, 39);
    cout << "/                                                 /   ";
    gotoxy(70, 40);
    cout << " *                                                 *  ";
    gotoxy(70, 41);
    cout << "/*                                                /*  ";
    gotoxy(70, 42);
    cout << "/*                                                /*  ";
    gotoxy(70, 43);
    cout << "/                                                 /   ";
    gotoxy(70, 44);
    cout << "                                                       ";
    gotoxy(70, 45);
    cout << "             Project by SM.Tec  Companies              ";
    gotoxy(70, 46);
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_RED);
    cout << " ***** ***** ***** ***** ***** ***** ***** ***** *****";
    gotoxy(70, 47);
    cout << "///// ///// ///// ///// ///// ///// ///// ///// /////  ";
    SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
