#ifndef POINT_H
#define POINT_H

#include <QVariant>

class Point {
public:
    explicit Point(qreal _x = 0, qreal _y = 0) : x(_x), y(_y) {};
    Point(const Point  &p)            : x(p.x), y(p.y) {};

    qreal x;
    qreal y;

    Point &operator=(const Point &other) {
        this->x = other.x;
        this->y = other.y;
        return *this;
    }
    Point operator+(Point const &other) const {
        Point res;
        res.x = this->x + other.x;
        res.y = this->y + other.y;
        return res;
    }
    Point operator-(Point const &other) const {
        Point res;
        res.x = this->x - other.x;
        res.y = this->y - other.y;
        return res;
    }
    Point operator*(qreal const num) const {
        Point res;
        res.x = this->x * num;
        res.y = this->y * num;
        return res;
    }
    Point operator/(qreal const num) const {
        Point res;
        res.x = this->x / num;
        res.y = this->y / num;
        return res;
    }

    Point &operator+=(const Point &other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }
    Point &operator-=(const Point &other) {
        this->x -= other.x;
        this->y -= other.y;
        return *this;
    }
    Point &operator*=(qreal const num) {
        this->x *= num;
        this->y *= num;
        return *this;
    }
    Point &operator/=(qreal const num) {
        this->x /= num;
        this->y /= num;
        return *this;
    }

    bool operator==(const Point &other) const {
      //return x == other.x && y == other.y;
        return qFuzzyCompare(x, other.x) && qFuzzyCompare(y, other.y);
    }

    bool operator!=(const Point &other) const {
        return !(*this == other);
    }

};

inline QDebug operator<<(QDebug dbg, const Point &p) {
    dbg.nospace() << "(" << p.x << ", " << p.y << ")";
    return dbg;
}

#endif // POINT_H
