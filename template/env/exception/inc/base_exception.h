/*!
\file base_exception.h
\author Фамилия И.О.
\date 1 Января 2025
\brief Класс для обработки исключений
*/

#pragma once

#include <string>
#include <exception>

/*!
Класс описания исключения
*/
class BaseException : public std::exception
{
protected:
    /*! Код ошибки */
    int code = -1;
    /*! Поясняющее сообщение ошибки */
    std::string message = "";

public:
    /*! Конструктор класса исключения */
    BaseException();
    /*! Конструктор с инициализацией другим объектом */
    BaseException(BaseException* other);
    /*! Конструктор с сообщением */
    BaseException(std::string msg);
    /*! Конструктор с кодом */
    BaseException(int code);
    /*! Конструктор с кодом и сообщением */
    BaseException(int code, std::string msg);
    /*! Деструктор */
    ~BaseException();
    /*! Возврат кода ошибки */
    int res();
    /*! Возврат сообщения об ошибке */
    std::string msg();
};