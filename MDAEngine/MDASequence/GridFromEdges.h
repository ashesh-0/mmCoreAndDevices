#ifndef _GridFromEdges_H_
#define _GridFromEdges_H_

#ifdef _MSC_VER
// We use exception specifications to instruct SWIG to generate the correct
// exception specifications for Java. Turn off the warnings that VC++ issues by
// the mere use of exception specifications (which VC++ does not implement).
#pragma warning(disable : 4290)
#endif

#include "BaseGridPlan.h"
class BaseGridPlan;

class GridFromEdges : public BaseGridPlan
{
public:
    GridFromEdges( std::tuple<float, float> overlap, OrderMode mode, float top, float left, float bottom, float right);
    int numRows(float dy);
    int numCols(float dx);
    float offsetX(float dx);
    float offsetY(float dy);
private:
    float top_;
    float left_;
    float bottom_;
    float right_;
};

#endif // _GridFromEdges_H_