#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>
#include "clsInputValidate.h"
 
using namespace std;

class clsFindCurrencyScreen : protected clsScreen 
{

private:
	enum enFindMethod { FindByCode = 1, FindByCountry = 2 };

	static enFindMethod _ReadFindMethod()
	{
		cout << "\nFind By: [1] Code or [2] Country ? ";
		short FindMethod;
		FindMethod = clsInputValidate::ReadIntNumberBetween(1, 2, "Plesae Choose the method [1] or [2]: ");
		return enFindMethod(FindMethod);
	}
	static void _Print(clsCurrency Currency)
	{
		cout << "\nCurrency Card: ";
		cout << "\n\n--------------------------------\n";
		cout << "Country  :" << Currency.Country() << endl;
		cout << "Code     :" << Currency.CurrencyCode() << endl;
		cout << "Name     :" << Currency.CurrencyName() << endl;
		cout << "Rate(1$) :" << Currency.Rate();
		cout << "\n\n---------------------------------\n";
	}

	static bool _FindByName()
	{

		cout << "Please enter Country Name: ";
		string Country = clsInputValidate::ReadString();
		clsCurrency Currency = clsCurrency::FindByCountry(Country);

		if (!Currency.IsEmpty())
		{
			cout << "\n\bCurrency Found: " << endl;
			_Print(Currency);
			return true;
		}
		else
		{
			cout << "\nNot Found :( ";
			return false;
		}
	}

	static bool _FindByCode()
	{
		cout << "Please enter CurrencyCode: ";
		string CurrencyCode = clsInputValidate::ReadString();
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		if (!Currency.IsEmpty())
		{
			_DrawScreenHeader("\tFind By Country Code");
			cout << "\n\bCurrency Found: " << endl;
			_Print(Currency);
			return true;
		}
		else
		{
			cout << "\nNot Found :( ";
			return false;
		}
	}

public:

	static void ShowFindCurrencyScreen()
	{
		enFindMethod FindMethod = _ReadFindMethod();

		switch (FindMethod)
		{
		case enFindMethod::FindByCode:
		{
			system("cls");
			_FindByCode();
			break;
		}
		case enFindMethod::FindByCountry:	
		{
			system("cls");
			_FindByName();
			break;
		}
		}
	}
};

