#include <iostream>
#include <stdexcept>
#include <vector>
#include <time.h>
#include <algorithm>

#include "Shapes/Shapes.h"
#include "Solvers/SkylineSolver.h"
#include "Solvers/MaxRectSolver.h"
#include "Solvers/ShelfSolver.h"
#include "RectanglePacker/RectanglePacker.h"

#include <fstream>
#include <random>

int main() {
    //freopen("output.txt", "w", stdout);

    std::ifstream in;
    in.open("input.json");

    rectpack::RectanglePacker rp;
    rp.inputFromJSON(in);
    rp.execute();

    in.close();

    return 0;
}

/*
Make named shapes in svg - reduce file size
Probabilistic sorter - optimizes the answers given by the algorithm
Support for non-90degree rotations - (contains for rotations)
*/
