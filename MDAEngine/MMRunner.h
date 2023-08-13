#ifndef _MMRunner_H_
#define _MMRunner_H_

#ifdef _MSC_VER
// We use exception specifications to instruct SWIG to generate the correct
// exception specifications for Java. Turn off the warnings that VC++ issues by
// the mere use of exception specifications (which VC++ does not implement).
#pragma warning(disable : 4290)
#endif
#include "MDAEvent.h"

class MDAEvent;

class CMMRunner
{
public:
    CMMRunner();
    ~CMMRunner();

    bool isRunning();
    bool isPaused();
    void cancel();
    void togglePause();
    void run(std::vector<MDAEvent> &events);
    bool runEvent(MDAEvent& event);
    bool waitUntilEvent(MDAEvent& event);
    void setupEvent(MDAEvent& event);
    unsigned char* execEvent(MDAEvent& event);
    void teardownEvent(MDAEvent& event);
    void resetTimer();
    float timeElapsed();
    bool checkCanceled();
    void finishRun();
    void prepareToRun();
    float getCurrentTime();
private:
    bool running_;
    bool paused_; 
    float pausedTime_;
    float pausedInterval_;
    bool cancelled_; 
    float startTime_;
};

#endif //_MMRunner_H_
