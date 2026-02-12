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
	eManageUsers = 7,
	eExit = 8,


};
enum enTransactionsOptions {
	eDeposit = 1,
	eWithdraw = 2,
	eTotalBalances = 3,
	eMainMenu = 4,

};
//
struct sUsers {
	string Name;
	string Password;
	int permissions;
	bool MarkForDelete = false;
};
sUsers loggedInUser;

void showMainMenu();
vector <sUsers>loadUsersFromFile(string fileName);

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
void printClientRecordLine(sClient client) {
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
			printClientRecordLine(client);
			cout << endl;
		}
		cout << "\n-----------------------------------------------------------------";
		cout << "-------------------------------------------------------\n" << endl;
		system("Pause");
	}
}
short readMainMenuOptinn(string message, short from = 1, short to = 8) {
	short answer = 0;
	do {
		cout << message << endl;
		cin >> answer;
	} while (answer<from || answer>to);
	return answer;

}



void goBackToTransactionsMenu();
void goBackToMainMenu();






void goBackToMainMenu() {
	cout << "\n\nPrees any key to go back to main screen..." << endl;
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
void loginScreen();
void 		manageUsersMenu();
//
void printDenied() {
	cout << "\n------------------------------------------------------------------\n" << endl;
	cout << "Access denied, " << endl;
	cout << "you dont have permission to access this," << endl;
	cout << "Please contact your admin to get more information" << endl;
	cout << "\n------------------------------------------------------------------\n" << endl;
}
enum enManagePermissions {
	pListClients = 1 << 0,
	pAddNewClient = 1 << 1,
	pDeleteClient = 1 << 2,
	pUpdateClient = 1 << 3,
	pFindClient = 1 << 4,
	pTransactions = 1 << 5,
	pManageUsers = 1 << 6
};
bool checkAccessPermissions(enMainMenuOptions option, sUsers user) {

	switch (option) {
	case enMainMenuOptions::eShowList:return user.permissions & enManagePermissions::pListClients;
	case enMainMenuOptions::eAddClient:return user.permissions & enManagePermissions::pAddNewClient;
	case enMainMenuOptions::eUpdateClient:return user.permissions & enManagePermissions::pUpdateClient;
	case enMainMenuOptions::eDeleteClients:return user.permissions & enManagePermissions::pDeleteClient;
	case enMainMenuOptions::eTransactions:return user.permissions & enManagePermissions::pTransactions;
	case enMainMenuOptions::eManageUsers:return user.permissions & enManagePermissions::pManageUsers;
	case enMainMenuOptions::eFindClient:return user.permissions & enManagePermissions::pFindClient;


	default:return true;

	}
}

void performMainMenuOptions(enMainMenuOptions mainMenuOption, sUsers user)
{
	if (user.permissions != -1) {


		if (!checkAccessPermissions(mainMenuOption, user)) {
			system("cls");


			printDenied();			system("pause");
			goBackToMainMenu();
			return;

		}
	}
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
		loginScreen();
		exit(0);
	}
	case enMainMenuOptions::eManageUsers: {
		manageUsersMenu();

	}

	}
}

void showMainMenu() {
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
	cout << "\t[7] Manage Users\n";
	cout << "\t[8] Logout\n";
	cout << "============================================================\n";



	performMainMenuOptions((enMainMenuOptions)readMainMenuOptinn("Choose what do you want to do? [1 to 8]? "), loggedInUser);


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



		showMainMenu();
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


//extension 2


sUsers convertUserLineToRecord(string line, string seperator = "#//#") {
	sUsers user;
	vector <string>vUsersData;


	vUsersData = split(line, seperator);
	if (vUsersData.size() < 3)
		return sUsers{};
	user.Name = vUsersData[0];
	user.Password = vUsersData[1];
	user.permissions = stod(vUsersData[2]);
	user.MarkForDelete = false;

	return user;

}

vector <sUsers>loadUsersFromFile(string fileName) {
	vector<sUsers>vUsers;
	fstream MyFile;
	MyFile.open(fileName, ios::in);

	if (MyFile.is_open()) {
		string line = "";
		sUsers user;
		while (getline(MyFile, line)) {

			user = convertUserLineToRecord(line);
			vUsers.push_back(user);
		}
		MyFile.close();
	}
	return vUsers;

}
string readString(string message) {
	string answer = "";
	cout << message;
	cin >> answer;
	return answer;
}
bool login(vector<sUsers>& vUsers) {

	string userName = readString("Enter Username:\t");
	string password = readString("Enter password:\t");

	for (sUsers& user : vUsers) {
		if (user.Name == userName && user.Password == password) {
			loggedInUser = user;
			showMainMenu();

			return true;
		}
	}

	return false;
}


void printLoginScreen() {
	cout << "\n-------------------------------------------\n" << endl;
	cout << "\t\t Login Screen" << endl;
	cout << "\n-------------------------------------------\n" << endl;
}
void loginScreen() {

	printLoginScreen();
	vector<sUsers>vUsers;
	vUsers = loadUsersFromFile("Users.txt");
	while (!login(vUsers)) {

		system("cls");

		printLoginScreen();
		cout << "Invalid Username/Password!" << endl;

	}

}

// add New User
bool checkIfUserExists(string userName, string fileName) {
	fstream MyFile;
	MyFile.open(fileName, ios::in);
	if (MyFile.is_open())
	{
		string line;
		sUsers user;

		while (getline(MyFile, line))
		{
			user = convertUserLineToRecord(line);
			if (user.Name == userName) {
				MyFile.close();
				return true;;
			}
		}
		MyFile.close();
	}
	return false;
}
string convertRecordToLine(sUsers user, string seperator = "#//#") {
	string stUserRecord = "";
	stUserRecord += user.Name + seperator;
	stUserRecord += user.Password + seperator;
	stUserRecord += to_string(user.permissions);

	return stUserRecord;



}



sUsers readNewUser() {

	sUsers user;
	char fullAccess = ' ';
	char options = ' ';
	//1

	cout << "Enter Username?" << endl;
	getline(cin >> ws, user.Name);

	while (checkIfUserExists(user.Name, "users.txt")) {
		cout << "User With User Name [" << user.Name << "] already exists, Enter another User Name?" << endl;
		getline(cin >> ws, user.Name);

	}

	//2
	cout << "Enter Password?\t";
	getline(cin, user.Password);

	//3

	cout << "Do you want to give full access?\t";
	cin >> fullAccess;
	if (fullAccess == 'y') {
		user.permissions = -1;
	}
	else {
		cout << "Do you want to give access to: " << endl;
		//1
		cout << "show Client List: ";
		cin >> options;
		if (options == 'y') {
			user.permissions = enManagePermissions::pListClients;
		}
		//2
		cout << "Add New Client: ";
		cin >> options;
		if (options == 'y') {
			user.permissions += enManagePermissions::pAddNewClient;
		}
		//3
		cout << "Delete Client: ";
		cin >> options;
		if (options == 'y') {
			user.permissions += enManagePermissions::pDeleteClient;
		}
		//4
		cout << "Update Client: ";
		cin >> options;
		if (options == 'y') {
			user.permissions += enManagePermissions::pUpdateClient;
		}
		//4
		cout << "Find Client: ";
		cin >> options;
		if (options == 'y') {
			user.permissions += enManagePermissions::pFindClient;
		}
		//5
		cout << "Transactions : ";
		cin >> options;
		if (options == 'y') {
			user.permissions += enManagePermissions::pTransactions;
		}
		//5
		cout << "Manage Users : ";
		cin >> options;
		if (options == 'y') {
			user.permissions += enManagePermissions::pManageUsers;
		}


	}
	return user;
}
void addNewUser() {
	sUsers user;
	user = readNewUser();
	addDataLineToFile("users.txt", convertRecordToLine(user));
}
void AddNewUser() {
	char addMore = 'Y';
	do {
		cout << "Adding New User \n\n" << endl;
		addNewUser();
		cout << "\n User Added Successfully, do you want to add more Users? Y/N\t";
		cin >> addMore;
	} while (toupper(addMore) == 'Y');
}
void showAddNewUserScreen() {
	cout << "\n-------------------------------------------\n" << endl;
	cout << "\t\t Add New User Screen" << endl;
	cout << "\n-------------------------------------------\n" << endl;
	AddNewUser();
}
//list users 

void printUserRecordLine(sUsers user) {
	cout << "| " << setw(15) << left << user.Name;
	cout << "| " << setw(10) << left << user.Password;
	cout << "| " << setw(40) << left << user.permissions;

}
void showAllUsersScreen() {
	vector <sUsers>vUsers = loadUsersFromFile("users.txt");
	cout << "\n\t\t\t\t\tClients List [" << vUsers.size() << "] Client (s).";
	cout << "\n-----------------------------------------------------------------";
	cout << "-------------------------------------------------------\n" << endl;
	cout << "|" << left << setw(15) << "User Name";
	cout << "|" << left << setw(10) << "Password ";
	cout << "|" << left << setw(40) << "permissions" << endl;
	cout << "\n-----------------------------------------------------------------";
	cout << "-------------------------------------------------------\n" << endl;

	if (vUsers.size() == 0) {
		cout << "\t\t\tNo Users Available in the system!";

	}
	else {
		for (sUsers& user : vUsers) {
			printUserRecordLine(user);
			cout << endl;
		}
		cout << "\n-----------------------------------------------------------------";
		cout << "-------------------------------------------------------\n" << endl;
		system("Pause");
	}
}
//find user 

void printUserCard(sUsers& user) {


	cout << "\nThe following are the user details\n";
	cout << "-------------------------------------------";
	cout << "\nUserName          : " << user.Name;
	cout << "\nPassword          : " << user.Password;
	cout << "\nPermission        : " << user.permissions;

	cout << "\n-------------------------------------------\n";
	system("pause");


}
string readUserName(string message) {
	string answer;
	cout << message;
	cin >> answer;
	return answer;
}
bool findUserByUserName(vector <sUsers>vUsers, sUsers& user, string userName) {
	for (sUsers& loopUser : vUsers) {
		if (loopUser.Name == userName) {
			user = loopUser;
			return true;
		}

	}
	return false;
}
void findUserScreen() {
	cout << "\n-------------------------------------------\n" << endl;
	cout << "\t\t Find User Screen" << endl;
	cout << "\n-------------------------------------------\n" << endl;
	vector <sUsers>vUsers = loadUsersFromFile("users.txt");
	sUsers user;
	string userName = readUserName("Please Enter User Name: ");
	if (findUserByUserName(vUsers, user, userName)) {
		printUserCard(user);
	}
	else {
		cout << "user with user Name [" << userName << "] does not exist. " << endl;
	}

}
//updateUsers
void saveFile(vector <sUsers>vUser, string fileName) {

	fstream MyFile;
	MyFile.open(fileName, ios::out);
	if (MyFile.is_open()) {
		string dataLine = "";
		for (sUsers& loopUser : vUser) {
			if (loopUser.MarkForDelete == false) {
				dataLine = convertRecordToLine(loopUser);
				MyFile << dataLine << endl;
			}
		}
		MyFile.close();
	}



}
sUsers changeUserDetails(sUsers user) {
	char fullAccess = ' ';
	char options = ' ';
	//2
	cout << "Enter Password?\t";
	getline(cin >> ws, user.Password);

	//3

	cout << "Do you want to give full access?\t";
	cin >> fullAccess;
	if (fullAccess == 'y')
	{
		user.permissions = -1;
	}
	else
	{
		cout << "Do you want to give access to: " << endl;
		//1
		cout << "show Client List: ";
		cin >> options;
		if (options == 'y')
		{

			user.permissions = enManagePermissions::pListClients;
		}
		//2
		cout << "Add New Client: ";
		cin >> options;
		if (options == 'y')
		{
			user.permissions += enManagePermissions::pAddNewClient;
		}
		//3
		cout << "Delete Client: ";
		cin >> options;
		if (options == 'y')
		{
			user.permissions += enManagePermissions::pDeleteClient;
		}
		//4
		cout << "Update Client: ";
		cin >> options;
		if (options == 'y')
		{
			user.permissions += enManagePermissions::pUpdateClient;
		}
		//4
		cout << "Find Client: ";
		cin >> options;
		if (options == 'y')
		{
			user.permissions += enManagePermissions::pFindClient;
		}
		//5
		cout << "Transactions : ";
		cin >> options;
		if (options == 'y')
		{
			user.permissions += enManagePermissions::pTransactions;
		}
		//5
		cout << "Manage Users : ";
		cin >> options;
		if (options == 'y')
		{
			user.permissions += enManagePermissions::pManageUsers;
		}


	}
	return user;

}
void updateUserByUserName(vector <sUsers>& vUsers, sUsers& user, string userName) {
	char answer = ' ';
	if (findUserByUserName(vUsers, user, userName)) {
		printUserCard(user);
		cout << "Are you sure you want to update this user y/n ? ";
		cin >> answer;
		if (tolower(answer) == 'y') {
			for (sUsers& loopUser : vUsers) {
				if (loopUser.Name == userName) {
					loopUser = changeUserDetails(loopUser);
					break;
				}
			}
			saveFile(vUsers, "users.txt");
			cout << "User updated successfully!" << endl;
			system("pause");
			return;
		}
	}
	else {
		cout << "user with user Name [" << userName << "] does not exist. " << endl;
		system("pause");
		return;

	}
}
void updateUserScreen() {
	cout << "\n-------------------------------------------\n" << endl;
	cout << "\t\t Update User Screen" << endl;
	cout << "\n-------------------------------------------\n" << endl;
	vector <sUsers>vUsers = loadUsersFromFile("users.txt");
	string userName = readUserName("Please Enter User Name: ");
	sUsers user;
	updateUserByUserName(vUsers, user, userName);






}

//delete user

void deleteUserByUserName(vector <sUsers>& vUsers, string userName) {
	char answer = ' ';
	sUsers user;
	if (userName == "Admin") {
		cout << "Cannot delete the default admin user." << endl;
		system("pause");
		return;
	}
	if (findUserByUserName(vUsers, user, userName)) {
		printUserCard(user);
		cout << "Are you sure you want to delete this user y/n ? ";
		cin >> answer;
		if (tolower(answer) == 'y') {
			for (sUsers& loopUser : vUsers) {
				if (loopUser.Name == userName) {
					loopUser.MarkForDelete = true;
					break;
				}
			}
			saveFile(vUsers, "users.txt");
			cout << "User deleted successfully!" << endl;
			system("pause");
			return;
		}
	}
	else {
		cout << "user with user Name [" << userName << "] does not exist. " << endl;
		system("pause");
		return;
	}
}
void deleteUserScreen() {
	cout << "\n-------------------------------------------\n" << endl;
	cout << "\t\t Delete User Screen" << endl;
	cout << "\n-------------------------------------------\n" << endl;
	vector <sUsers>vUsers = loadUsersFromFile("users.txt");
	string userName = readUserName("Please Enter User Name: ");
	deleteUserByUserName(vUsers, userName);


}
// manage users menu

enum enManageUsersOptions { enListUsers = 1, enAddNewUser = 2, enDeleteUser = 3, enUpdateUser = 4, enFindUser = 5, enMainMenu = 6 };


void performManageUsersOptions(enManageUsersOptions option) {
	switch (option) {
	case enManageUsersOptions::enListUsers:
	{
		system("cls");
		showAllUsersScreen();
		manageUsersMenu();
		break;
	}
	case enManageUsersOptions::enAddNewUser:
	{
		system("cls");
		showAddNewUserScreen();
		manageUsersMenu();
		break;

	}
	case enManageUsersOptions::enFindUser:
	{
		system("cls");
		findUserScreen();
		manageUsersMenu();
		break;

	}
	case enManageUsersOptions::enUpdateUser:
	{
		system("cls");
		updateUserScreen();
		manageUsersMenu();
		break;

	}
	case enManageUsersOptions::enDeleteUser:
	{
		system("cls");
		deleteUserScreen();
		manageUsersMenu();
		break;






	}
	case enManageUsersOptions::enMainMenu:
	{
		system("cls");
		showMainMenu();
		break;

	}


	}
}


void manageUsersMenu() {
	system("cls");
	cout << "============================================================\n";
	cout << "\t\Manage Users Menu Screen\n";
	cout << "============================================================\n";
	cout << "\t[1] List Users\n";
	cout << "\t[2] Add New User \n";
	cout << "\t[3] Delete User \n";
	cout << "\t[4] Update User \n";
	cout << "\t[5] Find User \n";
	cout << "\t[6] Main Menu\n";
	cout << "============================================================\n";

	performManageUsersOptions((enManageUsersOptions)readMainMenuOptinn("Choose what do you want to do? [1 to 6]? ", 1, 6));

}

int main()
{

	loginScreen();
}

