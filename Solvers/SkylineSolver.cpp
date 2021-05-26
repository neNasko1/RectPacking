#include <vector>
#include <set>
#include <algorithm>
#include <math.h>
#include <iterator>

#include "../Shapes.h"
#include "../Solvers.h"
#include "SkylineSolver.h"

SkylineSolver::SkylineSolver(const Rectangle &_bin) : Solver(_bin), skylineIntervalSet(), emptySpaces() {
    skylineIntervalSet.insert(SkylineInterval(_bin.width, 0));
}

SkylineSolver::~SkylineSolver() {}

SkylineSolver::SkylineInterval::SkylineInterval() : rightBorder(0), height(0) {}

SkylineSolver::SkylineInterval::SkylineInterval(const float _rightBorder, const float _height) : rightBorder(_rightBorder), height(_height) {}

bool SkylineSolver::SkylineInterval::operator <(const SkylineInterval &other) const {
    return this->rightBorder < other.rightBorder;
}

float SkylineSolver::getLeftBorder(std::multiset<SkylineInterval>::iterator &firstIterator) {
    float leftBorder;
    if(firstIterator == this->skylineIntervalSet.begin()) {
        leftBorder = 0;
    } else {
        firstIterator --;
        leftBorder = firstIterator->rightBorder;
        firstIterator ++;
    }
    return leftBorder;
}

void SkylineSolver::pushBox(const Rectangle &rect, std::multiset<SkylineInterval>::iterator &firstIterator) {
    float leftBorder = this->getLeftBorder(firstIterator);
    float height = 0, currentLeftBorder = leftBorder;

    std::vector<Box> fakeEmptyBoxes; //Doesn't represent actual empty places, but an abstract box with negative height, so we can figure out the real height in the end

    for(auto iter = firstIterator; iter != this->skylineIntervalSet.end();) {
        height = std::max(height, iter->height);

        if(iter->rightBorder <= leftBorder + rect.width) {
            auto copyIter = iter;
            fakeEmptyBoxes.push_back(Box(currentLeftBorder, iter->height, iter->rightBorder - currentLeftBorder, -iter->height)); //Important - box is not real
            bool equalityBreak = std::fabs(iter->rightBorder - leftBorder - rect.width) <= 1e-5;

            currentLeftBorder = iter->rightBorder;
            iter ++;

            this->skylineIntervalSet.erase(copyIter);
            if(equalityBreak) {
                break;
            }
        } else {
            fakeEmptyBoxes.push_back(Box(currentLeftBorder, iter->height, leftBorder + rect.width - currentLeftBorder, -iter->height)); //Important - box is not real
            break;
        }
    }

    for(auto &emptyBox : fakeEmptyBoxes) {
        emptyBox.height += height;
        this->emptySpaces.pushEmpty(emptyBox);
    }

    this->skylineIntervalSet.insert(SkylineInterval(leftBorder + rect.width, height + rect.height));
}

std::multiset<SkylineSolver::SkylineInterval>::iterator SkylineSolver::findBest(const Rectangle &rect, Box &ret) {
    float currentLeftBorder = 0;
    auto leftPointer = this->skylineIntervalSet.begin(), rightPointer = this->skylineIntervalSet.begin();

    std::multiset<float> heights; float heightSum = 0;
    heights.insert(leftPointer->height);

    float minWaste = 1e9;
    auto retIterator = this->skylineIntervalSet.end();

    while(leftPointer != this->skylineIntervalSet.end() && currentLeftBorder + rect.width <= this->bin.width) {
        while(rightPointer->rightBorder < currentLeftBorder + rect.width) {
            float rightPointerLeftBorder = rightPointer->rightBorder;

            rightPointer ++;
            if(rightPointer == this->skylineIntervalSet.end()) {break;}
            heights.insert(rightPointer->height);

            heightSum += rightPointer->height * (rightPointer->rightBorder - rightPointerLeftBorder); //Heightsum counts up a rough estimate of the area under the rectangle,
        }
        if(rightPointer == this->skylineIntervalSet.end()) {break;}

        float extractedMax = *(heights.rbegin()), currentWaste = extractedMax * (rightPointer->rightBorder - currentLeftBorder) - heightSum; //Current waste is a rough estimate of the wasted area by this choice

        if(currentWaste < minWaste && extractedMax + rect.height <= this->bin.height) {
            minWaste = currentWaste;
            ret = Box(currentLeftBorder, extractedMax, rect.width, rect.height);
            retIterator = leftPointer;
        }

        heightSum -= leftPointer->height * (leftPointer->rightBorder - currentLeftBorder);

        heights.erase(heights.find(leftPointer->height));
        currentLeftBorder = leftPointer->rightBorder;
        leftPointer ++;

    }
    return retIterator;
}

void SkylineSolver::solve(std::vector<Rectangle> &shapesToPush, const float maxTime) {
    std::sort(shapesToPush.begin(), shapesToPush.end(),
    [](const Rectangle &a, const Rectangle &b) {
        return a.getArea() > b.getArea();
    });

    for(auto &shp : shapesToPush) {
        Box shapePlace;
        auto placeIterator = this->findBest(shp, shapePlace);
        if(placeIterator != this->skylineIntervalSet.end()) {
            this->packed.push_back(shapePlace);
            this->pushBox(shapePlace, placeIterator);
            shp.placed = true;
        }
    }

    for(auto &shp : shapesToPush) if(!shp.placed) {
        Box shapePlace;
        if(this->emptySpaces.findBest(shp, shapePlace)) {
            this->packed.push_back(shapePlace);
            this->emptySpaces.pushBox(shapePlace);
            shp.placed = true;
        }
    }
}

