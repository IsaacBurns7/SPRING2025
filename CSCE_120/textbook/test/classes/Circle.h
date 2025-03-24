#pragma once
#include "Shape.h"

template<typename T>
class Circle: public Shape{
    public:
        Circle(Point p, int rr);

        Point center() const {return x;}
        void move(Point to) {x = to; }
        void draw() const;
        void rotate(int) {}

    private:
        Point x;
        int r;
};