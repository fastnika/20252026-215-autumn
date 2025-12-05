/*!
    \file polygon.cpp
    \author Мусин А.Р.
    \date 1 Декабря 2025
    \brief Реализация методов класса Polygon
*/

#include "polygon.h"
#include "polygon_utils.h"
#include <algorithm>
#include <stdexcept>

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
}

bool Polygon::Contains(const Point& p) const {
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

int Polygon::GetVertexCount() const {
    return vertices_.size();
}
