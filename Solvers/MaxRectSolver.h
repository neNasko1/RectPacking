#pragma once
#ifndef MAXRECT_SOLVER_H
#define MAXRECT_SOLVER_H

#include <vector>
#include "../Solvers.h"
#include "../Shapes.h"

class MaxRectSolver : public Solver {
private:
    EmptyRectanglesSet emptySpaces;
public:
    MaxRectSolver(const Rectangle &_bin);
    ~MaxRectSolver();
    bool pushShape(const Rectangle &shapeToPush);
    void solve(std::vector<Rectangle> &shapesToPush, const float maxTime);
};


#endif

