#ifndef __COMPLEX_H__
#define __COMPLEX_H__

#include <string>
#include <vector>

extern MemoryManager gMemoryManager;


class Complex 
  {
public:
  Complex() : r(0), c(0) {}
  Complex (double a, double b): r (a), c (b) {}
  inline void* operator new(size_t size)
    { 
    return gMemoryManager.allocate(sizeof(Complex));
    }

  inline void operator delete(void* object)
    {
    gMemoryManager.free(object);
    }

   
  private:
    double r; // Real Part
    double c; // Complex Part
  };

class Coordinate
  {
  int CoordX;
  int CoordY;
  int CoordZ;
  std::string name;
  public:  
    Coordinate() :CoordX(0), CoordY(0), CoordZ(0), name("") {}
    inline void* operator new(size_t size)
      { 
      return gMemoryManager.allocate(sizeof(Coordinate));
      }

    inline void  operator delete(void* object)
      {
      gMemoryManager.free(object);
      }

  };

class JobScheduler
  {
  std::vector<int> JobNumber;
  std::vector<int> MaxJobTime;
  int              StartTime;
  public:
    JobScheduler() {}   
    inline void* operator new(size_t size)
      { 
      return gMemoryManager.allocate(sizeof(JobScheduler));
      }

    inline void  operator delete(void* object)
      {
      gMemoryManager.free(object);
      }

  };


const int JOB_SCHEDULER_SIZE = sizeof(JobScheduler);
const int COMPLEX_SIZE = sizeof(Complex);
const int COORDINATE_SIZE = sizeof(Coordinate);
const int POOL_SIZE = 1024; //number of elements in a single pool
                            //can be chosen based on application requirements 

const int MAX_BLOCK_SIZE = 36; //depending on the application it may change 
                               //In above case it came as 36

#endif