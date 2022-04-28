#include<map>
#include<list>
#include <iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
#include<map>

using namespace std;

template<class T>
class Sportsman
{
private:
	string fullName;
	int age;
	T weight;
	T height;

public:

	friend ostream& operator<<(ostream& out, Sportsman<double>& operand)
	{
		out << operand.DisplayInformationAboutSportsman();
		return out;
	}
	Sportsman()
	{
		this->age = 0;
		this->fullName = "NULL";
		this->height = 0;
		this->weight = 0;
	}

	Sportsman(string name, int age, T weight, T height)
	{
		this->fullName = name;
		this->age = age;
		this->weight = weight;
		this->height = height;
	}

	Sportsman(const Sportsman& obj) :fullName(obj.fullName), age(obj.age), weight(obj.weight), height(obj.height) {}

	void DisplayInformationAboutSportsman()
	{
		cout << "Full name of the Sporstsmen - " << this->fullName << endl;
		cout << "Current age - " << this->age << endl;
		cout << "Current Weight - " << this->weight << endl;
		cout << "Current Height - " << this->height << endl << endl;
	}

	void WriteInFile(string fileName)
	{
		ofstream fout(fileName, ios_base::app);

		if (!fout.is_open()) cout << "\nError connected with opening file!\n";
		else
		{
			fout << "===========================================================" << endl;
			fout << "Full name of the Sporstsmen - " << this->fullName << endl;
			fout << "\nCurrent age - " << this->age << endl;
			fout << "\nCurrent Weight - " << this->weight << endl;
			fout << "\nCurrent Height - " << this->height << endl;
			fout << "===========================================================" << endl;
			fout << endl;
		}
		fout.close();

		cout << "\Information recorded successfully\n";
	}

	void SetFullName(string title) { this->fullName = title; }
	void SetAge(int age) { this->age = age; }
	void SetWeight(T weight) { this->weight = weight; }
	void SetHeight(T height) { this->height = height; }

	string GetFullName() const { return this->fullName; }
	int GetAge() const { return this->age; }
	T GetWeight() const { return this->weight; }
	T GetHeight() const { return this->height; }
};

class InsertOperations
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

	double GetValue()
	{
		double userValue;
		while (!(cin >> userValue) && cin.get() != '\n')
		{
			cout << "Error connected with input, try again: ";
			cin.clear();
			cin.ignore();
			while (cin.get() != '\n');
		}

		return userValue;
	}
};

class Competiton
{
private:
	list<Sportsman<double>> groopOfSportsmen;
	list<Sportsman<double>>::iterator ptrOnList;
	InsertOperations operations;
public:

	
	void AppendToList()
	{
		string nameOfSportsman;
		int ageOfSportman;
		double weightOfSportsman;
		double heightOfSportstman;

		cout << "\tAppending new person in list" << endl<<endl;

		operations.CleareBuffer();

		cout << "Please, enter full name of sportsman: ";
		getline(cin, nameOfSportsman);

		cout << "Enter age: ";
		ageOfSportman = operations.GetValue();

		cout << "Enter weight: ";
		weightOfSportsman = operations.GetValue();

		cout << "Enter height: ";
		heightOfSportstman = operations.GetValue();

		groopOfSportsmen.push_back(*new Sportsman<double>(nameOfSportsman, ageOfSportman, weightOfSportsman, heightOfSportstman));
	}

	void DisplayList()
	{
		this->ptrOnList = groopOfSportsmen.begin();

		while (ptrOnList != groopOfSportsmen.end())
		{
			ptrOnList->DisplayInformationAboutSportsman();
			ptrOnList++;
		}

		cout << "\nEnd of list reached!\n";

	}

	void EditList()
	{
		string nameOfSportsman;
		list<Sportsman<double>>::iterator currentPerson;
		bool isFinded = false;
		int ageOfSportsman;
		double weightOfSportsman, heightOfSportsman;

		operations.CleareBuffer();

		cout << "Enter name of Person, you would like to change: ";
		getline(cin, nameOfSportsman);

		this->ptrOnList = groopOfSportsmen.begin();

		while (ptrOnList != groopOfSportsmen.end())
		{
			if (nameOfSportsman == ptrOnList->GetFullName())
			{
				isFinded = true;
				currentPerson = ptrOnList;
			}
			ptrOnList++;
		}

		if (isFinded == true)
		{
			cout << "\nPerson is finded!\n";

			cout << "Please, enter full name of sportsman: ";
			getline(cin, nameOfSportsman);

			cout << "Enter age: ";
			ageOfSportsman = operations.GetValue();

			cout << "Enter weight: ";
			weightOfSportsman = operations.GetValue();

			cout << "Enter height: ";
			heightOfSportsman = operations.GetValue();

			currentPerson->SetFullName(nameOfSportsman);
			currentPerson->SetAge(ageOfSportsman);
			currentPerson->SetWeight(weightOfSportsman);
			currentPerson->SetHeight(heightOfSportsman);

			cout << "\nData is edited and new spotrsman added in list!\n";
		}
		else cout << "\nPerson with such input is not finded!";
	}

	bool IsEmpty() const
	{
		if (groopOfSportsmen.size() == 0) return true;
		else return false;
	}

	void DeleteFromList()
	{
		string nameOfSportsman;
		list<Sportsman<double>>::iterator currentPerson;
		bool isFinded = false;

		operations.CleareBuffer();

		cout << "Enter name of Person, you would like to delete: ";
		getline(cin, nameOfSportsman);

		this->ptrOnList = groopOfSportsmen.begin();

		while (ptrOnList != groopOfSportsmen.end())
		{
			if (nameOfSportsman == ptrOnList->GetFullName())
			{
				isFinded = true;
				currentPerson = ptrOnList;
			}
			ptrOnList++;
		}

		if (isFinded == true)
		{
			cout << "Person (" << nameOfSportsman << ") is deleted!";
			groopOfSportsmen.erase(currentPerson);
		}
		else cout << "\nPerson with such input is not finded!";
	}

	void FindInList()
	{
		string nameOfSportsman;
		list<Sportsman<double>>::iterator currentPerson;
		bool isFinded = false;

		operations.CleareBuffer();

		cout << "Enter name of Person, you would like to find: ";
		getline(cin, nameOfSportsman);

		this->ptrOnList = groopOfSportsmen.begin();

		while (ptrOnList != groopOfSportsmen.end())
		{
			if (nameOfSportsman == ptrOnList->GetFullName())
			{
				isFinded = true;
				currentPerson = ptrOnList;
			}
			ptrOnList++;
		}

		if (isFinded == true)
		{
			cout << "\nPerson is finded!\n";
			currentPerson->DisplayInformationAboutSportsman();

		} else cout << "\nPerson with such input is not finded!";
	}

	friend bool operator <(Sportsman<double>& first,Sportsman<double>& second);

	void SortList()
	{
		vector<Sportsman<double>> tempVector;
		list<Sportsman<double>> tempList;

		for (Sportsman<double> person:groopOfSportsmen)
		{
			tempVector.push_back(person);
		}

		sort(tempVector.begin(), tempVector.end());


		for (int  i = 0; i < tempVector.size(); i++)
		{
			tempList.push_back(tempVector[i]);
		}

		this->groopOfSportsmen = tempList;

		DisplayList();
		
		tempVector.clear();
		tempList.clear();
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

	void WriteInFileList()
	{
		int userChoice;
		list<Sportsman<double>>::iterator beginPtr = groopOfSportsmen.begin();
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

			while (beginPtr != groopOfSportsmen.end())
			{
				fout << "Full name: " << beginPtr->GetFullName() << endl;
				fout << "Age: " << beginPtr->GetAge() << endl;
				fout << "Weight: " << beginPtr->GetWeight() << endl;
				fout << "Height: " << beginPtr->GetHeight() << endl << endl;
				beginPtr++;
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

			while (beginPtr != groopOfSportsmen.end())
			{
				fout <<"Full name: "<< beginPtr->GetFullName() << endl;
				fout <<"Age: "<< beginPtr->GetAge() << endl;
				fout <<"Weight: "<<beginPtr->GetWeight() << endl;
				fout <<"Height: "<< beginPtr->GetHeight() << endl << endl;
				beginPtr++;
			}

			fout.close();
			cout << "\nAll information was recorded!\n";
			break;
		default:
			cout << "\nThere is no case with such input!\n";
			break;
		}

	}

	void ListMenu()
	{
		cout << "\tMenu" << endl;
		cout << "(1) - Append new person to list"
			<< "\n(2) - Display list"
			<< "\n(3) - Edit person"
			<< "\n(4) - Write to file list"
			<< "\n(5) - Delete from list"
			<< "\n(6) - Sort list"
			<< "\n(0) - Exit"
			<< "\n\nYour choice>> ";
	}

	void CleareList()
	{
		groopOfSportsmen.clear();

		try
		{
			if (groopOfSportsmen.size() != 0) throw "All memory not clean(Trainers)!\n";
		}
		catch (const char* exception)
		{
			cout << "Error: " << exception << endl;
			throw;
		}
	}
};

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

class Gym
{
private:
	int m_amountOfTrainers;

	InsertOperations operations;

	vector<Trainer> m_trainers;

	vector<Trainer>::iterator ptrOnVector;
public:
	void FindInVector()
	{
		string nameOfTrainer;
		vector<Trainer>::iterator currentTrainer;
		bool isFinded = false;

		operations.CleareBuffer();

		cout << "Enter name of Trainer, you would like to find: ";
		getline(cin, nameOfTrainer);

		this->ptrOnVector = m_trainers.begin();

		while (ptrOnVector != m_trainers.end())
		{
			if (nameOfTrainer == ptrOnVector->GetNameOfTrainer())
			{
				isFinded = true;
				currentTrainer = ptrOnVector;
			}
			ptrOnVector++;
		}

		if (isFinded == true)
		{
			cout << "\nPerson is finded!\n";
			currentTrainer->DisplayTrainerInformation();

		}
		else cout << "\nPerson with such input is not finded!";
	}

	void WriteVectorToFile()
	{
		int userChoice;
		vector<Trainer>::iterator beginPtr = m_trainers.begin();
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

			while (beginPtr != m_trainers.end())
			{
				
				fout << "Name: " << beginPtr->GetNameOfTrainer() << endl;
				fout << "Amount x: " << beginPtr->GetAmount() << endl << endl;
				beginPtr++;
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

			while (beginPtr != m_trainers.end())
			{

				fout << "Name: " << beginPtr->GetNameOfTrainer() << endl;
				fout << "Amount x: " << beginPtr->GetAmount() << endl << endl;
				beginPtr++;
			}

			fout.close();
			cout << "\nAll information was recorded!\n";
			break;
		default:
			cout << "\nThere is no case with such input!\n";
			break;
		}
	}

	void DeleteFromVector()
	{
		string nameOfTrainer;
		vector<Trainer>::iterator currentTrainer;
		bool isFinded = false;

		operations.CleareBuffer();

		cout << "Enter name of Person, you would like to delete: ";
		getline(cin, nameOfTrainer);

		this->ptrOnVector = m_trainers.begin();

		while (ptrOnVector != m_trainers.end())
		{
			if (nameOfTrainer == ptrOnVector->GetNameOfTrainer())
			{
				isFinded = true;
				currentTrainer = ptrOnVector;
			}
			ptrOnVector++;
		}

		if (isFinded == true)
		{
			cout << "Person (" << nameOfTrainer << ") is deleted!";
			m_trainers.erase(currentTrainer);
		}
		else cout << "\nPerson with such input is not finded!";
	}

	friend bool operator <(Trainer &first,Trainer &second);

	string EnterFileName()
	{
		string fileName;
		cin.ignore(100, '\n');

		cout << "Please, enter filename: ";
		getline(cin, fileName);
		fileName += ".txt";

		return fileName;
	}

	void EditList()
	{
		vector<Trainer>::iterator currentTrainer;
		bool isFinded = false;
		string nameOfTrainer;
		int amount;

		operations.CleareBuffer();

		cout << "Enter name of Trainer, you would like to change: ";
		getline(cin, nameOfTrainer);

		this->ptrOnVector = m_trainers.begin();

		while (ptrOnVector != m_trainers.end())
		{
			if (nameOfTrainer == ptrOnVector->GetNameOfTrainer())
			{
				isFinded = true;
				currentTrainer = ptrOnVector;
			}
			ptrOnVector++;
		}

		if (isFinded == true)
		{
			cout << "\nTrainer is finded!\n";

			cout << "Please, name of trainer: ";
			getline(cin, nameOfTrainer);

			cout << "Enter amount: ";
			amount = operations.GetValue();

			currentTrainer->SetNameOfTrainer(nameOfTrainer);
			currentTrainer->SetAmount(amount);
			

			cout << "\nData is edited!\n";
		}
		else cout << "\nTrainer with such input is not found!";
	}

	bool IsEmpty() const
	{
		if (m_trainers.size() == 0) return true;
		else return false;
	}

	void SortVector()
	{
		sort(m_trainers.begin(), m_trainers.end());

		DisplayElementsOfVector();
	}

	void AppendToVector()
	{
		string nameOfTrainer;
		int amountOfTrainers;

		operations.CleareBuffer();

		cout << "Please, enter name of trainer: ";
		getline(cin, nameOfTrainer);

		operations.CleareBuffer();

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

		m_trainers.push_back(*new Trainer(nameOfTrainer, amountOfTrainers));
	}

	void DisplayElementsOfVector()
	{
		int ordinalNumber = 1;
		
		cout << "\tList of trainers in the Gym" << endl;
		ptrOnVector = m_trainers.begin();

		while (ptrOnVector != m_trainers.end())
		{
			cout << ordinalNumber << ")";
			ptrOnVector->DisplayTrainerInformation();
			cout << endl;
			ordinalNumber++;
			ptrOnVector++;
		}
	}

	void VectorMenu()
	{
		cout << "\tMenu" << endl;
		cout << "(1) - Append new trainer to vector"
			<< "\n(2) - Display vector"
			<< "\n(3) - Edit trainer"
			<< "\n(4) - Write to file vector"
			<<"\n(5) - Delete from vector"
			<<"\n(6) - Sort vector"
			<< "\n(0) - Exit"
			<< "\n\nYour choice>> ";
	}

	void ClearVector()
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
};

bool operator <(Sportsman<double>& first, Sportsman<double>& second)
{
	return first.GetFullName() < second.GetFullName();
}

bool operator <(Trainer& first, Trainer& second)
{
	return first.GetNameOfTrainer() < second.GetNameOfTrainer();
}

void Menu()
{
	cout << "\t|Menu|"<<endl;
	cout << "==========================";
	cout << "\n| (1) - Work with list   |"
		 << "\n| (2) - Work with vector |"
		 << "\n| (0) - Exit             |"<<endl;
		cout << "=========================="
		<< "\n\nYour choice>> ";
}

int main()
{
	Competiton competition;
	Gym gym;
	InsertOperations operations;

	bool isWorking = true;
	bool isWorkingWithList = true;
	bool isWorkingWithVector = true;

	while (isWorking)
	{
		Menu();
		int userChoice = operations.GetValue();

		switch (userChoice)
		{
		case 1:
			while (isWorkingWithList)
			{
				competition.ListMenu();
				userChoice = operations.GetValue();

				switch (userChoice)
				{
				case 1:
					competition.AppendToList();
					break;
				case 2:
					if (competition.IsEmpty() == false) competition.DisplayList();
					else cout << "\nList is empty!\n";
					break;
				case 3:
					if (competition.IsEmpty() == false) competition.EditList();
					else cout << "\nList is empty!\n";
					break;
				case 4:
					if (competition.IsEmpty() == false) competition.WriteInFileList();
					else cout << "\nList is empty!\n";
					break;
				case 5:
					if (competition.IsEmpty() == false) competition.DeleteFromList();
					else cout << "\nList is empty!\n";
					break;
				case 6:
					if (competition.IsEmpty() == false) competition.SortList();
					else cout << "\nList is empty!\n";
					break;
				case 0:
					isWorkingWithList = false;
					break;
				default:
					cout << "\nThere is no case with such input!\n";
					break;
				}
				system("pause");
				system("cls");
			}
			break;
		case 2:
			while (isWorkingWithVector)
			{
				gym.VectorMenu();
				userChoice = operations.GetValue();

				switch (userChoice)
				{
				case 1:
					gym.AppendToVector();
					break;
				case 2:
					if (gym.IsEmpty() == false) gym.DisplayElementsOfVector();
					else cout << "\nVector is empty!\n";
					break;
				case 3:
					if (gym.IsEmpty() == false) gym.EditList();
					else cout << "\nVector is empty!\n";
					break;
				case 4:
					if (gym.IsEmpty() == false) gym.WriteVectorToFile();
					else cout << "\nVector is empty!\n";
					break;
				case 5:
					if (gym.IsEmpty() == false) gym.DeleteFromVector();
					else cout << "\nVector is empty!\n";
					break;
				case 6:
					if (gym.IsEmpty() == false) gym.SortVector();
					break;
				case 0:
					isWorkingWithVector = false;
					break;
				default:
					break;
				}
				system("pause");
				system("cls");
			}
			break;
			
		case 0:
			isWorking = false;
			break;
		default:
			cout << "\nThere is no case with such input!\n";
			break;
		}
		system("pause");
		system("cls");
	}

}

















class Dictionary
{
private:
	map <Sportsman<double>,Team> dictionaryOfSportsman;
	map <Sportsman<double>, Team>::iterator mapPtr;
	InsertOperations operations;
public:
	friend ostream& operator <<(ostream & out,const Dictionary &operand);

	void InsertToMap()
	{
		Sportsman<double> sportsman;
		Team team;
		string nameOfSportsman;
		string teamName;
		int ageOfSportsman;
		double weightOfSportsman;
		double heightOfSportsman;

		cout << "Please, enter full name of sportsman: ";
		getline(cin, nameOfSportsman);

		cout << "Enter age: ";
		ageOfSportsman = operations.GetValue();

		cout << "Enter weight: ";
		weightOfSportsman = operations.GetValue();

		cout << "Enter height: ";
		heightOfSportsman = operations.GetValue();
		
		cout << "Enter name of team: ";
		getline(cin, teamName);

		dictionaryOfSportsman.insert(make_pair(*new Sportsman<double>(nameOfSportsman, ageOfSportsman, weightOfSportsman, heightOfSportsman), *new Team(teamName)));
	}
	
	void DisplayMap()
	{
		mapPtr = dictionaryOfSportsman.begin();

		while (mapPtr != dictionaryOfSportsman.end())
		{
		cout << mapPtr->first.GetFullName()<<mapPtr->;
			
			mapPtr++;
		}
	}
};

class Team
{
private:
	string teamName;
public:

	Team(){}

	Team(string name):teamName(name){}

	void SetName(string name) { this->teamName = name; }
	string GetName() const { return this->teamName; }
};