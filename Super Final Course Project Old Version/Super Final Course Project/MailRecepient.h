#pragma once
#include"Person.h"
#include"Packet.h"
#include<vector>

class MailRecepient :public Person
{
private:
    string fullName;
    vector<shared_ptr<Packet>> packets;
public:
    MailRecepient() {}
    MailRecepient(string fullName, vector<shared_ptr<Packet>> packets) :fullName(fullName),
        packets(packets) {}

    friend ostream& operator <<(ostream& out,shared_ptr< MailRecepient>& mailRecepient);

    friend bool operator <(const shared_ptr<MailRecepient>& firstClient, const shared_ptr<MailRecepient>& secondClient);

    void setFullName(string fullName) override;

    void displayInformation() override;

    string getFullName() override;

    void displayRecepientMenu();

    void changePacketInformation(int number);

    int findCertainPacket(bool& isFound, string numberOfPacket);

    void addPacket(shared_ptr<Packet> packet);

    void deletePacket(int amount);

    int getAmountOfPackets() const;
};

