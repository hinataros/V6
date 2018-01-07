/**
   @author Sho Miyahara 2017
*/

#include "sharedMemory.hpp"

void RLS::SharedMemory::putData(SharedData *sharedData)
{
  temp = adr;
  data = (unsigned char *)sharedData;

  for(unsigned i=0; i<sizeof(SharedData); i++)
    *temp++ = *data++;
}
