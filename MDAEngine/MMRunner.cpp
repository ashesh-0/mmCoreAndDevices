#include "MMRunner.h"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstring>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <iostream>


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

CMMRunner::CMMRunner():
running_(false),
paused_(false),
pausedTime_(0),
pausedInterval_(0.1),
cancelled_(false)
{
    ofstream MyFile("test123.txt");
    MyFile << "Files can be tricky, but it is fun enough!";

   cout << "Hello world" <<endl ;
}

CMMRunner::~CMMRunner()
{
    try
    {
        // reset();
    }
    catch (...)
    {
        // LOG_ERROR(coreLogger_) << "Exception caught in CMMRunner desructor.";
    }
    // Not sure if we should delete the sequence_ or not. It is so because it is getting passed from 
    // outside and so should be deleted outside as well ?
    // delete sequence_;
}


int main(int argc, char **argv)
{
 auto var = CMMRunner();
}
