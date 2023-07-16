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
#include <vector>
#endif

using namespace std;

enum Indices {TIME, POSITION, GRID, CHANNEL, Z};
enum GridPlans {GridFromEdges, GridRelative, NoGrid};

int MaxNameLength = 256;
int MaxConfigLength = 2560;

class Position {
public:
    int x;
    int y;
    int z;
    char[MaxNameLength] name;
    // TODO: sequence?
    void setPosition(int x, int y, int z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    void setName(char[MaxNameLength] name) {
        // TODO: check pointer issue. if I change the argument, does the class name change? 
        strcpy(this->name, name);

    }

};

class Channel
{
public:
    char[MaxConfigLength] name;
    char[MaxNameLength] group;
    float exposure;
    bool doStack;
    float zOffset;
    uint acquireEvery;
    char[MaxNameLength] Camera;

    void setName(char[MaxConfigLength] name) {
        strcpy(this->name, name);
    }
    void setGroup(char[MaxNameLength] group) {
        strcpy(this->group, group);
    }
    void setExposure(float exposure) {
        this->exposure = exposure;
    }
    void setDoStack(bool doStack) {
        this->doStack = doStack;
    }
    void setZOffset(float zOffset) {
        this->zOffset = zOffset;
    }
    void setAcquireEvery(uint acquireEvery) {
        this->acquireEvery = acquireEvery;
    }
    void setCamera(char[MaxNameLength] Camera) {
        strcpy(this->Camera, Camera);
    }
};

vector<Indices> DefaultAxisOrder = {TIME, POSITION, GRID, CHANNEL, Z};


MDASequence::MDASequence(std::map<std::string, float> timePlan, std::vector<Position> stagePositions, std::map<std::string,int> gridPlan, 
    std::vector<Channel> channels, std::map<std::string, int> zPlan):
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