#include "interface_stream.h"

#pragma once

#define INTERFACE_COMMAND_BREAK     0
#define INTERFACE_COMMAND_INVALID   5
#define INTERFACE_COMMAND_1         1
#define INTERFACE_COMMAND_2         2
#define INTERFACE_COMMAND_3         3
#define INTERFACE_COMMAND_EXIT      4

class Interface
{
private:
    InterfaceStream* stream = nullptr;
    bool is_self = false;
public:

    Interface();
    Interface(InterfaceStream* i_stream);
    ~Interface();
    void set(std::string path);
    void show();
    int read();
};

// TODO  ласс с исключением