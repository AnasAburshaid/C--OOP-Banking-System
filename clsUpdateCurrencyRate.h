#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>
#include "clsInputValidate.h"

using namespace std;

class clsUpdateCurrencyRate : protected clsScreen
{

private:

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

public:
	static void ShowUpdateCurrenctScreen()
	{
		_DrawScreenHeader("\tUpdate Currency Screen");
		cout << "\nPlease Enter Currency Code: ";
		string CurrencyCode = clsInputValidate::ReadString();

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		if (!Currency.IsEmpty())
		{
			_Print(Currency);

			cout << "\nAre you sure you want to update the rate of " << Currency.CurrencyCode() << " Currency Rate? (y/n)? ";
			char choise = 'Y';
			cin >> choise;
			if (toupper(choise) == 'Y')
			{
				cout << "\nUpdate Currency Rate: ";
				cout << "\n______________________\n";

				cout << "Enter new Rate: ";
				float rate = clsInputValidate::ReadFloatNumber();

				Currency.UpdateRate(rate);
				cout << "\nCurrency Rate Updated Successfully : ";
				_Print(Currency);
			}
			else
				cout << "Nothing Changed...";
		}
		else
		{
			cout << "There is something wrong... ";
		}
	}

};

