#include "TCPSocket.h"

int main() {
    TCPSocket client;
    
    if (!client.connectToServer("127.0.0.1", 8080)) {
        std::cerr << "Failed to connect" << std::endl;
        return -1;
    }
    
    std::cout << "Connected to server!" << std::endl;
    
    std::string command;
    while (true) {
        std::cout << "Enter command: ";
        std::getline(std::cin, command);
        
        if (command == "quit") break;
        
        client.send(command);
        std::string response = client.receive();
        std::cout << "Server: " << response << std::endl;
    }
    
    return 0;
}