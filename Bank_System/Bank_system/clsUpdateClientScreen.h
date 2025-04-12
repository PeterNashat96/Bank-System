#pragma once
#include <iostream>
#include "clsScreen.h"
#include "Person.h"
#include "BankClient.h"
#include "clsInputValidate.h"

class clsUpdateClientScreen : protected clsScreen
{

public:

	static void ShowUpdateClientScreen()
	{
		_DrawScreenHeader("\t  Update Client Screen");

		clsBankClient::UpdateClient();
	}
}; 
