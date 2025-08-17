/*!
    \file main.cpp
    \author Фамилия И.О.
    \date 1 Января 2025
    \brief Заголовочный файл-образец с описанием реализации головной функции запуска программы

    Примечание: Данный файл является шаблоном-образцом для редактирования
*/

#include "interface.h"
#include "resource.h"
#include "my_class.h"
#include <vector>

int main(int argc, [[maybe_unused]] char* argv[])
{
    DEBUG_LOGGING("Run DEBUG MODE");
    
    Interface* menu = new Interface();
    std::vector<MyClass> impl;
    
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
        try
        {
#ifndef SELFTEST
            menu->show();
            menu->invite();
#endif
        switch (menu->read())
        {
        case INTERFACE_COMMAND_1:
        {
            DEBUG_LOGGING("Run Command_1");
            impl.push_back(MyClass());
            continue;
        }
        case INTERFACE_COMMAND_2:
        {
            DEBUG_LOGGING("Run Command_2");
            if (!impl.empty()) impl.pop_back();
            continue;
        }
        case INTERFACE_COMMAND_3:
        {
            DEBUG_LOGGING("Run Command_3");

            // Считывание дополнительных данных
            int data_i = menu->read_ex<int>();
            double data_d = menu->read_ex<double>();
            std::string data_s = menu->read_ex<std::string>();

            // Вывод считанных данных
            LOGGING(data_i << "\t" << data_d << "\t" << data_s);

            // Пример работы с экземпляром собственного класса MyClass
            if (!impl.empty())
            {
                int counter = 1;
                impl.back().example_external_func(counter, &counter);
            }

            continue;
        }
        case INTERFACE_COMMAND_EXIT:
        {
            DEBUG_LOGGING("Run Command_Exit");
            break;
        }
        case INTERFACE_COMMAND_BREAK:
        case INTERFACE_COMMAND_INVALID:
            DEBUG_LOGGING("Run Invalid_Command");
            new InterfaceException(CODE_INCORRECT_CONFIGURATION, "Invalid command input");
        }
        }
        catch (InterfaceException& ex)
        {
#ifdef SELFTEST
            ERR_LOGGING(CODE_SELFTEST_ERROR, "Invalid input selftest");
            if (!impl.empty()) impl.clear();
            delete menu;
            return CODE_SELFTEST_ERROR;
#else
            ERR_LOGGING(ex.res(), ex.msg());
            continue;
#endif
        }
        catch (MyClassException& ex)
        {
#ifdef SELFTEST
            ERR_LOGGING(CODE_SELFTEST_ERROR, ex.msg());
            if (!impl.empty()) impl.clear();
            delete menu;
            return CODE_SELFTEST_ERROR;
#else
            ERR_LOGGING(ex.res(), ex.msg());
            continue;
#endif
        }

        break;
    };

    // Завершение работы 
    if (!impl.empty()) impl.clear();
    delete menu;

    return CODE_NO_ERROR;
}
