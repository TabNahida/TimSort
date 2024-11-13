#ifndef TIMSORT_HPP
#define TIMSORT_HPP

#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>


namespace timsort
{

const int MIN_MERGE = 32;

// Calculate the minimum run length for TimSort
inline int minRunLength(int n)
{
    int r = 0; // Becomes 1 if any 1 bits are shifted off
    while (n >= MIN_MERGE)
    {
        r |= (n & 1);
        n >>= 1;
    }
    return n + r;
}

// Perform binary insertion sort
template <typename RandomAccessIterator, typename Compare>
void binaryInsertionSort(RandomAccessIterator begin, RandomAccessIterator end, RandomAccessIterator start, Compare comp)
{
    if (begin == end)
        return;
    for (RandomAccessIterator i = start; i != end; ++i)
    {
        auto temp = *i;
        RandomAccessIterator left = begin;
        RandomAccessIterator right = i;
        while (left < right)
        {
            RandomAccessIterator mid = left + (right - left) / 2;
            if (comp(temp, *mid))
                right = mid;
            else
                left = mid + 1;
        }
        for (RandomAccessIterator j = i; j > left; --j)
            *j = *(j - 1);
        *left = temp;
    }
}

// Identify and make ascending runs
template <typename RandomAccessIterator, typename Compare>
RandomAccessIterator countRunAndMakeAscending(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
    RandomAccessIterator runHi = first + 1;
    if (runHi == last)
        return runHi;

    // Determine if the run is descending
    if (comp(*(runHi++), *first))
    {
        while (runHi != last && comp(*runHi, *(runHi - 1)))
            ++runHi;
        std::reverse(first, runHi);
    }
    else
    {
        while (runHi != last && !comp(*runHi, *(runHi - 1)))
            ++runHi;
    }
    return runHi;
}

// Merge two runs
template <typename RandomAccessIterator, typename Compare>
void timSortMerge(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, Compare comp)
{
    typedef typename std::iterator_traits<RandomAccessIterator>::value_type T;
    std::vector<T> left(first, middle);
    std::vector<T> right(middle, last);

    auto left_it = left.begin();
    auto right_it = right.begin();
    auto dest = first;

    while (left_it != left.end() && right_it != right.end())
    {
        if (comp(*right_it, *left_it))
            *dest++ = *right_it++;
        else
            *dest++ = *left_it++;
    }
    while (left_it != left.end())
        *dest++ = *left_it++;
    while (right_it != right.end())
        *dest++ = *right_it++;
}

// Core TimSort algorithm
template <typename RandomAccessIterator, typename Compare>
void timSort(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
    int n = last - first;
    if (n < 2)
        return;

    int minRun = minRunLength(n);
    std::vector<std::pair<RandomAccessIterator, RandomAccessIterator>> runs;

    RandomAccessIterator current = first;
    while (current != last)
    {
        RandomAccessIterator runEnd = countRunAndMakeAscending(current, last, comp);

        int runLen = runEnd - current;
        if (runLen < minRun)
        {
            int force = std::min(minRun, static_cast<int>(last - current));
            binaryInsertionSort(current, current + force, current + runLen, comp);
            runEnd = current + force;
        }

        runs.emplace_back(current, runEnd);
        current = runEnd;
    }

    while (runs.size() > 1)
    {
        std::vector<std::pair<RandomAccessIterator, RandomAccessIterator>> newRuns;

        for (size_t i = 0; i < runs.size(); i += 2)
        {
            if (i + 1 == runs.size())
            {
                newRuns.push_back(runs[i]);
            }
            else
            {
                auto runAStart = runs[i].first;
                auto runAEnd = runs[i].second;
                auto runBStart = runs[i + 1].first;
                auto runBEnd = runs[i + 1].second;

                timSortMerge(runAStart, runAEnd, runBEnd, comp);
                newRuns.emplace_back(runAStart, runBEnd);
            }
        }
        runs.swap(newRuns);
    }
}

// TimSort function for input iterators
template <typename InputIterator, typename OutputIterator,
          typename Compare = std::less<typename std::iterator_traits<InputIterator>::value_type>>
void timsort(InputIterator first, InputIterator last, OutputIterator result, Compare comp = Compare())
{
    typedef typename std::iterator_traits<InputIterator>::value_type T;
    std::vector<T> data(first, last);
    timSort(data.begin(), data.end(), comp);
    std::copy(data.begin(), data.end(), result);
}

} // namespace timsort

#endif // TIMSORT_HPP
