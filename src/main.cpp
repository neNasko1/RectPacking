#include <iostream>
#include <stdexcept>
#include <vector>
#include <time.h>
#include <algorithm>
#include <fstream>
#include <random>

#include "Shapes/Shapes.h"
#include "Solvers/SkylineSolver.h"
#include "Solvers/MaxRectSolver.h"
#include "Solvers/ShelfSolver.h"
#include "RectanglePacker/RectanglePacker.h"
#include "DataStructures/RandomSorter.tpp"
#include "TestingUtils/TestingUtils.h"


int main() {
    rectpack::RectanglePacker rp;

    std::ifstream in("input.json");
    rp.inputFromJSON(in);
    in.close();

    rp.execute();

    std::ofstream out("rect.svg");
    rp.outputToSvg(out);
    out.close();

    return 0;
}
