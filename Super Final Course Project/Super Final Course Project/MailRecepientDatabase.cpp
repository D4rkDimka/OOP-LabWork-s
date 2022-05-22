#include "MailRecepientDatabase.h"
#include"PacketDatabase.h"

void MailRecepientDatabase::addNewRecepientToDatabase()
{
    string clientName;
    vector<shared_ptr<MailRecepient>> tempRecepients;
    bool isGot = false;
    string packageName;
    int amountOfDaysForStorage;
    int dayOfAdmission;
    int monthOfAdmission;
    int yearOfAdmission;
    bool isGiven;

    cout << "\t���������� ������ ������� � ����" << endl;
    cout << "\n������� ��� �������: ";
    inputOperations::cleareBuffer();
    getline(cin, clientName);
    cout << "\n���� �� � ������� �������: ";
    isGot = inputOperations::getCorrectAnswer();

    if (isGot == true)
    {
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

        vector<shared_ptr<Packet>> vector;
        vector.push_back(shared_ptr<Packet>(new Packet(packageName, amountOfDaysForStorage,
            dayOfAdmission, monthOfAdmission, yearOfAdmission, false)));
        recepients.push_back(shared_ptr<MailRecepient>(new MailRecepient(clientName, vector)));
       
        tempRecepients.push_back(shared_ptr<MailRecepient>(new MailRecepient(clientName, vector)));
        file.writeInFile(tempRecepients, "recepients.txt");
        file.writeInformationFile("���������� ������ ���������� � ������("+ clientName+")");
        cout << "\n����� ���������� ������� �������� � ����!\n";
        tempRecepients.clear();
    }
    else
    {
        vector<shared_ptr<Packet>> vector;
        vector.push_back(shared_ptr<Packet>(new Packet("��� ������", 0,
            0, 0, 0, false)));
        recepients.push_back(shared_ptr<MailRecepient>(new MailRecepient(clientName, vector)));
    
        tempRecepients.push_back(shared_ptr<MailRecepient>(new MailRecepient(clientName, vector)));
        file.writeInFile(tempRecepients, "recepients.txt");
        file.writeInformationFile("���������� ������ ���������� � ������(" + clientName + ")");
        cout << "\n����� ���������� ������� �������� � ����!\n";
        tempRecepients.clear();
        file.writeInFile(recepients, "recepient.txt");
    }

    
}

void MailRecepientDatabase::addNewRecepientToDatabase(string name, shared_ptr<Packet> packet)
{
    vector<shared_ptr<MailRecepient>> tempRecepients;
    vector<shared_ptr<Packet>> vector;
    recepients.push_back(shared_ptr<MailRecepient>(new MailRecepient(name, vector)));
    vector.push_back(packet);

    tempRecepients.push_back(shared_ptr<MailRecepient>(new MailRecepient(name, vector)));
    file.writeInFile(tempRecepients, "recepients.txt");
    file.writeInformationFile("���������� ������ ���������� � ������(" + name + ")");
    cout << "\n����� ���������� ������� �������� � ����!\n";
    tempRecepients.clear();
}

shared_ptr<Packet> MailRecepientDatabase::sendPacketToRecipient(string newRecepintName)
{
    string packageName;
    int amountOfDaysForStorage;
    int dayOfAdmission;
    int monthOfAdmission;
    int yearOfAdmission;

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
    cout << "������� ���� �������" << endl;
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
    int numberOfRecepient;
    bool isFound = findRecepient(newRecepintName,numberOfRecepient);
    PacketDatabase database;

    if (isFound == true)
    {
        cout << "\n������ � ����� ������ � ���� ����, ��� ����� ��������� �������!\n";
       
        addNewPacketToRecipient(shared_ptr<Packet>(new Packet(packageName, amountOfDaysForStorage, dayOfAdmission,
            monthOfAdmission, yearOfAdmission, false)), numberOfRecepient);

        return shared_ptr<Packet>(new Packet(packageName, amountOfDaysForStorage, dayOfAdmission,
            monthOfAdmission, yearOfAdmission, false)); 
    }
    else
    {
        vector<shared_ptr<MailRecepient>>tempRecepients;
        vector<shared_ptr<Packet>> tempPackets;
        vector<shared_ptr<Packet>> vector;

        vector.push_back(shared_ptr<Packet>(new Packet(packageName, amountOfDaysForStorage,
            dayOfAdmission, monthOfAdmission, yearOfAdmission, false)));

        recepients.push_back(shared_ptr<MailRecepient>(new MailRecepient(newRecepintName, vector)));

        tempRecepients.push_back(shared_ptr<MailRecepient>(new MailRecepient(newRecepintName, vector)));
        tempPackets.push_back(shared_ptr<Packet>(new Packet(packageName, amountOfDaysForStorage,
            dayOfAdmission, monthOfAdmission, yearOfAdmission, false)));
        
        file.writeInFile(tempRecepients, "recepients.txt");
        file.writeInFile(tempRecepients, "packets.txt");
        cout << "\n����� ���������� ������� �������� � ����!\n";
        cout << "\n����� ������� ������� ��������� � ����!\n";
        tempRecepients.clear();
        tempPackets.clear();

        return shared_ptr<Packet>(new Packet(packageName, amountOfDaysForStorage, dayOfAdmission,
            monthOfAdmission, yearOfAdmission, false));
    }
}

void MailRecepientDatabase::displayRecepientMenu()
{
    cout << "(1) - �������� ������ ������� � ����"
        << "\n(2) - ������� ������ ��������/������ �������� � �� �������"
        << "\n(3) - �������� �������������� �������"
        << "\n(4) - ������� ������� �� ����"
        << "\n(5) - ����� �������"
        << "\n(6) - ������������� ������ ��������"
        << "\n(7) - ������ �� �����"
        << "\n(8) - ����� �� ���������"
        << "\n(0) - �����"
        << "\n\n��� �����>> ";

    file.writeInformationFile("����� ���� �����������");
}

void MailRecepientDatabase::displayRecepientNamesFromDatabase()
{
    int numberOfClient = 1;

    cout << "\t���������� � ��������\n" << endl;

    for (int i = 0; i < recepients.size(); i++)
    {
        cout << numberOfClient << ") " << recepients[i]->getFullName() << endl << endl;

        numberOfClient++;
    }

    cout << "\n����� ����� �������� - " << getAmountOfRecepients() << endl;

    file.writeInformationFile("����� ���� ����������� �� ���� ��� ���������");
}

void MailRecepientDatabase::displayRecepientsWithPackages()
{
    int numberOfClient = 1;

    cout << "\t���������� � ��������\n" << endl;

    for (int i = 0; i < recepients.size(); i++)
    {
        cout << numberOfClient << ") ";
        recepients[i]->displayInformation();
        cout << endl << endl;

        numberOfClient++;
    }

    cout << "\n����� ����� �������� - " << getAmountOfRecepients() << endl;

    file.writeInformationFile("����� ���� ����������� � ��������� �� ���� ��� ���������");
}

void MailRecepientDatabase::displayCertainRecepient(int numberOfClient)
{
    recepients[numberOfClient]->displayInformation();
}

void MailRecepientDatabase::editRecepientCharacteristics()
{
    bool isFound = false;
    string clientName;
    string clientNewName;
    int numberOfClient;
    string numberOfPacket;
    bool isWorking = true;
    displayRecepientNamesFromDatabase();
    cout << "\n������� ��� �������, ������ �������� �� ������ ��������: ";
    inputOperations::cleareBuffer();
    getline(cin, clientName);

    numberOfClient = findCertainRecepient(clientName, isFound);

    if (isFound == true)
    {
        cout << "(1) - �������� ��� �������"
            << "\n(2) - �������� ������ ��� �������"
            << "\n\n��� �����>> ";
        int userChoice = inputOperations::getValueInt();

        switch (userChoice)
        {
        case 1:
            cout << "������� ����� ��� �������: ";
            inputOperations::cleareBuffer();
            getline(cin, clientNewName);
            recepients[numberOfClient]->setFullName(clientNewName);
            break;
        case 2:
            while (isWorking)
            {
                recepients[numberOfClient]->displayInformation();
                cout << "������� ����� �������, ������� �� ������ ��������: ";
                numberOfPacket = inputOperations::getValueStr();
                int numberFindPacket = recepients[numberOfClient]->findCertainPacket(isFound, numberOfPacket);

                if (isFound == true)
                {
                    recepients[numberOfClient]->changePacketInformation(numberFindPacket);
                    isWorking = false;
                }
                else cout << "\n������������ ����, ���������� ��� ���!\n";
            }
            break;
        default:
            cout << "\n����� � ����� ����� ���!\n";
            break;
        }

        file.writeInformationFile("��������� ����� ���������� (" +clientName +") �� ("+clientNewName+")");
    }
}

int MailRecepientDatabase::findCertainRecepient(string clientName, bool& isFound)
{
    int numberOfClient = 0;

    for (int i = 0; i < recepients.size(); i++)
    {
        if (recepients[i]->getFullName() == clientName)
        {
            isFound = true;
            numberOfClient = i;
        }
    }

    if (isFound == true) {
        cout << "���������� � ������(" << clientName << ") ������!" << endl << endl;
    }
    else cout << "���������� � ����� ������ ���!" << endl;

    file.writeInformationFile("����� ���������� � ������("+clientName+")");

    return numberOfClient;
}

bool MailRecepientDatabase::findRecepient(string clientName, int& number)
{
    bool isFound = false;

    for (int i = 0; i < recepients.size(); i++)
    {
        if (recepients[i]->getFullName() == clientName)
        {
            isFound = true;
            number = i;
        }
    }

    file.writeInformationFile("����� ���������� � ������ (" + clientName+")");

    return isFound;
}

void MailRecepientDatabase::deleteCertainRecepientFromDatabase()
{
    bool isDeleted = false;
    cout << "�������� �������, �������� �� ������ �������: " << endl << endl;
    displayRecepientNamesFromDatabase();
    cout << "\n������� ��� �������: ";
    string clientName;
    inputOperations::cleareBuffer();
    getline(cin, clientName);

    for (int i = 0; i < recepients.size(); i++)
    {
        if (recepients[i]->getFullName() == clientName)
        {
            recepients.erase(recepients.begin() + i);
            isDeleted = true;
        }
    }

    if (isDeleted == false)
    {
        cout << "\n���������� �� ��� ������ �� �����-�� �������! ���������� ��� ���!\n";
    }
    else 
    {
        cout << "���������� � ������(" << clientName << ") ��� ������� ������ �� ����!\n";
        file.writeInformationFile("���������� � ������ (" + clientName + ") ��� ������");
    } 
}

void MailRecepientDatabase::deleteRecepientsFromDatabase()
{
    recepients.clear();
;
    file.writeInformationFile("������ �������� ���� �����������");

    try
    {
        if (recepients.size() != 0) throw "������ �� �������(�������)\n";
    }
    catch (const char* exception)
    {
        cout << "������: " << exception << endl;
        throw;
    }
}

void MailRecepientDatabase::writeRecepientsInFile()
{
    file.writeInFile(recepients,"recepients.txt");

    file.writeInformationFile("������ ���� ����������� � ����");
}

void MailRecepientDatabase::readRecepientsFromFile()
{
    file.readFromFile(recepients);
    file.writeInformationFile("������ ���� ����������� �� �����");
}

void MailRecepientDatabase::sortRecepientsInDatabase()
{
    sort(recepients.begin(), recepients.end());
    file.writeInformationFile("���������� ���� �����������");
}

int MailRecepientDatabase::getAmountOfRecepients() const
{
    return recepients.size();
}

vector<shared_ptr<Packet>> MailRecepientDatabase::initializeMailRecepientDatabase()
{
    vector<string> firstNames = { "�������","���������","����","�������","������","�����","����","������","����������"
        ,"�����","�������","�����","��������","������","�������","�������","������" };
    vector<string> lastNames = { "����������(��)","���������","������(�)","�������(�)","�������(�)","���������","���������(�)","��������(�)"
        ,"���������(�)" ,"�����(�)" ,"������(�)" ,"�������(�)" ,"�����(�)" ,"�������(�)","������(�)","�����(�)" };
    vector<string> packages = { "GB1052","AS5212","GD6212","FG9210","BS902","VS1568","MR6900","GA2512","SG1245" ,"BA5125" ,"GL2515" ,"TE1234"
        ,"BL5222" ,"AB6125" ,"XX2512" ,"ZH5215" ,"VS6221" ,"PB2512" };
    vector<string> fullNames;
    PacketDatabase packetDatabase;
    int randomAmountOfRecepients = 15;

    srand(time(NULL));
    for (int i = 0; i < randomAmountOfRecepients; i++)
    {
        fullNames.push_back(firstNames[rand() % firstNames.size()] + " " + lastNames[rand() % lastNames.size()]);
    }

    for (int i = 0; i < randomAmountOfRecepients; i++)
    {
        vector<shared_ptr<Packet>> vector;
        recepients.push_back(shared_ptr<MailRecepient>(new MailRecepient(fullNames[i], vector)));
    }

    vector<shared_ptr<Packet>> tempVectorForPackets;

    for (int i = 0; i < randomAmountOfRecepients; i++)
    {
        int randomAmountOfPackets = rand() % 4 + 1;
        //�������� � ����.
        for (int j = 0; j < randomAmountOfPackets; j++)
        {
            string package = packages[rand() % packages.size()];

            packetDatabase.addNewPacketToDatabase(shared_ptr<Packet>(new Packet(package, rand() % 31 + 1, rand() % 31 + 1, rand() % 12 + 1,
                2020 + rand() % 2, false)));
            
            recepients[i]->addPacket(shared_ptr<Packet>(new Packet(package, rand() % 31 + 1, rand() % 31 + 1, rand() % 12 + 1,
                2020 + rand() % 2, false)));

            tempVectorForPackets.push_back(shared_ptr<Packet>(new Packet(package, rand() % 31 + 1, rand() % 31 + 1, rand() % 12 + 1,
                2020 + rand() % 2, false)));
        }
    }

    file.writeInFile(recepients, "recepients.txt");
    file.writeInformationFile("������������� ���� ����������� ��������� ��������� "+ recepients.size());
    return tempVectorForPackets;
}

bool MailRecepientDatabase::isEmpty()
{
    if (recepients.size() == 0)return true;
    else return false;

}

void MailRecepientDatabase::findAmountOfPeople()
{
    int day = 0, month = 0, year = 0;
    int amountOfPackets = 0;
    int counter = 0;
    int number = 0;
    string name;
    bool isFound = false;

    cout << "�������� �������� ��� ����������: "
        << "\n(1) - ����� �� ���������� �������"
        << "\n(2) - ����� �� �����"
        << "\n\n��� �����>> ";

    int userChoice = inputOperations::getValueInt();

    switch (userChoice)
    {
    case 1:
        cout << "\n������� ���������� ������� ��� ������: ";
        amountOfPackets = inputOperations::getValueInt();
        try
        {
            if (amountOfPackets < 0 || amountOfPackets>5) throw "������ ����� ������ ��� ����������(0 - 5)";
        }
        catch (const char* exception)
        {
            cout << "������: " << exception << endl;
            while (amountOfPackets < 0 || amountOfPackets>5)
            {
                cout << ">>";
                amountOfPackets = inputOperations::getValueInt();
                cout << "������: " << exception << endl;
            }
        }

        for (int i = 0; i < recepients.size(); i++)
        {
            if (recepients[i]->getAmountOfPackets() == amountOfPackets)
            {
                recepients[i]->displayInformation();
                cout << endl;
                isFound = true;
                counter++;
            }
        }
        if (isFound == false) cout << "\n����������� � ����� ������ �� �������!\n";
        cout << "\n���������� ������� - " << counter << endl;
        break;
    case 2:
        cout << "������� ��� ��� ������: ";
        inputOperations::cleareBuffer();
        getline(cin, name);

        for (int i = 0; i < recepients.size(); i++)
        {
            if (recepients[i]->getFullName() == name)
            {
                recepients[i]->displayInformation();
                cout << endl;
                isFound = true;
                counter++;
            }
        }

        if (isFound == false) cout << "\n����������� � ����� ������ �� �������!\n";
        cout << "\n���������� ������� - " << counter << endl;
        break;
    default:
        cout << "\n����� � ����� ������� ���!\n";
        break;
    }
    if(userChoice == 1) file.writeInformationFile("����� ����������� �� ���������� �������");
    else if(userChoice == 2) file.writeInformationFile("����� ����������� �� �����");
}

void MailRecepientDatabase::addNewPacketToRecipient(shared_ptr<Packet> packet,int numberOfRecepient)
{
    recepients[numberOfRecepient]->addPacket(packet);
    file.writeInformationFile("���������� ����� ������� ���������� ("+ recepients[numberOfRecepient]->getFullName()+")");
}
