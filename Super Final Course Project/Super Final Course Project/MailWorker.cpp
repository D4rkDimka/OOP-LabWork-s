#include "MailWorker.h"

void MailWorker::setFullName(string fullName)
{
    bool isCorrect = true;

    for (int i = 0; i < fullName.size(); i++)
    {
        if (fullName[i] > '0' && fullName[i] < '9') isCorrect = false;
    }

    if (isCorrect == false) throw "\n� ����� ����������� �����!\n";
}

void MailWorker::displayInformation()
{
    cout << "��� ���������: " << fullName
        << "\n���������: " << position << endl;
}

void MailWorker::manageClientDatabase()
{
    bool isWorking = true;

    if (clientDatabase.getAmountOfRecepients() == 0 && packageDatabase.isEmpty() == true)
    {
        vector<shared_ptr<Packet>>vectorOfPackets = clientDatabase.initializeMailRecepientDatabase();
        packageDatabase.initializePacketDatabase();

        for (int i = 0; i < vectorOfPackets.size(); i++)
        {
            packageDatabase.addNewPacketToDatabase(vectorOfPackets[i]);
        }
    }
    

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
            if (clientDatabase.isEmpty() == false) clientDatabase.readRecepientsFromFile();
            else cout << "\n���� ������ �������� �����!\n";
            break;
        case 8:
            if (clientDatabase.isEmpty() == false) clientDatabase.findAmountOfPeople();
            else cout << "\n���� ������ �������� �����!\n";
            break;
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

    if (clientDatabase.getAmountOfRecepients() == 0 && packageDatabase.isEmpty() == true)
    {
        vector<shared_ptr<Packet>>vectorOfPackets = clientDatabase.initializeMailRecepientDatabase();
        packageDatabase.initializePacketDatabase();

        for (int i = 0; i < vectorOfPackets.size(); i++)
        {
            packageDatabase.addNewPacketToDatabase(vectorOfPackets[i]);
        }
    }

    while (isWorking)
    {
        packageDatabase.displayPacketMenu();
        int userChoice = inputOperations::getValueInt();
        bool isFound = false;
        switch (userChoice)
        {
        case 1:
            packageDatabase.addNewPacketToDatabase();
            break;
        case 2:
            if (packageDatabase.isEmpty() == false)
            {
                packageDatabase.displayPacketsFromDatabase();
                cout << "���������� ������� - (" << packageDatabase.getSize() << ") \n" << endl;
            }
            else cout << "\n���� ������ ������� �����!\n";
            break;
        case 3:
            if (packageDatabase.isEmpty() == false) packageDatabase.editPacketsInformation();
            else cout << "\n���� ������ ������� �����!\n";
            break;
        case 4:
            if (packageDatabase.isEmpty() == false) packageDatabase.deleteCertainPacketFromDatabase();
            else cout << "\n���� ������ ������� �����!\n";
            break;
        case 5:
            if (packageDatabase.isEmpty() == false)
            {
                cout << "�������� �������, ������� �� ������ �����: ";
                packageDatabase.displayOnlyNumbersOfPackets();
                cout << "\n������� ����� �������: ";
                string packageName = inputOperations::getValueStr();
                int numberOfPackage = packageDatabase.findCertainPacket(packageName, isFound);
            }
            else cout << "\n���� ������ ������� �����!\n";
            break;
        case 6:
            if (packageDatabase.isEmpty() == false)
            {
                packageDatabase.sortPackages();
                packageDatabase.displayPacketsFromDatabase();
            }
            else cout << "\n���� ������ ������� �����!\n";
            break;
        case 7:
            if (packageDatabase.isEmpty() == false) packageDatabase.readPacketsFromFile();
            else cout << "\n���� ������ ������� �����!\n";
            break;
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

string MailWorker::getPosition() const
{
    return this->position;
}

string MailWorker::getFullName()
{
    return this->fullName;
}
