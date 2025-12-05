/*!
    \file polygon.h
    \author Мусин А.Р.
    \date 1 Декабря 2025
    \brief Заголовочный файл с описанием класса Polygon
*/

#pragma once

#include <vector>
#include "point.h"
#include "segment.h"

/*!
Класс для работы с многоугольником на плоскости
*/
class Polygon {
private:
    std::vector<Point> vertices_;
    bool is_defined_;

public:
    /*!
    Конструктор по умолчанию (неопределённый многоугольник)
    */
    Polygon();

    /*!
    Конструктор с параметрами
    \param vertices Вектор вершин многоугольника (минимум 3 вершины)
    */
    Polygon(const std::vector<Point>& vertices);

    /*!
    Проверка, определён ли многоугольник
    \return true если многоугольник определён и содержит минимум 3 вершины
    */
    bool IsDef() const { return is_defined_; }

    /*!
    Получить количество вершин
    \return Количество вершин многоугольника
    */
    size_t Size() const { return vertices_.size(); }

    /*!
    Получить вершину по индексу
    \param index Индекс вершины
    \return Вершина с указанным индексом
    \throw std::out_of_range если индекс выходит за границы
    */
    Point GetVertex(size_t index) const;

    /*!
    Получить ребро (отрезок) по индексу
    \param index Индекс ребра
    \return Отрезок от вершины index к вершине (index+1)%size
    \throw std::out_of_range если индекс выходит за границы
    */
    Segment GetEdge(size_t index) const;

    /*!
    Вычислить площадь многоугольника
    \return Площадь многоугольника
    \throw std::runtime_error если многоугольник не определён
    */
    double Area() const;

    /*!
    Проверить, является ли многоугольник вырожденным (площадь ≈ 0)
    \return true если многоугольник вырожден
    */
    bool IsDegenerate() const;

    /*!
    Проверить, содержит ли многоугольник точку
    \param p Проверяемая точка
    \return true если точка находится внутри многоугольника или на его границе
    */
    bool Contains(const Point& p) const;

    /*!
    Проверить пересечение с другим многоугольником
    \param other Другой многоугольник
    \return true если многоугольники пересекаются
    \throw std::runtime_error если один из многоугольников не определён
    */
    bool Intersects(const Polygon& other) const;

    /*!
    Вычислить минимальное расстояние до другого многоугольника
    \param other Другой многоугольник
    \return Минимальное расстояние между многоугольниками (0 если пересекаются)
    \throw std::runtime_error если один из многоугольников вырожден
    */
    double Distance(const Polygon& other) const;
    int GetVertexCount() const;

};