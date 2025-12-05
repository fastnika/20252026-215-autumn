/*!
    \file resource.h
    \author Мусин А.Р
    \date 1 декабря 2025
    \brief Ресурсы: коды ошибок и макросы логирования
*/

#pragma once

#include <iostream>
#include <iomanip>

#define ERR_LOGGING(code,msg) \
    std::cerr << std::endl << "\033[41m" << std::endl << "Error:\t" << msg << std::endl; \
    std::cerr << "Code:\t" << std::hex << std::showbase << std::setw(8) << std::setfill('0') << code << std::endl; \
    std::cerr << "File:\t" << __FILE__ << std::endl; \
    std::cerr << "Line:\t" << std::dec << __LINE__ << "\033[0m" << std::endl;

#ifdef DEBUG_MODE
#define DEBUG_LOGGING(msg) \
    std::cout << "\033[36m" << __FILE__ << "\033[0m : \033[33m" << __LINE__ << "\033[0m\t\033[32m" << msg << "\033[0m" << std::endl
#else
#define DEBUG_LOGGING(msg)
#endif

#define LOGGING(msg) std::cout << msg << std::endl

#define CODE_NO_ERROR 0x0
#define CODE_SELFTEST_ERROR 0x1
#define CODE_NO_INPUT_FILE 0x1001
#define CODE_NO_OUTPUT_FILE 0x1002
#define CODE_INCORRECT_ADV_DATA 0x1003
#define CODE_INCORRECT_INPUT_FILE 0x1004
#define CODE_INCORRECT_CONFIGURATION 0x1005
#define CODE_INCORRECT_CALCULATION 0x1006
#define CODE_INCORRECT_MEM_ALLOCATION 0x1007