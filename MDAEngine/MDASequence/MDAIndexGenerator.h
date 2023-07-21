#ifndef _MDAIndexGenerator_H_
#define _MDAIndexGenerator_H_

#ifdef _MSC_VER
// We use exception specifications to instruct SWIG to generate the correct
// exception specifications for Java. Turn off the warnings that VC++ issues by
// the mere use of exception specifications (which VC++ does not implement).
#pragma warning(disable : 4290)
#endif

#include <tuple>

// Return the next (row,col) while iterating over a grid in the specified order.
class MDAIndexGenerator
{
public:
    MDAIndexGenerator(int rows, int cols, bool snake, bool row_wise);
    std::tuple<int, int> next();
    void reset();
    unsigned int totalPositions();
private:
    int rows_;
    int cols_;
    bool snake_;
    bool row_wise_;
    int current_row_;
    int current_col_;
    int total_positions_;
};

#endif // _MDAIndexGenerator_H_