#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include"clsTotalBalancesScreen.h"
#include"clsTransferScreen.h"
#include "clsTransferLogScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private:

	static short _ReadTransactionsMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short choise = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6?");

		return choise;

	}

	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}
	static void _ShowWithdrawScreen()
	{
		clsWithdrawScreen::ShowWithDrawScreen();
	}
	static void _ShowTotalBalancesScreen()
	{		
		clsTotalBalancesScreen::ShowTotalBalances();
	}
	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransfer();
	}
	static void _ShowTransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferScreen();
	}

	static void _GoBakcToTransactionMenueScreen()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Transactions Menue...\n";

		system("pause>0");
		ShowTransactionsMenue();
	}

	enum enTransactionsMenueOptions {
		eDeposit = 1, eWithDraw = 2,
		eTotalBalances = 3,eTransfer = 4,eTransferLog = 5,eMainMeue = 6
	};

	static void _PerformTransactionMenueOptions(enTransactionsMenueOptions TransactionsMenueOptions)
	{
		switch (TransactionsMenueOptions)
		{
			case enTransactionsMenueOptions::eDeposit:
			{
				system("cls");
				_ShowDepositScreen();
				_GoBakcToTransactionMenueScreen();
				break;
			}
			case enTransactionsMenueOptions::eWithDraw:
			{
				system("cls");
				_ShowWithdrawScreen();
				_GoBakcToTransactionMenueScreen();
				break;
			}
			case enTransactionsMenueOptions::eTotalBalances:
			{
				system("cls");
				_ShowTotalBalancesScreen();
				_GoBakcToTransactionMenueScreen();
				break;
			}
			case enTransactionsMenueOptions::eTransfer:
			{
				system("cls");
				_ShowTransferScreen();
				_GoBakcToTransactionMenueScreen();
				break;
			}
			case enTransactionsMenueOptions::eTransferLog:
			{
				system("cls");
				_ShowTransferLogScreen();
				_GoBakcToTransactionMenueScreen();
				break;
			}
			case enTransactionsMenueOptions::eMainMeue:
			{
				//do nothing here 
			}
		}
	}

public:
	static void ShowTransactionsMenue()
	{
		system("cls");
		if (!_CheckAccessRights(clsBankUser::ePermissions::eTransactionsMenue))
		{
			return; // exit
		}

		_DrawScreenHeader("\t  Transaction Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Transaction Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit.\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
		cout << setw(37) << left << "" << "\t[3] Total Balanaces.\n";
		cout << setw(37) << left << "" << "\t[4] Transfer.\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformTransactionMenueOptions(enTransactionsMenueOptions(_ReadTransactionsMenueOption()));

	}
};

