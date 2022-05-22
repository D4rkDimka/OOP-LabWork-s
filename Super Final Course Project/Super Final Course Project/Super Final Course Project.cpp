#include"MailRecepientDatabase.h"
#include"Autorization.h"
#include"MailWorker.h"
#include<Windows.h>

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    bool isWorking = true;
    bool isAdmin = true;
    bool isUser = true;
    bool clientQueueWereCreated = false;
    bool isTookQueue = false;
    string login, password;
    bool isCorrectData = false;
    PacketDatabase packetDatabase;
    Autorization autorization;
    MailRecepientDatabase recepientsDatabase;
    MailWorker worker("Татьяна", "Управлающий");
    vector<shared_ptr<Packet>> userPacket;
    vector<string> packages = { "GB1052","AS5212","GD6212","FG9210","BS902","VS1568","MR6900","GA2512","SG1245" ,"BA5125" ,"GL2515" ,"TE1234"
       ,"BL5222" ,"AB6125" ,"XX2512" ,"ZH5215" ,"VS6221" ,"PB2512" };
    srand(time(NULL));
    
    for (int i = 0; i < rand() % 3+1; i++)
    {
        userPacket.push_back(shared_ptr<Packet>(new Packet(packages[rand() % packages.size()], rand() % 31 + 1, rand() % 31 + 1, rand() % 12 + 1,
            2020 + rand() % 2, false)));
        packetDatabase.addNewPacketToDatabase(userPacket[i]);
    }

    MailRecepient recipient("Вы", userPacket);

    if (autorization.getFileSize("LoginsAndPassword.txt") != 0) autorization.clearFile("LoginsAndPassword.txt");
    if(autorization.getFileSize("packets.txt") != 0) autorization.clearFile("packets.txt");
    if (autorization.getFileSize("recepients.txt") != 0) autorization.clearFile("recepients.txt");
    if (autorization.getFileSize("InformationFile.txt") != 0) autorization.clearFile("InformationFile.txt");

    while (isWorking)
    {
        cout << "(1) - Войти как пользователь"
            << "\n(2) - Войти как управляющий"
            << " \n(0) - Выйти"
            << "\n\nВаш выбор>> ";

        int userChoice = inputOperations::getValueInt();

        isUser = true;
        isAdmin = true;
        bool isRecipient = true;
        string nameOfRecipient;
        shared_ptr<Packet> packet;

        switch (userChoice)
        {
        case 1:
            while (isUser)
            {
                cout << "Вас обслуживает:" << endl;
                worker.displayInformation();
                cout << endl;
                recipient.displayRecepientMenu();
                userChoice = inputOperations::getValueInt();

                switch (userChoice)
                {
                case 1:
                    if (recipient.getAmountOfPackets() == 0) cout << "\nВ данный момент для вас нету посылок!\n";
                    else
                    {
                        cout << "\nДля вас пришла посылка(и)!\n";
                        
                        for (int i = 0; i < recipient.getAmountOfPackets(); i++)
                        {
                            recipient.displayInformation();
                            cout << "\nХотите забрать посылку?(Да/Нет): ";
                            bool userDecision = inputOperations::getCorrectAnswer();
                            bool areAll = false;
                            if (recipient.getAmountOfPackets() > 1)
                            {
                                cout << "\nЗабрать сразу все посылки?(Да/Нет): ";
                                areAll = inputOperations::getCorrectAnswer();

                            }
                            if (userDecision == true && areAll == false )
                            {
                                recipient.deletePacket(0);
                                cout << "\nВы забрали посылку!\n";
                            }
                            else if (userDecision == true && areAll == true)
                            {
                                for (int i = 0; i < recipient.getAmountOfPackets(); i++)
                                {
                                    recipient.deletePacket(recipient.getAmountOfPackets());
                                }
                                cout << "\nВы забрали все посылки!\n";
                            }
                            else cout << "\nПриходите в следующий раз, чтобы забрать!\n";
                        }
                    }                    
                    break;
                case 2:
                    inputOperations::cleareBuffer();
                    cout << "Введите имя получателя: ";
                    getline(cin, nameOfRecipient);
                    packet = recepientsDatabase.sendPacketToRecipient(nameOfRecipient);
                    packetDatabase.addNewPacketToDatabase(packet);
                    break;
                case 0:
                    isUser = false;
                    break;
                default:
                    cout << "\nКейса с таким номером нет!\n";
                    break;
                }
                system("pause");
                system("cls");
            }
            break;
        case 2:
            while (isAdmin)
            {
                autorization.autorizationMenu();
                userChoice = inputOperations::getValueInt();

                switch (userChoice)
                {
                case 1:
                    autorization.insertLoginAndPassword(login, password);
                    if (autorization.checkLogin(login, "loginAdmin") == true)
                    {
                        if (autorization.getFileSize("LoginsAndPassword.txt") != -1)
                        {
                            if (autorization.checkForExistingAccount(login) == false)
                            {
                                autorization.registerNewUser(login, password);
                            }
                            else cout << "\nАккаунт с таким логином уже существует,попробуйте еще раз!\n";
                        }
                        else
                        {
                            autorization.registerNewUser(login, password);
                        }
                    }
                    else cout << "\nДанные для логина введены некорректно,попробуйте еще раз!\n";
                    break;
                case 2:
                    if (autorization.getFileSize("LoginsAndPassword.txt") == 0)
                    {
                        cout << "\nСписок аккаунтов пуст, добавьте новый аккаунт!\n";
                    }
                    else
                    {
                        cout << "\tАвторизация" << endl;
                        cout << "Введите данные для входа" << endl << endl;
                        autorization.insertLoginAndPassword(login, password);
                        isCorrectData = autorization.isCorrectData(login, password);

                        if (isCorrectData)
                        {
                            while (isAdmin)
                            {
                                cout << "(1) - Управлять базой клиентов"
                                    << "\n(2) - Управлять базой посылок"
                                    << "\n(0) - Выход"
                                    << "\n\nВаш выбор>>";

                                int userChoice = inputOperations::getValueInt();

                                switch (userChoice)
                                {
                                case 1:
                                    worker.manageClientDatabase();
                                    break;
                                case 2:
                                    worker.managePackageDatabase();
                                    break;
                                case 0:
                                    isAdmin = false;
                                    break;
                                default:
                                    cout << "\nКейса с таким номером нет!\n";
                                    break;
                                }
                                system("pause");
                                system("cls");
                            }
                        }
                        else cout << "\nДанные введены некорректно, попробуйте еще раз!\n";
                    }
                    break;
                default:
                    cout << "\nКейса с таким номером нет!\n";
                    break;
                }
                system("pause");
                system("cls");
            }
            break;
        case 0:
            isWorking = false;
            cout << "\nЗавершение программы\n";
            break;
        default:
            cout << "\nКейса с таким номером нет!\n";
            break;
        }
    }
    recepientsDatabase.deleteRecepientsFromDatabase();
    packetDatabase.deletePacketsFromDatabase();
}
