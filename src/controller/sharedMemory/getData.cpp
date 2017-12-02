#include "sharedMemory.hpp"

void RLS::SharedMemory::getData(SharedData *sharedData)
{
  temp = adr;
  data = (unsigned char *)sharedData;

  for(unsigned i=0; i<sizeof(SharedData); i++)
    *data++ = *temp++;
}
