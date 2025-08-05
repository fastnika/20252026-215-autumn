/*!
    \file interface.h
    \author Фамилия И.О.
    \date 1 Января 2025
    \brief Заголовочный файл-образец с описанием интерфейса

    Примечание: Данный файл является шаблоном-образцом для редактирования
*/

// Указание директивой препроцессора однократного подключения
#pragma once

#include "interface_stream.h"
#include "base_exception.h"

/*!
    \defgroup INTERFACE_GROUP Группа идентификаторов Интерфейса
    @{
*/

/*!
    \brief Команда интерфейса: неизвестная команда
*/
#define INTERFACE_COMMAND_BREAK     0
/*!
    \brief Команда интерфейса: недопустимая команда
*/
#define INTERFACE_COMMAND_INVALID   5
/*!
    \brief Команда интерфейса: команда 1
*/
#define INTERFACE_COMMAND_1         1
/*!
    \brief Команда интерфейса: команда 2
*/
#define INTERFACE_COMMAND_2         2
/*!
    \brief Команда интерфейса: команда 3
*/
#define INTERFACE_COMMAND_3         3
/*!
    \brief Команда интерфейса: команда выхода
*/
#define INTERFACE_COMMAND_EXIT      4

/*! @} */

/*!
    Описание структуры команды
*/
typedef struct 
{
    /*!
        Идентификатор команды
    */
    int ID;
    /*!
        Расшифровка команды
    */
    std::string description;

} CommandInformation;

/*!
    Класс для работы с интерфейсом
*/
class Interface
{
private:

    /*!
        Поток пользовательских команд
    */
    InterfaceStream* stream = nullptr;
    
    /*!
        Признак самотестирования реализации
    */
    bool is_self = false;

public:

    /*!
        Конструктор класса интерфейса
    */
    Interface();
    
    /*!
        Конструктор класса интерфейса с инициализацией входного потока пользовательских команд
        \param[in] i_stream Искомый входной поток 
    */
    Interface(InterfaceStream* i_stream);
    
    /*!
        Деструктор класса интерфейса
    */
    ~Interface();
    
    /*!
        Установка источника для считывания пользовательских команд интерфейса
        \param[in] path Путь расположения источника
    */
    void set(std::string path);
    
    /*!
        Распечатка допустимых команд интерфейса
    */
    void show();
    
    /*!
        Чтение очередной команды из потока
        \return Искомая команда, введенная пользователем
    */
    int read();
};

/*!
    Класс обработки исключений при работе с интерфейсом
*/
class InterfaceException : public BaseException
{
    using BaseException::BaseException;
};
