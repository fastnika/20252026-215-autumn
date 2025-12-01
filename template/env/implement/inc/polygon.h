/*!
\file polygon.h
\author Мусин А.Р.
\date 1 Декабря 2025
\brief Классы для работы с геометрическими объектами
*/

#ifndef POLYGON_DISTANCE_H
#define POLYGON_DISTANCE_H

#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

class Point {
private:
    double x_, y_;
    bool is_defined_;

public:
    Point();
    Point(double x, double y);
    bool IsDef() const { return is_defined_; }
    double GetX() const;
    double GetY() const;
    Point operator+(const Point& other) const;
    Point operator-(const Point& other) const;
    Point operator*(double scalar) const;
    double Dot(const Point& other) const;
    double Cross(const Point& other) const;
    double Length() const;
    double Distance(const Point& other) const;
    friend Point operator*(double scalar, const Point& p);
};

class Segment {
private:
    Point p1_, p2_;
    bool is_defined_;

public:
    Segment();
    Segment(const Point& p1, const Point& p2);
    bool IsDef() const { return is_defined_; }
    Point GetP1() const;
    Point GetP2() const;
    double Length() const;
    Point Direction() const;
    double DistanceToPoint(const Point& p) const;
    double DistanceToSegment(const Segment& other) const;
    bool Intersects(const Segment& other) const;
};

class Polygon {
private:
    std::vector<Point> vertices_;
    bool is_defined_;

public:
    Polygon();
    Polygon(const std::vector<Point>& vertices);
    bool IsDef() const { return is_defined_; }
    size_t Size() const { return vertices_.size(); }
    Point GetVertex(size_t index) const;
    Segment GetEdge(size_t index) const;
    double Area() const;
    bool IsDegenerate() const;
    bool Contains(const Point& p) const;
    bool Intersects(const Polygon& other) const;
    double Distance(const Polygon& other) const;
};

namespace PolygonUtils {
    extern const double EPSILON;
    extern const double INF;
    bool AreCollinear(const Point& p1, const Point& p2, const Point& p3, double eps = 1e-9);
    bool IsPointOnSegment(const Point& p, const Segment& seg, double eps = 1e-9);
}

#endif