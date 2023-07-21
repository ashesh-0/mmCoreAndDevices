#ifndef _WINDOWS
// Needed on Unix for getcwd() and gethostname()
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#else
// for _getcwd
#include <direct.h>
#include <vector>
#endif

#include "GridFromEdges.h"
#include <cmath>
#include <iostream>
using namespace std;

GridFromEdges::GridFromEdges( std::tuple<float, float> overlap, OrderMode mode, float top, float left, float bottom, float right):
    BaseGridPlan(overlap, mode),
    top_(top),
    left_(left),
    bottom_(bottom),
    right_(right)
{
    ;
}

int GridFromEdges::numRows(float dy)
{
    float total_height = abs(top_ - bottom_) + dy;
    return ceil(total_height / dy);
}

int GridFromEdges::numCols(float dx)
{
    float total_width = abs(left_ - right_) + dx;
    return ceil(total_width / dx);
}

float GridFromEdges::offsetX(float dx)
{
    return fmin(left_, right_);
}

float GridFromEdges::offsetY(float dy)
{
    return fmin(top_, bottom_);
}

int main()
{
    auto overlap = std::tuple<float, float>(0.0, 0.0);
    auto mode = OrderMode::ROWWISE;
    float top = 0.0;
    float left = 0.0;
    float bottom = 10.0;
    float right = 20.0;
    auto obj = GridFromEdges( overlap, mode, top, left, bottom, right);
    obj.initialize(10.0, 10.0);
    auto next = obj.nextGridPosition();
    cout << "x: " << next.x << " y:" << next.y << " row:" << next.row <<" col:"<< next.col <<  endl;
    next = obj.nextGridPosition();
    cout << "x: " << next.x << " y:" << next.y << " row:" << next.row <<" col:"<< next.col <<  endl;
    next = obj.nextGridPosition();
    cout << "x: " << next.x << " y:" << next.y << " row:" << next.row <<" col:"<< next.col <<  endl;
    
}