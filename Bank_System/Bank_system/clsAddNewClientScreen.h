#pragma once
#include <iostream>
#include "clsScreen.h"
#include "BankClient.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAddNewClientScreen : protected clsScreen
{
private:

public:

    static void ShowAddNewClientScreen()
    {
        _DrawScreenHeader("\t  Add New Client Screen");

        clsBankClient::AddNewClient();
    }



};