/*!
    \file interface.cpp
    \author Фамилия И.О.
    \date 1 Января 2025
    \brief Заголовочный файл-образец с описанием методов интерфейса

    Примечание: Данный файл является шаблоном-образцом для редактирования
*/

#include "interface.h"
#include "resource.h"

/*!
    Список доступных пользовательских команд для ввода
*/
CommandInformation CommandInfo[] =
{
    {INTERFACE_COMMAND_1,    "Command_1"},
    {INTERFACE_COMMAND_2,    "Command_2"},
    {INTERFACE_COMMAND_3,    "Command_3"},
    {INTERFACE_COMMAND_EXIT, "Exit"},
};


Interface::Interface() : stream(new InterfaceStream())
{
    DEBUG_LOGGING("Init interface");
}

Interface::Interface(InterfaceStream* i_stream) : stream(i_stream)
{
    DEBUG_LOGGING("Init interface with stream");
}

Interface::~Interface()
{
    DEBUG_LOGGING("Destroy interface");
    
    // Оповещение пользователя о работе с интерфейсом
    leave();

    delete stream;
}

void Interface::set(std::string path)
{
    DEBUG_LOGGING("Set stream path " << path);
    try
    {
        stream->set(path);
    }
    catch (InterfaceStreamException &ex)
    {
        throw InterfaceException(ex.res(), ex.msg());
    }
}

void Interface::show()
{
    DEBUG_LOGGING("Show menu");
    
    std::cout << std::endl << "Available commands:" << std::endl;
    for (CommandInformation item : CommandInfo)
    {
        std::cout <<  item.ID << ". " << item.description << std::endl;
    }
}

void Interface::invite()
{
    DEBUG_LOGGING("Invite input");
    
    std::cout << std::endl << "Enter command: ";
}

void Interface::leave()
{
    DEBUG_LOGGING("Leave interface");
    
    std::cout << std::endl << "Finish" << std::endl;
}

int Interface::read()
{
    DEBUG_LOGGING("Read interface command");
    
    try
    {
        int cur_command_ID = stream->read();
        bool is_valid = false;

        // Поиск считанной команды среди ранее известных для определения корректности
        for (CommandInformation item : CommandInfo)
        {
            if (cur_command_ID == item.ID)
            {
                is_valid = true;
                break;
            }
        }

        return (is_valid) ? cur_command_ID : INTERFACE_COMMAND_BREAK;
    }
    catch (InterfaceStreamException &ex)
    {
#ifdef DEBUG_MODE
        ERR_LOGGING(ex.res(), ex.msg());
#endif
        return INTERFACE_COMMAND_INVALID;
    }
}

template<typename T> T Interface::read_ex()
{
    DEBUG_LOGGING("Read typed data");

    try
    {
	return stream->read_ex<T>();
    }
    catch (InterfaceStreamException &ex)
    {
	throw InterfaceException(ex.res(), ex.msg());
    }
}

// Список возможных вариантов вызова
template int Interface::read_ex();
template double Interface::read_ex();
template std::string Interface::read_ex();
