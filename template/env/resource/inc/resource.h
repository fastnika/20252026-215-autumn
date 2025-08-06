/*!
    \file resource.h
    \author Фамилия И.О.
    \date 1 Января 2025
    \brief Заголовочный файл-образец с описание кодов ошибок и соответствующего инструментария для логгирования

    Примечание: Данный файл является шаблоном-образцом для редактирования
*/

// Указание директивой препроцессора однократного подключения
#pragma once

#include <iomanip>
#include <iostream>

/*!
    Макро-функция обработчик форматированного логгирования ошибок
    \param[in] code Код ошибки
    \param[in] msg Пояснение ошибки
*/
#define ERR_LOGGING(code,msg) \
    std::cerr << std::endl << std::endl << "Error:\t" << msg << std::endl; \
    std::cerr << "Code:\t" << std::hex << std::showbase << std::setw(8) << std::setfill('0') << code << std::endl; \
    std::cerr << "File:\t" << __FILE__ << std::endl; \
    std::cerr << "Line:\t" << __LINE__ << std::endl;

/*!
    Макро-функция обработчик отладочного логгирования (включена только в режиме DEBUG)
    \param[in] msg Информационное сообщение
*/
#ifdef DEBUG_MODE
#define DEBUG_LOGGING(msg) std::cout << __FILE__ << ":" << __LINE__ << "\t" << msg << std::endl
#else
#define DEBUG_LOGGING(msg)
#endif

/*!
    \defgroup TASK_GROUP Группа идентификаторов Задачи
    @{
*/

/*!
    \brief Код ошибки: Успешное завершение работы программы
*/
#define CODE_NO_ERROR			0x0
/*!
    \brief Код ошибки: Самотестирование завершено некорректно
*/
#define CODE_SELFTEST_ERROR		0x1
/*!
    \brief Код ошибки: Отсутствует входной файл для обработки (или задан пользователем некорректно)
*/
#define CODE_NO_INPUT_FILE		0x1001
/*!
    \brief Код ошибки: Отсутствует выходной файл для обработки (или задан пользователем некорректно)
*/
#define CODE_NO_OUTPUT_FILE		0x1002
/*!
    \brief Код ошибки: Ошибочные дополнительные входные данные (запрашиваемые в дополнение ко входному файлу)
*/
#define CODE_INCORRECT_ADV_DATA		0x1003
/*!
    \brief Код ошибки: Ошибочные входные данные файла для обработки (файл пуст или данные некорректны)
*/
#define CODE_INCORRECT_INPUT_FILE	0x1004
/*!
    \brief Код ошибки: Неприменимые данные для обработки (по входящим данным не может быть проведено вычисление)
*/
#define CODE_INCORRECT_CONFIGURATION	0x1005
/*!
    \brief Код ошибки: Ошибка при проведении  вычислений (в процессе выполнения)
*/
#define CODE_INCORRECT_CALCULATION	0x1006
/*!
    \brief Код ошибки: Ошибка при проведении выделения памяти
*/
#define CODE_INCORRECT_MEM_ALLOCATION	0x1007

/*! @} */
