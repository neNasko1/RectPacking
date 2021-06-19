#pragma once
#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>

namespace rectpack {

typedef unsigned long long cordType;
const cordType CORDTYPE_INFINITY = 0xffffffffffffffff;

class Rectangle {
public:
    cordType width, height;
    bool placed;
    int data;

    Rectangle(const cordType _width = 0, const cordType _height = 0, const int _data = -1);
    Rectangle(const Rectangle &other);
    ~Rectangle();
    cordType getArea() const;
    cordType getPerimeter() const;
    Rectangle flip() const;
    void printToSvg(std::ostream &out) const;
};

std::ostream &operator <<(std::ostream &out, const Rectangle &rect);

class Box : public Rectangle {
public:
    cordType x, y;
    float angle;

    Box(const cordType _x = 0, const cordType _y = 0, const cordType _width = 0, const cordType _height = 0, const float _angle = 0, const int _data = -1);
    Box(const cordType _x, const cordType _y, const Rectangle &_rect, const float _angle = 0);
    Box(const Box &other);
    ~Box();
    bool containsAABB(const Box &other) const;
    void printToSvg(std::ostream &out) const;
};

std::ostream &operator <<(std::ostream &out, const Box &box);
bool areCollidingAABB(const Box &first, const Box &second);

namespace rectangleEvaluators {
    unsigned long long areaEvaluator(const Rectangle &rect);
    unsigned long long perimeterEvaluator(const Rectangle &rect);
    unsigned long long widthEvaluator(const Rectangle &rect);
    unsigned long long heightEvaluator(const Rectangle &rect);
};

};

#endif // SHAPES_H
