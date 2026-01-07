#pragma once
#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"

class clsWithdrawScreen : protected clsScreen
{
public:
    static void ShowWithDrawScreen()
    {
        _DrawScreenHeader("Withdraw Screen");

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

        cout << "Please enter Withdraw amount? ";
        double amount = clsInputValidate::ReadDblNumber();

        char c = 'Y';
        cout << "\nAre you sure you want to perform this transactions? (y/n)? ";
        cin >> c;

        if (toupper(c) == 'Y')
        {
            if (Client.Withdraw(amount))
            {
                cout << "\nClient updated successfully . ";
                cout << "\nNew Balance is =" << Client.GetAccountBalance();
            }
            else
            {
                cout << "\nCannout withdraw, Insuffeccient Balance! ";
                cout << "amount to withdraw is : " << amount;
                cout << "\nYour Balance is : " << Client.AccountBalance;
            }
        }

    }
};

