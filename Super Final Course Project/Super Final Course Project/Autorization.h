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

    void registerNewUser(string login, string password);

    void insertLoginAndPassword(string& login, string& password);

    void displayExistingAccounts();

    int encryptPassword(string password);

    void autorizationMenu();

    bool isCorrectData(string login, string password);

    bool checkLogin(string login, string findWord);

    bool checkForExistingAccount(string login);

    int getFileSize(string fileName);
};

