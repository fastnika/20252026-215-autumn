/*!
     \file my_class.cpp
     \author Фамилия И.О.
     \date 1 Января 2025
     \brief Заголовочный файл-образец с описанием реализуемых методов базового класса

     Примечание: Данный файл является шаблоном-образцом для редактирования
*/

#include "my_class.h"
#include "resource.h"

MyClass::MyClass() : example_internal_var(0), example_external_var(0)
{
    DEBUG_LOGGING("Init MyClass");
}

MyClass::~MyClass()
{
    DEBUG_LOGGING("Destroy MyClass");
}

void MyClass::example_internal_func(void)
{
    DEBUG_LOGGING("Run example_internal_func");
    
    // Пример реализации функции (демонстрация доступа к внутренним и внешним данным)
    
    example_internal_var++;
    example_external_var++;
    
    return;
}

int MyClass::example_external_func(int example_in_var, int* example_out_var)
{
    DEBUG_LOGGING("Run example_external_func");
    
    if (example_out_var == NULL)
        throw new MyClassException(CODE_INCORRECT_CALCULATION, "Invalid pointer for data");
    
    // Пример реализации функции (демонстрация возвращения внешнего аргумента и вычисленного значения)
    *example_out_var = example_internal_var;
    
    return (example_in_var + example_internal_var + example_external_var) % 2;
}
