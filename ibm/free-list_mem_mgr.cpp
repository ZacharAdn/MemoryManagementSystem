#include "memmgr.h"
#include "classes.h"

int main(int argc, char* argv[])
  {
  for(long i = 0; i < 500000; ++i)
    {
    JobScheduler* scheduler = new JobScheduler;
    Coordinate*   point  = new Coordinate;
    Complex*      number = new Complex;

    delete scheduler;
    delete point;
    delete number;
    }
  return 0;
  }

