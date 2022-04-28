
#include<iostream>
#include<string>
#include<vector>
#include<exception>
#include<Windows.h>
#include<iomanip>
#include<algorithm>
#include<fstream>
using namespace std;

class Exception
{
private:
	string m_message;
public:
	Exception(const string& message) :m_message(message) {}

	string What()const { return this->m_message; }
};

template<class T>
class SeasonTicket
{
private:
	T m_costOfTicket;
	int m_amountOfDays;
	int m_amountOfTrainings;
public:

	SeasonTicket() :m_amountOfDays(0), m_amountOfTrainings(0), m_costOfTicket(0) {}
	SeasonTicket(T cost, int days, int trainings) :m_costOfTicket(cost), m_amountOfDays(days), m_amountOfTrainings(trainings) {}
	~SeasonTicket()
	{
		cout << "\nObject client was deleted due the ";
	}

	void SetCost(T cost) { this->m_costOfTicket = cost; }
	void SetDays(int days) { this->m_amountOfDays = days; }
	void SetTrainings(int trainings) { this->m_amountOfTrainings = trainings; }

	T GetCost() const { return this->m_costOfTicket; }
	int GetAmountOfDays() const { return this->m_amountOfDays; }
	int GetAmountOfTrainings() const { return this->m_amountOfTrainings; }
};

class Client :public SeasonTicket<double>
{
private:
	string m_fullName;
	string m_regularCustomer;
public:

	Client() {}
	Client(double cost, int days, int trainings, string name, string regularity) :SeasonTicket(cost, days, trainings)
	{
		this->m_fullName = name;
		this->m_regularCustomer = regularity;

		for (int i = 0; i < name.size(); i++)
		{
			if (name[i] > '0' && name[i] < '9') throw runtime_error("There is numbers in the name!\n");
		}
	}
	~Client()
	{
		cout << "\nObject client was deleted!\n";
	}

	friend istream& operator >>(istream& in, Client& client);
	friend ostream& operator <<(ostream& out, Client& client);

	void SetFullName(string name) { this->m_fullName = name; }
	void SetRegularity(string state) { this->m_regularCustomer = state; }

	string GetName() const { return this->m_fullName; }
	string GetRegularity() const { return this->m_regularCustomer; }
};

istream& operator >>(istream& in, Client& client)
{
	cout << "\nEnter your full name: ";
	in >> client.m_fullName;

	cout << "\nEnter your regularity: ";
	in >> client.m_regularCustomer;

	return in;
}

ostream& operator <<(ostream& out, Client& client)
{
	out <<"Full name:  "<< client.m_fullName << " Regularity: " << client.m_regularCustomer << endl;
	return out;
}

//Flag showpos
class Trainer
{
private:
	string m_nameOfTrainer;
	int m_amount;

public:
	Trainer() :m_amount(0), m_nameOfTrainer("NULL") {}
	Trainer(string name, int amount) :m_nameOfTrainer(name), m_amount(amount) {}
	Trainer(const Trainer& obj)
	{
		this->m_amount = obj.m_amount;
		this->m_nameOfTrainer = obj.m_nameOfTrainer;
	}

	void DisplayTrainerInformation()
	{
		cout.setf(ios::showpos);
		cout << "Description - " << this->m_nameOfTrainer
			<< "\nAmount: " << this->m_amount << endl;
		cout.unsetf(ios::showpos);
	}

	void SetNameOfTrainer(string name) { this->m_nameOfTrainer = name; }
	void SetAmount(int amount) { this->m_amount = amount; }

	string GetNameOfTrainer() const { return this->m_nameOfTrainer; }
	int GetAmount() const { return this->m_amount; }
};

bool operator < (const Client& first, const Client& second)
{
	return first.GetName() < second.GetName();
}

class Database
{
private:
	template<class T>
	class EnteringOperations
	{
	public:

		void CleareBuffer()
		{
			if (char(cin.peek()) == '\n')
				cin.ignore();
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(32767, '\n');
			}
		}
		
		string GetCorrectAnswer()
		{
			string userInput;
			bool isFinded = true;

			while (isFinded)
			{
				cin >> userInput;

				try
				{
					if (userInput == "Y" || userInput == "y" || userInput == "Yes" || userInput == "yes")
					{
						isFinded = false;

					}
					else if (userInput == "N" || userInput == "n" || userInput == "no" || userInput == "No")
					{
						isFinded = false;
					}
					else
					{
						throw runtime_error("Not correct answer!");
						cin.clear();
					}
				}
				catch (runtime_error exception)
				{
					cout << "Error: " << exception.what() << "\nTry again:";
				}
			}

			return userInput;
		}

		string GetCorrectValue(int minValue, int middleValue, int maxValue, int userValue, bool& isRight)
		{
			string clientTicket;

			if (userValue == minValue)
			{
				clientTicket = "Standart";
				isRight = true;
			}
			else if (userValue == middleValue)
			{
				clientTicket = "Special";
				isRight = true;
			}
			else if (userValue == maxValue)
			{
				clientTicket = "Premium";
				isRight = true;
			}
			else
			{
				isRight = false;
			}

			return clientTicket;
		}

		T GetValue()
		{
			T userValue;

			while (!(cin >> userValue) && cin.get() != '\n')
			{
				cout << "Erorr connected with your input,try again: ";
				cin.clear();
				while (cin.get() != '\n');
			}

			return userValue;
		}
	};

	vector<Client*> m_clients;

	EnteringOperations<int> m_operations;
public:

	void CleareBuffer()
	{
		m_operations.CleareBuffer();
	}

	bool IsEmpty()
	{
		if (m_clients.size() == 0) return true;
		else return false;
	}

	string GetCorrectAnswer()
	{
		return m_operations.GetCorrectAnswer();
	}

	string GetCorrectValue(int minValue, int middleValue, int maxValue, int userValue, bool& isRightCost)
	{
		return m_operations.GetCorrectValue(minValue, middleValue, maxValue, userValue, isRightCost);
	}

	bool GetCorrectAmountOfDays(int userValue)
	{
		if (userValue >= 1 && userValue <= 31) return true;
		else
		{
			cout << "\nNot correct value,try again\n";
			return false;
		}
	}

	int GetValue()
	{
		return m_operations.GetValue();
	}

	void InsertNewPersonInDatabase()
	{
		string name = "", regularity;
		double maxPrice = 300, middlePrice = 200, minPrice = 100;
		int cost = 0, amountOfDays = 0, amountOfTrainings = 0;
		bool isRightCost = false;

		cout << "\tEntering information about Client\n\n";

		CleareBuffer();

		cout << "Please, enter full name of new Client: ";
		getline(cin, name);

		cout << "Is this client regular in trainigs(Y/N): ";

		bool isWorking = true;

		regularity = GetCorrectAnswer();

		cout.unsetf(ios::scientific);
		cout.setf(ios::fixed);

		cout << "Choose the cost of Season ticket: "
			<< "\n(Standard) - " << setw(7) << right << setprecision(2) << minPrice
			<< "\n(Special)  - " << setw(7) << right << setprecision(2) << middlePrice
			<< "\n(Premium)  - " << setw(7) << right << setprecision(2) << maxPrice
			<< "\n\nYour choice>> ";

		cout.width(0);

		cost = GetValue();

		GetCorrectValue(minPrice, middlePrice, maxPrice, cost, isRightCost);

		while (isWorking)
		{
			if (isRightCost == true) isWorking = false;
			else
			{
				cout << "\nChoose right cost,try again: ";
				cost = GetValue();
				GetCorrectValue(minPrice, middlePrice, maxPrice, cost, isRightCost);
			}
		}
		isWorking = true;
		bool isRightAmountOfdays = false;

		cout << "Please, enter amount of days you want to go(max 31 days): ";
		amountOfDays = GetValue();

		while (isWorking)
		{
			if (GetCorrectAmountOfDays(amountOfDays) == true) isWorking = false;
			else
			{
				cout << "Enter value: ";
				amountOfDays = GetValue();
			}
		}
		isWorking = true;

		cout << "Please, enter how much training will you have with the trainer(0 - 7): ";
		amountOfTrainings = GetValue();

		while (isWorking)
		{
			if (amountOfTrainings > 7 || amountOfTrainings < 0)
			{
				cout << "Not correct value, try again: ";
				amountOfTrainings = GetValue();
			}
			else isWorking = false;
		}
		try
		{
			m_clients.push_back(new Client(cost, amountOfDays, amountOfTrainings, name, regularity));
		}
		catch (runtime_error exception)
		{
			cout << "Error: " << exception.what() << endl;
		}

	}

	void DeleteFromDatabase()
	{
		int numberOfClient;
		int ordinalNumberInList = 1;

		cout << "Enter number of client you would like to delete: " << endl;
		cout << "\n\tDatabase of Clients" << endl;
		cout << "===================================================" << endl << endl;

		for (int i = 0; i < m_clients.size(); i++)
		{
			cout << ordinalNumberInList << ") " << m_clients[i]->GetName() << endl;
			ordinalNumberInList++;
		}

		cout << "\n===================================================" << endl;
		cout << "\nYour choice>> ";

		numberOfClient = GetValue();
		numberOfClient--;

		bool isFinded = false;

		if (numberOfClient >= 0 && numberOfClient <= m_clients.size())
		{
			for (int i = 0; i < m_clients.size(); i++)
			{
				if (i == numberOfClient)
				{
					isFinded = true;
				}
				else isFinded = false;
			}
		}

		if (isFinded == true)
		{
			cout << "\nClient (" << m_clients[numberOfClient]->GetName() << ") successfully  deleted" << endl;
			m_clients.erase(m_clients.begin() + numberOfClient);
		}
		else cout << "\nPerson with such number not finded!\n";
	}

	void DisplayPersonsDatabase()
	{
		int numberInList = 1;

		for (int i = 0; i < m_clients.size(); i++)
		{
			cout << "\n\tNumber of Client: " << numberInList << "\nFull Name: " << m_clients[i]->GetName() << endl;
			cout << "Amount of days : " << m_clients[i]->GetAmountOfDays() << endl;
			cout << "Regular visitor: " << m_clients[i]->GetRegularity() << endl;
			cout << "Amount of trainigs: " << m_clients[i]->GetAmountOfTrainings() << endl;
			numberInList++;
		}

		cout << "\nAmount of Clients: " << m_clients.size() << endl;
	}

	void EditPersonInDatabase()
	{
		int numberOfClient = 0;

		cout << "Enter number of client you would like to edit: ";
		int ordinalNumberInList = 1;

		cout << "\n\tDatabase of Clients" << endl;
		cout << "===================================================" << endl << endl;

		for (int i = 0; i < m_clients.size(); i++)
		{
			cout << ordinalNumberInList << ") " << m_clients[i]->GetName() << endl;
			ordinalNumberInList++;
		}

		cout << "\n===================================================" << endl;
		cout << "\nYour choice>> ";

		numberOfClient = GetValue();
		numberOfClient--;

		if (numberOfClient >= 0 && numberOfClient <= m_clients.size())
		{
			string name = "";
			string regularity = "";
			int amountOfDays = 0;
			int amountOfTrainings = 0;
			int maxPrice = 300;
			int middlePrice = 200;
			int minPrice = 100;
			int cost = 0;

			CleareBuffer();

			cout << "Please, enter new full name of new Client: ";
			getline(cin, name);

			cout << "Is this client regular in trainigs(Y/N):  ";
			regularity = GetCorrectAnswer();

			cout << "Choose the cost of Season ticket: "
				<< "\n(Standard) - " << setw(5) << right << setprecision(1) << minPrice
				<< "\n(Special)  - " << setw(5) << right << setprecision(1) << middlePrice
				<< "\n(Premium)  - " << setw(5) << right << setprecision(1) << maxPrice
				<< "\n\nYour choice>> ";
			cost = GetValue();

			cout << "Please, enter amount of days you want to go(max 31 days): ";
			amountOfDays = GetValue();

			cout << "Please, enter how much training will you have with the trainer(0 - 7): ";
			amountOfTrainings = GetValue();
			bool isWorking = true;

			while (isWorking)
			{
				if (amountOfTrainings < 0 && amountOfTrainings>7)
				{
					cout << "Try again: ";
					amountOfDays = GetValue();
				}
				else isWorking = false;
			}

			cout << "\nClient (" << m_clients[numberOfClient]->GetName() << ") successfully  edited" << endl;

			m_clients[numberOfClient]->SetFullName(name);
			m_clients[numberOfClient]->SetRegularity(regularity);
			m_clients[numberOfClient]->SetTrainings(amountOfTrainings);
			m_clients[numberOfClient]->SetDays(amountOfDays);
		}
	}

	void CleareListOfClients()
	{

		m_clients.clear();

		try
		{
			if (m_clients.size() != 0) throw "All memory not clean!(Clients)\n";
		}
		catch (const char* exception)
		{
			cout << "Error: " << exception << endl;
			throw;
		}
	}

	void SortListOfPersons()
	{

		sort(m_clients.begin(), m_clients.end());
	}

	void FindByNameOfClients()
	{
		string userInput;
		bool isFinded = false;
		int numberInList = 0;
		vector<Client*> tempClients;
		Database operations;

		operations.CleareBuffer();

		cout << "\nEnter fullname: ";
		getline(cin, userInput);

		for (int i = 0; i < m_clients.size(); i++)
		{
			if (m_clients[i]->GetName() == userInput)
			{
				isFinded = true;
				numberInList = i;
			}

			if (isFinded == true) tempClients.push_back(m_clients[numberInList]);
		}

		if (tempClients.size() == 0) cout << "\nThere is no Clients with such input!\n";
		else
		{
			cout << "\nClients with such name:" << endl;

			for (int i = 0; i < tempClients.size(); i++)
			{
				cout << "\nFull Name: " << tempClients[i]->GetName() << endl;
				cout << "Amount of days : " << tempClients[i]->GetAmountOfDays() << endl;
				cout << "Regular visitor: " << tempClients[i]->GetRegularity() << endl;
				cout << "Amount of trainigs: " << tempClients[i]->GetAmountOfTrainings() << endl;
			}

			cout << "\nAmount of Clients: " << tempClients.size() << endl;

		}

		tempClients.clear();
	}

	void FindByAmountOfDaysInTicket()
	{
		int amountOfDays;
		bool isWorking = true;
		bool isFinded = false;
		int numberInList = 0;
		vector<Client*> tempClients;

		cout << "\nEnter amount of days in the ticket: ";

		amountOfDays = GetValue();

		while (isWorking)
		{
			if (GetCorrectAmountOfDays(amountOfDays) == true) isWorking = false;
			else
			{
				cout << "Enter value: ";
				amountOfDays = GetValue();
			}
		}

		for (int i = 0; i < m_clients.size(); i++)
		{
			if (m_clients[i]->GetAmountOfDays() <= amountOfDays)
			{
				isFinded = true;
				numberInList = i;
			}

			if (isFinded == true) tempClients.push_back(m_clients[numberInList]);
		}

		if (tempClients.size() == 0) cout << "\nThere is no Clients with such input!\n";
		else
		{
			cout << "\nClients with such amount of trainings and less:" << endl;

			for (int i = 0; i < tempClients.size(); i++)
			{
				cout << "\nFull Name: " << tempClients[i]->GetName() << endl;
				cout << "Amount of days : " << tempClients[i]->GetAmountOfDays() << endl;
				cout << "Regular visitor: " << tempClients[i]->GetRegularity() << endl;
				cout << "Amount of trainigs: " << tempClients[i]->GetAmountOfTrainings() << endl;
			}

			cout << "\nAmount of Clients: " << tempClients.size() << endl;
		}

		tempClients.clear();
	}

	void FindByAmountOfDaysWithCoach()
	{
		int amountOfTrainings;
		bool isWorking = true;
		bool isFinded = false;
		int numberInList = 0;
		vector<Client*> tempClients;

		cout << "\nEnter amount of trainigs with coach: ";

		amountOfTrainings = GetValue();

		while (isWorking)
		{
			if (amountOfTrainings > 7 || amountOfTrainings < 0)
			{
				cout << "Not correct value, try again: ";
				amountOfTrainings = GetValue();
			}
			else isWorking = false;
		}

		for (int i = 0; i < m_clients.size(); i++)
		{
			if (m_clients[i]->GetAmountOfDays() <= amountOfTrainings)
			{
				isFinded = true;
				numberInList = i;
			}

			if (isFinded == true) tempClients.push_back(m_clients[numberInList]);
		}

		if (tempClients.size() == 0) cout << "\nThere is no Clients with such input!\n";
		else
		{
			cout << "\nClients with such amounts of trainings with coach:" << endl;

			for (int i = 0; i < tempClients.size(); i++)
			{
				cout << "\nFull Name: " << tempClients[i]->GetName() << endl;
				cout << "Amount of days : " << tempClients[i]->GetAmountOfDays() << endl;
				cout << "Regular visitor: " << tempClients[i]->GetRegularity() << endl;
				cout << "Amount of trainigs: " << tempClients[i]->GetAmountOfTrainings() << endl;
			}

			cout << "\nAmount of Clients: " << tempClients.size() << endl;

		}

		tempClients.clear();
	}

	void FindByParameter()
	{
		int userChoice;

		cout << "\nChoose the parameter to find by:\n"
			<< "\n(1) - By name of Client"
			<< "\n(2) - By ticket"
			<< "\n(3) - By amount of trainings with coach"
			<< "\n\nYour choice>> ";

		switch (userChoice = m_operations.GetValue())
		{
		case 1:
			FindByNameOfClients();
			break;
		case 2:
			FindByAmountOfDaysInTicket();
			break;
		case 3:
			FindByAmountOfDaysWithCoach();
			break;
		default:
			cout << "\nThere is no case with such number!\n";
			break;
		}
	}
};

class Gym
{
private:
	int m_amountOfTrainers;

	Database m_database;

	vector<Trainer*> m_trainers;

	vector<string> m_necassaryTrainers;
public:
	void EditInformationInFile()
	{
		string userInput;
		string fileName;
		string buffer;
		string newNameOfTrainer;
		ifstream fin;
		int numberOfTrainer;
		bool isFinded = false;

		fileName = EnterFileName();

		fin.open(fileName, ios::in);

		try
		{
			if (fin.is_open() == false) throw runtime_error("File cant't be open or not exists!\n");
			if(fin.good() == false) throw runtime_error("There are some bad bits!\n");
			if(fin.bad() == true) throw runtime_error("There are some bad bits!\n");
			if(fin.fail() == true) throw runtime_error("There are problems with necessary operations!\n");

		}
		catch (runtime_error exception)
		{
			cout << "Error: " << exception.what() << endl;
			return;
		}
		
		try
		{
			if (GetFileSize(fileName) == -1) throw runtime_error("File is empty!\n");

		}
		catch (runtime_error exception)
		{
			cout << "Error: " << exception.what() << endl;
			return;
		}

		cout << "\n============================================\n\n";

		while (getline(fin, buffer))
		{
			cout << buffer << endl;
		}

		cout << "============================================\n";

		fin.close();

		cout << "\nChoose information you would like to edit: ";
		getline(cin, userInput);

		for (int i = 0; i < m_trainers.size(); i++)
		{
			if (m_trainers[i]->GetNameOfTrainer() == userInput)
			{
				isFinded = true;
				numberOfTrainer = i;
			}
		}
		
		if (isFinded == true)
		{
			cout << "\nEnter new string: ";
			getline(cin, newNameOfTrainer);

			m_trainers[numberOfTrainer]->SetNameOfTrainer(newNameOfTrainer);

			ofstream fout;
			fout.open(fileName, ios::out);

			try
			{
				if (fout.is_open() == false) throw runtime_error("File cant't be open or not exists!\n");
				if (fout.good() == false) throw runtime_error("There are some bad bits!\n");
				if (fout.bad() == true) throw runtime_error("There are some bad bits!\n");
				if (fout.fail() == true) throw runtime_error("There are problems with necessary operations!\n");

			}
			catch (runtime_error exception)
			{
				cout << "Error: " << exception.what() << endl;
			}

			for (int i = 0; i < m_trainers.size(); i++)
			{
				fout << m_trainers[i]->GetNameOfTrainer() << endl;
				fout << "Amount of trainers: x" << m_trainers[i]->GetAmount() << endl<<endl;
			}

			fout.close();

			fin.open(fileName, ios::in);

			cout << "\n============================================\n\n";

			while (getline(fin, buffer))
			{
				cout << buffer << endl;
			}

			cout << "============================================\n";

			cout << "\nAll information was recorded!\n";
			fin.close();

		}
		else cout << "There is no information with such input!\n\n";
		
	}

	void DeleteInformationFromFile()
	{
		string userInput;
		string fileName;
		string buffer;
		string newNameOfTrainer;
		ifstream fin;
		int numberOfTrainer;
		bool isFinded = false;

		fileName = EnterFileName();

		fin.open(fileName, ios::in);

		try
		{
			if (fin.is_open() == false) throw runtime_error("File cant't be open or not exists!\n");
			if (fin.good() == false) throw runtime_error("There are some bad bits!\n");
			if (fin.bad() == true) throw runtime_error("There are some bad bits!\n");
			if (fin.fail() == true) throw runtime_error("There are problems with necessary operations!\n");

		}
		catch (runtime_error exception)
		{
			cout << "Error: " << exception.what() << endl;
			return;
		}

		try
		{
			if (GetFileSize(fileName) == -1) throw runtime_error("File is empty!\n");

		}
		catch (runtime_error exception)
		{
			cout << "Error: " << exception.what() << endl;
			return;
		}

		cout << "\n============================================\n\n";

		while (getline(fin, buffer))
		{
			cout << buffer << endl;
		}

		cout << "============================================\n";

		fin.close();

		cout << "\nChoose information you would like to remove: ";
		getline(cin, userInput);

		for (int i = 0; i < m_trainers.size(); i++)
		{
			if (m_trainers[i]->GetNameOfTrainer() == userInput)
			{
				isFinded = true;
				numberOfTrainer = i;
			}
		}

		if (isFinded == true)
		{
			m_trainers.erase(m_trainers.begin() + numberOfTrainer);
			ofstream fout;
			fout.open(fileName, ios::out);

			try
			{
				if (fout.is_open() == false) throw runtime_error("File cant't be open or not exists!\n");
				if (fout.good() == false) throw runtime_error("There are some bad bits!\n");
				if (fout.bad() == true) throw runtime_error("There are some bad bits!\n");
				if (fout.fail() == true) throw runtime_error("There are problems with necessary operations!\n");

			}
			catch (runtime_error exception)
			{
				cout << "Error: " << exception.what() << endl;
			}

			for (int i = 0; i < m_trainers.size(); i++)
			{
				fout << m_trainers[i]->GetNameOfTrainer() << endl;
				fout << "Amount of trainers: x" << m_trainers[i]->GetAmount() << endl;
			}

			fout.close();

			fin.open(fileName, ios::in);

			cout << "\n============================================\n\n";

			while (getline(fin, buffer))
			{
				cout << buffer << endl;
			}

			cout << "============================================\n";

			cout << "\nAll information was recorded!\n";
			fin.close();

		}
		else cout << "There is no information with such input!\n\n";

	}

	void FindInformationInFile()
	{
		string userInput;
		string fileName;
		string buffer;
		ifstream fin;
		bool isFinded = false;

		fileName = EnterFileName();

		fin.open(fileName, ios::in);

		try
		{
			if (fin.is_open() == false) throw runtime_error("File cant't be open or not exists!\n");
			if (fin.good() == false) throw runtime_error("There are some bad bits!\n");
			if (fin.bad() == true) throw runtime_error("There are some bad bits!\n");
			if (fin.fail() == true) throw runtime_error("There are problems with necessary operations!\n");

		}
		catch (runtime_error exception)
		{
			cout << "Error: " << exception.what() << endl;
			return;
		}

		try
		{
			if (GetFileSize(fileName) == -1) throw runtime_error("File is empty!\n");
			
		}
		catch (runtime_error exception)
		{
			cout << "Error: " << exception.what() << endl;
			return;
		}
		

		cout << "\nEnter name of trainer you would like to find: ";
		getline(cin, userInput);

		cout << "\n============================================\n\n";

		while (getline(fin, buffer))
		{
			if (buffer == userInput)
			{
				isFinded = true;
				cout << buffer << endl;
				getline(fin, buffer);
				cout << buffer << endl<<endl;
			}
		}

		if (isFinded == false) cout << "\nThere is no information with such input!\n";

		cout << "\n============================================\n";
	}

	void WriteListToFile()
	{
		int userChoice;
		string fileName;
		bool isWorking = true;
		ofstream fout;

		fileName = EnterFileName();

		cout << "\nChoose option how to open the file: \n"
			<< "\n1) - Overwrite file"
			<< "\n2) - Add to file"
			<< "\n\nYour choice>> ";

		while (isWorking)
		{
			cin >> userChoice;

			if (cin.fail() == true)
			{
				cout << "\nError with your input, try again: ";
				cin.clear();
				cin.ignore(100, '\n');
			}
			else
			{
				isWorking = false;
			}
		}

		switch (userChoice)
		{
		case 1:
			fout.open(fileName, ios_base::trunc);

			try
			{
				if (fout.is_open() == false || fout.bad() == true) throw runtime_error("File can not be open or critical error appears!");
			}
			catch (runtime_error exception)
			{
				cout << "Error: " << exception.what() << endl;
				break;
			}

			cout << "\nFile opens!\n";

			for (int i = 0; i < m_trainers.size(); i++)
			{
				fout << m_trainers[i]->GetNameOfTrainer() << endl;
				fout << "Amount of trainers: x" << m_trainers[i]->GetAmount() << endl << endl;
			}

			fout.close();
			cout << "\nAll information was recorded!\n";
			break;
		case 2:
			fout.open(fileName, ios_base::app);

			try
			{
				if (fout.is_open() == false || fout.bad() == true) throw runtime_error("File can not be open or critical error appears!");
			}
			catch (runtime_error exception)
			{
				cout << "Error: " << exception.what() << endl;
				break;
			}

			for (int i = 0; i < m_trainers.size(); i++)
			{
				fout << m_trainers[i]->GetNameOfTrainer() << endl;
				fout << "Amount of trainers: x" << m_trainers[i]->GetAmount() << endl << endl;
			}

			fout.close();
			cout << "\nAll information was recorded!\n";
			break;
		default:
			cout << "\nThere is no case with such input!\n";
			break;
		}
	}

	int GetFileSize(string fileName)
	{
		ifstream fin(fileName, ios::in);
		int fileSize = 0;
		fin.seekg(0, ios::end);
		fileSize = fin.tellg();
		fin.close();

		return fileSize;
	}

	string EnterFileName()
	{
		string fileName;
		cin.ignore(100, '\n');

		cout << "Please, enter filename: ";
		getline(cin, fileName);
		fileName += ".txt";

		return fileName;
	}

	string GetFileName(string& fileName) const { return fileName; }

	void ReadFromFile()
	{
		string buffer;
		string fileName;
		bool isWorking = true;
		ifstream fin;

		fileName = EnterFileName();

		fin.open(fileName, ios_base::in);

		try
		{
			if (fin.is_open() == false || fin.bad() == true) throw runtime_error("File cant't be open or not exists!");
		}
		catch (runtime_error exception)
		{
			cout << "Error: " << exception.what() << endl;
			return;
		}

		cout << "\n============================================\n\n";

		while (!fin.eof())
		{
			getline(fin, buffer);
			cout << buffer << endl;
		}

		cout << "============================================\n";

		fin.close();
		cout << "\nAll information was read!\n";

	}

	void ShowClientsMenu()
	{
		cout << "\tMenu to manage clients"
			<< "\n(1) - Add new client to database"
			<< "\n(2) - Show list of clients"
			<< "\n(3) - Delete client from database"
			<< "\n(4) - Edit characteristics of clients"
			<< "\n(5) - Find by parameter"
			<< "\n(0) - Get back"
			<< "\n\nYour choice>> ";
	}

	bool FileIsEmpty(string fileName)
	{
		ifstream fin;
		fin.open(fileName, ios_base::in);

		if (fin.is_open() && fin.bad() == false)
		{
			if (fin.peek() == EOF) return true;
			else return false;
		}
	}

	void ShowTrainingsMenu()
	{
		cout << "\tMenu to manage trainings"
			<< "\n(1) - Add trainer to the gym"
			<< "\n(2) - Display list of Necessary trainers"
			<< "\n(3) - Display list of trainers"
			<< "\n(4) - Menu to work with file"
			<< "\n(0) - Get back"
			<< "\n\nYour choice>> ";
	}

	void ShowCommonMenu()
	{
		cout << "\tCommon menu to manage Gym"
			<< "\n(1) - Manage clients database"
			<< "\n(2) - Replenish trainings database"
			<< "\n(0) - Exit"
			<< "\n\nYour choice>> ";
	}

	void MenuToWorkWothFile()
	{
		cout << "\tMenu to work with file"
			<< "\n(1) - Write database to file"
			<< "\n(2) - Read information from file"
			<< "\n(3) - Find information in file"
			<< "\n(4) - Edit information in file"
			<< "\n(5) - Delete information from file"
			<< "\n(0) - Get back"
			<< "\n\nYour choice>> ";
	}

	bool CheckForEnoughtOfTrainers(int minimalValue)
	{
		try
		{
			if (m_trainers.size() != minimalValue)
			{
				throw runtime_error("Not enought of trainers in the GYM\n");
			}
		}
		catch (runtime_error except)
		{
			cout << "Finded except: " << except.what() << endl;
		}
	}

	bool IsEmpty() const
	{
		if (m_trainers.size() == 0) return true;
		else return false;
	}

	void SortTrainers()
	{
		sort(m_trainers.begin(), m_trainers.end());
	}

	void SortNecassaryTrainers()
	{
		sort(m_necassaryTrainers.begin(), m_necassaryTrainers.end());

	}

	void CreateListOfNecessaryTrainers()
	{
		m_necassaryTrainers.push_back("Butterfly");
		m_necassaryTrainers.push_back("Treadmill");
		m_necassaryTrainers.push_back("Stepper");
		m_necassaryTrainers.push_back("Orbitrek");
		m_necassaryTrainers.push_back("Climber");
		m_necassaryTrainers.push_back("Hammer");
		m_necassaryTrainers.push_back("Smith trainer");
		m_necassaryTrainers.push_back("Crossover");
		m_necassaryTrainers.push_back("Gravitron");
		m_necassaryTrainers.push_back("Dumbbell rack");
	}

	void DisplayListOfNecessaryTrainers()
	{
		int ordinalNumber = 1;

		cout << "\tList of neccesery trainers" << endl;

		for (int i = 0; i < m_necassaryTrainers.size(); i++)
		{
			cout << ordinalNumber << ") " << m_necassaryTrainers[i] << endl;
			ordinalNumber++;
		}
	}

	void AddNewTrainerInGym()
	{
		string nameOfTrainer;
		int amountOfTrainers;
		Database operations;

		operations.CleareBuffer();

		cout << "Please, enter name of trainer: ";
		getline(cin, nameOfTrainer);

		cout << "Enter amount of " << nameOfTrainer << "(<10): ";
		amountOfTrainers = operations.GetValue();

		bool isWorking = true;

		while (isWorking)
		{
			if (amountOfTrainers < 0 || amountOfTrainers > 10)
			{
				cout << "\nNot correct value, try again: \n";
				amountOfTrainers = operations.GetValue();
			}
			else isWorking = false;
		}

		m_trainers.push_back(new Trainer(nameOfTrainer, amountOfTrainers));

		bool isFinded = false;
		int numberOfTrainer;

		for (int i = 0; i < m_necassaryTrainers.size(); i++)
		{
			if (nameOfTrainer == m_necassaryTrainers[i])
			{
				isFinded = true;
				numberOfTrainer = i;
			}
		}
		if (isFinded == true)
		{
			m_necassaryTrainers.erase(m_necassaryTrainers.begin() + numberOfTrainer);
		}
	}

	void DisplayListOfTrainersInGym()
	{
		int ordinalNumber = 1;

		cout << "\tList of trainers in the Gym" << endl;

		for (const auto& trainer : m_trainers)
		{
			cout << ordinalNumber << ")";
			trainer->DisplayTrainerInformation();
			cout << endl;
			ordinalNumber++;
		}
	}

	void CleareListOfTrainers()
	{
		m_trainers.clear();

		try
		{
			if (m_trainers.size() != 0) throw "All memory not clean(Trainers)!\n";
		}
		catch (const char* exception)
		{
			cout << "Error: " << exception << endl;
			throw;
		}
	}

	bool IsEmptyNecessaryList()
	{
		if (m_necassaryTrainers.size() == 0) return true;
		else return false;
	}

	void SetAmountOfTrainers(int number) { this->m_amountOfTrainers = number; }

	int GetAmountOfTrainersByOnePosition() const { return this->m_amountOfTrainers; }
};

void Quit()
{
	exit(0);
}

void ShutdownProgram()
{
	cout << "\nFunction of shuttingdown the program!\n";
	set_terminate(Quit);
	throw 0;
}

int main()
{
	Gym gym;
	Database operations;

	bool isWorking = true;
	bool isWorkingClietnsMenu = true;
	bool isWorkingTrainingsMenu = true;
	bool isWorkingWithFile = true;
	bool fileIsOpen = false;
	bool isSortedForNTrainers = false;
	bool isSortedForSTrainers = false;
	bool isSorted = false;

	string fileName;

	gym.CreateListOfNecessaryTrainers();

	while (isWorking)
	{
		gym.ShowCommonMenu();
		int menuChoice = operations.GetValue();

		switch (menuChoice)
		{
		case 1:
			isWorkingClietnsMenu = true;

			while (isWorkingClietnsMenu)
			{
				gym.ShowClientsMenu();

				switch (menuChoice = operations.GetValue())
				{
				case 1:
					operations.InsertNewPersonInDatabase();
					break;
				case 2:
					if (operations.IsEmpty() == false)
					{
						string userChoice;

						operations.DisplayPersonsDatabase();

						if (isSorted == false)
						{
							cout << "\nWould you like to Sort this list?(Y/N)\n"
								<< "\nYour choice>> ";
							userChoice = operations.GetCorrectAnswer();

							if (userChoice == "Y" || userChoice == "y" || userChoice == "Yes" || userChoice == "yes")
							{
								system("cls");
								operations.SortListOfPersons();
								cout << "\tList after sorting\n";
								operations.DisplayPersonsDatabase();
								isSorted = true;
							}
						}
					}
					else cout << "\nDatabase is empty!\n";
					break;
				case 3:
					if (operations.IsEmpty() == false) operations.DeleteFromDatabase();
					else cout << "\nDatabase is empty!\n";
					break;
				case 4:
					if (operations.IsEmpty() == false) operations.EditPersonInDatabase();
					else cout << "\nDatabase is empty!\n";
					break;
				case 5:
					if (operations.IsEmpty() == false) operations.FindByParameter();
					else cout << "\nDatabase is empty!\n";
					break;
				case 0:
					isWorkingClietnsMenu = false;
					break;
				default:
					cout << "\nThere is no case with such input, try again!\n";
					break;
				}
				system("pause");
				system("cls");
			}
			break;
		case 2:
			isWorkingTrainingsMenu = true;

			while (isWorkingTrainingsMenu)
			{
				gym.ShowTrainingsMenu();

				switch (menuChoice = operations.GetValue())
				{
				case 1:
					gym.AddNewTrainerInGym();
					break;
				case 2:
					if (gym.IsEmptyNecessaryList() == false)
					{
						string userChoice;

						gym.DisplayListOfNecessaryTrainers();

						if (isSortedForNTrainers == false)
						{
							cout << "\nWould you like to Sort this list?(Y/N)\n"
								<< "\nYour choice>> ";
							userChoice = operations.GetCorrectAnswer();

							if (userChoice == "Y" || userChoice == "y" || userChoice == "Yes" || userChoice == "yes")
							{
								system("cls");
								gym.SortNecassaryTrainers();
								cout << "\tList after sorting\n";
								gym.DisplayListOfNecessaryTrainers();
								isSortedForNTrainers = true;
							}
						}

					}
					else cout << "\nList of necessary trainers is empty!\n";
					break;
				case 3:
					if (gym.IsEmpty() == false)
					{
						string userChoice;

						gym.DisplayListOfTrainersInGym();

						if (isSortedForSTrainers == false)
						{
							cout << "\nWould you like to Sort this list?(Y/N)\n"
								<< "\nYour choice>> ";
							userChoice = operations.GetCorrectAnswer();

							if (userChoice == "Y" || userChoice == "y" || userChoice == "Yes" || userChoice == "yes")
							{
								system("cls");
								gym.SortTrainers();
								cout << "\tList after sorting\n";
								gym.DisplayListOfTrainersInGym();
								isSortedForSTrainers = true;
							}
						}
					}
					else cout << "\nList of trainers is empty!\n";
					break;
				case 4:
					isWorkingWithFile = true;

					while (isWorkingWithFile)
					{
						gym.MenuToWorkWothFile();
						menuChoice = operations.GetValue();

						switch (menuChoice)
						{
						case 1:
							if (gym.IsEmpty() == false) gym.WriteListToFile();
							else cout << "\nDatabase is empty!\n";
							fileIsOpen = true;
							break;
						case 2:
							gym.ReadFromFile();
							break;
						case 3:
							if (fileIsOpen == true) gym.FindInformationInFile();
							else cout << "\nWrite database to file!\n";
							break;
						case 4:
							if (fileIsOpen == true) gym.EditInformationInFile();
							else cout << "\nWrite database to file!\n";
							break;
						case 5:
							if (fileIsOpen == true) gym.DeleteInformationFromFile();
							else cout << "\nWrite database to file!\n";
							break;
						case 0:
							isWorkingWithFile = false;
							break;
						default:
							cout << "\nThere is no case with such input, try again!\n";
							break;
						}
						system("pause");
						system("cls");
					}
					break;
				case 0:
					isWorkingTrainingsMenu = false;
					break;
				default:
					cout << "\nThere is no case with such input, try again!\n";
					break;
				}
				system("pause");
				system("cls");
			}
			break;
		case 0:
			try
			{
				ShutdownProgram();
			}
			catch (int exception)
			{
			}
			isWorking = false;
			break;
		default:
			cout << "\nThere is no case with such input, try again!\n";
			break;
		}
		system("pause");
		system("cls");
	}

	try
	{
		gym.CleareListOfTrainers();
		operations.CleareListOfClients();
	}
	catch (const char* exception)
	{
		cout << "Clean up memory!" << exception << endl;
	}
}

