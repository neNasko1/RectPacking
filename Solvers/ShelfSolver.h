#pragma once
#ifndef SHELF_SOLVER_H
#define SHELF_SOLVER_H

#include <vector>
#include "../Shapes/Shapes.h"
#include "Solvers.h"

namespace rectpack {

class ShelfSolver : public Solver {
private:
    void solveForPermutation(std::vector<Rectangle> &shapesToPush, const float maxTime);
public:
    ShelfSolver(const Rectangle &_bin);
    ~ShelfSolver();
};

};

#endif

