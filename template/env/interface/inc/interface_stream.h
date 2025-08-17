/*!
     \file interface_stream.h
     \author Фамилия И.О.
     \date 1 Января 2025
     \brief Заголовочный файл-образец с описанием класса для работы с потоком команд

     Примечание: Данный файл является шаблоном-образцом для редактирования
*/

// Указание директивой препроцессора однократного подключения
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "base_exception.h"

/*!
    Класс для работы с потоком интерфейса
*/
class InterfaceStream
{
private:

    /*!
        Входной поток команд интерфейса
    */
    std::istream* in_stream = nullptr;

    /*!
        Признак инициализации потока команд интерфейса внутри класса
    */
    bool self_stream_init = false;

    /*!
        Очистака потока команд интерфейса
    */
    void clear();

public:

    /*!
        Конструктор класса для работы с потоком интерфейса
    */
    InterfaceStream();

    /*!
        Конструктор класса для работы с указанным потоком интерфейса
        \param[in] stream Искомый поток команд
    */
    InterfaceStream(std::istream* stream);
    
    /*!
        Конструктор класса для работы с указанным потоком интерфейса
        \param[in] stream Расположение файла потока команд
    */
    InterfaceStream(std::string path);
    
    /*!
        Деструктор класса для работы с потоком интерфейса
    */
    ~InterfaceStream();
    
    /*!
        Выставление нового потока команд
        \param[in] stream Искомый поток команд
    */
    void set(std::istream* stream);
    
    /*!
        Выставление нового потока команд
        \param[in] stream Расположение файла потока команд
    */
    void set(std::string path);
    
    /*!
        Чтение очередной команды из потока команд
    */
    int read();

    /*!
        Чтение типизированных данных из потока
    */
    template<typename T> T read_ex();
};

/*!
    Класс обработки исключений при работе с потоком интерфейса
*/
class InterfaceStreamException : public BaseException
{
    using BaseException::BaseException;
};
