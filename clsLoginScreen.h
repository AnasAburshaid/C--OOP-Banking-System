#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include"clsBankUser.h"
#include"clsInputValidate.h"
#include"clsMainScreen.h"
#include"clsGlobal.h"
#include"clsDate.h"

using namespace std;

class clsLoginScreen :protected clsScreen
{	
	static bool _Login()
	{
		_DrawScreenHeader("\t    Login Screen ");
		string username, password;
		bool loginCheck = false;
		short TrailsLeft = 3;

		do {
			if (loginCheck)
			{
				TrailsLeft--;
				cout << "\ninvalid Username/Password ... ";
				cout << "\nYou have " << TrailsLeft << " Trail(s) to login.\n";
			}
			if (TrailsLeft == 0)
			{
				cout << "\nYou Have Reached your limits You got blocked.. :(\n\n";
				return false; 
			}

			cout << "\nEnter Username : ";
			username = clsInputValidate::ReadString();

			cout << "Enter Password : ";
			password = clsInputValidate::ReadString();

			//now we made golbal variable in another File called CurrectUser holding clsBankUser DataType
			CurrentUser	 = clsBankUser::Find(username, password);

			//now CurrentUser can access all of the BankUser Functions so 
			//we can know if the login is true or not by IsEmpty() funciton
			
			loginCheck = CurrentUser.IsEmpty();

		} while (loginCheck);

		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenue();
		return true;
	}

public:

	static bool ShowLoginScreen()
	{
		system("cls");
		return _Login();
	}

};

