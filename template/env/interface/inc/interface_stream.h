/*!
\file interface_stream.h
\author Мусин А.Р
\date 1 декабря 2025
\brief Класс для работы с потоком команд
*/

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "base_exception.h"

class InterfaceStream {
private:
    std::istream* in_stream = nullptr;
    bool self_stream_init = false;
    void clear();

public:
    InterfaceStream();
    InterfaceStream(std::istream* stream);
    InterfaceStream(std::string path);
    ~InterfaceStream();
    void set(std::istream* stream);
    void set(std::string path);
    int read();
    template <typename T> T read_ex();
};

class InterfaceStreamException : public BaseException {
public:
    using BaseException::BaseException;
};