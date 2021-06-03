#include "EmptyRectangleSet.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <math.h>

namespace rectpack {

EmptyRectanglesSet::EmptyRectanglesSet() : emptyRectangles(), fullBin() {}

EmptyRectanglesSet::EmptyRectanglesSet(const Box &_rect) : emptyRectangles(), fullBin(_rect) {}

EmptyRectanglesSet::~EmptyRectanglesSet() {}

//Pushes and calculates new empty rectangles, only works for rectangles with rotations 0/90
void EmptyRectanglesSet::pushBox(const Box &shape) {
    Box shapeCopy;
    if(std::fabs(shape.angle) <= 1e-5) {
        shapeCopy = shape;
    } else {
        shapeCopy = Box(shape.x - shape.height, shape.y, shape.height, shape.width);
    }
    std::vector<Box> newEmptyRectangles;
    for(const auto &it : this->emptyRectangles) {
        if(areCollidingAABB(it, shapeCopy)) {
            newEmptyRectangles.push_back(Box(it.x, it.y, shapeCopy.x - it.x, it.height));
            newEmptyRectangles.push_back(Box(it.x, it.y, it.width, shapeCopy.y - it.y));
            newEmptyRectangles.push_back(Box(shapeCopy.x + shapeCopy.width, it.y, it.x + it.width - shapeCopy.x - shapeCopy.width, it.height));
            newEmptyRectangles.push_back(Box(it.x, shapeCopy.y + shapeCopy.height, it.width, it.y + it.height - shapeCopy.y - shapeCopy.height));
        } else {
            newEmptyRectangles.push_back(it);
        }
    }
    this->emptyRectangles.resize(0);
    std::sort(newEmptyRectangles.begin(), newEmptyRectangles.end(),
        [](const Box &a, const Box &b) {
            return a.getArea() > b.getArea();
        });

    for(const auto &shp : newEmptyRectangles) {
        if(shp.width > 0 && shp.height > 0) {
            bool flag = true;
            for(const auto &shpBigger : this->emptyRectangles) {
                if(shpBigger.containsAABB(shp)) {
                    flag = false;
                    break;
                }
            }
            if(flag) {
                this->emptyRectangles.push_back(shp);
            }
        }
    }
}

void EmptyRectanglesSet::pushEmpty(const Box &emptRect) {
    this->emptyRectangles.push_back(emptRect);
}

void EmptyRectanglesSet::clear() {
    this->emptyRectangles.resize(0);
    this->pushEmpty(this->fullBin);
}

bool EmptyRectanglesSet::findBest(const Rectangle &rect, Box &ret) {
    float minWaste = 1e9;
    bool flag = false;
    for(const auto &emp : this->emptyRectangles) {
        if(emp.width >= rect.width && emp.height >= rect.height) {
            float currentWaste = (emp.width - rect.width) * (emp.height) + (emp.height - rect.height) * (emp.width);
            if(currentWaste < minWaste) {
                minWaste = currentWaste;
                ret = Box(emp.x, emp.y, rect, 0);
                flag = true;
            }
        }

        if(emp.width >= rect.height && emp.height >= rect.width) {
            float currentWaste = (emp.width - rect.height) * (emp.height) + (emp.height - rect.width) * (emp.width);
            if(currentWaste < minWaste) {
                minWaste = currentWaste;
                ret = Box(emp.x + rect.height, emp.y, rect, 90);
                flag = true;
            }
        }
    }
    return flag;
}

bool EmptyRectanglesSet::findBestRotation(const Rectangle &rect, Box &ret, Box &boundingBox) {
    const float INCREMENT = 0.01, PI = 3.14159265;
    float minWaste = 1e9;
    bool flag = false;
    for(float angle = 0; angle < PI * 2; angle += INCREMENT) {

        float transformWidthxDelta = rect.width * cos(angle), transformWidthyDelta = rect.width * sin(angle);
        float transformHeightxDelta = rect.height * cos(angle + PI / 2.), transformHeightyDelta = rect.height * sin(angle + PI / 2.);

        float AABBleftx  = std::min(std::min(0.f, transformWidthxDelta), std::min(transformHeightxDelta, transformWidthxDelta + transformHeightxDelta));
        float AABBrightx = std::max(std::max(0.f, transformWidthxDelta), std::max(transformHeightxDelta, transformWidthxDelta + transformHeightxDelta));
        float AABBdowny  = std::min(std::min(0.f, transformWidthyDelta), std::min(transformHeightyDelta, transformWidthyDelta + transformHeightyDelta));
        float AABBupy    = std::max(std::max(0.f, transformWidthyDelta), std::max(transformHeightyDelta, transformWidthyDelta + transformHeightyDelta));

        Rectangle transformRect(AABBrightx - AABBleftx, AABBupy - AABBdowny);
        Box nowRet;
        if(this->findBest(transformRect, nowRet)) {
            float currentWaste = transformRect.getArea() - rect.getArea();
            if(minWaste > currentWaste) {
                minWaste = currentWaste;
                boundingBox = nowRet;
                ret = Box(nowRet.x - AABBleftx, nowRet.y - AABBdowny, rect, angle * 360.f / (PI * 2.f));
                flag = true;
            }
        }
    }
    return flag;
}

};
