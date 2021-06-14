#pragma once
#ifndef SHELF_SOLVER_H
#define SHELF_SOLVER_H

#include <vector>
#include "../Shapes/Shapes.h"
#include "Solvers.h"

namespace rectpack {

/**
 * Class which extends Solver and uses the shelf algorithm to pack the rectangles.
 */
class ShelfSolver : public Solver {
private:
    /**
     * Packs the rectangles in the given bin and saves the packing in the buffer.
     * @param shapesToSolveFor Rectangles to pack.
     * @param maxTime Maximal time given to the method to solve.
     */
    void solveForPermutation(std::vector<Rectangle> &shapesToSolveFor, const float maxTime);
public:
    ShelfSolver(const Rectangle &_bin);
    ~ShelfSolver();
};

};

#endif

