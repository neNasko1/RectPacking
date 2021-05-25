#pragma once
#ifndef EMPTYRECTANGLESET_H
#define EMPTYRECTANGLESET_H

#include <vector>
#include "Shapes.h"

class EmptyRectanglesSet {
private:
    std::vector<Box> emptyRectangles;
public:
    EmptyRectanglesSet();
    EmptyRectanglesSet(const Box &_rect);
    void   pushBox (const Box &shape);
    void pushEmpty (const Box &emptRect);
    bool  findBest (const Rectangle &rect, Box &ret);
};

#endif // EMPTYRECTANGLESET_H
