/*!
     \file my_class.cpp
     \author Фамилия И.О.
     \date 1 Января 2025
     \brief Заголовочный файл-образец с описанием реализуемых методов класса

     Данный файл содержит в себе описание прототипов реализуемых функций,
     которые демонстрируют решение следующих задач:
     - Задача 1: Здесь приводится описание Задачи 1
     - Задача 2: Здесь приводится описание Задачи 2

     Примечание: Данный файл является шаблоном-образцом для редактирования
*/

#include "my_class.h"
#include "resource.h"

MyClass::MyClass() : example_internal_var(0), example_external_var(0)
{

}

MyClass::~MyClass()
{

}

void MyClass::example_internal_func(void)
{
    // Пример реализации функции (демонстрация доступа к внутренним и внешним данным)
    
    example_internal_var++;
    example_external_var++;
    
    return;
}

int MyClass::example_external_func(int example_in_var, int* example_out_var)
{
    if (example_out_var == NULL)
        throw new MyClassException(CODE_INCORRECT_CALCULATION, "Invalid pointer for data");
    
    // Пример реализации функции (демонстрация возвращения внешнего аргумента и вычисленного значения)
    *example_out_var = example_internal_var;
    
    return (example_in_var + example_internal_var + example_external_var) % 2;
}
