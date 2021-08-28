#pragma once

// A class to hold 2d points

class Point {
public:
    int x, y;

    Point() :x(0), y(0) {}
    Point(int x, int y) { this->x = x; this->y = y; }
    ~Point() {}
    bool operator ==(const Point& p) const { return p.x == this->x && p.y == this->y; }
    bool operator !=(const Point& p) const { return p.x != this->x || p.y != this->y; }
};