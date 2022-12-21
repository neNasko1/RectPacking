#pragma once
#ifndef EMPTYRECTANGLESET_H
#define EMPTYRECTANGLESET_H

#include <vector>
#include "../Shapes/Shapes.h"

namespace rectpack {

class EmptyRectanglesSet {
private:
    /// Array where we store all the empty rectangles. All functions ensure no rectangle is contained in another.
    std::vector<Box> emptyRectangles;
    /// First empty rectangle.
    Box fullBin;
public:
    EmptyRectanglesSet();
    EmptyRectanglesSet(const Box &_rect);
    ~EmptyRectanglesSet();
    /**
     * Clears the set and initializes it with this->fullBin.
     */
    void  clear();
    /**
     * Pushes box and recalculates the new empty rectangles in the set.
     * @param shape Box to be pushed
     */
    void  pushBox   (const Box &shape);
    /**
     * Pushes empty box in the set.
     * @param emptyRect empty box to be pushed.
     */
    void  pushEmpty (const Box &emptyRect);
    /**
     * Finds best placement for a shape.
     * @param rect Shape to place.
     * @param ret Found placement.
     * @ret Was it possible to place this shape.
     */
    bool  findBest   (const Rectangle &rect, Box &ret);
    /**
     * Finds best placement for a rotated shape.
     * @param rect Shape to place.
     * @param ret Found placement.
     * @param boundingBox AABB bounding box.
     * @ret Was it possible to place this shape.
     */
    bool  findBestRotation(const Rectangle &rect, Box &ret, Box &boundingBox);
};

};

#endif // EMPTYRECTANGLESET_H
