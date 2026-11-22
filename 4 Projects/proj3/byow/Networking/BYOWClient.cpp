#include "BYOWClient.hpp"
int main(int argc, char **argv) {
    std::string ip;
    int port;
    if (argc == 3) {
        ip = argv[1];
        port = std::stoi(argv[2]);
    } else {
        std::cout << "BYOW Client\nIP Address: ";
        std::cin >> ip;
        std::cout << "Port: ";
        if (!(std::cin >> port))
            return 1;
    }
    BYOWClient client;
    try {
        client.startConnection(ip, port);
        while (Draw::isOpen()) {
            if (Draw::hasNextKeyTyped())
                client.sendCommand(std::string(1, Draw::nextKeyTyped()));
            if (client.shouldClose())
                break;
            client.showCanvas();
            Draw::pause(1);
        }
    } catch (const std::exception &e) {
        std::cerr << "Disconnected: " << e.what() << '\n';
        client.stopConnection();
        return 1;
    }
    client.stopConnection();
}
