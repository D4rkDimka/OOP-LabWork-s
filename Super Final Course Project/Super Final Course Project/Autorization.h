#pragma once
#include"User.h"
#include<vector>
#include<fstream>
#include"InputOperations.h"

class Autorization
{
private:
    vector<User> users;
public:
    void clearFile(string fileName);

    void registerNewUser(string login, string password, string fileName,string name);

    void insertLoginAndPassword(string& login, string& password);

    void getLoginAndPassword(string& login, string& password,string fileName,string name);

    void displayExistingAccounts();

    int encryptPassword(string password);

    void autorizationMenu();

    string getPassword(string login);

    bool isCorrectData(string login, string password);

    bool checkLogin(string login, string findWord);

    bool checkForExistingAccount(string login,string fileName);

    int getFileSize(string fileName);

    int getAmountOfAccounts();
};

