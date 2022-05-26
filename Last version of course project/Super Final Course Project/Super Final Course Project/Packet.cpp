#include "Packet.h"

void Packet::diplayPacketInformation()
{
    cout.setf(ios::boolalpha);
    cout << this->numberOfPacket << "\t\t\t" << this->amountOfDaysForStorage << "\t\t\t   " << dayOfAdmission << "/" << monthOfAdmission << "/" << yearOfAdmission << "\t\t    " << isGiven << "\t" << this->address << "\t" << this->senderName << endl;
    cout.unsetf(ios::boolalpha);
}

bool operator <(const shared_ptr<Packet>& firstPackage, const shared_ptr<Packet>& secondPackage)
{
    if (firstPackage.get()->getAmountOfDaysForStorage() < secondPackage.get()->getAmountOfDaysForStorage()) return true;
    else return false;
}

ostream& operator<<(ostream& out, shared_ptr<Packet>& package)
{
    cout.setf(ios::boolalpha);
    cout << "Номер посылки: " << package->numberOfPacket
        << "\nКоличество дней для хранения: " << package->amountOfDaysForStorage
        << "\nДата поступления: " << package->dayOfAdmission << "/" << package->monthOfAdmission << "/" << package->yearOfAdmission
        << "\nПосылка отдана: " << package->isGiven
        << "\nАдрес: " << package->address
        << "\nИмя отправителя: " << package->senderName << endl;
        
    cout.unsetf(ios::boolalpha);
    return out;
}

void Packet::setIsGivenPacket(bool isGiven)
{
    this->isGiven = isGiven;
}

void Packet::setNumberOfPacket(string number)
{
    this->numberOfPacket = number;
}

void Packet::setDayOfAdmission(int dayOfAdmission)
{
    this->dayOfAdmission = dayOfAdmission;
}

void Packet::setMonthOfAdmission(int monthOfAdmission)
{
    this->monthOfAdmission = monthOfAdmission;
}

void Packet::setYearOfAdmission(int yearOfAdmission)
{
    this->yearOfAdmission = yearOfAdmission;
}

void Packet::setAmountOfDaysForStorage(int amountOfDaysForStorage)
{
    this->amountOfDaysForStorage = amountOfDaysForStorage;
}

void Packet::setAddress(string address)
{
    this->address = address;
}

void Packet::setSenderName(string name)
{
    this->senderName = name;
}

string Packet::getSenderName() const
{
    return this->senderName;
}

bool Packet::getCondition() const
{
    return this->isGiven;
}

string Packet::getAddress() const
{
    return this->address;
}

string Packet::getNumberOfPacket() const
{
    return this->numberOfPacket;
}

int Packet::getAmountOfDaysForStorage() const
{
    return this->amountOfDaysForStorage;
}

int Packet::getDayOfAdmission() const
{
    return this->dayOfAdmission;
}

int Packet::getMonthOfAdmission() const
{
    return this->monthOfAdmission;
}

int Packet::getYearOfAdmission() const
{
    return this->yearOfAdmission;
}

int Packet::getAmountOfObjects()
{
    return amountOfCreatedObjects;
}

void Packet::minusAmountOfObjects()
{
    Packet::amountOfCreatedObjects--;
}

int Packet::amountOfCreatedObjects = 0;