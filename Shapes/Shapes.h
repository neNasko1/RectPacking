#pragma once
#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>

namespace rectpack {

class Rectangle {
public:
    float width, height;
    bool placed;
    int data;

    Rectangle(const float _width = 0, const float _height = 0, const int _data = -1);
    Rectangle(const Rectangle &other);
    ~Rectangle();
    float getArea() const;
    Rectangle flip() const;
    void printToSvg(std::ostream &out) const;
};

std::ostream &operator <<(std::ostream &out, const Rectangle &rect);

class Box : public Rectangle {
public:
    float x, y;
    float angle;

    Box(const float _x = 0, const float _y = 0, const float _width = 0, const float _height = 0, const float _angle = 0, const int _data = -1);
    Box(const float _x, const float _y, const Rectangle &_rect, const float _angle = 0);
    Box(const Box &other);
    ~Box();
    bool containsAABB(const Box &other) const;
    void printToSvg(std::ostream &out) const;
};

std::ostream &operator <<(std::ostream &out, const Box &box);
bool areCollidingAABB(const Box &first, const Box &second);

};

#endif // SHAPES_H
