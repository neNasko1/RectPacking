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
private:
    void outputToSvg();
public:
    std::vector<Rectangle> shapes;
    Rectangle bin;
    int mask;
    float maxTime;
    Packing packed;
    std::string outputFile;

    RectanglePacker(int _mask = 0, int _maxTime = 0);
    RectanglePacker(const RectanglePacker &other);
    void inputFromJSON(std::istream &in);
    void execute();
};

};

#endif // PARSER_H
