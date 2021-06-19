#pragma once
#ifndef RANDOMSORTER_TPP
#define RANDOMSORTER_TPP

#include <vector>
#include <algorithm>

#include "RandomSorter.h"
#include "../Shapes/Shapes.h"

template<class RandomIterator, class T>
void randomSort(const RandomIterator begin, const RandomIterator end, unsigned long long (*evaluator)(T)) {
    //Utility to generate 32 bit random integer
    auto randULL = []() -> unsigned long long {
        using ull = unsigned long long;
        ull ret = ((ull)rand() << (ull)48) + ((ull)rand() << (ull)32) + ((ull)rand() << (ull)16) + (ull)rand();
        return ret;
    };

    // Generate and sort value-index pairs
    std::vector<std::pair<unsigned int, int> > valueIndexPairs;
    for(auto it = begin; it != end; it ++) {
        int evaluatedValue = evaluator(*it);
        valueIndexPairs.push_back({randULL() % evaluatedValue, it - begin});
    }
    std::sort(valueIndexPairs.begin(), valueIndexPairs.end());

    //Retrieve real sorting
    std::vector<bool> lookedAt(end - begin, false);
    for(int i = 0; i < (end - begin); i ++) {
        if(lookedAt[i]) {continue;}
        auto tmp = *(begin + i);
        int currentInd = i;
        while(valueIndexPairs[currentInd].second != i) {
            lookedAt[currentInd] = true;
            *(begin + currentInd) = *(begin + valueIndexPairs[currentInd].second);
            currentInd = valueIndexPairs[currentInd].second;
        }
        lookedAt[currentInd] = true;
        *(begin + currentInd) = tmp;
    }
}

#endif
