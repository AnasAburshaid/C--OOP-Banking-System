#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"

class clsFindCLientScreen : protected clsScreen
{
private:


public:
	static void ShowFindClientScrren()
	{
        if (!_CheckAccessRights(clsBankUser::ePermissions::eFind))
        {
            return; // exit
        }

        _DrawScreenHeader("\t Find CLient Screen");

        string AccountNumber = "";
        cout << "\nPlease Enter Client AccountNumber : ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient is not found , Choose another one : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        if (Client.IsEmpty())
        {
            cout << "\nCLient Was Not Found :( " << endl;
        }
        else
        {
            cout << "\nThe CLient is Found :) \n" << endl;
            cout << "\nHere is The details of the CLient : \n";
        }
        Client.Print();
	}

};

