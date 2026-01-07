#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include"clsUtil.h"

using namespace std;

class clsTransferScreen : protected clsScreen
{

private:
	static void _Print(clsBankClient &Client)
	{
		cout << "\nClient Card: ";
		cout << "\n\n-------------------------------";
		cout << "\nFull Name  : " << Client.FullName();
		cout << "\nAcc. Number: " << Client.AccountNumber();
		cout << "\nBalance    : " << Client.AccountBalance;
		cout << "\n\n-------------------------------";
	}	

	static string _ReadAccountNumber(string message)
	{
		cout << message;
		string accountnumber;

		accountnumber = clsInputValidate::ReadString();

		while (!clsBankClient::IsClientExist(accountnumber))
		{
			cout << "\nClient is not found , Choose another one : ";
			accountnumber = clsInputValidate::ReadString();
		}

		return accountnumber;
	}

	static float _ReadAmount(int SourceBalance)
	{
		float amount;

		cout << "\nEnter Transfer amount: ";
		amount = clsInputValidate::ReadFloatNumber();

		if (SourceBalance < amount)
		{
			cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
			amount = clsInputValidate::ReadDblNumber();
		}

		return amount;

	}   

public:
	static void ShowTransfer()
	{
		string Accountnumber1, Accountnumber2;
		_DrawScreenHeader("\t Transfer Screen");
		 

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number to Transfer From : "));

		_Print(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number to Transfer From : "));

		_Print(DestinationClient);

		float amount = _ReadAmount(SourceClient.AccountBalance);

		cout << "\nAre you sure you want to perform this transaction? (y/n)? ";
		char choise = 'Y';
		cin >> choise;

		if (toupper(choise) == 'Y')
		{
			SourceClient.Tranfer(DestinationClient, amount,CurrentUser.UserName);
			cout << "\nTransfer done successfully\n";
		}
		else
		{
			cout << "\nNothing happened sir .. ";
		}

		_Print(SourceClient);
		_Print(DestinationClient);
	}
};

