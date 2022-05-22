#include "MailRecepient.h"
#include"InputOperations.h"

void MailRecepient::setFullName(string fullName)
{
    this->fullName = fullName;
}

void MailRecepient::displayInformation()
{
    cout << "Имя получателя посылки: " << fullName << endl;
    cout << "\tИнформация о посылке\n" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << "Номер посылки" << "\tКоличество дней для хранения" << "\tДата поступления" << "\tПосылка отдана" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < packets.size(); i++)
    {
        packets[i]->diplayPacketInformation();
    }
}

string MailRecepient::getFullName()
{
    return this->fullName;
}

void MailRecepient::displayRecepientMenu()
{
    cout << "\tКлиентское меню"
        << "\n(1) - Получить посылку"
        << "\n(2) - Отправить посылку"
        << "\n(3) - Посмотреть личную информацию"
        << "\n(4) - Изменить личную информацию"
        << "\n(0) - Уйти"
        << "\n\nВаш выбор>>";
}

void MailRecepient::changePacketInformation(int number)
{
    string packageName;
    int amountOfDaysForStorage;
    int dayOfAdmission;
    int monthOfAdmission;
    int yearOfAdmission;
    bool isFound = false;
    bool isGiven;

    cout << "\nВведите номер посылки: ";
    packageName = inputOperations::getValueStr();

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

    try
    {
        packets[number]->setNumberOfPacket(packageName);
        packets[number]->setAmountOfDaysForStorage(amountOfDaysForStorage);
        packets[number]->setDayOfAdmission(dayOfAdmission);
        packets[number]->setMonthOfAdmission(monthOfAdmission);
        packets[number]->setYearOfAdmission(yearOfAdmission);

    }
    catch (const char* exception)
    {
        cout << "Ошибка: " << exception << endl;
    }
}

int MailRecepient::findCertainPacket(bool& isFound, string numberOfPacket)
{
    isFound = false;

    for (int i = 0; i < packets.size(); i++)
    {
        if (packets[i]->getNumberOfPacket() == numberOfPacket) {
            isFound = true;
            return i;
        }
        else return -1;
    }
}

void MailRecepient::addPacket(shared_ptr<Packet> packet)
{
    packets.push_back(packet);
}

void MailRecepient::deletePacket(int amount)
{
    packets.erase(packets.begin());
    if (amount > 1) packets.clear();
}

int MailRecepient::getAmountOfPackets() const
{
    return packets.size();
}

bool operator <(const shared_ptr<MailRecepient>& firstClient, const shared_ptr<MailRecepient>& secondClient)
{
    if (firstClient.get()->getFullName() < secondClient.get()->getFullName()) return true;
    else return false;
}

ostream& operator<<(ostream& out,shared_ptr <MailRecepient>& mailRecepient)
{
    cout << "Имя получателя посылки: " << mailRecepient->fullName << endl;

    for (int i = 0; i < mailRecepient->packets.size(); i++)
    {
        mailRecepient->packets[i]->diplayPacketInformation();
    }
    return out;
}
