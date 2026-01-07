#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream> 
#include"clsDate.h"
#include"clsUtil.h"

const string FileName3 = "C:\\Users\\amjad\\OneDrive\\Desktop\\BankProject\\Currencies.txt";

class clsCurrency
{

private:

	enum enMode { EmptyMode = 0, UpdateMode = 1 };

	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static vector<clsCurrency> _LoadDataFileToVector()
	{
		fstream file;
		file.open(FileName3, ios::in);
		vector<clsCurrency> vCurrency;

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsCurrency currency = _ConvertLineToCurrencyObject(line);
				vCurrency.push_back(currency);
			}
		}
		file.close();
		return vCurrency;
	}

	static clsCurrency _ConvertLineToCurrencyObject(string line , string delim = "#//#")
	{
		vector<string> vLine = clsString::Split(line,delim);
		return clsCurrency(enMode::UpdateMode, vLine[0], vLine[1], vLine[2], stof(vLine[3]));

	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency& Currency,string delim = "#//#")
	{
		string DataLine = "";

		DataLine += Currency.Country() + delim;
		DataLine += Currency.CurrencyCode() + delim;
		DataLine += Currency.CurrencyName() + delim;
		DataLine += to_string(Currency.Rate());

		return DataLine;
	}

	static void _SaveCurrencyDataToFile(vector<clsCurrency> &vCurrency)
	{
		fstream file;
		file.open(FileName3, ios::out);

		if (file.is_open())
		{
			string DataLine;

			for (clsCurrency& currency : vCurrency)
			{
				DataLine = _ConvertCurrencyObjectToLine(currency);
				file << DataLine << endl;
			}
			file.close();
		}
	}

	void _Update()
	{
		vector<clsCurrency> vCurrency = _LoadDataFileToVector();

		for (clsCurrency& Currency : vCurrency)
		{
			if (Currency.CurrencyCode() == CurrencyCode())
			{
				Currency = *this; // that will change the vector cause of the refrence then save that changed vector to the file
				break;
			}
		}
		_SaveCurrencyDataToFile(vCurrency);
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	float Rate()
	{
		return _Rate;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency Currency = FindByCode(CurrencyCode);
		return (!Currency.IsEmpty());
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		fstream file;
		file.open(FileName3, ios::in);

		if (file.is_open())
		{
			string line;
			while (getline(file,line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(line);

				if (Currency.CurrencyCode() == CurrencyCode)
				{
					file.close();
					return Currency;
				}
			}
		}
		//if reached here then there is no match
		return _GetEmptyCurrencyObject();

	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);

		fstream file;
		file.open(FileName3, ios::in);

		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(line);

				if (clsString::UpperAllString(Currency.Country()) == Country)
				{
					file.close();
					return Currency;
				}
			}
		}
		//if reached here then there is no match
		return _GetEmptyCurrencyObject();

	}

	static vector<clsCurrency> GetCurrenciesList()
	{
		return _LoadDataFileToVector();
	}

	float ConvertToUSD(float amount)
	{
		return (float)amount / Rate();
	}

	float ConvertToAnotherCurrency(float amount,clsCurrency &Currency2)
	{
		float AmountInUSD = ConvertToUSD(amount);

		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return (float)AmountInUSD * Currency2.Rate();

	}
};

