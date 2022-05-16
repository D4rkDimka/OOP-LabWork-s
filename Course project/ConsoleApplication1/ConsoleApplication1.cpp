#include<vector>
#include <iostream>
#include<string>
#include<algorithm>
#include<memory>
#include<fstream>
#include<Windows.h>
#include<iomanip>

using namespace std;

namespace inputOperations
{ 
    int getValueInt()
    {
        int userValue;

        while (!(cin >> userValue) && cin.get() != '\n')
        {
            cout << "Некорректный ввод данных, попробуйте еще раз: ";
            cin.clear();
            while (cin.get() != '\n');
        }

        return userValue;
    }

    void cleareBuffer()
    {
        if (char(cin.peek()) == '\n')
            cin.ignore();
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
        }
    }

    bool getCorrectAnswer()
    {
        string userInput;
        bool isFinded = true;
        bool isGiven = false;
        while (isFinded)
        {
            cin >> userInput;

            try
            {
                if (userInput == "Да" || userInput == "да" || userInput == "Д" || userInput == "д")
                {
                    isFinded = false;
                    isGiven = true;

                }
                else if (userInput == "Н" || userInput == "н" || userInput == "Нет" || userInput == "нет")
                {
                    isFinded = false;
                    isGiven = false;
                }
                else
                {
                    throw runtime_error("Не корректный ввод данных!");
                    cin.clear();
                }
            }
            catch (runtime_error exception)
            {
                cout << "Ошибка: " << exception.what() << "\nПопробуйте еще раз:";
            }
        }

        return isGiven;
    }

    string getValueStr()
    {
        string userInput;
        cin>>userInput;
        return userInput;
    }
}

class User
{
private:
    string login;
    string password;
public:
    User(){}
    User(string login, string password):login(login),password(password){}

    void setPassword(string password) { this->password = password; }
    void setLogin(string login) { this->login = login; }

    string getPassword() const { return this->password; }
    string getLogin() const { return this->login; }

};

class Autorization
{
private:
    vector<User> users;
public:
    void registerNewUser()
    {
        vector<User> tempUsers;
        bool isExist = false;
        string login;
        string password;
        string fileName = "LoginsAndPassword.txt";
    
        insertLoginAndPassword(login, password);      
        
        tempUsers.push_back(*new User(login, password));
        User buffer = tempUsers[0];
            
        //encryptLoginAndPassword(login,password);

        ofstream fout;
        fout.open(fileName, ios_base::app);

        try
        {
            if (fout.is_open() == false || fout.bad() == true) throw runtime_error
            ("Файл не может быть открыт или появились критическеи ошибки открытии!");
        }
        catch (runtime_error exception)
        {
            cout << "Ошибка: " << exception.what() << endl;
        }
            
        fout << login << endl;
        fout << password << endl<<endl;

        fout.close();
        cout << "\nВся информация была успешно записана!\n";
        tempUsers.clear();
    }

    void insertLoginAndPassword(string &login, string &password)
    {
        cout << "Введите логин: ";
        login = inputOperations::getValueStr();
        cout << "Введите пароль: ";
        password = inputOperations::getValueStr();
    }

    void downloaduserAccountsFromFIle()
    {
        string fileName = "LoginsAndPassword.txt";
        ifstream fin;
        User user;

        fin.open(fileName, ios_base::in);

        try
        {
            if (fin.is_open() == false || fin.bad() == true) throw runtime_error("Файл не может быть открыт или не существует!");
        }
        catch (runtime_error exception)
        {
            cout << "Ошибка: " << exception.what() << endl;
            return;
        }
        string buffer;
        string login;
        string password;

        while (!fin.eof())
        {
            getline(fin, login);
            getline(fin, password);
            getline(fin, buffer);
            users.push_back(*new User(login, password));
        }

        fin.close();

        displayExistingAccounts();
        cout << "\nВся информация из файла была успешно считана!\n";
    }

    void displayExistingAccounts()
    {
        for (int i = 0; i < users.size(); i++)
        {
            cout << users[i].getLogin() <<" " << users[i].getPassword() << endl<<endl;
        }
    }

    void encryptLoginAndPassword(string& login, string& password)
    {
        for (int i = 0; i < login.size(); i++)
        {
            if (login[i] == 'Z') login[i] = 'A';
            else login[i]++;
        }

        for (int i = 0; i < password.size(); i++)
        {
            if (password[i] == 'Z') password[i] = 'A';
            else password[i]++;
        }

    }

    void decryptLoginAndPassword(string& login, string& password)
    {

        for (int i = 0; i < login.size(); i++)
        {
            if (login[i] == 'A') login[i] = 'Z';
            else login[i]--;
        }

        for (int i = 0; i < password.size(); i++)
        {
            if (password[i] == 'A') password[i] = 'Z';
            else password[i]--;
        }
    }

    void autorizationMenu()
    {
        cout << "(1) - Добавить новый аккаунт"
            << "\n(2) - Войти в существующий аккаунт"
            << "\n\nВаш выбор>>";
    }

    bool isCorrectData(string login,string password)
    {
        for (int i = 0; i < users.size(); i++)
        {
            if (users[i].getLogin() == login && users[i].getPassword() == password) return true;
            else return false;
        }
    }
    
    bool checkLogin(string login,string findWord)
    {
        int i, j;
        bool isConsistOf = false;
        int size = login.length() - findWord.length()+1;

        for (i = 0; i < size; i++) {
            j = 0;
            while ((j < findWord.length()) && (findWord[j] == login[i + j])) {
                j = j + 1;
            }
            if (j == findWord.length())
            {
                isConsistOf = true;
            }
        }
        return isConsistOf;
    }
};

class Package
{
private:
    string numberOfPackage;
    int amountOfDaysForStorage;
    int dayOfAdmission;
    int monthOfAdmission;
    int yearOfAdmission;
    bool isGiven;
    static int amountOfCreatedObjects;
public:
    Package() {}
    Package(string numberOfPackage, int amountOfDaysForStorage, int dayOfAdmission, int monthOfAdmission, int yearOfAdmission, bool isGiven) :
        numberOfPackage(numberOfPackage), amountOfDaysForStorage(amountOfDaysForStorage), dayOfAdmission(dayOfAdmission), monthOfAdmission
        (monthOfAdmission), yearOfAdmission(yearOfAdmission), isGiven(isGiven) {
        amountOfCreatedObjects++;
    }

    void diplayPackageInformation()
    {
        cout.setf(ios::boolalpha);
        cout << "Номер посылки: " << this->numberOfPackage
            << "\nКоличество дней для хранения: " << this->amountOfDaysForStorage
            << "\nДата поступления: " << dayOfAdmission << "/" << monthOfAdmission << "/" << yearOfAdmission
            << "\nПосылка отдана: " << isGiven << endl;
        cout.unsetf(ios::boolalpha);
    }

    friend ostream& operator<<(ostream& out, Package& package);

    void setGiven(bool isGiven) { this->isGiven = isGiven; }

    void setNumberOfPackage(string number) { this->numberOfPackage = number; }

    void setDayOfAdmission(int day)
    {
        if (day < 0 && day> 31) throw "\nНекорректный ввод данных для дня поступления посылки!\n";
    }

    void setMonthOfAdmission(int month)
    {
        if (month < 0 && month> 31) throw "\nНекорректный ввод данных для месяца поступления посылки!\n";
    }

    void setYearOfAdmission(int year)
    {
        if (year < 0 && year> 31) throw "\nНекорректный ввод данных для года поступления посылки!\n";
    }

    void setAmountOfDaysForStorage(int days)
    {
        if (days < 0 && days > 31) throw "\nНекорректный ввод данных для количества дней хранения!\n";
    }

    bool getCondition() const { return this->isGiven; }

    string getNumberOfPackage() const { return this->numberOfPackage; }

    int getAmountOfDaysForStorage() const { return this->amountOfDaysForStorage; }

    int getDayOfAdmission() const { return this->dayOfAdmission; }

    int getMonthOfAdmission() const { return this->dayOfAdmission; }

    int getYearOfAdmission() const { return this->dayOfAdmission; }

    bool isStored()
    {
        if (dayOfAdmission < getDayOfAdmission() + getAmountOfDaysForStorage()) return true;
        else return false;
    }

    static int getAmountOfObjects()
    {
        return amountOfCreatedObjects;
    }
};

ostream& operator<<(ostream& out, Package& package)
{
    cout.setf(ios::boolalpha);
    cout << "Номер посылки: " << package.numberOfPackage
        << "\nКоличество дней для хранения: " << package.amountOfDaysForStorage
        << "\nДата поступления: " << package.dayOfAdmission << "/" << package.monthOfAdmission << "/" << package.yearOfAdmission
        << "\nПосылка отдана: " << package.isGiven << endl;
    cout.unsetf(ios::boolalpha);
    return out;
}

bool operator <(const shared_ptr<Package>& firstPackage, const shared_ptr<Package>& secondPackage)
{
    if (firstPackage.get()->getAmountOfDaysForStorage() < secondPackage.get()->getAmountOfDaysForStorage()) return true;
    else return false;
}

int Package::amountOfCreatedObjects = 0;

template<class T>
class FileOperations
{
private:
    string fileName;
    shared_ptr <T> buffer;
public:
    FileOperations() {}
    FileOperations(string fileName) :fileName(fileName) {}

    string enterFileName()
    {
        cin.ignore(100, '\n');

        cout << "Пожалуйста,введите имя файла: ";
        getline(cin, fileName);
        fileName += ".txt";
        return fileName;
    }

    string getFileName() const { return fileName; }

    void writeInFile(vector<shared_ptr<T>> vector)
    {
        ofstream fout;
        int userChoice;
        bool isWorking = true;

        fileName = enterFileName();

        cout << "\nВыберете метод записи в файл: \n"
            << "\n1) - Перезапись файла"
            << "\n2) - Добавление информации в файл"
            << "\n\nВаш выбор>> ";

        userChoice = inputOperations::getValueInt();

        switch (userChoice)
        {
        case 1:
            fout.open(fileName, ios_base::trunc | ios::binary);

            try
            {
                if (fout.is_open() == false || fout.bad() == true) throw runtime_error
                ("Файл не может быть открыт или появились критическеи ошибки открытии!");
            }
            catch (runtime_error exception)
            {
                cout << "Ошибка: " << exception.what() << endl;
                break;
            }

            for (int i = 0; i < vector.size(); i++)
            {
                buffer = vector[i];
                fout.write(reinterpret_cast<char*>(&buffer), sizeof T);
            }

            fout.close();
            cout << "\nВся информации была успешно записана!\n";
            break;
        case 2:
            fout.open(fileName, ios_base::app || ios::binary);

            try
            {
                if (fout.is_open() == false || fout.bad() == true) throw runtime_error
                ("Файл не может быть открыт или появились критическеи ошибки открытии!");
            }
            catch (runtime_error exception)
            {
                cout << "Ошибка: " << exception.what() << endl;
                break;
            }

            for (int i = 0; i < vector.size(); i++)
            {
                buffer = vector[i];
                fout.write(reinterpret_cast<char*>(&buffer), sizeof T);
            }

            fout.close();
            cout << "\nВся информация была успешно записана!\n";
            break;
        default:
            cout << "\nНет кейсов с такими вводом!\n";
            break;
        }
    }

    void readFromFile(vector<shared_ptr<T>> vector)
    {
        ifstream fin;
        bool isWorking = true;

        fileName = enterFileName();

        fin.open(fileName, ios_base::in | ios::binary);

        try
        {
            if (fin.is_open() == false || fin.bad() == true) throw runtime_error("Файл не может быть открыт или не существует!");
        }
        catch (runtime_error exception)
        {
            cout << "Ошибка: " << exception.what() << endl;
            return;
        }

        auto ptr = vector.begin();
        fin.seekg(0, ios::end);
        int size = fin.tellg() / sizeof(T);
        fin.seekg(0);

        for (int i = 0; i < vector.size(); i++)
        {
            fin.read(reinterpret_cast<char*>(&buffer), sizeof(T));
            cout << buffer << endl;
        }

        fin.close();
        cout << "\nВся информация из файла была успешно считана!\n";

    }

    int getFileSize()
    {
        ifstream fin;
        fin(fileName, ios::in);
        int fileSize = 0;
        fin.seekg(0, ios::end);
        fileSize = fin.tellg();
        fin.close();

        return fileSize;
    }
};

class PackageDatabase
{
private:
    vector<shared_ptr<Package>> packages;
    FileOperations<Package> file;
public:
    PackageDatabase() {}

    void displayPackageMenu()
    {
        cout << "(1) - Добавить посылку в базу"
            << "\n(2) - Вывести список посылок"
            << "\n(3) - Изменить характеристики посылку"
            << "\n(4) - Удалить посылку из списка"
            << "\n(5) - Найти посылку"
            << "\n(6) - Отсортировать список с посылками"
            << "\n(7) - Записать в файл"
            << "\n(8) - Чтение из файла"
            << "\n(0) - Выход"
            << "\n\nВаш выбор>> ";
    }

    void addNewPackage()
    {
        string packageName;
        int amountOfDaysForStorage;
        int dayOfAdmission;
        int monthOfAdmission;
        int yearOfAdmission;
        bool isGiven;

        cout << "\tДобавление новой посылки в базу" << endl;
        cout << "\nВведите номер посылки: ";
        packageName = inputOperations::getValueStr();
        inputOperations::cleareBuffer();
        cout << "\nВведите количество дней для хранения данной посылки: ";
        amountOfDaysForStorage = inputOperations::getValueInt();
        try
        {
            if (amountOfDaysForStorage < 0 || amountOfDaysForStorage >31) throw "Ошибка ввода границ для переменной(0 - 31)";
        }
        catch (const char* exception)
        {
            cout << "Ошибка: " << exception << endl;
            while (amountOfDaysForStorage < 0 || amountOfDaysForStorage >31)
            {
                cout << ">>";
                amountOfDaysForStorage = inputOperations::getValueInt();
                cout << "Ошибка: " << exception << endl;
            }
        }
        cout << "\n============================================" << endl;
        cout << "Введите дату получения посылки" << endl;
        cout << "============================================" << endl;
        cout << "\nВведите день: ";
        dayOfAdmission = inputOperations::getValueInt();

        try
        {
            if (dayOfAdmission < 0 || dayOfAdmission > 31) throw "Ошибка ввода границ для переменной(0 - 31)";
        }
        catch (const char* exception)
        {
            cout << "Ошибка: " << exception << endl;
            while (dayOfAdmission < 0 || dayOfAdmission > 31)
            {
                cout << ">>";
                dayOfAdmission = inputOperations::getValueInt();
                cout << "Ошибка: " << exception << endl;
            }
        }

        cout << "\nВведите месяц: ";
        monthOfAdmission = inputOperations::getValueInt();

        try
        {
            if (monthOfAdmission < 0 || monthOfAdmission>12) throw "Ошибка ввода границ для переменной(0 - 12)";
        }
        catch (const char* exception)
        {
            cout << "Ошибка: " << exception << endl;
            while (monthOfAdmission < 0 || monthOfAdmission > 12)
            {
                cout << ">>";
                monthOfAdmission = inputOperations::getValueInt();
                cout << "Ошибка: " << exception << endl;
            }
        }

        cout << "\nВведите год: ";
        yearOfAdmission = inputOperations::getValueInt();

        try
        {
            if (yearOfAdmission < 2000 || yearOfAdmission >2022) throw "Ошибка ввода границ для переменной(2000 - 2022)";
        }
        catch (const char* exception)
        {
            cout << "Ошибка: " << exception << endl;
            while (yearOfAdmission < 2000 || yearOfAdmission > 2022)
            {
                cout << ">>";
                yearOfAdmission = inputOperations::getValueInt();
                cout << "Ошибка: " << exception << endl;
            }
        }

        cout << "\nПосылка отдана(Да/Нет): ";
        isGiven = inputOperations::getCorrectAnswer();

        packages.push_back(shared_ptr<Package>(
            new Package(packageName, amountOfDaysForStorage, dayOfAdmission, monthOfAdmission, yearOfAdmission, isGiven)));
        cout << "\nНовая посылка успешно добавлена в базу!\n";
    }

    void displayPackages()
    {
        cout << "\tИнформация о посылках\n" << endl;

        for (int i = 0; i < packages.size(); i++)
        {
            packages[i]->diplayPackageInformation();
            cout << endl;
        }
    }

    void editPackagesInformation()
    {
        string packageName;
        int amountOfDaysForStorage;
        int dayOfAdmission;
        int monthOfAdmission;
        int yearOfAdmission;
        bool isFound = false;
        bool isGiven;

        cout << "Выберете посылку, данные которой вы хотите изменить: " << endl;
        displayPackages();
        cout << "\nВведите номер посылки: ";
        packageName = inputOperations::getValueStr();

        int numberOfPackage = findCertainPackege(packageName, isFound);

        if (isFound == true)
        {
            cout << "\nВведите номер посылки: ";
            packageName = inputOperations::getValueStr();
            inputOperations::cleareBuffer();
            cout << "\nВведите количество дней для хранения данной посылки: ";
            amountOfDaysForStorage = inputOperations::getValueInt();
            try
            {
                if (amountOfDaysForStorage < 0 || amountOfDaysForStorage >31) throw "Ошибка ввода границ для переменной(0 - 31)";
            }
            catch (const char* exception)
            {
                cout << "Ошибка: " << exception << endl;
                while (amountOfDaysForStorage < 0 || amountOfDaysForStorage >31)
                {
                    cout << ">>";
                    amountOfDaysForStorage = inputOperations::getValueInt();
                    cout << "Ошибка: " << exception << endl;
                }
            }
            cout << "\n============================================" << endl;
            cout << "Введите дату получения посылки" << endl;
            cout << "============================================" << endl;
            cout << "\nВведите день: ";
            dayOfAdmission = inputOperations::getValueInt();

            try
            {
                if (dayOfAdmission < 0 || dayOfAdmission > 31) throw "Ошибка ввода границ для переменной(0 - 31)";
            }
            catch (const char* exception)
            {
                cout << "Ошибка: " << exception << endl;
                while (dayOfAdmission < 0 || dayOfAdmission > 31)
                {
                    cout << ">>";
                    dayOfAdmission = inputOperations::getValueInt();
                    cout << "Ошибка: " << exception << endl;
                }
            }

            cout << "\nВведите месяц: ";
            monthOfAdmission = inputOperations::getValueInt();

            try
            {
                if (monthOfAdmission < 0 || monthOfAdmission>12) throw "Ошибка ввода границ для переменной(0 - 12)";
            }
            catch (const char* exception)
            {
                cout << "Ошибка: " << exception << endl;
                while (monthOfAdmission < 0 || monthOfAdmission > 12)
                {
                    cout << ">>";
                    monthOfAdmission = inputOperations::getValueInt();
                    cout << "Ошибка: " << exception << endl;
                }
            }

            cout << "\nВведите год: ";
            yearOfAdmission = inputOperations::getValueInt();

            try
            {
                if (yearOfAdmission < 2000 || yearOfAdmission >2022) throw "Ошибка ввода границ для переменной(2000 - 2022)";
            }
            catch (const char* exception)
            {
                cout << "Ошибка: " << exception << endl;
                while (yearOfAdmission < 2000 || yearOfAdmission > 2022)
                {
                    cout << ">>";
                    yearOfAdmission = inputOperations::getValueInt();
                    cout << "Ошибка: " << exception << endl;
                }
            }

            cout << "\nПосылка отдана(Да/Нет): ";
            isGiven = inputOperations::getCorrectAnswer();

            try
            {
                packages[numberOfPackage]->setNumberOfPackage(packageName);
                packages[numberOfPackage]->setAmountOfDaysForStorage(amountOfDaysForStorage);
                packages[numberOfPackage]->setDayOfAdmission(dayOfAdmission);
                packages[numberOfPackage]->setMonthOfAdmission(monthOfAdmission);
                packages[numberOfPackage]->setYearOfAdmission(yearOfAdmission);

            }
            catch (const char* exception)
            {
                cout << "Ошибка: " << exception << endl;
            }
        }
    }

    int findCertainPackege(string packageName, bool& isFound)
    {
        int numberOfPackage = 0;
        string nameOfPackage;

        for (int i = 0; i < packages.size(); i++)
        {
            if (packages[i]->getNumberOfPackage() == packageName)
            {
                isFound = true;
                numberOfPackage = i;
                nameOfPackage = packages[i]->getNumberOfPackage();
            }
        }

        if (isFound == true) {
            cout << "Посылка с номером(" << nameOfPackage << ") найдена!" << endl << endl;
            packages[numberOfPackage]->diplayPackageInformation();
        }
        else cout << "Посылки с таким номером нет!" << endl;

        return numberOfPackage;
    }

    void displayOnlyNumbersOfPackages()
    {
        cout << "\n\tИнформация о посылках\n" << endl;

        for (int i = 0; i < packages.size(); i++)
        {
            cout << packages[i]->getNumberOfPackage() << endl;
        }
    }

    void deletePackageFromDatabase()
    {
        bool isDeleted = false;
        cout << "Выберете посылку, которую вы хотите удалить: " << endl << endl;
        displayPackages();
        cout << "\nВведите номер посылки: ";
        string packageName = inputOperations::getValueStr();

        for (int i = 0; i < packages.size(); i++)
        {
            if (packages[i]->getNumberOfPackage() == packageName)
            {
                packages.erase(packages.begin() + i);
                isDeleted = true;
            }
        }

        if (isDeleted == false)
        {
            cout << "\nПосылка не была удалена по какой-то причине! Попробуйте еще раз!\n";
        }
        else cout << "Посылка с номером(" << packageName << ") была успешно удалена из базы!\n";
    }

    void clearDatabase()
    {
        packages.clear();

        try
        {
            if (packages.size() != 0) throw "Память не очищина(Упаковки)\n";
        }
        catch (const char* exception)
        {
            cout << "Ошибка: " << exception << endl;
            throw;
        }
    }

    void writePackagesInFile()
    {
        file.writeInFile(packages);
    }

    void readPackagesFromFile()
    {
        file.readFromFile(packages);
    }

    void sortPackages()
    {
        sort(packages.begin(), packages.end());
    }

    bool isEmpty()
    {
        if (packages.size() == 0)return true;
        else return false;
    }
};

class Person
{
public:
    virtual void setFullName(string fullName) = 0;
    virtual string getFullName() = 0;
    virtual void displayInformation() = 0;
};

class MailRecepient :public Person
{
private:
    string fullName;
    Package package;
    vector<MailRecepient> clients;
public:
    MailRecepient(){}
    MailRecepient(string fullName,Package package) :fullName(fullName),
        package(package){}

    void setFullName (string fullName) override
    {
        bool isCorrect = true;

        for (int i = 0; i < fullName.size(); i++)
        {
            if (fullName[i] > '0' && fullName[i] < '9') isCorrect = false;
        }

        if (isCorrect == false) throw "\nВ имени присутсвуют цифры!\n";
        else this->fullName = fullName; 
    }

    void displayInformation() override
    {
        cout << "Имя получателя посылки: " << fullName<<endl;
        package.diplayPackageInformation();
    }

    string getFullName() override { return this->fullName; }

    void displayClientsInQueue()
    {
        int numberOfClient = 1;

        for (int i = 0; i < clients.size(); i++)
        {
            cout << numberOfClient << ") " << clients[i].getFullName() << endl << endl;

            numberOfClient++;
        }

        //cout << "\nОбщее число клиентов - " << getAmountOfClients() << endl;
    }

    void changePackageInformation()
    {
        string packageName;
        int amountOfDaysForStorage;
        int dayOfAdmission;
        int monthOfAdmission;
        int yearOfAdmission;
        bool isFound = false;
        bool isGiven;

        cout << "\nВведите номер посылки: ";
        packageName = inputOperations::getValueStr();

        cout << "\nВведите номер посылки: ";
        packageName = inputOperations::getValueStr();
        inputOperations::cleareBuffer();
        cout << "\nВведите количество дней для хранения данной посылки: ";
        amountOfDaysForStorage = inputOperations::getValueInt();
        try
        {
            if (amountOfDaysForStorage < 0 || amountOfDaysForStorage >31) throw "Ошибка ввода границ для переменной(0 - 31)";
        }
        catch (const char* exception)
        {
            cout << "Ошибка: " << exception << endl;
            while (amountOfDaysForStorage < 0 || amountOfDaysForStorage >31)
            {
                cout << ">>";
                amountOfDaysForStorage = inputOperations::getValueInt();
                cout << "Ошибка: " << exception << endl;
            }
        }
        cout << "\n============================================" << endl;
        cout << "Введите дату получения посылки" << endl;
        cout << "============================================" << endl;
        cout << "\nВведите день: ";
        dayOfAdmission = inputOperations::getValueInt();

        try
        {
            if (dayOfAdmission < 0 || dayOfAdmission > 31) throw "Ошибка ввода границ для переменной(0 - 31)";
        }
        catch (const char* exception)
        {
            cout << "Ошибка: " << exception << endl;
            while (dayOfAdmission < 0 || dayOfAdmission > 31)
            {
                cout << ">>";
                dayOfAdmission = inputOperations::getValueInt();
                cout << "Ошибка: " << exception << endl;
            }
        }

        cout << "\nВведите месяц: ";
        monthOfAdmission = inputOperations::getValueInt();

        try
        {
            if (monthOfAdmission < 0 || monthOfAdmission>12) throw "Ошибка ввода границ для переменной(0 - 12)";
        }
        catch (const char* exception)
        {
            cout << "Ошибка: " << exception << endl;
            while (monthOfAdmission < 0 || monthOfAdmission > 12)
            {
                cout << ">>";
                monthOfAdmission = inputOperations::getValueInt();
                cout << "Ошибка: " << exception << endl;
            }
        }

        cout << "\nВведите год: ";
        yearOfAdmission = inputOperations::getValueInt();

        try
        {
            if (yearOfAdmission < 2000 || yearOfAdmission >2022) throw "Ошибка ввода границ для переменной(2000 - 2022)";
        }
        catch (const char* exception)
        {
            cout << "Ошибка: " << exception << endl;
            while (yearOfAdmission < 2000 || yearOfAdmission > 2022)
            {
                cout << ">>";
                yearOfAdmission = inputOperations::getValueInt();
                cout << "Ошибка: " << exception << endl;
            }
        }

        cout << "\nПосылка отдана(Да/Нет): ";
        isGiven = inputOperations::getCorrectAnswer();

        try
        {
            package.setNumberOfPackage(packageName);
            package.setAmountOfDaysForStorage(amountOfDaysForStorage);
            package.setDayOfAdmission(dayOfAdmission);
            package.setMonthOfAdmission(monthOfAdmission);
            package.setYearOfAdmission(yearOfAdmission);

        }
        catch (const char* exception)
        {
            cout << "Ошибка: " << exception << endl;
        }
    }

    void displayRecepientMenu()
    {
        cout << "\tКлиентское меню"
            << "\n(1) - Занять очередь"
            << "\n(2) - Подождать время"
            << "\n(3) - Подойти к кассе"
            << "\n(0) - Уйти"
            << "\n\nВаш выбор>>";
    }

    void createClientsQueue()
    {
        vector<string> firstNames = { "Дмитрий ","Александр ","Иван ","Георгий ","Михаил ","Борис ","Егор " };
        vector<string> lastNames = { "Лужковский","Лекашенич","Громов","Озернов","Клубнин","Зиновенко","Капитонов" };
        vector<string> packages = { "GB1052","AS5212","GD6212","FG9210","BS902","VS1568","MR6900" };
        int randomAmountOfClients = rand() % 7;
        vector<string> fullNames;
        srand(time(NULL));

        for (int i = 0; i < randomAmountOfClients; i++)
        {
            fullNames.push_back(firstNames[rand() % randomAmountOfClients] + lastNames[rand() % randomAmountOfClients]);
        }

        for (int i = 0; i < fullNames.size(); i++)
        {
            clients.push_back(*new MailRecepient(fullNames[i], *new Package(packages[rand() % randomAmountOfClients], rand() % 31 + 1, rand() % 31 + 1, rand() % 12 + 1,
                2020 + rand() % 2, false)));
        }

    }

    void getInQueue()
    {
        srand(time(NULL));
        vector<string> packages = { "GB1052","AS5212","GD6212","FG9210","BS902","VS1568","MR6900" };
        clients.push_back(*new MailRecepient("Вы", *new Package(packages[rand() % 7], rand() % 31 + 1, rand() % 31 + 1, rand() % 12 + 1,
            2020 + rand() % 2, false)));
    }

    void waitTimeInQueue()
    {   
        if (clients.size() != 0) clients.erase(clients.begin());
        else cout << "\nВ очереди больше нет людей!\n";
    }

    int getAmountOfClients() { return clients.size(); }

    bool isEmptyClientsQueue()
    {
        if (clients.size() == 0)return true;
        else return false;
    }
};

bool operator <(const shared_ptr<MailRecepient>& firstClient, const shared_ptr<MailRecepient>& secondClient)
{
    if (firstClient.get()->getFullName() < secondClient.get()->getFullName()) return true;
    else return false;
}

class ClientDatabase
{
private:
    vector<shared_ptr <MailRecepient>> clients;
    FileOperations<MailRecepient> file;

public:
    ClientDatabase()
    {
    }

    void addNewClient()
    {
        string clientName;
        bool isGot = false;
        string packageName;
        int amountOfDaysForStorage;
        int dayOfAdmission;
        int monthOfAdmission;
        int yearOfAdmission;
        bool isGiven;

        cout << "\tДобавление нового клиента в базу" << endl;
        cout << "\nВведите имя клиента: ";
        inputOperations::cleareBuffer();
        getline(cin, clientName);
        cout << "\nЕсть ли у клиента посылки: ";
        isGot = inputOperations::getCorrectAnswer();

        if (isGot == true)
        {
            cout << "\nВведите номер посылки: ";
            packageName = inputOperations::getValueStr();
            inputOperations::cleareBuffer();
            cout << "\nВведите количество дней для хранения данной посылки: ";
            amountOfDaysForStorage = inputOperations::getValueInt();
            try
            {
                if (amountOfDaysForStorage < 0 || amountOfDaysForStorage >31) throw "Ошибка ввода границ для переменной(0 - 31)";
            }
            catch (const char* exception)
            {
                cout << "Ошибка: " << exception << endl;
                while (amountOfDaysForStorage < 0 || amountOfDaysForStorage >31)
                {
                    cout << ">>";
                    amountOfDaysForStorage = inputOperations::getValueInt();
                    cout << "Ошибка: " << exception << endl;
                }
            }
            cout << "\n============================================" << endl;
            cout << "Введите дату получения посылки" << endl;
            cout << "============================================" << endl;
            cout << "\nВведите день: ";
            dayOfAdmission = inputOperations::getValueInt();

            try
            {
                if (dayOfAdmission < 0 || dayOfAdmission > 31) throw "Ошибка ввода границ для переменной(0 - 31)";
            }
            catch (const char* exception)
            {
                cout << "Ошибка: " << exception << endl;
                while (dayOfAdmission < 0 || dayOfAdmission > 31)
                {
                    cout << ">>";
                    dayOfAdmission = inputOperations::getValueInt();
                    cout << "Ошибка: " << exception << endl;
                }
            }

            cout << "\nВведите месяц: ";
            monthOfAdmission = inputOperations::getValueInt();

            try
            {
                if (monthOfAdmission < 0 || monthOfAdmission>12) throw "Ошибка ввода границ для переменной(0 - 12)";
            }
            catch (const char* exception)
            {
                cout << "Ошибка: " << exception << endl;
                while (monthOfAdmission < 0 || monthOfAdmission > 12)
                {
                    cout << ">>";
                    monthOfAdmission = inputOperations::getValueInt();
                    cout << "Ошибка: " << exception << endl;
                }
            }

            cout << "\nВведите год: ";
            yearOfAdmission = inputOperations::getValueInt();

            try
            {
                if (yearOfAdmission < 2000 || yearOfAdmission >2022) throw "Ошибка ввода границ для переменной(2000 - 2022)";
            }
            catch (const char* exception)
            {
                cout << "Ошибка: " << exception << endl;
                while (yearOfAdmission < 2000 || yearOfAdmission > 2022)
                {
                    cout << ">>";
                    yearOfAdmission = inputOperations::getValueInt();
                    cout << "Ошибка: " << exception << endl;
                }
            }

            cout << "\nПосылка отдана(Да/Нет): ";
            isGiven = inputOperations::getCorrectAnswer();
            clients.push_back(shared_ptr<MailRecepient>(new MailRecepient(clientName, *new Package(packageName, amountOfDaysForStorage,
                dayOfAdmission, monthOfAdmission, yearOfAdmission, isGiven))));
        }
        else
        {
            clients.push_back(shared_ptr<MailRecepient>(new MailRecepient(clientName, *new Package("Нет данных", 0,
                0, 0, 0, false))));
        }
    }

    void displayClientMenu()
    {
        cout << "(1) - Добавить нового клиента в базу"
            << "\n(2) - Вывести список клиентов/список клиентов и их посылки"
            << "\n(3) - Изменить характеристики клиента"
            << "\n(4) - Удалить клиента из базы"
            << "\n(5) - Найти клиента"
            << "\n(6) - Отсортировать список клиентов"
            << "\n(7) - Записать в файл"
            << "\n(8) - Чтение из файла"
            << "\n(0) - Выход"
            << "\n\nВаш выбор>> ";
    }

    void displayClients()
    {
        int numberOfClient = 1;

        cout << "\tИнформация о клиентах\n" << endl;

        for (int i = 0; i < clients.size(); i++)
        {
            cout << numberOfClient << ") " << clients[i]->getFullName() << endl << endl;

            numberOfClient++;
        }

        cout << "\nОбщее число клиентов - " << getAmountOfClients() << endl;
    }

    void displayClientsWithPackages()
    {
        int numberOfClient = 1;

        cout << "\tИнформация о клиентах\n" << endl;

        for (int i = 0; i < clients.size(); i++)
        {
            cout << numberOfClient << ") ";
            clients[i]->displayInformation();
            cout<< endl << endl;

            numberOfClient++;
        }

        cout << "\nОбщее число клиентов - " << getAmountOfClients() << endl;
    }

    void displayCertainClient(int numberOfClient)
    {
        clients[numberOfClient]->displayInformation();
    }

    void editClientsInformation()
    {
        bool isFound = false;
        string clientName;
        string clientNewName;
        int numberOfClient;
        displayClients();
        cout << "\nВведите имя клиента, данные которого вы хотите изменить: ";
        inputOperations::cleareBuffer();
        getline(cin,clientName);

        numberOfClient = findCertainClient(clientName, isFound);

        if (isFound == true)
        {
            cout << "(1) - Изменить имя клиента"
                << "\n(2) - Изменить данные его посылки"
                << "\n\nВаш выбор>> ";
            int userChoice = inputOperations::getValueInt();

            switch (userChoice)
            {
            case 1:
                cout << "Введите новое имя клиента: ";
                inputOperations::cleareBuffer();
                getline(cin, clientNewName);
                clients[numberOfClient]->setFullName(clientNewName);
                break;
            case 2:
                clients[numberOfClient]->changePackageInformation();
                break;
            default:
                cout << "\nКейса с таким номер нет!\n";
                break;
            }
        }
    }

    int findCertainClient(string clientName, bool& isFound)
    {
        int numberOfClient = 0;

        for (int i = 0; i < clients.size(); i++)
        {
            if (clients[i]->getFullName() == clientName)
            {
                isFound = true;
                numberOfClient = i;
            }
        }

        if (isFound == true) {
            cout << "Клиент с именем(" << clientName << ") найден!" << endl << endl;
        }
        else cout << "Клиента с таким именем нет!" << endl;

        return numberOfClient;
    }

    void deleteClient()
    {
        bool isDeleted = false;
        cout << "Выберете клиента, которого вы хотите удалить: " << endl << endl;
        displayClients();
        cout << "\nВведите имя клиента: ";
        string clientName;
        inputOperations::cleareBuffer();
        getline(cin, clientName);

        for (int i = 0; i < clients.size(); i++)
        {
            if (clients[i]->getFullName() == clientName)
            {
                clients.erase(clients.begin() + i);
                isDeleted = true;
            }
        }

        if (isDeleted == false)
        {
            cout << "\nКлиент не был удален по какой-то причине! Попробуйте еще раз!\n";
        }
        else cout << "Клиент с именем(" << clientName << ") был успешно удален из базы!\n";
    }

    void clearDatabase()
    {
        clients.clear();

        try
        {
            if (clients.size() != 0) throw "Память не очищина(Клиенты)\n";
        }
        catch (const char* exception)
        {
            cout << "Ошибка: " << exception << endl;
            throw;
        }
    }

    void writeClientsInFile()
    {
        file.writeInFile(clients);
    }

    void readClientsFromFile()
    {
        file.readFromFile(clients);
    }

    void sortClients()
    {
        sort(clients.begin(), clients.end());
    }

    int getAmountOfClients() const { return clients.size(); }

    bool isEmpty()
    {
        if (clients.size() == 0)return true;
        else return false;
    }
};

class MailWorker : public Person
{
private:
    string fullName;
    string position;
    PackageDatabase packageDatabase;
    ClientDatabase clientDatabase;
public:
    MailWorker(){}
    MailWorker(string fullName, string position) :fullName(fullName), position(position) {}

    void setFullName(string fullName) override
    {
        bool isCorrect = true;

        for (int i = 0; i < fullName.size(); i++)
        {
            if (fullName[i] > '0' && fullName[i] < '9') isCorrect = false;
        }

        if (isCorrect == false) throw "\nВ имени присутсвуют цифры!\n";
    }

    void displayInformation() override
    {
        cout << "Имя работника: " << fullName
            << "\nДолжность: " << position << endl;
    }

    void manageClientDatabase()
    {
        bool isWorking = true;
        
        while (isWorking)
        {
            clientDatabase.displayClientMenu();
            int userChoice = inputOperations::getValueInt();
            bool isFound = false;

            switch (userChoice)
            {
            case 1:
                clientDatabase.addNewClient();
                break;
            case 2:
                if (clientDatabase.isEmpty() == false)
                {
                    cout << "(1) - Вывести список клиентов"
                        << "\n(2) - Вывести список клиентов и их посылки"
                        << "\n\nВаш выбор>> ";
                    int userChoice = inputOperations::getValueInt();
                    
                    switch (userChoice)
                    {
                    case 1:
                        clientDatabase.displayClients();
                        break;
                    case 2:
                        clientDatabase.displayClientsWithPackages();
                        break;
                    default:
                        cout << "\nТакого кейса нет!\n";
                        break;
                    }
                }
                else cout << "\nБаза данных клиентов пуста!\n";
                break;
            case 3:
                if (clientDatabase.isEmpty() == false) clientDatabase.editClientsInformation();
                else cout << "\nБаза данных клиентов пуста!\n";
                break;
            case 4:
                if (clientDatabase.isEmpty() == false) clientDatabase.deleteClient();
                else cout << "\nБаза данных клиентов пуста!\n";
                break;
            case 5:
                if (clientDatabase.isEmpty() == false)
                {
                    cout << "Выберете клиента, которого вы хотите найти: "<<endl;
                    clientDatabase.displayClients();
                    cout << "\nВведите имя клиента: ";
                    string clientName;
                    inputOperations::cleareBuffer();
                    getline(cin,clientName);
                    int numberOfClient= clientDatabase.findCertainClient(clientName, isFound);

                    if (isFound == true)
                    {
                        clientDatabase.displayCertainClient(numberOfClient);
                        cout << endl;
                    }
                }
                else cout << "\nБаза данных клиентов пуста!\n";
                break;
            case 6:
                if (clientDatabase.isEmpty() == false)
                {
                    clientDatabase.sortClients();
                    clientDatabase.displayClients();
                }
                else cout << "\nБаза данных клиентов пуста!\n";
                break;
            case 7:
                if (clientDatabase.isEmpty() == false) clientDatabase.writeClientsInFile();
                else cout << "\nБаза данных клиентов пуста!\n";
                break;
            case 8:
                if (clientDatabase.isEmpty() == false) clientDatabase.readClientsFromFile();
                else cout << "\nБаза данных клиентов пуста!\n";
                break;
            case 0:
                isWorking = false;
                break;
            default:
                cout << "\nКейса с таким номером нет!\n";
                break;
            }
            system("pause");
            system("cls");
        }
    }

    void managePackageDatabase()
    {
        bool isWorking = true;

        while (isWorking)
        {
            packageDatabase.displayPackageMenu();
            int userChoice = inputOperations::getValueInt();
            bool isFound = false;
            switch (userChoice)
            {
            case 1:
                packageDatabase.addNewPackage();
                break;
            case 2:
                if (packageDatabase.isEmpty() == false)
                {
                    packageDatabase.displayPackages();
                    cout << "Количество посылок - (" << Package::getAmountOfObjects() << ") \n" << endl;
                }
                else cout << "\nБаза данных посылок пуста!\n";
                break;
            case 3:
                if (packageDatabase.isEmpty() == false) packageDatabase.editPackagesInformation();
                else cout << "\nБаза данных посылок пуста!\n";
                break;
            case 4:
                if (packageDatabase.isEmpty() == false) packageDatabase.deletePackageFromDatabase();
                else cout << "\nБаза данных посылок пуста!\n";
                break;
            case 5:
                if (packageDatabase.isEmpty() == false)
                {
                    cout << "Выберете посылку, которую вы хотите найти: ";
                    packageDatabase.displayOnlyNumbersOfPackages();
                    cout << "\nВведите номер посылки: ";
                    string packageName = inputOperations::getValueStr();
                    int numberOfPackage = packageDatabase.findCertainPackege(packageName, isFound);
                }
                else cout << "\nБаза данных посылок пуста!\n";
                break;
            case 6:
                if (packageDatabase.isEmpty() == false)
                {
                    packageDatabase.sortPackages();
                    packageDatabase.displayPackages();
                }
                else cout << "\nБаза данных посылок пуста!\n";
                break;
            case 7:
                if (packageDatabase.isEmpty() == false) packageDatabase.writePackagesInFile();
                else cout << "\nБаза данных посылок пуста!\n";
                break;
            case 8:
                if (packageDatabase.isEmpty() == false) packageDatabase.readPackagesFromFile();
                else cout << "\nБаза данных посылок пуста!\n";
                break;
            case 0:
                isWorking = false;
                break;
            default:
                cout << "\nКейса с таким номером нет!\n";
                break;
            }
            system("pause");
            system("cls");
        }
    }

    void setPosition(string number) { this->position = position; }

    string getPosition() const { return this->position; }

    string getFullName() override { return this->fullName; }
};


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    bool isWorking = true;
    bool isAdmin = true;
    bool isUser = true;
    bool clientQueueWereCreated = false;
    bool isTookQueue = false;
    string login, password;
    bool isCorrectData = false;

    Autorization insert;
    MailWorker worker("Татьяна", "Управлающий");
    MailRecepient recipient;


    while (isWorking)
    {
        cout << "(1) - Войти как пользователь"
            << "\n(2) - Войти как управляющий"
            <<" \n(0) - Выйти"
            << "\n\nВаш выбор>> ";

        int userChoice = inputOperations::getValueInt();
        
        isUser = true;
        isAdmin = true;

        switch (userChoice)
        {
        case 1:
            while (isUser)
            {
                recipient.displayRecepientMenu();
                userChoice = inputOperations::getValueInt();
                
                if (clientQueueWereCreated == false) 
                {
                    recipient.createClientsQueue();
                    clientQueueWereCreated = true;
                } 

                switch (userChoice)
                {
                case 1:
                    if (isTookQueue == true) cout << "\nВы уже заняли очередь! Ваш номер - " << recipient.getAmountOfClients() << endl;
                    else
                    {
                        recipient.getInQueue();
                        cout << "\nВаш номер в очереди - " << recipient.getAmountOfClients() << endl;
                        isTookQueue = true;
                    }
                    break;
                case 2:
                    if (isTookQueue == true)
                    {
                        recipient.waitTimeInQueue();
                    }
                    else cout << "\nЧтобы выполнить это действие - займите очередь!\n";
                    break;
                case 3:
                    if (isTookQueue == true)
                    {
                        if (recipient.getAmountOfClients() == 1)
                        {
                            bool isFound = false;
                            cout << "Вас обслуживает " << worker.getFullName() << " " << worker.getPosition() << endl<<endl;
                            cout << "Для вас есть посылка" << endl;
                            
                            recipient.displayInformation();
                        }
                            //recipient.comeToCheckOut();
                        else cout << "\nПодождите, еще не подошла ваша очередь!\n";
                    }
                    else cout << "\nЧтобы выполнить это действие - займите очередь!\n";
                    break;
                case 0:
                    isUser = false;
                    break;
                default:
                    cout << "\nТакого кейса нет. Попробуйте еще раз!\n";
                    break;
                }

                if (isTookQueue == true)
                {
                    cout << "\n\tОчередь с клиентами" << endl;
                    cout << "======================================================" << endl<<endl;
                    recipient.displayClientsInQueue();
                    cout << "======================================================" << endl;
                }
                
                system("pause");
                system("cls");
            }
            break;
        case 2:
            while (isAdmin)
            {
                insert.autorizationMenu();
                userChoice = inputOperations::getValueInt();

                switch (userChoice)
                {
                case 1:
                    cout << "\tСоздание нового пользователя" << endl;
                    insert.registerNewUser();
                    break;
                case 2:
                    cout << "\tАвторизация" << endl;
                    cout << "Введите данные для входа" << endl << endl;
                    insert.insertLoginAndPassword(login, password);
                    isCorrectData = insert.isCorrectData(login, password);

                    if (isCorrectData)
                    {
                        if (insert.checkLogin(login, "loginAdmin") == true)
                        {
                            while (isAdmin)
                            {
                                cout << "(1) - Управлять базой клиентов"
                                    << "\n(2) - Управлять базой посылок"
                                    << "\n(0) - Выход"
                                    << "\n\nВаш выбор>>";

                                int userChoice = inputOperations::getValueInt();

                                switch (userChoice)
                                {
                                case 1:
                                    worker.manageClientDatabase();
                                    break;
                                case 2:
                                    worker.managePackageDatabase();
                                    break;
                                case 0:
                                    isAdmin = false;
                                default:
                                    cout << "\nКейса с таким номером нет!\n";
                                    break;
                                }
                                system("pause");
                                system("cls");
                            }
                        }
                    }
                    else cout << "\nНекорректный ввод данных, попробуйте еще раз\n";
                    break;
                default:
                    cout << "Кейса с таким вводом нет!\n";
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
            cout << "\nТакого кейса нет. Попробуйте еще раз!\n";
            break;
        }

    }
}
//Добавить возможность отправить посылку.
