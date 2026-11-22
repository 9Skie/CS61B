#pragma once
#include "Socket.hpp"
#include "Draw.hpp"
class BYOWClient {
    int width = 0, height = 0;
    net::Socket frames, commands;

  public:
    void startConnection(const std::string &ip, int port) {
        frames = net::Socket::connect(ip, port);
        commands = net::Socket::connect(ip, port);
    }
    bool shouldClose() {
        if (commands.ready()) {
            char message[4];
            commands.readAll(message, 4);
            return true;
        }
        return false;
    }
    void stopConnection() {
        frames.close();
        commands.close();
    }
    void sendCommand(const std::string &message) {
        commands.sendAll(message.data(), message.size());
    }
    void showCanvas() {
        if (!frames.ready())
            return;
        bool configure = frames.readNumber(1) != 0;
        if (configure) {
            width = frames.readNumber(4);
            height = frames.readNumber(4);
            Draw::setCanvasSize(width, height);
            Draw::setXscale(0, width);
            Draw::setYscale(0, height);
        }
        auto size = frames.readNumber(8);
        if (size > 64 * 1024 * 1024)
            throw std::runtime_error("Frame too large");
        std::vector<unsigned char> bytes(size);
        frames.readAll(bytes.data(), bytes.size());
        Draw::displayPng(bytes);
    }
};
