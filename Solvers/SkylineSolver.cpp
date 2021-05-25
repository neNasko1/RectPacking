#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

#include "../Shapes.h"
#include "../Solvers.h"
#include "SkylineSolver.h"

SkylineSolver::SkylineSolver(const Rectangle &_bin) : Solver(_bin), skylineIntervalSet() {
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
    float height = 0;
    for(auto iter = firstIterator; iter != this->skylineIntervalSet.end();) {
        height = std::max(height, iter->height);
        if(iter->rightBorder <= leftBorder + rect.width) {
            auto copyIter = iter;
            iter ++;
            this->skylineIntervalSet.erase(copyIter);
        } else {
            break;
        }
    }
    this->skylineIntervalSet.insert(SkylineInterval(leftBorder + rect.width, rect.height + height));
}

std::multiset<SkylineSolver::SkylineInterval>::iterator SkylineSolver::findBest(const Rectangle &rect, Box &ret) {
    float nowLeftBorder = 0;
    auto leftPointer = this->skylineIntervalSet.begin(), rightPointer = this->skylineIntervalSet.begin();

    std::multiset<float> heights;
    heights.insert(leftPointer->height);

    float minWaste = 1e9;
    auto retIterator = this->skylineIntervalSet.end();

    for(; leftPointer != this->skylineIntervalSet.end() && nowLeftBorder + rect.width <= this->bin.width; leftPointer ++) {
        while(rightPointer != this->skylineIntervalSet.end() && rightPointer->rightBorder < nowLeftBorder + rect.width) {
            rightPointer ++;
            heights.insert(rightPointer->height);
        }
        if(rightPointer == this->skylineIntervalSet.end()) {break;}

        float extractedMax = *(heights.rbegin());
        if(extractedMax < minWaste) {
            minWaste = extractedMax;
            ret = Box(nowLeftBorder, minWaste, rect.width, rect.height);
            retIterator = leftPointer;
        }

        heights.erase(heights.find(leftPointer->height));
        nowLeftBorder = leftPointer->rightBorder;
    }
    if(ret.y + ret.height > this->bin.height) {
        return this->skylineIntervalSet.end();
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
}

