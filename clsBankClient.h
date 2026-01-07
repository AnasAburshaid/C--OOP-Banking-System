#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <fstream>
#include<vector>

using namespace std;

class clsBankClient : public clsPerson
{
private:
	struct stTransferLogRecord;
	enum enMode { EmptyMode = 0, UpdateMode = 1 , AddClientMode = 2 , DeleteClientMode = 4};

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkForDelete = false;

	static clsBankClient _ConvertRecordToClientObject(string Record , string Delim)
	{
	
		vector<string> vRecord = clsString::Split(Record, Delim);
		return clsBankClient(enMode::UpdateMode, vRecord[0], vRecord[1], vRecord[2], vRecord[3], vRecord[4], vRecord[5],stod(vRecord[6]));

	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _LoadClientObjectToVector()
	{
		vector<clsBankClient> vClients;

		fstream file;
		file.open("C:\\Users\\amjad\\OneDrive\\Desktop\\BankProject\\Clients.txt", ios::in);

		if (file.is_open())
		{
			string Record; 
			while (getline(file, Record))
			{
				clsBankClient Client = _ConvertRecordToClientObject(Record,"#//#");
				vClients.push_back(Client);
			}
			return vClients;
			file.close();
		}

	}


	static string _ConvertClientObjectToLine(clsBankClient Client , string delim)
	{
		string ClientRecord = "";

		ClientRecord += Client.FirstName + delim;
		ClientRecord += Client.LastName + delim;
		ClientRecord += Client.Email + delim;
		ClientRecord += Client.Phone + delim;
		ClientRecord += Client.AccountNumber() + delim;
		ClientRecord += Client.PinCode + delim;
		ClientRecord += to_string(Client.AccountBalance);

		return ClientRecord;

	}

	static void _SaveClientDataToFile(vector<clsBankClient>& vClient)
	{
		fstream file;
		file.open("C:\\Users\\amjad\\OneDrive\\Desktop\\BankProject\\Clients.txt", ios::out);

		if (file.is_open())
		{
			for (clsBankClient& client : vClient)
			{
				if (client._MarkForDelete == false)
				{
					string Record = _ConvertClientObjectToLine(client, "#//#");
					file << Record << endl;
				}
			}
			file.close();
		}

	}

	static stTransferLogRecord _TransferLogRecordPrepare(string Record, string delim)
	{
		stTransferLogRecord TransferRecord;
		vector<string> vUserData;
		vUserData = clsString::Split(Record, delim);

		TransferRecord.date = vUserData[0];
		TransferRecord.S_AccountNumber = vUserData[1];
		TransferRecord.D_AccountNumber = vUserData[2];
		TransferRecord.amount = stoi(vUserData[3]);
		TransferRecord.S_AccountBalance = stoi(vUserData[4]);
		TransferRecord.D_AccountBalance = stoi(vUserData[5]);
		TransferRecord.Username = vUserData[6];

		return TransferRecord;
	}

	static vector<stTransferLogRecord> _LoadTransferLogFromFile()
	{
		vector<stTransferLogRecord> vClients;
		fstream file;
		file.open("C:\\Users\\amjad\\OneDrive\\Desktop\\BankProject\\TransferRegister.txt", ios::in);

		if (file.is_open())
		{
			string Line;
			while (getline(file, Line))
			{
				stTransferLogRecord Record = _TransferLogRecordPrepare(Line, "#//#");
				vClients.push_back(Record);
			}
			return vClients;

			file.close();
		}

	}

	void _Update()
	{
		vector<clsBankClient> vClients = _LoadClientObjectToVector();

		for (clsBankClient& client : vClients)
		{
			if (client.AccountNumber() == AccountNumber())
			{
				client = *this;
				break;
			}
		}
		_SaveClientDataToFile(vClients);
	}

	void _AddDataLineToFile(string Line)
	{
		fstream file;
		file.open("C:\\Users\\amjad\\OneDrive\\Desktop\\BankProject\\Clients.txt", ios::out | ios::app);

		if (file.is_open())
		{
			file << Line << endl;
			file.close();
		}
	}

	void _AddClient()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this, "#//#"));
	}

	void _Delete()
	{
		vector<clsBankClient> vClient = _LoadClientObjectToVector();

		for (clsBankClient& Client : vClient)
		{
			if (Client.AccountNumber() == AccountNumber())
			{
				Client._MarkForDelete = true;
				break;
			}
		}
		_SaveClientDataToFile(vClient);

		*this = _GetEmptyClientObject();
	}

	string _TransferLogLine(clsBankClient DestinationClient, int amount, string username, string delim = "#//#")
	{
		string Line = "";

		Line += clsDate::GetSystemDateTimeString() + delim;
		Line += AccountNumber() + delim;
		Line += DestinationClient.AccountNumber() + delim;
		Line += to_string(amount) + delim;
		Line += to_string(AccountBalance) + delim;
		Line += to_string(DestinationClient.AccountBalance) + delim;
		Line += username;

		return Line;

	}

	void _TransferRegisterLog(clsBankClient DestinationClient , int amount , string username)
	{
		fstream file1;
		file1.open("C:\\Users\\amjad\\OneDrive\\Desktop\\BankProject\\TransferRegister.txt", ios::out | ios::app);

		string TranferRecord = _TransferLogLine(DestinationClient,amount,username);

		if (file1.is_open())
		{
			file1 << TranferRecord << endl;
			file1.close();
		}
	
	}




public:
	struct stTransferLogRecord
	{
		string date;
		string D_AccountNumber;
		string S_AccountNumber;
		float amount;
		float S_AccountBalance;
		float D_AccountBalance;
		string Username;
	};

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
	string AccountNumber, string PinCode, float AccountBalance) 
	:clsPerson(FirstName, LastName, Email, Phone)
	{
		this->_Mode = Mode;
		this->_AccountNumber = AccountNumber;
		this->_AccountBalance = AccountBalance;
		this->_PinCode = PinCode;

	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	string GetPinCode()
	{
		return _PinCode;
	}

	void SetPinCode(string Pincode)
	{
		_PinCode = Pincode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;


	float GetAccountBalance()
	{
		return _AccountBalance;
	}

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;


	void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << Phone;
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________\n";

	}

	static clsBankClient Find(string AccountNumber)
	{
		fstream file;
		file.open("C:\\Users\\amjad\\OneDrive\\Desktop\\BankProject\\Clients.txt", ios::in);
		vector<clsBankClient> vClient;

		if (file.is_open())
		{
			string Line;
			while (getline(file, Line))
			{
				clsBankClient Client = _ConvertRecordToClientObject(Line, "#//#");

				if (Client.AccountNumber() == AccountNumber)
				{
					file.close();
					return Client;
				}

				//to save the clients except the found one (save the rest of clients)
				vClient.push_back(Client);
			}
			file.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		fstream file;
		file.open("C:\\Users\\amjad\\OneDrive\\Desktop\\BankProject\\Clients.txt", ios::in);
		vector<clsBankClient> vClient;

		if (file.is_open())
		{
			string Line;
			while (getline(file, Line))
			{
				clsBankClient Client = _ConvertRecordToClientObject(Line, "#//#");

				if (Client.AccountNumber() == AccountNumber && Client.GetPinCode() == PinCode)
				{
					file.close();
					return Client;
				}

				//to save the clients except the found one (save the rest of clients)
				vClient.push_back(Client);
			}
			file.close();
		}
		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);
		return (!Client.IsEmpty());
		
	}

	static clsBankClient GetAddNewClientObject(string accountnumber)
	{
		return clsBankClient(enMode::AddClientMode, "", "", "", "", accountnumber, "", 0);
	}

	static clsBankClient GetDeletClientObject(string accountnumber)
	{
		return clsBankClient(enMode::DeleteClientMode, "", "", "", "", accountnumber, "", 0);
	}

	static vector<clsBankClient> GetCLientInfo()
	{
		return _LoadClientObjectToVector();
	}

	static int GetTotalBalances()
	{
		vector<clsBankClient> vClients = _LoadClientObjectToVector();
		int TotalBalnce = 0;

		for (clsBankClient& Client : vClients)
		{
			TotalBalnce += Client.GetAccountBalance();
		}

		return TotalBalnce;
	}

	enum enSaveResult { svFaildEmptyProject = 0, svSucceeded = 1 };


	bool Deposit(double number)
	{
		while (number < 0)
		{
			return false;
		}
		_AccountBalance += number;
		Save();
	}

	bool Withdraw(double number )
	{
		while (number > _AccountBalance)
		{
			return false;
		}
		_AccountBalance -= number;
		Save();
	}

	void Tranfer(clsBankClient &DestinationClient, int amount,string username)
	{
		Withdraw(amount);
		DestinationClient.Deposit(amount);
		_TransferRegisterLog(DestinationClient, amount, username);
	}

	enSaveResult Save()
	{
		switch (_Mode)
		{
			case enMode::EmptyMode:
			{ 
				return enSaveResult::svFaildEmptyProject;
			}
			case enMode::UpdateMode:
			{
				_Update();

				return enSaveResult::svSucceeded;
			}
			case enMode::AddClientMode:
			{
				if (IsClientExist(AccountNumber()))
				{
					return enSaveResult::svFaildEmptyProject;
				}
				else
				{
					_AddClient();

					//after we add we need to switch to the update mode 
					_Mode = enMode::UpdateMode;

					return enSaveResult::svSucceeded;
				}
			}
			case enMode::DeleteClientMode:
			{
				_Delete();
				return enSaveResult::svSucceeded;
			}
		}
	}

	static vector<stTransferLogRecord> GetTransferLog()
	{
		return _LoadTransferLogFromFile();
	}

};

