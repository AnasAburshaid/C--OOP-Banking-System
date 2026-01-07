#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include"clsBankUser.h"
#include"clsInputValidate.h"

using namespace std;
class clsUpdateUserScreen : clsScreen
{
private:
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

		return Permission;
	}

	static void _ReadUserInfo(clsBankUser& user)
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

public:
	static bool UpdateUserScreen()
	{
		_DrawScreenHeader("\t Update User Screen");
		string Username = "";
		cout << "\nPlease Enter Username : ";
		Username = clsInputValidate::ReadString();

		if (!clsBankUser::IsUserExist(Username))
		{
			cout << "\nUser with (" << Username << ") name does'nt Exists :( " << endl;;
			return false;
		}
		clsBankUser User = clsBankUser::Find(Username);
		User.Print();

		cout << "\nDo you want to update this user? (y/n) ";
		char choise = 'Y';
		cin >> choise;

		if (toupper(choise) == 'Y')
		{
			cout << "\n\nUpdate User info : ";
			cout << "\n------------------------";
			_ReadUserInfo(User);

			clsBankUser::enSaveResults SaveReslut;

			SaveReslut = User.Save();
			
			switch (SaveReslut)
			{
			case clsBankUser::enSaveResults::svSucceeded:
			{
				cout << "\nUser Updated Successfully ";
				User.Print();
				return true;
			}
			case clsBankUser::enSaveResults::svFaildEmptyObject:
			{
				cout << "\nUser didnt update, Something went wrong :( ";
				return true;
			}
			}

		}
		else
		{
			cout << "\nNothing happend sir, thanks for your time :) ";
			return false;
		}
	}
};

