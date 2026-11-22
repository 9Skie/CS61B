#pragma once
#include "Support.hpp"
#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <netdb.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>
namespace net {
class Socket {
    int fd = -1;

  public:
    Socket() = default;
    explicit Socket(int descriptor) : fd(descriptor) {
        if (fd < 0)
            throw std::runtime_error(std::strerror(errno));
#ifdef SO_NOSIGPIPE
        int one = 1;
        setsockopt(fd, SOL_SOCKET, SO_NOSIGPIPE, &one, sizeof(one));
#endif
    }
    Socket(const Socket &) = delete;
    Socket &operator=(const Socket &) = delete;
    Socket(Socket &&other) noexcept : fd(other.fd) {
        other.fd = -1;
    }
    Socket &operator=(Socket &&other) noexcept {
        if (this != &other) {
            close();
            fd = other.fd;
            other.fd = -1;
        }
        return *this;
    }
    ~Socket() {
        close();
    }
    void close() noexcept {
        if (fd >= 0) {
            ::close(fd);
            fd = -1;
        }
    }
    static Socket listen(int port) {
        if (port < 1 || port > 65535)
            throw std::invalid_argument("Invalid port");
        Socket s(::socket(AF_INET, SOCK_STREAM, 0));
        int yes = 1;
        setsockopt(s.fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
        sockaddr_in address{};
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = htonl(INADDR_ANY);
        address.sin_port = htons(port);
        if (::bind(s.fd, reinterpret_cast<sockaddr *>(&address), sizeof(address)) < 0 ||
            ::listen(s.fd, 2) < 0)
            throw std::runtime_error(std::strerror(errno));
        return s;
    }
    static Socket connect(const std::string &host, int port) {
        if (port < 1 || port > 65535)
            throw std::invalid_argument("Invalid port");
        addrinfo hints{}, *list = nullptr;
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        int error = getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &list);
        if (error)
            throw std::runtime_error(gai_strerror(error));
        std::unique_ptr<addrinfo, decltype(&freeaddrinfo)> guard(list, freeaddrinfo);
        for (auto *p = list; p; p = p->ai_next) {
            int descriptor = ::socket(p->ai_family, p->ai_socktype, p->ai_protocol);
            if (descriptor < 0)
                continue;
            Socket s(descriptor);
            if (::connect(s.fd, p->ai_addr, p->ai_addrlen) == 0)
                return s;
        }
        throw std::runtime_error("Cannot connect to " + host);
    }
    Socket accept() {
        int result;
        do {
            result = ::accept(fd, nullptr, nullptr);
        } while (result < 0 && errno == EINTR);
        return Socket(result);
    }
    bool ready() const {
        if (fd < 0)
            return false;
        pollfd p{fd, POLLIN, 0};
        int result = ::poll(&p, 1, 0);
        if (result < 0 && errno != EINTR)
            throw std::runtime_error(std::strerror(errno));
        return result > 0 && (p.revents & (POLLIN | POLLHUP | POLLERR));
    }
    void sendAll(const void *data, size_t length) {
        auto *p = static_cast<const unsigned char *>(data);
        while (length) {
#ifdef MSG_NOSIGNAL
            auto n = ::send(fd, p, length, MSG_NOSIGNAL);
#else
            auto n = ::send(fd, p, length, 0);
#endif
            if (n < 0 && errno == EINTR)
                continue;
            if (n <= 0)
                throw std::runtime_error("Socket send failed");
            p += n;
            length -= n;
        }
    }
    void readAll(void *data, size_t length) {
        auto *p = static_cast<unsigned char *>(data);
        while (length) {
            auto n = ::recv(fd, p, length, 0);
            if (n < 0 && errno == EINTR)
                continue;
            if (n <= 0)
                throw std::runtime_error("Socket read failed or peer disconnected");
            p += n;
            length -= n;
        }
    }
    void writeNumber(uint64_t value, int bytes) {
        unsigned char buffer[8];
        for (int i = bytes - 1; i >= 0; --i) {
            buffer[i] = value & 255;
            value >>= 8;
        }
        sendAll(buffer, bytes);
    }
    uint64_t readNumber(int bytes) {
        unsigned char buffer[8];
        readAll(buffer, bytes);
        uint64_t value = 0;
        for (int i = 0; i < bytes; ++i)
            value = (value << 8) | buffer[i];
        return value;
    }
};
} // namespace net
