#pragma once
#ifndef RANDOMSORTER_H
#define RANDOMSORTER_H

/**
 * Function which orders elements randomly, but the bigger elements have a bigger chance to be in the end.
 * @param begin Begin iterator.
 * @param end End iterator.
 * @param evaluator Function which evaluates the elements.
 */
template<class RandomIterator, class T>
void randomSort(const RandomIterator begin, const RandomIterator end, unsigned long long (*evaluator)(T));

#endif // RANDOMSORTER_H
