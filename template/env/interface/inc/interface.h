/*!
\file interface.h
\author Мусин А.Р
\date 1 декабря 2025
\brief Интерфейс приложения
*/

#pragma once

#include "interface_stream.h"
#include "base_exception.h"

#define INTERFACE_COMMAND_BREAK 0
#define INTERFACE_COMMAND_INVALID 5
#define INTERFACE_COMMAND_1 1
#define INTERFACE_COMMAND_2 2
#define INTERFACE_COMMAND_3 3
#define INTERFACE_COMMAND_EXIT 4

typedef struct {
    int ID;
    std::string description;
} CommandInformation;

class Interface {
private:
    InterfaceStream* stream = nullptr;
    bool is_self = false;

public:
    Interface();
    Interface(InterfaceStream* i_stream);
    ~Interface();
    void set(std::string path);
    void show();
    void invite();
    void leave();
    int read();
    template <typename T> T read_ex();
};

class InterfaceException : public BaseException {
public:
    using BaseException::BaseException;
};