/*!
    \file polygon_utils.h
    \author Мусин А.Р.
    \date 1 Декабря 2025
    \brief Заголовочный файл с вспомогательными функциями и константами
*/

#pragma once

#include <limits>
#include "point.h"

class Segment;  // Forward declaration

/*!
Пространство имён с вспомогательными функциями и константами для работы с геометрией
*/
namespace PolygonUtils {
    /*!
    Константа для сравнения чисел с плавающей запятой
    */
    extern const double EPSILON;

    /*!
    Константа бесконечности
    */
    extern const double INF;

    /*!
    Проверить, являются ли три точки коллинеарными (лежат на одной прямой)
    \param p1 Первая точка
    \param p2 Вторая точка
    \param p3 Третья точка
    \param eps Допуск для сравнения
    \return true если точки коллинеарны
    */
    bool AreCollinear(const Point& p1, const Point& p2, const Point& p3, double eps = 1e-9);

    /*!
    Проверить, лежит ли точка на отрезке
    \param p Проверяемая точка
    \param seg Отрезок
    \param eps Допуск для сравнения
    \return true если точка лежит на отрезке
    */
    bool IsPointOnSegment(const Point& p, const Segment& seg, double eps = 1e-9);
}
