/*!
    \file segment.cpp
    \author Мусин А.Р.
    \date 1 Декабря 2025
    \brief Реализация методов класса Segment
*/

#include "segment.h"
#include "polygon_utils.h"
#include <algorithm>

Segment::Segment() : p1_(), p2_(), is_defined_(false) {}

Segment::Segment(const Point& p1, const Point& p2)
    : p1_(p1), p2_(p2), is_defined_(p1.IsDef() && p2.IsDef()) {}

Point Segment::GetP1() const { return p1_; }

Point Segment::GetP2() const { return p2_; }

double Segment::Length() const { return p1_.Distance(p2_); }

Point Segment::Direction() const { return p2_ - p1_; }

double Segment::DistanceToPoint(const Point& p) const {
    Point ab = p2_ - p1_;
    Point ap = p - p1_;
    double ab2 = ab.Dot(ab);
    if (ab2 < PolygonUtils::EPSILON) return p1_.Distance(p);
    double t = ap.Dot(ab) / ab2;
    t = std::max(0.0, std::min(1.0, t));
    Point closest = p1_ + ab * t;
    return p.Distance(closest);
}

double Segment::DistanceToSegment(const Segment& other) const {
    Point d1 = p2_ - p1_;
    Point d2 = other.p2_ - other.p1_;
    Point r = p1_ - other.p1_;
    double a = d1.Dot(d1);
    double b = d1.Dot(d2);
    double c = d2.Dot(d2);
    double d_ = d1.Dot(r);
    double e = d2.Dot(r);
    double det = a * c - b * b;
    double s = 0.0, t = 0.0;

    if (a < PolygonUtils::EPSILON) return other.DistanceToPoint(p1_);
    if (c < PolygonUtils::EPSILON) return DistanceToPoint(other.p1_);

    if (det < PolygonUtils::EPSILON) {
        s = 0.0;
        if (b > PolygonUtils::EPSILON) {
            t = d_ / b;
        } else if (c > PolygonUtils::EPSILON) {
            t = e / c;
        }
        t = std::max(0.0, std::min(1.0, t));
    } else {
        s = (b * e - c * d_) / det;
        t = (a * e - b * d_) / det;
        s = std::max(0.0, std::min(1.0, s));
        t = std::max(0.0, std::min(1.0, t));
    }

    Point c1 = p1_ + d1 * s;
    Point c2 = other.p1_ + d2 * t;
    return c1.Distance(c2);
}

bool Segment::Intersects(const Segment& other) const {
    Point d1 = p2_ - p1_;
    Point d2 = other.p2_ - other.p1_;
    Point d3 = other.p1_ - p1_;
    double cross1 = d1.Cross(d2);

    if (std::abs(cross1) < PolygonUtils::EPSILON) {
        if (std::abs(d1.Cross(d3)) < PolygonUtils::EPSILON) {
            double t0 = d1.Dot(d3) / d1.Dot(d1);
            double t1 = t0 + d1.Dot(d2) / d1.Dot(d1);
            if (t0 > t1) std::swap(t0, t1);
            return (t1 >= -PolygonUtils::EPSILON && t0 <= 1.0 + PolygonUtils::EPSILON);
        }
        return false;
    }

    double t = d3.Cross(d2) / cross1;
    double u = d3.Cross(d1) / cross1;
    return (t >= -PolygonUtils::EPSILON && t <= 1.0 + PolygonUtils::EPSILON &&
            u >= -PolygonUtils::EPSILON && u <= 1.0 + PolygonUtils::EPSILON);
}