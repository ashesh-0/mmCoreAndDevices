#ifndef _MMCORE_H_
#define _MMCORE_H_

#ifdef _MSC_VER
// We use exception specifications to instruct SWIG to generate the correct
// exception specifications for Java. Turn off the warnings that VC++ issues by
// the mere use of exception specifications (which VC++ does not implement).
#pragma warning(disable : 4290)
#endif

#include <map>
#include <vector>
#include <string>

class MDASequence;

class MDASequence
{
public:
    MDASequence(std::map<std::string, float> timePlan, std::vector<int> statePositions, std::map<std::string,int> gridPlan, 
    std::map<std::string, int> zPlan);
private:
    int uid_;
};

#endif //_MMCORE_H_
