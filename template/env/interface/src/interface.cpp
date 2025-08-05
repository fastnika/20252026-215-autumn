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
    std::cout << std::endl << "Available commands:" << std::endl;
    for each (CommandInformation item in CommandInfo)
    {
        std::cout <<  item.ID << ". " << item.description << std::endl;
    }    
}

int Interface::read()
{
    try
    {
        int cur_command_ID = stream->read();
        bool is_valid = false;

        // Поиск считанной команды среди ранее известных для определения корректности
        for each (CommandInformation item in CommandInfo)
        {
            if (cur_command_ID == item.ID)
            {
                is_valid = true;
                break;
            }
        }

        return (is_valid) ? cur_command_ID : INTERFACE_COMMAND_BREAK;
    }
    catch (InterfaceStreamException ex)
    {
        // TODO Добавить в CMakeLists.txt конфигурацию Debug и Release (флаг -g для Debug)
//#ifdef DEBUG
        ERR_LOGGING(ex.res(), ex.msg());
//#endif
        return INTERFACE_COMMAND_INVALID;
    }
}
