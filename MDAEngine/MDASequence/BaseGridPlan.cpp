#include "BaseGridPlan.h"
#include <climits>

using namespace std;


GridPosition::GridPosition(float x, float y, float row, float col, bool is_relative):
x(x),
y(y),
row(row),
col(col),
is_relative(is_relative)
{
    ;
}

BaseGridPlan::BaseGridPlan(std::tuple<float, float> overlap, OrderMode mode):
overlap_(overlap),
mode_(mode),
isRelative_(false)
{
    ;
}
void BaseGridPlan::initialize(float fovWidth, float fovHeight)
{
    step_size_ = getStepSize(fovWidth, fovHeight);
    float dx = std::get<0>(step_size_);
    float dy = std::get<1>(step_size_);
    auto num_rows = numRows(dy);
    auto num_cols = numCols(dx);
    bool snake = mode_== OrderMode::COLWISE_SNAKE || mode_== OrderMode::ROWWISE_SNAKE;
    bool row_wise = mode_== OrderMode::ROWWISE || mode_== OrderMode::ROWWISE_SNAKE;
    idx_gen_ = new MDAIndexGenerator(num_rows, num_cols, snake, row_wise);
}
std::tuple<float,float> BaseGridPlan::getStepSize(float fovWidth, float fovHeight)
{
    float dx = fovWidth - (fovWidth*std::get<0>(overlap_))/100.0 ; // TODO: what is the meaning of overlap? 
    float dy = fovHeight - (fovHeight*std::get<1>(overlap_))/100.0 ;
    return std::make_tuple(dx, dy);
}
GridPosition BaseGridPlan::nextGridPosition()
{
    tuple<int,int> idx = idx_gen_->next();
    auto row = std::get<0>(idx);
    auto col = std::get<1>(idx);
    if (row == INT_MIN && col == INT_MIN)
    {
        return GridPosition(INT_MIN, INT_MIN, INT_MIN, INT_MIN, isRelative_);
    }

    auto dx = get<0>(step_size_);
    auto x = dx* col + offsetX(dx);
    
    auto dy = get<1>(step_size_);
    auto y = dy* row + offsetY(dy);

    return GridPosition(x, y, row, col, isRelative_);
}

void BaseGridPlan::resetIdxGenerator()
{
    idx_gen_->reset();
}

unsigned int BaseGridPlan::totalPositions()
{
    return idx_gen_->totalPositions();
}
