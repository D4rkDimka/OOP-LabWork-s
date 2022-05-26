#include "MailWorker.h"

void MailWorker::setFullName(string fullName)
{
    this->fullName = fullName;
}

void MailWorker::displayInformation()
{
    cout << "��� ���������: " << fullName
        << "\n���������: " << position << endl;
}

void MailWorker::manageClientDatabase()
{
    bool isWorking = true;    

    while (isWorking)
    {
        clientDatabase.displayRecepientMenu();
        int userChoice = inputOperations::getValueInt();
        bool isFound = false;

        switch (userChoice)
        {
        case 1:
            clientDatabase.addNewRecepientToDatabase();
            break;
        case 2:
            if (clientDatabase.isEmpty() == false)
            {
                cout << "(1) - ������� ������ ��������"
                    << "\n(2) - ������� ������ �������� � �� �������"
                    << "\n\n��� �����>> ";
                int userChoice = inputOperations::getValueInt();

                switch (userChoice)
                {
                case 1:
                    clientDatabase.displayRecepientNamesFromDatabase();
                    break;
                case 2:
                    clientDatabase.displayRecepientsWithPackages();
                    break;
                default:
                    cout << "\n������ ����� ���!\n";
                    break;
                }
            }
            else cout << "\n���� ������ �������� �����!\n";
            break;
        case 3:
            if (clientDatabase.isEmpty() == false) clientDatabase.editRecepientCharacteristics();
            else cout << "\n���� ������ �������� �����!\n";
            break;
        case 4:
            if (clientDatabase.isEmpty() == false) clientDatabase.deleteCertainRecepientFromDatabase();
            else cout << "\n���� ������ �������� �����!\n";
            break;
        case 5:
            if (clientDatabase.isEmpty() == false)
            {
                cout << "�������� �������, �������� �� ������ �����: " << endl;
                clientDatabase.displayRecepientNamesFromDatabase();
                cout << "\n������� ��� �������: ";
                string clientName;
                inputOperations::cleareBuffer();
                getline(cin, clientName);
                int numberOfClient = clientDatabase.findCertainRecepient(clientName, isFound);

                if (isFound == true)
                {
                    clientDatabase.displayCertainRecepient(numberOfClient);
                    cout << endl;
                }
            }
            else cout << "\n���� ������ �������� �����!\n";
            break;
        case 6:
            if (clientDatabase.isEmpty() == false)
            {
                clientDatabase.sortRecepientsInDatabase();
                clientDatabase.displayRecepientNamesFromDatabase();
            }
            else cout << "\n���� ������ �������� �����!\n";
            break;
        case 7:
            //if (clientDatabase.isEmpty() == false) clientDatabase.readRecepientsFromFile();
            //else cout << "\n���� ������ �������� �����!\n";
            if (clientDatabase.isEmpty() == false) clientDatabase.findAmountOfPeople();
            else cout << "\n���� ������ �������� �����!\n";
            break;
        //case 8:
            
          //  break;
        case 0:
            isWorking = false;
            break;
        default:
            cout << "\n����� � ����� ������� ���!\n";
            break;
        }
        system("pause");
        system("cls");
    }
}

void MailWorker::managePackageDatabase()
{
    bool isWorking = true;

    while (isWorking)
    {
        packetDatabase.displayPacketMenu();
        int userChoice = inputOperations::getValueInt();
        bool isFound = false;
        switch (userChoice)
        {
        case 1:
            packetDatabase.addNewPacketToDatabase();
            break;
        case 2:
            if (packetDatabase.isEmpty() == false)
            {
                packetDatabase.displayPacketsFromDatabase();
                cout << "���������� ������� - (" << packetDatabase.getSize() << ") \n" << endl;
            }
            else cout << "\n���� ������ ������� �����!\n";
            break;
        case 3:
            if (packetDatabase.isEmpty() == false) packetDatabase.editPacketsInformation();
            else cout << "\n���� ������ ������� �����!\n";
            break;
        case 4:
            if (packetDatabase.isEmpty() == false) packetDatabase.deleteCertainPacketFromDatabase();
            else cout << "\n���� ������ ������� �����!\n";
            break;
        case 5:
            if (packetDatabase.isEmpty() == false)
            {
                cout << "�������� �������, ������� �� ������ �����: ";
                packetDatabase.displayOnlyNumbersOfPackets();
                cout << "\n������� ����� �������: ";
                string packageName = inputOperations::getValueStr();
                int numberOfPackage = packetDatabase.findCertainPacket(packageName, isFound);
            }
            else cout << "\n���� ������ ������� �����!\n";
            break;
        case 6:
            if (packetDatabase.isEmpty() == false)
            {
                packetDatabase.sortPackages();
                packetDatabase.displayPacketsFromDatabase();
            }
            else cout << "\n���� ������ ������� �����!\n";
            break;
        case 7:
          //  if (packetDatabase.isEmpty() == false) packetDatabase.readPacketsFromFile();
            //else cout << "\n���� ������ ������� �����!\n";
            if (packetDatabase.isEmpty() == false) packetDatabase.findAmountOfPackets();
            else cout << "\n���� ������ ������� �����!\n";
            break;
        //case 8: 
        case 0:
            isWorking = false;
            break;
        default:
            cout << "\n����� � ����� ������� ���!\n";
            break;
        }
        system("pause");
        system("cls");
    }
}

void MailWorker::setPosition(string number)
{
    this->position = position;
}

void MailWorker::initializeRecepientAndPacketDatabase()
{
    if (clientDatabase.getAmountOfRecepients() == 0 && packetDatabase.isEmpty() == true)
    {
        vector<shared_ptr<Packet>>vectorOfPackets = clientDatabase.initializeMailRecepientDatabase();
        packetDatabase.initializePacketDatabase();

        for (int i = 0; i < vectorOfPackets.size(); i++)
        {
            packetDatabase.addNewPacketToDatabase(vectorOfPackets[i]);
        }
    }
}

string MailWorker::getPosition() const
{
    return this->position;
}

string MailWorker::getFullName()
{
    return this->fullName;
}

void MailWorker::sendPacket(string newRecepintName)
{
    string packageName;
    int amountOfDaysForStorage;
    int dayOfAdmission;
    int monthOfAdmission;
    int yearOfAdmission;
    string address;
    string senderName;

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
    bool isFound = clientDatabase.findRecepient(newRecepintName, numberOfRecepient);

    cout << "\n������� ����� ����������: ";
    inputOperations::cleareBuffer();
    getline(cin, address);

    cout << "\n������� ��� �����������: ";
    inputOperations::cleareBuffer();
    getline(cin, senderName);

    if (isFound == true)
    {
        cout << "\n������ � ����� ������ � ���� ����, ��� ����� ��������� �������!\n";

         clientDatabase.addNewPacketToRecipient(shared_ptr<Packet>(new Packet(packageName, amountOfDaysForStorage, dayOfAdmission,
            monthOfAdmission, yearOfAdmission, false, address, senderName)), numberOfRecepient);
       packetDatabase.addNewPacketToDatabase(shared_ptr<Packet>(new Packet(packageName, amountOfDaysForStorage, dayOfAdmission,
            monthOfAdmission, yearOfAdmission, false, address, senderName)));
    }
    else
    {
        vector<shared_ptr<Packet>> tempPackets;
        vector<shared_ptr<Packet>> vector;

        vector.push_back(shared_ptr<Packet>(new Packet(packageName, amountOfDaysForStorage,
            dayOfAdmission, monthOfAdmission, yearOfAdmission, false, address, senderName)));

        clientDatabase.addNewRecepientToDatabase(newRecepintName, vector[0]);

        packetDatabase.addNewPacketToDatabase(shared_ptr<Packet>(new Packet(packageName, amountOfDaysForStorage, dayOfAdmission,
            monthOfAdmission, yearOfAdmission, false, address, senderName)));
        cout << "\n����� ���������� ������� �������� � ����!\n";
        cout << "\n����� ������� ������� ��������� � ����!\n";
    }
}
