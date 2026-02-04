// bank1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>
#include<vector>
#include<cctype>
#include <fstream>
#include <iomanip>

using namespace std;

const string fileName = "Records.txt";
struct sClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0;
	bool MarkForDelete = false;

};
enum enMainMenuOptions {
	eShowList = 1,
	eAddClient = 2,
	eDeleteClients = 3,
	eUpdateClient = 4,
	eFindClient = 5,
	eTransactions = 6,
	eExit = 7,
};
enum enTransactionsOptions {
	eDeposit = 1,
	eWithdraw = 2,
	eTotalBalances = 3,
	eMainMenu = 4,

};
void performMainMenuOptions(enMainMenuOptions mainMenuOption);

vector<string>split(string line, string seperator = "#//#") {
	size_t pos = 0;
	string word = "";
	vector<string>vWords;
	while ((pos = line.find(seperator)) != std::string::npos) {
		word = line.substr(0, pos);
		if (word != "") {
			vWords.push_back(word);

		}
		line.erase(0, pos + seperator.length());
	}

	vWords.push_back(line);

	return vWords;
}

sClient convertLineToRecord(string line, string seperator = "#//#") {
	sClient client;
	vector <string>vClientData;

	vClientData = split(line, seperator);
	client.AccountNumber = vClientData[0];
	client.PinCode = vClientData[1];
	client.Name = vClientData[2];
	client.Phone = vClientData[3];
	client.AccountBalance = stod(vClientData[4]);
	return client;

}
vector <sClient>loadClientsFromFile(string fileName) {
	vector<sClient>vClients;
	fstream MyFile;
	MyFile.open(fileName, ios::in);

	if (MyFile.is_open()) {
		string line = "";
		sClient client;
		while (getline(MyFile, line)) {
			client = convertLineToRecord(line);
			vClients.push_back(client);
		}
		MyFile.close();
	}
	return vClients;

}
void printClintRecordLine(sClient client) {
	cout << "| " << setw(15) << left << client.AccountNumber;
	cout << "| " << setw(10) << left << client.PinCode;
	cout << "| " << setw(40) << left << client.Name;
	cout << "| " << setw(12) << left << client.Phone;
	cout << "| " << setw(12) << left << client.AccountBalance;
}
void showAllClientsScreen() {
	vector <sClient>vClient = loadClientsFromFile(fileName);
	cout << "\n\t\t\t\t\tClients List [" << vClient.size() << "] Client (s).";
	cout << "\n-----------------------------------------------------------------";
	cout << "-------------------------------------------------------\n" << endl;
	cout << "|" << left << setw(15) << "Account Number";
	cout << "|" << left << setw(10) << " Pin Code ";
	cout << "|" << left << setw(40) << " Client Name";
	cout << "|" << left << setw(12) << " Phone";
	cout << "|" << left << setw(12) << " Balance " << endl;
	cout << "\n-----------------------------------------------------------------";
	cout << "-------------------------------------------------------\n" << endl;

	if (vClient.size() == 0) {
		cout << "\t\t\tNo Clients Available in the system!";

	}
	else {
		for (sClient& client : vClient) {
			printClintRecordLine(client);
			cout << endl;
		}
		cout << "\n-----------------------------------------------------------------";
		cout << "-------------------------------------------------------\n" << endl;
		system("Pause");
	}
}
short readMainMenuOptinn(string message, short from = 1, short to = 7) {
	short answer = 0;
	do {
		cout << message << endl;
		cin >> answer;
	} while (answer<from || answer>to);
	return answer;

}

void showMainMenue() {
	system("cls");
	cout << "============================================================\n";
	cout << "\t\tMain Menu Screen\n";
	cout << "============================================================\n";
	cout << "\t[1] Show Client List\n";
	cout << "\t[2] Add New Client \n";
	cout << "\t[3] Delete Client \n";
	cout << "\t[4] Update Client \n";
	cout << "\t[5] Find Client \n";
	cout << "\t[6] Transactions\n";
	cout << "\t[7] Exit\n";
	cout << "============================================================\n";



	performMainMenuOptions((enMainMenuOptions)readMainMenuOptinn("Choose what do you want to do? [1 to 7]? "));


}

void goBackToTransactionsMenu();
void goBackToMainMenu();






void goBackToMainMenu() {
	cout << "\n\nPrees any key to go back to main screen..." << endl;
	system("pause>0");
	showMainMenue();
}

// Add new client 
bool checkIfClientExists(string accountNumber, string fileName) {
	fstream MyFile;
	MyFile.open(fileName, ios::in);
	if (MyFile.is_open())
	{
		string line;
		sClient client;

		while (getline(MyFile, line))
		{
			client = convertLineToRecord(line);
			if (client.AccountNumber == accountNumber) {
				MyFile.close();
				return true;;
			}
		}
		MyFile.close();
	}
	return false;
}

sClient readNewClient() {

	sClient client;


	//1



	cout << "Enter Account Number?" << endl;

	getline(cin >> ws, client.AccountNumber);

	while (checkIfClientExists(client.AccountNumber, fileName)) {
		cout << "Client With account number [" << client.AccountNumber << "] already exists, Enter another Account number?" << endl;
		getline(cin >> ws, client.AccountNumber);

	}




	//2
	cout << "Enter PinCode?\t";
	getline(cin, client.PinCode);

	//3
	cout << "Enter Name?\t";
	getline(cin, client.Name);
	//4
	cout << "Enter Phone?\t";
	getline(cin, client.Phone);

	//5
	cout << "Enter AccountBalance\t";
	cin >> client.AccountBalance;


	return client;
}
void addDataLineToFile(string fileName, string dataLine) {
	fstream MyFile;
	MyFile.open(fileName, ios::out | ios::app);
	if (MyFile.is_open()) {
		MyFile << dataLine << endl;
		MyFile.close();
	}
}

string convertRecordToLine(sClient client, string seperator = "#//#") {
	string stClientRecord = "";
	stClientRecord += client.AccountNumber + seperator;
	stClientRecord += client.PinCode + seperator;
	stClientRecord += client.Name + seperator;
	stClientRecord += client.Phone + seperator;
	stClientRecord += to_string(client.AccountBalance);

	return stClientRecord;



}
void addNewClient() {
	sClient client;
	client = readNewClient();
	addDataLineToFile(fileName, convertRecordToLine(client));
}
void AddNewClients() {
	char addMore = 'Y';
	do {
		cout << "Adding New Client \n\n" << endl;
		addNewClient();
		cout << "\n Client Added Successfully, do you want to add more clients? Y/N\t";
		cin >> addMore;
	} while (toupper(addMore) == 'Y');
}
void showAddNewClientsScreen() {
	cout << "\n-------------------------------------------\n" << endl;
	cout << "\t\t Add New Client Screen" << endl;
	cout << "\n-------------------------------------------\n" << endl;
	AddNewClients();
}



// delete clients
vector<sClient> saveClientsDataToFile(string fileName, vector<sClient>vClients) {
	fstream MyFile;
	MyFile.open(fileName, ios::out);
	if (MyFile.is_open()) {
		string dataLine = "";
		for (sClient& loopClient : vClients) {
			if (loopClient.MarkForDelete == false) {
				dataLine = convertRecordToLine(loopClient);
				MyFile << dataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}
void printClientCard(sClient client) {
	cout << "The following are the client's details\n";
	cout << "-------------------------------------------";
	cout << "\nAccount Number: " << client.AccountNumber;
	cout << "\nPin Code      : " << client.PinCode;
	cout << "\nName          : " << client.Name;
	cout << "\nPhone         : " << client.Phone;
	cout << "\nBalance       : " << client.AccountBalance;
	cout << "\n-------------------------------------------\n";

}
bool findByAccountNumber(string accountNumber, vector <sClient>& vClients, sClient& client) {
	for (sClient& loopClient : vClients) {
		if (loopClient.AccountNumber == accountNumber) {
			client = loopClient;
			return true;
		}
	}
	return false;
}
bool MarkClientForDeleteByAccountNumber(string accountNumber, vector<sClient>& client) {
	for (sClient& loopClient : client) {
		if (loopClient.AccountNumber == accountNumber) {
			loopClient.MarkForDelete = true;
			return true;
		}
	}
	return false;

}
bool deleteClientByAccountNumber(string accountNumber, vector <sClient>& vClients) {

	sClient client;
	char answer = 'n';
	if (findByAccountNumber(accountNumber, vClients, client)) {
		printClientCard(client);
		cout << "Are you sure you want to delete this client Y/N ?\t";
		cin >> answer;
		if (tolower(answer) == 'y') {
			MarkClientForDeleteByAccountNumber(accountNumber, vClients);
			saveClientsDataToFile(fileName, vClients);
			vClients = loadClientsFromFile(fileName);
			cout << "\nClient Deleted successfully" << endl;
			system("Pause");

			return true;
		}
	}
	else {
		cout << "Client with Account Number[" << accountNumber << "] does not exist" << endl;
		system("Pause");

		return false;
	}

}


string readClinetAccountNumber() {
	string accountNumber;
	cout << "\nPlease Enter Account Number : ";
	cin >> accountNumber;

	return accountNumber;
}
void showDeleteClientsScreen() {
	cout << "\n-------------------------------------------\n" << endl;
	cout << "\t\t Delete Client Screen" << endl;
	cout << "\n-------------------------------------------\n" << endl;
	vector<sClient>vClients = loadClientsFromFile(fileName);
	string AccountNumber = readClinetAccountNumber();
	deleteClientByAccountNumber(AccountNumber, vClients);


}
//update client 
sClient changeClientRecord(string accountNumber) {
	sClient client;
	client.AccountNumber = accountNumber;
	cout << "\n\nEnter PinCode?\t";
	getline(cin >> ws, client.PinCode);
	cout << "\n\nEnter Name?\t";
	getline(cin, client.Name);
	cout << "\n\nEnter Phone?\t";
	getline(cin, client.Phone);
	cout << "\n\nEnter Account Balance?\t";
	cin >> client.AccountBalance;


	return client;

}
bool updateClientByAccountNumber(string accountNumber, vector<sClient>& vClients) {

	sClient client;
	char answer = 'n';

	if (findByAccountNumber(accountNumber, vClients, client))
	{
		printClientCard(client);
		cout << "Are you sure you want to update this client Y/N ?\t";
		cin >> answer;
		if (tolower(answer) == 'y') {
			for (sClient& loopClient : vClients)
			{
				if (loopClient.AccountNumber == accountNumber) {
					loopClient = changeClientRecord(accountNumber);
					break;
				}

			}
			saveClientsDataToFile(fileName, vClients);
			cout << "Client Updated successfully." << endl;
			system("pause");
			return true;

		}

	}
	else
	{
		cout << "Client with Account Number[" << accountNumber << "] does not exist" << endl;
		system("Pause");
	}
	return false;
}
void showUpdateClientsScreen() {
	cout << "\n-------------------------------------------\n" << endl;
	cout << "\t\t Update Client Screen" << endl;
	cout << "\n-------------------------------------------\n" << endl;
	vector<sClient>vClients = loadClientsFromFile(fileName);
	string AccountNumber = readClinetAccountNumber();
	updateClientByAccountNumber(AccountNumber, vClients);
}
// find client 
void showFindClientScreen() {
	cout << "\n-------------------------------------------\n" << endl;
	cout << "\t\t Find Client Screen" << endl;
	cout << "\n-------------------------------------------\n" << endl;
	vector <sClient>vClients = loadClientsFromFile(fileName);
	string accountNumber = readClinetAccountNumber();
	sClient client;

	if (findByAccountNumber(accountNumber, vClients, client)) {
		printClientCard(client);

	}
	else {
		cout << "\n\n Client with account number [" << accountNumber << "] was not found!" << endl;
	}

}

void showExitScreen() {
	cout << "\n-------------------------------------------\n" << endl;
	cout << "\t\t Exit Screen" << endl;
	cout << "\n-------------------------------------------\n" << endl;

	cout << "\t\t Ending the Program..." << endl;
}
void performMainMenuOptions(enMainMenuOptions mainMenuOption)
{
	switch (mainMenuOption)
	{
	case enMainMenuOptions::eShowList:
	{
		system("cls");
		showAllClientsScreen();
		goBackToMainMenu();
		break;
	}
	case enMainMenuOptions::eAddClient:
	{
		system("cls");
		showAddNewClientsScreen();
		goBackToMainMenu();
		break;
	}
	case enMainMenuOptions::eDeleteClients:
	{
		system("cls");
		showDeleteClientsScreen();
		goBackToMainMenu();
		break;

	}
	case enMainMenuOptions::eUpdateClient:
	{
		system("cls");
		showUpdateClientsScreen();
		goBackToMainMenu();
		break;

	}
	case enMainMenuOptions::eFindClient:
	{
		system("cls");
		showFindClientScreen();
		goBackToMainMenu();
		break;
	}
	case enMainMenuOptions::eTransactions:
	{
		system("cls");
		goBackToTransactionsMenu();
		break;

	}
	case enMainMenuOptions::eExit:
	{
		system("cls");
		showExitScreen();
		system("pause");
		exit(0);
	}
	}
}

//bank extenstion 
// withdraw

void withdraw(sClient& client) {

	double withdrawAmount = 0;
	char answer = 'n';
	cout << "Please Enter Withdraw amount " << endl;
	cin >> withdrawAmount;
	if (withdrawAmount > client.AccountBalance) {
		cout << "Invalid amount. your balance is [" << client.AccountBalance << "]" << endl;
		system("pause");

		return;
	}
	cout << "\nAre you sure you want to Withdraw this amount Y/N \t";
	cin >> answer;
	if (tolower(answer) == 'y') {
		client.AccountBalance = client.AccountBalance - withdrawAmount;
		cout << "Amount withdrew successfully." << endl;
		system("pause");

	}
	else {
		cout << "\nWithdraw cancelled.\n";
	}

};
bool withdrawLogic(vector<sClient>& vClients, string accountNumber) {

	for (sClient& client : vClients) {
		if (client.AccountNumber == accountNumber) {
			printClientCard(client);
			withdraw(client);
			saveClientsDataToFile(fileName, vClients);
			return true;
		}
	}
	return false;


}
void showWithdrawScreen() {
	cout << "\n-------------------------------------------\n" << endl;
	cout << "\t\t Withdraw Screen" << endl;
	cout << "\n-------------------------------------------\n" << endl;

	vector <sClient>vClients = loadClientsFromFile(fileName);
	string accountNumber = readClinetAccountNumber();

	if (!withdrawLogic(vClients, accountNumber)) {
		cout << "Client with account number [" << accountNumber << "] does not exist " << endl;
		system("pause");
	}


}








// deposit

void deposit(sClient& Client) {
	char answer = 'n';

	double depositAmount = 0;
	cout << "Please Enter deposit amount " << endl;
	cin >> depositAmount;
	if (depositAmount <= 0) {
		cout << "Invalid amount.\n";
		return;
	}
	cout << "\nAre you sure you want to deposit this amount Y/N \t";
	cin >> answer;
	if (tolower(answer) == 'y') {
		Client.AccountBalance = Client.AccountBalance + depositAmount;
	}
	else {
		cout << "\nDeposit cancelled.\n";
	}

}

bool depositLogic(string accountNumber, vector<sClient>& vClients) {


	for (sClient& loopClient : vClients)
	{
		if (loopClient.AccountNumber == accountNumber)
		{
			printClientCard(loopClient);

			deposit(loopClient);

			saveClientsDataToFile(fileName, vClients);
			;
			return true;
		}
	}



	return false;


}
void showDepositScreen() {
	cout << "\n-------------------------------------------\n" << endl;
	cout << "\t\t Depoist Screen" << endl;
	cout << "\n-------------------------------------------\n" << endl;

	vector<sClient> vClients = loadClientsFromFile(fileName);
	string accountNumber = readClinetAccountNumber();
	if (depositLogic(accountNumber, vClients)) {
		cout << "Amount Deposited successfully." << endl;
		system("pause");

	}
	else {
		cout << "Client with account number [" << accountNumber << "] does not exist " << endl;
		system("pause");
	}



}


void printTotalBalanceRecordLine(sClient& client) {
	cout << "| " << setw(15) << left << client.AccountNumber;
	cout << "| " << setw(40) << left << client.Name;
	cout << "| " << setw(12) << left << client.AccountBalance;
}

void showTotalBalanceScreen() {
	double totalBalance = 0;
	vector <sClient>vClient = loadClientsFromFile(fileName);
	cout << "\n\t\t\t\t\tClients List [" << vClient.size() << "] Client (s).";
	cout << "\n-----------------------------------------------------------------";
	cout << "-------------------------------------------------------\n" << endl;
	cout << "|" << left << setw(15) << "Account Number";
	cout << "|" << left << setw(40) << " Client Name";
	cout << "|" << left << setw(12) << " Balance " << endl;
	cout << "\n-----------------------------------------------------------------";
	cout << "-------------------------------------------------------\n" << endl;

	if (vClient.size() == 0) {
		cout << "\t\t\tNo Clients Available in the system!";

	}
	else {
		for (sClient& client : vClient) {
			printTotalBalanceRecordLine(client);
			cout << endl;
			totalBalance = totalBalance + client.AccountBalance;

		}
		cout << "\n-----------------------------------------------------------------";
		cout << "-------------------------------------------------------\n" << endl;
		cout << "\n\t\t\tTotal Balances = " << totalBalance << endl;

		system("Pause");
	}
}
void performTransactionsOptions(enTransactionsOptions option) {
	switch (option) {
	case enTransactionsOptions::eDeposit:
	{
		system("cls");
		showDepositScreen();

		goBackToTransactionsMenu();
		break;
	}
	case enTransactionsOptions::eWithdraw:
	{
		system("cls");

		showWithdrawScreen();

		goBackToTransactionsMenu();

		break;
	}
	case enTransactionsOptions::eTotalBalances:
	{
		system("cls");

		showTotalBalanceScreen();

		goBackToTransactionsMenu();

		break;
	}
	case enTransactionsOptions::eMainMenu:
	{
		system("cls");



		showMainMenue();
		break;
	}
	}
}
void goBackToTransactionsMenu() {
	system("cls");
	cout << "============================================================\n";
	cout << "\t\Transactions Menu Screen\n";
	cout << "============================================================\n";
	cout << "\t[1] Deposit\n";
	cout << "\t[2] Withdraw \n";
	cout << "\t[3] Total Balances \n";
	cout << "\t[4] Main menu \n";

	cout << "============================================================\n";



	performTransactionsOptions((enTransactionsOptions)readMainMenuOptinn("Choose what do you want to do? [1 to 4]? ", 1, 4));

}


int main()
{

	showMainMenue();
}

