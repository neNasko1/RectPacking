#pragma once
#ifndef EMPTYRECTANGLESET_H
#define EMPTYRECTANGLESET_H

#include <vector>
#include "../Shapes/Shapes.h"

namespace rectpack {

class EmptyRectanglesSet {
private:
    std::vector<Box> emptyRectangles;
    Box fullBin;
public:
    EmptyRectanglesSet();
    EmptyRectanglesSet(const Box &_rect);
    ~EmptyRectanglesSet();
    void clear();
    void  pushBox   (const Box &shape);
    void  pushEmpty (const Box &emptRect);
    bool  findBest   (const Rectangle &rect, Box &ret);
    bool  findBestRotation(const Rectangle &rect, Box &ret, Box &boundingBox);
};

};

#endif // EMPTYRECTANGLESET_H
