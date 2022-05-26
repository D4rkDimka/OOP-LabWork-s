#pragma once
#include<iostream>
#include<string>
using namespace std;

class User
{
private:
    string login;
    string password;
public:
    User() {}
    User(string login, string password) :login(login), password(password) {}

    void setPassword(string password);
    void setLogin(string login);

    string getPassword() const;
    string getLogin() const;
};

