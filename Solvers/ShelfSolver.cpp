#include <vector>
#include <algorithm>

#include "../Shapes/Shapes.h"
#include "ShelfSolver.h"

namespace rectpack {

ShelfSolver::ShelfSolver(const Rectangle &_bin) : Solver(_bin) {}

ShelfSolver::~ShelfSolver() {}

void ShelfSolver::solveForPermutation(std::vector<Rectangle> &shapesToSolveFor, const float maxTime) {
    this->buffer.clear();

    // Pushes rectangles row by row.

    float currentx = 0, currenty = 0;
    float highestInRow = 0;
    auto beginClock = clock();

    do {
        highestInRow = 0;
        currentx = 0;
        for(auto &shp : shapesToSolveFor) if(!shp.placed && clock() - beginClock < maxTime) {
            if(this->bin.width - currentx >= shp.width && this->bin.height - currenty >= shp.height) {
                highestInRow = std::max(highestInRow, shp.height);
                shp.placed = true;
                this->buffer.push_back(Box(currentx, currenty, shp, 0));
                currentx += shp.width;
            }
        }
        currenty += highestInRow;
    } while(highestInRow != 0 && clock() - beginClock < maxTime);
}

};
