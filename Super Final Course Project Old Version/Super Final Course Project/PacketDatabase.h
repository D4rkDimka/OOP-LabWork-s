#pragma once
#include"FileOperations.h"
#include"Packet.h"
#include<algorithm>
class PacketDatabase
{
private:
    vector<shared_ptr<Packet>> packets;
    FileOperations<Packet> file;
public:
    PacketDatabase() {}

    void displayPacketMenu();

    void initializePacketDatabase();

    void addNewPacketToDatabase();

    void addNewPacketToDatabase(shared_ptr <Packet> packet);

    void displayPacketsFromDatabase();

    void editPacketsInformation();

    int findCertainPacket(string packetName, bool& isFound);

    void displayOnlyNumbersOfPackets();

    void deleteCertainPacketFromDatabase();

    void deletePacketsFromDatabase();

    void readPacketsFromFile();

    void sortPackages();

    bool isEmpty();

    int getSize();
    
    void findAmountOfPackets();
};
