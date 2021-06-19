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

/**
 * Class which extends Solver and uses the skyline algorithm to pack the rectangles.
 */
class SkylineSolver final : public Solver {
private:
    /**
     * Class which is used to store the upper hull intervals.
     */
    class SkylineInterval {
    public:
        /// Right border of interval in the x axis.
        cordType rightBorder;
        /// Height of interval in the y axis.
        cordType height;
        SkylineInterval();
        SkylineInterval(const cordType _rightBorder, const cordType _height);
        /**
         * < Operator overloading for SkylineIntervals sorting by right border.
         */
        bool operator <(const SkylineInterval &other) const;
    };
    /// Set of intervals in the upper hull.
    std::multiset<SkylineInterval> skylineIntervalSet;
    /// Set of empty spaces which are blocked by the upper hull and could be used for later packing.
    EmptyRectanglesSet emptySpacesSet;
    /**
     * Gets the left border of an interval - notice its the right border of the interval directly to the left of it.
     * @param firstIterator Set iterator to the interval.
     * @return Left border in the x axis.
     */
    cordType getLeftBorder(std::multiset<SkylineInterval>::iterator &firstIterator);
    /**
     * Finds best interval to put rectangle on top of.
     * @param rect Rectangle to search for.
     * @param ret Actual box position for the rectangle to be put in.
     * @return Set iterator for interval which will be under the new rectangle. If there is no suitable interval returns skylineIntervalSet.end().
     */
    std::multiset<SkylineInterval>::iterator findBest(const Rectangle &rect, Box &ret);
    /**
     * Pushes box in the skylineIntervalSet, and pushes empty spaces in the emptySpaces accordingly.
     * @param rect Rectangle to push.
     * @param bestIntervalIterator Interval to put the rectangle on.
     */
    void pushBox(const Rectangle &rect, std::multiset<SkylineInterval>::iterator &bestIntervalIterator);
    /**
     * Packs the rectangles in the given bin and saves the packing in the buffer.
     * @param shapesToSolveFor Rectangles to pack.
     * @param maxTime Maximal time given to the method to solve.
     */
    void solveForPermutation(std::vector<Rectangle> &shapesToSolveFor, const float maxTime);
public:
    SkylineSolver(const Rectangle &_bin);
    ~SkylineSolver();
};

};

#endif
