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

    int nowx = 0, nowy = 0;
    int highestInRow = 0;
    do {
        highestInRow = 0;
        nowx = 0;
        for(auto &shp : shapesToPush) if(!shp.placed) {
            if(highestInRow == 0 && this->bin.height - nowy < shp.height) {
                continue;
            } else if(this->bin.width - nowx >= shp.width) {
                shp.placed = true;
                if(highestInRow == 0) {
                    highestInRow = shp.height;
                }
                this->packed.shapes.push_back(Box(nowx, nowy, shp));
                nowx += shp.width;
            }
        }
        nowy += highestInRow;
    } while(highestInRow != 0);
}

