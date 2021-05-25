#pragma once
#ifndef SHELF_SOLVER_H
#define SHELF_SOLVER_H

#include <vector>
#include "../Solvers.h"
#include "../Shapes.h"

class ShelfSolver : public Solver {
public:
    ShelfSolver(const Rectangle &_bin);
    ~ShelfSolver();
    void solve(std::vector<Rectangle> &shapesToPush, const float maxTime);
};

#endif

