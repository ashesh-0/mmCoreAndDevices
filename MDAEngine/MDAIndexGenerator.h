#ifndef _TIMEPLAN_H_
#define _TIMEPLAN_H_

#ifdef _MSC_VER
// We use exception specifications to instruct SWIG to generate the correct
// exception specifications for Java. Turn off the warnings that VC++ issues by
// the mere use of exception specifications (which VC++ does not implement).
#pragma warning(disable : 4290)
#endif

// class TimePlan
// {
// public:
//     TimePlan();
//     float getInterval();
//     unsigned int getLoops();
//     float getDuration();
//     float getLastEventTime();
//     void setIntervalDuration(float interval, float duration);
//     void setIntervalLoops(float interval, unsigned int loops);
//     void setDurationLoops(float duration, unsigned int loops);
//     float getNextEventTime();
//     float getNextEventTimeSeconds();

// private:
//     // TODO: Implementation for Not ? 
//     float interval_; // Time between frames.
//     int loops_; // Number of frames (including the first frame).
//     float duration_; // Total duration of sequence
//     bool init_done_;
//     int loop_idx_;
//     float last_event_time_;
// };
#include <tuple>

class GridPosition
{
public:
    GridPosition(float x, float y, float row, float col, bool is_relative);
    float x;
    float y;
    float row;
    float col;
    bool is_relative;
}

enum RelativeTo
{
    CENTER, TOPLEFT
};

enum OrderMode
{
    ROWWISE, COLWISE, ROWWISE_SNAKE, COLWISE_SNAKE, SPIRAL
};

// Return the next (row,col) while iterating over a grid in the specified order.
class IndexGenerator
{
public:
    IndexGenerator(int rows, int cols, bool snake, bool row_wise);
    std::tuple<int, int> next();
private:
    int rows_;
    int cols_;
    bool snake_;
    bool row_wise_;
    int current_row_;
    int current_col_;
};
