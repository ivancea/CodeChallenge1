#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

struct Packet {
    int sequence;
    int identifier;
    int data;

    Packet() {}
    Packet(int sequence, int identifier, int data) : sequence(sequence), identifier(identifier), data(data) {}
    Packet(const Packet& other) : sequence(other.sequence), identifier(other.identifier), data(other.data) {}
    Packet(Packet&& other) : sequence(other.sequence), identifier(other.identifier), data(other.data) {}

    Packet& operator=(const Packet& other) {
        sequence = other.sequence;
        identifier = other.identifier;
        data = other.data;
        return *this;
    }
};

vector<Packet> readFile(const string& fileName) {
    ifstream file(fileName);
    
    vector<Packet> packets;

    string temp;

    // Discard header
    getline(file, temp);

    while (!file.eof()) {
        Packet packet;

        file >> dec >> packet.sequence;
        file.ignore();
        file >> dec >> packet.identifier;
        file.ignore();
        file >> hex >> packet.data;

        packets.emplace_back(packet);
    }

    return packets;
}

// With default order, showing identifier: "What a mess, you will need to reorder everything to get the price"

int main() {
    vector<Packet> packets = readFile("test.csv");

    /*sort(packets.begin(), packets.end(), [](const Packet& a, const Packet& b) {
        return a.data < b.data;
    });*/

    for (Packet packet : packets) {
        char ch = packet.identifier;
        cerr << ch;
        cout << ch;
    }
    cerr << endl;
    cout << endl;
}