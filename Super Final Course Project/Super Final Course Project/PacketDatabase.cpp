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
        << "\n(0) - Выход"
        << "\n\nВаш выбор>> ";

    file.writeInformationFile("Вывод меню посылок");
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
    file.writeInformationFile("Инициализация начальным значением базы посылок" + packets.size());
}

void PacketDatabase::addNewPacketToDatabase()
{
    string packageName;
    int amountOfDaysForStorage;
    int dayOfAdmission;
    int monthOfAdmission;
    int yearOfAdmission;
    bool isGiven;

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

    cout << "\nПосылка отдана(Да/Нет): ";
    isGiven = inputOperations::getCorrectAnswer();

    packets.push_back(shared_ptr<Packet>(
        new Packet(packageName, amountOfDaysForStorage, dayOfAdmission, monthOfAdmission, yearOfAdmission, isGiven)));
    vector<shared_ptr<Packet>> tempPackets;

    tempPackets.push_back(shared_ptr<Packet>(
        new Packet(packageName, amountOfDaysForStorage, dayOfAdmission, monthOfAdmission, yearOfAdmission, isGiven)));
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
    cout << "\n----------------------------------------------------------------------------------------------------" << endl;
    cout << "Номер посылки" << "\tКоличество дней для хранения" << "\tДата поступления" << "\tПосылка отдана" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
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
