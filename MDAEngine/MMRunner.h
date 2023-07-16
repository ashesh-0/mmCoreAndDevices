#ifndef _MMCORE_H_
#define _MMCORE_H_

#ifdef _MSC_VER
// We use exception specifications to instruct SWIG to generate the correct
// exception specifications for Java. Turn off the warnings that VC++ issues by
// the mere use of exception specifications (which VC++ does not implement).
#pragma warning(disable : 4290)
#endif

// #include "MMCore.h"
#include "MDASequence.h"
class MDASequence;

class CMMRunner
{
public:
    CMMRunner();
    ~CMMRunner();

    bool isRunning();
private:
    bool running_;
    bool paused_; 
    float pausedTime_;
    float pausedInterval_;
    bool cancelled_; 
    MDASequence *sequence_ = nullptr;
};

#endif //_MMCORE_H_
