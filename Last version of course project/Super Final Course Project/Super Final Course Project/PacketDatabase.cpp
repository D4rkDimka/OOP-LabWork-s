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
        << "\n(8) - ����� �� ���������"
        << "\n(0) - �����"
        << "\n\n��� �����>> ";

    file.writeInformationFile("����� ���� �������");
}

void PacketDatabase::initializePacketDatabase()
{
    srand(time(NULL));
    vector<string> numberOfPackets = { "GB1052","AS5212","GD6212","FG9210","BS902","VS1568","MR6900","FS2512","GS2521","AQ5211",
                                        "LB2511","ZZ2500","UE4211" ,"NO0821" ,"MZ2911" };
    vector<string> addreses = { " ������������� ���. 14","������������� ��. 4"," ������ ������������� ���. 11"
        , "���������� ��. 25", " �������� ��. 20", "��������� ��. 3", "���� ����� ��. 17", "����� �������� ��. 3", 
        "�������� ������ ��. 21", "�������� ��. 7�", "������ ���. 26", "��������� ��. 13/�", "������� ���. 2", "������� ��. 12",
        "���������� ��. 5", };
    vector<string> firstNames = { "�������","���������","����","�������","������","�����","����","������","����������"
       ,"�����","�������","�����","��������","������","�������","�������","������" };
    vector<string> lastNames = { "����������(��)","���������","������(�)","�������(�)","�������(�)","���������","���������(�)","��������(�)"
        ,"���������(�)" ,"�����(�)" ,"������(�)" ,"�������(�)" ,"�����(�)" ,"�������(�)","������(�)","�����(�)" };
    
    int startedNumberOfPackages = 15;

    vector<string> fullNames;
    srand(time(NULL));
    for (int i = 0; i < startedNumberOfPackages; i++)
    {
        fullNames.push_back(firstNames[rand() % firstNames.size()] + " " + lastNames[rand() % lastNames.size()]);
    }

    srand(time(NULL));

    for (int i = 0; i < startedNumberOfPackages; i++)
    {
        string numberOfPacket = numberOfPackets[rand() % 14 + 0];

        packets.push_back(shared_ptr<Packet>(
            new Packet(numberOfPacket, rand() % 31 + 1, rand() % 31 + 1, rand() % 12 + 1,
                2020 + rand() % 2, false,addreses[rand()% addreses.size()],fullNames[rand()%fullNames.size()])));
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
    string address;
    string senderName;

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
   
    cout << "\n������� ����� ����������: ";
    inputOperations::cleareBuffer();
    getline(cin, address);

    cout << "\n������� ��� �����������: ";
    inputOperations::cleareBuffer();
    getline(cin, senderName);

    packets.push_back(shared_ptr<Packet>(
        new Packet(packageName, amountOfDaysForStorage, dayOfAdmission, monthOfAdmission, yearOfAdmission, false, address, senderName)));
    vector<shared_ptr<Packet>> tempPackets;

    tempPackets.push_back(shared_ptr<Packet>(
        new Packet(packageName, amountOfDaysForStorage, dayOfAdmission, monthOfAdmission, yearOfAdmission, false, address, senderName)));
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
    cout << "\n-------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "����� �������" << "\t���������� ���� ��� ��������" << "\t���� �����������" << "\t������� ������" <<"\t\t�����"<<"\t\t�����������"<< endl;
    cout << "---------------------------------------------------------------------------------------------------------------------------------" << endl;
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
    string address;
    string senderName;
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


        cout << "\n������� ����� ����������: ";
        inputOperations::cleareBuffer();
        getline(cin, address);

        cout << "\n������� ��� �����������: ";
        inputOperations::cleareBuffer();
        getline(cin, senderName);

        try
        {
            packets[numberOfPackage]->setNumberOfPacket(newPackageName);
            packets[numberOfPackage]->setAmountOfDaysForStorage(amountOfDaysForStorage);
            packets[numberOfPackage]->setDayOfAdmission(dayOfAdmission);
            packets[numberOfPackage]->setMonthOfAdmission(monthOfAdmission);
            packets[numberOfPackage]->setYearOfAdmission(yearOfAdmission);
            packets[numberOfPackage]->setAddress(address);
            packets[numberOfPackage]->setSenderName(senderName);

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

void PacketDatabase::findAmountOfPackets()
{
   
    string numberOfPacket;
    string address;
    int counter = 0;
    string name;
    bool isFound = false;

    cout << "�������� �������� ��� ����������: "
        << "\n(1) - ����� ������� �� ������"
        << "\n(2) - ����� �� ������"
        << "\n\n��� �����>> ";

    int userChoice = inputOperations::getValueInt();

    switch (userChoice)
    {
    case 1:
        cout << "\n������� ����� ������� ��� ������: ";
        inputOperations::cleareBuffer();
        getline(cin, numberOfPacket);

        for (int i = 0; i < packets.size(); i++)
        {
            if (packets[i]->getNumberOfPacket() == numberOfPacket)
            {
                packets[i]->diplayPacketInformation();
                cout << endl;
                isFound = true;
                counter++;
            }
        }
        if (isFound == false) cout << "\n������� � ����� ������ �� �������!\n";
        cout << "\n���������� ������� - " << counter << endl;
        break;
    case 2:
        cout << "������� ����� ��� ������: ";
        inputOperations::cleareBuffer();
        getline(cin, name);

        for (int i = 0; i < packets.size(); i++)
        {
            if (packets[i]->getAddress() == address)
            {
                packets[i]->diplayPacketInformation();
                cout << endl;
                isFound = true;
                counter++;
            }
        }

        if (isFound == false) cout << "\n������� � ����� ������ �� �������!\n";
        cout << "\n���������� ������� - " << counter << endl;
        break;
    default:
        cout << "\n����� � ����� ������� ���!\n";
        break;
    }
    if (userChoice == 1) file.writeInformationFile("����� ������� �� ������ �������");
    else if (userChoice == 2) file.writeInformationFile("����� ������� �� ������");
}
