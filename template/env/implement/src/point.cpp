/*!
    \file point.cpp
    \author Мусин А.Р.
    \date 1 Декабря 2025
    \brief Реализация методов класса Point
*/

#include "point.h"
#include <stdexcept>
#include <cmath>

Point::Point() : x_(0), y_(0), is_defined_(false) {}

Point::Point(double x, double y) : x_(x), y_(y), is_defined_(true) {}

double Point::GetX() const {
    if (!is_defined_) throw std::runtime_error("Point undefined");
    return x_;
}

double Point::GetY() const {
    if (!is_defined_) throw std::runtime_error("Point undefined");
    return y_;
}

Point Point::operator+(const Point& other) const {
    return Point(x_ + other.x_, y_ + other.y_);
}

Point Point::operator-(const Point& other) const {
    return Point(x_ - other.x_, y_ - other.y_);
}

Point Point::operator*(double scalar) const {
    return Point(x_ * scalar, y_ * scalar);
}

Point operator*(double scalar, const Point& p) {
    return p * scalar;
}

double Point::Dot(const Point& other) const {
    return x_ * other.x_ + y_ * other.y_;
}

double Point::Cross(const Point& other) const {
    return x_ * other.y_ - y_ * other.x_;
}

double Point::Length() const {
    return std::sqrt(x_ * x_ + y_ * y_);
}

double Point::Distance(const Point& other) const {
    double dx = x_ - other.x_;
    double dy = y_ - other.y_;
    return std::sqrt(dx * dx + dy * dy);
}