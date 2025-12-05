/*!
    \file polygon_utils.cpp
    \author Мусин А.Р.
    \date 1 Декабря 2025
    \brief Реализация вспомогательных функций
*/

#include "polygon_utils.h"
#include "segment.h"
#include <cmath>
#include <limits>

namespace PolygonUtils {
    const double EPSILON = 1e-9;
    const double INF = std::numeric_limits<double>::infinity();

    bool AreCollinear(const Point& p1, const Point& p2, const Point& p3, double eps) {
        Point v1 = p2 - p1;
        Point v2 = p3 - p1;
        return std::abs(v1.Cross(v2)) < eps;
    }

    bool IsPointOnSegment(const Point& p, const Segment& seg, double eps) {
        Point p1 = seg.GetP1();
        Point p2 = seg.GetP2();
        if (!AreCollinear(p1, p2, p, eps)) return false;
        double min_x = std::min(p1.GetX(), p2.GetX()) - eps;
        double max_x = std::max(p1.GetX(), p2.GetX()) + eps;
        double min_y = std::min(p1.GetY(), p2.GetY()) - eps;
        double max_y = std::max(p1.GetY(), p2.GetY()) + eps;
        return (p.GetX() >= min_x && p.GetX() <= max_x &&
                p.GetY() >= min_y && p.GetY() <= max_y);
    }
}