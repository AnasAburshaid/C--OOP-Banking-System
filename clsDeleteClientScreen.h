#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"

class clsDeleteClientScreen : protected clsScreen
{
public:
    static bool DeleteCLient()
    {
        if (!_CheckAccessRights(clsBankUser::ePermissions::eDelete))
        {
            return false; // exit
        }

        _DrawScreenHeader("\t Delete Client Screen");

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
        cout << "\n\nAre you sure you want to delete this client? (y/n) ";
        char choise = 'Y';
        cin >> choise;
        while (toupper(choise) == 'Y')
        {
            clsBankClient DelClient = clsBankClient::GetDeletClientObject(AccountNumber);

            clsBankClient::enSaveResult SaveResult;

            SaveResult = DelClient.Save();

            switch (SaveResult)
            {
            case clsBankClient::enSaveResult::svFaildEmptyProject:
            {
                cout << "Failed, the file is empty :( ";
                return false;
            }
            case clsBankClient::enSaveResult::svSucceeded:
            {
                cout << "\n\nClient Deleted successfully :) ";
                return true;
            }
            }
        }
        cout << "\nOk sir.. nothing happend :) THANKS .";
        return false;


    }

};

