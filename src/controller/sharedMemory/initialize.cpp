/**
   @author Sho Miyahara 2017
*/

#include "sharedMemory.hpp"

void RLS::SharedMemory::initialize()
{
  key = 1;

  if((id = shmget(key, SHAREDMEMORYSIZE, IPC_CREAT|0666)) < 0){
    perror("shmget");
    exit(id);
  }

  if((adr = (unsigned char *)shmat(id, NULL, 0)) == (unsigned char *)-1){
    perror("shmat");
    exit(1);
  }

  puts("Shared memory initialized.");
}
