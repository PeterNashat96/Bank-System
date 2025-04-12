#pragma once
#include <iostream>
#include <string>
#include "Person.h"
#include "clsString.h"
#include "clsInputValidate.h"
#include <vector>
#include <fstream>
#include <iomanip>

    using namespace std;
    class clsBankClient : public clsPerson
    {

    private:

        enum enMode { EmptyMode = 0, UpdateMode = 1 , AddNewMode = 2 };
        enMode _Mode;
        string _AccountNumber;
        string _PinCode;
        float _AccountBalance;
        bool _MarkedForDelete = false;

        static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
        {
            vector<string> vClientData;
            vClientData = clsString::Split(Line, Seperator);

            return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
                vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

        }

        static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
        {

            string stClientRecord = "";
            stClientRecord += Client.GetFirstName() + Seperator;
            stClientRecord += Client.GetLastName() + Seperator;
            stClientRecord += Client.GetEmail() + Seperator;
            stClientRecord += Client.GetPhone() + Seperator;
            stClientRecord += Client.AccountNumber() + Seperator;
            stClientRecord += Client.GetPinCode() + Seperator;
            stClientRecord += to_string(Client.GetAccountBalance());

            return stClientRecord;

        }

        static  vector <clsBankClient> _LoadClientsDataFromFile()
        {

            vector <clsBankClient> vClients;

            fstream MyFile;
            MyFile.open("Clients.txt", ios::in);//read Mode

            if (MyFile.is_open())
            {

                string Line;


                while (getline(MyFile, Line))
                {

                    clsBankClient Client = _ConvertLinetoClientObject(Line);

                    vClients.push_back(Client);
                }

                MyFile.close();

            }

            return vClients;

        }

        static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
        {

            fstream MyFile;
            MyFile.open("Clients.txt", ios::out);//overwrite

            string DataLine;

            if (MyFile.is_open())
            {

                for (clsBankClient C : vClients)
                {
                    if (!C.MarkedForDeleted())
                    {
                        //we only write records that are not marked for delete.  
                        DataLine = _ConverClientObjectToLine(C);
                        MyFile << DataLine << endl;

                    }

                }

                MyFile.close();

            }

        }

        void _Update()
        {
            vector <clsBankClient> _vClients;
            _vClients = _LoadClientsDataFromFile();
            for (clsBankClient& C : _vClients)
            {
                if (C.AccountNumber() == AccountNumber())
                {
                    C = *this;
                    break;
                }
            }
            _SaveCleintsDataToFile(_vClients);
        }

        void _AddDataLineToFile(string  stDataLine)
        {
            fstream MyFile;
            MyFile.open("Clients.txt", ios::out | ios::app);

            if (MyFile.is_open())
            {

                MyFile << stDataLine << endl;

                MyFile.close();
            }

        }

        static clsBankClient _GetEmptyClientObject()
        {
            return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
        }

        void _AddNew()
        {

            _AddDataLineToFile(_ConverClientObjectToLine(*this));
        }


    public:


        clsBankClient(enMode Mode, string FirstName, string LastName,
            string Email, string Phone, string AccountNumber, string PinCode,
            float AccountBalance) :
            clsPerson(FirstName, LastName, Email, Phone)

        {
            _Mode = Mode;
            _AccountNumber = AccountNumber;
            _PinCode = PinCode;
            _AccountBalance = AccountBalance;

        }

        bool IsEmpty()
        {
            return (_Mode == enMode::EmptyMode);
        }

        string AccountNumber()
        {
            return _AccountNumber;
        }

        void SetPinCode(string PinCode)
        {
            _PinCode = PinCode;
        }

        string GetPinCode()
        {
            return _PinCode;
        }

        void SetAccountBalance(float AccountBalance)
        {
            _AccountBalance = AccountBalance;
        }

        float GetAccountBalance()
        {
            return _AccountBalance;
        }
    
        bool MarkedForDeleted()
        {
            return _MarkedForDelete;
        }

        void SetMarkedForDeleted()
        {
            _MarkedForDelete = 1;
        }

        void Print()
        {
            cout << "\nClient Card:";
            cout << "\n___________________";
            cout << "\nFirstName   : " << GetFirstName();
            cout << "\nLastName    : " << GetLastName();
            cout << "\nFull Name   : " << FullName();
            cout << "\nEmail       : " << GetEmail();
            cout << "\nPhone       : " << GetPhone();
            cout << "\nAcc. Number : " << _AccountNumber;
            cout << "\nPassword    : " << _PinCode;
            cout << "\nBalance     : " << _AccountBalance;
            cout << "\n___________________\n";

        }

        static clsBankClient Find(string AccountNumber)
        {


            fstream MyFile;
            MyFile.open("Clients.txt", ios::in);//read Mode

            if (MyFile.is_open())
            {
                string Line;
                while (getline(MyFile, Line))
                {
                    clsBankClient Client = _ConvertLinetoClientObject(Line);
                    if (Client.AccountNumber() == AccountNumber)
                    {
                        MyFile.close();
                        return Client;
                    }

                }

                MyFile.close();

            }

            return _GetEmptyClientObject();
        }

        static clsBankClient Find(string AccountNumber, string PinCode)
        {

            fstream MyFile;
            MyFile.open("Clients.txt", ios::in);//read Mode

            if (MyFile.is_open())
            {
                string Line;
                while (getline(MyFile, Line))
                {
                    clsBankClient Client = _ConvertLinetoClientObject(Line);
                    if (Client.AccountNumber() == AccountNumber && Client.GetPinCode() == PinCode)
                    {
                        MyFile.close();
                        return Client;
                    }

                }

                MyFile.close();

            }
            return _GetEmptyClientObject();
        }

        static void FindClient()
        {
            string AccountNumber;
            cout << "\nPlease Enter Account Number: ";
            AccountNumber = clsInputValidate::ReadString();
            while (!clsBankClient::IsClientExist(AccountNumber))
            {
                cout << "\nAccount number is not found, choose another one: ";
                AccountNumber = clsInputValidate::ReadString();
            }

            clsBankClient Client1 = clsBankClient::Find(AccountNumber);

            Client1.Print();
        }

        enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

        enSaveResults Save()
        {
            if (_Mode == enMode::EmptyMode)
            {
                return enSaveResults::svFaildEmptyObject;
            }
            else if(_Mode == enMode::UpdateMode)
            {
                _Update();
                return enSaveResults::svSucceeded;
            }
            else if (_Mode == enMode::AddNewMode)
            {
                //This will add new record to file or database
                if (clsBankClient::IsClientExist(_AccountNumber))
                {
                    return enSaveResults::svFaildAccountNumberExists;
                }
                else
                {
                    _AddNew();
                    //We need to set the mode to update after add new
                    _Mode = enMode::UpdateMode;
                    return enSaveResults::svSucceeded;
                }

            }
        }

        void Deposit(double Amount)
        {
            _AccountBalance += Amount;
            Save();
        }

        void WithDraw(double Amount)
        {
            _AccountBalance -= Amount;
            Save();
        }

        static bool IsClientExist(string AccountNumber)
        {

            clsBankClient Client1 = clsBankClient::Find(AccountNumber);
            return (!Client1.IsEmpty());
        }

        static void ReadClientInfo(clsBankClient& Client)
        {
            cout << "\nEnter FirstName: ";
            Client.SetFirstName(clsInputValidate::ReadString());

            cout << "\nEnter LastName: ";
            Client.SetLastName(clsInputValidate::ReadString());

            cout << "\nEnter Email: ";
            Client.SetEmail(clsInputValidate::ReadString());

            cout << "\nEnter Phone: ";
            Client.SetPhone(clsInputValidate::ReadString());

            cout << "\nEnter PinCode: ";
            Client.SetPinCode(clsInputValidate::ReadString());

            cout << "\nEnter Account Balance: ";
            Client.SetAccountBalance(clsInputValidate::ReadFloatNumber());
        }

        static void UpdateClient()
        {
            string AccountNumber = "";

            cout << "\nPlease Enter client Account Number: ";
            AccountNumber = clsInputValidate::ReadString();

            while (!clsBankClient::IsClientExist(AccountNumber))
            {
                cout << "\nAccount number is not found, choose another one: ";
                AccountNumber = clsInputValidate::ReadString();
            }

            clsBankClient Client = clsBankClient::Find(AccountNumber);

            Client.Print();

            cout << "\n\nUpdate Client Info:";
            cout << "\n____________________\n";

            ReadClientInfo(Client);

            clsBankClient::enSaveResults SaveResult;
            SaveResult = Client.Save();

        }

        static void AddNewClient()
        {
            string AccountNumber = "";

            cout << "\nPlease Enter Account Number: ";
            AccountNumber = clsInputValidate::ReadString();
            while (clsBankClient::IsClientExist(AccountNumber))
            {
                cout << "\nAccount Number Is Already Used, Choose another one: ";
                AccountNumber = clsInputValidate::ReadString();
            }

            clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

            ReadClientInfo(NewClient);

            clsBankClient::enSaveResults SaveResult;
            SaveResult = NewClient.Save();

            if (SaveResult == clsBankClient::enSaveResults::svSucceeded)
            {
                cout << "\nAccount Addeded Successfully :-)\n";
                NewClient.Print();
            }

            else if(clsBankClient::enSaveResults::svFaildEmptyObject)
            {
                cout << "\nError account was not saved because it's Empty";
            }

            else if(clsBankClient::enSaveResults::svFaildAccountNumberExists)
            {
                cout << "\nError account was not saved because account number is used!\n";
            }
        }

        static clsBankClient GetAddNewClientObject(string AccountNumber)
        {
            return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
        }


        bool Delete()
        {
            vector<clsBankClient> _vClients;
            _vClients = _LoadClientsDataFromFile();
        
            for (clsBankClient& C : _vClients)
            {
                if (C.AccountNumber() == _AccountNumber)
                {
                    C._MarkedForDelete = true;
                    break;
                }

            }

            _SaveCleintsDataToFile(_vClients);

            *this = _GetEmptyClientObject();

            return true;
        }

        static void DeleteClient()
        {
            string AccountNumber = "";

            cout << "\nPlease Enter Account Number: ";
            AccountNumber = clsInputValidate::ReadString();
            while (!clsBankClient::IsClientExist(AccountNumber))
            {
                cout << "\nAccount number is not found, choose another one: ";
                AccountNumber = clsInputValidate::ReadString();
            }

            clsBankClient Client = clsBankClient::Find(AccountNumber);
            Client.Print();

            cout << "\nAre you sure you want to delete this client y/n? ";

            char Answer = 'n';
            cin >> Answer;

            if (Answer == 'y' || Answer == 'Y')
            {
                Client.Delete();
                cout << "\nClient Deleted Successfully :-)\n";
                Client.Print();
            }
        }

        static void PrintClientRecordLine(clsBankClient Client)
        {
            cout << "| " << left << setw(15) << Client.AccountNumber();
            cout << "| " << left << setw(20) << Client.FullName();
            cout << "| " << left << setw(12) << Client.GetPhone();
            cout << "| " << left << setw(20) << Client.GetEmail();
            cout << "| " << left << setw(10) << Client.GetPinCode();
            cout << "| " << left << setw(12) << Client.GetAccountBalance();
        }

        static void ShowClientsList()
        {

            vector <clsBankClient> vClients = clsBankClient::GetClientsList();

            cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
            cout << "\n_______________________________________________________";
            cout << "_________________________________________\n" << endl;

            cout << "| " << left << setw(15) << "Accout Number";
            cout << "| " << left << setw(20) << "Client Name";
            cout << "| " << left << setw(12) << "Phone";
            cout << "| " << left << setw(20) << "Email";
            cout << "| " << left << setw(10) << "Pin Code";
            cout << "| " << left << setw(12) << "Balance";
            cout << "\n_______________________________________________________";
            cout << "_________________________________________\n" << endl;

            if (vClients.size() == 0)
                cout << "\t\t\t\tNo Clients Available In the System!";
            else

                for (clsBankClient Client : vClients)
                {

                    PrintClientRecordLine(Client);
                    cout << endl;
                }

            cout << "\n_______________________________________________________";
            cout << "_________________________________________\n" << endl;
            cout << "\t\t\t\t\t   Total Balances = " << clsBankClient::GetTotalBalance() << endl;
        }

        static vector <clsBankClient> GetClientsList()
        {
            return _LoadClientsDataFromFile();
        }

        static double GetTotalBalance()
        {
            double Total = 0;
            vector<clsBankClient> _vClients = clsBankClient::GetClientsList();
            for (clsBankClient& C : _vClients)
            {
                Total += C.GetAccountBalance();
            }
            return Total;
        }
    };
