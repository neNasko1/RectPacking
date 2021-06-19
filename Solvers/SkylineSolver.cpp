#include <vector>
#include <set>
#include <algorithm>
#include <math.h>
#include <iterator>

#include "../Shapes/Shapes.h"
#include "Solvers.h"
#include "SkylineSolver.h"

namespace rectpack {

SkylineSolver::SkylineSolver(const Rectangle &_bin) : Solver(_bin), skylineIntervalSet(), emptySpacesSet() {}

SkylineSolver::SkylineInterval::SkylineInterval() : rightBorder(0), height(0) {}

SkylineSolver::SkylineInterval::SkylineInterval(const cordType _rightBorder, const cordType _height) : rightBorder(_rightBorder), height(_height) {}

SkylineSolver::~SkylineSolver() {}

bool SkylineSolver::SkylineInterval::operator <(const SkylineInterval &other) const {
    return this->rightBorder < other.rightBorder;
}

cordType SkylineSolver::getLeftBorder(std::multiset<SkylineInterval>::iterator &firstIterator) {
    cordType leftBorder;
    if(firstIterator == this->skylineIntervalSet.begin()) {
        leftBorder = 0;
    } else {
        firstIterator --;
        leftBorder = firstIterator->rightBorder;
        firstIterator ++;
    }
    return leftBorder;
}

void SkylineSolver::pushBox(const Rectangle &rect, std::multiset<SkylineInterval>::iterator &bestIntervalIterator) {
    cordType leftBorder = this->getLeftBorder(bestIntervalIterator);
    cordType height = 0, currentLeftBorder = leftBorder;

    // Doesn't represent actual empty spaces, but an abstract box with negative height, so we can figure out the real height in the end
    std::vector<Box> fakeEmptySpaces;

    for(auto iter = bestIntervalIterator; iter != this->skylineIntervalSet.end();) {
        height = std::max(height, iter->height);
        if(iter->rightBorder <= leftBorder + rect.width) {
            auto copyIter = iter;
            fakeEmptySpaces.push_back(Box(currentLeftBorder, iter->height, iter->rightBorder - currentLeftBorder, -iter->height)); // Important - box is not real
            bool equalityBreak = iter->rightBorder == leftBorder + rect.width; // If current rightBorder is the same as the rightBorder of iter we should break out.

            // Erase iter's interval from the skylineIntervalSet and move it to the right.
            currentLeftBorder = iter->rightBorder;
            iter ++;
            this->skylineIntervalSet.erase(copyIter);

            if(equalityBreak) {
                break;
            }
        } else {
            // Last interval under the pushed box.
            fakeEmptySpaces.push_back(Box(currentLeftBorder, iter->height, leftBorder + rect.width - currentLeftBorder, -iter->height)); // Important - box is not real
            break;
        }
    }

    // Fix the emptyPlaces
    for(auto &emptySpace : fakeEmptySpaces) {
        emptySpace.height += height;
        this->emptySpacesSet.pushEmpty(emptySpace);
    }

    this->skylineIntervalSet.insert(SkylineInterval(leftBorder + rect.width, height + rect.height));
}

std::multiset<SkylineSolver::SkylineInterval>::iterator SkylineSolver::findBest(const Rectangle &rect, Box &ret) {
    cordType currentLeftBorder = 0;
    auto leftPointer = this->skylineIntervalSet.begin(), rightPointer = this->skylineIntervalSet.begin();

    std::multiset<cordType> heights; cordType heightSum = 0;
    heights.insert(leftPointer->height);

    cordType minWaste = CORDTYPE_INFINITY;
    auto retIterator = this->skylineIntervalSet.end();

    // Finds out which intervals are going to be under a rectangle if you put its left border to be the same as the left border of leftPointer.
    // using a 2-pointer approach. rightPointer is moved accordingly.

    while(leftPointer != this->skylineIntervalSet.end() && currentLeftBorder + rect.width <= this->bin.width) {
        // Moving rightPointer accordingly.
        while(rightPointer->rightBorder < currentLeftBorder + rect.width) {
            cordType rightPointerLeftBorder = rightPointer->rightBorder;
            rightPointer ++;
            if(rightPointer == this->skylineIntervalSet.end()) {break;}
            heights.insert(rightPointer->height);

            //Heightsum is a part of the calculated currentWaste.
            heightSum += rightPointer->height * (rightPointer->rightBorder - rightPointerLeftBorder);
        }
        // If the rectangle is going to be outside of the bin break out.
        if(rightPointer == this->skylineIntervalSet.end()) {break;}

        // Finds out the height of the highest interval between leftPointer and rightPointer.
        cordType extractedMax = *(heights.rbegin());
        // Current waste is a rough estimate of the wasted area by this choice
        cordType currentWaste = extractedMax * (rightPointer->rightBorder - currentLeftBorder) - heightSum;

        // If currentWaste is smaller than minWaste change return value.
        if(currentWaste < minWaste && extractedMax + rect.height <= this->bin.height) {
            minWaste = currentWaste;
            ret = Box(currentLeftBorder, extractedMax, rect, 0);
            retIterator = leftPointer;
        }

        // Moves leftPointer.
        heightSum -= leftPointer->height * (leftPointer->rightBorder - currentLeftBorder);
        heights.erase(heights.find(leftPointer->height));
        currentLeftBorder = leftPointer->rightBorder;
        leftPointer ++;

    }
    return retIterator;
}

void SkylineSolver::solveForPermutation(std::vector<Rectangle> &shapesToSolveFor, const float maxTime) {
    // Reset the solver to the initial conditions.
    this->buffer.clear();
    this->skylineIntervalSet.clear();
    this->emptySpacesSet.clear();
    auto beginClock = clock();

    skylineIntervalSet.insert(SkylineInterval(this->bin.width, 0));

    // Search for a place to put each rectangle on - only using the upper hull.
    for(auto &shp : shapesToSolveFor) if(clock() - beginClock < maxTime) {
        Box shapePlace;
        auto placeIterator = this->findBest(shp, shapePlace);
        if(placeIterator != this->skylineIntervalSet.end()) {
            this->buffer.push_back(shapePlace);
            this->pushBox(shapePlace, placeIterator);
            shp.placed = true;
        }
    }

    // Search for a place to put each rectangle on - only using the empty spaces in emptySpacesSet.
    for(auto &shp : shapesToSolveFor) if(clock() - beginClock < maxTime && !shp.placed) {
        Box shapePlace;
        if(this->emptySpacesSet.findBest(shp, shapePlace)) {
            this->buffer.push_back(shapePlace);
            this->emptySpacesSet.pushBox(shapePlace);
            shp.placed = true;
        }
    }

    // Search for a place to put each rectangle on(using rotations) - only using the empty spaces in emptySpacesSet.
    for(auto &shp : shapesToSolveFor) if(clock() - beginClock < maxTime && !shp.placed) {
        Box shapePlace, boundingBox;
        if(this->emptySpacesSet.findBestRotation(shp, shapePlace, boundingBox)) {
            this->buffer.push_back(shapePlace);
            this->emptySpacesSet.pushBox(boundingBox);
            shp.placed = true;
        }
    }
}

};
