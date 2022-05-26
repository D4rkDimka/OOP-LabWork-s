#pragma once
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

class Packet
{
private:
    string numberOfPacket;
    int amountOfDaysForStorage;
    int dayOfAdmission;
    int monthOfAdmission;
    int yearOfAdmission;
    bool isGiven;
    string address;
    static int amountOfCreatedObjects;
public:
    Packet(){}
    Packet(string numberOfPackage, int amountOfDaysForStorage, int dayOfAdmission, int monthOfAdmission, int yearOfAdmission, bool isGiven) :
        numberOfPacket(numberOfPackage), amountOfDaysForStorage(amountOfDaysForStorage), dayOfAdmission(dayOfAdmission), monthOfAdmission
        (monthOfAdmission), yearOfAdmission(yearOfAdmission), isGiven(isGiven) {
        amountOfCreatedObjects++;
    }

    friend bool operator <(const shared_ptr<Packet>& firstPackage, const shared_ptr<Packet>& secondPackage);

    friend ostream& operator<<(ostream& out,shared_ptr<Packet>& package);

    void diplayPacketInformation();

    void setIsGivenPacket(bool isGiven);

    void setNumberOfPacket(string number);

    void setDayOfAdmission(int dayOfAdmission);

    void setMonthOfAdmission(int monthOfAdmission);

    void setYearOfAdmission(int yearOfAdmission);

    void setAmountOfDaysForStorage(int amountOfDaysForStorage);

    void setAddress(string address);

    bool getCondition() const;

    string getAddress() const;

    string getNumberOfPacket() const;

    int getAmountOfDaysForStorage() const;

    int getDayOfAdmission() const;

    int getMonthOfAdmission() const;

    int getYearOfAdmission() const;

    static int getAmountOfObjects();

    void minusAmountOfObjects();
};

