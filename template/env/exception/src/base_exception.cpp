/*!
     \file base_exception.cpp
     \author Фамилия И.О.
     \date 1 Января 2025
     \brief Заголовочный файл-образец с описанием реализуемых методов класса для обработки исключения

     Примечание: Данный файл является шаблоном-образцом для редактирования
*/

#include "base_exception.h"

BaseException::BaseException()
{

}

BaseException::BaseException(BaseException* other)
{
    this->code = other->code;
    this->message = other->message;
}

BaseException::BaseException(std::string msg)
{
    this->code = -1;
    this->message = msg;
}

BaseException::BaseException(int code)
{
    this->code = code;
    this->message = "";
}

BaseException::BaseException(int code, std::string msg)
{
    this->code = code;
    this->message = msg;
}

BaseException::~BaseException()
{

}

int BaseException::res()
{
    return this->code;
}

std::string BaseException::msg()
{
    return this->message;
}
