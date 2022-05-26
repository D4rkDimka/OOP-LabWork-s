#include "MailWorker.h"

void MailWorker::setFullName(string fullName)
{
    this->fullName = fullName;
}

void MailWorker::displayInformation()
{
    cout << "Имя работника: " << fullName
        << "\nДолжность: " << position << endl;
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
            //if (clientDatabase.isEmpty() == false) clientDatabase.readRecepientsFromFile();
            //else cout << "\nБаза данных клиентов пуста!\n";
            if (clientDatabase.isEmpty() == false) clientDatabase.findAmountOfPeople();
            else cout << "\nБаза данных клиентов пуста!\n";
            break;
        //case 8:
            
          //  break;
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
          //  if (packetDatabase.isEmpty() == false) packetDatabase.readPacketsFromFile();
            //else cout << "\nБаза данных посылок пуста!\n";
            if (packetDatabase.isEmpty() == false) packetDatabase.findAmountOfPackets();
            else cout << "\nБаза данных посылок пуста!\n";
            break;
        //case 8: 
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

    cout << "\nВведите номер посылки: ";
    packageName = inputOperations::getValueStr();
    inputOperations::cleareBuffer();
    cout << "\nВведите количество дней для хранения данной посылки: ";
    amountOfDaysForStorage = inputOperations::getValueInt();
    try
    {
        if (amountOfDaysForStorage < 0 || amountOfDaysForStorage >31) throw "Ошибка ввода границ для переменной(0 - 31)";
    }
    catch (const char* exception)
    {
        cout << "Ошибка: " << exception << endl;
        while (amountOfDaysForStorage < 0 || amountOfDaysForStorage >31)
        {
            cout << ">>";
            amountOfDaysForStorage = inputOperations::getValueInt();
            cout << "Ошибка: " << exception << endl;
        }
    }
    cout << "\n============================================" << endl;
    cout << "Введите дату посылки" << endl;
    cout << "============================================" << endl;
    cout << "\nВведите день: ";
    dayOfAdmission = inputOperations::getValueInt();

    try
    {
        if (dayOfAdmission < 0 || dayOfAdmission > 31) throw "Ошибка ввода границ для переменной(0 - 31)";
    }
    catch (const char* exception)
    {
        cout << "Ошибка: " << exception << endl;
        while (dayOfAdmission < 0 || dayOfAdmission > 31)
        {
            cout << ">>";
            dayOfAdmission = inputOperations::getValueInt();
            cout << "Ошибка: " << exception << endl;
        }
    }

    cout << "\nВведите месяц: ";
    monthOfAdmission = inputOperations::getValueInt();

    try
    {
        if (monthOfAdmission < 0 || monthOfAdmission>12) throw "Ошибка ввода границ для переменной(0 - 12)";
    }
    catch (const char* exception)
    {
        cout << "Ошибка: " << exception << endl;
        while (monthOfAdmission < 0 || monthOfAdmission > 12)
        {
            cout << ">>";
            monthOfAdmission = inputOperations::getValueInt();
            cout << "Ошибка: " << exception << endl;
        }
    }

    cout << "\nВведите год: ";
    yearOfAdmission = inputOperations::getValueInt();

    try
    {
        if (yearOfAdmission < 2000 || yearOfAdmission >2022) throw "Ошибка ввода границ для переменной(2000 - 2022)";
    }
    catch (const char* exception)
    {
        cout << "Ошибка: " << exception << endl;
        while (yearOfAdmission < 2000 || yearOfAdmission > 2022)
        {
            cout << ">>";
            yearOfAdmission = inputOperations::getValueInt();
            cout << "Ошибка: " << exception << endl;
        }
    }
    int numberOfRecepient;
    bool isFound = clientDatabase.findRecepient(newRecepintName, numberOfRecepient);

    cout << "\nВведите адрес получателя: ";
    inputOperations::cleareBuffer();
    getline(cin, address);

    cout << "\nВведите имя отправителя: ";
    inputOperations::cleareBuffer();
    getline(cin, senderName);

    if (isFound == true)
    {
        cout << "\nКлиент с таким именем в базе есть, ему будет добавлена посылка!\n";

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
        cout << "\nНовый получатель успешно добавлен в базу!\n";
        cout << "\nНовая посылка успешно добавлена в базу!\n";
    }
}
