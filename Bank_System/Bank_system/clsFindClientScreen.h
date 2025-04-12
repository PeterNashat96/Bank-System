#pragma once
#include <iostream>
#include "clsScreen.h"
#include "Person.h"
#include "BankClient.h"
#include "clsInputValidate.h"

class clsFindClientScreen : protected clsScreen
{

public:

	static void ShowFindClientScreen()
	{
		_DrawScreenHeader("\t  Find Client Screen");

		clsBankClient::FindClient();
	}
};
