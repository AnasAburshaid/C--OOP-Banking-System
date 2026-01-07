#pragma once
#include <iostream>
#include <string>
#include "clsString.h"
#include <vector>
#include <fstream> 
#include"clsDate.h"
#include"clsUtil.h"
#include"clsScreen.h"
#include"clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include"clsUpdateCurrencyRate.h"
#include"clsCurrencyCalculator.h"

using namespace std;


class clsCurrencyExchangeScreen : protected clsScreen
{
private:
	enum enCurrencyExchangeMenueoptions {
		eListCurrencies = 1, eFindCurrency = 2,
		eUpdateRate = 3, eCurrencyCalculator = 4,
		eMainMenue = 5
	};

	static short _ReadCurrencyExchangeOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short choise = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5?");

		return choise;

	}

	static void _ShowListCurrenciesScreen()
	{
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}
	static void _ShowFindCurrencyScrren()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}
	static void _ShowUpdateRateScreen()
	{
		clsUpdateCurrencyRate::ShowUpdateCurrenctScreen();
	}
	static void _ShowCurrencyCalculatorScreen()
	{
		clsCurrencyCalculator::ShowCurrencyCalculatorScrren();
	}
	static void _GoBackToCurrencyExchangeMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Currency Exchange Menue...\n";

		system("pause>0");
		CurrencyExchangeMenue();
	}

	static void _PerformCurrencyExchangeOptions(enCurrencyExchangeMenueoptions CurrencyExchangeOption)
	{
		switch (CurrencyExchangeOption)
		{
		case enCurrencyExchangeMenueoptions::eListCurrencies:
		{
			system("cls");
			_ShowListCurrenciesScreen();
			_GoBackToCurrencyExchangeMenue();
			break;

		}
		case enCurrencyExchangeMenueoptions::eFindCurrency:
		{
			system("cls");
			_ShowFindCurrencyScrren();
			_GoBackToCurrencyExchangeMenue();
			break;
		}
		case enCurrencyExchangeMenueoptions::eUpdateRate:
		{
			system("cls");
			_ShowUpdateRateScreen();
			_GoBackToCurrencyExchangeMenue();
			break;
		}
		case enCurrencyExchangeMenueoptions::eCurrencyCalculator:
		{
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrencyExchangeMenue();
			break;
		}
		case enCurrencyExchangeMenueoptions::eMainMenue:
		{
			//nothing
		}
		}
	}

public:
	static void CurrencyExchangeMenue()
	{
		system("cls");
		_DrawScreenHeader("\tCurrency Exchange Main Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t  Currency Exchange Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformCurrencyExchangeOptions(enCurrencyExchangeMenueoptions(_ReadCurrencyExchangeOption()));
	}

};

