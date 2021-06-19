#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <fstream>
#include <set>

#include "../Shapes/Shapes.h"
#include "../DataStructures/EmptyRectangleSet.h"
#include "../DataStructures/RandomSorter.tpp"
#include "Solvers.h"

namespace rectpack {

Packing::Packing() : score(0), shapes()  {}
Packing::Packing(const std::vector<Box> &_shapes) : score(0), shapes(_shapes) {
    for(const auto &shp : _shapes) {
        this->score += shp.getArea();
    }
}
Packing::Packing(const Packing &other) : score(other.score), shapes(other.shapes) {}

Packing::~Packing() {}

bool Packing::compareAndSwap(const Packing &other) {
    if(other.score > this->score) {
        *this = other;
        return true;
    }
    return false;
}

void Packing::push_back(const Box &shape) {
    this->score += shape.getArea();
    this->shapes.push_back(shape);
}

void Packing::pop_back() {
    this->score -= this->shapes.back().getArea();
    this->shapes.pop_back();
}

void Packing::clear() {
    this->score = 0;
    this->shapes.resize(0);
}

void Packing::printToSvg(std::ostream &out) {
    std::set<int> used;
    out << "\t<defs>" << std::endl;
    for(const auto &shp : this->shapes) {
        if(used.find(shp.data) == used.end()) {
            out << "\t\t<g id = \"" << shp.data << "\">" << std::endl;
            out << "\t\t\t<rect x = \"" << 0 << "\" y = \"" << 0 << "\" width=\"" << shp.width << "\" height=\"" << shp.height
                << "\" style=\"fill:rgb(255, 255, 210, 255);stroke-width:0.3;stroke:rgb(0, 255, 0)\" />" << std::endl;
            out << "\t\t</g>" << std::endl;
            used.insert(shp.data);
        }
    }
    out << "\t</defs>" << std::endl;
    for(const auto &shp : this->shapes) {
        out << "\t<use xlink:href=\"#" << shp.data << "\" transform=\"translate(" << shp.x << ", " << shp.y << ") rotate(" << shp.angle << ", " << 0 << ", " << 0 << ") \"/>" << std::endl;
    }
}

Solver::Solver(const Rectangle &_bin) : bin(_bin), buffer(), packed() {}

Solver::~Solver() {}

void Solver::printToSvg(std::ostream &out) {
    out << "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width='2000' height='2000' viewBox=\"0 0 2000 2000\">" << std::endl;

    this->bin.printToSvg(out);
    std::cout << "Here " << std::endl;
    this->packed.printToSvg(out);

    out << "\t<text x = \"" << 2 << "\" y = \"" << this->bin.height + 10 << "\" fill = \"red\" style=\"font-size: 4pt;\">" << this->packed.score << "from " << this->bin.getArea() << "</text>" << std::endl;
    out << "</svg>" << std::endl;
}

void Solver::solve(const std::vector<Rectangle> &shapesToSolveFor, const float maxTime, cordType (*evaluator)(const Rectangle &)) {
    auto copyShapesToSolveFor = shapesToSolveFor;
    auto beginClock = clock();

    // Shuffles until there is no time left
    while(maxTime - (clock() - beginClock) > 0) {
        randomSort(copyShapesToSolveFor.begin(), copyShapesToSolveFor.end(), evaluator);
        // We want the biggest to be picked first.
        reverse(copyShapesToSolveFor.begin(), copyShapesToSolveFor.end());

        this->solveForPermutation(copyShapesToSolveFor, maxTime - (clock() - beginClock));
        if(this->packed.compareAndSwap(this->buffer)) {
            std::cout << this->packed.score << std::endl;
        }

        for(auto &toReset : copyShapesToSolveFor) {
            toReset.placed = false;
        }
    }
}

};
