#ifndef _MDAGridPlan_H_
#define _MDAGridPlan_H_

#ifdef _MSC_VER
// We use exception specifications to instruct SWIG to generate the correct
// exception specifications for Java. Turn off the warnings that VC++ issues by
// the mere use of exception specifications (which VC++ does not implement).
#pragma warning(disable : 4290)
#endif

#include "MDAIndexGenerator.h"
class MDAIndexGenerator;

class GridPosition
{
public:
    GridPosition(float x, float y, float row, float col, bool is_relative);
    float x;
    float y;
    float row;
    float col;
    bool is_relative;
};

enum RelativeTo
{
    CENTER, TOPLEFT
};

enum OrderMode
{
    ROWWISE, COLWISE, ROWWISE_SNAKE, COLWISE_SNAKE, SPIRAL
};

class BaseGridPlan
{
public:
    BaseGridPlan( std::tuple<float, float> overlap, OrderMode mode);
    GridPosition nextGridPosition();
    unsigned int totalPositions();
    void initialize(float fovWidth, float fovHeight);
private:
    std::tuple<float,float> overlap_;
    OrderMode mode_;
    MDAIndexGenerator* idx_gen_;
    std::tuple<float,float> step_size_;
    bool isRelative_;
    std::tuple<float,float> getStepSize(float fovWidth, float fovHeight);
    virtual int numRows(float dy) = 0;    
    virtual int numCols(float dx) = 0 ;
    virtual float offsetX(float dx) = 0;
    virtual float offsetY(float dy) = 0;
    void resetIdxGenerator();
    
};

#endif // _MDAGridPlan_H_

