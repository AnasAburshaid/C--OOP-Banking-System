#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>
#include "clsInputValidate.h"

using namespace std;

class clsCurrencyCalculator : protected clsScreen
{
private:

	static float _ReadAmount()
	{
		cout << "\nEnter Amount to Exchange: ";
		float Amount = 0;

		Amount = clsInputValidate::ReadFloatNumber();
		return Amount;
	}

	static void _Print(clsCurrency Currency , string Message)
	{ 
		cout << "\n " << Message << "\n";
		cout << "\n\n--------------------------------\n";
		cout << "Country  :" << Currency.Country() << endl;
		cout << "Code     :" << Currency.CurrencyCode() << endl;
		cout << "Name     :" << Currency.CurrencyName() << endl;
		cout << "Rate(1$) :" << Currency.Rate();
		cout << "\n\n---------------------------------\n";
	}

	static clsCurrency _ReadCurrency(string message)
	{
		string CurrencyCode;
		cout << message << endl;

		CurrencyCode = clsInputValidate::ReadString();
		
		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency is not found, choose another one: ";
			CurrencyCode = clsInputValidate::ReadString();
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return Currency;

	}


public:

	static void ShowCurrencyCalculatorScrren()
	{
		char Choise = 'Y';
		do {
			_DrawScreenHeader("\tCurrency Calculator Screen");

			clsCurrency Currency1 = _ReadCurrency("\nPlease enter Currency1 Code: ");
			clsCurrency Currency2 = _ReadCurrency("\nPlease enter Currency2 Code: ");
			float amount = _ReadAmount();

			_Print(Currency1, "\nConvert From: ");

			if (Currency2.CurrencyCode() == "USD")
			{
				cout << amount << Currency1.CurrencyCode() << " = " << Currency1.ConvertToUSD(amount) << "USD";
				
			}
			else{
				cout << amount << Currency1.CurrencyCode() << " = "
					<< Currency1.ConvertToAnotherCurrency(amount, Currency2) << Currency2.CurrencyCode();
			}
			
			cout << "\nDo you want to perform another calculation? (y/n)? ";
			cin >> Choise;

			if (toupper(Choise) == 'Y')
			{
				system("cls");
			}

		} while (toupper(Choise) == 'Y');
	}

};

