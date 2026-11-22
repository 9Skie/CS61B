#pragma once
#include "Socket.hpp"
#include "Draw.hpp"
// C++ port of the networking helper by Arjun Sahai and Boren Tsai.
// Two TCP streams: PNG frames and bidirectional ASCII commands.
class BYOWServer {
    net::Socket server, frames, commands;
    void sendCanvas(int width, int height, bool configure) {
        frames.writeNumber(configure, 1);
        if (configure) {
            frames.writeNumber(width, 4);
            frames.writeNumber(height, 4);
        }
        auto bytes = Draw::png();
        frames.writeNumber(bytes.size(), 8);
        frames.sendAll(bytes.data(), bytes.size());
    }

  public:
    explicit BYOWServer(int port) : server(net::Socket::listen(port)) {
        std::cout << "Server started. Waiting for client to connect...\n";
        frames = server.accept();
        commands = server.accept();
        std::cout << "Client connected!\n";
    }
    void sendCanvasConfig(int width, int height) {
        sendCanvas(width, height, true);
    }
    void sendCanvas() {
        sendCanvas(0, 0, false);
    }
    bool clientHasKeyTyped() {
        return commands.ready();
    }
    char clientNextKeyTyped() {
        char c;
        commands.readAll(&c, 1);
        return c;
    }
    void stopConnection() noexcept {
        try {
            commands.sendAll("QUIT", 4);
        } catch (const std::exception &) {
        }
        commands.close();
        frames.close();
        server.close();
    }
};
