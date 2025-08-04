/*!
     \file interface_stream.cpp
     \author Фамилия И.О.
     \date 1 Января 2025
     \brief Заголовочный файл-образец с описанием реализуемых методов класса для работы с потоком команд

     Примечание: Данный файл является шаблоном-образцом для редактирования
*/

#include "interface_stream.h"
#include "resource.h"

InterfaceStream::InterfaceStream() : in_stream(&std::cin)
{

}

InterfaceStream::InterfaceStream(std::istream* stream)
{
    set(stream);
}

InterfaceStream::InterfaceStream(std::string path)
{
    set(path);
}

InterfaceStream::~InterfaceStream()
{
    clear();
}

void InterfaceStream::clear()
{
    if (this->in_stream != &std::cin)
    {
        static_cast<std::ifstream*>(this->in_stream)->close();
        if (self_stream_init) delete this->in_stream; // TODO delete для std::cin вроде бы не нужен
    }

    this->in_stream = nullptr;
}

void InterfaceStream::set(std::string path)
{
    // Формирование нового stream
    std::ifstream* stream = new std::ifstream();
    stream->open(path.c_str());
    if (!stream->is_open())
    {
        delete stream;
        throw new InterfaceStreamException(CODE_INCORRECT_INPUT_FILE, "No input file");
    }
    
    // Предварительная очистка 
    clear();

    // Установка нового stream
    self_stream_init = true;
    set(stream);
}

void InterfaceStream::set(std::istream* stream)
{
    this->in_stream = stream;
}

int InterfaceStream::read()
{
    int choice;
    *(this->in_stream) >> choice;
    if (this->in_stream->fail())
    {
        this->in_stream->clear(); // Сброс состояния ошибки
        this->in_stream->ignore(); // Очищение буфера
        throw new InterfaceStreamException(CODE_INCORRECT_CONFIGURATION, "Invalid input");
    }
    this->in_stream->ignore(); // Убирание лишних символов
    
    return choice;
}
