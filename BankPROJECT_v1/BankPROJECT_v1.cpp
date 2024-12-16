#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
string FileName = "Clients_Data.txt";
string delim = "#//#";

void GetChoiceFromUser();

struct Struc {

	string AccountNumber;
	string  Name;
	string PineCode;
	string PhoneNumber;
	double Balence;

};


//========Print Fonctions================

void PrintTransactionsMenu()
{
	cout << "\n====================================================================\n";
	cout << setw(40) << "         Transactions Main Menu Screen ";
	cout << "\n====================================================================\n\n";

	cout << setw(15) << left << "         [1] Deposit." << endl;

	cout << setw(15) << left << "         [2] Withdraw." << endl;

	cout << setw(15) << left << "         [3] Total Balences." << endl;

	cout << setw(15) << left << "         [4] Main Menue." << endl;

	cout << "\n====================================================================\n\n";



}

void PintClients(vector <Struc> vClient)
{
	cout << "                              Client List (" << vClient.size() << ") Client(s) ." << endl;

	cout << "======================================================================================================\n\n";


	cout << "|" << setw(20) << left << " Account Number ";
	cout << "|" << setw(20) << left << " Pine Code ";
	cout << "|" << setw(30) << left << " Full Name ";
	cout << "|" << setw(20) << left << " Phone Number ";
	cout << "|" << setw(20) << left << " Balence ";
	cout << "\n======================================================================================================\n\n";


	for (Struc& n : vClient)
	{
		cout << "|" << setw(20) << left << n.AccountNumber;
		cout << "|" << setw(20) << left << n.PineCode;
		cout << "|" << setw(30) << left << n.Name;
		cout << "|" << setw(20) << left << n.PhoneNumber;
		cout << "|" << setw(20) << left << n.Balence;

		cout << endl;

	}
	cout << "\n======================================================================================================\n\n";

}

void PrintClientScreanForAction(string action)
{

	cout << "\n\n------------------------------------------------\n";
	cout << "         " << action << " Client Screen";
	cout << "\n------------------------------------------------\n";
	cout << "Add New Client  : " << endl << endl;



}

void PrintClientScreanForAction()
{
	cout << "\n\n------------------------------------------------\n";
	cout << "         Add New Client Screen";
	cout << "\n------------------------------------------------\n";
	cout << "Add New Client  : " << endl << endl;



}

void PrintClientCard(Struc n)
{
	cout << "\n======================================================================================================\n";

	cout << "                              Client List Card." << endl;

	cout << "======================================================================================================\n\n";


	cout << setw(10) << left << " Account Number  " << ": " << n.AccountNumber << endl;
	cout << setw(10) << left << " Pine Code       " << ": " << n.PineCode << endl;
	cout << setw(5) << left << " Full Name       " << ": " << n.Name << endl;
	cout << setw(10) << left << " Phone Number    " << ": " << n.PhoneNumber << endl;
	cout << setw(10) << left << " Balence         " << ": " << n.Balence;


	cout << "\n\n======================================================================================================\n\n";



}

void PrintBalenceList(vector <Struc> vClient)
{
	cout << "                              Client Balence List (" << vClient.size() << ") Client(s) ." << endl;

	cout << "======================================================================================================\n\n";


	cout << "|" << setw(20) << left << " Account Number ";
	cout << "|" << setw(30) << left << " Client Full Name ";
	cout << "|" << setw(20) << left << " Balence ";
	cout << "\n======================================================================================================\n\n";


	for (Struc& n : vClient)
	{
		cout << "|" << setw(20) << left << n.AccountNumber;
		cout << "|" << setw(30) << left << n.Name;
		cout << "|" << setw(20) << left << n.Balence;

		cout << endl;

	}
	cout << "\n======================================================================================================\n\n";


}

//--------Rest Of Fonctions =------------------------------------------------


vector <string>  SplitLine(string Line)
{
	vector <string> vClient;
	string word;
	size_t pos;

	while ((pos = Line.find(delim)) != std::string::npos)
	{
		word = Line.substr(0, pos);
		if (word != "")
		{
			vClient.push_back(word);
			Line.erase(0, pos + delim.length());
		}
	}

	if (Line != "")
	{
		vClient.push_back(Line);

	}

	return vClient;
}

Struc ConvertLineToStruc(string Line)
{
	Struc sClient;

	vector <string> vClient;
	vClient = SplitLine(Line);

	sClient.AccountNumber = vClient[0];
	sClient.PineCode = vClient[1];
	sClient.Name = vClient[2];
	sClient.PhoneNumber = vClient[3];
	sClient.Balence = stod(vClient[4]);



	return sClient;
}

vector <Struc> LoadDataFromFileToVector()
{
	Struc sClient;
	vector <Struc> vClient;
	string Line = "";

	fstream Myfile;
	Myfile.open(FileName, ios::in);
	if (Myfile.is_open())
	{
		while (getline(Myfile, Line))
		{
			if (Line != "")
			{

				sClient = ConvertLineToStruc(Line);
				vClient.push_back(sClient);
			}

		}

		Myfile.close();
	}



	return vClient;
}

string CheckIfTheAccountNumberExist()
{
	vector <Struc> vClient;
	string  NewAccountNumber;
	vector <string> vAccountNumber;


	vClient = LoadDataFromFileToVector();
	PrintClientScreanForAction();



	for (Struc& n : vClient)
		vAccountNumber.push_back(n.AccountNumber);

	do {
		cout << "\nEnter Account Number : ";
		cin >> NewAccountNumber;
		bool flag = false;
		cout << endl << endl;

		for (const string& n : vAccountNumber)
		{
			if (n == NewAccountNumber)
			{
				flag = true;
				break;
			}
		}

		if (flag)
		{
			cout << "Account number already exists. Please enter a new one.\n";
		}

		else
		{
			vAccountNumber.push_back(NewAccountNumber);
			cout << "Account number added successfully!\n";
			break;
		}




	} while (true);

	return NewAccountNumber;

}

string ConvertStrucToLine(Struc n)
{
	string Line = "";

	Line = n.AccountNumber + delim;
	Line += n.PineCode + delim;
	Line += n.Name + delim;
	Line += n.PhoneNumber + delim;
	Line += to_string(n.Balence);

	Line += "\n";

	return Line;
}

void SaveLineInTheFile(string Line)
{
	fstream Myfile;
	Myfile.open(FileName, ios::app);

	if (Myfile.is_open())
	{
		Myfile << Line;
		Myfile.close();
	}
}


void SaveVectorInTheFile(vector <Struc> NewVector)
{
	fstream Myfile;
	string Line;
	Myfile.open(FileName, ios::out);





	if (Myfile.is_open())
	{
		for (Struc& n : NewVector)
		{
			Line = ConvertStrucToLine(n);
			Myfile << Line;

		}


		Myfile.close();
	}

}

vector <Struc> CopyVectorWithoutClientByAccountNumber(string AccountNumber)
{
	vector <Struc> vClient, NewVector;
	vClient = LoadDataFromFileToVector();

	for (Struc& n : vClient)
	{
		if (n.AccountNumber != AccountNumber)
		{
			NewVector.push_back(n);
		}
	}

	return NewVector;

}

string ChooseClientToBeTreated()
{
	vector <Struc> vClient;
	bool flag = true;
	vClient = LoadDataFromFileToVector();
	string AccountNumber;

	while (flag)
	{
		cin >> AccountNumber;
		cout << endl;

		for (Struc& n : vClient)
		{
			if (n.AccountNumber == AccountNumber)
			{
				flag = false;

			}

		}
		if (flag == false)
		{
			return AccountNumber;
		}
		else
		{
			cout << "There Is No Client With That AccountNumber !!!\n\n";
			flag = true;
		}
		cout << "Enter AccountNumber : ";

	}


	//	return AccountNumber;

}

string EditClient(string AccountNumber, Struc n)
{

	string Line, temp[4];
	double Balence;
	temp[0] = AccountNumber;

	cout << "\nEnter Client PineCode : ";
	getline(cin >> ws, temp[1]);
	cout << endl;


	cout << "Enter Client Full Name : ";
	getline(cin, temp[2]);
	cout << endl;

	cout << "Enter Client Phone Number : ";
	getline(cin, temp[3]);
	cout << endl;

	cout << "Enter Client Balence : ";
	cin >> Balence;
	cout << endl;

	cout << "\n_____________________________________________________________________\n\n";

	for (int i = 0; i < temp->size(); i++)
		Line += temp[i] + delim;


	Line += to_string(Balence) + "\n";

	return Line;



}

void GetClientfromUserAndSaveIt(string AccountNumber)
{
	system("cls");
	PrintClientScreanForAction();
	Struc sClient;
	string Line;

	sClient.AccountNumber = AccountNumber;

	cout << "\nAccount Number : " << AccountNumber << endl << endl;

	cout << "Enter Client PineCode : ";
	getline(cin >> ws, sClient.PineCode);
	cout << endl;

	cout << "Enter Client Full Name : ";
	getline(cin, sClient.Name);
	cout << endl;

	cout << "Enter Client Phone Number : ";
	getline(cin, sClient.PhoneNumber);
	cout << endl;

	cout << "Enter Client Balence : ";
	cin >> sClient.Balence;
	cout << endl;

	cout << "\n_____________________________________________________________________\n\n";

	Line = ConvertStrucToLine(sClient);

	SaveLineInTheFile(Line);


}

//========Body Of Tronsaction fonctions=========================================================================


string checkIftheAccountNumberDoesntExist(string AccountNumber) {
	string NewAccountNumber;
	vector<Struc> vClient;
	vClient = LoadDataFromFileToVector();

	vector<string> vAccountNumber;

	bool flag = false;

	for (Struc& n : vClient)
		vAccountNumber.push_back(n.AccountNumber);


	cout << "\nEnter Account Number : ";
	cin >> NewAccountNumber;
	cout << endl << endl;


	do {




		for (const string& n : vAccountNumber)
		{
			if (n == NewAccountNumber)
			{
				flag = true;
				break;
			}
		}
		if (flag == false)
		{
			cout << "This Account Number Doesn't Exist !!!\n";
			cout << "Please Enter a knew One : ";
			cin >> NewAccountNumber;
			cout << endl;
		}

	} while (flag == false);

	return NewAccountNumber;
}

vector <Struc> EditClientAsNewVector(string AccountNumber, double deposit)
{
	vector <Struc> vClient = LoadDataFromFileToVector();
	vector <Struc> NewV;


	for (Struc& n : vClient)
	{


		if (n.AccountNumber == AccountNumber)
		{
			n.AccountNumber = AccountNumber;
			n.PineCode = n.PineCode;
			n.Name = n.Name;
			n.PhoneNumber = n.PhoneNumber;
			n.Balence = (n.Balence + deposit);

			NewV.push_back(n);

		}
		else
			NewV.push_back(n);

	}


	return NewV;
}

double CheckTheWithdrawAmount(double amountOfClient)
{
	double Withdraw;
	bool flag = true;
	cout << "\nPlease Enter Withdraw Amount : ";
	cin >> Withdraw;

	if (amountOfClient < Withdraw)
	{
		do {
			cout << "\nAmount Exceeds The Balence, You Can Withdraw Up To : " << amountOfClient;
			cout << endl;
			cout << "\nPlease Enter Another Withdraw Amount : ";
			cin >> Withdraw;
		} while (amountOfClient < Withdraw);
	}

	return Withdraw;
}



//========Body Fonctions oF Transactions=======================================================

void ToTalBalences()
{
	double total = 0;

	vector <Struc> vClient = LoadDataFromFileToVector();
	PrintBalenceList(vClient);

	for (Struc& n : vClient)
	{
		total += n.Balence;

	}
	cout << "                              " << "Total Baleces = " << total;

	cout << "\n\nPress Any Key To Go Back To The Transaction Menu ...\n";
	system("pause>0");

}

void Withdraw()
{
	char cond = 'n';

	double amountOfClient;
	string action = "Withdraw";
	double TempWithdraw;
	PrintClientScreanForAction(action);

	string AccountNumber;

	AccountNumber = checkIftheAccountNumberDoesntExist(AccountNumber);
	vector <Struc> vClient = LoadDataFromFileToVector();
	vector <Struc> NewV;

	system("cls");

	for (Struc& n : vClient)
	{
		if (n.AccountNumber == AccountNumber)
		{
			PrintClientCard(n);
			amountOfClient = n.Balence;
			break;
		}
	}

	TempWithdraw = CheckTheWithdrawAmount(amountOfClient);




	cout << "\n\n\nAre You Sure You Want To Perform This Transaction ? y/n  : ";
	cin >> cond;
	cout << endl;

	if (cond == 'y' || cond == 'Y')
	{
		TempWithdraw = TempWithdraw * -1;

		NewV = EditClientAsNewVector(AccountNumber, TempWithdraw);

		SaveVectorInTheFile(NewV);



		cout << "\n\nTransaction Performed Successfully ...";
		cout << "\nClient Curent Balence = " << amountOfClient + TempWithdraw << endl;


	}




	cout << "\n\nPress Any Key To Go Back To The Transaction Menu ...\n";
	system("pause>0");


}


void Deposit()
{
	char cond = 'n';
	double deposit, balence;
	string action = "Deposit";

	PrintClientScreanForAction(action);

	string AccountNumber;
	AccountNumber = checkIftheAccountNumberDoesntExist(AccountNumber);
	vector <Struc> vClient = LoadDataFromFileToVector();
	vector <Struc> NewV;

	system("cls");

	for (Struc& n : vClient)
	{
		if (n.AccountNumber == AccountNumber)
		{
			balence = n.Balence;
			PrintClientCard(n);
			break;
		}
	}

	cout << "\nPlease Enter Deposit Amount : ";
	cin >> deposit;

	cout << "\n\n\nAre You Sure You Want To Perform This Transaction ? y/n  : ";
	cin >> cond;
	cout << endl;

	if (cond == 'y' || cond == 'Y')
	{

		NewV = EditClientAsNewVector(AccountNumber, deposit);

		SaveVectorInTheFile(NewV);



		cout << "\n\nTransaction Performed Successfully ...";

		cout << "\nClient Curent Balence = " << balence + deposit << endl;
	}




	cout << "\n\nPress Any Key To Go Back To The Transaction Menu ...\n";
	system("pause>0");

}


// 
//========Body Fonctions=======================================================

void FindClient()
{
	vector <Struc> vClient = LoadDataFromFileToVector();
	string AccountNumber;
	bool flage = false;

	cout << "Enter Client AccountNumber To Find It  : ";
	AccountNumber = ChooseClientToBeTreated();

	for (Struc& n : vClient)
	{
		if (n.AccountNumber == AccountNumber)
		{
			PrintClientCard(n);
			cout << "\n\n\nPress Any Key To Go Back To The main Menu ...\n";
			system("pause>0");
			flage = true;
		}

	}
	if (false)
	{
		cout << "This AccountNumber Doesn't Exist !!!" << endl;
		cout << "\n\n\nPress Any Key To Go Back To The main Menu ...\n";
		system("pause>0");

	}
}


void UpdateClientInfo()
{

	char cond = 'n';
	vector <Struc> vClient;
	string Line;
	vClient = LoadDataFromFileToVector();
	string AccountNumber;

	cout << "\nEnter AccountNumber Of The Client To Be Updated : ";
	AccountNumber = ChooseClientToBeTreated();

	system("cls");

	for (Struc& n : vClient)
	{
		if (n.AccountNumber == AccountNumber)
		{
			PrintClientCard(n);
			break;

		}

	}


	cout << "\n\nAre You Sur To Update This Client ?  y/n  :";
	cin >> cond;

	if (cond == 'y' || cond == 'Y')
	{
		fstream Myfile;
		Myfile.open(FileName, ios::out);

		if (Myfile.is_open())
		{
			for (Struc& n : vClient)
			{
				if (n.AccountNumber != AccountNumber)
				{
					Line = "";
					Line = ConvertStrucToLine(n);
					SaveLineInTheFile(Line);

				}
				else
				{
					Line = "";
					Line = EditClient(AccountNumber, n);
					SaveLineInTheFile(Line);
				}

			}

			Myfile.close();
		}


		cout << "\n\n\nClient Updated Successfully ...\n";

		cout << "Press Any Key To Go Back To The main Menu ...\n";
		system("pause>0");
	}
	else
	{
		cout << "\n\n\nPress Any Key To Go Back To The main Menu ...\n";
		system("pause>0");
	}



}


void DelateClient()
{
	char cond = 'n';
	vector <Struc> vClient, NewVector;
	vClient = LoadDataFromFileToVector();
	string AccountNumber;

	cout << "\nEnter AccountNumber Of The Client To Be Deleated : ";
	AccountNumber = ChooseClientToBeTreated();

	system("cls");

	for (Struc& n : vClient)
	{
		if (n.AccountNumber == AccountNumber)
		{
			PrintClientCard(n);
			break;

		}

	}


	cout << "\n\nAre You Sur To DeLate This Client ?  y/n  :";
	cin >> cond;

	if (cond == 'y' || cond == 'Y')
	{

		NewVector = CopyVectorWithoutClientByAccountNumber(AccountNumber);

		SaveVectorInTheFile(NewVector);
		cout << "\n\n\nClient Delated Successfully ...\n";

		cout << "Press Any Key To Go Back To The main Menu ...\n";
		system("pause>0");
	}
	else
	{
		cout << "\n\n\nPress Any Key To Go Back To The main Menu ...\n";
		system("pause>0");
	}

}


void AddNewClient()
{
	char cond = 'n';
	string AccountNumber;



	do
	{
		AccountNumber = CheckIfTheAccountNumberExist();

		GetClientfromUserAndSaveIt(AccountNumber);

		cout << "\n\nClient Added Successfully ..., Do you Want To Add More ? y/n : \n";
		cin >> cond;
		system("cls");
	} while (cond == 'y' || cond == 'Y');

	cout << "\n\n\nPress Any Key To Go Back To The main Menue ...\n";
	system("pause>0");
}

void ShowClientList()
{

	vector <Struc> vClient;
	vClient = LoadDataFromFileToVector();

	PintClients(vClient);

	cout << "\n\n\nPress Any Key To Go Back To The main Menu ...\n";
	system("pause>0");



}

void Transactions()
{
	short choice;
	system("cls");
	PrintTransactionsMenu();

	cout << "Choose What You Want To Do ? [ 1 to 4 ]  : ";
	cin >> choice;


	switch (choice)
	{
	case 1:
	{
		system("cls");
		Deposit();
		Transactions();
		break;
	}

	case 2:
	{
		system("cls");
		Withdraw();
		Transactions();
		break;
	}

	case 3:
	{
		system("cls");
		ToTalBalences();
		Transactions();
		break;
	}

	case 4:
	{
		system("cls");
		GetChoiceFromUser();
		break;
	}

	default:
	{
		Transactions();
		break;
	}
	}



}

//======Print Fonctions=============================================================
void PrintMenu()
{

	cout << "\n====================================================================\n";
	cout << setw(40) << "                Main Menu Screen ";
	cout << "\n====================================================================\n\n";

	cout << setw(15) << left << "         [1] Show Clients List." << endl;

	cout << setw(15) << left << "         [2] Add New Client." << endl;

	cout << setw(15) << left << "         [3] Delate Client." << endl;

	cout << setw(15) << left << "         [4] Update Client Info." << endl;

	cout << setw(15) << left << "         [5] Find Client." << endl;

	cout << setw(15) << left << "         [6] Transactions." << endl;

	cout << setw(15) << left << "         [7] Exit." << endl;

	cout << "\n====================================================================\n\n";



}


//======Main Fonctions===================================================================



void GetChoiceFromUser()
{
	system("cls");
	int choice;

	PrintMenu();
	cout << "Choose What You Want To Do ? [ 1 to 7 ]  : ";
	cin >> choice;


	switch (choice)
	{
	case 1:
	{
		system("cls");
		ShowClientList();
		GetChoiceFromUser();
		break;
	}

	case 2:
	{
		system("cls");
		AddNewClient();
		GetChoiceFromUser();
		break;
	}

	case 3:
	{
		system("cls");
		DelateClient();
		GetChoiceFromUser();
		break;
	}

	case 4:
	{
		system("cls");
		UpdateClientInfo();
		GetChoiceFromUser();
		break;
	}

	case 5:
	{
		system("cls");
		FindClient();
		GetChoiceFromUser();
		break;
	}

	case 6:
	{
		system("cls");
		Transactions();
		GetChoiceFromUser();
		break;
	}

	case 7:
		break;


	default:
	{
		GetChoiceFromUser();
		break;
	}
	}
}

int main()
{
	GetChoiceFromUser();

	return 0;
}