#pragma once

#include <iostream>
#include"clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include"clsAddClientScreen.h"
#include"clsDeleteClientScreen.h"
#include"clsUpdateCLientScreen.h"
#include"clsFindCLientScreen.h"
#include "clsTransactionsScreen.h"
#include"clsManageUserScreen.h"
#include <iomanip>
#include"clsGlobal.h"
#include"clsLoginRegisterScreen.h"
#include"clsCurrencyExchangeScreen.h"


using namespace std;

class clsMainScreen : protected clsScreen
{

    enum enMainMenueOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7, eLoginRegister = 8, eCurrencyExchange = 9, eExit = 10
    };

    static short _ReadMainMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
        short choise = clsInputValidate::ReadShortNumberBetween(1, 10,"Enter Number between 1 to 10?");

        return choise;
        
    }

    static void _ShowClientListScreen()
    {
        clsClientListScreen::ShowCLientList();
    }

    static void _AddNewCLientMenueScreen()
    {
        clsAddClientScreen::AddNewClient();
    }

    static void _DeleteClientMenueScreen()
    {
        clsDeleteClientScreen::DeleteCLient();
    }

    static void _UpdateCLientMenueScreen()
    {
        clsUpdateCLientScreen::UpdateClient();
    }

    static void _FindClientMenueScreen()
    {
        clsFindCLientScreen::ShowFindClientScrren();
    }

    static void _ShowTransactionMenueScreen()
    {
        clsTransactionsScreen::ShowTransactionsMenue();
    }

    static void _ShowManageUsersScreen()
    {
        clsManageUserScreen::ShowManageUsersMenue();
    }
    static void _ShowLoginRegisterScreen()
    {
        clsLoginRegisterScreen::LoginRegisterScreen();
    }
    static void _ShowCurrencyExchangeMenue()
    {
        clsCurrencyExchangeScreen::CurrencyExchangeMenue();
    }
    static  void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

        system("pause>0");
        ShowMainMenue();
    }

    //here we will use the global variable to make the currentuser empty
    static void _LogOutScreen()
    {
        CurrentUser = clsBankUser::Find("", "");
        //now will not found any user with " " which is current user is empty now 
        //important : we can call the login here that cause a call stack error
        //login waits the mainMenue in the stack so you cant call again the login
        //insted we will make the loop in the main function with that simple 
    }

    /*static void _ShowEndScreen()
    {
        cout << "\n\bLogging you off :)";
    }*/

    static void _PerfromMainMenueOption(enMainMenueOptions MenueOptions)
    {
        switch (MenueOptions)
        {
            case enMainMenueOptions::eListClients:
            {
                system("cls");
                _ShowClientListScreen();
                _GoBackToMainMenue();
                break;
            }
            case enMainMenueOptions::eAddNewClient:
            {
                system("cls");
                _AddNewCLientMenueScreen();
                _GoBackToMainMenue();
                break;
            }
            case enMainMenueOptions::eDeleteClient:
            {
                system("cls");
                _DeleteClientMenueScreen();
                _GoBackToMainMenue();
                break;
            }
            case enMainMenueOptions::eUpdateClient:
            {
                system("cls");
                _UpdateCLientMenueScreen();
                _GoBackToMainMenue();
                break;
            }
            case enMainMenueOptions::eFindClient:
            {
                system("cls");
                _FindClientMenueScreen();
                _GoBackToMainMenue();
                break;
            }
            case enMainMenueOptions::eShowTransactionsMenue:
            {
                system("cls");
                _ShowTransactionMenueScreen();
                _GoBackToMainMenue();
                break;
            }
            case enMainMenueOptions::eManageUsers:
            {
                system("cls");
                _ShowManageUsersScreen();
                _GoBackToMainMenue();
            }
            case enMainMenueOptions::eLoginRegister:
            {
                system("cls");
                _ShowLoginRegisterScreen();
                _GoBackToMainMenue();
                break;
            }
            case enMainMenueOptions::eCurrencyExchange:
            {
                system("cls");
                _ShowCurrencyExchangeMenue();
                _GoBackToMainMenue();
                break;
            }
            case enMainMenueOptions::eExit:
            {
                system("cls");
                _LogOutScreen();
                break;
            }

        }
    }

public:
	static void ShowMainMenue()
	{
        system("cls");
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenueOption(enMainMenueOptions(_ReadMainMenueOption()));
        
    }
};

