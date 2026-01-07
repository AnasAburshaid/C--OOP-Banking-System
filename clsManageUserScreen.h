#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include"clsInputValidate.h"
#include "clsListUsersScreen.h"
#include"clsAddNewUserScreen.h"
#include "clsDeteletUserScreen.h"
#include "clsUpdateUserScreen.h"
#include"clsFindUserScreen.h"

class clsManageUserScreen : protected clsScreen
{
	enum enManageUserMenueOptions {
		eListUsers = 1, eAddUser = 2,
		eDeleteUser = 3, eUpdateUser = 4,
		eFindUser = 5, eMainMenue = 6
	};

	static short _ReadManageUserOptions()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short choise = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6?");

		return choise;

	}

	static void _ShowListUsersScreen()
	{
		clsListUsersScreen::ShowUserList();
	}
	static void _ShowAddUserScreen()
	{
		clsAddNewUserScreen::AddNewUserScreen();
	}
	static void _ShowDeleteUserScreen()
	{
		clsDeteletUserScreen::DeleteUserScreen();
	}
	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::UpdateUserScreen();
	}
	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::FindUserScreen();
	}
	static void _GoBakcToManageUsersMenueScreen()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Manage Users Menue...\n";

		system("pause>0");
		ShowManageUsersMenue();
	}


	static void _PerformManageUserOptions(enManageUserMenueOptions ManageUserOptions)
	{
		switch (ManageUserOptions)
		{
		case enManageUserMenueOptions::eListUsers:
		{
			system("cls");
			_ShowListUsersScreen();
			_GoBakcToManageUsersMenueScreen();
			break;
		}
		case enManageUserMenueOptions::eAddUser:
		{
			system("cls");
			_ShowAddUserScreen();
			_GoBakcToManageUsersMenueScreen();
			break;
		}
		case enManageUserMenueOptions::eDeleteUser:
		{
			system("cls");
			_ShowDeleteUserScreen();
			_GoBakcToManageUsersMenueScreen();
			break;
		}
		case enManageUserMenueOptions::eUpdateUser:
		{
			system("cls");
			_ShowUpdateUserScreen();
			_GoBakcToManageUsersMenueScreen();
			break;
		}
		case enManageUserMenueOptions::eFindUser:
		{
			system("cls");
			_ShowFindUserScreen();
			_GoBakcToManageUsersMenueScreen();
			break;
		}
		case enManageUserMenueOptions::eMainMenue:
		{
			//do nothing here 
		}
		}
	}

public:
	static void ShowManageUsersMenue()
	{
		system("cls");
		if (!_CheckAccessRights(clsBankUser::ePermissions::eManageUsersMenue))
		{
			return; // exit
		}

		_DrawScreenHeader("\t  Transaction Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Manage Users Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Users.\n";
		cout << setw(37) << left << "" << "\t[2] Add new User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformManageUserOptions(enManageUserMenueOptions(_ReadManageUserOptions()));

	}
};

