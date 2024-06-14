/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** InputParser
*/

#pragma once

#include <string>
#include <vector>

class InputParser {
    public:
        class ParseError: public std::exception {
            private:
                const std::string _message;
            public:
                explicit ParseError(const std::string &message): _message(message) {}
                explicit ParseError(const char *const message): _message(message) {}
                virtual ~ParseError() noexcept { }
                const char *what() const noexcept override { return _message.c_str(); }
        };
        InputParser(int ac, char **av);
        ~InputParser();
        void parseMandatory(void);
        void parseOption(void);
        std::string getAdress(void) const;
        std::size_t getPort(void) const;
        bool getRef(void) const;

    private:
        std::vector<std::string> _inputs;
        std::string _adress;
        std::size_t _port;
        bool _ref;
};
