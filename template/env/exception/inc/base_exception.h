/*!
     \file base_exception.h
     \author Фамилия И.О.
     \date 1 Января 2025
     \brief Заголовочный файл-образец с описанием прототипов реализуемых функций

     Примечание: Данный файл является шаблоном-образцом для редактирования
*/

#include <exception>
#include <string>

#pragma once

class BaseException : public std::exception
{
protected:
    struct
    {
	int _code = -1;
	std::string _msg = "";
    } error;

public:
    BaseException();
    BaseException(BaseException* other);
    BaseException(std::string msg);
    BaseException(int code);
    BaseException(int code, std::string msg);

    ~BaseException();

    int res();
    std::string msg();
}
