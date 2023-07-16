#ifndef _MMCORE_H_
#define _MMCORE_H_

#ifdef _MSC_VER
// We use exception specifications to instruct SWIG to generate the correct
// exception specifications for Java. Turn off the warnings that VC++ issues by
// the mere use of exception specifications (which VC++ does not implement).
#pragma warning(disable : 4290)
#endif

#include <ctime>
#include <vector>

#define InvalidTime -955.0

class TimePlan;
class MultiPhaseTimePlan;

class TimePlan
{
public:
    TimePlan();
    float getInterval();
    unsigned int getLoops();
    float getDuration();
    float getLastEventTime();
    void setIntervalDuration(float interval, float duration);
    void setIntervalLoops(float interval, unsigned int loops);
    void setDurationLoops(float duration, unsigned int loops);
    float getNextEventTime();
    float getNextEventTimeSeconds();

private:
    // TODO: Implementation for Not ? 
    float interval_; // Time between frames.
    int loops_; // Number of frames (including the first frame).
    float duration_; // Total duration of sequence
    bool init_done_;
    int loop_idx_;
    float last_event_time_;
};

class MultiPhaseTimePlan
{
public:
    MultiPhaseTimePlan();
    ~MultiPhaseTimePlan();
    float getNextEventTime();
    void setIntervalDuration(float interval, float duration);
    void setIntervalLoops(float interval, unsigned int loops);
    void setDurationLoops(float duration, unsigned int loops);
    float getNextEventTimeSeconds();

private:
    bool init_done_;
    int loop_idx_;
    std::vector<TimePlan*> timeplans_;
    unsigned int timeplan_idx_;
    float cur_timeplan_start_time_;
};
#endif //_MMCORE_H_
