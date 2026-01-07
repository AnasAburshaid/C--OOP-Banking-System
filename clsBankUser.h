#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream> 
#include"clsDate.h"
#include"clsUtil.h"

const string FileName = "C:\\Users\\amjad\\OneDrive\\Desktop\\BankProject\\Users.txt";
const string FileName2 = "C:\\Users\\amjad\\OneDrive\\Desktop\\BankProject\\LoginRegester.txt";
using namespace std;
class clsBankUser : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2, DeleteUserMode = 3 };

    struct stLoginRegisterRecord;

    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;

    bool _MarkedForDelete = false;

    static clsBankUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);

        return clsBankUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5], 2) , stoi(vUserData[6]));

    }

    static stLoginRegisterRecord _ConvertLoginRecordObject(string Line, string Seperator = "#//#")
    {
        stLoginRegisterRecord LoginRecord;
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);
        
        LoginRecord.date = vUserData[0];
        LoginRecord.username = vUserData[1];
        LoginRecord.password = vUserData[2];
        LoginRecord.permissions = stoi(vUserData[3]);

        return LoginRecord;

    }

    static string _ConverUserObjectToLine(clsBankUser User, string Seperator = "#//#")
    {

        string UserRecord = "";
        UserRecord += User.FirstName + Seperator;
        UserRecord += User.LastName + Seperator;
        UserRecord += User.Email + Seperator;
        UserRecord += User.Phone + Seperator;
        UserRecord += User.UserName + Seperator;
        UserRecord += clsUtil::EncryptText(User.Password, 2) + Seperator;
        UserRecord += to_string(User.Permissions);

        return UserRecord;

    }

    static  vector <clsBankUser> _LoadUsersDataFromFile()
    {

        vector <clsBankUser> vUsers;

        fstream MyFile;
        MyFile.open(FileName, ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsBankUser User = _ConvertLinetoUserObject(Line);

                vUsers.push_back(User);
            }

            MyFile.close();

        }

        return vUsers;

    }

    static  vector <stLoginRegisterRecord> _LoadLoginUserDataFromFile()
    {

        vector <stLoginRegisterRecord> vUsers;

        fstream MyFile;
        MyFile.open(FileName2, ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                stLoginRegisterRecord Record = _ConvertLoginRecordObject(Line);

                vUsers.push_back(Record);
            }

            MyFile.close();

        }

        return vUsers;

    }

    static void _SaveUsersDataToFile(vector <clsBankUser> vUsers)
    {

        fstream MyFile;
        MyFile.open(FileName, ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankUser U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsBankUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsBankUser& U : _vUsers)
        {
            if (U.UserName == UserName)
            {
                U = *this;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    void _Delete()
    {
        vector<clsBankUser> vUsers = _LoadUsersDataFromFile();

        for (clsBankUser& User : vUsers)
        {
            if (User.UserName == UserName)
            {
                User._MarkedForDelete = true;
                break;
            }
        }
        _SaveUsersDataToFile(vUsers);

        *this = _GetEmptyUserObject();
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open(FileName, ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsBankUser _GetEmptyUserObject()
    {
        return clsBankUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    string _PrepareLoginRecord(string delim = "#//#")
    {
        string LoginRecord = "";
        LoginRecord += clsDate::GetSystemDateTimeString() + delim;
        LoginRecord += UserName + delim;
        LoginRecord += Password + delim;
        LoginRecord += to_string(Permissions);

        return LoginRecord;
    }

public:
    enum ePermissions { eFullAccess = -1, eList = 1, eAdd = 2, eDelete = 4, eUpdate = 8, eFind = 16, eTransactionsMenue = 32, eManageUsersMenue = 64,eLoginRegister = 128 };

    struct stLoginRegisterRecord {

        string username;
        string password;
        int permissions;
        string date;
    };


    clsBankUser(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string UserName, string Password,
        int Permissions) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string GetUserName()
    {
        return _UserName;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }

    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    void SetPassword(string Password)
    {
        _Password = Password;
    }

    string GetPassword()
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int GetPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

   
    static clsBankUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open(FileName, ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();

        }

        return _GetEmptyUserObject();
    }

    void Print()
    {
        cout << "\nUser Card : ";
        cout << "\n\n---------------------------";
        cout << "\nFistName   :" << FirstName;
        cout << "\nLastName   :" << LastName;
        cout << "\nFull Name  :" << FullName();
        cout << "\nEmail      :" << Email;
        cout << "\nPhone      :" << Phone;
        cout << "\nUsername   :" << UserName;
        cout << "\nPassword   :" << Password;
        cout << "\nPermission :" << Permissions;
        cout << "\n\n---------------------------";
    }


    static clsBankUser Find(string UserName, string Password)
    {

        fstream MyFile;
        MyFile.open(FileName, ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName && User.Password == Password)
                {
                    MyFile.close();
                    return User;
                }

            }

            MyFile.close();

        }
        return _GetEmptyUserObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsBankUser::IsUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _AddNew();
                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        case enMode::DeleteUserMode:
        {
            _Delete();
            return enSaveResults::svSucceeded;
        }
        }

    }

    static bool IsUserExist(string UserName)
    {

        clsBankUser User = clsBankUser::Find(UserName);
        return (!User.IsEmpty());
    }

    bool Delete()
    {
        vector <clsBankUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsBankUser& U : _vUsers)
        {
            if (U.UserName == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyUserObject();

        return true;

    }   

    static clsBankUser GetAddNewUserObject(string UserName)
    {
        return clsBankUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }
    static clsBankUser GetDeletUserObject(string UserName)
    {
        return clsBankUser(enMode::DeleteUserMode, "", "", "", "", UserName, "", 0);
    }

    static vector <clsBankUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    static vector <stLoginRegisterRecord> GetLoginList()
    {
        return _LoadLoginUserDataFromFile();
    }

    bool CheckAccessPermission(ePermissions Permission)
    {
        if (Permission == -1)
        {
            return true;
        }
        if ((this->Permissions & Permission) == Permission)
        {
            return true;
        }
        else
            return false;
    }

    void RegisterLogin()
    {
        fstream file1;
        file1.open("C:\\Users\\amjad\\OneDrive\\Desktop\\LoginRegester.txt", ios::out | ios::app);
        string Record = _PrepareLoginRecord();

        file1 << Record << endl;

        file1.close();
        
    }

};

