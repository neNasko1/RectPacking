#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <iostream>
#include <sstream>

#include "../json11/json11.hpp"

#include "../Solvers/Solvers.h"
#include "../Solvers/MaxRectSolver.h"
#include "../Solvers/SkylineSolver.h"
#include "../Solvers/ShelfSolver.h"

namespace rectpack {

class RectanglePacker {
public:
    std::vector<Rectangle> shapes;
    Rectangle bin;
    int mask;
    float maxTime;
    int seed;
    Packing packed;

    RectanglePacker(int _mask = 0, float _maxTime = 0, int _seed = 0);
    RectanglePacker(const RectanglePacker &other);
    void inputFromJSON(std::istream &in);
    void execute();
    void outputToSvg(std::ostream &out);
};

};

#endif // PARSER_H
