#pragma once
#include"Person.h"
#include"PacketDatabase.h"
#include"MailRecepientDatabase.h"

class MailWorker :public Person
{
private:
    string fullName;
    string position;
    PacketDatabase packetDatabase;
    MailRecepientDatabase clientDatabase;
public:
    MailWorker(string fullName, string position) :fullName(fullName), position(position) {}

    void setFullName(string fullName) override;

    void displayInformation() override;

    void manageClientDatabase();

    void managePackageDatabase();

    void setPosition(string number);

    void initializeRecepientAndPacketDatabase();

    string getPosition() const;

    string getFullName() override;

    void  sendPacket(string newRecepintName);
};

