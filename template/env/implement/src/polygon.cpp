/*!
\file polygon.cpp
\author Мусин А.Р
\date 1 Декабря 2025
\brief Реализация методов классов геометрических объектов
*/

#include "polygon.h"
#include <exception>
#include <stdexcept>

namespace PolygonUtils {
    const double EPSILON = 1e-9;
    const double INF = std::numeric_limits<double>::infinity();
}

// ============================================================================
// POINT
// ============================================================================

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

// ============================================================================
// SEGMENT
// ============================================================================

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

Polygon::Polygon() : is_defined_(false) {}
Polygon::Polygon(const std::vector<Point>& vertices)
    : vertices_(vertices), is_defined_(true) {
    if (vertices_.size() < 3) is_defined_ = false;
    for (const auto& v : vertices_) {
        if (!v.IsDef()) {
            is_defined_ = false;
            break;
        }
    }
}

Point Polygon::GetVertex(size_t index) const {
    if (index >= vertices_.size()) throw std::out_of_range("Vertex index out of range");
    return vertices_[index];
}

Segment Polygon::GetEdge(size_t index) const {
    if (index >= vertices_.size()) throw std::out_of_range("Edge index out of range");
    size_t next_index = (index + 1) % vertices_.size();
    return Segment(vertices_[index], vertices_[next_index]);
}

double Polygon::Area() const {
    if (!is_defined_) throw std::runtime_error("Polygon is not defined");
    double area = 0.0;
    size_t n = vertices_.size();
    for (size_t i = 0; i < n; ++i) {
        size_t j = (i + 1) % n;
        area += vertices_[i].GetX() * vertices_[j].GetY() -
                vertices_[j].GetX() * vertices_[i].GetY();
    }
    return std::abs(area) / 2.0;
}

bool Polygon::IsDegenerate() const {
    return Area() < PolygonUtils::EPSILON;
}bool Polygon::Contains(const Point& p) const {
    for (size_t i = 0; i < vertices_.size(); ++i) {
        if (PolygonUtils::IsPointOnSegment(p, GetEdge(i), PolygonUtils::EPSILON)) {
            return true;
        }
    }

    int count = 0;
    size_t n = vertices_.size();
    for (size_t i = 0; i < n; ++i) {
        size_t j = (i + 1) % n;
        Point v1 = vertices_[i];
        Point v2 = vertices_[j];
        double y1 = v1.GetY();
        double y2 = v2.GetY();
        double py = p.GetY();

        if (std::abs(y2 - y1) < PolygonUtils::EPSILON) continue;
        if ((y1 > py) != (y2 > py)) {
            double x_intersect = (v2.GetX() - v1.GetX()) * (py - y1) / (y2 - y1) + v1.GetX();
            if (p.GetX() < x_intersect - PolygonUtils::EPSILON) {
                count++;
            }
        }
    }

    return (count % 2) == 1;
}

bool Polygon::Intersects(const Polygon& other) const {
    if (!is_defined_ || !other.is_defined_)
        throw std::runtime_error("Polygon not defined");

    for (size_t i = 0; i < vertices_.size(); ++i) {
        Segment e1 = GetEdge(i);
        for (size_t j = 0; j < other.vertices_.size(); ++j) {
            Segment e2 = other.GetEdge(j);
            if (e1.Intersects(e2)) return true;
        }
    }

    for (size_t i = 0; i < other.vertices_.size(); ++i) {
        if (Contains(other.vertices_[i])) return true;
    }

    for (size_t i = 0; i < vertices_.size(); ++i) {
        if (other.Contains(vertices_[i])) return true;
    }

    return false;
}

double Polygon::Distance(const Polygon& other) const {
    if (IsDegenerate() || other.IsDegenerate())
        throw std::runtime_error("Cannot compute distance for degenerate polygons");

    if (Intersects(other)) return 0.0;

    double min_dist = PolygonUtils::INF;

    for (size_t i = 0; i < vertices_.size(); ++i) {
        Segment e1 = GetEdge(i);
        for (size_t j = 0; j < other.vertices_.size(); ++j) {
            Segment e2 = other.GetEdge(j);
            min_dist = std::min(min_dist, e1.DistanceToSegment(e2));
        }
    }

    return min_dist;
}

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

bool PolygonUtils::AreCollinear(const Point& p1, const Point& p2, const Point& p3, double eps) {
    Point v1 = p2 - p1;
    Point v2 = p3 - p1;
    return std::abs(v1.Cross(v2)) < eps;
}

bool PolygonUtils::IsPointOnSegment(const Point& p, const Segment& seg, double eps) {
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