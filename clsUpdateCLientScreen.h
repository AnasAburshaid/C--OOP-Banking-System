#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"

class clsUpdateCLientScreen: protected clsScreen
{
private:
    static void ReadDataClient(clsBankClient& Client)
    {
        cout << "\nEnter First Name : ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter Last Name : ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email : ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone : ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter Pin Code : ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter AccountBalance : ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();

    }
public:
    static bool UpdateClient()
    {

        if (!_CheckAccessRights(clsBankUser::ePermissions::eUpdate))
        {
            return false; // exit
        }

        _DrawScreenHeader("\t Update CLient Screen");

        string AccountNumber = "";
        cout << "\nPlease Enter Client AccountNumber : ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient is not found , Choose another one : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        Client.Print();

        cout << "\nUpdate Client info : ";
        cout << "\n_______________________\n";

        cout << "\nDo you want to update at this client ?? (y/n) ";
        char c = 'Y';
        cin >> c;
        if (toupper(c) == 'Y')
        {
            ReadDataClient(Client);

            clsBankClient::enSaveResult Result;

            Result = Client.Save();

            switch (Result)
            {
            case clsBankClient::enSaveResult::svFaildEmptyProject:
            {
                cout << "\nthe file is empty error :( ";
                return false;
            }
            case clsBankClient::enSaveResult::svSucceeded:
            {
                cout << "\nAccount updated successfully :) \n";
                Client.Print();
                return  true;
            }
            }
        }
        else
        {
            cout << "Nothing Updated :) ";
            return false;
        }
        return false;
    }

};

