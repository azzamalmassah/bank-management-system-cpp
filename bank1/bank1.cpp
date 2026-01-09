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
enum enMainMenuOptions{
	eShowList = 1,
	eAddClient = 2,
	eDeleteClients = 3,
	eUpdateClient = 4,
	eFindClient = 5,
	eExit = 6
};
void performMainMenuOptions(enMainMenuOptions mainMenuOption);
vector<string>split(string line, string separator = "#//#") {
	short pos = 0;
	string word = "";
	vector<string>vWords;
	while ((pos = line.find(separator)) != std::string::npos) {
		word = line.substr(0, pos);
		if (word != "") {
			vWords.push_back(word);

		}
		line.erase(0,pos + separator.length());
	}
	if (line != "") {
		vWords.push_back(line);
	}
	return vWords;
}


sClient convertLineToRecord(string line,string separator ="#//#") {
	sClient client;
	vector <string>vClientData;
	
	vClientData = split(line, separator);
	if (vClientData.size() < 5)
		return client;
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
void printClientRecordLine(sClient &client) {
	cout << "| " <<setw(15) << left << client.AccountNumber;
	cout << "| " << setw(10) << left << client.PinCode;
	cout << "| " << setw(40) << left << client.Name;
	cout << "| " <<  setw(12) << left << client.Phone;
	cout << "| " <<  setw(12) << left << client.AccountBalance;
}
void showAllClientsScreen() {
	vector <sClient>vClients = loadClientsFromFile(fileName);
	cout << "\n\t\t\t\t\tClients List [" << vClients.size() << "] Client (s).";
	cout << "\n-----------------------------------------------------------------";
	cout << "-------------------------------------------------------\n" << endl;
	cout << "|" << left << setw(15) << "Account Number";
	cout << "|" << left << setw(10) << " Pin Code ";
	cout << "|" << left << setw(40) << " Client Name";
	cout << "|" << left << setw(12) << " Phone";
	cout << "|" << left << setw(12) << " Balance " << endl;
	cout << "\n-----------------------------------------------------------------";
	cout << "-------------------------------------------------------\n" << endl;

	if (vClients.size() == 0) {
		cout << "\t\t\tNo Clients Available in the system!";

	}
	else {
		for (sClient& client : vClients) {
			printClientRecordLine(client);
			cout << endl;
		}
		cout << "\n-----------------------------------------------------------------";
		cout << "-------------------------------------------------------\n" << endl;
		system("Pause");
	}
}
short readMainMenuOption(string message, short from = 1, short to = 6) {
	short answer = 0;
	do {
		cout << message << endl;
		cin >> answer;
	} while (answer<from || answer>to);
	return answer;

}

void showMainMenu(){
	system("cls");
	cout << "============================================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "============================================================\n";
	cout << "\t[1] Show Client List\n";
	cout << "\t[2] Add New Client \n";
	cout << "\t[3] Delete Client \n";
	cout << "\t[4] Update Client \n";
	cout << "\t[5] Find Client \n";
	cout << "\t[6] Exit\n";
	cout << "============================================================\n";



	performMainMenuOptions((enMainMenuOptions)readMainMenuOption("Choose what do you want to do? [1 to 6]? "));


}
void goBackToMainMenu() {
	cout << "Prees any key to go back to main screen..." << endl;
	system("pause>0");
	showMainMenu();
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
	short temp = 0;
	string accountNumber = "";
	

	//1
	


		cout << "Enter Account Number?" << endl;
		
		getline(cin >> ws, client.AccountNumber);

		while (checkIfClientExists( client.AccountNumber,fileName)) {
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
void addDataLineToFile(string fileName,string dataLine) {
	fstream MyFile;
	MyFile.open(fileName, ios::out | ios::app);
	if (MyFile.is_open()) {
		MyFile << dataLine << endl;
		MyFile.close();
	}
}

string convertRecordToLine(sClient client,string separator ="#//#") {
	string stClientRecord = "";
	stClientRecord += client.AccountNumber + separator;
	stClientRecord += client.PinCode + separator;
	stClientRecord += client.Name + separator;
	stClientRecord += client.Phone + separator ;
	stClientRecord += to_string(client.AccountBalance);

	return stClientRecord;



}
void addNewClient(){
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
void printClientCard(const sClient& client) {
	cout << "The following are the client's details\n";
	cout << "-------------------------------------------";
	cout << "\nAccount Number:  " <<client.AccountNumber;
	cout <<"\n Pin Code      :" << client.PinCode;
	cout << "\nName          :" << client.Name;
	cout << "\nPhone         :"  << client.Phone;
	cout << "\nBalance       : "  << client.AccountBalance;
	cout << "\n-------------------------------------------\n";

}
bool findByAccountNumber(string accountNumber, vector <sClient>& vClients,sClient &client) {
	for (sClient& loopClient : vClients) {
		if (loopClient.AccountNumber == accountNumber) {
			client = loopClient;
			return true;
		}
	}
	return false;
}
bool MarkClientForDeleteByAccountNumber(string accountNumber, vector<sClient>&client) {
	for (sClient& loopClient : client) {
		if (loopClient.AccountNumber == accountNumber) {
			loopClient.MarkForDelete = true;
			return true;
		}
	}
	return false;

}
bool deleteClientByAccountNumber(string accountNumber, vector <sClient>&vClients){

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
	return false;

}


string readClientAccountNumber() {
	string accountNumber;
	cout << "\nPlease Enter Account Number : ";
	cin >> accountNumber;

	return accountNumber;
}
void showDeleteClientsScreen(){
	cout << "\n-------------------------------------------\n" << endl;
	cout << "\t\t Delete Client Screen" << endl;
	cout << "\n-------------------------------------------\n" << endl;
	vector<sClient>vClients = loadClientsFromFile(fileName);
	string AccountNumber = readClientAccountNumber();
	deleteClientByAccountNumber(AccountNumber, vClients);


}
//update client 
sClient changeClientRecord(string accountNumber){
	sClient client;
	client.AccountNumber = accountNumber;
	cout << "\n\nEnter PinCode?\t";
	getline(cin >> ws, client.PinCode);
	cout << "\n\nEnter Name?\t";
	getline(cin , client.Name);
	cout << "\n\nEnter Phone?\t";
	getline(cin, client.Phone);
	cout << "\n\nEnter Account Balance?\t";
	cin >> client.AccountBalance;


	return client;

}
bool updateClientByAccountNumber(string accountNumber,vector<sClient> &vClients ){

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
	string AccountNumber = readClientAccountNumber();
	updateClientByAccountNumber(AccountNumber, vClients);
}
// find client 
void showFindClientScreen() {
	cout << "\n-------------------------------------------\n" << endl;
	cout << "\t\t Find Client Screen" << endl;
	cout << "\n-------------------------------------------\n" << endl;
	vector <sClient>vClients = loadClientsFromFile(fileName);
	string accountNumber = readClientAccountNumber();
	sClient client;
	
		if (findByAccountNumber(accountNumber,vClients,client)) {
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
	case enMainMenuOptions::eDeleteClients :
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
	case enMainMenuOptions::eExit:
	{
		system("cls");
		showExitScreen();
		exit(0);
	}
	}
}
int main()
{

	showMainMenu();
}

