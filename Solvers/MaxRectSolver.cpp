#include <vector>
#include <algorithm>
#include <math.h>

#include "../DataStructures/EmptyRectangleSet.h"
#include "MaxRectSolver.h"
#include "Solvers.h"

namespace rectpack {

MaxRectSolver::MaxRectSolver(const Rectangle &_bin) : Solver(_bin), emptySpacesSet(Box(0, 0, _bin, 0))  {}

MaxRectSolver::~MaxRectSolver()  {}

void MaxRectSolver::solveForPermutation(std::vector<Rectangle> &shapesToSolveFor, const float maxTime) {
    this->buffer.clear();
    this->emptySpacesSet.clear();

    auto beginClock = clock();

    // Search for a place to put each rectangle on - only using the empty spaces in emptySpacesSet.
    for(auto &shp : shapesToSolveFor) if(clock() - beginClock < maxTime) {
        Box shapePlace;
        if(this->emptySpacesSet.findBest(shp, shapePlace)) {
            this->buffer.push_back(shapePlace);
            this->emptySpacesSet.pushBox(shapePlace);
            shp.placed = true;
        }
    }

    // Search for a place to put each rectangle on(using rotations) - only using the empty spaces in emptySpacesSet.
    for(auto &shp : shapesToSolveFor) if(clock() - beginClock < maxTime && !shp.placed) {
        Box shapePlace, boundingBox;
        if(this->emptySpacesSet.findBestRotation(shp, shapePlace, boundingBox)) {
            this->buffer.push_back(shapePlace);
            this->emptySpacesSet.pushBox(boundingBox);
            shp.placed = true;
        }
    }
}

};
