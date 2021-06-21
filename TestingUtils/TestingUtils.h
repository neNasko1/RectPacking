#pragma once
#ifndef TESTING_H
#define TESTING_H

#include <time.h>
#include <math.h>

#include "../RectanglePacker/RectanglePacker.h"
#include "../Shapes/Shapes.h"

namespace rectpack {
    /**
     * Find non-generous bounding box around given box;
     * @param box Box to get bounding box from.
     * @return boundingBox
     */
    Box boundingBox(const Box &box);
    bool boundingBoxAreCollidingAABB(const Box &a, const Box &b);
    /**
     * Does packing have an intersection.
     * @param packed Packing to check.
     * @return Is there a collision.
     */
    bool intersectingPair(const Packing &packed);
    /**
     * Full stress testing of rectanglepacker class.
     */
    void stressTest(const float maxTime);
};

#endif // TESTING_H
