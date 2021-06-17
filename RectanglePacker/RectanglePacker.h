#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <iostream>
#include <sstream>

#include "../json11/json11.hpp"

#include "../Solvers/Solvers.h"
#include "../Shapes/Shapes.h"
#include "../Solvers/MaxRectSolver.h"
#include "../Solvers/SkylineSolver.h"
#include "../Solvers/ShelfSolver.h"

namespace rectpack {

/**
 * Class which receives input and executes packing algorithms according to the given settings.
 */
class RectanglePacker {
public:
    /// Shapes to pack.
    std::vector<Rectangle> shapes;
    /// Bin to pack in.
    Rectangle bin;
    /// Mask of solvers to use.
    int mask;
    /// Max time given to each solver.
    float maxTime;
    /// Seed to seed the rng.
    int seed;
    /// Evaluator to randomly sort by.
    int (*evaluator)(const Rectangle &);
    /// Best packing found by execute().
    Packing packed;

    RectanglePacker(int _mask = 0, float _maxTime = 0, int _seed = 0, int (*_evaluator)(const Rectangle&) = rectangleEvaluators::areaEvaluator);
    RectanglePacker(const RectanglePacker &other);
    ~RectanglePacker();
    /**
     * Input setting for the packer in JSON format.
     * @param in Stream to input from.
     */
    void inputFromJSON(std::istream &in);
    /**
     * Execute packing algorithms according to already inputed settings.
     */
    void execute();
    /**
     * Output best packing in SVG format.
     * @param out Stream to output to.
     */
    void outputToSvg(std::ostream &out);
};

};

#endif // PARSER_H
