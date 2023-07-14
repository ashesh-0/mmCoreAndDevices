#include "MDASequence.h"
#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstring>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iostream>

#include <string>
#include <vector>
#include <map>

#ifndef _WINDOWS
// Needed on Unix for getcwd() and gethostname()
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#else
// for _getcwd
#include <direct.h>
#endif

using namespace std;

MDASequence::MDASequence(std::map<std::string, float> timePlan, std::vector<int> statePositions, std::map<std::string,int> gridPlan, 
    std::map<std::string, int> zPlan):
uid_(0)
{
    ;
}

// int main(int argc, char **argv)
// {
//     std::map<std::string, float> timePlan = {{"a", 1.0}, {"b", 2.0}};
//     std::vector<int> statePositions = {1, 2, 3};
//     std::map<std::string,int> gridPlan = {{"a", 1}, {"b", 2}}; 
//     std::map<std::string, int> zPlan = {{"a", 1}, {"b", 2}};
//     auto var = MDASequence(timePlan, statePositions, gridPlan, zPlan);
// }