#pragma once
#include <type_traits>

template <typename T>
class Shape{
    public:
        static_assert(std::is_arithmetic_v<T>, "Point's attributes must be an arithmetic type");
        struct Point{
            T x;
            T y;
        };
        virtual Point center() const = 0; // = 0 means that theres no current implementation
        virtual void move(Point to) = 0;
        virtual void draw() const = 0;
        virtual void rotate(int angle) = 0;

        virtual ~Shape(){ } //destructor
};