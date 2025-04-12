#pragma once
#include <iostream>
#include "clsScreen.h"
#include "Person.h"
#include "BankClient.h"
#include "clsInputValidate.h"

class clsDeleteClientScreen : protected clsScreen
{

  public:

	  static void ShowDeleteClientScreen()
	  {

		  _DrawScreenHeader("\t  Delete Client Screen");
	
		  clsBankClient::DeleteClient();
	  }
};