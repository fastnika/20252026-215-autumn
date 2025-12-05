/*!
    \file interface.cpp
    \author Мусин А.Р
    \date 1 декабря 2025
    \brief Реализация методов интерфейса
*/

#include "interface.h"
#include "resource.h"

CommandInformation CommandInfo[] = {
    {INTERFACE_COMMAND_1, "Create polygon"},
    {INTERFACE_COMMAND_2, "Remove polygon"},
    {INTERFACE_COMMAND_3, "Calculate distance"},
    {INTERFACE_COMMAND_EXIT, "Exit"},
};

Interface::Interface() : stream(new InterfaceStream()) {
    DEBUG_LOGGING("Init interface");
}

Interface::Interface(InterfaceStream* i_stream) : stream(i_stream) {
    DEBUG_LOGGING("Init interface with stream");
}

Interface::~Interface() {
    DEBUG_LOGGING("Destroy interface");
    leave();
    delete stream;
}

void Interface::set(std::string path) {
    DEBUG_LOGGING("Set stream path " << path);
    try {
        stream->set(path);
    } catch (InterfaceStreamException &ex) {
        throw InterfaceException(ex.res(), ex.msg());
    }
}

void Interface::show() {
    DEBUG_LOGGING("Show menu");
    std::cout << std::endl << "Available commands:" << std::endl;
    for (CommandInformation item : CommandInfo) {
        std::cout << item.ID << ". " << item.description << std::endl;
    }
}

void Interface::invite() {
    DEBUG_LOGGING("Invite input");
    std::cout << std::endl << "Enter command: ";
}

void Interface::leave() {
    DEBUG_LOGGING("Leave interface");
    std::cout << std::endl << "Finish" << std::endl;
}

int Interface::read() {
    DEBUG_LOGGING("Read interface command");
    try {
        int cur_command_ID = stream->read();
        bool is_valid = false;
        for (CommandInformation item : CommandInfo) {
            if (cur_command_ID == item.ID) {
                is_valid = true;
                break;
            }
        }
        return (is_valid) ? cur_command_ID : INTERFACE_COMMAND_BREAK;
    } catch (InterfaceStreamException &ex) {
#ifdef DEBUG_MODE
        ERR_LOGGING(ex.res(), ex.msg());
#endif
        return INTERFACE_COMMAND_INVALID;
    }
}

template <typename T> T Interface::read_ex() {
    DEBUG_LOGGING("Read typed data");
    try {
        return stream->read_ex<T>();
    } catch (InterfaceStreamException &ex) {
        throw InterfaceException(ex.res(), ex.msg());
    }
}

template int Interface::read_ex();
template double Interface::read_ex();
template std::string Interface::read_ex();