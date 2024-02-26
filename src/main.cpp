// messages end with /r/n. A CR-LF pair. no null terminator
#include <iostream>
#include <cstring>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/poll.h>
class Client {
private:
    int socket;
public:
    std::string s;
    explicit Client(int clientSocket) : socket(clientSocket) {}
    void sendData(const char* data, size_t dataSize) {
        send(socket, data, dataSize, 0);
    }
    ssize_t receiveData(char* buffer, size_t bufferSize) {
        return recv(socket, buffer, bufferSize, 0);
    }
    void closeConnection() {
        close(socket);
    }
    int getSocket() const {
        return socket;
    }
};
int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error: Failed to create socket" << std::endl;
        return 1;
    }
    // Bind the socket to an address and port
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // Listen on all interfaces
    serverAddr.sin_port = htons(8080);        // Listen on port 8080
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error: Failed to bind socket" << std::endl;
        close(serverSocket);
        return 1;
    }
    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) == -1) {
        std::cerr << "Error: Failed to listen for connections" << std::endl;
        close(serverSocket);
        return 1;
    }
    std::vector<Client> clients;
    struct pollfd serverPoll;
    serverPoll.fd = serverSocket;
    serverPoll.events = POLLIN;
 while (true) {
    struct pollfd fds[clients.size() + 1]; // +1 for server socket
    memset(fds, 0, sizeof(fds));
    fds[0].fd = serverSocket;
    fds[0].events = POLLIN;
    // Add client sockets to the pollfd array
    for (size_t i = 0; i < clients.size(); ++i) {
        fds[i + 1].fd = clients[i].getSocket();
        fds[i + 1].events = POLLIN;
    }
    int activity = poll(fds, clients.size() + 1, 100); // Poll with a timeout of 100 milliseconds
    if (activity == -1) {
        std::cerr << "Error: Failed to poll" << std::endl;
        break;
    }
    // Check if the server socket has incoming connection requests
    if (fds[0].revents & POLLIN) {
        int clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == -1) {
            std::cerr << "Error: Failed to accept connection" << std::endl;
        } else {
            std::cout << "New client connected" << std::endl;
            clients.push_back(Client(clientSocket));
        }
    }
    // Check each client socket for incoming data
    for (size_t i = 0; i < clients.size(); ++i) {
        if (fds[i + 1].revents & POLLIN) {
            char buffer[1024];
            ssize_t bytesRead = clients[i].receiveData(buffer, sizeof(buffer));
            if (bytesRead <= 0) {
                // Connection closed or error
                if (bytesRead == 0) {
                    std::cout << "Client disconnected" << std::endl;
                } else {
                    std::cerr << "Error: Failed to receive data from client" << std::endl;
                }
                clients[i].closeConnection();
                clients.erase(clients.begin() + i); // Remove the client from the vector
                --i; // Decrement i to account for the erased element
            } else {
                buffer[bytesRead] = '\0';
                std::cout << "Received from client " << clients[i].getSocket() << ": " << buffer << std::endl;
            }
        }
    }
}
    // Close all client connections
    for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); ++it) {
        it->closeConnection();
    }
    // Close the server socket (not reached in this code)
    close(serverSocket);
    return 0;
}