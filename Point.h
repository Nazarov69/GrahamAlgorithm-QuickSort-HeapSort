#ifndef POINT_H
#define POINT_H

#define collinear 0
#define left -1
#define right 1

class Point {
    int x;
    int y;
public:
    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}
    int get_x() { return x; }
    int get_y() { return y; }
    void set_point(int _x, int _y) {
        x = _x;
        y = _y;
    }
    void set_point(Point& pt) {
        x = pt.get_x();
        y = pt.get_y();
    }
    void set_x(int _x) { x = _x; }
    void set_y(int _y) { y = _y; }
    int orientation(const Point& p1, const Point& p2) {
        int value = (p1.y - y) * (p2.x - p1.x) - (p1.x - x) * (p2.y - p1.y);
        if (value == 0) return collinear;
        else if (value > 0) return right;
        else return left;
    }
    int sq_distance(const Point& pt) { return (x - pt.x) * (x - pt.x) + (y - pt.y) * (y - pt.y); }
    bool equals(const Point& pt) { return x == pt.x && y == pt.y; }
    void print() { printf_s("(%d,%d)", x, y); }
};
#endif
