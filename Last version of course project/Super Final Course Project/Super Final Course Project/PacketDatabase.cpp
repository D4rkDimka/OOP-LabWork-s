#include "PacketDatabase.h"
#include<cstdlib>

void PacketDatabase::displayPacketMenu()
{
    cout << "(1) - Добавить посылку в базу"
        << "\n(2) - Вывести список посылок"
        << "\n(3) - Изменить характеристики посылку"
        << "\n(4) - Удалить посылку из списка"
        << "\n(5) - Найти посылку"
        << "\n(6) - Отсортировать список с посылками"
        << "\n(7) - Чтение из файла"
        << "\n(8) - Поиск по параметру"
        << "\n(0) - Выход"
        << "\n\nВаш выбор>> ";

    file.writeInformationFile("Вывод меню посылок");
}

void PacketDatabase::initializePacketDatabase()
{
    srand(time(NULL));
    vector<string> numberOfPackets = { "GB1052","AS5212","GD6212","FG9210","BS902","VS1568","MR6900","FS2512","GS2521","AQ5211",
                                        "LB2511","ZZ2500","UE4211" ,"NO0821" ,"MZ2911" };
    vector<string> addreses = { " Автозаводской пер. 14","Иерусалимская ул. 4"," шестой Путепроводный пер. 11"
        , "Лермонтова ул. 25", " Нахимова ул. 20", "Связистов ул. 3", "Янки Мавра ул. 17", "Ширмы Григория ул. 3", 
        "Жиновича Иосифа ул. 21", "Калинина ул. 7А", "Ермака пер. 26", "Тарханова ул. 13/А", "Рабочий пер. 2", "Рылеева ул. 12",
        "Иодковская ул. 5", };
    vector<string> firstNames = { "Дмитрий","Александр","Иван","Георгий","Михаил","Борис","Егор","Лариса","Александра"
       ,"Мария","Наталья","Мария","Светлана","Марина","Алексей","Татьяна","Оксана" };
    vector<string> lastNames = { "Лужковский(ая)","Лекашенич","Громов(а)","Озернов(а)","Клубнин(а)","Зиновенко","Капитонов(а)","Богданов(а)"
        ,"Харитонов(а)" ,"Мухин(а)" ,"Князев(а)" ,"Бобылев(а)" ,"Зимин(а)" ,"Пахомов(а)","Шашков(а)","Рогов(а)" };
    
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
    file.writeInformationFile("Инициализация начальным значением базы посылок" + packets.size());
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

    cout << "\tДобавление новой посылки в базу" << endl;
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
   
    cout << "\nВведите адрес получателя: ";
    inputOperations::cleareBuffer();
    getline(cin, address);

    cout << "\nВведите имя отправителя: ";
    inputOperations::cleareBuffer();
    getline(cin, senderName);

    packets.push_back(shared_ptr<Packet>(
        new Packet(packageName, amountOfDaysForStorage, dayOfAdmission, monthOfAdmission, yearOfAdmission, false, address, senderName)));
    vector<shared_ptr<Packet>> tempPackets;

    tempPackets.push_back(shared_ptr<Packet>(
        new Packet(packageName, amountOfDaysForStorage, dayOfAdmission, monthOfAdmission, yearOfAdmission, false, address, senderName)));
    file.writeInFile(tempPackets, "packets.txt");

    file.writeInformationFile("Добавлена посылки ("+ packageName + ") в базу");
    cout << "\nНовая посылка успешно добавлена в базу!\n";
    tempPackets.clear();
}

void PacketDatabase::addNewPacketToDatabase(shared_ptr <Packet> packet)
{
    packets.push_back(packet);

    vector<shared_ptr<Packet>> tempPackets;
    tempPackets.push_back(packet);
    file.writeInFile(tempPackets, "packets.txt");
    file.writeInformationFile("Добавление посылка (" + packet->getNumberOfPacket() + ") в базу");
    tempPackets.clear();
}

void PacketDatabase::displayPacketsFromDatabase()
{
    cout << "\tИнформация о посылках\n" << endl;
    cout << "\n-------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Номер посылки" << "\tКоличество дней для хранения" << "\tДата поступления" << "\tПосылка отдана" <<"\t\tАдрес"<<"\t\tОтправитель"<< endl;
    cout << "---------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < packets.size(); i++)
    {
        packets[i]->diplayPacketInformation();
        cout << endl;
    }

    file.writeInformationFile("Вывод посылок из базы для просмотра");
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

    cout << "Выберете посылку, данные которой вы хотите изменить: " << endl;
    displayOnlyNumbersOfPackets();
    cout << "\nВведите номер посылки: ";
    packageName = inputOperations::getValueStr();

    int numberOfPackage = findCertainPacket(packageName, isFound);

    if (isFound == true)
    {
        cout << "\nВведите новый номер посылки: ";
        string newPackageName = inputOperations::getValueStr();
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

        cout << "\nПосылка отдана(Да/Нет): ";
        isGiven = inputOperations::getCorrectAnswer();


        cout << "\nВведите адрес получателя: ";
        inputOperations::cleareBuffer();
        getline(cin, address);

        cout << "\nВведите имя отправителя: ";
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
            cout << "Ошибка: " << exception << endl;
        }
        file.writeInformationFile("Изменение посылки (" + packageName + ")"+ " на ("+ newPackageName+")");
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
        cout << "Посылка с номером(" << nameOfPackage << ") найдена!" << endl << endl;
        packets[numberOfPackage]->diplayPacketInformation();
    }
    else cout << "Посылки с таким номером нет!" << endl;

    file.writeInformationFile("Поиск посылки("+ packetName+")");
    return numberOfPackage;
}

void PacketDatabase::displayOnlyNumbersOfPackets()
{
    cout << "\n\tИнформация о посылках\n" << endl;

    for (int i = 0; i < packets.size(); i++)
    {
        cout << packets[i]->getNumberOfPacket() << endl;
    }

    file.writeInformationFile("Вывод посылок из базы для просмотра");
}

void PacketDatabase::deleteCertainPacketFromDatabase()
{
    bool isDeleted = false;
    cout << "Выберете посылку, которую вы хотите удалить: " << endl << endl;
    displayOnlyNumbersOfPackets();
    cout << "\nВведите номер посылки: ";
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
        cout << "\nПосылка не была удалена по какой-то причине! Попробуйте еще раз!\n";
    }
    else 
    {
        Packet packet;
        packet.minusAmountOfObjects();
        cout << "Посылка с номером(" << packageName << ") была успешно удалена из базы!\n";

        file.writeInformationFile("Посылка ("+ packageName+") удалена из базы");
    } 
    
   
}

void PacketDatabase::deletePacketsFromDatabase()
{
    packets.clear();

    try
    {
        if (packets.size() != 0) throw "Память не очищина(Упаковки)\n";
    }
    catch (const char* exception)
    {
        cout << "Ошибка: " << exception << endl;
        throw;
    }

    file.writeInformationFile("Полное очищение базы посылок");
}

void PacketDatabase::readPacketsFromFile()
{
    file.readFromFile(packets);
    file.writeInformationFile("Чтение посылок из текстового файла");
}

void PacketDatabase::sortPackages()
{
    sort(packets.begin(), packets.end());
    file.writeInformationFile("Сортировка базы посылок");
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

    cout << "Выберите параметр для фильтрации: "
        << "\n(1) - Найти посылку по номеру"
        << "\n(2) - Найти по адресу"
        << "\n\nВаш выбор>> ";

    int userChoice = inputOperations::getValueInt();

    switch (userChoice)
    {
    case 1:
        cout << "\nВведите номер посылки для поиска: ";
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
        if (isFound == false) cout << "\nПосылок с таким вводом не найдено!\n";
        cout << "\nКоличество посылок - " << counter << endl;
        break;
    case 2:
        cout << "Введите адрес для поиска: ";
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

        if (isFound == false) cout << "\nПосылок с таким вводом не найдено!\n";
        cout << "\nКоличество посылок - " << counter << endl;
        break;
    default:
        cout << "\nКейса с таким номером нет!\n";
        break;
    }
    if (userChoice == 1) file.writeInformationFile("Поиск посылок по номеру посылки");
    else if (userChoice == 2) file.writeInformationFile("Поиск посылок по адресу");
}
