/*!
    \file interface.cpp
    \author ������� �.�.
    \date 1 ������ 2025
    \brief ������������ ����-������� � ��������� ������� ����������

    ����������: ������ ���� �������� ��������-�������� ��� ��������������
*/

#include "interface.h"
#include "resource.h"

/*!
    ������ ��������� ���������������� ������ ��� �����
*/
CommandInformation CommandInfo[] =
{
    {INTERFACE_COMMAND_1,    "Command_1"},
    {INTERFACE_COMMAND_2,    "Command_2"},
    {INTERFACE_COMMAND_3,    "Command_3"},
    {INTERFACE_COMMAND_EXIT, "Exit"},
};


Interface::Interface() : stream(new InterfaceStream())
{

}

Interface::Interface(InterfaceStream* i_stream) : stream(i_stream)
{

}

Interface::~Interface()
{
    delete stream;
}

void Interface::set(std::string path)
{
    stream->set(path);

    std::cout << "SELFTEST mode activate";
}

void Interface::show()
{
    std::cout << std::endl << "Available commands:" << std::endl;
    for each (CommandInformation item in CommandInfo)
    {
        std::cout <<  item.ID << ". " << item.description << std::endl;
    }    
}

int Interface::read()
{
    try
    {
        int cur_command_ID = stream->read();
        bool is_valid = false;

        // ����� ��������� ������� ����� ����� ��������� ��� ����������� ������������
        for each (CommandInformation item in CommandInfo)
        {
            if (cur_command_ID == item.ID)
            {
                is_valid = true;
                break;
            }
        }

        return (is_valid) ? cur_command_ID : INTERFACE_COMMAND_BREAK;
    }
    catch (InterfaceStreamException ex)
    {
        // TODO �������� � CMakeLists.txt ������������ Debug � Release (���� -g ��� Debug)
//#ifdef DEBUG
        ERR_LOGGING(ex.res(), ex.msg());
//#endif
        return INTERFACE_COMMAND_INVALID;
    }
}
