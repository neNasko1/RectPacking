#pragma once
#ifndef SOLVERS_H
#define SOLVERS_H

#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <set>

#include "../Shapes/Shapes.h"
#include "../DataStructures/EmptyRectangleSet.h"

namespace rectpack {

class Packing {
public:
    float score;
    std::vector<Box> shapes;

    Packing();
    Packing(const std::vector<Box> &_shapes);
    Packing(const Packing &other);
    ~Packing();
    bool compareAndSwap(const Packing &other);
    void push_back(const Box &shape);
    void pop_back();
    void clear();
    void printToSvg(std::ostream &out);
};

class Solver {
protected:
    Rectangle bin;
    virtual void solveForPermutation(std::vector<Rectangle> &shapesToPush, const float maxTime) = 0;
    Packing buffer;
public:
    Packing packed;
    Solver(const Rectangle &_bin);
    ~Solver();
    void solve(const std::vector<Rectangle> &shapesToPush, const float maxTime);
    void printToSvg(std::ostream &out);
};

};

#endif // SOLVERS_H

