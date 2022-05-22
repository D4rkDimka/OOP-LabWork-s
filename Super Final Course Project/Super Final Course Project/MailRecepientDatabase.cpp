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

    cout << "\tДобавление нового клиента в базу" << endl;
    cout << "\nВведите имя клиента: ";
    inputOperations::cleareBuffer();
    getline(cin, clientName);
    cout << "\nЕсть ли у клиента посылки: ";
    isGot = inputOperations::getCorrectAnswer();

    if (isGot == true)
    {
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
        cout << "Введите дату получения посылки" << endl;
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

        vector<shared_ptr<Packet>> vector;
        vector.push_back(shared_ptr<Packet>(new Packet(packageName, amountOfDaysForStorage,
            dayOfAdmission, monthOfAdmission, yearOfAdmission, false)));
        recepients.push_back(shared_ptr<MailRecepient>(new MailRecepient(clientName, vector)));
       
        tempRecepients.push_back(shared_ptr<MailRecepient>(new MailRecepient(clientName, vector)));
        file.writeInFile(tempRecepients, "recepients.txt");
        file.writeInformationFile("Добавление нового получателя с именем("+ clientName+")");
        cout << "\nНовый получатель успешно добавлен в базу!\n";
        tempRecepients.clear();
    }
    else
    {
        vector<shared_ptr<Packet>> vector;
        vector.push_back(shared_ptr<Packet>(new Packet("Нет данных", 0,
            0, 0, 0, false)));
        recepients.push_back(shared_ptr<MailRecepient>(new MailRecepient(clientName, vector)));
    
        tempRecepients.push_back(shared_ptr<MailRecepient>(new MailRecepient(clientName, vector)));
        file.writeInFile(tempRecepients, "recepients.txt");
        file.writeInformationFile("Добавление нового получателя с именем(" + clientName + ")");
        cout << "\nНовый получатель успешно добавлен в базу!\n";
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
    file.writeInformationFile("Добавление нового получателя с именем(" + name + ")");
    cout << "\nНовый получатель успешно добавлен в базу!\n";
    tempRecepients.clear();
}

shared_ptr<Packet> MailRecepientDatabase::sendPacketToRecipient(string newRecepintName)
{
    string packageName;
    int amountOfDaysForStorage;
    int dayOfAdmission;
    int monthOfAdmission;
    int yearOfAdmission;

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
    bool isFound = findRecepient(newRecepintName,numberOfRecepient);
    PacketDatabase database;

    if (isFound == true)
    {
        cout << "\nКлиент с таким именем в базе есть, ему будет добавлена посылка!\n";
       
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
        cout << "\nНовый получатель успешно добавлен в базу!\n";
        cout << "\nНовая посылка успешно добавлена в базу!\n";
        tempRecepients.clear();
        tempPackets.clear();

        return shared_ptr<Packet>(new Packet(packageName, amountOfDaysForStorage, dayOfAdmission,
            monthOfAdmission, yearOfAdmission, false));
    }
}

void MailRecepientDatabase::displayRecepientMenu()
{
    cout << "(1) - Добавить нового клиента в базу"
        << "\n(2) - Вывести список клиентов/список клиентов и их посылки"
        << "\n(3) - Изменить характеристики клиента"
        << "\n(4) - Удалить клиента из базы"
        << "\n(5) - Найти клиента"
        << "\n(6) - Отсортировать список клиентов"
        << "\n(7) - Чтение из файла"
        << "\n(8) - Найти по параметру"
        << "\n(0) - Выход"
        << "\n\nВаш выбор>> ";

    file.writeInformationFile("Вывод меню получателей");
}

void MailRecepientDatabase::displayRecepientNamesFromDatabase()
{
    int numberOfClient = 1;

    cout << "\tИнформация о клиентах\n" << endl;

    for (int i = 0; i < recepients.size(); i++)
    {
        cout << numberOfClient << ") " << recepients[i]->getFullName() << endl << endl;

        numberOfClient++;
    }

    cout << "\nОбщее число клиентов - " << getAmountOfRecepients() << endl;

    file.writeInformationFile("Вывод всех получателей из базы для просмотра");
}

void MailRecepientDatabase::displayRecepientsWithPackages()
{
    int numberOfClient = 1;

    cout << "\tИнформация о клиентах\n" << endl;

    for (int i = 0; i < recepients.size(); i++)
    {
        cout << numberOfClient << ") ";
        recepients[i]->displayInformation();
        cout << endl << endl;

        numberOfClient++;
    }

    cout << "\nОбщее число клиентов - " << getAmountOfRecepients() << endl;

    file.writeInformationFile("Вывод всех получателей с посылками из базы для просмотра");
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
    cout << "\nВведите имя клиента, данные которого вы хотите изменить: ";
    inputOperations::cleareBuffer();
    getline(cin, clientName);

    numberOfClient = findCertainRecepient(clientName, isFound);

    if (isFound == true)
    {
        cout << "(1) - Изменить имя клиента"
            << "\n(2) - Изменить данные его посылки"
            << "\n\nВаш выбор>> ";
        int userChoice = inputOperations::getValueInt();

        switch (userChoice)
        {
        case 1:
            cout << "Введите новое имя клиента: ";
            inputOperations::cleareBuffer();
            getline(cin, clientNewName);
            recepients[numberOfClient]->setFullName(clientNewName);
            break;
        case 2:
            while (isWorking)
            {
                recepients[numberOfClient]->displayInformation();
                cout << "Введите номер посылку, которую вы хотите изменить: ";
                numberOfPacket = inputOperations::getValueStr();
                int numberFindPacket = recepients[numberOfClient]->findCertainPacket(isFound, numberOfPacket);

                if (isFound == true)
                {
                    recepients[numberOfClient]->changePacketInformation(numberFindPacket);
                    isWorking = false;
                }
                else cout << "\nНекорректный ввод, попробуйте еще раз!\n";
            }
            break;
        default:
            cout << "\nКейса с таким номер нет!\n";
            break;
        }

        file.writeInformationFile("Изменение имени получателя (" +clientName +") на ("+clientNewName+")");
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
        cout << "Получатель с именем(" << clientName << ") найден!" << endl << endl;
    }
    else cout << "Получатель с таким именем нет!" << endl;

    file.writeInformationFile("Поиск Получатель с именем("+clientName+")");

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

    file.writeInformationFile("Поиск Получатель с именем (" + clientName+")");

    return isFound;
}

void MailRecepientDatabase::deleteCertainRecepientFromDatabase()
{
    bool isDeleted = false;
    cout << "Выберете клиента, которого вы хотите удалить: " << endl << endl;
    displayRecepientNamesFromDatabase();
    cout << "\nВведите имя клиента: ";
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
        cout << "\nПолучатель не был удален по какой-то причине! Попробуйте еще раз!\n";
    }
    else 
    {
        cout << "Получатель с именем(" << clientName << ") был успешно удален из базы!\n";
        file.writeInformationFile("Получатель с именем (" + clientName + ") был удален");
    } 
}

void MailRecepientDatabase::deleteRecepientsFromDatabase()
{
    recepients.clear();
;
    file.writeInformationFile("Полное очищение базы получателей");

    try
    {
        if (recepients.size() != 0) throw "Память не очищина(Клиенты)\n";
    }
    catch (const char* exception)
    {
        cout << "Ошибка: " << exception << endl;
        throw;
    }
}

void MailRecepientDatabase::writeRecepientsInFile()
{
    file.writeInFile(recepients,"recepients.txt");

    file.writeInformationFile("Запись базы получателей в файл");
}

void MailRecepientDatabase::readRecepientsFromFile()
{
    file.readFromFile(recepients);
    file.writeInformationFile("Чтение базы получателей из файла");
}

void MailRecepientDatabase::sortRecepientsInDatabase()
{
    sort(recepients.begin(), recepients.end());
    file.writeInformationFile("Сортировка базы получателей");
}

int MailRecepientDatabase::getAmountOfRecepients() const
{
    return recepients.size();
}

vector<shared_ptr<Packet>> MailRecepientDatabase::initializeMailRecepientDatabase()
{
    vector<string> firstNames = { "Дмитрий","Александр","Иван","Георгий","Михаил","Борис","Егор","Лариса","Александра"
        ,"Мария","Наталья","Мария","Светлана","Марина","Алексей","Татьяна","Оксана" };
    vector<string> lastNames = { "Лужковский(ая)","Лекашенич","Громов(а)","Озернов(а)","Клубнин(а)","Зиновенко","Капитонов(а)","Богданов(а)"
        ,"Харитонов(а)" ,"Мухин(а)" ,"Князев(а)" ,"Бобылев(а)" ,"Зимин(а)" ,"Пахомов(а)","Шашков(а)","Рогов(а)" };
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
        //Записать в файл.
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
    file.writeInformationFile("Инициализация базы получателей начальным значением "+ recepients.size());
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

    cout << "Выберите параметр для фильтрации: "
        << "\n(1) - Найти по количеству посылок"
        << "\n(2) - Найти по имени"
        << "\n\nВаш выбор>> ";

    int userChoice = inputOperations::getValueInt();

    switch (userChoice)
    {
    case 1:
        cout << "\nВведите количество посылок для поиска: ";
        amountOfPackets = inputOperations::getValueInt();
        try
        {
            if (amountOfPackets < 0 || amountOfPackets>5) throw "Ошибка ввода границ для переменной(0 - 5)";
        }
        catch (const char* exception)
        {
            cout << "Ошибка: " << exception << endl;
            while (amountOfPackets < 0 || amountOfPackets>5)
            {
                cout << ">>";
                amountOfPackets = inputOperations::getValueInt();
                cout << "Ошибка: " << exception << endl;
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
        if (isFound == false) cout << "\nПолучателей с таким вводом не найдено!\n";
        cout << "\nКоличество человек - " << counter << endl;
        break;
    case 2:
        cout << "Введите имя для поиска: ";
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

        if (isFound == false) cout << "\nПолучателей с таким вводом не найдено!\n";
        cout << "\nКоличество человек - " << counter << endl;
        break;
    default:
        cout << "\nКейса с таким номером нет!\n";
        break;
    }
    if(userChoice == 1) file.writeInformationFile("Поиск получаталей по количеству посылок");
    else if(userChoice == 2) file.writeInformationFile("Поиск получателей по имени");
}

void MailRecepientDatabase::addNewPacketToRecipient(shared_ptr<Packet> packet,int numberOfRecepient)
{
    recepients[numberOfRecepient]->addPacket(packet);
    file.writeInformationFile("Добавление новой посылки получателю ("+ recepients[numberOfRecepient]->getFullName()+")");
}
