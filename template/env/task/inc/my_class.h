/*!
     \file my_class.h
     \author Фамилия И.О.
     \date 1 Января 2025
     \brief Заголовочный файл-образец с описанием класса реализуемой задачи

     Примечание: Данный файл является шаблоном-образцом для редактирования
*/

// Указание директивой препроцессора однократного подключения
#pragma once

#include "base_exception.h"

/*!
    Класс описания реалиазации
*/
class MyClass
{
private:
    /*!
        Пример ввода переменной внутренней области видимости
    */
    int example_internal_var = 0;

    /*!
        Пример метода реализации класса внешней области видимости
    */
    void example_internal_func(void);
public:

    /*!
        Конструктор класса реализации
    */
    MyClass();
    
    /*!
        Деструктор класса реализации
    */
    ~MyClass();

    /*!
        Пример ввода переменной внешней области видимости
    */
    int example_external_var = 0;

    /*!
        Пример метода реализации класса внешней области видимости
        \param[in] example_in_var Пример входного аргумента функции
        \param[out] example_out_var Пример выходного аргумента функции
        \return Искомое вычисленное значение функции 
    */
    int example_external_func(int example_in_var, int* example_out_var);
};

class MyClassException : public BaseException
{
    using BaseException::BaseException;
};
