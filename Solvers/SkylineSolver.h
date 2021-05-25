#pragma once
#ifndef SKYLINE_SOLVER_H
#define SKYLINE_SOLVER_H

#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

#include "../Shapes.h"
#include "../Solvers.h"

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
    void pushBox(const Rectangle &rect, std::multiset<SkylineInterval>::iterator &firstIterator);
public:
    SkylineSolver(const Rectangle &_bin);
    ~SkylineSolver();
    void solve(std::vector<Rectangle> &shapesToPush, const float maxTime);
};

#endif
