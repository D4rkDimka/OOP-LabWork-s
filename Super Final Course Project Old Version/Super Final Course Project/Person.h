#pragma once
#include<string>
using namespace std;

class Person
{
public:
    virtual void setFullName(string fullName) = 0;
    virtual string getFullName() = 0;
    virtual void displayInformation() = 0;
};

