#include <iostream>

class Vector;

class Point{
public:
    int x, y;
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
    void move(Vector dir);
};

class Vector {
public:
    int Vx, Vy;
    Vector(Point sta, Point end) {
        this->Vx = end.x - sta.x;
        this->Vy = end.y - sta.y;
    }
};

void Point::move(Vector dir) {
    x += dir.Vx;
    y += dir.Vy;
}

int main() {
    int x1, y1, x2, y2, x3, y3;
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

    Point p(x1, y1);
    Vector dir(Point(x2, y2), Point(x3, y3));
    p.move(dir);

    std::cout << p.x << ' ' << p.y;
}