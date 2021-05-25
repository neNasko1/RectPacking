#include <vector>
#include <algorithm>

#include "../EmptyRectangleSet.h"
#include "MaxRectSolver.h"

MaxRectSolver::MaxRectSolver(const Rectangle &_bin) : Solver(_bin), emptySpaces(Box(0, 0, _bin))  {}
MaxRectSolver::~MaxRectSolver()  {}
void MaxRectSolver::solve(std::vector<Rectangle> &shapesToPush, const float maxTime) {
    auto beginClock = clock();

    std::sort(shapesToPush.begin(), shapesToPush.end(),
    [](const Rectangle &a, const Rectangle &b) {
        return a.getArea() > b.getArea();
    });

    for(auto &shp : shapesToPush) {
        if(clock() - beginClock >= maxTime) {break;}
        Box shapePlace;
        if(this->emptySpaces.findBest(shp, shapePlace)) {
            this->packed.shapes.push_back(shapePlace);
            this->emptySpaces.pushBox(shapePlace);
            shp.placed = true;
        }
    }
}
