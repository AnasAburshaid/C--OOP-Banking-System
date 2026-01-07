#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include"clsBankUser.h"
#include"clsInputValidate.h"

using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{
private:

    static void _PrintLoginRecord(clsBankUser::stLoginRegisterRecord Record)
    {
        cout << setw(8) << left << "" << "| " << setw(35) << left << Record.date;
        cout << "| " << setw(20) << left << Record.username;
        cout << "| " << setw(20) << left << Record.password;
        cout << "| " << setw(10) << left << Record.permissions;
    }

public:
	static void LoginRegisterScreen()
	{
        if (!_CheckAccessRights(clsBankUser::ePermissions::eLoginRegister))
        {
            return; // exit
        }

		vector<clsBankUser::stLoginRegisterRecord> vUsers = clsBankUser::GetLoginList();

		string Title = "Login Register list screen";
		string SubTitle = "\t    (" + to_string(vUsers.size()) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;



        if (vUsers.size() <= 0)
        {
            cout << "\nThere is no data ... EMPTY  :( ";
        }
        else
        {
            for (clsBankUser::stLoginRegisterRecord& Record : vUsers)
            {
                _PrintLoginRecord(Record);
                cout << endl;
            }

            cout << setw(8) << left << "" << "\n\t___________________________________________________________";
            cout << "______________________________________________\n" << endl;
        }
	}
};

