#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include"clsAddNewClientScreen.h"
#include"clsDeleteClientScreen.h"
#include"clsUpdateClientScreen.h"
#include"clsFindClientScreen.h"
#include"clsTransScreen.h"

using namespace std;

class cLsMainScreen : protected clsScreen
{


private:

    enum enMainMenuOptions
    {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenu = 6,
        eManageUsers = 7, eExit = 8
    };

    static short _ReadMainMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static  void _GoBackToMainMenu()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menu...\n";
        system("pause>0");
        ShowMainMenu();
    }

    static void _ShowAllClientsScreen()
    {
        clsBankClient::ShowClientsList();
    }

    static void _ShowAddNewClientsScreen()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();

    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenu()
    {
        clsTransScreen::ShowTransScreen();
    }

    static void _ShowManageUsersMenu()
    {
        cout << "\nUsers Menu Will be here...\n";

    }

    static void _ShowEndScreen()
    {
        cout << "\nEnd Screen Will be here...\n";

    }

    static void _PerfromMainMenuOption(enMainMenuOptions MainMenuOption)
    {
        if (MainMenuOption == enMainMenuOptions::eListClients)
        {
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenu();
        }
        else if (MainMenuOption == enMainMenuOptions::eAddNewClient)
        {
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenu();
        }
        else if (MainMenuOption == enMainMenuOptions::eDeleteClient)
        {
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenu();
        }
        else if (MainMenuOption == enMainMenuOptions::eUpdateClient)
        {
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenu();
        }
        else if (MainMenuOption == enMainMenuOptions::eFindClient)
        {
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenu();
        }
        else if (MainMenuOption == enMainMenuOptions::eShowTransactionsMenu)
        {
            system("cls");
            _ShowTransactionsMenu();
            _GoBackToMainMenu();
        }
        else if (MainMenuOption == enMainMenuOptions::eManageUsers)
        {
            system("cls");
            _ShowManageUsersMenu();
        }
        else if (MainMenuOption == enMainMenuOptions::eExit)
        {
            system("cls");
            _ShowEndScreen();
        }
    }


public:


    static void ShowMainMenu()
    {

        system("cls");
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenuOption((enMainMenuOptions)_ReadMainMenuOption());
    }

};

