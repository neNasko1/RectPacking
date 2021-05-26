#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <set>

#include "Shapes.h"
#include "EmptyRectangleSet.h"
#include "Solvers.h"

Packing::Packing() {}
Packing::Packing(const std::vector<Box> &_shapes) {
    this->shapes = _shapes;
    for(const auto &shp : _shapes) {
        this->score += shp.getArea();
    }
}
Packing::Packing(const Packing &other) {this->score = other.score; this->shapes = other.shapes;}
Packing::~Packing() {}
void Packing::compareAndSwap(const Packing &other) {
    if(other.score > this->score) {
        *this = other;
    }
}
void Packing::push_back(const Box &shape) {
    this->score += shape.getArea();
    this->shapes.push_back(shape);
}
void Packing::pop_back() {
    this->score -= this->shapes.back().getArea();
    this->shapes.pop_back();
}

Solver::Solver(const Rectangle &_bin) : bin(_bin), packed() {}
void Solver::printToSvg(std::ostream &out) {
    out << "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width='800' height='800' viewBox=\"0 0 600 600\">" << std::endl;

    this->bin.printToSvg(out);

    for(const auto &shp : this->packed.shapes) {
        shp.printToSvg(out);
    }

    out << "\t<text x = \"" << 2 << "\" y = \"" << this->bin.height + 10 << "\" fill = \"red\" style=\"font-size: 4pt;\">" << this->packed.score << "from " << this->bin.getArea() << "</text>" << std::endl;
    out << "</svg>" << std::endl;
}
