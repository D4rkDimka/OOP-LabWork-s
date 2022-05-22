#pragma once
#include"Packet.h"
#include"MailRecepient.h"
#include"FileOperations.h"
#include<algorithm>
class MailRecepientDatabase
{
private:
    vector<shared_ptr <MailRecepient>> recepients;
    FileOperations<MailRecepient> file;

public:
    void addNewPacketToRecipient(shared_ptr<Packet> packet,int number);

    void addNewRecepientToDatabase();

    void addNewRecepientToDatabase(string name, shared_ptr <Packet> packet);

    shared_ptr<Packet> sendPacketToRecipient(string newRecepintName);

    void displayRecepientMenu();

    void displayRecepientNamesFromDatabase();

    void displayRecepientsWithPackages();

    void displayCertainRecepient(int numberOfClient);

    void editRecepientCharacteristics();

    int findCertainRecepient(string clientName, bool& isFound);

    bool findRecepient(string clientName,int& number);

    void deleteCertainRecepientFromDatabase();

    void deleteRecepientsFromDatabase();

    void writeRecepientsInFile();

    void readRecepientsFromFile();

    void sortRecepientsInDatabase();

    int getAmountOfRecepients() const;

    vector<shared_ptr<Packet>> initializeMailRecepientDatabase();

    bool isEmpty();

    void findAmountOfPeople();
        
};

