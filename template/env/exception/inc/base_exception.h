/*!
     \file base_exception.h
     \author Фамилия И.О.
     \date 1 Января 2025
     \brief Заголовочный файл-образец с описанием прототипов реализуемых функций

     Примечание: Данный файл является шаблоном-образцом для редактирования
*/

#include <exception>
#include <string>

class task_base_exception : public std::exception
{
protected:
    struct
    {
	int _code = -1;
	std::string _msg = "";
    } error;

public:
    base_exception();
    base_exception(base_exception* other);
    base_exception(std::string msg);
    base_exception(int code);
    base_exception(int code, std::string msg);

    ~base_exception();

    int res();
    std::string msg();
}
