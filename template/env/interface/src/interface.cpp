#include "interface.h"

Interface::Interface() : stream(new InterfaceStream())
{

}

Interface::Interface(InterfaceStream* i_stream) : stream(i_stream)
{

}

Interface::~Interface()
{
    delete stream;
}

void Interface::set(std::string path)
{
    stream->set(path);

    std::cout << "SELFTEST mode activate";
}

void Interface::show()
{
    std::cout << std::endl << "Available commands:";
    std::cout << std::endl << INTERFACE_COMMAND_1 << ". Command_1";
    std::cout << std::endl << INTERFACE_COMMAND_2 << ". Command_2";
    std::cout << std::endl << INTERFACE_COMMAND_3 << ". Command_3";
    std::cout << std::endl << INTERFACE_COMMAND_EXIT << ". Exit";
}

int Interface::read()
{
    return stream->read();
}