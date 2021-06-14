#pragma once
#ifndef MAXRECT_SOLVER_H
#define MAXRECT_SOLVER_H

#include <vector>
#include "../Shapes/Shapes.h"
#include "Solvers.h"

namespace rectpack {

/**
 * Class which extends Solver and uses the guillotine algorithm to pack the rectangles.
 */
class MaxRectSolver : public Solver {
private:
    /// Set of empty spaces which are blocked by the upper hull and could be used for later packing.
    EmptyRectanglesSet emptySpacesSet;
    /**
     * Packs the rectangles in the given bin and saves the packing in the buffer.
     * @param shapesToSolveFor Rectangles to pack.
     * @param maxTime Maximal time given to the method to solve.
     */
    void solveForPermutation(std::vector<Rectangle> &shapesToSolveFor, const float maxTime);
public:
    MaxRectSolver(const Rectangle &_bin);
    ~MaxRectSolver();
};

};

#endif

