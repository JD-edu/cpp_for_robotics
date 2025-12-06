#include "TCPSocket.h"

int main() {
    TCPSocket server;
    
    if (!server.createServer(8080)) {
        std::cerr << "Failed to create server" << std::endl;
        return -1;
    }
    
    std::cout << "Server listening on port 8080..." << std::endl;
    
    TCPSocket* client = server.acceptClient();
    if (client) {
        std::cout << "Client connected!" << std::endl;
        
        while (true) {
            std::string data = client->receive();
            if (data.empty()) break;
            
            std::cout << "Received: " << data << std::endl;
            client->send("Echo: " + data);
        }
        
        delete client;
    }
    
    return 0;
}