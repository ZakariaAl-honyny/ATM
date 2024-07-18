
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

struct stClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0;
	bool MarkForDelete = false;
};

enum enMainMenueOptions
{
	eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposit = 3, eCheckBalance = 4, eLogout = 5
};

const string ClientsFileName = "Clients.txt";
stClient CurrentClient;

void ShowNormalWithdrawScreen();
void ShowQuickWithdrawScreen();
void ShowMainMenue();
void Login();

vector<string> SplitString(string S1, string delimiter = " ")
{
	vector<string> vString;

	short Pos = 0;
	string sWord; // define a string variable

	// use find() function to get the position of the delimiter
	while ((Pos = short(S1.find(delimiter))) != std::string::npos)
	{
		sWord = S1.substr(0, Pos); // store the word
		if (sWord != "")
		{
			vString.push_back(sWord);
		}

		S1.erase(0, Pos + delimiter.length()); // erase() until position and move to next word.
	}

	if (S1 != "")
	{
		vString.push_back(S1);// it push last word of the string
	}

	return vString;

}

stClient ConvertClintLineToRecord(string Line, string Sperator = "#//#")
{
	stClient Client;
	vector<string> vClientData;

	vClientData = SplitString(Line, Sperator);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);// cast string to double

	return Client;
}
string ConvertClientRecordToLine(stClient Client, string Sperator = "#//#")
{
	string stClientRecord = "";

	stClientRecord += Client.AccountNumber + Sperator;
	stClientRecord += Client.PinCode + Sperator;
	stClientRecord += Client.Name + Sperator;
	stClientRecord += Client.Phone + Sperator;
	stClientRecord += to_string(Client.AccountBalance);

	return stClientRecord;
}

vector<stClient> LoadClientsDataFromFile(string FileName)
{
	vector<stClient> vClients;
	fstream MyFile;

	MyFile.open(FileName, ios::in); // Read Mode

	if (MyFile.is_open())
	{
		string Line;
		stClient Client;

		while (getline(MyFile, Line))
		{

			Client = ConvertClintLineToRecord(Line);

			vClients.push_back(Client);
		}

		MyFile.close();
	}

	return vClients;
}

void PrintClintRecordLine(stClient Client)
{

	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;

}
void PrintClientCard(stClient Client)
{
	cout << "\nThe Folloing are the client details:\n";
	cout << "---------------------------------";
	cout << "\nAccount Number : " << Client.AccountNumber;
	cout << "\nPinCode        : " << Client.PinCode;
	cout << "\nName           : " << Client.Name;
	cout << "\nPhone          : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << "\n---------------------------------\n";
}

bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, stClient& Client)
{
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	for (stClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
		{
			Client = C;
			return true;
		}
	}
	return false;

}

vector<stClient> SaveClientsDataToFile(string FileName, vector<stClient> vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out); // overWrite

	string DataLine = "";

	if (MyFile.is_open())
	{


		for (stClient& Client : vClients)
		{
			if (Client.MarkForDelete == false)
			{
				//we only write records that are not marked for delete

				DataLine = ConvertClientRecordToLine(Client);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}

	return vClients;
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<stClient>& vClients)
{

	char Answer = 'n';

	cout << "\n\nAre you sure you want perform this transaction?? Y/N ? ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{

		for (stClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveClientsDataToFile(ClientsFileName, vClients);
				cout << "\n\nDone Successfully, your new balance is: " << C.AccountBalance << endl;

				return true;
			}
		}

		return false;
	}
	return false;
}

double ReadDepositAmount()
{
	double Amount = 0;
	do
	{
		cout << "\nEnter a positive Deposit Amount? ";
		cin >> Amount;

	} while (Amount <= 0);
	
	return Amount;
}

void PerfromDepositOption()
{
	double DepositAmount = ReadDepositAmount();
	
	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, DepositAmount, vClients);
	CurrentClient.AccountBalance += DepositAmount;

}

void ShowCheckClientBalance()
{
	cout << "\n------------------------------------------\n";
	cout << "\t\tCheck Balance Screen";
	cout << "\n------------------------------------------\n";

	cout << "Your Balance is: " << CurrentClient.AccountBalance << "\n";
}

void ShowDepositScreen()
{
	cout << "\n------------------------------------------\n";
	cout << "\t\tDeposit Screen";
	cout << "\n------------------------------------------\n";
	PerfromDepositOption();
}

short ReadQuickWithdrawOption()
{
	short Choice = 0;
	while (Choice < 1 || Choice > 9)
	{
		cout << "\nChoose what to Withdraw from[1] to [8] ? ";
		cin >> Choice;
	} 

	return Choice;
}

short GetQuickWithdrawAmount(short QuickWithdrawOption)
{
	/*short WithdrawAmount[8] = { 20, 50, 100, 200, 400, 600, 800, 1000 };
	return WithdrawAmount[QuickWithdrawOption - 1];*/
	//Or
	switch (QuickWithdrawOption)
	{
	case 1: 
		return 20;
	case 2:
		return 50;
	case 3:
		return 100;
	case 4:
		return 200;
	case 5:
		return 400;
	case 6:
		return 600;
	case 7:
		return 800;
	case 8:
		return 1000;
	default:
		return 0;

	}

}

void PerfromQuickWithdrawOption(short QuickWithdrawOption)
{
	if (QuickWithdrawOption == 9)//exit
		return;

	short WithdrawBalance = GetQuickWithdrawAmount(QuickWithdrawOption);

	// Valaidate that the amount does not exceeds the Balance
	if (WithdrawBalance > CurrentClient.AccountBalance)
	{
		cout << "\nThe amount exceeds your balance, make anther choice.\n";
		ShowQuickWithdrawScreen();
		system("pause");
		return;
	}

	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, (WithdrawBalance * -1), vClients);
	CurrentClient.AccountBalance -= WithdrawBalance;

}

int ReadWithdrawAmount()
{
	int Amount = 0;
	cout << "\nEnter an amount multiple of  5's ? ";
	cin >> Amount;

	while (Amount % 5 != 0)
	{
		cout << "\nEnter an amount multiple of  5's ? ";
		cin >> Amount;

	}
	return Amount;
}

void PerfromNormalWithdrawOption()
{
	double WithdrawBalance = ReadWithdrawAmount();

	// Valaidate that the amount does not exceeds the Balance
	if (WithdrawBalance > CurrentClient.AccountBalance)
	{
		cout << "\nThe amount exceeds your balance, make anther choice.\n";
		system("pause");
		ShowNormalWithdrawScreen();
		return;
	}

	vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, (WithdrawBalance * -1), vClients);
	CurrentClient.AccountBalance -= WithdrawBalance;
}

void ShowNormalWithdrawScreen()
{
	system("cls");
	cout << "\n------------------------------------------\n";
	cout << "\t\tNormal Withdraw Screen";
	cout << "\n------------------------------------------\n";
	PerfromNormalWithdrawOption();
}

void ShowQuickWithdrawScreen()
{

	system("cls");
	cout << "=============================================\n";
	cout << "\tQuick Withdraw\n";
	cout << "=============================================\n";
	cout << "\t[1] 20 \t [2] 50 \n";
	cout << "\t[3] 100\t [4] 200\n";
	cout << "\t[5] 400\t [6] 600\n";
	cout << "\t[7] 800\t [8] 1000\n";
	cout << "\t[9] Exit\n";
	cout << "=============================================\n";
	cout << "Your Balance is: " << CurrentClient.AccountBalance;
	PerfromQuickWithdrawOption((enMainMenueOptions)ReadQuickWithdrawOption());
}

void GoBackToMainMenue()
{
	cout << "\n\nPress any key to go back to main menue...";
	system("pause>0");
	ShowMainMenue();
}

short ReadMainMenueOption()
{
	cout << "Choose what do you want to do? [1 to 5]? ";
	short Choice = 0;
	cin >> Choice;

	return Choice;
}

void PerformMainmenueOption(enMainMenueOptions MainMenueOption)
{

	switch (MainMenueOption)
	{
	case enMainMenueOptions::eQuickWithdraw:
		system("cls");
		ShowQuickWithdrawScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eNormalWithdraw:
		system("cls");
		ShowNormalWithdrawScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eDeposit:
		system("cls");
		ShowDepositScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eCheckBalance:
		system("cls");
		ShowCheckClientBalance();
		GoBackToMainMenue();
		break;

	case enMainMenueOptions::eLogout:
		system("cls");
		Login();
		break;

	default:
	{
		ShowMainMenue();
		break;
	}

	}
}

void ShowMainMenue()
{
	system("cls");
	cout << "=============================================\n";
	cout << "\t\tATM Main  Menue  Screen\n";
	cout << "=============================================\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "=============================================\n";

	PerformMainmenueOption((enMainMenueOptions)ReadMainMenueOption());
}

bool LoadClientInfo(string AccountNumber, string PinCode)
{
	
	if (FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, CurrentClient))
		return true;
	else
		return false;

}

void Login()
{
	bool LoginFailed = false;
	string AccountNumber, PinCode;
	do
	{
		system("cls");
		cout << "\n=============================================\n";
		cout << "\tLogin Screen";
		cout << "\n=============================================\n";

		if (LoginFailed)
		{
			cout << "Invalid AccountNumber/PinCode!\n";
		}

		cout << "Enter Account Number? ";
		cin >> AccountNumber;

		cout << "Enter Pin? ";
		cin >> PinCode;

		LoginFailed = !LoadClientInfo(AccountNumber, PinCode);

	} while (LoginFailed);

	ShowMainMenue();

}

int main()
{

	Login();

	system("pause>0");
	return 0;

}
