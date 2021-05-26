#include <vector>
#include <algorithm>

#include "ShelfSolver.h"
#include "../Shapes.h"

ShelfSolver::ShelfSolver(const Rectangle &_bin) : Solver(_bin) {}

ShelfSolver::~ShelfSolver() {}

void ShelfSolver::solve(std::vector<Rectangle> &shapesToPush, const float maxTime) {
    std::sort(shapesToPush.begin(), shapesToPush.end(),
    [](const Rectangle &a, const Rectangle &b) {
        return a.height > b.height;
    });

    float currentx = 0, currenty = 0;
    float highestInRow = 0;
    do {
        highestInRow = 0;
        currentx = 0;
        for(auto &shp : shapesToPush) if(!shp.placed) {
            if(highestInRow == 0 && this->bin.height - currenty < shp.height) {
                continue;
            } else if(this->bin.width - currentx >= shp.width) {
                shp.placed = true;
                if(highestInRow == 0) {
                    highestInRow = shp.height;
                }
                this->packed.push_back(Box(currentx, currenty, shp));
                currentx += shp.width;
            }
        }
        currenty += highestInRow;
    } while(highestInRow != 0);
}

