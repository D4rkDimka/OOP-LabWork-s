#include "MailRecepient.h"
#include"InputOperations.h"

void MailRecepient::setFullName(string fullName)
{
    this->fullName = fullName;
}

void MailRecepient::displayInformation()
{
    cout << "��� ���������� �������: " << fullName << endl;
    cout << "\t���������� � �������\n" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "����� �������" << "\t���������� ���� ��� ��������" << "\t���� �����������" << "\t������� ������" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < packets.size(); i++)
    {
        packets[i]->diplayPacketInformation();
    }
}

string MailRecepient::getFullName()
{
    return this->fullName;
}

void MailRecepient::displayRecepientMenu()
{
    cout << "\t���������� ����"
        << "\n(1) - �������� �������"
        << "\n(2) - ��������� �������"
        << "\n(3) - ���������� ������ ����������"
        << "\n(4) - �������� ������ ����������"
        << "\n(0) - ����"
        << "\n\n��� �����>>";
}

void MailRecepient::changePacketInformation(int number)
{
    string packageName;
    int amountOfDaysForStorage;
    int dayOfAdmission;
    int monthOfAdmission;
    int yearOfAdmission;
    bool isFound = false;
    bool isGiven;

    cout << "\n������� ����� �������: ";
    packageName = inputOperations::getValueStr();

    cout << "\n������� ����� �������: ";
    packageName = inputOperations::getValueStr();
    inputOperations::cleareBuffer();
    cout << "\n������� ���������� ���� ��� �������� ������ �������: ";
    amountOfDaysForStorage = inputOperations::getValueInt();
    try
    {
        if (amountOfDaysForStorage < 0 || amountOfDaysForStorage >31) throw "������ ����� ������ ��� ����������(0 - 31)";
    }
    catch (const char* exception)
    {
        cout << "������: " << exception << endl;
        while (amountOfDaysForStorage < 0 || amountOfDaysForStorage >31)
        {
            cout << ">>";
            amountOfDaysForStorage = inputOperations::getValueInt();
            cout << "������: " << exception << endl;
        }
    }
    cout << "\n============================================" << endl;
    cout << "������� ���� ��������� �������" << endl;
    cout << "============================================" << endl;
    cout << "\n������� ����: ";
    dayOfAdmission = inputOperations::getValueInt();

    try
    {
        if (dayOfAdmission < 0 || dayOfAdmission > 31) throw "������ ����� ������ ��� ����������(0 - 31)";
    }
    catch (const char* exception)
    {
        cout << "������: " << exception << endl;
        while (dayOfAdmission < 0 || dayOfAdmission > 31)
        {
            cout << ">>";
            dayOfAdmission = inputOperations::getValueInt();
            cout << "������: " << exception << endl;
        }
    }

    cout << "\n������� �����: ";
    monthOfAdmission = inputOperations::getValueInt();

    try
    {
        if (monthOfAdmission < 0 || monthOfAdmission>12) throw "������ ����� ������ ��� ����������(0 - 12)";
    }
    catch (const char* exception)
    {
        cout << "������: " << exception << endl;
        while (monthOfAdmission < 0 || monthOfAdmission > 12)
        {
            cout << ">>";
            monthOfAdmission = inputOperations::getValueInt();
            cout << "������: " << exception << endl;
        }
    }

    cout << "\n������� ���: ";
    yearOfAdmission = inputOperations::getValueInt();

    try
    {
        if (yearOfAdmission < 2000 || yearOfAdmission >2022) throw "������ ����� ������ ��� ����������(2000 - 2022)";
    }
    catch (const char* exception)
    {
        cout << "������: " << exception << endl;
        while (yearOfAdmission < 2000 || yearOfAdmission > 2022)
        {
            cout << ">>";
            yearOfAdmission = inputOperations::getValueInt();
            cout << "������: " << exception << endl;
        }
    }

    cout << "\n������� ������(��/���): ";
    isGiven = inputOperations::getCorrectAnswer();

    try
    {
        packets[number]->setNumberOfPacket(packageName);
        packets[number]->setAmountOfDaysForStorage(amountOfDaysForStorage);
        packets[number]->setDayOfAdmission(dayOfAdmission);
        packets[number]->setMonthOfAdmission(monthOfAdmission);
        packets[number]->setYearOfAdmission(yearOfAdmission);

    }
    catch (const char* exception)
    {
        cout << "������: " << exception << endl;
    }
}

int MailRecepient::findCertainPacket(bool& isFound, string numberOfPacket)
{
    isFound = false;

    for (int i = 0; i < packets.size(); i++)
    {
        if (packets[i]->getNumberOfPacket() == numberOfPacket) {
            isFound = true;
            return i;
        }
        else return -1;
    }
}

void MailRecepient::addPacket(shared_ptr<Packet> packet)
{
    packets.push_back(packet);
}

void MailRecepient::deletePacket(int amount)
{
    packets.erase(packets.begin());
    if (amount > 1) packets.clear();
}

int MailRecepient::getAmountOfPackets() const
{
    return packets.size();
}

bool operator <(const shared_ptr<MailRecepient>& firstClient, const shared_ptr<MailRecepient>& secondClient)
{
    if (firstClient.get()->getFullName() < secondClient.get()->getFullName()) return true;
    else return false;
}

ostream& operator<<(ostream& out,shared_ptr <MailRecepient>& mailRecepient)
{
    cout << "��� ���������� �������: " << mailRecepient->fullName << endl;

    for (int i = 0; i < mailRecepient->packets.size(); i++)
    {
        mailRecepient->packets[i]->diplayPacketInformation();
    }
    return out;
}
