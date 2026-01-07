#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"


    

class clsAddClientScreen : protected clsScreen
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
    static void AddNewClient()
    {
        if (!_CheckAccessRights(clsBankUser::ePermissions::eAdd))
        {
            return; // exit
        }

        _DrawScreenHeader("\tAdd Client Screen");
        string AccountNumber = "";

        cout << "\nPlease Enter Client AccountNumber : ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with Exists, Enter another one : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

        ReadDataClient(NewClient);

        clsBankClient::enSaveResult SaveResult;

        SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResult::svFaildEmptyProject:
        {
            cout << "\nAdding new client failed :( ";
            break;
        }
        case clsBankClient::enSaveResult::svSucceeded:
        {
            cout << "\nNew Client has been added successfully :) \n";
            break;
        }
        }


    }

};

