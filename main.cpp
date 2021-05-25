#include <iostream>
#include <stdexcept>
#include <vector>
#include <time.h>
#include <algorithm>

#include "Shapes.h"
#include "Solvers/SkylineSolver.h"
#include "Solvers/MaxRectSolver.h"
#include "Solvers/ShelfSolver.h"

#include <fstream>
#include <random>

int main() {
    srand(10);
    ShelfSolver slv(Rectangle(300, 300));

    int n = 1000;
    std::vector<Rectangle> shps;

    for(int i = 0; i < n; i ++) {
        shps.push_back(Rectangle(10 + rand() % 20, 10 + rand() % 20));
    }

    slv.solve(shps, 1000000);

    std::ofstream out;
    out.open("rect.svg");
    slv.printToSvg(out);
    //slv.printToSvg(std::cout);
    out.close();
    return 0;
}

/*
TODO:
Wedn:
Svg
contains arecolliding

Thurs:
time useful
JSON11

Fri:
Quality
*/
