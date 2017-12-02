#include "sharedMemory.hpp"

void RLS::SharedMemory::finalize()
{
  if(shmdt(adr)==-1){
    perror("shmdt");
  }

  if(shmctl(id, IPC_RMID, NULL) < 0)
    perror("shmctl");

  puts("Shared memory segment marked for deletion");
}
