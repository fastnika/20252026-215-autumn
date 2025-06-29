#include <iostream>
#include <fstream>
#include <string>

#pragma once

class InterfaceStream
{
private:
    std::istream* in_stream = nullptr;
public:


    InterfaceStream();
    InterfaceStream(std::istream* stream);
    InterfaceStream(std::string path);
    ~InterfaceStream();
    void set(std::istream* stream);
    void set(std::string path);
    int read();
};


// Обработка исключений