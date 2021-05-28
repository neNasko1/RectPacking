#include <fstream>
#include <iostream>
#include <sstream>

#include "../json11/json11.hpp"

#include "../Solvers/Solvers.h"
#include "../Solvers/MaxRectSolver.h"
#include "../Solvers/SkylineSolver.h"
#include "../Solvers/ShelfSolver.h"
#include "RectanglePacker.h"

namespace rectpack {

RectanglePacker::RectanglePacker(int _mask, int _maxTime) : shapes(), mask(_mask), maxTime(_maxTime) {}
RectanglePacker::RectanglePacker(const RectanglePacker &other) : shapes(other.shapes), bin(other.bin), mask(other.mask), maxTime(other.maxTime), packed(other.packed) {}

void RectanglePacker::inputFromJSON(std::istream &in) {
    std::stringstream inStream;
    inStream << in.rdbuf();
    std::string inputString = inStream.str();

    std::string err;
    auto json = json11::Json::parse(inputString, err);

    if(err != "") {
        std::cout << "There was an error : " << err << std::endl;
        exit(0);
    }

    this->bin = Rectangle(json["Bin"]["W"].number_value(), json["Bin"]["H"].number_value());
    this->mask = json["Settings"]["Mask"].int_value();
    this->maxTime = json["Settings"]["MaxTime"].number_value();

    for(const auto &shp : json["Shapes"].array_items()) {
        float w = shp["W"].number_value(), h = shp["H"].number_value(); int count = shp["Count"].int_value();
        for(int i = 0; i < count; i ++) {
            this->shapes.push_back(Rectangle(w, h));
        }
    }

    this->outputFile = json["Outputfile"].string_value();

    std::cout << "Read from stream" << std::endl;
    std::cout << this->bin << " " << this->mask << " " << this->maxTime << " " << std::endl;
    for(const auto &shp : this->shapes) {
        std::cout << shp << "; ";
    }
    std::cout << std::endl;
}

void RectanglePacker::execute() {
    if(this->mask & 1) {
        SkylineSolver solver(this->bin);
        solver.solve(this->shapes, this->maxTime);
        this->packed.compareAndSwap(solver.packed);
    }
    if(this->mask & 2) {
        MaxRectSolver solver(this->bin);
        solver.solve(this->shapes, this->maxTime);
        this->packed.compareAndSwap(solver.packed);
    }
    if(this->mask & 4) {
        ShelfSolver solver(this->bin);
        solver.solve(this->shapes, this->maxTime);
        this->packed.compareAndSwap(solver.packed);
    }
    this->outputToSvg();
}

void RectanglePacker::outputToSvg() {
    std::ofstream out;
    out.open(this->outputFile);

    out << "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width='2000' height='2000' viewBox=\"0 0 2000 2000\">" << std::endl;

    this->bin.printToSvg(out);

    for(const auto &shp : this->packed.shapes) {
        shp.printToSvg(out);
    }

    out << "\t<text x = \"" << 2 << "\" y = \"" << this->bin.height + 10 << "\" fill = \"red\" style=\"font-size: 4pt;\">" << this->packed.score << "from " << this->bin.getArea() << "</text>" << std::endl;
    out << "</svg>" << std::endl;

    out.close();
}

};
