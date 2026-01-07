#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include"clsBankUser.h"
#include"clsInputValidate.h"

using namespace std;

class clsAddNewUserScreen: protected clsScreen
{
private:

	static void _ReadUserInfo(clsBankUser &user)
	{
		cout << "\nEnter First Name : ";
		user.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter Last Name : ";
		user.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email : ";
		user.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone : ";
		user.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password : ";
		user.Password = clsInputValidate::ReadString();

		cout << "\nEnter Permission : ";
		user.Permissions = _ReadUserPermissions();
	}

	static short _ReadUserPermissions()
	{
		short Permission = 0;

		cout << "\nDo you want to give full access? y/n?";
		char Answer = 'Y';

		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			return -1;
		}

		cout << "\ndo you want to give access to : ";
		cout << "\nShow Client list? y/n? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')	
		{
			Permission = (Permission | clsBankUser::ePermissions::eList);
		}
		cout << "\nAdd New Client? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission = (Permission | clsBankUser::ePermissions::eAdd);
		}
		cout << "\nDelete Client? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission = (Permission | clsBankUser::ePermissions::eDelete);
		}
		cout << "\nUpdate New Client? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission = (Permission | clsBankUser::ePermissions::eUpdate);
		}
		cout << "\nFind New Client? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission = (Permission | clsBankUser::ePermissions::eFind);
		}
		cout << "\nTransactions? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission = (Permission | clsBankUser::ePermissions::eTransactionsMenue);
		}
		cout << "\nManage Users? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission = (Permission | clsBankUser::ePermissions::eManageUsersMenue);
		}
		cout << "\nLogin register screen? y/n? ";
		cin >> Answer;
		if (toupper(Answer) == 'Y')
		{
			Permission = (Permission | clsBankUser::ePermissions::eLoginRegister);
		}

		return Permission;
	}

public:
	static void AddNewUserScreen()
	{
		string Username = "";
		_DrawScreenHeader("\t\ Add New User Screen");

		cout << "\nPlease enter User Name: ";
		Username = clsInputValidate::ReadString();

		while (clsBankUser::IsUserExist(Username))
		{
			cout << "\nUser with ("<<Username<<") name Exists, Enter another one : ";
			Username = clsInputValidate::ReadString();
		}
		clsBankUser NewUser = clsBankUser::GetAddNewUserObject(Username);
		_ReadUserInfo(NewUser);

		clsBankUser::enSaveResults SaveResult;

		SaveResult = NewUser.Save();

		switch (SaveResult)
		{
			case clsBankUser::enSaveResults::svSucceeded:
			{
				cout << "\nUser Saved Successfully ";
				NewUser.Print();
				break;

			}
			case clsBankUser::enSaveResults::svFaildEmptyObject:
			{
				cout << "\nAdding new User Failed ";
				break;
			}
		}

		
	}

};

