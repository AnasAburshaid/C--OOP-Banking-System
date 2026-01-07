#pragma once
#include <iostream>
#include"clsGlobal.h"
#include"clsDate.h"
using namespace std;

class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n\n";

        clsDate CurrentDate = clsDate::GetSystemDate();
        cout << "\t\t\t\t\tUser: " << CurrentUser.UserName << endl;
        cout << "\t\t\t\t\tDate: "<<CurrentDate.GetDay()<<"/"<<CurrentDate.GetMonth()<<"/"<<CurrentDate.GetYear()<<"\n\n";
    }

    static bool _CheckAccessRights(clsBankUser::ePermissions Permission)
    {
        if (!CurrentUser.CheckAccessPermission(Permission))
        {
            cout << "\t\t\t\t\t------------------------------------------------";
            cout << "\n\n\t\t\t\t\tAccess Denied! Contact your Admin ... ";
            cout << "\n\t\t\t\t\t------------------------------------------------";
            return false;
        }
        else
            return true;
    }
};

