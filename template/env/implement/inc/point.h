/*!
    \file point.h
    \author Мусин А.Р.
    \date 1 Декабря 2025
    \brief Заголовочный файл с описанием класса Point
*/

#pragma once

#include <cmath>

/*!
Класс для работы с двумерной точкой
*/
class Point {
private:
    double x_;
    double y_;
    bool is_defined_;

public:
    /*!
    Конструктор по умолчанию (неопределённая точка)
    */
    Point();

    /*!
    Конструктор с параметрами
    \param x Координата по оси X
    \param y Координата по оси Y
    */
    Point(double x, double y);

    /*!
    Проверка, определена ли точка
    \return true если точка определена
    */
    bool IsDef() const { return is_defined_; }

    /*!
    Получить координату X
    \return Координата X
    \throw std::runtime_error если точка не определена
    */
    double GetX() const;

    /*!
    Получить координату Y
    \return Координата Y
    \throw std::runtime_error если точка не определена
    */
    double GetY() const;

    /*!
    Сложение двух точек (как векторов)
    \param other Вторая точка
    \return Новая точка - сумма координат
    */
    Point operator+(const Point& other) const;

    /*!
    Вычитание двух точек (как векторов)
    \param other Вторая точка
    \return Новая точка - разность координат
    */
    Point operator-(const Point& other) const;

    /*!
    Умножение точки на скаляр
    \param scalar Скалярный множитель
    \return Новая точка с умноженными координатами
    */
    Point operator*(double scalar) const;

    /*!
    Скалярное произведение двух векторов
    \param other Вторая точка
    \return Результат скалярного произведения
    */
    double Dot(const Point& other) const;

    /*!
    Векторное произведение (в 2D возвращает z-компоненту)
    \param other Вторая точка
    \return Z-компонента векторного произведения
    */
    double Cross(const Point& other) const;

    /*!
    Длина вектора (расстояние от начала координат)
    \return Длина вектора
    */
    double Length() const;

    /*!
    Расстояние между двумя точками
    \param other Вторая точка
    \return Евклидово расстояние
    */
    double Distance(const Point& other) const;

    /*!
    Умножение скаляра на точку (friend функция)
    \param scalar Скалярный множитель
    \param p Точка
    \return Новая точка с умноженными координатами
    */
    friend Point operator*(double scalar, const Point& p);
};