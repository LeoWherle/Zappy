/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** Client
*/

#include <functional>
#include <cstring>
#include <arpa/inet.h>
#include "Client.hpp"

namespace connection {
    Client::Client(int timeout, std::string &ip, std::size_t port)
    {
        _timeout.tv_sec = timeout / 1000000;
        _timeout.tv_usec = timeout % 1000000;
        _socket = 0;
        _sockAddr.sin_addr.s_addr = inet_addr(ip.c_str());
        _sockAddr.sin_family = AF_INET;
        _sockAddr.sin_port = htons(port);
    }

    Client::~Client()
    {
    }

    void Client::setUpConnection(void)
    {
        _socket = socket(AF_INET, SOCK_STREAM, 0);
        if (_socket <= 0) {
            throw Client::ConnectionExecption("Can't create socket");
        }
        if (connect(_socket, (struct sockaddr *) &_sockAddr, sizeof(_sockAddr)) < 0) {
            throw Client::ConnectionExecption("Can't connect to socket");
        }
    }

    void Client::handleStd(ReadBuffer &in, WriteBuffer &out)
    {
        if (FD_ISSET(STDIN_FILENO, &_readFd)) {
            auto reader = [&](char *buffer, uint32_t size) -> ssize_t {
                return read(STDIN_FILENO, buffer, size);
            };
            try {
                std::cout << "test" << std::endl;
                in.fill_buffer(reader);
                std::cout << "STD: " << in.buffer() << std::endl;
            } catch (ReadBuffer::ReadError const &) {
                std::cerr << "Couldn't read STDIN" << std::endl;
            }
        }
        if (FD_ISSET(STDOUT_FILENO, &_writeFd)) {
            try {
                out._write(STDOUT_FILENO);
            } catch (WriteBuffer::WriteError const &) {
                std::cerr << "Couldn't write to STDOUT" << std::endl;
            }
        }
    }

    void Client::handleConnection(ReadBuffer &in, WriteBuffer &out)
    {
        if (FD_ISSET(_socket, &_readFd)) {
            auto reader = [&](char *buffer, uint32_t size) -> ssize_t {
                return read(_socket, buffer, size);
            };
            in.fill_buffer(reader);
        }
        if (FD_ISSET(_socket, &_writeFd)) {
            out._write(_socket);
        }
    }

    void Client::handleSelect(ReadBuffer &in, WriteBuffer &out, ReadBuffer &stdInput, WriteBuffer &stdOutput)
    {
        FD_ZERO(&_readFd);
        FD_ZERO(&_writeFd);
        FD_SET(STDIN_FILENO, &_readFd);
        FD_SET(_socket, &_readFd);
        if (out.size() > 0) {
            FD_SET(_socket, &_writeFd);
        }
        /*
            Stdout/Stdin are setup for debug purposes.
            We might supress it in the futur
        */
        if (stdOutput.size() > 0) {
            FD_SET(STDOUT_FILENO, &_writeFd);
        }
        /* Max fd is the socket, client must handle connection with the server only*/
        int nbReady = select(_socket + 1, &_readFd, &_writeFd, NULL, NULL);
        if (nbReady < 0) {
            throw Client::ConnectionExecption(strerror(errno));
        } else if (nbReady > 0) {
            try {
                handleStd(stdInput, stdOutput);
                handleConnection(in, out);
            }  catch (WriteBuffer::WriteError const &) {
                throw Client::Disconnection("Couldn't write to the server, closing connection");
            } catch (ReadBuffer::ConnectionClosed const &) {
                throw ReadBuffer::ConnectionClosed("Connection closed, closing GUI");
            } catch (ReadBuffer::ReadError const &e) {
                throw e;
            }
        }
    }
}