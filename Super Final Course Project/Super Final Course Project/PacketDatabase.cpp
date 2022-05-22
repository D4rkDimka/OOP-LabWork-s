#include "PacketDatabase.h"
#include<cstdlib>

void PacketDatabase::displayPacketMenu()
{
    cout << "(1) - �������� ������� � ����"
        << "\n(2) - ������� ������ �������"
        << "\n(3) - �������� �������������� �������"
        << "\n(4) - ������� ������� �� ������"
        << "\n(5) - ����� �������"
        << "\n(6) - ������������� ������ � ���������"
        << "\n(7) - ������ �� �����"
        << "\n(0) - �����"
        << "\n\n��� �����>> ";

    file.writeInformationFile("����� ���� �������");
}

void PacketDatabase::initializePacketDatabase()
{
    srand(time(NULL));
    vector<string> numberOfPackets = { "GB1052","AS5212","GD6212","FG9210","BS902","VS1568","MR6900","FS2512","GS2521","AQ5211",
                                        "LB2511","ZZ2500","UE4211" ,"NO0821" ,"MZ2911" };
    int startedNumberOfPackages = 15;

    srand(time(NULL));

    for (int i = 0; i < startedNumberOfPackages; i++)
    {
        string numberOfPacket = numberOfPackets[rand() % 14 + 0];

        packets.push_back(shared_ptr<Packet>(
            new Packet(numberOfPacket, rand() % 31 + 1, rand() % 31 + 1, rand() % 12 + 1,
                2020 + rand() % 2, false)));
    }
    file.writeInFile(packets, "packets.txt");
    file.writeInformationFile("������������� ��������� ��������� ���� �������" + packets.size());
}

void PacketDatabase::addNewPacketToDatabase()
{
    string packageName;
    int amountOfDaysForStorage;
    int dayOfAdmission;
    int monthOfAdmission;
    int yearOfAdmission;
    bool isGiven;

    cout << "\t���������� ����� ������� � ����" << endl;
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

    packets.push_back(shared_ptr<Packet>(
        new Packet(packageName, amountOfDaysForStorage, dayOfAdmission, monthOfAdmission, yearOfAdmission, isGiven)));
    vector<shared_ptr<Packet>> tempPackets;

    tempPackets.push_back(shared_ptr<Packet>(
        new Packet(packageName, amountOfDaysForStorage, dayOfAdmission, monthOfAdmission, yearOfAdmission, isGiven)));
    file.writeInFile(tempPackets, "packets.txt");

    file.writeInformationFile("��������� ������� ("+ packageName + ") � ����");
    cout << "\n����� ������� ������� ��������� � ����!\n";
    tempPackets.clear();
}

void PacketDatabase::addNewPacketToDatabase(shared_ptr <Packet> packet)
{
    packets.push_back(packet);

    vector<shared_ptr<Packet>> tempPackets;
    tempPackets.push_back(packet);
    file.writeInFile(tempPackets, "packets.txt");
    file.writeInformationFile("���������� ������� (" + packet->getNumberOfPacket() + ") � ����");
    tempPackets.clear();
}

void PacketDatabase::displayPacketsFromDatabase()
{
    cout << "\t���������� � ��������\n" << endl;
    cout << "\n----------------------------------------------------------------------------------------------------" << endl;
    cout << "����� �������" << "\t���������� ���� ��� ��������" << "\t���� �����������" << "\t������� ������" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < packets.size(); i++)
    {
        packets[i]->diplayPacketInformation();
        cout << endl;
    }

    file.writeInformationFile("����� ������� �� ���� ��� ���������");
}

void PacketDatabase::editPacketsInformation()
{
    string packageName;
    int amountOfDaysForStorage;
    int dayOfAdmission;
    int monthOfAdmission;
    int yearOfAdmission;
    bool isFound = false;
    bool isGiven;

    cout << "�������� �������, ������ ������� �� ������ ��������: " << endl;
    displayOnlyNumbersOfPackets();
    cout << "\n������� ����� �������: ";
    packageName = inputOperations::getValueStr();

    int numberOfPackage = findCertainPacket(packageName, isFound);

    if (isFound == true)
    {
        cout << "\n������� ����� ����� �������: ";
        string newPackageName = inputOperations::getValueStr();
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
            packets[numberOfPackage]->setNumberOfPacket(newPackageName);
            packets[numberOfPackage]->setAmountOfDaysForStorage(amountOfDaysForStorage);
            packets[numberOfPackage]->setDayOfAdmission(dayOfAdmission);
            packets[numberOfPackage]->setMonthOfAdmission(monthOfAdmission);
            packets[numberOfPackage]->setYearOfAdmission(yearOfAdmission);

        }
        catch (const char* exception)
        {
            cout << "������: " << exception << endl;
        }
        file.writeInformationFile("��������� ������� (" + packageName + ")"+ " �� ("+ newPackageName+")");
    }
}

int PacketDatabase::findCertainPacket(string packetName, bool& isFound)
{
    int numberOfPackage = 0;
    string nameOfPackage;

    for (int i = 0; i < packets.size(); i++)
    {
        if (packets[i]->getNumberOfPacket() == packetName)
        {
            isFound = true;
            numberOfPackage = i;
            nameOfPackage = packets[i]->getNumberOfPacket();
        }
    }

    if (isFound == true) {
        cout << "������� � �������(" << nameOfPackage << ") �������!" << endl << endl;
        packets[numberOfPackage]->diplayPacketInformation();
    }
    else cout << "������� � ����� ������� ���!" << endl;

    file.writeInformationFile("����� �������("+ packetName+")");
    return numberOfPackage;
}

void PacketDatabase::displayOnlyNumbersOfPackets()
{
    cout << "\n\t���������� � ��������\n" << endl;

    for (int i = 0; i < packets.size(); i++)
    {
        cout << packets[i]->getNumberOfPacket() << endl;
    }

    file.writeInformationFile("����� ������� �� ���� ��� ���������");
}

void PacketDatabase::deleteCertainPacketFromDatabase()
{
    bool isDeleted = false;
    cout << "�������� �������, ������� �� ������ �������: " << endl << endl;
    displayOnlyNumbersOfPackets();
    cout << "\n������� ����� �������: ";
    string packageName = inputOperations::getValueStr();

    for (int i = 0; i < packets.size(); i++)
    {
        if (packets[i]->getNumberOfPacket() == packageName)
        {
            packets.erase(packets.begin() + i);
            isDeleted = true;
        }
    }

    if (isDeleted == false)
    {
        cout << "\n������� �� ���� ������� �� �����-�� �������! ���������� ��� ���!\n";
    }
    else 
    {
        Packet packet;
        packet.minusAmountOfObjects();
        cout << "������� � �������(" << packageName << ") ���� ������� ������� �� ����!\n";

        file.writeInformationFile("������� ("+ packageName+") ������� �� ����");
    } 
    
   
}

void PacketDatabase::deletePacketsFromDatabase()
{
    packets.clear();

    try
    {
        if (packets.size() != 0) throw "������ �� �������(��������)\n";
    }
    catch (const char* exception)
    {
        cout << "������: " << exception << endl;
        throw;
    }

    file.writeInformationFile("������ �������� ���� �������");
}

void PacketDatabase::readPacketsFromFile()
{
    file.readFromFile(packets);
    file.writeInformationFile("������ ������� �� ���������� �����");
}

void PacketDatabase::sortPackages()
{
    sort(packets.begin(), packets.end());
    file.writeInformationFile("���������� ���� �������");
}

bool PacketDatabase::isEmpty()
{
    if (packets.size() == 0) return true;
    else return false;
}

int PacketDatabase::getSize()
{
    return packets.size();
}
