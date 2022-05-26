#include "User.h"

void User::setPassword(string password)
{
	this->password = password;
}

void User::setLogin(string login)
{
	this->login = login;
}

string User::getPassword() const
{
	return this->password;
}

string User::getLogin() const
{
	return this->login;
}
