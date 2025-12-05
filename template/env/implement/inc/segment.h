/*!
    \file segment.h
    \author Мусин А.Р.
    \date 1 Декабря 2025
    \brief Заголовочный файл с описанием класса Segment
*/

#pragma once

#include "point.h"

/*!
Класс для работы с отрезком (сегментом) на плоскости
*/
class Segment {
private:
    Point p1_;
    Point p2_;
    bool is_defined_;

public:
    /*!
    Конструктор по умолчанию (неопределённый отрезок)
    */
    Segment();

    /*!
    Конструктор с параметрами
    \param p1 Начальная точка отрезка
    \param p2 Конечная точка отрезка
    */
    Segment(const Point& p1, const Point& p2);

    /*!
    Проверка, определён ли отрезок
    \return true если отрезок определён
    */
    bool IsDef() const { return is_defined_; }

    /*!
    Получить начальную точку
    \return Начальная точка отрезка
    */
    Point GetP1() const;

    /*!
    Получить конечную точку
    \return Конечная точка отрезка
    */
    Point GetP2() const;

    /*!
    Вычислить длину отрезка
    \return Длина отрезка
    */
    double Length() const;

    /*!
    Получить направляющий вектор отрезка
    \return Вектор от p1 к p2
    */
    Point Direction() const;

    /*!
    Вычислить расстояние от отрезка до точки
    \param p Точка
    \return Минимальное расстояние от отрезка до точки
    */
    double DistanceToPoint(const Point& p) const;

    /*!
    Вычислить расстояние между двумя отрезками
    \param other Второй отрезок
    \return Минимальное расстояние между отрезками
    */
    double DistanceToSegment(const Segment& other) const;

    /*!
    Проверить пересечение двух отрезков
    \param other Второй отрезок
    \return true если отрезки пересекаются
    */
    bool Intersects(const Segment& other) const;
};