#define SHAREDMEMORYSIZE 1000000

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "sharedData.hpp"

namespace RLS{
  class SharedMemory{
  public:
    key_t key;
    int id;
    unsigned char *adr, *temp, *data;

    void initialize();
    void finalize();
    void putData(SharedData*);
    void getData(SharedData*);
  };
}
