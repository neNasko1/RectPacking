#pragma once
#ifndef SKYLINE_SOLVER_H
#define SKYLINE_SOLVER_H

#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

#include "../Shapes/Shapes.h"
#include "Solvers.h"
#include "MaxRectSolver.h"

namespace rectpack {

class SkylineSolver : public Solver {
private:
    class SkylineInterval {
    public:
        float rightBorder, height;
        SkylineInterval();
        SkylineInterval(const float _rightBorder, const float _height);
        bool operator <(const SkylineInterval &other) const;
    };
    std::multiset<SkylineInterval> skylineIntervalSet;
    float getLeftBorder(std::multiset<SkylineInterval>::iterator &firstIterator);
    std::multiset<SkylineInterval>::iterator findBest(const Rectangle &rect, Box &ret);
    EmptyRectanglesSet emptySpaces;
    void pushBox(const Rectangle &rect, std::multiset<SkylineInterval>::iterator &firstIterator);
    void solveForPermutation(std::vector<Rectangle> &shapesToPush, const float maxTime);
public:
    SkylineSolver(const Rectangle &_bin);
    ~SkylineSolver();
};

};

#endif
