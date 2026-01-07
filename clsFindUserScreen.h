#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include"clsBankUser.h"
#include"clsInputValidate.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
{
public:
    static void FindUserScreen()
    {
        _DrawScreenHeader("\t Find User Screen");

        string Username = "";
        cout << "\nPlease Enter Username : ";
        Username = clsInputValidate::ReadString();

        while (!clsBankUser::IsUserExist(Username))
        {
            cout << "\nUser is not found , Choose another one : ";
            Username = clsInputValidate::ReadString();
        }

        clsBankUser User = clsBankUser::Find(Username);
        if (User.IsEmpty())
        {
            cout << "\nUser Was Not Found :( " << endl;
        }
        else
        {
            cout << "\nThe User is Found :) \n" << endl;
            cout << "\nHere is The details of the User : \n";
        }
        User.Print();
    }
};

