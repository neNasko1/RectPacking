#include "EmptyRectangleSet.h"
#include <vector>
#include <algorithm>

EmptyRectanglesSet::EmptyRectanglesSet() : emptyRectangles() {}

EmptyRectanglesSet::EmptyRectanglesSet(const Box &_rect) : emptyRectangles() {this->emptyRectangles.push_back(_rect);}

void EmptyRectanglesSet::pushBox(const Box &shape) {
    std::vector<Box> newEmptyRectangles;
    for(const auto &it : this->emptyRectangles) {
        if(areColliding(it, shape)) {
            newEmptyRectangles.push_back(Box(it.x, it.y, shape.x - it.x, it.height));
            newEmptyRectangles.push_back(Box(it.x, it.y, it.width, shape.y - it.y));
            newEmptyRectangles.push_back(Box(shape.x + shape.width, it.y, it.x + it.width - shape.x - shape.width, it.height));
            newEmptyRectangles.push_back(Box(it.x, shape.y + shape.height, it.width, it.y + it.height - shape.y - shape.height));
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
                if(shpBigger.contains(shp)) {
                    flag = false;
                    break;
                }
            }
            if(flag) {
                this->emptyRectangles.push_back(shp);
            }
        }
    }

#ifdef DEBUGOUTPUTS
    std::cout << "Pushing shape" << std::endl;
    for(const auto &emp : this->emptyRectangles) {
        std::cout << emp << " ";
    }
    std::cout << std::endl;
#endif
}

void EmptyRectanglesSet::pushEmpty(const Box &emptRect) {
    this->emptyRectangles.push_back(emptRect);
#ifdef DEBUGOUTPUTS
    std::cout << "Pushing empty" << std::endl;
    for(const auto &emp : this->emptyRectangles) {
        std::cout << emp << " ";
    }
    std::cout << std::endl;
#endif
}

bool EmptyRectanglesSet::findBest(const Rectangle &rect, Box &ret) {
    int minWaste = 1e9;
    bool flag = false;
    for(const auto &emp : this->emptyRectangles) {
        if(emp.width >= rect.width && emp.height >= rect.height) {
            int nowWaste = emp.width - rect.width + emp.height - rect.height;
            if(nowWaste < minWaste) {
                minWaste = nowWaste;
                ret = Box(emp.x, emp.y, rect.width, rect.height);
                flag = true;
            }
        }
    }
    return flag;
}
