#include "Autorization.h"
#include<conio.h>

void Autorization::clearFile(string fileName)
{
    std::ofstream ofs;
    ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void Autorization::registerNewUser(string login, string password)
{
    vector<User> tempUsers;
    bool isExist = false;
    string fileName = "LoginsAndPassword.txt";

    isExist = checkForExistingAccount(login);
    if (isExist == true)
    {
        cout << "\nАккаунт с таким логином уже создан, попробуйте еще раз!\n";
    }
    else
    {
        users.push_back(*new User(login, password));

        int encryptedPassword = encryptPassword(password);

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
        fout << encryptedPassword << endl << endl;

        fout.close();
        cout << "\nВся информация была успешно записана!\n";
        tempUsers.clear();
    }

}

void Autorization::insertLoginAndPassword(string& login, string& password)
{
    cout << "Введите логин: ";
    login = inputOperations::getValueStr();
    cout << "Введите пароль: ";
    password = inputOperations::getValueStr();
}

void Autorization::displayExistingAccounts()
{
    for (int i = 0; i < users.size(); i++)
    {
        cout << users[i].getLogin() << " " << users[i].getPassword() << endl << endl;
    }
}

int Autorization::encryptPassword(string password)
{
    hash<string> encrypt;
    unsigned int encryptedPassword = encrypt(password);
    
    return encryptedPassword;
}

void Autorization::autorizationMenu()
{
    cout << "(1) - Добавить новый аккаунт"
        << "\n(2) - Войти в существующий аккаунт"
        << "\n\nВаш выбор>>";
}

bool Autorization::isCorrectData(string login, string password)
{
    bool isCorrect = false;

    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].getLogin() == login && users[i].getPassword() == password) isCorrect = true;
    }

    return isCorrect;
}

bool Autorization::checkLogin(string login, string findWord)
{
    int i, j;
    bool isConsistOf = false;
    int size = login.length() - findWord.length() + 1;

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

bool Autorization::checkForExistingAccount(string userLogin)
{
    string fileName = "LoginsAndPassword.txt";
    ifstream fin;
    bool isExist = false;

    fin.open(fileName, ios_base::in);

    try
    {
        if (fin.is_open() == false || fin.bad() == true) throw runtime_error("Файл не может быть открыт или не существует!");
    }
    catch (runtime_error exception)
    {
        cout << "Ошибка: " << exception.what() << endl;
    }

    string buffer;
    string login;
    string password;
    
    while (!fin.eof())
    {
        getline(fin, login);
        getline(fin, password);
        getline(fin, buffer);
        if (login == userLogin) isExist = true;
    }

    fin.close();
    return isExist;
}

int Autorization::getFileSize(string fileName)
{
    ifstream fin (fileName, ios::in);
    int fileSize = 0;
    fin.seekg(0, ios::end);
    fileSize = fin.tellg();
    fin.close();

    return fileSize;
}
