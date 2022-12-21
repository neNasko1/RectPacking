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

/**
 * Class which encapsulates a packing of boxes with its score(sum of areas).
 */
class Packing {
public:
    /// Sum of the areas of the boxes in this packing.
    cordType score;
    /// Boxes in the packing
    std::vector<Box> shapes;

    Packing();
    Packing(const std::vector<Box> &_shapes);
    Packing(const Packing &other);
    ~Packing();
    /**
     * Compares packing with another packing and if the other packing is better(with higher score) swaps them.
     * @param other Packing to compare with.
     * @return Was a swap performed?
     */
    bool compareAndSwap(const Packing &other);
    /**
     * Pushes a box in the current packing.
     * @param shape Box to push.
     */
    void push_back(const Box &shape);
    /**
     * Pops the last pushed element in this packing.
     */
    void pop_back();
    /**
     * Pops all elements from this packing.
     */
    void clear();
    /**
     * Prints current packing in SVG format.
     * @param out Stream to print in.
     */
    void printToSvg(std::ostream &out);
};

/**
 * Abstract class which solves the rectangle packing problem.
 */
class Solver {
protected:
    /// Bin to pack the boxes in.
    Rectangle bin;
    /// Buffer where current packing is saved in.
    Packing buffer;
    /**
     * Packs the rectangles in the given bin and saves the packing in the buffer.
     * @param shapesToSolveFor Rectangles to pack.
     * @param maxTime Maximal time given to the method to solve.
     */
    virtual void solveForPermutation(std::vector<Rectangle> &shapesToSolveFor, const float maxTime) = 0;
public:
    /// Current best packing.
    Packing packed;
    Solver(const Rectangle &_bin);
    ~Solver();
    /**
     * Tries out different permutations of the given rectangles to find out an optimal answers.
     * @param shapesToSolveFor Rectangles to solve the problem for.
     * @param maxTime Maximal time given to the solver to solve.
     */
    void solve(const std::vector<Rectangle> &shapesToSolveFor, const float maxTime, unsigned long long (*evaluator)(const Rectangle &));
    /**
     * Prints current packing in SVG format.
     * @param out Stream to print in.
     */
    void printToSvg(std::ostream &out);
};

};

#endif // SOLVERS_H

