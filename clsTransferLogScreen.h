#pragma once


#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include"clsUtil.h"

using namespace std;

class clsTransferLogScreen : protected clsScreen
{
private:
	static void _PrintTransferLog(clsBankClient::stTransferLogRecord Record)
	{
		cout << setw(8) << left << "" << "| " << setw(35) << left << Record.date;
		cout << "| " << setw(15) << left << Record.S_AccountNumber;
		cout << "| " << setw(15) << left << Record.D_AccountNumber;
		cout << "| " << setw(15) << left << Record.amount;
		cout << "| " << setw(20) << left << Record.S_AccountBalance;
		cout << "| " << setw(20) << left << Record.D_AccountBalance;
		cout << "| " << setw(20) << left << Record.Username;

	}
public:

	static void ShowTransferScreen()
	{
		vector < clsBankClient::stTransferLogRecord> vClients = clsBankClient::GetTransferLog();

		string Title = "Transfer Log List screen";
		string SubTitle = "\t    (" + to_string(vClients.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);
		 
		cout << setw(8) << left << "" << "\n\t_________________________________________________________________________________________";
		cout << "_________________________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
		cout << "| " << left << setw(15) << "s.Acct";
		cout << "| " << left << setw(15) << "d.Acct";
		cout << "| " << left << setw(15) << "Amount";
		cout << "| " << left << setw(20) << "s.Balance";
		cout << "| " << left << setw(20) << "d.Balance";
		cout << "| " << left << setw(20) << "User";
		cout << setw(8) << left << "" << "\n\t_________________________________________________________________________________________";
		cout << "_________________________________________________________\n" << endl;

		if (vClients.size() <= 0)
		{
			cout << "\nThere is no data ... EMPTY  :( ";
		}
		else
		{
			for (clsBankClient::stTransferLogRecord & Record : vClients)
			{
				_PrintTransferLog(Record);
				cout << endl;
			}

			cout << setw(8) << left << "" << "\n\t_________________________________________________________________________________________";
			cout << "_________________________________________________________\n" << endl;
		}
	}
};

