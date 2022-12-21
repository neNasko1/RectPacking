#pragma once
#ifndef TESTING_H
#define TESTING_H

#include <time.h>
#include <math.h>

#include "../RectanglePacker/RectanglePacker.h"
#include "../Shapes/Shapes.h"

namespace rectpack {
namespace testinglib {
    // Library for testing rectangle packing's correctness using stresstesting.
    /**
     * Find non-generous bounding box around given box;
     * @param box Box to get bounding box from.
     * @return boundingBox
     */
    Box boundingBox(const Box &box);
    bool boundingBoxAreCollidingAABB(const Box &a, const Box &b);
    /**
     * Checks if packing is ok.
     * @param packed Packing to check.
     * @return Is there a collision.
     */
    bool okPacking(const Packing &packed);
    /**
     * Full stress testing of rectanglepacker class.
     */
    void stressTest(const float maxTime);
}
};

#endif // TESTING_H
