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
    if (this->in_stream != &std::cin)
        static_cast<std::ifstream*>(this->in_stream)->close();
    
    delete this->in_stream;
}

void InterfaceStream::set(std::string path)
{
    std::ifstream* stream = new std::ifstream();
    stream->open(path.c_str());
    if (!stream->is_open())
    {
        std::cerr << std::endl << "Failed to open " << path; // TODO Исключение
    }

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
    if (this->in_stream->fail()) {
        this->in_stream->clear(); // Сбрасываем состояние ошибки
        this->in_stream->ignore(); // Очищаем буфер
        std::cout << "Invalid input. Returning to menu.\n"; // TODO Исключение
    }
    this->in_stream->ignore(); // Убираем лишние символы
    return choice;
}
