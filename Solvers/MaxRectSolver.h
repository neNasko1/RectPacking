#pragma once
#ifndef MAXRECT_SOLVER_H
#define MAXRECT_SOLVER_H

#include <vector>
#include "../Shapes/Shapes.h"
#include "Solvers.h"

namespace rectpack {

class MaxRectSolver : public Solver {
private:
    EmptyRectanglesSet emptySpaces;
    void solveForPermutation(std::vector<Rectangle> &shapesToPush, const float maxTime);
public:
    MaxRectSolver(const Rectangle &_bin);
    ~MaxRectSolver();
    bool pushShape(const Rectangle &shapeToPush);
};

};

#endif

