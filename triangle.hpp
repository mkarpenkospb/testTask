#pragma once

#include <utility>
#include <cmath>
#include <algorithm>
#include <vector>

namespace figures {

    bool dblEq(double d1, double d2, double delta) {
        return fabs(d1 - d2) < delta;
    }

    class point {
    public:
        explicit point(const double &x, const double &y) : x(x), y(y) {};
        point() : x(0), y(0){};
        bool operator==(const point&);
        bool operator!=(const point&);
        double x;
        double y;
    };

    bool point::operator==(const point &other) {
        return dblEq(x, other.x, 0.00001) && dblEq(y, other.y, 0.00001);
    }

    bool point::operator!=(const point &other) {
        return !(*this == other);
    }

    // компаратор для сортировки точек по первой координате
    auto compP = [] (const point &p1, const point &p2) {
        return p1.x < p2.x;
    };

    double dist(const point &p1, const point &p2) {
        return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    }


    class line {
    public:
        explicit line(const point &p1, const point &p2);
        bool operator==(const line&);
        bool operator!=(const line&);
        line() = default;
        point p1{};
        point p2{};
        double length = 0;
    };

    line::line(const point &p1, const point &p2) {
        if (p1.x < p2.x) {
            this->p1 = p1;
            this->p2 = p2;
        } else {
            this->p2 = p1;
            this->p1 = p2;
        }
        length = dist(this->p1, this->p2);
    }

    bool line::operator==(const line &other) {
        return (p1 == other.p1) && (p2 == other.p2);
    }

    bool line::operator!=(const line &other) {
        return !(*this == other);
    }

    bool operator==(std::vector<line> &lhs, const std::vector<line> &rhs) {
        if (lhs.size() == rhs.size()) {
            size_t n = lhs.size();
            for(size_t i = 0; i < n; ++i) {
                if (lhs[i] != rhs[i]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    line getRotated(double t) {
        double a = atan(t);
        return line(point(0,0), point(cos(a), sin(a)));
    }

    point third(const point &p1, const point &p2, double ratio = 1.0 / 2, double height = 0) {
        double side = dist(p1, p2);
        if (dblEq(height, 0, 0.0001)) { height = (side / 2) * sqrt(3);}
        // точка в пропорции
        point pm = point((1 - ratio) * p1.x + ratio * p2.x,
                         (1 - ratio) * p1.y + ratio * p2.y);
        if (dblEq(p1.x, p2.x, 0.000001)) {
            return point(p1.x + height, pm.y);
        } else if (dblEq(p1.y, p2.y, 0.000001)) {
            return point(pm.x, p1.y + height);
        }
        // наклон прямой, перпендикулярной p1 p2
        double k = - (p1.x - p2.x) / (p1.y - p2.y);
        line v01 = getRotated(k);
        return point(v01.p2.x * height + pm.x, v01.p2.y * height + pm.y);
    }

    class triangle {
    public:
        explicit triangle(point, point, point);
        triangle() = default;
        point p1{};
        point p2{};
        point p3{};
    };

    triangle::triangle(point c1, point c2, point c3) {
        point arr[3] = {c1, c2, c3};
        std::sort(arr, arr + 3, compP);
        p1 = arr[0];
        p2 = arr[1];
        p3 = arr[2];
    }

    bool isosceles (const triangle &t) {
        return dblEq(dist(t.p1, t.p2), dist(t.p2, t.p3), 0.0001)
               && dblEq(dist(t.p2, t.p3), dist(t.p3, t.p1), 0.0001);
    }

    double maxL(const point &p1, const point &p2) {
        return 2 * dist(p1, p2) * sqrt(1 / 3.0);
    }

    // функция проверки L. Если такой длины не поместится, пустой вектор
    std::vector<line> cutWall(const triangle &t, const double &l) {
        if (isosceles(t)) {
            // максимум что можно поместить - катет треугольника
            // с гипотенузой - 2 / 3 стороны и катетом 1 / 3 стороны
            double limit = maxL(t.p1, t.p2) / 2;
            if (l/2 < 0) {
                return std::vector<line>();
            }
            if (l/2 < limit) {
                // поместим центр каждой линии на треть соответствующей стороны,
                // перпендикулярно ей
                line l1(third(t.p1, t.p2, 1.0 / 3, l / 2.0), third(t.p1, t.p2, 1.0 / 3, -l / 2.0));
                line l2(third(t.p2, t.p3, 1.0 / 3, l / 2.0), third(t.p2, t.p3, 1.0 / 3, -l / 2.0));
                line l3(third(t.p3, t.p1, 1.0 / 3, l / 2.0), third(t.p3, t.p1, 1.0 / 3, -l / 2.0));
                return std::vector<line>{l1, l2, l3};
            }
        }
        return std::vector<line>();
    }

}