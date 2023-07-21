#include "TimePlan.h"
#include <ctime>
#include <stdexcept>
#include <iostream>

using namespace std;

TimePlan::TimePlan():
    interval_(0),
    loops_(0),
    duration_(0),
    loop_idx_(0),
    last_event_time_(InvalidTime),
    init_done_(false)
{
    ;
}


void TimePlan::setIntervalDuration(float interval, float duration)
{
    interval_ = interval;
    duration_ = duration;
    loops_ = static_cast<int> (duration / interval + 1);
    init_done_ = true;
}

void TimePlan::setIntervalLoops(float interval, unsigned int loops)
{
    interval_ = interval;
    loops_ = loops;
    // Note it was interval * loops. But it should be interval * (loops-1) ? 
    duration_ = interval * (loops-1);
    init_done_ = true;
}

void TimePlan::setDurationLoops(float duration, unsigned int loops)
{
    duration_ = duration;
    loops_ = loops;
    // Note it was duration / loops. But it should be duration / (loops-1) ?
    interval_ = duration / (loops-1);
    init_done_ = true;
}

float TimePlan::getInterval()
{
    if (init_done_)
        return interval_;
    else
        throw runtime_error("TimePlan not initialized");
}

unsigned int TimePlan::getLoops()
{
    if (init_done_)
        return loops_;
    else
        throw runtime_error("TimePlan not initialized");
}

float TimePlan::getDuration()
{
    if (init_done_)
        return duration_;
    else
        throw runtime_error("TimePlan not initialized");
}

float TimePlan::getNextEventTime()
{
    if (!init_done_)
        throw runtime_error("TimePlan not initialized");

    if (loop_idx_ >= loops_)
        return InvalidTime;

    cout << "loops" << loops_ << " loop_idx " << loop_idx_ << endl;
    last_event_time_ = interval_*loop_idx_;
    loop_idx_++;
    return last_event_time_;

}
float TimePlan::getLastEventTime()
{
    if (!init_done_)
        throw runtime_error("TimePlan not initialized");
    return last_event_time_;
}

float TimePlan::getNextEventTimeSeconds(){
    auto next_time = getNextEventTime();
    if (next_time == InvalidTime)
        return InvalidTime;
    else
        return next_time / CLOCKS_PER_SEC;
}



// multiphase timeplan
MultiPhaseTimePlan::MultiPhaseTimePlan():
    init_done_(false),
    loop_idx_(0),
    timeplan_idx_(0),
    cur_timeplan_start_time_(0)
{
    ;
}
MultiPhaseTimePlan::~MultiPhaseTimePlan()
{
    timeplans_.clear();
}

void MultiPhaseTimePlan::setIntervalDuration(float interval, float duration)
{
    auto timeplan = new TimePlan();
    timeplan->setIntervalDuration(interval, duration);
    timeplans_.push_back(timeplan);
    init_done_ = true;
}

void MultiPhaseTimePlan::setIntervalLoops(float interval, unsigned int loops)
{
    auto timeplan = new TimePlan();
    timeplan->setIntervalLoops(interval, loops);
    timeplans_.push_back(timeplan);
    init_done_ = true;
}
void MultiPhaseTimePlan::setDurationLoops(float duration, unsigned int loops)
{
    auto timeplan = new TimePlan();
    timeplan->setDurationLoops(duration, loops);
    timeplans_.push_back(timeplan);
    init_done_ = true;
}

float MultiPhaseTimePlan::getNextEventTime(){
    if (init_done_){
        auto timeplan = timeplans_[timeplan_idx_];
        auto next_time = timeplan->getNextEventTime();
        if (next_time != InvalidTime)
            return cur_timeplan_start_time_ + next_time;
        else
        {
            auto last_event_time = timeplan->getLastEventTime();
            cur_timeplan_start_time_ += last_event_time;

            timeplan_idx_ += 1;
            if (timeplan_idx_ > timeplans_.size())
                return InvalidTime;
            else
            {
                timeplans_[timeplan_idx_]->getNextEventTime(); // this will return 0 since it the first call. ignore it.
                return cur_timeplan_start_time_ + timeplans_[timeplan_idx_]->getNextEventTime();
            }
        }
       
    }
    else
        throw runtime_error("TimePlan not initialized");
}

float MultiPhaseTimePlan::getNextEventTimeSeconds(){
    auto next_time = getNextEventTime();
    if (next_time == InvalidTime)
        return InvalidTime;
    else
        return next_time / CLOCKS_PER_SEC;
}

int main(){
    auto timeplan = MultiPhaseTimePlan();
    timeplan.setIntervalDuration(4, 10);
    timeplan.setIntervalLoops(2, 3);
    // timeplan.setDurationLoops(3, 3);
    cout << timeplan.getNextEventTime()  << endl;
    cout << timeplan.getNextEventTime() << endl;
    cout << timeplan.getNextEventTime() << endl;
    cout << timeplan.getNextEventTime() << endl;
    cout << timeplan.getNextEventTime() << endl;

    return 0;
    }