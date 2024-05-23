/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <cstdint>
#include <vector>
#include <string>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include "readBuffer.hpp"
#include "writeBuffer.hpp"

namespace connection {
    class Client {
        public:
            class ConnectionExecption : public std::exception {
                public:
                    explicit ConnectionExecption(const std::string &message): _message(message) {}
                    explicit ConnectionExecption(const char *const message): _message(message) {}
                    const char *what() const noexcept override { return _message.c_str(); }
                private:
                    const std::string _message;
            };
            class Disconnection : public std::exception {
                public:
                    explicit Disconnection(const std::string &message): _message(message) {}
                    explicit Disconnection(const char *const message): _message(message) {}
                    const char *what() const noexcept override { return _message.c_str(); }
                private:
                    const std::string _message;
            };

            /**
             * @brief timeout defined in microseconds
             */
            Client(int timeout, std::string &ip, int port);
            ~Client();

            void handleStd(readBuffer &in, writeBuffer &out);
            void handleConnection(readBuffer &in, writeBuffer &out);
            void setUpConnection(void);
            void handleSelect(readBuffer &in, writeBuffer &out, readBuffer &stdInput, writeBuffer &stdOutput);
        private:
            fd_set _readFd;
            fd_set _writeFd;
            int _socket;
            struct sockaddr_in _sockAddr;
            struct timeval _timeout;
    };
}

#endif /* !CLIENT_HPP_ */