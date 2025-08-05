/*!
    \file main.cpp
    \author Фамилия И.О.
    \date 1 Января 2025
    \brief Заголовочный файл-образец с описанием реализации головной функции запуска программы

    Примечание: Данный файл является шаблоном-образцом для редактирования
*/

#include "interface.h"
#include "resource.h"

int main(int argc, char* argv[])
{
    Interface* menu = new Interface();
    
    //
    // Инициализация интерфейса
    //
#ifdef SELFTEST
    if (argc != 2)
    {
        std::cerr << "SELFTEST: Invalid input";
        return CODE_SELFTEST_ERROR;
    }

    menu->set(argv[1]);
#else
    if (argc > 2)
    {
        std::cerr << "UI: Invalid input";
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
        std::cout << std::endl << "Enter command: ";
#endif
        switch (menu->read())
        {
        case INTERFACE_COMMAND_1:
            std::cout << std::endl << "Run Command_1";
            continue;
        case INTERFACE_COMMAND_2:
            std::cout << std::endl << "Run Command_2";
            continue;
        case INTERFACE_COMMAND_3:
            std::cout << std::endl << "Run Command_3";
            // TODO : Считывание дополнительных данных, например - вещественных
	        continue;
        case INTERFACE_COMMAND_EXIT:
            std::cout << std::endl << "Go away!";
            break;
        case INTERFACE_COMMAND_BREAK:
        case INTERFACE_COMMAND_INVALID:
#ifdef SELFTEST
            std::cout << std::endl << "Invalid input selftest";
            delete menu;
            return CODE_SELFTEST_ERROR;
#else
            std::cout << std::endl << "Invalid input";
            continue;
#endif
        }

        break;
    };

    std::cout << std::endl << "Finish" << std::endl;

    delete menu;

    return CODE_NO_ERROR;
}
