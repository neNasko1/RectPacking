#include <vector>
#include <algorithm>
#include <math.h>

#include "../DataStructures/EmptyRectangleSet.h"
#include "MaxRectSolver.h"
#include "Solvers.h"

namespace rectpack {

MaxRectSolver::MaxRectSolver(const Rectangle &_bin) : Solver(_bin), emptySpaces(Box(0, 0, 0, _bin))  {}

MaxRectSolver::~MaxRectSolver()  {}

void MaxRectSolver::solveForPermutation(std::vector<Rectangle> &shapesToPush, const float maxTime) {
    this->buffer.clear();
    this->emptySpaces.clear();

    auto beginClock = clock();

    for(auto &shp : shapesToPush) if(clock() - beginClock < maxTime) {
        Box shapePlace;
        if(this->emptySpaces.findBest(shp, shapePlace)) {
            this->buffer.push_back(shapePlace);
            this->emptySpaces.pushBox(shapePlace);
            shp.placed = true;
        }
    }
}

};
