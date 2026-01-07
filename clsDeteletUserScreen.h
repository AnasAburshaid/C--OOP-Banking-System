#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include"clsBankUser.h"
#include"clsInputValidate.h"

using namespace std;

class clsDeteletUserScreen : protected clsScreen
{
public:
	static bool DeleteUserScreen()
	{
		_DrawScreenHeader("\t Delete User Screen");
		string Username = "";
		cout << "\nPlease Enter Username : ";
		Username = clsInputValidate::ReadString();

		if (!clsBankUser::IsUserExist(Username))
		{
			cout << "\nUser with (" << Username << ") name does'nt Exists :( " << endl;
			return false;
		}
		clsBankUser User = clsBankUser::Find(Username);
		User.Print();

		cout << "\nDo you want to delete this user? (y/n) ";
		char choise = 'Y';
		cin >> choise;

		if(toupper(choise)=='Y')
		{
			clsBankUser DelUser = clsBankUser::GetDeletUserObject(Username);
			clsBankUser::enSaveResults SaveResult;

			SaveResult = DelUser.Save();

			switch (SaveResult)
			{
			case clsBankUser::enSaveResults::svSucceeded:
			{
				cout << "\nUser Deleted Successfully .";
				return true;
			}
			case clsBankUser::enSaveResults::svFaildEmptyObject:
			{
				cout << "\n There is something wrong ... ";
				return true;
			}
			}
			
		}
		else
		{
			cout << "\n\bOk sir nothing happend :) ";
			return false;
		}


	}
};

