#pragma once
#ifndef SOLVERS_H
#define SOLVERS_H

#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <set>

#include "Shapes.h"
#include "EmptyRectangleSet.h"

class Packing : public std::vector<Box> {
public:
    float score;
    std::vector<Box> shapes;

    Packing();
    Packing(const std::vector<Box> &_shapes);
    Packing(const Packing &other);
    ~Packing();
    void compareAndSwap(const Packing &other);
    void push_back(const Box &shape);
    void pop_back();
};

class Solver {
protected:
    Rectangle bin;
    Packing packed;
public:
    virtual void solve(std::vector<Rectangle> &shapesToPush, const float maxTime) = 0;
    Solver(const Rectangle &_bin);
    void printToSvg(std::ostream &out);
};

#endif // SOLVERS_H

