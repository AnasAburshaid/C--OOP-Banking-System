#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "clsScreen.h"
#include"clsBankUser.h"

using namespace std;

class clsListUsersScreen : protected clsScreen
{
    static void _PrintUserRecord(clsBankUser User)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << User.UserName;
        cout << "| " << setw(20) << left << User.FullName();
        cout << "| " << setw(12) << left << User.Phone;
        cout << "| " << setw(25) << left << User.Email;
        cout << "| " << setw(10) << left << User.Password;
        cout << "| " << setw(12) << left << User.Permissions;

    }
public:
    static void ShowUserList()
    {
        vector<clsBankUser> vUsers = clsBankUser::GetUsersList();

        string Title = "\t  User List Screen";
        string SubTitle = "\t    (" + to_string(vUsers.size()) + ") User(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t___________________________________________________________";
        cout << "______________________________________________\n" << endl;
        cout << setw(8) << left << "" << "| " << left << setw(15) << "Username";
        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(25) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permission";
        cout << setw(8) << left << "" << "\n\t___________________________________________________________";
        cout << "______________________________________________\n" << endl;


        if (vUsers.size() <= 0)
        {
            cout << "\nThere is no data ... EMPTY  :( ";
        }
        else
        {
            for (clsBankUser& User : vUsers)
            {
                _PrintUserRecord(User);
                cout << endl;
            }

            cout << setw(8) << left << "" << "\n\t___________________________________________________________";
            cout << "______________________________________________\n" << endl;
        }

    }

};


