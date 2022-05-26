#include "MailWorker.h"

void MailWorker::setFullName(string fullName)
{
    bool isCorrect = true;

    for (int i = 0; i < fullName.size(); i++)
    {
        if (fullName[i] > '0' && fullName[i] < '9') isCorrect = false;
    }

    if (isCorrect == false) throw "\nВ имени присутсвуют цифры!\n";
}

void MailWorker::displayInformation()
{
    cout << "Имя работника: " << fullName
        << "\nДолжность: " << position << endl;
}

void MailWorker::manageClientDatabase()
{
    bool isWorking = true;

    if (clientDatabase.getAmountOfRecepients() == 0 && packetDatabase.isEmpty() == true)
    {
        vector<shared_ptr<Packet>>vectorOfPackets = clientDatabase.initializeMailRecepientDatabase();
        packetDatabase.initializePacketDatabase();

        for (int i = 0; i < vectorOfPackets.size(); i++)
        {
            packetDatabase.addNewPacketToDatabase(vectorOfPackets[i]);
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
                cout << "(1) - Вывести список клиентов"
                    << "\n(2) - Вывести список клиентов и их посылки"
                    << "\n\nВаш выбор>> ";
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
                    cout << "\nТакого кейса нет!\n";
                    break;
                }
            }
            else cout << "\nБаза данных клиентов пуста!\n";
            break;
        case 3:
            if (clientDatabase.isEmpty() == false) clientDatabase.editRecepientCharacteristics();
            else cout << "\nБаза данных клиентов пуста!\n";
            break;
        case 4:
            if (clientDatabase.isEmpty() == false) clientDatabase.deleteCertainRecepientFromDatabase();
            else cout << "\nБаза данных клиентов пуста!\n";
            break;
        case 5:
            if (clientDatabase.isEmpty() == false)
            {
                cout << "Выберете клиента, которого вы хотите найти: " << endl;
                clientDatabase.displayRecepientNamesFromDatabase();
                cout << "\nВведите имя клиента: ";
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
            else cout << "\nБаза данных клиентов пуста!\n";
            break;
        case 6:
            if (clientDatabase.isEmpty() == false)
            {
                clientDatabase.sortRecepientsInDatabase();
                clientDatabase.displayRecepientNamesFromDatabase();
            }
            else cout << "\nБаза данных клиентов пуста!\n";
            break;
        case 7:
            if (clientDatabase.isEmpty() == false) clientDatabase.readRecepientsFromFile();
            else cout << "\nБаза данных клиентов пуста!\n";
            break;
        case 8:
            if (clientDatabase.isEmpty() == false) clientDatabase.findAmountOfPeople();
            else cout << "\nБаза данных клиентов пуста!\n";
            break;
        case 0:
            isWorking = false;
            break;
        default:
            cout << "\nКейса с таким номером нет!\n";
            break;
        }
        system("pause");
        system("cls");
    }
}

void MailWorker::managePackageDatabase()
{
    bool isWorking = true;

    if (clientDatabase.getAmountOfRecepients() == 0 && packetDatabase.isEmpty() == true)
    {
        vector<shared_ptr<Packet>>vectorOfPackets = clientDatabase.initializeMailRecepientDatabase();
        packetDatabase.initializePacketDatabase();

        for (int i = 0; i < vectorOfPackets.size(); i++)
        {
            packetDatabase.addNewPacketToDatabase(vectorOfPackets[i]);
        }
    }

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
                cout << "Количество посылок - (" << packetDatabase.getSize() << ") \n" << endl;
            }
            else cout << "\nБаза данных посылок пуста!\n";
            break;
        case 3:
            if (packetDatabase.isEmpty() == false) packetDatabase.editPacketsInformation();
            else cout << "\nБаза данных посылок пуста!\n";
            break;
        case 4:
            if (packetDatabase.isEmpty() == false) packetDatabase.deleteCertainPacketFromDatabase();
            else cout << "\nБаза данных посылок пуста!\n";
            break;
        case 5:
            if (packetDatabase.isEmpty() == false)
            {
                cout << "Выберете посылку, которую вы хотите найти: ";
                packetDatabase.displayOnlyNumbersOfPackets();
                cout << "\nВведите номер посылки: ";
                string packageName = inputOperations::getValueStr();
                int numberOfPackage = packetDatabase.findCertainPacket(packageName, isFound);
            }
            else cout << "\nБаза данных посылок пуста!\n";
            break;
        case 6:
            if (packetDatabase.isEmpty() == false)
            {
                packetDatabase.sortPackages();
                packetDatabase.displayPacketsFromDatabase();
            }
            else cout << "\nБаза данных посылок пуста!\n";
            break;
        case 7:
            if (packetDatabase.isEmpty() == false) packetDatabase.readPacketsFromFile();
            else cout << "\nБаза данных посылок пуста!\n";
            break;
        case 8:
            if (packetDatabase.isEmpty() == false) packetDatabase.findAmountOfPackets();
            else cout << "\nБаза данных посылок пуста!\n";
            break;
        case 0:
            isWorking = false;
            break;
        default:
            cout << "\nКейса с таким номером нет!\n";
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
