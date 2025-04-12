#pragma once
#include <iostream>
#include "clsMainScreen.h"
#include "clsScreen.h"
#include "Person.h"
#include "BankClient.h"
#include "clsInputValidate.h"

class clsTransScreen : protected clsScreen
{
private:

    enum enTransMenuOptions {enDepo = 1 , enWithdraw = 2 , enTotalBalances = 3 , enMainMenu = 4};

    static void _PerfromTransMenuOption(enTransMenuOptions TransMenuOption)
    {
        if (TransMenuOption == enTransMenuOptions::enDepo)
        {
            system("cls");
            DepoScreen();
            cout << setw(37) << left << "" << "\n\tPress any key to go back to Transactions Menu...\n";
            system("pause>0");
            ShowTransMenu();
        }
        else if (TransMenuOption == enTransMenuOptions::enWithdraw)
        {
            system("cls");
            WithDrawScreen();
            cout << setw(37) << left << "" << "\n\tPress any key to go back to Transactions Menu...\n";
            system("pause>0");
            ShowTransMenu();
        }
        else if (TransMenuOption == enTransMenuOptions::enTotalBalances)
        {
            system("cls");
            cout << "\n\n";
            cout << setw(37) << left << "" << "Total Balance of Bank : " << clsBankClient::GetTotalBalance() << '\n';
            cout << setw(37) << left << "" << "\n\tPress any key to go back to Transactions Menu...\n";
            system("pause>0");
            ShowTransMenu();
        }
        else if (TransMenuOption == enTransMenuOptions::enMainMenu)
        {
            system("cls");
        }
    }

    static short _ReadTransMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 4]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 4, "Enter Number between 1 to 4? ");
        return Choice;
    }

    static void DepoScreen()
    {
            _DrawScreenHeader("\t   Deposit Screen");

            cout << "\nPlease enter AccountNumber? ";
            string AccountNumber = clsInputValidate::ReadString();

            while (!clsBankClient::IsClientExist(AccountNumber))
            {
                cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
                AccountNumber = clsInputValidate::ReadString();
            }

            clsBankClient Client1 = clsBankClient::Find(AccountNumber);
            Client1.Print();

            double Amount = 0;
            cout << "\nPlease enter deposit amount? ";
            Amount = clsInputValidate::ReadDblNumber();

            cout << "\nAre you sure you want to perform this transaction? ";
            char Answer = 'n';
            cin >> Answer;

            if (Answer == 'Y' || Answer == 'y')
            {
                Client1.Deposit(Amount);
                cout << "\nAmount Deposited Successfully.\n";
                cout << "\nNew Balance Is: " << Client1.GetAccountBalance();

            }
            else
            {
                cout << "\nOperation was cancelled.\n";
            }
    }

    static void WithDrawScreen()
    {
        _DrawScreenHeader("\t   Withdraw Screen");

        cout << "\nPlease enter AccountNumber? ";

        string AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        Client1.Print();

        double Amount = 0;
        cout << "\nPlease enter Withdraw amount? ";
        Amount = clsInputValidate::ReadDblNumber();

        cout << "\nAre you sure you want to perform this transaction? [y:n] ";
        char Answer = 'n';
        cin >> Answer;

        if (Answer == 'Y' || Answer == 'y')
        {
            Client1.WithDraw(Amount);
            cout << "\nAmount Withdrew Successfully.\n";
            cout << "\nNew Balance Is: " << Client1.GetAccountBalance();
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
    }


public:

	static void ShowTransScreen()
	{
        clsTransScreen::ShowTransMenu();
	}
 

	static void ShowTransMenu()
	{
        system("cls");
        _DrawScreenHeader("\tTransactions Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tTransactions Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerfromTransMenuOption((enTransMenuOptions)_ReadTransMenuOption());
	}
}; 
