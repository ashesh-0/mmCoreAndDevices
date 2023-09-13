%module mmrunner
%{
#define SWIG_FILE_WITH_INIT
#include "MDAPosition.h"
#include "MDAEvent.h"
#include "MMRunner.h"
%}

%include "MDAPosition.h"
%include "MDAEvent.h"
%include "MMRunner.h"

// swig -c++ -python mmrunner.i 
// c++ -c mmrunner_wrap.cxx -I/home/ubuntu/miniconda3/envs/micro-manager/include/python3.7m -fPIC
// c++ -shared mmrunner_wrap.o  -o _mmrunner.o