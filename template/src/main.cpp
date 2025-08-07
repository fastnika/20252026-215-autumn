/*!
    \file main.cpp
    \author Фамилия И.О.
    \date 1 Января 2025
    \brief Заголовочный файл-образец с описанием реализации головной функции запуска программы

    Примечание: Данный файл является шаблоном-образцом для редактирования
*/

#include "interface.h"
#include "resource.h"

int main(int argc, [[maybe_unused]] char* argv[])
{
    DEBUG_LOGGING("Run DEBUG MODE");
    
    Interface* menu = new Interface();

    //
    // Инициализация интерфейса
    //
#ifdef SELFTEST
    DEBUG_LOGGING("Run SELFTEST MODE");
    
    if (argc != 2)
    {
        ERR_LOGGING(CODE_SELFTEST_ERROR, "SELFTEST invalid input");
        delete menu;
        return CODE_SELFTEST_ERROR;
    }

    try
    {
        menu->set(argv[1]);
    }
    catch (InterfaceException& ex)
    {
        ERR_LOGGING(ex.res(), ex.msg());
        delete menu;
        return ex.res();
    }
#else
    if (argc > 2)
    {
        ERR_LOGGING(CODE_INCORRECT_CONFIGURATION, "UI invalid input");
        delete menu;
        return CODE_INCORRECT_CONFIGURATION;
    }
#endif

    //
    // Работа с интерфейсом
    //
    while (true)
    {
#ifndef SELFTEST
        menu->show();
        menu->invite();
#endif
        switch (menu->read())
        {
        case INTERFACE_COMMAND_1:
            DEBUG_LOGGING("Run Command_1");
            continue;
        case INTERFACE_COMMAND_2:
            DEBUG_LOGGING("Run Command_2");
            continue;
        case INTERFACE_COMMAND_3:
            DEBUG_LOGGING("Run Command_3");
            // TODO : Считывание дополнительных данных, например - вещественных
	        continue;
        case INTERFACE_COMMAND_EXIT:
            DEBUG_LOGGING("Run Command_Exit");
            break;
        case INTERFACE_COMMAND_BREAK:
        case INTERFACE_COMMAND_INVALID:
#ifdef SELFTEST
            ERR_LOGGING(CODE_SELFTEST_ERROR, "Invalid input selftest");
            delete menu;
            return CODE_SELFTEST_ERROR;
#else
            DEBUG_LOGGING("Invalid input");
            continue;
#endif
        }

        break;
    };

    delete menu;

    return CODE_NO_ERROR;
}
