#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<Windows.h>
#include<ctime>
using namespace std;

struct Time
{
	int DAY_TIME;
	int MONTH_TIME;
	int YEAR_TIME;
};

template<class T>
struct Status
{
	T* ptr;
	int counter;
};

enum ErrorComdition
{
	RIGHT_CONDITION = 0,
	FALSE_CONTIDITION = 1
};

enum State { BEGIN,MIDDLE};

template<class T>
class SmartPointer
{
private:
	Status<T>* smartPtr;
public:
	SmartPointer(T* ptr)
	{
		if (!ptr) smartPtr = NULL;
		else
		{
			smartPtr = new Status<T>();
			smartPtr->ptr = ptr;
			smartPtr->counter = 1;
		}

	}

	void DisplayCounterOfObjects()
	{
		cout << smartPtr->counter;
	}

	int GetCounterOfObjects() const { return smartPtr->counter; }

	SmartPointer(const SmartPointer& obj)
	{
		smartPtr = obj.smartPtr;
		if (smartPtr != NULL) smartPtr->counter++;
	}

	~SmartPointer()
	{
		if (smartPtr != NULL)
		{
			smartPtr->counter--;
			if (smartPtr->counter == 0)
			{
				delete smartPtr->ptr;
				delete smartPtr;
			}
		}
	}

	T* operator->() const
	{
		if (smartPtr != NULL) return smartPtr->ptr;
		else return NULL;
	}

	SmartPointer <T>& operator=(const SmartPointer& obj)
	{
		if (smartPtr != NULL)
		{
			smartPtr->counter--;
			if (smartPtr->counter == 0)
			{
				delete smartPtr->ptr;
				delete smartPtr;
			}
		}

		smartPtr = obj.smartPtr;
		if (smartPtr != NULL) smartPtr->counter++;

		return *this;

	}
};

template<class T>
class Sportsman
{
private:
	string fullName;
	string teamName;
	int age;
	T weight;
	T height;

public:
	Sportsman()
	{
		this->age = 0;
		this->fullName = "NULL";
		this->height = 0;
		this->weight = 0;
		this->teamName = "NULL";
	}

	Sportsman(string name, string teamName, int age, T weight, T height)
	{
		this->fullName = name;
		this->teamName = teamName;
		this->age = age;
		this->weight = weight;
		this->height = height;
	}

	Sportsman(const Sportsman& obj):fullName(obj.fullName),age(obj.age),teamName(obj.teamName), weight(obj.weight), height(obj.height){}

	void SetFullName(string title) {this->fullName = title;}
	void SetTeamName(string title) { this->teamName = title; }
	void SetAge(int age) { this->age = age; }
	void SetWeight(T weight) { this->weight = weight; }
	void SetHeight(T height) { this->height = height; }

	string GetFullName() const { return this->fullName; }
	string GetTeamName() const { return this->teamName; }
	int GetAge() const { return this->age; }
	T GetWeight() const { return this->weight; }
	T GetHeight() const { return this->height; }

	void DisplayInformationAboutSportsman()
	{
		cout << "===========================================================" << endl;
		cout << "Full name of the Sporstsmen - " << this->fullName << endl;
		cout << "Team name - " << this->teamName << endl;
		cout << "Current age - " << this->age << endl;
		cout << "Current Weight - " << this->weight << endl;
		cout << "Current Height - " << this->height << endl;
		cout << "===========================================================" << endl;
	}

	void WriteInFile(string fileName)
	{
		ofstream fout(fileName,ios_base::app);

		if (!fout.is_open()) cout << "\nError connected with opening file!\n";
		else
		{
			fout << "===========================================================" << endl;
			fout << "Full name of the Sporstsmen - " << this->fullName << endl;
			fout << "\nTeam name - " << this->teamName << endl;
			fout << "\nCurrent age - " << this->age << endl;
			fout << "\nCurrent Weight - " << this->weight << endl;
			fout << "\nCurrent Height - " << this->height << endl;
			fout << "===========================================================" << endl;
			fout << endl;
		}
		fout.close();
		
		cout <<"\Information recorded successfully\n";
	}
};

class CompetitionPlace
{
private:
	string location;
public:
	CompetitionPlace()
	{
		this->location = "NULL";
	}
	CompetitionPlace(string location)
	{
		this->location = location;
	}
	void SetLocation(string location) { this->location = location; }
	string GetLocation() const { return this->location; }
};

class Competition
{
private:
	Time timeOfCompetition;
	Sportsman<double> sportsmen;
	CompetitionPlace place;
	vector<SmartPointer<Sportsman<double>>> vector;
public:
	Competition()
	{
		this->timeOfCompetition.DAY_TIME = 0;
		this->timeOfCompetition.MONTH_TIME = 0;
		this->timeOfCompetition.YEAR_TIME = 0;
	}

	void ShowMenu()
	{
		cout << "\tMenu to manage the competition"
			<< "\n(1) - Add sportsman to List"
			<< "\n(2) - Display List of sportmen"
			<< "\n(3) - Edit characteristics of sportsmen"
			<< "\n(4) - Start competition"
			<< "\n(0) - Exit"
			<< "\n\nYour choice>> ";
	}

	template<class T>
	T GetValue()
	{
		T userValue;
		while (!(cin >> userValue) && cin.get() != '\n')
		{
			cout << "Error connected with input, try again: ";
			cin.clear();
			cin.ignore();
			while (cin.get() != '\n');
		}

		return userValue;
	}

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

	string GetAnswer(ErrorComdition& errorState)
	{
		string userInput;
		bool isFinded = true;

		while (isFinded)
		{
			getline(cin, userInput);

			if (userInput == "Y" || userInput == "y")
			{
				isFinded = false;
				errorState = RIGHT_CONDITION;
			}
			else if (userInput == "N" || userInput == "n")
			{
				isFinded = false;
				errorState = FALSE_CONTIDITION;
			}
			else
			{
				cout << "Not correct answer, try again: ";
				cin.clear();
			}
		}

		return userInput;
	}

	void SetTime(int day, int month, int year)
	{
		this->timeOfCompetition.DAY_TIME = day;
		this->timeOfCompetition.MONTH_TIME = month;
		this->timeOfCompetition.YEAR_TIME = year;
	}

	void SetLocation(string location)
	{
		place.SetLocation(location);
	}

	void ShowTimeOfCompetition()
	{
		cout << "Current date of Competition:";
		cout << "\nDay: " << this->timeOfCompetition.DAY_TIME << "\tMonth: " << this->timeOfCompetition.MONTH_TIME << "   Year: " << this->timeOfCompetition.YEAR_TIME << endl;
	}

	void FindTheWinner()
	{
		srand(time_t(NULL));
		int position = rand() % vector.size();

		for (int i = 0; i < vector.size(); i++)
		{
			SmartPointer<Sportsman<double>>temp = vector[i];
			vector[i] = vector[position];
			vector[position] = temp;
		}

		int numberOfPlace = 1;
		cout << "\n\tFinal List of Winners\n"<<endl;
		
		for (int i = 0; i < vector.size(); i++)
		{
			cout << "№ " << numberOfPlace << " " << vector[i]->GetFullName() << endl;
			numberOfPlace++;
		}

		string fileName;
		cout << "Please, enter the filename to record the information: ";
		getline(cin, fileName);
		fileName += ".txt";

		for (int i = 0; i < vector.size(); i++)
		{
			vector[i]->WriteInFile(fileName);
		}

	}

	void InsertNewSportsman()
	{
		string name, teamName;
		int age;
		double weight, height;
		SmartPointer<Sportsman<double>> sportsman(new Sportsman<double>());

		cout << "\tRedactor of characteristics"
			<< "\nEnter whole information about Sportsman:\n";
		CleareBuffer();

		cout << "\nFull Name: ";
		getline(cin, name);

		cout << "Team name: ";
		getline(cin, teamName);

		cout << "Age: ";
		age = GetValue<int>();

		cout << "Weight: ";
		weight = GetValue<double>();

		cout << "Height: ";
		height = GetValue<double>();

		sportsman->SetFullName(name);
		sportsman->SetAge(age);
		sportsman->SetHeight(height);
		sportsman->SetTeamName(teamName);
		sportsman->SetWeight(weight);

		vector.push_back(sportsman);
		cout << "\nWhole information has been recorded!\n";
	}

	void DisplayListOfSportsmen()
	{
		int numberOfSportsmen = 1;
		for (int i = 0; i < vector.size(); i++)
		{
			cout << "№ in the List:" << numberOfSportsmen<<endl;
			vector[i]->DisplayInformationAboutSportsman();
			numberOfSportsmen++;
		}

		cout << "Total amount of people - " << vector.size()<<endl;
	}

	void ClearMemoryFromVector()
	{
		vector.clear();
	}

	void EditCharacterictics()
	{
		cout << "Enter number of Person, you would like to change: ";
		int number = GetValue<int>();
		number--;
		if (number <= vector.size() && number>= 0)
		{
			string name, teamName;
			int age;
			double weight, height;

			for (int i = 0; i < vector.size(); i++)
			{
				if (number == i)
				{
					CleareBuffer();

					cout << "\nFull Name: ";
					getline(cin, name);

					cout << "Team name: ";
					getline(cin, teamName);

					cout << "Age:";
					age = GetValue<int>();

					cout << "Weight: ";
					weight = GetValue<double>();

					cout << "Height: ";
					height = GetValue<double>();

					vector[number]->SetFullName(name);
					vector[number]->SetAge(age);
					vector[number]->SetHeight(height);
					vector[number]->SetTeamName(teamName);
					vector[number]->SetWeight(weight);

					cout << "\nWhole information has been recorded!\n";
				}
			}
		}
		else cout << "\nThere is no such number!\n";
	}

	void EditLocation()
	{
		string location;
		cout << "Enter new Location of competition: ";
		getline(cin, location);
		place.SetLocation(location);
	}
	
	bool IsEmpty()
	{
		if (vector.size() == 0)	return true;
		else return false;
	}

	int GetDay() const { return timeOfCompetition.DAY_TIME; }
	int GetMonth() const { return timeOfCompetition.MONTH_TIME; }
	int GetYear() const { return timeOfCompetition.YEAR_TIME; }
	int GetAvarageOfPeople() const { return this->vector.size(); }
	string GetLocation() const { return place.GetLocation(); }
};

template <class T2>
class Transaction
{
private:
	T2* currentState;
	T2* prevState; 
public:
	Transaction() :prevState(NULL), currentState(new T2) {}
	
	Transaction(const Transaction& obj) : currentState(new T2(*(obj.currentState))), prevState(NULL) {}
	
	~Transaction()
	{
		delete currentState;
		delete prevState;
	}
	
	Transaction& operator=(const Transaction& obj)
	{
		if (this != &obj) // проверка на случай obj=obj
		{
			delete currentState; // удаление текущего значения объекта
			currentState = new T2(*(obj.currentState));
		}
		return *this;
	}
	
	void ShowState(State stage)
	{
		cout << "\n\tState of editing object\n";
		if (!stage) cout << "Before transaction" << endl;
		else cout << "After transaction  " << endl;
		if (prevState) cout << "prevState = " << prevState->GetLocation() << endl;
		else cout << "prevState = NULL " << endl;
		cout << "currentState = " << currentState->GetLocation() << endl;
	}

	int BeginTransactions(string location)
	{
		delete prevState; 
		prevState = currentState; 
		currentState = new T2(*prevState);
		if (!currentState) return 0;
		currentState->SetLocation(location);
		return 1;
	}
	
	void Commit()
	{
		delete prevState; // удаление предыдущего значения
		prevState = NULL; // предыдущего состояния нет
	}
	
	void DeleteTransactions()
	{
		if (prevState)
		{
			delete currentState; // удаление текущего значения
			currentState = prevState; // предыдущее становится текущим
			prevState = NULL; // предыдущего состояния нет
		}
	}
	
	T2* operator->() {return currentState;}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	bool isWorking = true;
	Competition competition;
	string userAnswer;
	ErrorComdition errorState;
	Transaction<Competition>timeOfCompetition;
	int day = 0,month = 0,year = 0;
	string street = "";
	int amountOfSportmen;
	while (isWorking)
	{
		competition.ShowMenu();
		int menuChoice = competition.GetValue<int>();

		switch (menuChoice)
		{
		case 1:
			competition.InsertNewSportsman();
			break;
		case 2:
			if (competition.IsEmpty() == false) competition.DisplayListOfSportsmen();
			else cout << "\nList of sportsmen is empty!\n";
			break;
		case 3:
			if (competition.IsEmpty() == false) competition.EditCharacterictics();
			else cout << "\nList of sportsmen is empty!\n";
			break;
		case 4:
			if (competition.IsEmpty() == false)
			{
				cout << "First Inicialization" << endl
				<< "\nEnter Day: ";
				day = competition.GetValue<int>();
				cout << "\nEnter Month: ";
				month = competition.GetValue<int>();
				cout << "\nEnter Year: ";
				year = competition.GetValue<int>();
				competition.CleareBuffer();

				cout << "\nEnter street: ";
				getline(cin, street);

				timeOfCompetition->SetTime(day, month, year);
				timeOfCompetition->SetLocation(street);
				cout << "\nFirst Inicialization passed succesful\n";
				system("cls");
				system("pause");
				cout << "\tStarted informiaton about Competition"
					<< "\n\nLocation - " << street << endl;
				timeOfCompetition->ShowTimeOfCompetition();
				amountOfSportmen = competition.GetAvarageOfPeople();
				cout << "Amount of sportmen - " << amountOfSportmen;
				
				cout << "\n\nWould you like to start a competition with such parametres: ";
				cout << "\n(Y/N): ";
				userAnswer = competition.GetAnswer(errorState);

				if (errorState == ErrorComdition::RIGHT_CONDITION)
				{
					timeOfCompetition.BeginTransactions(street);
					timeOfCompetition.ShowState(State::BEGIN);
					competition.FindTheWinner();
					timeOfCompetition.Commit();

				}
				else if (errorState == ErrorComdition::FALSE_CONTIDITION)
				{
					cout << "Enter street: ";
					getline(cin, street);

					timeOfCompetition.BeginTransactions(street);
					timeOfCompetition.ShowState(State::BEGIN);

					cout<< "\n\nLocation - " << street << endl;
					timeOfCompetition->ShowTimeOfCompetition();
					amountOfSportmen = competition.GetAvarageOfPeople();
					cout << "Amount of sportmen - " << amountOfSportmen;

					competition.FindTheWinner();
					timeOfCompetition.Commit();
				}
			}
			else cout << "\nList of sportsmen is empty!\n";
			break;
		case 0:
			isWorking = false;
			break;
		}
		system("pause");
		system("cls");
	}	
}